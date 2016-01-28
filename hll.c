/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  implements hll directives:
*               .IF, .WHILE, .REPEAT, .ELSE, .ELSEIF, .ENDIF,
*               .ENDW, .UNTIL, .UNTILCXZ, .BREAK, .CONTINUE.
*               also handles C operators:
*               ==, !=, >=, <=, >, <, &&, ||, &, !,
*               and flags:
*               ZERO?, CARRY?, SIGN?, PARITY?, OVERFLOW?
*
****************************************************************************/

#include <ctype.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "equate.h"
#include "label.h"
#include "expreval.h"
#include "types.h"
#include "hll.h"
#include "segment.h"
#include "listing.h"
#include "lqueue.h"
#include "myassert.h"

int Tokenize(char *, unsigned int, struct asm_tok[], unsigned int);

#define LABELSIZE 8
#define LABELSGLOBAL 0 /* make the generated labels global */
#define JMPPREFIX      /* define spaces before "jmp" or "loop" */
#define LABELFMT "@C%04X"

/* v2.10: static variables moved to ModuleInfo */
#define HllStack ModuleInfo.g.HllStack
#define HllFree  ModuleInfo.g.HllFree

#if LABELSGLOBAL
#define LABELQUAL "::"
#else
#define LABELQUAL ":"
#endif

#ifdef DEBUG_OUT
#define EOLCHAR '^'  /* this allows better displays */
#define EOLSTR  "^"
#else
#define EOLCHAR '\n' /* line termination char in generated source */
#define EOLSTR  "\n"
#endif

/* values for struct hll_item.cmd */
enum hll_cmd {
  HLL_IF,
  HLL_WHILE,
  HLL_REPEAT,
  HLL_BREAK,  /* .IF behind .BREAK or .CONTINUE */
  HLL_FOR,
};

/* index values for struct hll_item.labels[] */
enum hll_label_index {
  LTEST,      /* test (loop) condition  */
  LEXIT,      /* block exit             */
  LSTART,     /* loop start             */
  LSKIP,      /* skip counters          */
  LCONT,      /* for .CONTINUE in .for */
};

/* values for struct hll_item.flags */
enum hll_flags {
  HLLF_ELSEOCCURED = 0x01,
};


/* item for .IF, .WHILE, .REPEAT, .FOR, ... */
struct hll_item {
  struct hll_item     *next;
  uint_32             labels[5];      /* labels for LTEST, LEXIT, LSTART, LSKIP */
  char                *condlines;     /* .WHILE-blocks only: lines to add after 'test' label */
  char                *counterlines;  /* pointer to allocated memory for counters */
  uint_32             cmcnt;          /* comma counter  */
  enum hll_cmd        cmd;            /* start cmd (IF, WHILE, REPEAT) */
  bool                cond;          /* condision  */
  enum hll_flags      flags;          /* v2.08: added */
};

/* v2.08: struct added */
struct hll_opnd {
  char    *lastjmp;
  uint_32 lasttruelabel; /* v2.08: new member */
};

static ret_code GetExpression(struct hll_item *hll, int *i, struct asm_tok[], int ilabel, bool is_true, char *buffer, struct hll_opnd *);

/* c binary ops.
* Order of items COP_EQ - COP_LE  and COP_ZERO - COP_OVERFLOW
* must not be changed.
*/
enum c_bop {
  COP_NONE,
  COP_EQ,   /* == */
  COP_NE,   /* != */
  COP_GT,   /* >  */
  COP_LT,   /* <  */
  COP_GE,   /* >= */
  COP_LE,   /* <= */
  COP_AND,  /* && */
  COP_OR,   /* || */
  COP_ANDB, /* &  */
  COP_NEG,  /* !  */
  COP_ZERO, /* ZERO?   not really a valid C operator */
  COP_CARRY,/* CARRY?  not really a valid C operator */
  COP_SIGN, /* SIGN?   not really a valid C operator */
  COP_PARITY,  /* PARITY?   not really a valid C operator */
  COP_OVERFLOW, /* OVERFLOW? not really a valid C operator */
  //added by habran
  COP_LESS,/* SIGN=OVERFLOW  not really a valid C operator */
  COP_GREATER, /* SIGNED ZERO OR CARRY   not really a valid C operator */
  COP_ABOVE,  /* ZERO OR CARRY  not really a valid C operator */
  COP_EQUAL,
  COP_BELOW
};

/* items in table below must match order COP_ZERO - COP_OVERFLOW */
static const char flaginstr[] = { 'z', 'c', 's', 'p', 'o', 'l', 'g', 'a', 'e', 'b' };

/* items in tables below must match order COP_EQ - COP_LE */
static const char unsigned_cjmptype[] = { 'z', 'z', 'a', 'b', 'b', 'a' };
static const char signed_cjmptype[] = { 'z', 'z', 'g', 'l', 'l', 'g' };
static const char neg_cjmptype[] = { 0, 1, 0, 0, 1, 1 };

/* in Masm, there's a nesting level limit of 20. In JWasm, there's
* currently no limit.
*/

#ifdef DEBUG_OUT
static unsigned evallvl;
static unsigned cntAlloc;  /* # of allocated hll_items */
static unsigned cntReused; /* # of reused hll_items */
static unsigned cntCond;   /* # of allocated 'condlines'-buffer in .WHILE-blocks */
static unsigned cntCondBytes; /* total size of allocated 'condlines'-buffers */
#endif

static uint_32 GetHllLabel(void)
/********************************/
{
  return (++ModuleInfo.hll_label);
}

/* get a C binary operator from the token stream.
* there is a problem with the '<' because it is a "string delimiter"
* which Tokenize() usually is to remove.
* There has been a hack implemented in Tokenize() so that it won't touch the
* '<' if .IF, .ELSEIF, .WHILE, .UNTIL, .UNTILCXZ or .BREAK/.CONTINUE has been
* detected.
*/

#define CHARS_EQ  '=' + ( '=' << 8 )
#define CHARS_NE  '!' + ( '=' << 8 )
#define CHARS_GE  '>' + ( '=' << 8 )
#define CHARS_LE  '<' + ( '=' << 8 )
#define CHARS_AND '&' + ( '&' << 8 )
#define CHARS_OR  '|' + ( '|' << 8 )

static enum c_bop GetCOp(struct asm_tok *item)
/**********************************************/
{
  int size;
  enum c_bop rc;
  char *p = item->string_ptr;

  size = (item->token == T_STRING ? item->stringlen : 0);

  if (size == 2) {
    switch (*(uint_16 *)p) {
    case CHARS_EQ:  rc = COP_EQ;  break;
    case CHARS_NE:  rc = COP_NE;  break;
    case CHARS_GE:  rc = COP_GE;  break;
    case CHARS_LE:  rc = COP_LE;  break;
    case CHARS_AND: rc = COP_AND; break;
    case CHARS_OR:  rc = COP_OR;  break;
    default: return(COP_NONE);
    }
  }
  else if (size == 1) {
    switch (*p) {
    case '>': rc = COP_GT;   break;
    case '<': rc = COP_LT;   break;
    case '&': rc = COP_ANDB; break;
    case '!': rc = COP_NEG;  break;
    default: return(COP_NONE);
    }
  }
  else {
    if (item->token != T_ID)
      return(COP_NONE);
    /* a valid "flag" string must end with a question mark */
    size = strlen(p);
    if (*(p + size - 1) != '?')
      return(COP_NONE);
    if (size == 5 && (0 == _memicmp(p, "ZERO", 4)))
      rc = COP_ZERO;
    else if (size == 6 && (0 == _memicmp(p, "CARRY", 5)))
      rc = COP_CARRY;
    else if (size == 5 && (0 == _memicmp(p, "SIGN", 4)))
      rc = COP_SIGN;
    else if (size == 7 && (0 == _memicmp(p, "PARITY", 6)))
      rc = COP_PARITY;
    else if (size == 9 && (0 == _memicmp(p, "OVERFLOW", 8)))
      rc = COP_OVERFLOW;
    //added by habran
    else if (size == 5 && (0 == _memicmp(p, "LESS", 4)))
      rc = COP_LESS;
    else if (size == 8 && (0 == _memicmp(p, "GREATER", 7)))
      rc = COP_GREATER;
    else if (size == 6 && (0 == _memicmp(p, "ABOVE", 5)))
      rc = COP_ABOVE;
    else if (size == 6 && (0 == _memicmp(p, "EQUAL", 5)))
      rc = COP_EQUAL;
    else if (size == 6 && (0 == _memicmp(p, "BELOW", 5)))
      rc = COP_BELOW;
    else
      return(COP_NONE);
  }
  return(rc);
}

/* render an instruction */

static char *RenderInstr(char *dst, const char *instr, int start1, int end1, int start2, int end2, struct asm_tok tokenarray[])
/*******************************************************************************************************************************/
{
  int i;
#ifdef DEBUG_OUT
  char *old = dst;
#endif
  i = strlen(instr);
  /* copy the instruction */
  memcpy(dst, instr, i);
  dst += i;
  /* copy the first operand's tokens */
  *dst++ = ' ';
  i = tokenarray[end1].tokpos - tokenarray[start1].tokpos;
  memcpy(dst, tokenarray[start1].tokpos, i);
  dst += i;
  if (start2 != EMPTY) {
    *dst++ = ',';
    /* copy the second operand's tokens */
    *dst++ = ' ';
    i = tokenarray[end2].tokpos - tokenarray[start2].tokpos;
    memcpy(dst, tokenarray[start2].tokpos, i);
    dst += i; 
  }
  else if (end2 != EMPTY) {
    dst += sprintf(dst, ", %d", end2);
  }
  *dst++ = EOLCHAR;
  *dst = NULLC;
  DebugMsg1(("%u RenderInstr(%s)=>%s<\n", evallvl, instr, old));
  return(dst);
}

static char *GetLabelStr(int_32 label, char *buff)
/**************************************************/
{
  sprintf(buff, LABELFMT, label);
  return(buff);
}

/* render a Jcc instruction */

static char *RenderJcc(char *dst, char cc, int neg, uint_32 label)
/******************************************************************/
{
#ifdef DEBUG_OUT
  char *old = dst;
#endif
  /* create the jump opcode: j[n]cc */
  *dst++ = 'j';
  if (neg)
    *dst++ = 'n';
  *dst++ = cc;
  if (neg == FALSE)
    *dst++ = ' '; /* make sure there's room for the inverse jmp */

  *dst++ = ' ';
  GetLabelStr(label, dst);
  dst += strlen(dst);
  *dst++ = EOLCHAR;
  *dst = NULLC;
  DebugMsg1(("%u RenderJcc()=>%s<\n", evallvl, old));
  return(dst);
}

/* a "token" in a C expression actually is an assembly expression */

static ret_code GetToken(struct hll_item *hll, int *i, struct asm_tok tokenarray[], struct expr *opnd)
/******************************************************************************************************/
{
  int end_tok;

  /* scan for the next C operator in the token array.
  * because the ASM evaluator may report an error if such a thing
  * is found ( CARRY?, ZERO? and alikes will be regarded as - not yet defined - labels )
  */
  for (end_tok = *i; end_tok < Token_Count; end_tok++) {
    if ((GetCOp(&tokenarray[end_tok])) != COP_NONE)
      break;
  }
  if (end_tok == *i) {
    opnd->kind = EXPR_EMPTY;
    return(NOT_ERROR);
  }
  if (ERROR == EvalOperand(i, tokenarray, end_tok, opnd, 0))
    return(ERROR);

  /* v2.11: emit error 'syntax error in control flow directive'.
  * May happen for expressions like ".if 1 + CARRY?"
  */
  if (*i > end_tok) {
    return(EmitError(SYNTAX_ERROR_IN_CONTROL_FLOW_DIRECTIVE));
  }

  return(NOT_ERROR);
}

static uint_32 GetLabel(struct hll_item *hll, int index)
/********************************************************/
{
  /**/myassert(hll->labels[index]);
  return(hll->labels[index]);
}

/* a "simple" expression is
* 1. two tokens, coupled with a <cmp> operator: == != >= <= > <
* 2. two tokens, coupled with a "&" operator
* 3. unary operator "!" + one token
* 4. one token (short form for "<token> != 0")
*/
static ret_code GetSimpleExpression(struct hll_item *hll, int *i, struct asm_tok tokenarray[], int ilabel, bool is_true, char *buffer, struct hll_opnd *hllop)
/**************************************************************************************************************************************************************/
{
  enum c_bop op;
  char instr;
  int op1_pos;
  int op1_end;
  int op2_pos;
  int op2_end;
  char *p;
  struct expr op1;
  struct expr op2;
  uint_32 label;

  DebugMsg1(("%u GetSimpleExpression(>%.32s< buf=>%s<) enter\n", evallvl, tokenarray[*i].tokpos, buffer));

  while (tokenarray[*i].string_ptr[0] == '!' && tokenarray[*i].string_ptr[1] == '\0') {
    (*i)++; //GetCOp( i );
    is_true = 1 - is_true;
  }

  /* the problem with '()' is that is might enclose just a standard Masm
  * expression or a "hll" expression. The first case is to be handled
  * entirely by the expression evaluator, while the latter case is to be
  * handled HERE!
  */
  if (tokenarray[*i].token == T_OP_BRACKET) {
    int brcnt;
    int j;
    for (brcnt = 1, j = *i + 1; tokenarray[j].token != T_FINAL; j++) {
      if (tokenarray[j].token == T_OP_BRACKET)
        brcnt++;
      else if (tokenarray[j].token == T_CL_BRACKET) {
        brcnt--;
        if (brcnt == 0) /* a standard Masm expression? */
          break;
      }
      else if ((GetCOp(&tokenarray[j])) != COP_NONE)
        break;
    }
    if (brcnt) {
      (*i)++;
      DebugMsg1(("%u GetSimpleExpression: calling GetExpression, i=%u\n", evallvl, *i));
      if (ERROR == GetExpression(hll, i, tokenarray, ilabel, is_true, buffer, hllop))
        return(ERROR);

      if (tokenarray[*i].token != T_CL_BRACKET) {
        //if (( tokenarray[*i].token == T_FINAL ) || ( tokenarray[*i].token == T_CL_BRACKET ))
        DebugMsg(("GetSimpleExpression: expected ')', found: %s\n", tokenarray[*i].string_ptr));
        return(EmitError(SYNTAX_ERROR_IN_CONTROL_FLOW_DIRECTIVE));
      }
      (*i)++;
      return(NOT_ERROR);
    }
  }

  /* get (first) operand */
  op1_pos = *i;
  if (ERROR == GetToken(hll, i, tokenarray, &op1))
    return (ERROR);
  op1_end = *i;

  op = GetCOp(&tokenarray[*i]); /* get operator */

  /* lower precedence operator ( && or || ) detected? */
  if (op == COP_AND || op == COP_OR) {
    /* v2.11: next 2 lines removed - && and || operators need a valid first operand */
    //if ( op1.kind == EXPR_EMPTY )
    //    return( NOT_ERROR );
    op = COP_NONE;
  }
  else if (op != COP_NONE)
    (*i)++;

  label = GetLabel(hll, ilabel);

  DebugMsg1(("%u GetSimpleExpression: EvalOperand ok, kind=%X, i=%u [%s]\n", evallvl, op1.kind, *i, tokenarray[*i].tokpos));

  /* check for special operators with implicite operand:
  * COP_ZERO, COP_CARRY, COP_SIGN, COP_PARITY, COP_OVERFLOW
  */
  if (op >= COP_ZERO) {
    if (op1.kind != EXPR_EMPTY) {
      DebugMsg(("GetSimpleExpression: non-empty expression rejected: %s\n", tokenarray[op1_pos].tokpos));
      return(EmitError(SYNTAX_ERROR_IN_CONTROL_FLOW_DIRECTIVE));
    }
    p = buffer;
    hllop->lastjmp = p;
       RenderJcc(p, flaginstr[op - COP_ZERO], !is_true, label);
    return(NOT_ERROR);
  }

  switch (op1.kind) {
  case EXPR_EMPTY:
    DebugMsg(("GetSimpleExpression: empty expression rejected\n"));
    return(EmitError(SYNTAX_ERROR_IN_CONTROL_FLOW_DIRECTIVE)); /* v2.09: changed from NOT_ERROR to ERROR */
  case EXPR_FLOAT:
    DebugMsg(("GetSimpleExpression: float expression rejected: %s\n", tokenarray[op1_pos].tokpos));
    return(EmitError(REAL_OR_BCD_NUMBER_NOT_ALLOWED)); /* v2.10: added */
  }

  if (op == COP_NONE) {
    switch (op1.kind) {
    case EXPR_REG:
      if (op1.indirect == FALSE) {
        p = RenderInstr(buffer, "test", op1_pos, op1_end, op1_pos, op1_end, tokenarray);
        hllop->lastjmp = p;
        RenderJcc(p, 'z', is_true, label);
        break;
      }
      /* no break */
    case EXPR_ADDR:
      p = RenderInstr(buffer, "cmp", op1_pos, op1_end, EMPTY, 0, tokenarray);
      hllop->lastjmp = p;
      RenderJcc(p, 'z', is_true, label);
      break;
    case EXPR_CONST:
#if 0
      /* v2.05: string constant is allowed! */
      if (op1.string != NULL) {
        return(EmitError(SYNTAX_ERROR_IN_CONTROL_FLOW_DIRECTIVE));
      }
#endif
      /* v2.11: error if constant doesn't fit in 32-bits */
      if (op1.hvalue != 0 && op1.hvalue != -1)
        return(EmitConstError(&op1));

      hllop->lastjmp = buffer;

      if ((is_true == TRUE && op1.value) ||
        (is_true == FALSE && op1.value == 0)) {
        sprintf(buffer, "jmp " LABELFMT EOLSTR, label);
      }
      else {
        //strcpy( buffer, " " EOLSTR ); /* v2.11: obsolete */
        *buffer = NULLC;
      }
      break;
#ifdef DEBUG_OUT
    default: /**/myassert(0); break;
#endif
    }
    return(NOT_ERROR);
  }

  /* get second operand for binary operator */
  op2_pos = *i;
  if (ERROR == GetToken(hll, i, tokenarray, &op2)) {
    return(ERROR);
  }
  DebugMsg1(("%u GetSimpleExpression: EvalOperand 2 ok, type=%X, i=%u [%s]\n", evallvl, op2.type, *i, tokenarray[*i].tokpos));
  if (op2.kind != EXPR_CONST && op2.kind != EXPR_ADDR && op2.kind != EXPR_REG) {
    DebugMsg(("GetSimpleExpression: syntax error, op2.kind=%u\n", op2.kind));
    return(EmitError(SYNTAX_ERROR_IN_CONTROL_FLOW_DIRECTIVE));
  }
  op2_end = *i;

  /* now generate ASM code for expression */

  if (op == COP_ANDB) {
    p = RenderInstr(buffer, "test", op1_pos, op1_end, op2_pos, op2_end, tokenarray);
    hllop->lastjmp = p;
    RenderJcc(p, 'e', is_true, label);
  }
  else if (op <= COP_LE) { /* ==, !=, >, <, >= or <= operator */
    /*
    * optimisation: generate 'or EAX,EAX' instead of 'cmp EAX,0'.
    * v2.11: use op2.value64 instead of op2.value
    */
    if (Options.masm_compat_gencode &&
      (op == COP_EQ || op == COP_NE) &&
      op1.kind == EXPR_REG && op1.indirect == FALSE &&
      op2.kind == EXPR_CONST && op2.value64 == 0) {
      p = RenderInstr(buffer, "or", op1_pos, op1_end, op1_pos, op1_end, tokenarray);
    }
    else {
      p = RenderInstr(buffer, "cmp", op1_pos, op1_end, op2_pos, op2_end, tokenarray);
    }

    instr = ((IS_SIGNED(op1.mem_type) || IS_SIGNED(op2.mem_type)) ? signed_cjmptype[op - COP_EQ] : unsigned_cjmptype[op - COP_EQ]);
    hllop->lastjmp = p;
    RenderJcc(p, instr, neg_cjmptype[op - COP_EQ] ? is_true : !is_true, label);
  }
  else {
    DebugMsg(("GetSimpleExpression: unexpected operator %s\n", tokenarray[op1_pos].tokpos));
    return(EmitError(SYNTAX_ERROR_IN_CONTROL_FLOW_DIRECTIVE));
  }
  return(NOT_ERROR);
}

/* invert a Jump:
* - Jx  -> JNx (x = e|z|c|s|p|o )
* - JNx -> Jx  (x = e|z|c|s|p|o )
* - Ja  -> Jbe, Jae -> Jb
* - Jb  -> Jae, Jbe -> Ja
* - Jg  -> Jle, Jge -> Jl
* - Jl  -> Jge, Jle -> Jg
* added in v2.11:
* - jmp -> 0
* - 0   -> jmp
*/
static void InvertJump(char *p)
/*******************************/
{
  if (*p == NULLC) { /* v2.11: convert 0 to "jmp" */
    strcpy(p, "jmp ");
    return;
  }

  p++;
  if (*p == 'e' || *p == 'z' || *p == 'c' || *p == 's' || *p == 'p' || *p == 'o') {
    *(p + 1) = *p;
    *p = 'n';
    return;
  }
  else if (*p == 'n') {
    *p = *(p + 1);
    *(p + 1) = ' ';
    return;
  }
  else if (*p == 'a') {
    *p++ = 'b';
  }
  else if (*p == 'b') {
    *p++ = 'a';
  }
  else if (*p == 'g') {
    *p++ = 'l';
  }
  else if (*p == 'l') {
    *p++ = 'g';
  }
  else {
    /* v2.11: convert "jmp" to 0 */
    if (*p == 'm') {
      p--;
      *p = NULLC;
    }
    return;
  }
  if (*p == 'e')
    *p = ' ';
  else
    *p = 'e';
  return;
}

/* Replace a label in the source lines generated so far.
* todo: if more than 0xFFFF labels are needed,
* it may happen that length of nlabel > length of olabel!
* then the simple memcpy() below won't work!
*/

static void ReplaceLabel(char *p, uint_32 olabel, uint_32 nlabel)
/*****************************************************************/
{
  char oldlbl[16];
  char newlbl[16];
  int i;

  GetLabelStr(olabel, oldlbl);
  GetLabelStr(nlabel, newlbl);

  i = strlen(newlbl);

  DebugMsg1(("%u ReplaceLabel(%s->%s, >%s<)\n", evallvl, oldlbl, newlbl, p));
  while (p = strstr(p, oldlbl)) {
    memcpy(p, newlbl, i);
    p += i;
  }
}

/* operator &&, which has the second lowest precedence, is handled here */

static ret_code GetAndExpression(struct hll_item *hll, int *i, struct asm_tok tokenarray[], int ilabel, bool is_true, char *buffer, struct hll_opnd *hllop)
/***********************************************************************************************************************************************************/
{
  char *ptr = buffer;
  uint_32 truelabel = 0;
  //char buff[16];
  //char *nlabel;
  //char *olabel;

  DebugMsg1(("%u GetAndExpression(>%.32s< buf=>%s<) enter\n", evallvl, tokenarray[*i].tokpos, buffer));

  if (ERROR == GetSimpleExpression(hll, i, tokenarray, ilabel, is_true, ptr, hllop))
    return(ERROR);
  while (COP_AND == GetCOp(&tokenarray[*i])) {

    (*i)++;
    DebugMsg1(("%u GetAndExpression: &&-operator found, is_true=%u, lastjmp=%s\n", evallvl, is_true, hllop->lastjmp ? hllop->lastjmp : "NULL"));

    if (is_true) {
      /* todo: please describe what's done here and why! */
      if (hllop->lastjmp) {
        char *p = hllop->lastjmp;
        InvertJump(p);          /* step 1 */
        if (truelabel == 0)     /* step 2 */
          truelabel = GetHllLabel();

        if (*p) {               /* v2.11: there might be a 0 at lastjmp */
          p += 4;               /* skip 'jcc ' or 'jmp ' */
          GetLabelStr(truelabel, p);
          strcat(p, EOLSTR);
        }

        DebugMsg1(("%u GetAndExpression: jmp inverted >%s<\n", evallvl, hllop->lastjmp));
        ReplaceLabel(buffer, GetLabel(hll, ilabel), truelabel);
        hllop->lastjmp = NULL;
      }
    }
    ptr += strlen(ptr);
    hllop->lasttruelabel = 0; /* v2.08 */
    if (ERROR == GetSimpleExpression(hll, i, tokenarray, ilabel, is_true, ptr, hllop))
      return(ERROR);
  };

  if (truelabel > 0) {
    ptr += strlen(ptr);
    GetLabelStr(truelabel, ptr);
    strcat(ptr, LABELQUAL EOLSTR);
    DebugMsg1(("%u GetAndExpression: label added >%s<\n", evallvl, ptr));
    hllop->lastjmp = NULL;
  }
  return(NOT_ERROR);
}

/* operator ||, which has the lowest precedence, is handled here */

static ret_code GetExpression(struct hll_item *hll, int *i, struct asm_tok tokenarray[], int ilabel, bool is_true, char *buffer, struct hll_opnd *hllop)
/********************************************************************************************************************************************************/
{
  char *ptr = buffer;
  uint_32 truelabel = 0;

  DebugMsg1(("%u GetExpression(>%.32s< buf=>%s<) enter\n", ++evallvl, tokenarray[*i].tokpos, buffer));

  /* v2.08: structure changed from for(;;) to while() to increase
  * readability and - optionally - handle the second operand differently
  * than the first.
  */

  if (ERROR == GetAndExpression(hll, i, tokenarray, ilabel, is_true, ptr, hllop)) {
    DebugMsg1(("%u GetExpression exit, error\n", evallvl--));
    return(ERROR);
  }
  while (COP_OR == GetCOp(&tokenarray[*i])) {

    uint_32 nlabel;
    uint_32 olabel;
    char buff[16];

    /* the generated code of last simple expression has to be modified
    1. the last jump must be inverted
    2. a "is_true" label must be created (it's used to jump "behind" the expr)
    3. create a new label
    4. the current "false" label must be generated

    if it is a .REPEAT, step 4 is slightly more difficult, since the "false"
    label is already "gone":
    4a. create a new label
    4b. replace the "false" label in the generated code by the new label
    */

    (*i)++;
    DebugMsg1(("%u GetExpression: ||-operator found, is_true=%u, lastjmp=%s\n", evallvl, is_true, hllop->lastjmp ? hllop->lastjmp : "NULL"));

    if (is_true == FALSE) {
      if (hllop->lastjmp) {
        char *p = hllop->lastjmp;
        InvertJump(p);           /* step 1 */
        if (truelabel == 0)      /* step 2 */
          truelabel = GetHllLabel();
        if (*p) { /* v2.11: there might be a 0 at lastjmp */
          p += 4;                /* skip 'jcc ' or 'jmp ' */
          GetLabelStr(truelabel, p);
          strcat(p, EOLSTR);
        }
        /* v2.08: if-block added */
        if (hllop->lasttruelabel)
          ReplaceLabel(ptr, hllop->lasttruelabel, truelabel);
        DebugMsg1(("%u GetExpression: jmp inverted, dest changed >%s<\n", evallvl, ptr));
        hllop->lastjmp = NULL;

        nlabel = GetHllLabel();  /* step 3 */
        olabel = GetLabel(hll, ilabel);
        if (hll->cmd == HLL_REPEAT) {
          ReplaceLabel(buffer, olabel, nlabel);
          sprintf(ptr + strlen(ptr), "%s" LABELQUAL EOLSTR, GetLabelStr(nlabel, buff));
        }
        else {
          sprintf(ptr + strlen(ptr), "%s" LABELQUAL EOLSTR, GetLabelStr(olabel, buff));
          ReplaceLabel(buffer, olabel, nlabel);
        }
        DebugMsg1(("%u GetExpression: dest changed, label added >%s<\n", evallvl, ptr));
      }
    }
    ptr += strlen(ptr);
    hllop->lasttruelabel = 0; /* v2.08 */
    if (ERROR == GetAndExpression(hll, i, tokenarray, ilabel, is_true, ptr, hllop)) {
      DebugMsg1(("%u GetExpression exit, error\n", evallvl--));
      return(ERROR);
    }
  }
  if (truelabel > 0) {
    /* v2.08: this is needed, but ober-hackish. to be improved... */
    if (hllop->lastjmp && hllop->lasttruelabel) {
      DebugMsg1(("%u GetExpression: suppressed ReplaceLabel %u -> %u, lastjmp=%s\n", evallvl, hllop->lasttruelabel, truelabel, hllop->lastjmp));
      ReplaceLabel(ptr, hllop->lasttruelabel, truelabel);
      *(strchr(hllop->lastjmp, EOLCHAR) + 1) = NULLC;
    }
    ptr += strlen(ptr);
    GetLabelStr(truelabel, ptr);
    strcat(ptr, LABELQUAL EOLSTR);
    DebugMsg1(("%u GetExpression: label added >%s<\n", evallvl, ptr));
    hllop->lasttruelabel = truelabel; /* v2.08 */
  }
  DebugMsg1(("%u GetExpression exit\n", evallvl--));
  return(NOT_ERROR);
}

/*
* write assembly test lines to line queue.
* v2.11: local line buffer removed; src pointer has become a parameter.
*/

static ret_code QueueTestLines(char *src)
/*****************************************/
{
  char *start;

  DebugMsg1(("QueueTestLines(\"%s\") enter\n", src ? src : "NULL"));
  while (src) {
    //if (*src == ' ') src++; /* v2.11: obsolete */
    start = src;
    if (src = strchr(src, EOLCHAR))
      *src++ = NULLC;
    if (*start)
      AddLineQueue(start);
  }

  DebugMsg1(("QueueTestLines exit\n"));
  return(NOT_ERROR);
}

/*
* evaluate the C like boolean expression found in HLL structs
* like .IF, .ELSEIF, .WHILE, .UNTIL and .UNTILCXZ
* might return multiple lines (strings separated by EOLCHAR)
* - i = index for tokenarray[] where expression starts. Is restricted
*       to one source line (till T_FINAL)
* - label: label to jump to if expression is <is_true>!
* is_true:
*   .IF:       FALSE
*   .ELSEIF:   FALSE
*   .WHILE:    TRUE
*   .UNTIL:    FALSE
*   .UNTILCXZ: FALSE
*   .BREAK .IF:TRUE
*   .CONT .IF: TRUE
*/


static ret_code EvaluateHllExpression(struct hll_item *hll, int *i, struct asm_tok tokenarray[], int ilabel, bool is_true, char *buffer)
/****************************************************************************************************************************************/
{
  struct hll_opnd hllop = { NULL, 0 };

  DebugMsg1(("EvaluateHllExpression enter\n"));

  *buffer = NULLC;
  if (ERROR == GetExpression(hll, i, tokenarray, ilabel, is_true, buffer, &hllop))
    return(ERROR);
  /* v2.11: changed */
  //if ( *buffer == EOLCHAR ) {
  //DebugMsg(( "EvaluateHllExpression: EOL at pos 0 in line buffer\n" ));
  if (tokenarray[*i].token != T_FINAL) {
    DebugMsg(("EvaluateHllExpression: unexpected tokens >%s<\n", tokenarray[*i].tokpos));
    return(EmitError(SYNTAX_ERROR_IN_CONTROL_FLOW_DIRECTIVE));
  }
  return(NOT_ERROR);
}

/* for .UNTILCXZ: check if expression is simple enough.
* what's acceptable is ONE condition, and just operators == and !=
* Constants (0 or != 0) are also accepted.
*/

static ret_code CheckCXZLines(char *p)
/**************************************/
{
  int lines = 0;
  int i;
  int addchars;
  char *px;
  bool NL = TRUE;

  DebugMsg1(("CheckCXZLines enter, p=>%s<\n", p));
  /* syntax ".untilcxz 1" has a problem: there's no "jmp" generated at all.
  * if this syntax is to be supported, activate the #if below.
  */
  for (; *p; p++) {
    if (*p == EOLCHAR) {
      NL = TRUE;
      lines++;
    }
    else if (NL) {
      NL = FALSE;
      if (*p == 'j') {
        p++;
        /* v2.06: rewritten */
        if (*p == 'm' && lines == 0) {
          addchars = 2; /* make room for 2 chars, to replace "jmp" by "loope" */
          px = "loope";
        }
        else if (lines == 1 && (*p == 'z' || (*p == 'n' && *(p + 1) == 'z'))) {
          addchars = 3; /* make room for 3 chars, to replace "jz"/"jnz" by "loopz"/"loopnz" */
          px = "loop";
        }
        else
          return(ERROR); /* anything else is "too complex" */
        //replace_instr:
        for (p--, i = strlen(p); i >= 0; i--) {
          *(p + addchars + i) = *(p + i);
        }
        memcpy(p, px, strlen(px));
      }
#if 0 /* handle ".untilcxz 1" like masm does */
      else if (*p == ' ' && *(p + 1) == EOLCHAR && lines == 0) {
        p++;
        GetLabelStr(hll->labels[LSTART], p);
        strcat(p, EOLSTR);
        addchars = 5;
        px = "loope";
        goto replace_instr;
      }
#endif
    }
  }
  if (lines > 2)
    return(ERROR);
  return(NOT_ERROR);
}
#ifdef _WIN64
static const char reax[] = "rax\0";
static const char recx[] = "rcx\0";
static const char redx[] = "rdx\0";
#else
static const char reax[] = "eax\0";
static const char recx[] = "ecx\0";
static const char redx[] = "edx\0";
#endif
static void WriteAsmLine(const char *cmd, const char *s1, const char *s2){
  char codebuff[256];
  strcpy(codebuff, cmd);
  strcat(codebuff, s1);
  strcat(codebuff, ", ");
  strcat(codebuff, s2);
  AddLineQueue(codebuff);				// MOV RAX,param
  return;
}
static ret_code ForInitAndNext(struct asm_tok tokenarray[], int cnt, char *buff){
  int a;
  int j;
  int	b = 0;
  bool brct = 0;
  char codebuff[256];
  char param[256];
  char init[256];
  char op[4];
  char *p;
  //create valid command and add to LineQueue
  do {
    //extracting the first parameter "param" before the operator
    a = 0;
    while (buff[b] && !strchr("=!<>&|-+*^%/", buff[b]))
    {
      if (buff[b] == '-' || buff[b] == '+') break;
      param[a] = buff[b];
      b++;
      a++;
    }
    param[a] = '\0';
    //end of param
    //is it simple operator
    if ((buff[b + 1] == '+') || (buff[b + 1] == '-')){            //if ++ or -- finish it here
      param[a] = '\0';
      if ((buff[b] == '+') && (buff[b + 1] == '+')) strcpy(codebuff, " inc ");
      else if ((buff[b] == '-') && (buff[b + 1] == '-')) strcpy(codebuff, " dec ");
      strcat(codebuff, param);
      AddLineQueue(codebuff);
      b += 3;
    }

    //we finis here "inc REX" or  "dec REX" or "inc mem" or "dec mem"
    else						//if not ++ or -- 
    {							//extracting the operator
      op[0] = buff[b];
      b++;
      if (op[0] == '='){     //if operator is only '='
        op[1] = '\0';       //finish here
      }
      else {                 //extract next operator
        op[1] = buff[b];
        b++;
        if ((op[1] == '<' || op[1] == '>') && (buff[b] == '=')){
          op[2] = buff[b]; //if a second operator is shift sign "<<=" or ">>="
          op[3] = NULLC;
          b++;
        }
        else op[2] = NULLC; //not shift so we have two operands

      }
      //we finished with param and op
      //now extracting the second parameter "init" after the operator
      for (a = 0; buff[b];){ //checking if we have a char in a single ' '
        if (buff[b] == '(' && buff[b - 1] != 39 && buff[b + 1] != 39 && b) break;
        if (buff[b] == ',' && buff[b - 1] != 39 && buff[b + 1] != 39 && b) break;
        init[a] = buff[b];
        b++;
        a++;
      }
      if (buff[b] == '(' && buff[b - 1] != 39 && buff[b + 1] != 39 && b){
        for (; buff[b] && buff[b] != ')'; b++, a++){
          init[a] = buff[b];
        }
        if (buff[b] == ')' && buff[b - 1] != 39 && buff[b + 1] != 39){
          init[a] = buff[b];
          b++;
          a++;
        }
        brct = TRUE;
      }
      init[a] = NULLC;
      b++;
      //we finished with init
      //is operator devision, multiplication or mod
      if (op[0] == '/' || op[0] == '*' || op[0] == '%') {
        Tokenize(param, 0, tokenarray, 0);
        if (strcasecmp(param, reax) && strcasecmp(init, reax)){ //param not rax init not rax?    
          if (tokenarray[0].token == T_REG){			//is param register              
            if (strcasecmp(param, recx)){				//make sure that param is not rcx
              WriteAsmLine(" mov  ", reax, param);				// MOV RAX,param
            }						if (op[0] == '/' || op[0] == '%'){
              strcpy(codebuff, " cdq ");			//extend to RDX if division	
              AddLineQueue(codebuff);
            }
            Tokenize(init, 0, tokenarray, 0);
            if (tokenarray[0].token == T_NUM){      //is init number? 
              WriteAsmLine(" mov  ", recx, init);        //MOV RCX,init
              if (op[0] == '/' || op[0] == '%')
                strcpy(codebuff, " idiv ");		//IDIV RCX        
              else strcpy(codebuff, " imul ");		//IMUL RCX        
              strcat(codebuff, recx);
              AddLineQueue(codebuff);
              goto cont;
            }
            else {
              if (op[0] == '/' || op[0] == '%') //it is a variable
                strcpy(codebuff, " idiv ");
              else strcpy(codebuff, " imul ");
              strcat(codebuff, init);
              AddLineQueue(codebuff);
              goto cont;
            }
          }
          //if param is a variable
          else if (tokenarray[0].token == T_ID){		 //YES             
            WriteAsmLine(" mov  ", recx, init);        //MOV RCX,init
            WriteAsmLine(" mov  ", reax, param);		// MOV RAX,param
            if (op[0] == '/' || op[0] == '%'){
              strcpy(codebuff, " cdq ");
              AddLineQueue(codebuff);
              strcpy(codebuff, " idiv ");
            }
            else strcpy(codebuff, " imul ");
            strcat(codebuff, recx);
            AddLineQueue(codebuff);
          cont:
            if (op[0] == '%') {
              WriteAsmLine(" mov  ", param, redx);
              goto skip;
            }
            else {
              WriteAsmLine(" mov  ", param, reax);
              goto skip;
            }
          }
        }
        // if param is not RAX and init is RCX
        else if ((strcasecmp(param, reax) && !(strcasecmp(init, recx)))){
          if (op[0] == '/' || op[0] == '%'){
            strcpy(codebuff, " cdq ");
            AddLineQueue(codebuff);
            strcpy(codebuff, " idiv ");
          }
          else strcpy(codebuff, " imul ");
          strcat(codebuff, recx);
          AddLineQueue(codebuff);
          if (op[0] == '%') WriteAsmLine(" mov  ", param, redx);
          goto skip;
        }
        // if param is RAX and init is RCX
        else if ((!(strcasecmp(param, reax)) && (!(strcmp(init, recx))))){
          if (op[0] == '/' || op[0] == '%'){
            strcpy(codebuff, " cdq ");
            AddLineQueue(codebuff);
            strcpy(codebuff, " idiv ");
          }
          else strcpy(codebuff, " imul ");
          strcat(codebuff, recx);
          AddLineQueue(codebuff);
          if (op[0] == '%') WriteAsmLine(" mov  ", param, redx);
          goto skip;
        }
        // if param is RAX and init is not RCX
        else if (!(strcasecmp(param, reax) && (strcasecmp(init, recx)))){
          WriteAsmLine(" mov  ", recx, init);        //MOV RCX,init
          if (op[0] == '/' || op[0] == '%'){
            strcpy(codebuff, " cdq ");
            AddLineQueue(codebuff);
            strcpy(codebuff, " idiv ");
          }
          else strcpy(codebuff, " imul ");
          strcat(codebuff, recx);
          AddLineQueue(codebuff);
          if (op[0] == '%') WriteAsmLine(" mov  ", param, redx);
          goto skip;
        }
      }
      //if operator not devision, multiplication or mod
      else if (op[0] == '-') strcpy(codebuff, " sub ");
      else if (op[0] == '+') strcpy(codebuff, " add ");
      else if (op[0] == '&') strcpy(codebuff, " and ");
      else if (op[0] == '|') strcpy(codebuff, " or ");
      else if (op[0] == '^') strcpy(codebuff, " xor ");
      else if (op[0] == '<' && op[1] == '<') strcpy(codebuff, " shl ");
      else if (op[0] == '>' && op[1] == '>') strcpy(codebuff, " shr ");
      Tokenize(init, 0, tokenarray, 0);
      if (tokenarray[0].token == T_REG || tokenarray[0].token == T_NUM || tokenarray[0].token == T_FLOAT || tokenarray[0].token == T_DIRECTIVE)
        goto simple;
      Tokenize(param, 0, tokenarray, 0);
      if (tokenarray[0].token == T_REG){
      simple:			Tokenize(param, 0, tokenarray, 0);

        if (strlen(init) == 1 && init[0] == '0')                        //REX=0?
          WriteAsmLine(" xor  ", param, param);							            //XOR REX,REX //instead MOV REX,0				
        else if ((strlen(op) == 1) && ((init[4] == ' ') || (init[4] == '\t'))){  //op is '='
          if ((0 == _memicmp(init, "BYTE PTR", 8)) ||                   //reax=BYTE PTR al 
            (0 == _memicmp(init, "BPTR", 4)) ||
            (0 == _memicmp(init, "WPTR", 4)) ||
            (0 == _memicmp(init, "WORD PTR", 8)))                     //reax=WORD PTR ax 

            WriteAsmLine(" movzx  ", param, init);                      //movzx reax,ax					    
          else if (0 == _memicmp(init, "ADDR", 4))
            WriteAsmLine(" lea  ", param, init + 5);
          else WriteAsmLine(" mov  ", param, init);
        }
        else if ((strlen(op) == 1) && ((init[6] == ' ') || (init[6] == '\t'))){
          if (0 == _memicmp(init, "OFFSET", 6))
            WriteAsmLine(" lea  ", param, init + 7);
          else WriteAsmLine(" mov  ", param, init);
        }
        else if ((strlen(op) == 1) && ((init[5] == ' ') || (init[5] == '\t'))){            //op is '='
          if ((0 == _memicmp(init, "DWORD PTR", 9) || 0 == _memicmp(init, "DPTR", 4)
            && (param[0] == 'r' || param[0] == 'R'))) 							   //rax=DWORD PTR eax
            WriteAsmLine(" movsxd  ", param, init);								     //movsxd rax,eax
          else WriteAsmLine(" mov  ", param, init);
        }
        else if ((strlen(op) == 1) && brct){											    //op is '='
          for (j = strlen(init); j; j--){
            if (init[j] == ')') init[j] = NULLC;
            if (init[j] == '('){
              for (p = init, p += j; *p; p++){
                if (*p == ',' && cnt) --cnt;
              }
              init[j] = ',';
            }
          }
          strcpy(codebuff, " invoke  ");
          strcat(codebuff, init);
          AddLineQueue(codebuff);
          WriteAsmLine(" mov  ", param, reax);
          brct = FALSE;
        }
        else {
          if (strlen(op) == 1)
            WriteAsmLine(" mov  ", param, init);
          else
            WriteAsmLine(codebuff, param, init);
        }
      }
      else
      {
        if (init[0] == 39 && init[2] == 39)
          WriteAsmLine(" mov  byte ptr ", param, init);
        else {
          WriteAsmLine(" mov  ", reax, init);
          WriteAsmLine(codebuff, param, reax);
        }
      }
    }
  skip:
    if (cnt) cnt--;
  } while (cnt);
  return(NOT_ERROR);
}

/* .IF, .WHILE, .REPEAT or .FOR directive */

ret_code HllStartDir(int i, struct asm_tok tokenarray[])
/********************************************************/
{
  struct hll_item      *hll;
  ret_code             rc = NOT_ERROR;
  int                  cmd = tokenarray[i].tokval;
  char buff[16];
  char buffer[MAX_LINE_LEN * 2];
  char codebuff[256];
  char param[256];
  char init[256];
  char limit[MAX_LINE_LEN];
  char op[4];
  char forbuff[MAX_LINE_LEN];
  char forbuffinit[MAX_LINE_LEN];
  char forbuffcond[MAX_LINE_LEN];
  char forbuffcnt[MAX_LINE_LEN];
  char transformed[MAX_LINE_LEN];
  int a;
  int j;
  int b;
  int e;
  int size;
  int eqcnt;
  int cmcnt;
  char *p;
  char c;

  DebugMsg1(("HllStartDir(%s) enter\n", tokenarray[i].string_ptr));

  i++; /* skip directive */

  /* v2.06: is there an item on the free stack? */
  if (HllFree) {
    hll = HllFree;
    DebugCmd(cntReused++);
  }
  else {
    hll = LclAlloc(sizeof(struct hll_item));
    DebugCmd(cntAlloc++);
  }

  /* structure for .IF .ELSE .ENDIF
  *    cond jump to LTEST-label
  *    ...
  *    jmp LEXIT
  *  LTEST:
  *    ...
  *  LEXIT:

  * structure for .IF .ELSEIF
  *    cond jump to LTEST
  *    ...
  *    jmp LEXIT
  *  LTEST:
  *    cond jump to (new) LTEST
  *    ...
  *    jmp LEXIT
  *  LTEST:
  *    ...

  * structure for .WHILE and .REPEAT:
  *   jmp LTEST (for .WHILE only)
  * LSTART:
  *   ...
  * LTEST: (jumped to by .continue)
  *   a) test end condition, cond jump to LSTART label
  *   b) unconditional jump to LSTART label
  * LEXIT: (jumped to by .BREAK)
  */

  hll->labels[LEXIT] = 0;

  switch (cmd) {
  case T_DOT_IF:
    hll->labels[LSTART] = 0; /* not used by .IF */
    hll->labels[LTEST] = GetHllLabel();
    hll->cmd = HLL_IF;
    hll->flags = 0;
    /* get the C-style expression, convert to ASM code lines */
    rc = EvaluateHllExpression(hll, &i, tokenarray, LTEST, FALSE, buffer);
    if (rc == NOT_ERROR) {
      QueueTestLines(buffer);
      /* if no lines have been created, the LTEST label isn't needed */
      //if ( !is_linequeue_populated() ) {
      if (buffer[0] == NULLC) {
        hll->labels[LTEST] = 0;
      }
    }
    break;
    // added by habran
  case T_DOT_FOR:
    /* create the label to loop start */
    hll->labels[LEXIT] = 0; //this is needed for .FOR loop
    hll->labels[LSTART] = GetHllLabel();
    hll->labels[LSKIP] = GetHllLabel();
    hll->labels[LCONT] = 0;
    hll->labels[LTEST] = 0;
    hll->flags = 0;
    hll->cmd = HLL_FOR;
    //copy string to the buffer and get read of spaces
    p = tokenarray[i].tokpos;
    for (b = 0; *p; p++)
    {
      if ((*p == ' ') || (*p == '\t')) {
        //if there is QWORD PTR, DWORD PTR, WORD PTR, BYTE PTR, OFFSET or ADDR leave a space between
        c = tolower(*(p + 1));
        if ((c >= 'a') && (c <= 'z')){
          forbuff[b] = *p;
          b++;
        }
      }
      else {
        forbuff[b] = *p;
        b++;
      }
    }
    forbuff[b] = NULLC;
    if (0 == _memicmp(forbuff, "(::)", 4)){
      hll->cmcnt = 0;
    }
    else {
      //count initializers
      eqcnt = 1;
      forbuffinit[0] = NULLC;
      for (j = 1, b = 0; forbuff[j];){
        c = forbuff[j];
        if (c == ':') {
          if (forbuff[j - 1] != 39 && forbuff[j + 1] != 39) break;
        }
        if (c == ',' && forbuff[j - 1] != 39 && forbuff[j + 1] != 39) eqcnt++;
        forbuffinit[b] = c;
        if (c == 39 && forbuffinit[b - 2] == 39){
          b++;
          forbuffinit[b] = ' ';
        }
        j++;
        b++;
      }
      forbuffinit[b] = NULLC;
      j++;
      //coppy the condition to the buffer
      forbuffcond[0] = NULLC;
      hll->labels[LTEST] = 0;
      for (b = 0; forbuff[j] && forbuff[j] != ':'; forbuffcond[b] = forbuff[j], j++, b++);
      if (forbuffcond[b - 2] == '>' && forbuffcond[b - 1] == '0') forbuffcond[b - 2] = NULLC;
      forbuffcond[b] = NULLC;
      if (!b) hll->cond = FALSE;
      else    hll->cond = TRUE;
      j++;
      //copy the counter to the buffer
      cmcnt = 0;
      forbuffcnt[0] = NULLC;
      hll->condlines = "";
      for (b = 0; forbuff[j] != ')';b++,j++){
        forbuffcnt[b] = forbuff[j];
        if (forbuffcnt[b] == ',' && forbuff[j - 1] != 39 && forbuff[j + 1] != 39) ++cmcnt;
        if (forbuffcnt[b] == 39 && forbuffcnt[b - 2] == 39){
          b++;
          forbuffcnt[b] = ' ';
        }
      }
      if (forbuffcnt[b - 1] == ')') b--;
      forbuffcnt[b] = NULLC;
      //create valid command and add to LineQueue to initiate .for loop vars
      //anything that is before the first ':'
      if (forbuffinit[0]) ForInitAndNext(tokenarray, eqcnt, forbuffinit);
      //note hll->counterlines is new var in the struct hll_item for store of forbuffcnt used in .ENDFOR
      //hll->cmcnt is also new var in the struct hll_item for commas counter used in .ENDFOR
      //copy forbuffcnt context to hll->counterlines 
      //forbuffcnt contains anything that is written after the second ':'
      hll->cmcnt = 0;
      if (forbuffcnt[0])
      {
      //skip altering conditions the first time
        AddLineQueueX(" jmp %s", GetLabelStr(hll->labels[LSKIP], buff));
        size = strlen(forbuffcnt) + 1;
        hll->counterlines = LclAlloc(size);
        memcpy(hll->counterlines, forbuffcnt, size);
        hll->cmcnt = cmcnt + 1;
      }
      else hll->counterlines = "";    //there is nothing after the second ':'
      if (forbuffcond[0]){
        strcpy(transformed, ".for ");
        strcat(transformed, forbuffcond);
        strcat(transformed, "\0");
        tokenarray[0].string_ptr = ".for\0";
        tokenarray[0].tokpos = transformed;
        Token_Count = Tokenize(tokenarray[0].tokpos, 0, tokenarray, 0);
        if (tokenarray[i].token != T_FINAL) {
          rc = EvaluateHllExpression(hll, &i, tokenarray, LSTART, TRUE, buffer);
          if (rc == NOT_ERROR) {
            size = strlen(buffer) + 1;
            hll->condlines = LclAlloc(size);
            memcpy(hll->condlines, buffer, size);
            DebugCmd(cntCond++); DebugCmd(cntCondBytes += size);
          }
        }
        else
          hll->condlines = "";
      }
    }
    AddLineQueueX("%s" LABELQUAL, GetLabelStr(hll->labels[LSTART], buff));
    tokenarray[i].token = T_FINAL;
    break;
    //end of .FOR
  case T_DOT_WHILE:
  case T_DOT_REPEAT:
    /* create the label to start of loop */
    hll->labels[LSTART] = GetHllLabel();
    hll->labels[LTEST] = 0; /* v2.11: test label is created only if needed */
    //hll->labels[LEXIT] = GetHllLabel(); /* v2.11: LEXIT is only needed for .BREAK */
    if (cmd == T_DOT_WHILE) {
      hll->cmd = HLL_WHILE;
      hll->condlines = NULL;
      if (tokenarray[i].token != T_FINAL) {
        rc = EvaluateHllExpression(hll, &i, tokenarray, LSTART, TRUE, buffer);
        if (rc == NOT_ERROR) {
          int size;
          size = strlen(buffer) + 1;
          hll->condlines = LclAlloc(size);
          memcpy(hll->condlines, buffer, size);
          DebugCmd(cntCond++); DebugCmd(cntCondBytes += size);
        }
      }
      else
        buffer[0] = NULLC;  /* just ".while" without expression is accepted */

      /* create a jump to test label */
      /* optimisation: if line at 'test' label is just a jump, dont create label and don't jump! */
      if (_memicmp(buffer, "jmp", 3)) {
        hll->labels[LTEST] = GetHllLabel();
        AddLineQueueX(JMPPREFIX "jmp %s", GetLabelStr(hll->labels[LTEST], buff));
      }
    }
    else {
      hll->cmd = HLL_REPEAT;
    }
    AddLineQueueX("%s" LABELQUAL, GetLabelStr(hll->labels[LSTART], buff));
    break;
#ifdef DEBUG_OUT
  default: /**/myassert(0); break;
#endif
  }

  if (tokenarray[i].token != T_FINAL && rc == NOT_ERROR) {
    DebugMsg(("HllStartDir: unexpected token [%s]\n", tokenarray[i].tokpos));
    EmitErr(SYNTAX_ERROR_EX, tokenarray[i].tokpos);
    rc = ERROR;
    //return( ERROR ); /* v2.08: continue and parse the line queue */
  }
  /* v2.06: remove the item from the free stack */
  if (hll == HllFree)
    HllFree = hll->next;
  hll->next = HllStack;
  HllStack = hll;

  if (ModuleInfo.list)
    LstWrite(LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL);

  if (is_linequeue_populated()) /* might be NULL! (".if 1") */
    RunLineQueue();

  return(rc);
}

/*
* .ENDIF, .ENDW, .ENDFOR .UNTIL and .UNTILCXZ directives.
* These directives end a .IF, .WHILE or .REPEAT block.
*/
ret_code HllEndDir(int i, struct asm_tok tokenarray[])
/******************************************************/
{
  //struct asym       *sym;
  struct hll_item     *hll;
  ret_code            rc = NOT_ERROR;
  int                 cmd = tokenarray[i].tokval;
  char buff[16];
  //char buffer[MAX_LINE_LEN*2];


  char buffer[MAX_LINE_LEN * 2];

  DebugMsg1(("HllEndDir(%s) enter\n", tokenarray[i].string_ptr));

  if (HllStack == NULL) {
    DebugMsg(("HllEndDir: hll stack is empty\n"));
    return(EmitError(DIRECTIVE_MUST_BE_IN_CONTROL_BLOCK));
  }

  hll = HllStack;
  HllStack = hll->next;
  /* v2.06: move the item to the free stack */
  hll->next = HllFree;
  HllFree = hll;

  switch (cmd) {
  case T_DOT_ENDIF:
    if (hll->cmd != HLL_IF) {
      DebugMsg(("HllEndDir: no .IF on the hll stack\n"));
      return(EmitErr(BLOCK_NESTING_ERROR, tokenarray[i].string_ptr));
    }
    i++;
    /* if a test label isn't created yet, create it */
    if (hll->labels[LTEST]) {
      AddLineQueueX("%s" LABELQUAL, GetLabelStr(hll->labels[LTEST], buff));
    }
    break;
    // added by habran
  case T_DOT_ENDFOR:
    if (hll->cmd != HLL_FOR) {
      DebugMsg(("HllEndDir: no .FOR on the hll stack\n"));
      EmitErr(BLOCK_NESTING_ERROR, tokenarray[i].string_ptr);
      return(ERROR);
    }
    i++;
    //Insert .CONTINUE label here if there is any 
    if (hll->labels[LCONT])
      AddLineQueueX("%s" LABELQUAL, GetLabelStr(hll->labels[LCONT], buff));
    //forever loop '.for (::)'
    if (hll->cmcnt == 0) goto adlabel;
    //If counters exist  
    else if (hll->counterlines[0]){
      //here we write counters
      if (hll->counterlines) {      //if there is something after second ':' expand it here
        ForInitAndNext(tokenarray, hll->cmcnt, hll->counterlines);
        LclFree(hll->counterlines);
      } 
      //first jump from the top happens here after the counters
      AddLineQueueX("%s" LABELQUAL, GetLabelStr(hll->labels[LSKIP], buff));
      /* create test label */
      if (hll->labels[LTEST]) {
        AddLineQueueX("%s" LABELQUAL, GetLabelStr(hll->labels[LTEST], buff));
      }
      QueueTestLines(hll->condlines);
      LclFree(hll->condlines);
    }
    else
      AddLineQueueX(" jmp %s", GetLabelStr(hll->labels[LSTART], buff));
    if (!hll->cond)
 adlabel:
      AddLineQueueX(" jmp %s", GetLabelStr(hll->labels[LSTART], buff));
    tokenarray[i].token = T_FINAL;
    break;
    //end of .ENDFOR
  case T_DOT_ENDW:
    if (hll->cmd != HLL_WHILE) {
      DebugMsg(("HllEndDir: no .WHILE on the hll stack\n"));
      return(EmitErr(BLOCK_NESTING_ERROR, tokenarray[i].string_ptr));
    }
    i++;
    /* create test label */
    if (hll->labels[LTEST]) {
      AddLineQueueX("%s" LABELQUAL, GetLabelStr(hll->labels[LTEST], buff));
    }
    QueueTestLines(hll->condlines);
    LclFree(hll->condlines);
    break;
  case T_DOT_UNTILCXZ:
    if (hll->cmd != HLL_REPEAT) {
      DebugMsg(("HllEndDir: no .REPEAT on the hll stack\n"));
      return(EmitErr(BLOCK_NESTING_ERROR, tokenarray[i].string_ptr));
    }
    i++;
    if (hll->labels[LTEST]) /* v2.11: LTEST only needed if .CONTINUE has occured */
      AddLineQueueX("%s" LABELQUAL, GetLabelStr(hll->labels[LTEST], buff));

    /* read in optional (simple) expression */
    if (tokenarray[i].token != T_FINAL) {
      rc = EvaluateHllExpression(hll, &i, tokenarray, LSTART, FALSE, buffer);
      if (rc == NOT_ERROR) {
        rc = CheckCXZLines(buffer);
        if (rc == NOT_ERROR)
          QueueTestLines(buffer); /* write condition lines */
        else
          EmitError(EXPR_TOO_COMPLEX_FOR_UNTILCXZ);
      }
    }
    else {
      AddLineQueueX(JMPPREFIX "loop %s", GetLabelStr(hll->labels[LSTART], buff));
    }
    break;
  case T_DOT_UNTIL:
    if (hll->cmd != HLL_REPEAT) {
      DebugMsg(("HllEndDir: no .REPEAT on the hll stack\n"));
      return(EmitErr(BLOCK_NESTING_ERROR, tokenarray[i].string_ptr));
    }
    i++;
    if (hll->labels[LTEST]) /* v2.11: LTEST only needed if .CONTINUE has occured */
      AddLineQueueX("%s" LABELQUAL, GetLabelStr(hll->labels[LTEST], buff));

    /* read in (optional) expression */
    /* if expression is missing, just generate nothing */
    if (tokenarray[i].token != T_FINAL) {
      rc = EvaluateHllExpression(hll, &i, tokenarray, LSTART, FALSE, buffer);
      if (rc == NOT_ERROR)
        QueueTestLines(buffer); /* write condition lines */
    }
    break;
#ifdef DEBUG_OUT
  default: /**/myassert(0); break;
#endif
  }

  /* create the exit label if it has been referenced */
  if (hll->labels[LEXIT])
    AddLineQueueX("%s" LABELQUAL, GetLabelStr(hll->labels[LEXIT], buff));

  if (tokenarray[i].token != T_FINAL && rc == NOT_ERROR) {
    EmitErr(SYNTAX_ERROR_EX, tokenarray[i].tokpos);
    rc = ERROR;
  }
  if (ModuleInfo.list)
    LstWrite(LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL);

  /* v2.11: always run line-queue if it's not empty. */
  if (is_linequeue_populated())
    RunLineQueue();

  return(rc);
}

/*
* .ELSE, .ELSEIF, .CONTINUE and .BREAK directives.
* .ELSE, .ELSEIF:
*    - create a jump to exit label
*    - render test label if it was referenced
*    - for .ELSEIF, create new test label and evaluate expression
* .CONTINUE, .BREAK:
*    - jump to test / exit label of innermost .WHILE/.REPEAT block
*
*/
ret_code HllExitDir(int i, struct asm_tok tokenarray[])
/*******************************************************/
{
  //int               level;
  //struct asym       *sym;
  struct hll_item     *hll;
  ret_code            rc = NOT_ERROR;
  int                 idx;
  int                 cmd = tokenarray[i].tokval;
  char buff[16];
  char buffer[MAX_LINE_LEN * 2];

  DebugMsg1(("HllExitDir(%s) enter\n", tokenarray[i].string_ptr));

  hll = HllStack;

  if (hll == NULL) {
    DebugMsg(("HllExitDir stack error\n"));
    return(EmitError(DIRECTIVE_MUST_BE_IN_CONTROL_BLOCK));
  }

  switch (cmd) {
  case T_DOT_ELSE:
  case T_DOT_ELSEIF:
    if (hll->cmd != HLL_IF) {
      DebugMsg(("HllExitDir(%s): labels[LTEST]=%X\n", tokenarray[i].string_ptr, hll->labels[LTEST]));
      return(EmitErr(BLOCK_NESTING_ERROR, tokenarray[i].string_ptr));
    }
    /* v2.08: check for multiple ELSE clauses */
    if (hll->flags & HLLF_ELSEOCCURED) {
      return(EmitError(DOT_ELSE_CLAUSE_ALREADY_OCCURED_IN_THIS_DOT_IF_BLOCK));
    }

    /* the 'exit'-label is only needed if an .ELSE branch exists.
    * That's why it is created delayed.
    */
    if (hll->labels[LEXIT] == 0)
      hll->labels[LEXIT] = GetHllLabel();
    AddLineQueueX(JMPPREFIX "jmp %s", GetLabelStr(hll->labels[LEXIT], buff));

    if (hll->labels[LTEST] > 0) {
      AddLineQueueX("%s" LABELQUAL, GetLabelStr(hll->labels[LTEST], buff));
      hll->labels[LTEST] = 0;
    }
    i++;
    if (cmd == T_DOT_ELSEIF) {
      /* create new labels[LTEST] label */
      hll->labels[LTEST] = GetHllLabel();
      rc = EvaluateHllExpression(hll, &i, tokenarray, LTEST, FALSE, buffer);
      if (rc == NOT_ERROR)
        QueueTestLines(buffer);
    }
    else
      hll->flags |= HLLF_ELSEOCCURED;

    break;
  case T_DOT_BREAK:
  case T_DOT_CONTINUE:
    for (; hll && hll->cmd == HLL_IF; hll = hll->next);
    if (hll == NULL) {
      return(EmitError(DIRECTIVE_MUST_BE_IN_CONTROL_BLOCK));
    }
    /* v2.11: create 'exit' and 'test' labels delayed.
    */
    if (cmd == T_DOT_BREAK) {
      if (hll->labels[LEXIT] == 0)
        hll->labels[LEXIT] = GetHllLabel();
      idx = LEXIT;
    }
    else if (hll->cmd == HLL_FOR) {
      /* added by habran 
         .CONTINUE label is created here for .FOR loops only if it exists.
         It is different than .WHILE because it has to first alter counters
      */
        if (hll->labels[LCONT] == 0) hll->labels[LCONT] = GetHllLabel();
        idx = (hll->labels[LCONT] ? LCONT : LSTART);
      }else {
            /* 'test' is not created for .WHILE loops here; because
             * if it doesn't exist, there's no condition to test.
             */
            if ( hll->cmd == HLL_REPEAT && hll->labels[LTEST] == 0 )
                hll->labels[LTEST] = GetHllLabel();
            idx = ( hll->labels[LTEST] ? LTEST : LSTART );
        }

    /* .BREAK .IF ... or .CONTINUE .IF ? */
    i++;
    if (tokenarray[i].token != T_FINAL) {
      if (tokenarray[i].token == T_DIRECTIVE && tokenarray[i].tokval == T_DOT_IF) {
        enum hll_cmd savedcmd = hll->cmd;
        hll->cmd = HLL_BREAK;
        i++;
        /* v2.11: set rc and don't exit if an error occurs; see hll3.aso */
        rc = EvaluateHllExpression(hll, &i, tokenarray, idx, TRUE, buffer);
        if (rc == NOT_ERROR)
          QueueTestLines(buffer);
        hll->cmd = savedcmd;
      }
    }
    else {
      AddLineQueueX(JMPPREFIX "jmp %s", GetLabelStr(hll->labels[idx], buff));
    }
    break;
#ifdef DEBUG_OUT
  default: /**/myassert(0); break;
#endif
  }
  if (tokenarray[i].token != T_FINAL && rc == NOT_ERROR) {
    EmitErr(SYNTAX_ERROR_EX, tokenarray[i].tokpos);
    rc = ERROR;
  }

  if (ModuleInfo.list)
    LstWrite(LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL);

  /* v2.11: always run line-queue if it's not empty. */
  if (is_linequeue_populated())
    RunLineQueue();

  return(rc);
}

/* check if an hll block has been left open. called after pass 1 */

void HllCheckOpen(void)
/***********************/
{
  if (HllStack) {
    //EmitErr( BLOCK_NESTING_ERROR, ".if-.repeat-.while" );
    EmitErr(UNMATCHED_BLOCK_NESTING, ".if-.repeat-.while");
  }
  DebugMsg(("HllCheckOpen: allocated items:%u, reused items:%u, .while cond-blocks/bytes:%u/%u\n", cntAlloc, cntReused, cntCond, cntCondBytes));
}

#if FASTMEM==0
void HllFini(void)
/******************/
{
  struct hll_item *curr;
  struct hll_item *next;
  /* release the items in the HllFree heap.
  * there might also be some left in HllStack...
  */
  for (curr = HllFree; curr; curr = next) {
    next = curr->next;
    LclFree(curr);
  }
}
#endif

/* HllInit() is called for each pass */

void HllInit(int pass)
/**********************/
{
  //if ( pass == PASS_1 )
  //    HllFree = NULL;

  //HllStack = NULL; /* empty stack of open hll directives */
  ModuleInfo.hll_label = 0; /* init hll label counter */
#ifdef DEBUG_OUT
  evallvl = 0;
  if (pass == PASS_1) {
    cntAlloc = 0;
    cntReused = 0;
    cntCond = 0;
    cntCondBytes = 0;
  }
#endif
  return;
}
