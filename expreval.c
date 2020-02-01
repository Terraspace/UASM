/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  expression evaluator.
*
****************************************************************************/

#include <stddef.h>
#include <ctype.h>

#include "globals.h"
#include "parser.h"
#include "reswords.h"
#include "expreval.h"
#include "segment.h"
#include "proc.h"
#include "assume.h"
#include "tokenize.h"
#include "types.h"
#include "label.h"
#include "atofloat.h"
#include "myassert.h"
#include "lqueue.h"
#include "data.h"
#include "symbols.h"

#if defined(WINDOWSDDK)
#define PRIx64       "llx"
#else
#include <inttypes.h>
#endif

#define ALIAS_IN_EXPR 1 /* allow alias names in expression */

#define UNARY_PLUSMINUS 0
#define BINARY_PLUSMINUS 1

/* activate if a detailed error location is needed and -dt cant be used */
#if 0
#define ERRLOC( i ) printf("Error at %s.%u: %u >%s< >%s<\n", __FILE__, __LINE__, i, ModuleInfo.tokenarray[i].string_ptr, ModuleInfo.tokenarray[0].tokpos )
//#undef DebugMsg1
//#define DebugMsg1( x ) printf x
#else
#define ERRLOC( i )
#endif

#if STACKBASESUPP==0
extern enum special_token basereg[];
#else
extern uint_32          StackAdj;
#endif
bool gmaskflag;
#ifdef DEBUG_OUT
static int evallvl = 0;
#endif
extern uint_32          GetCurrOffset( void );
extern void ShiftLeft (uint_64 *dstHi, uint_64 *dstLo,uint_64 num, int pos);
//extern ret_code data_item( int *, struct asm_tok[], struct asym *, uint_32, const struct asym *, uint_32, bool inside_struct, bool, bool, int );
extern ret_code      BackPatch( struct asym *sym );
/* the following static variables should be moved to ModuleInfo. */
static struct asym *thissym; /* helper symbol for THIS operator */
static struct asym *nullstruct; /* used for T_DOT if second op is a forward ref */
static struct asym *nullmbr; /* used for T_DOT if "current" struct is a forward ref */
static int (* fnEmitErr)( int, ... );
static int noEmitErr( int msg, ... );

/* code label type values - returned by SIZE and TYPE operators */
enum labelsize {
    LS_SHORT  = 0xFF01, /* it's documented, but can a label be "short"? */
    //LS_NEAR16 = 0xFF02, /* v2.09: the near values are calculated */
    //LS_NEAR32 = 0xFF04,
    //LS_NEAR64 = 0xFF08,
    LS_FAR16  = 0xFF05,
    LS_FAR32  = 0xFF06,
};

static void init_expr( struct expr *opnd )
/****************************************/
{
    opnd->value    = 0;
    opnd->hvalue   = 0;
    opnd->hlvalue  = 0;
    opnd->quoted_string   = NULL;
    opnd->base_reg = NULL;
    opnd->idx_reg  = NULL;
    opnd->label_tok = NULL;
    opnd->override = NULL;
    opnd->instr    = EMPTY;
    opnd->kind     = EXPR_EMPTY;
    opnd->mem_type = MT_EMPTY;
    opnd->scale    = 0;
    opnd->Ofssize  = USE_EMPTY;
    opnd->flags1   = 0;
    opnd->sym      = NULL;
    opnd->mbr      = NULL;
    opnd->type     = NULL;
	opnd->isptr = FALSE;
}

static ret_code  GetMask128(struct expr *opnd1, int index, struct asm_tok tokenarray[])
  {
    uint_64         dst128Hi = opnd1->hlvalue;
    uint_64         dst128Lo = opnd1->llvalue;
	  struct          asym *lbl = NULL;
    char            buffer[MAX_LINE_LEN];
    char            buffer1[MAX_LINE_LEN];
    char            buff[18];
    char            *ptr;
    int             i= Token_Count; /* i must remain the start index */


      strcpy( buffer,tokenarray->tokpos); 
    /* if GTEMP is not created yet do it now */
    if (Parse_Pass == PASS_1){
      lbl = SymSearch("GMASK");
      if (lbl == NULL){
        strcpy(buffer1, ".data");
        strcpy(tokenarray->tokpos, buffer1);
        Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);
        ParseLine(tokenarray);
        strcpy(buffer1, "GMASK OWORD 0x");
        num2hex64(dst128Hi, buff);
        strcat(buffer1, buff);
        num2hex64(dst128Lo, buff);
        strcat(buffer1, buff);
        strcpy(tokenarray->tokpos, buffer1);
        Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);
        ParseLine(tokenarray);
        strcpy(buffer1, ".code");
        strcpy(tokenarray->tokpos, buffer1);
        Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);
        ParseLine(tokenarray);
        ptr = tokenarray->tokpos;
        while (*ptr != '\0')*(ptr++) = '\0';
        ptr = buffer;
        while (*ptr != ',')ptr++;
        ptr++;
        *ptr = '\0';
        strcat(ptr, "GMASK");
        AddLineQueue(buffer);
        strcpy(tokenarray->tokpos, buffer);
        Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);
        tokenarray[Token_Count+1].token = T_FINAL;
        ParseLine(tokenarray);
        }
      else{ /* global variable GMASK exist, reuse it   */
        num2hex64(dst128Lo, buff);
        strcpy(buffer1, "mov dword ptr  ");
        ptr = buffer1 + 14;
        strcpy(ptr, "GMASK");                  /* mov dword ptr rubi.rc */
        ptr += 5;
        strcpy(ptr, ", LOW32(0x");              /* mov dword ptr rubi.rc, LOW32( */
        ptr += 10;
        strcat(ptr, buff); /* mov dword ptr rubi.rc, LOW32(dst128Lo */
        strcat(ptr, ")");
        strcpy(tokenarray->tokpos, buffer1);
        Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);
        ParseLine(tokenarray);
        /* second DWORD */
        ptr = buffer1 + 19;
        strcpy(ptr, "+4 ,HIGH32(0x");          /* mov dword ptr rubi.rc, HIGH32( */
        ptr += 13;
        strcat(ptr, buff); /* mov dword ptr rubi.rc, LOW32(dst128Lo */
        strcat(ptr, ")");
        strcpy(tokenarray->tokpos, buffer1);
        Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);
        ParseLine(tokenarray);
        /* third DWORD */
        num2hex64(dst128Hi, buff);
        ptr = buffer1 + 19;
        strcpy(ptr, "+8, LOW32(0x");          /* mov dword ptr rubi.rc, LOW32( */
        ptr += 12;
        strcat(ptr, buff); /* mov dword ptr rubi.rc, LOW32(dst128Lo */
        strcat(ptr, ")");
        strcpy(tokenarray->tokpos, buffer1);
        Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);
        ParseLine(tokenarray);
        /* forth DWORD */
        ptr = buffer1 + 19;
        strcpy(ptr, "+8+4, HIGH32(0x");          /* mov dword ptr rubi.rc, HIGH32( */
        ptr += 15;
        strcat(ptr, buff); /* mov dword ptr rubi.rc, LOW32(dst128Lo */
        strcat(ptr, ")");
        strcpy(tokenarray->tokpos, buffer1);
        Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);
        ParseLine(tokenarray);
        ptr = tokenarray->tokpos;
        while (*ptr != '\0')*(ptr++) = '\0';
        ptr = buffer;
        while (*ptr != ',')ptr++;
        ptr++;
        *ptr = '\0';
        strcat(ptr, "GMASK");
        strcpy(tokenarray->tokpos, buffer);
        Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);
        tokenarray[Token_Count+1].token = T_FINAL;
        ParseLine(tokenarray);
        } 
      }   
    //strcpy(buffer1, "nop");
    strcpy(tokenarray->tokpos, "por ");
    strcat(tokenarray->tokpos,tokenarray[1].string_ptr);
    strcat(tokenarray->tokpos,", ");
    strcat(tokenarray->tokpos,tokenarray[1].string_ptr);
    //strcpy(tokenarray->tokpos, buffer1);
    Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);
    tokenarray[Token_Count+1].token = T_FINAL;
    gmaskflag = TRUE;
    DebugMsg1(("GetMask128(%s) exit, current ofs=%" I32_SPEC "X\n",  GetCurrOffset() ));
    return( NOT_ERROR );      
  }

/*   InitRecordVar is used for inline initialise RECORD to be compatibile with masm, v2.41 
*    now it can be used as :
*    mov     al, COLOR<1, 7, 0, 1>         ;1 111 0 001 = F1
*    mov     cobalt.rc, COLOR<1, 7, 0, 1>  ;1 111 0 001 = F1
*/
static ret_code  InitRecordVar( struct expr *opnd1, int index, struct asm_tok tokenarray[], const struct dsym *symtype )
/****************************************************************************************************************************/
{
    char            *ptr, *ptr2, *ptr3;
    struct sfield   *f;
    int_32          nextofs;
    int             i;
    int             nlabel;
    struct asym    *sym = NULL;
    struct          asym *lbl = NULL;
#if AMD64_SUPPORT
    uint_64         dst128Hi;
    uint_64         dst128Lo;
    uint_64         dwRecIHi;
    uint_64         dwRecILo;
    uint_64         dwRecInit;
#else
    uint_32         dwRecInit;
#endif
    bool            is_record_set;
    struct expr     opndx;
    char            buffer[MAX_LINE_LEN];
    char            buffer1[MAX_LINE_LEN];
    char            buff[16];
	  int             tok_start = index - 1;
	  int             len;
	  char            *oldptr;

    /**/myassert( symtype->sym.state == SYM_TYPE && symtype->sym.typekind != TYPE_TYPEDEF );
    if ( tokenarray[index].token == T_STRING ) {
        if ( tokenarray[index].string_delim != '<' &&
            tokenarray[index].string_delim != '{' ) {
            return( EmitError( MISSING_ANGLE_BRACKET_OR_BRACE_IN_LITERAL ) );
        }
        i = Token_Count + 1;
        Token_Count = Tokenize( tokenarray[index].string_ptr, i, tokenarray, TOK_RESCAN );
        /* once Token_Count has been modified, don't exit without
         * restoring this value!
         */
        index++;

    } 
    if ( symtype->sym.typekind == TYPE_RECORD ) {
        dwRecInit = 0;
        dst128Hi = 0; /* clear Hi 64 bit for the 128 bit RECORD */
        dst128Lo = 0; /* clear Lo 64 bit for the 128 bit RECORD */
        is_record_set = FALSE;
    }

    /* scan the RECORD's members */
    for( f = symtype->e.structinfo->head; f != NULL; f = f->next ) {

        DebugMsg1(("InitRecordVar(%s) field=%s ofs=%" I32_SPEC "u total_size=%" I32_SPEC "u total_len=%" I32_SPEC "u value=>%s< >%s<\n",
                  symtype->sym.name,
                  f->sym.name,
                  f->sym.offset,
                  f->sym.total_size,
                  f->sym.total_length,
                  f->ivalue, tokenarray[i].tokpos ));

        /* is it a RECORD field? */
        if ( f->sym.mem_type == MT_BITS ) {
            if ( tokenarray[i].token == T_COMMA || tokenarray[i].token == T_FINAL ) {
                if ( f->ivalue[0] ) {
                    int j = Token_Count + 1;
                    int max_item = Tokenize( f->ivalue, j, tokenarray, TOK_RESCAN );
                    EvalOperand( &j, tokenarray, max_item, &opndx, 0 );
                    is_record_set = TRUE;
                } else {
                    opndx.value = 0;
                    opndx.kind = EXPR_CONST;
                    opndx.quoted_string = NULL;
                }
            } else {
                EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 );
                is_record_set = TRUE;
            }
            if ( opndx.kind != EXPR_CONST || opndx.quoted_string != NULL )
                EmitError( CONSTANT_EXPECTED );

            /* fixme: max bits in 64-bit is 64 - see MAXRECBITS! */
            if ( f->sym.total_size < 32 ) {
                uint_32 dwMax = (1 << f->sym.total_size);
                if ( opndx.value >= dwMax )
                    EmitErr( INITIALIZER_MAGNITUDE_TOO_LARGE, f->sym.name );
            }
#if AMD64_SUPPORT
            if (symtype->sym.mem_type == MT_OWORD){
                dwRecIHi = 0;  /* clear Hi 64 bit for the 128 bit RECORD */
                dwRecILo = 0;  /* clear Lo 64 bit for the 128 bit RECORD */
                ShiftLeft(&dwRecIHi,&dwRecILo,opndx.llvalue,f->sym.offset);
                dst128Hi |= dwRecIHi; /* OR Hi 64 bit for the 128 bit RECORD */
                dst128Lo |= dwRecILo; /* clear Lo 64 bit for the 128 bit RECORD */
              }
            else
               dwRecInit |= opndx.llvalue << f->sym.offset;
#else
            dwRecInit |= opndx.value << f->sym.offset;
#endif
        } 
        else if ( f->sym.total_size == f->sym.total_length &&
                   tokenarray[i].token == T_STRING &&
                   tokenarray[i].stringlen > 1 &&
                   ( tokenarray[i].string_delim == '"' ||
                    tokenarray[i].string_delim == '\'' ) ) {
            /* v2.07: it's a byte type, but no array, string initializer must have true length 1 */
            EmitError( STRING_OR_TEXT_LITERAL_TOO_LONG );
            i++;
        } 
        /* Add padding bytes if necessary (never inside RECORDS!).
         * f->next == NULL : it's the last field of the struct/union/record
         */
        if ( symtype->sym.typekind != TYPE_RECORD ) {
            if ( f->next == NULL || symtype->sym.typekind == TYPE_UNION )
                nextofs = symtype->sym.total_size;
            else
                nextofs = f->next->sym.offset;

            if ( f->sym.offset + f->sym.total_size < nextofs ) {
                DebugMsg1(("InitRecordVar: padding, field=%s ofs=%" I32_SPEC "X total=%" I32_SPEC "X nextofs=%" I32_SPEC "X\n",
                          f->sym.name, f->sym.offset, f->sym.total_size, nextofs ));
                SetCurrOffset( CurrSeg, nextofs - (f->sym.offset + f->sym.total_size), TRUE, TRUE );
            }
        }
        /* for a union, just the first field is initialized */
        if ( symtype->sym.typekind == TYPE_UNION )
            break;

        if ( f->next != NULL ) {

            if ( tokenarray[i].token != T_FINAL )
                if ( tokenarray[i].token == T_COMMA )
                    i++;
                else {
                    EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos );
                    while ( tokenarray[i].token != T_FINAL && tokenarray[i].token != T_COMMA )
                        i++;
                }
        }
    }  /* end for */
    opnd1->llvalue = dwRecInit;
    if (tokenarray[1].token == T_REG) {
      ptr=tokenarray->tokpos + 4;
      while (isspace(*ptr))ptr++;
      if (*ptr == 'r' || *ptr == 'R')
        goto all;
      else if (opnd1->llvalue < 0x100000000)
        goto all;
      else
      EmitErr(INITIALIZER_OUT_OF_RANGE);
all:
      /* mov dword ptr rubi.rc, LOW32(dst128Lo) 
      *  mov dword ptr rubi.rc+4 ,HIGH32(dst128Lo)
      *  mov dword ptr rubi.rc+8 , LOW32(dst128Hi)
      *  mov dword ptr rubi.rc+8+4,HIGH32(dst128Hi) */

      if (0 == _stricmp(tokenarray->string_ptr, "movxmmr128")){
          strcpy( buffer,tokenarray->tokpos+10);
          ptr = buffer;
          while (*ptr != ',')ptr++;
          *ptr = '\0';
          ptr++;
          /* if not created global variable GTEMP create it   */
            lbl = SymSearch("GTEMP");
            if (lbl == NULL){
            strcpy(buffer1, ".data");
            strcpy(tokenarray->tokpos, buffer1);
            Token_Count = Tokenize( tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT );
            ParseLine(tokenarray);          
            sprintf(buff, "GTEMP");
            strcpy(buffer1,buff);
            strcat(buffer1,ptr);
            strcpy(tokenarray->tokpos, buffer1);
            Token_Count = Tokenize( tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT );
            ParseLine(tokenarray);
            strcpy(buffer1, ".code");
            strcpy(tokenarray->tokpos, buffer1);
            Token_Count = Tokenize( tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT );
            ParseLine(tokenarray);
          }
           else{ /* global variable GTEMP exist, reuse it   */
             strcpy(buffer1, "mov dword ptr  ");
             ptr = buffer1 + 14;
             strcpy(ptr, "GTEMP");                  /* mov dword ptr rubi.rc */
             ptr += 5;
             strcpy(ptr, ", LOW32(");              /* mov dword ptr rubi.rc, LOW32( */
             ptr += 8;
             sprintf(ptr, "0x%" PRIx64, dst128Lo); /* mov dword ptr rubi.rc, LOW32(dst128Lo */
             while (*ptr)ptr++;
             *ptr = ')';
             ptr++;
             *ptr = '\0';
             strcpy(tokenarray->tokpos, buffer1);
             Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);
             ParseLine(tokenarray);
             /* second DWORD */
             strcpy(buffer1, "mov dword ptr  ");
             ptr = buffer1 + 14;
             strcpy(ptr, "GTEMP");                  /* mov dword ptr rubi.rc */
             ptr += 5;
             strcpy(ptr, "+4 ,HIGH32(");          /* mov dword ptr rubi.rc, HIGH32( */
             ptr += 11;
             sprintf(ptr, "0x%" PRIx64, dst128Lo); /* mov dword ptr rubi.rc, LOW32(dst128Lo */
             while (*ptr)ptr++;
             *ptr = ')';
             ptr++;
             *ptr = '\0';
             strcpy(tokenarray->tokpos, buffer1);
             Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);
             ParseLine(tokenarray);
             /* third DWORD */
             strcpy(buffer1, "mov dword ptr  ");
             ptr = buffer1 + 14;
             strcpy(ptr, "GTEMP");                  /* mov dword ptr rubi.rc */
             ptr += 5;
             strcpy(ptr, "+8, LOW32(");          /* mov dword ptr rubi.rc, LOW32( */
             ptr += 10;
             sprintf(ptr, "0x%" PRIx64, dst128Hi); /* mov dword ptr rubi.rc, LOW32(dst128Hi */
             while (*ptr)ptr++;
             *ptr = ')';
             ptr++;
             *ptr = '\0';
             strcpy(tokenarray->tokpos, buffer1);
             Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);
             ParseLine(tokenarray);
             /* forth DWORD */
             strcpy(buffer1, "mov dword ptr  ");
             ptr = buffer1 + 14;
             strcpy(ptr, "GTEMP");                  /* mov dword ptr rubi.rc */
             ptr += 5;
             strcpy(ptr, "+8+4, HIGH32(");          /* mov dword ptr rubi.rc, HIGH32( */
             ptr += 13;
             sprintf(ptr, "0x%" PRIx64, dst128Hi); /* mov dword ptr rubi.rc, LOW32(dst128Lo */
             while (*ptr)ptr++;
             *ptr = ')';
             ptr++;
             *ptr = '\0';
             strcpy(tokenarray->tokpos, buffer1);
             Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);
             ParseLine(tokenarray);
         }
         /* now write new line with "movups xmm1, GTEMP"   */
		  strcpy(buffer1, MOVE_UNALIGNED_FLOAT());
          strcat(buffer1,buffer);
          strcat(buffer1," , ");
          strcat(buffer1,"GTEMP");
          strcpy(tokenarray->tokpos, buffer1);
          Token_Count = Tokenize( tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT );
          goto exit;
       }else if (0 == _stricmp(tokenarray->string_ptr, "mov128")){
         strcpy( buffer,tokenarray->tokpos+6);
          ptr = buffer;
          while (*ptr != ',')ptr++;
          *ptr = '\0';
          strcpy(buffer1, "mov dword ptr  " );
          ptr = buffer1+14;
          strcpy(ptr, buffer);                  /* mov dword ptr rubi.rc */
          ptr += strlen(buffer);
          strcpy(ptr, ", LOW32(");              /* mov dword ptr rubi.rc, LOW32( */
          ptr += 8;
          sprintf(ptr, "0x%" PRIx64, dst128Lo); /* mov dword ptr rubi.rc, LOW32(dst128Lo */
          while (*ptr)ptr++;
          *ptr = ')';
          ptr++;
          *ptr = '\0';
          strcpy(tokenarray->tokpos, buffer1);
          Token_Count = Tokenize( tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT );
          ParseLine(tokenarray);
          /* second DWORD */
          strcpy(buffer1, "mov dword ptr  " );
          ptr = buffer1+14;
          strcpy(ptr, buffer);                  /* mov dword ptr rubi.rc */
          ptr += strlen(buffer);
          strcpy(ptr, "+4 ,HIGH32(");          /* mov dword ptr rubi.rc, HIGH32( */
          ptr += 11;
          sprintf(ptr, "0x%" PRIx64, dst128Lo); /* mov dword ptr rubi.rc, LOW32(dst128Lo */
          while (*ptr)ptr++;
          *ptr = ')';
          ptr++;
          *ptr = '\0';
          strcpy(tokenarray->tokpos, buffer1);
          Token_Count = Tokenize( tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT );
          ParseLine(tokenarray);
          /* third DWORD */
          strcpy(buffer1, "mov dword ptr  " );
          ptr = buffer1+14;
          strcpy(ptr, buffer);                  /* mov dword ptr rubi.rc */
          ptr += strlen(buffer);
          strcpy(ptr, "+8, LOW32(");          /* mov dword ptr rubi.rc, LOW32( */
          ptr += 10;
          sprintf(ptr, "0x%" PRIx64, dst128Hi); /* mov dword ptr rubi.rc, LOW32(dst128Hi */
          while (*ptr)ptr++;
          *ptr = ')';
          ptr++;
          *ptr = '\0';
          strcpy(tokenarray->tokpos, buffer1);
          Token_Count = Tokenize( tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT );
          ParseLine(tokenarray);
          /* forth DWORD */
          strcpy(buffer1, "mov dword ptr  " );
          ptr = buffer1+14;
          strcpy(ptr, buffer);                  /* mov dword ptr rubi.rc */
          ptr += strlen(buffer);
          strcpy(ptr, "+8+4, HIGH32(");          /* mov dword ptr rubi.rc, HIGH32( */
          ptr += 13;
          sprintf(ptr, "0x%" PRIx64, dst128Hi); /* mov dword ptr rubi.rc, LOW32(dst128Lo */
          while (*ptr)ptr++;
          *ptr = ')';
          ptr++;
          *ptr = '\0';
          strcpy(tokenarray->tokpos, buffer1);
          Token_Count = Tokenize( tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT );
        goto exit;
       }
     else{
       strcpy(buffer, tokenarray->tokpos);
       ptr = strstr(buffer, tokenarray[tok_start].string_ptr);
       oldptr = ptr;
       len = 0;
       while (*ptr != '>')
         {
         ptr++;
         len++;
         }
       ptr = tokenarray->tokpos + (oldptr - buffer);
       for (i = 0; i <= len; i++)
         *ptr++ = 0x20;
       ptr = buffer;
       sprintf(ptr, "0x%" PRIx64, dwRecInit);
       oldptr = tokenarray->tokpos + (oldptr - buffer);
       len = strlen(buffer);
       for (i = 0; i < len; i++)
         *oldptr++ = *ptr++;
       Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);
       goto exit;
       }
    }
    else if (opnd1->llvalue < 0x100000000) 
      goto all;
    else 
	{
		goto all;
/*		strcpy(buffer, tokenarray->tokpos);
		ptr = buffer;
		while (*ptr != ',') ptr++;
		ptr++;
		sprintf(ptr, "0x%" PRIx64, dwRecInit);
		strcpy(tokenarray->tokpos, buffer);
		Token_Count = Tokenize(tokenarray->tokpos, 0, tokenarray, TOK_DEFAULT);*/
	}
exit:
    DebugMsg1(("InitRecordVar(%s) exit, current ofs=%" I32_SPEC "X\n", symtype->sym.name, GetCurrOffset() ));
    return( NOT_ERROR );
}
    //push   253
    //push   254
    //movq  xmm1, [esp]

static void TokenAssign( struct expr *opnd1, const struct expr *opnd2 )
/*********************************************************************/
{
#if 1
    /* note that offsetof() is used. This means, don't change position
     of field <type> in expr! */
    memcpy( opnd1, opnd2, offsetof( struct expr, type ) );
#else
    opnd1->llvalue  = opnd2->llvalue;
    opnd1->hlvalue  = opnd2->hlvalue;
    opnd1->quoted_string   = opnd2->quoted_string; /* probably useless */
    opnd1->base_reg = opnd2->base_reg;
    opnd1->idx_reg  = opnd2->idx_reg;
    opnd1->label_tok = opnd2->label_tok;
    opnd1->override = opnd2->override;
    opnd1->instr    = opnd2->instr;
    opnd1->kind     = opnd2->kind;
    opnd1->mem_type = opnd2->mem_type;
    opnd1->scale    = opnd2->scale;
    opnd1->Ofssize  = opnd2->Ofssize;
    opnd1->flags1   = opnd2->flags1;
    opnd1->sym      = opnd2->sym;
    opnd1->mbr      = opnd2->mbr;
//  opnd1->type     = opnd2->type;
#endif
}

//#define BRACKET_PRECEDENCE 1
//#define PTR_PRECEDENCE     4
//#define PLUS_PRECEDENCE    9
#define CMP_PRECEDENCE    10

static int get_precedence( const struct asm_tok *item )
/*****************************************************/
{
    /* The following table is taken verbatim from MASM 6.1 Programmer's Guide,
     * page 14, Table 1.3.

     * 1            (), []
     * 2            LENGTH, SIZE, WIDTH, MASK, LENGTHOF, SIZEOF
     * 3            . (structure-field-name operator)
     * 4            : (segment override operator), PTR
     * 5            LROFFSET, OFFSET, SEG, THIS, TYPE
     * 6            HIGH, HIGHWORD, LOW, LOWWORD
     * 7            +, - (unary)
     * 8            *, /, MOD, SHL, SHR
     * 9            +, - (binary)
     * 10           EQ, NE, LT, LE, GT, GE
     * 11           NOT
     * 12           AND
     * 13           OR, XOR
     * 14           OPATTR, SHORT, .TYPE

     * The following table appears in QuickHelp online documentation for
     * both MASM 6.0 and 6.1. It's slightly different!

     * 1            LENGTH, SIZE, WIDTH, MASK
     * 2            (), []
     * 3            . (structure-field-name operator)
     * 4            : (segment override operator), PTR
     * 5            THIS, OFFSET, SEG, TYPE
     * 6            HIGH, LOW
     * 7            +, - (unary)
     * 8            *, /, MOD, SHL, SHR
     * 9            +, - (binary)
     * 10           EQ, NE, LT, LE, GT, GE
     * 11           NOT
     * 12           AND
     * 13           OR, XOR
     * 14           SHORT, OPATTR, .TYPE, ADDR

     * japheth: the first table is the prefered one. Reasons:
     * - () and [] must be first.
     * - it contains operators SIZEOF, LENGTHOF, HIGHWORD, LOWWORD, LROFFSET
     * - ADDR is no operator for expressions. It's exclusively used inside
     *   INVOKE directive.

     * However, what's wrong in both tables is the precedence of
     * the dot operator: Actually for both Uasm and Wasm the dot precedence
     * is 2 and LENGTH, SIZE, ... have precedence 3 instead.

     * Precedence of operator TYPE was 5 in original Wasm source. It has
     * been changed to 4, as described in the Masm docs. This allows syntax
     * "TYPE DWORD ptr xxx"

     * v2.02: another case which is problematic:
     *     mov al,BYTE PTR CS:[]
     * Since PTR and ':' have the very same priority, the evaluator will
     * first calculate 'BYTE PTR CS'. This is invalid, but didn't matter
     * prior to v2.02 because register coercion was never checked for
     * plausibility. Solution: priority of ':' is changed from 4 to 3.
     */

    switch( item->token ) {
    case T_UNARY_OPERATOR:
    case T_BINARY_OPERATOR:
        return( item->precedence );
    case T_OP_BRACKET:
    case T_OP_SQ_BRACKET:
        /* v2.08: with -Zm, the priority of [] and (), if
         * used as binary operator, is 9 (like binary +/-).
         * test cases: mov ax,+5[bx]
         *             mov ax,-5[bx]
         */
        //return( 1 );
        return( ModuleInfo.m510 ? 9 : 1 );
    case T_DOT:
        return( 2 );
    case T_COLON:
        //return( 4 );
        return( 3 ); /* changed for v2.02 */
    case '*':
    case '/':
        return( 8 );
    case '+':
    case '-':
        return( item->specval ? 9 : 7 );
    }
    /* shouldn't happen! */
    DebugMsg(("get_precedence: unexpected operator=%s\n", item->string_ptr));
    fnEmitErr( SYNTAX_ERROR_EX, item->string_ptr );
    return( ERROR );
}

#if 0
static bool is_operator( enum tok_type tt )
/*****************************************/
/* determine if token is an operator */
{
    /* T_OP_BRACKET and above: "(,[,],},:,.,+,-,*,/" */
    /* rest: T_REG, T_STYPE, T_RES_ID, T_ID, T_STRING,
     * T_NUM, T_FLOAT, T_BAD_NUM, T_DBL_COLON, T_PERCENT
     */
    return( tt >= T_OP_BRACKET || tt == T_UNARY_OPERATOR || tt == T_BINARY_OPERATOR );
}

static bool is_unary_op( enum tok_type tt )
/*****************************************/
/* determine if token is an unary operator */
{
    return( tt == T_OP_BRACKET || tt == T_OP_SQ_BRACKET || tt ==  '+' || tt == '-' || tt == T_UNARY_OPERATOR );
}

#else
#define is_operator( tt ) ( tt >= T_OP_BRACKET || tt == T_UNARY_OPERATOR || tt == T_BINARY_OPERATOR )
#define is_unary_op( tt ) ( tt == T_OP_BRACKET || tt == T_OP_SQ_BRACKET || tt ==  '+' || tt == '-' || tt == T_UNARY_OPERATOR )
#endif

/* get value for simple types
 * NEAR, FAR and PROC are handled slightly differently:
 * the HIBYTE is set to 0xFF, and PROC depends on the memory model
 */
static unsigned int GetTypeSize(enum memtype mem_type, int Ofssize)
/*******************************************************************/
{
	if ((mem_type & MT_SPECIAL) == 0) {
#if AVXSUPP
		if (mem_type == MT_ZMMWORD)
			return (0x40);
		else
#endif
			return((mem_type & MT_SIZE_MASK) + 1);
	}
	if (Ofssize == USE_EMPTY)
		Ofssize = ModuleInfo.Ofssize;
	switch (mem_type) {
	case MT_NEAR: return (0xFF00 | (2 << Ofssize));
	case MT_FAR:  return ((Ofssize == USE16) ? LS_FAR16 : 0xFF00 | ((2 << Ofssize) + 2));
	}
	/* shouldn't happen */
	return(0);
}


#if AMD64_SUPPORT
static uint_64 GetRecordMask( struct dsym *record )
#else
static uint_32 GetRecordMask( struct dsym *record )
#endif
/*************************************************/
{
#if AMD64_SUPPORT
    uint_64 mask = 0;
#else
    uint_32 mask = 0;
#endif
    int i;
    struct sfield *fl;

    for ( fl = record->e.structinfo->head; fl; fl = fl->next ) {
        struct asym *sym = &fl->sym;
        for ( i = sym->offset ;i < sym->offset + sym->total_size; i++ )
#if AMD64_SUPPORT
            mask |= (1LL << (uint_64)i);
#else
			mask |= (1 << i);
#endif
    }
    return( mask );
}

/* v2.06: the value of number strings is now evaluated here.
 * Prior to v2.06, it was evaluated in the tokenizer and the
 * value was stored in the token string buffer. Since the content
 * of the token buffer is no longer destroyed when macros or
 * generated code is run, the old strategy needed too much space.
 */

void myatoi128( const char *src, uint_64 dst[], int base, int size )
/******************************************************************/
{
    uint_32             val;
    unsigned            len;
    const char          *end = src + size;
    uint_16             *px;

    dst[0] = 0;
    dst[1] = 0;
#if CHEXPREFIX
    if (((src[1] | 0x20) == 'x') && (*src == '0')){
      src += 2;
      end += 2;
    }
#endif
    do {
        val = ( *src <= '9' ? *src - '0' : ( *src | 0x20 ) - 'a' + 10 );
        px = (uint_16 *)dst;
        for ( len = ( 2 * sizeof( uint_64 ) ) >> 1; len; len-- ) {
            val += (uint_32)*px * base;
            *(px++) = val;
            val >>= 16;
        };
        //myassert( val == 0 ); /* if number doesn't fit in 128 bits */
        src++;
    } while( src < end );
    return;
}

/* get an operand. operands are:
 * - integer constant      : EXPR_CONST
 * - quoted string         : EXPR_CONST
 * - register              : EXPR_REG (indirect = 1/0)
 * - user identifier (T_ID): EXPR_ADDR | EXPR_CONST
 * - reserved ID (T_RES_ID): EXPR_CONST ( EXPR_ADDR if id=FLAT )
 * - float constant        : EXPR_FLOAT
 *
 * valid user identifiers are
 * - TYPE ( struct/union, typedef, record )
 * - STRUCT FIELD (also bitfield)
 * - variable (internal, external, stack ) or constant (EQU, '=')
 * valid reserved IDs are types (BYTE, WORD, ... ) and FLAT
 */
static ret_code get_operand( struct expr *opnd, int *idx, struct asm_tok tokenarray[], const uint_8 flags )
/*********************************************************************************************************/
{
    char        *tmp;
    struct asym *sym;
    int         i = *idx;
    int         j;
    char        labelbuff[16];/* for anonymous labels */
	int         cnt;
    char        *p;
	char clabel[100];
	struct asym *labelsym;
	struct asym *labelsym2;
	struct asm_tok tok;

    DebugMsg1(("%u get_operand(idx=%u >%s<) enter [memtype=%Xh]\n", evallvl, i, tokenarray[i].tokpos, opnd->mem_type ));
    switch( tokenarray[i].token ) {
	case T_DOT:
		/* Allow .labelname to be used as an operand */
		if ((tokenarray[*idx].token == T_DOT && tokenarray[(*idx) + 1].token == T_ID))
		{
			// check that T_ID is a label
			sprintf(clabel, "%s%s", ".", tokenarray[(*idx) + 1].string_ptr);
			labelsym = SymFind(clabel);
			labelsym2 = SymFind(tokenarray[(*idx) + 1].string_ptr);

			if ((*idx) > 0)
			{
				tok = tokenarray[(*idx) - 1];
			}
			if (labelsym != NULL ||
				(labelsym == NULL && tok.token != T_ID && tok.token != T_CL_SQ_BRACKET && tok.token != T_CL_BRACKET) ||
				(labelsym != NULL && labelsym->label))
			{
				(*idx)++;
				strcpy(clabel, tokenarray[(*idx)].string_ptr);
				sprintf(tokenarray[(*idx)].string_ptr, "%s%s", ".", &clabel);
			}
			else if (labelsym == NULL && labelsym2 == NULL)
			{

			}
			i++;
			goto isNowID;
		}
    case T_NUM:
        DebugMsg1(("%u get_operand: T_NUM, %s, base=%u, len=%u\n", evallvl, tokenarray[i].string_ptr, tokenarray[i].numbase, tokenarray[i].itemlen ));
        opnd->kind = EXPR_CONST;
        myatoi128( tokenarray[i].string_ptr, &opnd->llvalue, tokenarray[i].numbase, tokenarray[i].itemlen );
        //opnd->llvalue = tokenarray[i].value64;
        //opnd->hlvalue = ( tokenarray[i].numflg == NF_NULL ? 0 : *(uint_64 *)( tokenarray[i].string_ptr - sizeof(uint_64) ) );
        break;
    case T_STRING:
        DebugMsg1(("%u get_operand: T_STRING, %s, size=%u\n", evallvl, tokenarray[i].string_ptr, tokenarray[i].stringlen ));
        /* string enclosed in <> or {} are rejected since v1.94! */
		if (tokenarray[i].string_delim != '"' && tokenarray[i].string_delim != '\'') {
			/* here is handled EVEX Static Rounding Mode
			* {sae},   {rn-sae},{rd-sae},{ru-sae} {rz-sae}
			* ZLLBVAAA ZLLBVAAA ZLLBVAAA ZLLBVAAA ZLLBVAAA
			* 00010000 00010000 00110000 01010000 01110000
			* to destinguish between SAE and RN  I added 0x10
			* to all 4 other decorators
			* which will be subtracted in codegen.c
			*/
			/* optimized and alowed white space after '{' and before '}', v2.38 */
			if (tokenarray[i].string_delim == '{' && evex) {
				p = tokenarray[i].string_ptr;
				while (isspace(*p)) p++;           /* skip white spaces*/
				if (memcmp(p, "rn-sae", 6) == 0) {
					opnd->kind = EXPR_DECORATOR;
					opnd->saeflags = 0x20;
					break;
				}
				else if (memcmp(p, "rd-sae", 6) == 0) {
					opnd->kind = EXPR_DECORATOR;
					opnd->saeflags = 0x40;
					break;
				}
				else if (memcmp(p, "ru-sae", 6) == 0) {
					opnd->kind = EXPR_DECORATOR;
					opnd->saeflags = 0x60;
					break;
				}
				else if (memcmp(p, "rz-sae", 6) == 0) {
					opnd->kind = EXPR_DECORATOR;
					opnd->saeflags = 0x80;
					break;
				}
				else if (memcmp(p, "sae", 3) == 0) {
					opnd->kind = EXPR_DECORATOR;
					opnd->saeflags = 0x10;
					break;
				}
				//EmitError(UNAUTHORISED_USE_OF_EVEX_ENCODING);
			}
			else if (opnd->is_opattr) /* OPATTR operator accepts anything! */
				break;
			/* v2.0: display a comprehensible error msg if a quote is missing */
			if (tokenarray[i].string_delim == NULLC &&
				(*tokenarray[i].string_ptr == '"' || *tokenarray[i].string_ptr == '\''))
				fnEmitErr(MISSING_QUOTATION_MARK_IN_STRING);
			else
				fnEmitErr(MISSING_QUOTATION_MARK_IN_STRING, tokenarray[i].tokpos);
			return(ERROR);
		}
        opnd->kind = EXPR_CONST;
        opnd->quoted_string = &tokenarray[i];
        //opnd->value = 0;
        tmp = tokenarray[i].string_ptr + 1; /* skip the quote */

        /* v2.06: use max. 16 bytes to create the "value".
         * Prior to 2.06, max 8 bytes were used for 64-bit and
         * max 4 bytes were used for 16-/32-bit.
         */
        j = ( tokenarray[i].stringlen > sizeof( opnd->chararray ) ? sizeof( opnd->chararray ) : tokenarray[i].stringlen );
        for( ; j; j-- )
            opnd->chararray[j-1] = *tmp++;
        break;
    case T_REG:
        DebugMsg1(( "%u get_operand: T_REG, string=%s, tokval=%u, regno=%u\n", evallvl, tokenarray[i].string_ptr, tokenarray[i].tokval, tokenarray[i].bytval ));        
        opnd->kind = EXPR_REG;
        opnd->base_reg = &tokenarray[i];
        j = tokenarray[i].tokval;
        
        /* check if cpu is sufficient for register */
        if( ( ( GetCpuSp( j ) & P_EXT_MASK ) &&
             (( GetCpuSp( j ) & ModuleInfo.curr_cpu & P_EXT_MASK) == 0) ||
             ( ModuleInfo.curr_cpu & P_CPU_MASK ) < ( GetCpuSp( j ) & P_CPU_MASK ) ) ) {
            /* v2.11: do not exit in indirect mode; avoids additional syntax error caused by ']' */
            if ( flags & EXPF_IN_SQBR ) {
                opnd->kind = EXPR_ERROR;
                fnEmitErr( INSTRUCTION_OR_REGISTER_NOT_ACCEPTED_IN_CURRENT_CPU_MODE );
            } else
                return( fnEmitErr( INSTRUCTION_OR_REGISTER_NOT_ACCEPTED_IN_CURRENT_CPU_MODE ) );
        }

		if ((i > 0 && tokenarray[i - 1].tokval == T_TYPE) ||
			(i > 1 && tokenarray[i - 1].token == T_OP_BRACKET
				&& tokenarray[i - 2].tokval == T_TYPE))
			; /* v2.26 [reg + type reg] | [reg + type(reg)] */

		else if (flags & EXPF_IN_SQBR) {
        //if( flags & EXPF_IN_SQBR && (i == 0 || tokenarray[i - 1].tokval != T_TYPE) ) 
		//{
            /* a valid index register? */
            if ( GetSflagsSp( j ) & SFR_IREG ) {
                opnd->indirect = TRUE;
                opnd->assumecheck = TRUE;
            } else if ( GetValueSp( j ) & OP_SR ) {
                /* a segment register inside square brackets is only
                 * accepted by Masm if it is the segment part of an
                 * address (mov ax,[bx+cs:label])!
                 */
                /* v2.10: check moved here avain. regression v2.08-2.09, where
                 * it was in colon_op(). see regression test OVERRID3.ASC.
                 */
                //if( tokenarray[i+1].token != T_COLON ) {
                if( tokenarray[i+1].token != T_COLON ||
                   ( Options.strict_masm_compat && tokenarray[i+2].token == T_REG ) ) {
                    return( fnEmitErr( INVALID_USE_OF_REGISTER ) );
                }
            } else {
                if ( opnd->is_opattr ) /* v2.11: just set error for opattr */
                    opnd->kind = EXPR_ERROR;
                else
                  opnd->indirect = TRUE;
                    //return( fnEmitErr( MUST_BE_INDEX_OR_BASE_REGISTER ) );
            }
        }
        break;
    case T_ID:
		isNowID:
        tmp = tokenarray[i].string_ptr;
        //if ( opnd->type ) { /* v2.11 */
        if ( opnd->is_dot ) {
            DebugMsg1(("%u get_operand: T_ID, is_dot=1, id=%s, opnd.type=%s\n", evallvl, tokenarray[i].string_ptr, opnd->type ? opnd->type->name : "NULL" ));
            //__debugbreak();
            opnd->value = 0;
            sym = ( opnd->type ? SearchNameInStruct( opnd->type, tmp, &opnd->uvalue, 0 ) : NULL );
            DebugMsg1(("get_operand(%s): is_dot, sym=%s, offset=%" I32_SPEC "Xh\n",
                       tmp, sym ? sym->name : "NULL", opnd->uvalue ));
            if ( sym == NULL ) {
                sym = SymSearch( tmp );
                if ( sym ) {
                    /*
                     * skip a type specifier matching the data item's type
                     * that's something like "<item>.<type>.<member>"
                     */
                    if ( sym->state == SYM_TYPE ) {
                        /*
                         * v2.07: "if" added.
                         * Masm accepts a different type spec if the "assumed"
                         * type is undefined
                         * v2.09: the change in v2.07 is a regression. if it's a type,
                         * then "usually" assume a type coercion and "switch" to the
                         * new type - but not for register assume. This isn't fixed
                         * yet, because there's no way to find out if a register assume
                         * did set field 'type'.
                         * v2.09: oldstructs condition added, see regression test dotop4.asm.
                         * v2.11: fixme? opnd->type may be NULL here?
                         * v2.12: for opnd->type==NULL test case, see expr5.aso.
                         */
                        //if ( sym == opnd->type || opnd->type->isdefined == FALSE )
                        //if ( sym == opnd->type || opnd->type->isdefined == FALSE || ModuleInfo.oldstructs )
                        if ( sym == opnd->type || ( opnd->type && opnd->type->isdefined == FALSE ) || ModuleInfo.oldstructs )
                            ; //opnd->sym = sym;
                        else {
                            sym = NULL;
                        }
                    } else if ( ModuleInfo.oldstructs &&
                               ( sym->state == SYM_STRUCT_FIELD ||
                                sym->state == SYM_EXTERNAL || /* v2.01: added */
                                /* v2.05: changed */
                                //( sym->state == SYM_INTERNAL && sym->mem_type == MT_ABS ) ) )
                                sym->state == SYM_INTERNAL ) )
                        //opnd->sym = sym;
                        ;
                    else {
                        /* fixme: clear sym?
                         * if the symbol is not a type, it's an error which can
                         * be detected in pass 1 already. dot_op() will emit
                         * 'struct field expected' if sym isn't cleared.
                         * v2.11: always clear sym.
                         */
                        //if ( opnd->type != nullstruct )
                        sym = NULL;
                    }
                }
            }
        } else {
            DebugMsg1(("%u get_operand: T_ID, id=%s\n", evallvl, tokenarray[i].string_ptr ));
            /* ensure anonym labels are uppercase */
            /* v2.06: changed. Previously member 'string_ptr' was used to
             * store the anonymous label, but one cannot safely assume that
             * there's enough free space for a larger symbol name! It (partly)
             * worked by accident, because @F/@B usually are the last tokens
             * in a line [ but see: .if ( eax == @F && ecx == 2 ) ].
             */
            if ( *tmp == '@' && *(tmp+2 ) == NULLC ) {
                if ( *(tmp+1) == 'b' || *(tmp+1 ) == 'B' )
                    tmp = GetAnonymousLabel( labelbuff, 0 );
                else if (*(tmp+1) == 'f' || *(tmp+1 ) == 'F' )
                    tmp = GetAnonymousLabel( labelbuff, 1 );
            }
            sym = SymSearch( tmp );
        }
        if ( sym == NULL ||
            sym->state == SYM_UNDEFINED ||
            ( sym->state == SYM_TYPE && sym->typekind == TYPE_NONE ) ||  /* v2.10: added */
#if ALIAS_IN_EXPR == 0
            sym->state == SYM_ALIAS || /* v2.04: added */
#endif
            sym->state == SYM_MACRO ||
            sym->state == SYM_TMACRO ) {

            /* for OPATTR, anything is ok */
            if ( opnd->is_opattr ) {
                DebugMsg1(( "get_operand(%s): OPATTR, symbol invalid\n", tokenarray[i].string_ptr ));
                opnd->kind = EXPR_ERROR;
                break;
            }
#if 0 /* v2.10: obsolete, since fnEmitErr() won't display anything in "EQU" mode */
            /* if it is EQU, don't display an error, but return ERROR */
            if ( flags & EXPF_NOERRMSG ) {
                DebugMsg1(("get_operand(%s): EQU, symbol invalid\n", tokenarray[i].string_ptr));
                return( ERROR );
            }
#endif
            if ( sym && ( sym->state == SYM_MACRO ||
#if ALIAS_IN_EXPR == 0
                         sym->state == SYM_ALIAS || /* v2.04: added */
#endif
                         sym->state == SYM_TMACRO ) ) {
                DebugMsg1(("get_operand(%s): symbol is macro/textmacro/alias!\n", tokenarray[i].string_ptr));
                fnEmitErr( INVALID_SYMBOL_TYPE_IN_EXPRESSION, sym->name );
                return( ERROR );
            }
            /* v2.11: flag EXPF_NOUNDEF won't accept undefined symbols anymore.
             * previously, it did just avoid to create a label with state SYM_UNDEFINED -
             * hence the old name, EXPF_NOLCREATE
             */
            //if( Parse_Pass == PASS_1 ) {
            if( Parse_Pass == PASS_1 && !( flags & EXPF_NOUNDEF ) ) {
                /* if symbol wasn't found, assume it is a forward ref! */
                if ( sym == NULL ) {
                    /* v2.11: flag EXPF_NOLCREATE has got another meaning */
                    //if ( opnd->type == NULL && !( flags & EXPF_NOLCREATE ) ) { /* added v1.95 */
                    if ( opnd->type == NULL ) {
                        sym = SymLookup( tmp );
                        sym->state = SYM_UNDEFINED;
                        sym_add_table( &SymTables[TAB_UNDEF], (struct dsym *)sym ); /* add UNDEFINED */
                        DebugMsg1(("get_operand(%s): symbol not (yet) defined, CurrProc=%s\n", tmp, CurrProc ? CurrProc->sym.name : "NULL" ));
                    
                    // } else if ( opnd->type == NULL || opnd->type != nullstruct ) { /* v2.08: if changed */
                    // } else if ( opnd->type == NULL || opnd->type->typekind != TYPE_NONE ) { /* v2.11: if changed */
                    } else if ( opnd->type->typekind != TYPE_NONE ) {
                        /* no struct or struct is known and defined */
                        DebugMsg(("get_operand(%s): symbol error (type=%s typekind=%u)\n", tmp, opnd->type ? opnd->type->name : "NULL", opnd->type ? opnd->type->typekind : 0 ));
                        if ( *opnd->type->name )
                            fnEmitErr( MEMBER_NOT_DEFINED, opnd->type->name, tmp );
                        else
                            fnEmitErr( SYMBOL_NOT_DEFINED, tmp );
                        return( ERROR );
                    } else {
                        /* forward reference to a struct.
                         * In these cases, assume everything is ok.
                         */
                        if ( !nullmbr ) {
                            nullmbr = SymAlloc( "" );
                        }
                        DebugMsg(("get_operand(%s): forward reference to a struct (using nullmbr)\n", tmp ));
                        /* "break" because nullmbr has state SYM_UNDEFINED */
                        opnd->mbr = nullmbr;
                        opnd->kind = EXPR_CONST;
                        break;
                    }
                }
            } else {
                DebugMsg1(("get_operand(%s): symbol %s not defined, pass > 1, curr proc=>%s<, \n", tokenarray[i].string_ptr, tmp, CurrProc ? CurrProc->sym.name : "NULL" ));
                if ( opnd->type && *opnd->type->name ) {
                    fnEmitErr( MEMBER_NOT_DEFINED, opnd->type->name, tmp );
                } else {
                    fnEmitErr( SYMBOL_NOT_DEFINED, *(tmp+1) == '&' ? "@@" : tmp );
                }
                return( ERROR );
            }
#if ALIAS_IN_EXPR /* v2.04b: added */
        } else if ( sym->state == SYM_ALIAS ) {
            /* ALIAS symbols are not really useable in expressions.
             * The alias' substitute symbol is, however.
             */
            sym = sym->substitute; /* can't be NULL */
#endif
        }
        /* set default values */
        sym->used = TRUE;
        DebugMsg1(("get_operand(%s): sym->state=%u type=>%s< ofs=%X memtype=%Xh total_size=%u defined=%u\n",
                tokenarray[i].string_ptr, sym->state, sym->type ? sym->type->name : "NULL", sym->offset, sym->mem_type, sym->total_size, sym->isdefined ));
        switch ( sym->state ) {
        case SYM_TYPE: /* STRUCT, UNION, RECORD, TYPEDEF */
            /* v2.09: no structinfo data for typedefs */
            if ( sym->typekind != TYPE_TYPEDEF && ((struct dsym *)sym)->e.structinfo->isOpen ) {
                DebugMsg1(("get_operand(%s): struct/union definition isn't closed!\n", sym->name ));
                opnd->kind = EXPR_ERROR;
                break;
            }
            /* skip "alias" types */
            for ( ; sym->type; sym = sym->type );
            opnd->kind = EXPR_CONST;
            opnd->mem_type = sym->mem_type;
            opnd->is_type = TRUE;
            opnd->type = sym;
            DebugMsg1(("get_operand(%s): symbol.typekind=%u (STRUCT/UNION/TYPEDEF/RECORD)\n", sym->name, sym->typekind ));

            /* v2.08: if() removed. This was an old hack. */
            //if ( tokenarray[i-1].token != T_DOT && tokenarray[i+1].token != T_DOT )
            /* v2.06: the default value for RECORD types is the mask value */
            if ( sym->typekind == TYPE_RECORD ) {
#if AMD64_SUPPORT
                opnd->llvalue = GetRecordMask( (struct dsym *)sym );
#else
                opnd->value = GetRecordMask( (struct dsym *)sym );
#endif
            } else if ( ( sym->mem_type & MT_SPECIAL_MASK ) == MT_ADDRESS ) { /* v2.09: added */
                if ( sym->mem_type == MT_PROC ) {
                    opnd->value = sym->total_size;
                    opnd->Ofssize = sym->Ofssize;
                } else
                    opnd->value = GetTypeSize( sym->mem_type, sym->Ofssize );
            } else
                opnd->value = sym->total_size;

            break;
        case SYM_STRUCT_FIELD:
            DebugMsg1(("get_operand(%s): structure field, ofs=%Xh\n", sym->name, sym->offset ));

            /* opnd->value might have been set by SearchNameInStruct() already! */
            opnd->value += sym->offset;
            opnd->kind = EXPR_CONST;
            opnd->mbr = sym;
            /* skip "alias" types (probably obsolete by now!) */
            for ( ; sym->type; sym = sym->type );
            opnd->mem_type = sym->mem_type;
            /*
             * check if the member field is a type (struct or union).
             * If yes, set the <type> member!
             * this cannot be done in PrepareOp()
             */
            opnd->type = ( sym->state == SYM_TYPE && sym->typekind != TYPE_TYPEDEF ) ? sym : NULL;
            DebugMsg1(("get_operand: mem_type=%Xh type=%s\n", opnd->mem_type, opnd->type ? opnd->type->name : "NULL" ));
            break;
        default: /* SYM_INTERNAL, SYM_EXTERNAL, SYM_SEG, SYM_GRP, SYM_STACK */
            opnd->kind = EXPR_ADDR;
            /* call internal function (@Line, ... ) */
            if ( sym->predefined && sym->sfunc_ptr )
                sym->sfunc_ptr( sym, NULL );
            //if( opnd->sym->mem_type == MT_ABS ) {
            if( sym->state == SYM_INTERNAL && sym->segment == NULL ) {
                opnd->kind = EXPR_CONST;
                opnd->uvalue = sym->uvalue;
                opnd->hvalue = sym->value3264;
                DebugMsg1(("get_operand(%s): equate hval=%Xh, lval=%Xh\n", sym->name, opnd->hvalue, opnd->uvalue ));
                opnd->mem_type = sym->mem_type;
                /* don't set the symbol reference, it isn't a label */
            } else if( sym->state == SYM_EXTERNAL &&
                      sym->mem_type == MT_EMPTY &&
                      sym->iscomm == FALSE ) {
                /* type remains EXPR_ADDR, to force fixup creation */
                //opnd->mem_type = sym->mem_type; /* v2.10: unnecessary, init value IS MT_EMPTY */
                opnd->is_abs = TRUE;
                opnd->sym = sym;
            } else {
                opnd->label_tok = &tokenarray[i];

                /* a variable with arbitrary type? */
                /* v2.05: added check for MT_EMPTY */
                //if( opnd->sym->type ) { 
                if( sym->type && sym->type->mem_type != MT_EMPTY ) {
                    /* skip "alias" types */
                    /* v2.05: obsolete */
                    //for ( sym2 = opnd->sym; sym2->type; sym2 = sym2->type );
                    //opnd->mem_type = sym2->mem_type;
                    opnd->mem_type = sym->type->mem_type;
                } else {
                    opnd->mem_type = sym->mem_type;
                }
                /* since there is no fixup for auto variables, the "offset"
                 must be stored in the <value> field */
                if ( sym->state == SYM_STACK ) {
#if STACKBASESUPP
                  
                    if ((ModuleInfo.win64_flags & W64F_HABRAN) && sym->isparam){
                      opnd->llvalue = sym->offset;// +StackAdj;
                      cnt = CurrProc->e.procinfo->pushed_reg;
                      cnt = cnt * 8;
                      cnt += sym->offset + CurrProc->e.procinfo->localsize + CurrProc->e.procinfo->xmmsize; //pointing to RSP
                      if (CurrProc->sym.langtype == LANG_VECTORCALL)
                        cnt += CurrProc->e.procinfo->vsize ;     //pointing abowe RSP to the shadow space off RCX RDX R8 R9                      
                      //else 
                        cnt -= 8;
                        if ((cnt & 7) != 0) cnt = (cnt + 7)&(-8);
                      opnd->llvalue = cnt;
                    }
                    else 
                      opnd->llvalue = (int_64)(sym->offset + (int)StackAdj);
#else
                    opnd->llvalue = sym->offset;
#endif
                    opnd->indirect = TRUE;
                    /* v2.10: base register values now set here */
                    opnd->base_reg = &tokenarray[i];
#if STACKBASESUPP
                    tokenarray[i].tokval = CurrProc->e.procinfo->basereg;
#else
                    tokenarray[i].tokval = basereg[ModuleInfo.Ofssize];
#endif
                    tokenarray[i].bytval = GetRegNo( tokenarray[i].tokval );
                }
                opnd->sym = sym;
                /* v2.09: added (also see change in PrepareOp() )
                 * and see case SYM_STRUCT_FIELD.
                 */
                for ( ; sym->type; sym = sym->type );
                opnd->type = ( sym->state == SYM_TYPE && sym->typekind != TYPE_TYPEDEF ) ? sym : NULL;
            }
            break;
        }
        break;
    case T_STYPE:
        DebugMsg1(("%u get_operand: T_STYPE (>%s<, value=%X)\n", evallvl, tokenarray[i].string_ptr, tokenarray[i].tokval));
        opnd->kind = EXPR_CONST;
        /* for types, return the size as numeric constant */
        /* fixme: mem_type should be set only when used as first arg of PTR op! */
        opnd->mem_type = GetMemtypeSp( tokenarray[i].tokval );
        opnd->Ofssize = GetSflagsSp( tokenarray[i].tokval );
        opnd->value = GetTypeSize( opnd->mem_type, opnd->Ofssize );
        opnd->is_type = TRUE;
        opnd->type = NULL; /* v2.08: added */
        break;
    case T_RES_ID:
        DebugMsg1(("%u get_operand: T_RES_ID (>%s<, value=%X)\n", evallvl, tokenarray[i].string_ptr, tokenarray[i].tokval));
        if ( tokenarray[i].tokval == T_FLAT ) {
            /* v2.09: query NOUNDEF flag */
            //if ( error_msg ) { /* don't define FLAT group in EQU expression! */
            if ( ( flags & EXPF_NOUNDEF ) == 0 ) {
                /* v2.08 cpu check added */
                if( ( ModuleInfo.curr_cpu & P_CPU_MASK ) < P_386 ) {
                    fnEmitErr( INSTRUCTION_OR_REGISTER_NOT_ACCEPTED_IN_CURRENT_CPU_MODE );
                    return( ERROR );
                }
                DefineFlatGroup();
            }
            if ( !( opnd->sym = &ModuleInfo.flat_grp->sym ) )
                return( ERROR );

            opnd->label_tok = &tokenarray[i];
            opnd->kind = EXPR_ADDR;

        } else {
            return( fnEmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
        }
        break;
    case T_FLOAT: /* v2.05 */
        DebugMsg1(("%u get_operand: T_FLOAT (>%s<)\n", evallvl, tokenarray[i].string_ptr ));
        opnd->kind = EXPR_FLOAT;
        opnd->float_tok = &tokenarray[i];
        //opnd->ftype = ( tokenarray[i].floattype != 0 );
        break;
    //case T_CL_BRACKET:
    //case T_CL_SQ_BRACKET:
    default:
        DebugMsg1(("%u get_operand: default (token=%u, string=%s)\n", evallvl, tokenarray[i].token, tokenarray[i].string_ptr));
        if ( opnd->is_opattr ) {    /* for OPATTR, allow any operand */
            if ( tokenarray[i].token == T_FINAL ||
                tokenarray[i].token == T_CL_BRACKET ||
                tokenarray[i].token == T_CL_SQ_BRACKET ) /* don't go beyond T_FINAL, ) or ] ! */
                return( NOT_ERROR );
            break;
        }
        if ( tokenarray[i].token == T_BAD_NUM )
            /* Masm complains even if in EQU-mode */
            fnEmitErr( NONDIGIT_IN_NUMBER, tokenarray[i].string_ptr );
        else if ( tokenarray[i].token == T_COLON )
            fnEmitErr( SYNTAX_ERROR_UNEXPECTED_COLON );
        else if ( isalpha( *tokenarray[i].string_ptr ) )
            fnEmitErr( EXPRESSION_EXPECTED, tokenarray[i].tokpos ); /* better error msg */
        else
            fnEmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos );
        return( ERROR );
    }
    (*idx)++;
    DebugMsg1(("%u get_operand exit, ok, kind=%d value=%" I64_SPEC "X hvalue=%" I64_SPEC "X mem_type=%Xh abs=%u string=%s is_type=%u type=>%s< sym=%s mbr=%s\n",
               evallvl, opnd->kind, opnd->llvalue, opnd->hlvalue, opnd->mem_type, opnd->is_abs,
               opnd->quoted_string ? opnd->quoted_string->string_ptr : "NULL",
               opnd->is_type, opnd->type ? opnd->type->name : "NULL",
               opnd->sym ? opnd->sym->name : "NULL",
               opnd->mbr ? opnd->mbr->name : "NULL" ));
    return( NOT_ERROR );
}

#if 0
static bool check_same( struct expr *opnd1, struct expr *opnd2, enum exprtype kind )
/**********************************************************************************/
/* Check if both tok_1 and tok_2 equal type */
{
    return( ( opnd1->kind == kind && opnd2->kind == kind ) ? TRUE : FALSE );
}
#else
#define check_same( first, second, KIND ) ( first->kind == KIND && second->kind == KIND )
#endif

static bool check_both( const struct expr *opnd1, const struct expr *opnd2, enum exprtype type1, enum exprtype type2 )
/********************************************************************************************************************/
/* Check if tok_1 == type1 and tok_2 == type2 or vice versa */
{
    if( opnd1->kind == type1 && opnd2->kind == type2 )
        return( TRUE );
    if( opnd1->kind == type2 && opnd2->kind == type1 )
        return( TRUE );
    return( FALSE );
}

static ret_code index_connect( struct expr *opnd1, const struct expr *opnd2 )
/***************************************************************************/
/* Connects the register lists. called by plus_op() and dot_op() */
{
    /* move opnd2.base to either opnd1.base or opnd1.idx */
    if ( opnd2->base_reg != NULL ) {
        if ( opnd1->base_reg == NULL )
            opnd1->base_reg = opnd2->base_reg;
        else if ( opnd1->idx_reg == NULL ) {
            /* v2.10: exchange base and index register.
             * was previously in parser.c, and only done
             * if -Zg was active.
             */
            if ( opnd2->base_reg->bytval == 4 ) {   /* if opnd2->base_reg->bytval is [E|R]SP, exchange regs */
                opnd1->idx_reg = opnd1->base_reg;
                opnd1->base_reg = opnd2->base_reg;
            } else {
                opnd1->idx_reg = opnd2->base_reg;
            }
        } else {
            return( fnEmitErr( MULTIPLE_INDEX_REGISTERS_NOT_ALLOWED ) );
        }
        opnd1->indirect = TRUE;
    }
    /* move opnd2.idx to opnd1.index - if it is free */
    if( opnd2->idx_reg != NULL ) {
        //if ( opnd2->scale == 0 && opnd1->base_reg == NULL ) {
        //    opnd1->base_reg = opnd2->idx_reg;
        //} else if ( opnd1->idx_reg == NULL ) {
        if ( opnd1->idx_reg == NULL ) {
            opnd1->idx_reg = opnd2->idx_reg;
            opnd1->scale = opnd2->scale;
        } else {
            return( fnEmitErr( MULTIPLE_INDEX_REGISTERS_NOT_ALLOWED ) );
        }
        opnd1->indirect = TRUE;
    }
    return( NOT_ERROR );
}

/* convert an address operand to a const operand if possible.
 * called for '*', '/', '+', '-' and binary (EQ,NE, ... SHL, SHR, ... OR,AND,XOR) operators.
 * the main purpose is: if a forward reference is included,
 * assume it is referencing a constant, not a label.
 */

static void MakeConst( struct expr *opnd )
/****************************************/
{
    if( ( opnd->kind != EXPR_ADDR ) || opnd->indirect ) /* v2.09: check for indirect added */
        return;

    if( opnd->sym ) {
        if ( Parse_Pass > PASS_1 )
            return;
        /* added for v1.94: if the evaluator assumed an address because
         * the label wasn't defined yet, then negate this. Also, an
         * EXTERNDEF:ABS is to be accepted.
         * v2.07: if the "not yet defined" label was an argument of
         * an (OFFSET) operator, do NOT change the type!
         */
        if ( ( opnd->sym->state == SYM_UNDEFINED && opnd->instr == EMPTY ) ||
            ( opnd->sym->state == SYM_EXTERNAL && opnd->sym->weak == TRUE && opnd->is_abs == TRUE ) )
            ;
        else
            return;
        /* assume a value != 0 to avoid problems with div */
        opnd->value = 1;
    }

    opnd->label_tok = NULL;
    if( opnd->mbr != NULL ) {
        if( opnd->mbr->state == SYM_STRUCT_FIELD ) {
#if 0 /* v2.09: mbr can only be SYM_STRUCT_FIELD or SYM_UNDEFINED (if nullmbr) */
        } else if( opnd->mbr->state == SYM_TYPE ) {
            opnd->value += opnd->mbr->total_size;
            opnd->mbr = NULL;
#endif
        } else {
            return;
        }
    }
#if 0 /* v2.09: obsolete */
    if( opnd->base_reg != NULL )
        return;
    if( opnd->idx_reg  != NULL )
        return;
#endif
    if( opnd->override != NULL )
        return;
    opnd->instr = EMPTY;
    opnd->kind = EXPR_CONST;
    //opnd->indirect = FALSE; /* not needed */
    opnd->explicit = FALSE;
    opnd->mem_type = MT_EMPTY;
}

/* used by EQ, NE, GT, GE, LE, LT if item is a direct address
 */

static ret_code MakeConst2( struct expr *opnd1, struct expr *opnd2 )
/******************************************************************/
{

    if ( opnd1->sym->state == SYM_EXTERNAL ) {
        return( fnEmitErr( INVALID_USE_OF_EXTERNAL_SYMBOL, opnd1->sym->name ) );
    } else if ( ( opnd1->sym->segment != opnd2->sym->segment &&
                 /* v2.07: ignore segments if at least one label is a fwd ref */
                 opnd1->sym->state != SYM_UNDEFINED &&
                 opnd2->sym->state != SYM_UNDEFINED ) ||
               opnd2->sym->state == SYM_EXTERNAL ) {
        return( fnEmitErr( OPERANDS_MUST_BE_IN_SAME_SEGMENT ) );
    }
    opnd1->kind = EXPR_CONST;
    opnd1->value += opnd1->sym->offset;
    opnd2->kind = EXPR_CONST;
    opnd2->value += opnd2->sym->offset;
    return( NOT_ERROR );
}

static ret_code ConstError( struct expr *opnd1, struct expr *opnd2 )
/******************************************************************/
{
    if ( opnd1->is_opattr )
        return( NOT_ERROR );
    if ( opnd1->kind == EXPR_FLOAT || opnd2->kind == EXPR_FLOAT )
        fnEmitErr( REAL_OR_BCD_NUMBER_NOT_ALLOWED );
    else
        fnEmitErr( CONSTANT_EXPECTED );
    return( ERROR );
}

/* used by + and - binary operators */

static void fix_struct_value( struct expr *opnd )
/***********************************************/
{
    if( opnd->mbr && ( opnd->mbr->state == SYM_TYPE ) ) {
        opnd->value += opnd->mbr->total_size;
        opnd->mbr = NULL;
    }
}

static int check_direct_reg( const struct expr *opnd1, const struct expr *opnd2 )
/*******************************************************************************/
{
    if( ( opnd1->kind == EXPR_REG ) && ( opnd1->indirect == FALSE )
        || ( opnd2->kind == EXPR_REG ) && ( opnd2->indirect == FALSE ) ) {
        return( ERROR );
    }
    return( NOT_ERROR );
}

static unsigned GetSizeValue( struct asym *sym )
/**********************************************/
{
    if ( sym->mem_type == MT_PTR )
        return( SizeFromMemtype( sym->isfar ? MT_FAR : MT_NEAR, sym->Ofssize, sym->type ) );
    return( SizeFromMemtype( sym->mem_type, sym->Ofssize, sym->type ) );
}

static unsigned IsOffset( struct expr *opnd )
/*******************************************/
{
    if ( opnd->mem_type == MT_EMPTY )
        if ( opnd->instr == T_OFFSET ||
#if IMAGERELSUPP
            opnd->instr == T_IMAGEREL ||
#endif
#if SECTIONRELSUPP
            opnd->instr == T_SECTIONREL ||
#endif
            opnd->instr == T_LROFFSET )
            return( 1 );
    return( 0 );
}

static ret_code invalid_operand( struct expr *opnd, char *oprtr, char *operand )
/******************************************************************************/
{
    if ( !opnd->is_opattr )
        fnEmitErr( INVALID_OPERAND_FOR_OPERATOR, _strupr( oprtr), operand );
    return( ERROR );
}

/* operators
 * LENGTH:    number of items of first initializer's first dimension
 * SIZE:      size in bytes of first initializer's first dimension
 * LENGTHOF:  number of elements in an array
 * SIZEOF:    size in bytes of item (array/struct)
 *
 * these operators accept structure fields, stack variables and data labels.
 * the old SIZE and LENGTH ops also accept code labels (memtype NEAR/FAR).
 * in Masm, symbolic constants (defined with EQU or =) are
 * also accepted, but no plain numbers!?
 */

static ret_code sizlen_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
/*********************************************************************************************************/
{
    opnd1->kind = EXPR_CONST;

    DebugMsg1(("sizlen_op(%s): sym=%X, mbr=%X, type=>%s<\n", GetResWName( oper, NULL ),
               opnd2->sym, opnd2->mbr, opnd2->type ? opnd2->type->name : "NULL" ));

    if ( sym ) {
        if ( sym->state == SYM_STRUCT_FIELD || sym->state == SYM_STACK )
            ;
        else if ( sym->state == SYM_UNDEFINED ) {
            /* v2.10: forward references should have attributes EXPR_ADDR + sym.state=SYM_UNDEFINED */
            opnd1->kind = EXPR_ADDR;
            opnd1->sym = sym;
        } else if ( ( sym->state == SYM_EXTERNAL ||
                 sym->state == SYM_INTERNAL) &&
                 //sym->mem_type != MT_ABS &&
                 sym->mem_type != MT_EMPTY &&
                 //sym->mem_type != MT_PROC && /* MT_PROC probably obsolete */
                 sym->mem_type != MT_FAR &&
                 sym->mem_type != MT_NEAR )
            ;
        else if ( sym->state == SYM_GRP || sym->state == SYM_SEG ) {
            return( fnEmitErr( EXPECTED_DATA_LABEL ) );
        } else if ( oper == T_SIZE || oper == T_LENGTH )
            ;
        else {
            return( fnEmitErr( EXPECTED_DATA_LABEL ) );
        }
    }

    switch( oper ) {
    case T_LENGTH:
        /* data items and struct fields have a "first" count.
         * for procedure locals (+arguments) and code labels, always 1 is returned.
         */
        /* v2.09: first_length is valid if isdata is set */
        //opnd1->value = ( sym->state != SYM_STACK && sym->isarray ) ? sym->first_length : 1;
        opnd1->value = sym->isdata ? sym->first_length : 1;
        break;
    case T_LENGTHOF:
        /* LENGTHOF needs either a data label or a structure field */
        /* a TYPE (structure, typedef) is invalid */
        if( opnd2->kind == EXPR_CONST ) {
            opnd1->value = opnd2->mbr->total_length;
#if 0 /* v2.09: unnecessary */
        } else if( sym->state == SYM_UNDEFINED && Parse_Pass == PASS_1 ) {
            opnd1->value = sym->total_length;
#endif
        } else if ( sym->state == SYM_EXTERNAL && sym->iscomm == FALSE ) {
            /* for externals other than COMM, total_length field is used otherwise */
            opnd1->value = 1;
        } else {
            opnd1->value = sym->total_length;
        }
        break;
    case T_SIZE:
        /* v2.04: first_size is no longer set for SYM_STACK. */
        if( sym == NULL ) {
            /* v2.09: check memtype */
            if ( ( opnd2->mem_type & MT_SPECIAL_MASK ) == MT_ADDRESS )
                opnd1->value = 0xFF00 | opnd2->value;
            else
                opnd1->value = opnd2->value;
        } else if ( sym->isdata ) {
            opnd1->value = sym->first_size;
#if 0 /* v2.09: can't happen, since for a type, sym is NULL */
        } else if( sym->state == SYM_TYPE ) {
            opnd1->value = sym->total_size;
#endif
        } else if( sym->state == SYM_STACK ) {
            opnd1->value = GetSizeValue( sym );
        } else if( sym->mem_type == MT_NEAR ) {
            /* v2.09: also handle 64-bit */
            //opnd1->value = GetSymOfssize( sym ) ? LS_NEAR32 : LS_NEAR16;
            opnd1->value = 0xFF00 | ( 2 << GetSymOfssize( sym ) );
        } else if( sym->mem_type == MT_FAR ) {
            opnd1->value = GetSymOfssize( sym ) ? LS_FAR32 : LS_FAR16;
        } else {
            opnd1->value = GetSizeValue( sym );
        }
        DebugMsg1(("sizlen_op(SIZE): result=%u [symbol %s, first_size=%u]\n", opnd1->value, sym ? sym->name : "NULL", sym ? sym->first_size : 0 ));
        break;
    case T_SIZEOF:
#ifdef DEBUG_OUT
        if (sym)
            DebugMsg1(("sizlen_op(sizeof): symbol %s, state=%u, size=%u\n", sym->name, sym->state, sym->total_size ));
        else if ( opnd2->is_type && opnd2->type )
            DebugMsg1(("sizlen_op(sizeof): symbol %s (TYPE), opnd2.value=%u\n", opnd2->type->name, opnd2->value ));
        else
            DebugMsg1(("sizlen_op(sizeof): symbol NULL, opnd2.value=%u\n", opnd2->value ));
#endif
        /* if sym is NULL, then operand is a type constant */
        if ( sym == NULL ) {
            /* v2.06: default value of RECORD types is the mask! */
            if ( opnd2->is_type && opnd2->type && opnd2->type->typekind == TYPE_RECORD )
                opnd1->value = opnd2->type->total_size;
            else
                opnd1->value = opnd2->value;
#if 1 /* v2.05: don't use total_size for externals anymore! */
        } else if ( sym->state == SYM_EXTERNAL && sym->iscomm == FALSE ) {
            opnd1->value = GetSizeValue( sym );
            //if ( sym->iscomm == TRUE )
            //    opnd1->value *= sym->total_length;
#endif
        } else
            opnd1->value = sym->total_size;
        break;
    }
    return( NOT_ERROR );
}

/* TYPE operator */

static ret_code type_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
/*******************************************************************************************************/
{
    DebugMsg1(("type_op: opnd2 kind=%d memtype=%X sym=%s type=%s instr=%d istype=%u explicit=%u\n",
               opnd2->kind,
               opnd2->mem_type,
               sym ? sym->name : "NULL",
               opnd2->type ? opnd2->type->name : "NULL",
               opnd2->instr,
               opnd2->is_type,
               opnd2->explicit ));
    opnd1->kind = EXPR_CONST;
    /* TYPE accepts arrays/structs/unions */
    /* v2.11: if memtype isn't empty, ignore any unary operator
     * test cases:
     * - type qword ptr sym.
     * - type qword ptr offset sym
     * operators LOW, HIGH, LOWWORD, HIGHWORD, LOW32, HIGH32,
     * OFFSET, IMAGEREL, SECTIONREL and LROFFSET
     * will set opnd.memtype to MT_EMPTY.
     */
    if( opnd2->instr != EMPTY && opnd2->mem_type != MT_EMPTY ) {
        opnd2->instr = EMPTY;
        sym = NULL;
    }
    if( opnd2->instr != EMPTY ) {
        if ( opnd2->sym ) {
            switch ( opnd2->instr ) {
            case T_LOW:
            case T_HIGH:
                opnd1->value = 1;
                break;
            case T_LOWWORD:
            case T_HIGHWORD:
                //case T_SEG: /* masm returns 0 for TYPE SEG <label>! */
                opnd1->value = 2;
                break;
#if LOHI32
            case T_LOW32:
            case T_HIGH32:
                opnd1->value = 4;
                break;
#endif
            case T_OFFSET:
            case T_LROFFSET:
#if SECTIONRELSUPP
            case T_SECTIONREL: /* masm returns 0 for TYPE SECTIONREL <label>! */
#endif
#if IMAGERELSUPP
            case T_IMAGEREL: /* masm returns 0 for TYPE IMAGEREL <label>! */
#endif
                opnd1->value = 2 << GetSymOfssize( opnd2->sym );
                opnd1->is_type = TRUE; /* v2.03: added */
                break;
            }
        }
    } else if ( sym == NULL ) {
        //printf( "sym=NULL kind=%d mem_type=%X indirect=%u is_type=%u type=%s\n", opnd2->kind, opnd2->mem_type, opnd2->indirect, opnd2->is_type, opnd2->type ? opnd2->type->name : "NULL" );
        /* for types, return total_size */
        if ( opnd2->is_type == TRUE ) {
            /* v2.06: default value of RECORD types is the mask! */
            if ( opnd2->type && opnd2->type->typekind == TYPE_RECORD )
                opnd2->value = opnd2->type->total_size;
            //opnd1->value = opnd2->value;
            TokenAssign( opnd1, opnd2 );
            /* v2.05: added, (type procptr) ptr <reg>
             * the type probably should be set generally,
             * but this variant is the one used by INVOKE, other
             * usages are virtually irrelevant.
             * v2.10: opnd1->type now always set. Example:
             *   ( type x ) eq ( type y )
             * also see new function cmp_types()
             */
            //if ( opnd2->mem_type == MT_PROC )
            opnd1->type = opnd2->type;

        } else if ( opnd2->kind == EXPR_REG && opnd2->indirect == FALSE ) {
            opnd1->value = SizeFromRegister( opnd2->base_reg->tokval );
            opnd1->is_type = TRUE; /* v2.03: added */
            /* v2.10: check for assumes if it's a full size GPR */
            if ( opnd1->value == CurrWordSize &&
                opnd1->mem_type == MT_EMPTY &&
                ( GetValueSp( opnd2->base_reg->tokval ) & OP_RGT8 ) &&
                ( sym = GetStdAssumeEx( opnd2->base_reg->bytval ) ) ) {
                DebugMsg1(("type_op: assume type=%X [name=>%s< memtype=%X]\n", sym, sym->name, sym->mem_type ));
                opnd1->type = sym;
                opnd1->mem_type = sym->mem_type;
                opnd1->value = sym->total_size;
            } else {
                opnd1->mem_type = opnd2->mem_type; /* v2.10: added */
                opnd1->type = opnd2->type; /* v2.10: added */
                if ( opnd1->mem_type == MT_EMPTY )
                    MemtypeFromSize( opnd1->value, &opnd1->mem_type ); /* v2.03: added */
            }

#if 0 /* Masm returns 0 for TYPE <segment_register> */
            /* if it is a segment register, use default word size */
            if ( opnd1->value == 0 )
                opnd1->value = Use32 ? 4 : 2;
#endif
        //} else if ( opnd2->explicit ) { /* v2.05: changed */
        //} else if ( opnd2->mem_type != MT_EMPTY ) { /* v2.10: changed */
        } else if ( opnd2->mem_type != MT_EMPTY || opnd2->explicit ) {
            if ( opnd2->mem_type != MT_EMPTY ) {
                opnd1->value = SizeFromMemtype( opnd2->mem_type, opnd2->Ofssize, opnd2->type );
                opnd1->mem_type = opnd2->mem_type; /* v2.04: added */
            } else {
                if ( opnd2->type ) {
                    opnd1->value = opnd2->type->total_size;
                    opnd1->mem_type = opnd2->type->mem_type;
                }
            }
            opnd1->is_type = TRUE; /* v2.04: added */
            opnd1->type = opnd2->type; /* v2.09: added */
        } else /* it is a number or EXPR_REG + indirect */
            opnd1->value = 0;
#if 0
    } else if ( sym->state == SYM_TYPE ) {
        TokenAssign( opnd1, opnd2 );
        opnd1->type = sym;
#endif
    } else if ( sym->state == SYM_UNDEFINED ) { /* v2.10: added */
        opnd1->kind = EXPR_ADDR;
        opnd1->sym = sym;
        /* is_type must be set, to avoid the forward referenced symbol be changed
         * to a type if the type expression is the left operand of PTR
         */
        opnd1->is_type = TRUE;
        //} else if( sym->mem_type == MT_TYPE ) { /* v2.04: check for explicit */
    } else if( sym->mem_type == MT_TYPE && opnd2->explicit == FALSE ) {
        opnd1->value = sym->type->total_size;
        opnd1->is_type = TRUE; /* v2.03: added */
        //if ( opnd1->mem_type == MT_EMPTY ) /* v2.09 */
        opnd1->mem_type = sym->type->mem_type; /* v2.09 */
        opnd1->type = sym->type; /* v2.09 */
        //printf( "sym=%s MT_TYPE type=%s type->memt=%X\n", sym->name, sym->type->name, sym->type->mem_type );
    } else {
#if 1 /* v2.03: added */
        opnd1->is_type = TRUE;
        if ( opnd1->mem_type == MT_EMPTY )
            opnd1->mem_type = opnd2->mem_type;
#endif
        //if ( opnd2->type ) { /* v2.10a: see types14.asm */
        if ( opnd2->type && opnd2->mbr == NULL ) {
            opnd1->type_tok = opnd2->type_tok;
            opnd1->type = opnd2->type;
            opnd1->value = opnd1->type->total_size;
        } else if ( sym->mem_type == MT_PTR ) {
            //printf( "sym=%s MT_PTR target_memt=%X target=%s\n", sym->name, sym->ptr_memtype, sym->target_type ? sym->target_type->name : "NULL" );
            opnd1->type_tok = opnd2->type_tok; /* v2.10: added */
            opnd1->value = SizeFromMemtype( sym->isfar ? MT_FAR : MT_NEAR, sym->Ofssize, NULL );
        } else if( sym->mem_type == MT_NEAR ) {
            /* v2.09: also handle 64-bit */
            //opnd1->value = GetSymOfssize( sym ) ? LS_NEAR32 : LS_NEAR16;
            opnd1->value = 0xFF00 | ( 2 << GetSymOfssize( sym ) );
        } else if( sym->mem_type == MT_FAR ) {
            opnd1->value = GetSymOfssize( sym ) ? LS_FAR32 : LS_FAR16;
        } else
            opnd1->value = SizeFromMemtype( opnd2->mem_type, GetSymOfssize( sym ), sym->type );
    }
    DebugMsg1(("type_op: result value=%u is_type=%u type=%s\n", opnd1->value, opnd1->is_type, opnd1->type ? opnd1->type->name : "NULL" ));
    return( NOT_ERROR );
}

/* v2.08: changed plain hex numbers to enum */
enum opattr_bits {
    OPATTR_CODELABEL = 0x01,
    OPATTR_DATALABEL = 0x02,  /* memory variable, has relocatable data label */
    OPATTR_IMMEDIATE = 0x04,  /* immediate value */
    OPATTR_DIRECTMEM = 0x08,  /* uses direct memory addressing */
    OPATTR_REGISTER  = 0x10,  /* is a register value */
    OPATTR_DEFINED   = 0x20,  /* no reference to undefined label */
    OPATTR_SSREL     = 0x40,  /* is relative to SS */
    OPATTR_EXTRNREF  = 0x80,  /* references external label */
    OPATTR_LANG_MASK = 0x700,
};

/*
 * T_DOT_TYPE: implement .TYPE as an alias for OPATTR
 * T_OPATTR:
 */
static ret_code opattr_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
/*********************************************************************************************************/
{

    DebugMsg1(("opattr_op: arg kind=%d memtype=%X sym=%s\n",
               opnd2->kind, opnd2->mem_type,
               opnd2->sym ? opnd2->sym->name : "NULL" ));
    opnd1->kind = EXPR_CONST;
    opnd1->sym = NULL;  /* clear symbol in case it is undef */
    opnd1->value = 0;
    opnd1->mem_type = MT_EMPTY;
    opnd1->is_opattr = FALSE; /* v2: added */

    if ( opnd2->kind == EXPR_EMPTY )
        return( NOT_ERROR );

    /* bit 0: code label (near|far)? */
    if ( opnd2->kind == EXPR_ADDR ) {
        if ( opnd2->sym && opnd2->sym->state != SYM_STACK &&
            ( opnd2->mem_type & MT_SPECIAL_MASK ) == MT_ADDRESS )
            opnd1->value |= OPATTR_CODELABEL;

        if ( IsOffset( opnd2 ) &&
            opnd2->sym &&
            ( opnd2->sym->mem_type & MT_SPECIAL_MASK ) == MT_ADDRESS )
            opnd1->value |= OPATTR_CODELABEL;

        /* bit 1: memory variable, relocatable data label? */
        if ( opnd2->sym &&
            (( opnd2->sym->mem_type == MT_TYPE ||
              ( opnd2->mem_type & MT_SPECIAL ) == 0 ) ||
             ( opnd2->mem_type == MT_EMPTY &&
              ( opnd2->sym->mem_type & MT_SPECIAL ) == 0 )))
            opnd1->value |= OPATTR_DATALABEL;
    }
    /* kind==EXPR_ADDR is not reliably set for indirect register addressing! */
    /* v2.12: check if operand is valid */
    //if ( opnd2->indirect )
    if ( opnd2->kind != EXPR_ERROR && opnd2->indirect )
        opnd1->value |= OPATTR_DATALABEL;


    /* bit 2: immediate value? */
	/* John Hankinson modified here to allow -Zne switch to treat literal string macro argument with opattr type = 0 */
	if (Options.strict_masm_compat && opnd2->kind == EXPR_CONST && opnd2->mem_type != MT_SQWORD && opnd2->quoted_string != NULL)
	{
	}
    else if ( opnd2->kind == EXPR_CONST ||
        ( opnd2->kind == EXPR_ADDR &&
         opnd2->indirect == FALSE &&
         (( opnd2->mem_type == MT_EMPTY && IsOffset(opnd2) ) ||
          //( opnd2->mem_type == MT_ABS ) ||  /* v2.06: added (abs. external) */
          ( opnd2->mem_type == MT_EMPTY ) ||  /* v2.06: added (abs. external) */
          (( opnd2->mem_type & MT_SPECIAL_MASK ) == MT_ADDRESS )) &&
         ( opnd2->sym->state == SYM_INTERNAL ||
          opnd2->sym->state == SYM_EXTERNAL ) ) )
        opnd1->value |= OPATTR_IMMEDIATE;

    /* bit 3: uses direct memory addressing?
     */
    if ( opnd2->kind == EXPR_ADDR &&
        opnd2->indirect == FALSE &&
        //opnd2->base_reg == NULL &&
        (( opnd2->mem_type == MT_EMPTY && opnd2->instr == EMPTY ) ||
         ( opnd2->mem_type == MT_TYPE ) || /* v2.05: added */
         (( opnd2->mem_type & MT_SPECIAL ) == 0 ) ||
         opnd2->mem_type == MT_PTR ) &&
        (opnd2->sym == NULL ||
         opnd2->sym->state == SYM_INTERNAL ||
         opnd2->sym->state == SYM_EXTERNAL ) )
        opnd1->value |= OPATTR_DIRECTMEM;

    if ( opnd2->kind == EXPR_REG && opnd2->indirect == FALSE )
        opnd1->value |= OPATTR_REGISTER;

    //if ( opnd2->kind != EXPR_ERROR && ( opnd2->sym == 0 || opnd2->sym->isdefined == TRUE ) )
	/* John Hankinson modified here to allow -Zne switch to treat literal string macro argument with opattr type = 0 */
	if (Options.strict_masm_compat && opnd2->kind == EXPR_CONST && opnd2->mem_type != MT_SQWORD && opnd2->quoted_string != NULL)
	{
	}
    else if ( opnd2->kind != EXPR_ERROR && opnd2->kind != EXPR_FLOAT && ( opnd2->sym == NULL || opnd2->sym->isdefined == TRUE ) )
        opnd1->value |= OPATTR_DEFINED; 

    if ( ( opnd2->sym && opnd2->sym->state == SYM_STACK ) ||
        ( opnd2->indirect && opnd2->base_reg &&
         /* v2.11: use new flag SFR_SSBASED */
         //( opnd2->base_reg->tokval == T_ESP || opnd2->base_reg->tokval == T_EBP || opnd2->base_reg->tokval == T_BP ) ) )
         ( GetSflagsSp( opnd2->base_reg->tokval ) & SFR_SSBASED ) ) )
            opnd1->value |= OPATTR_SSREL;
    
    if ( opnd2->sym && opnd2->sym->state == SYM_EXTERNAL )
        opnd1->value |= OPATTR_EXTRNREF;

    if ( oper == T_OPATTR )
        /* v2.12: no language if symbol isn't defined properly */
        //if ( opnd2->sym )
        if ( opnd2->sym && opnd2->kind != EXPR_ERROR )
            opnd1->value |= opnd2->sym->langtype << 8;

    DebugMsg1(("opattr_op returns %Xh\n", opnd1->value));
    return( NOT_ERROR );
}

static ret_code short_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
/********************************************************************************************************/
{
    if ( opnd2->kind != EXPR_ADDR ||
        ( opnd2->mem_type != MT_EMPTY &&
         opnd2->mem_type != MT_NEAR &&
         opnd2->mem_type != MT_FAR ) ) {
        return( fnEmitErr( EXPRESSION_MUST_BE_A_CODE_ADDRESS ) );
    }
    TokenAssign( opnd1, opnd2 );
    opnd1->instr = oper;
    return( NOT_ERROR );
}

static ret_code seg_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
/******************************************************************************************************/
{
    /* v2.10: check for sym==NULL ( seg ds:[0] ) added */
    if ( opnd2->sym == NULL || opnd2->sym->state == SYM_STACK || opnd2->is_abs ) {
        return( fnEmitErr( OPERAND_MUST_BE_RELOCATABLE ) );
    }
    TokenAssign( opnd1, opnd2 );
    opnd1->instr = oper;
    if ( opnd1->mbr ) /* v2.08: set value more selectively */
        opnd1->value = 0;    /* v2.07: added ( SEG <member> ) */
    opnd1->mem_type = MT_EMPTY; /* v2.04a */
    return( NOT_ERROR );
}

/*
 handles FRAMEOFS operator.
*/
static ret_code frameofs_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
	if ((sym && sym->state == SYM_GRP) || opnd2->instr == T_SEG) {
		return(invalid_operand(opnd2, GetResWName(oper, NULL), name));
	}

	/* if operand is a constant value, error */
	if (opnd2->kind == EXPR_CONST) {
		return(invalid_operand(opnd2, GetResWName(oper, NULL), name));
	}

	/* offset operator accepts types, but returns always 0 */
	if (opnd2->is_type)
		opnd2->value = 0;

	TokenAssign(opnd1, opnd2);
	opnd1->instr = oper;
	opnd1->base_reg = NULL;
	opnd1->override = NULL;
	opnd1->idx_reg = NULL;
	opnd1->mem_type = MT_EMPTY;
	opnd1->kind = EXPR_CONST;

	return(NOT_ERROR);
}

/*
handles ARGIDX operator.
*/
static ret_code argidx_op(int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name)
{
	int argNo = 1;
	bool argFound = FALSE;
	struct dsym* param = NULL;

	if (CurrProc == NULL)
	{
		EmitErr(ARGIDX_NOT_IN_PROC);
		return(invalid_operand(opnd2, GetResWName(oper, NULL), name));
	}

	if ((sym && sym->state == SYM_GRP) || opnd2->instr == T_SEG) {
		return(invalid_operand(opnd2, GetResWName(oper, NULL), name));
	}

	/* if operand is a constant value or register, error */
	if (opnd2->kind == EXPR_CONST) {
		return(invalid_operand(opnd2, GetResWName(oper, NULL), name));
	}
	if (opnd2->kind == EXPR_REG) {
		return(invalid_operand(opnd2, GetResWName(oper, NULL), name));
	}

	/* argidx operator accepts types, but returns always 0 */
	if (opnd2->is_type)
		opnd2->value = 0;

	/* Scan current proc parameters to find a match */
	param = CurrProc->e.procinfo->paralist;
	while (param)
	{
		if (strcmp(opnd2->sym->name, param->sym.name) == 0)
		{
			argFound = TRUE;
			break;
		}
		argNo++;
		param = param->nextparam;
	}

	/* If parameter not found, return 0 */
	if (!argFound)
		opnd2->value = 0;

	opnd2->value = argNo;

	TokenAssign(opnd1, opnd2);
	opnd1->instr = oper;
	opnd1->base_reg = NULL;
	opnd1->override = NULL;
	opnd1->idx_reg = NULL;
	opnd1->mem_type = MT_EMPTY;
	opnd1->kind = EXPR_CONST;

	return(NOT_ERROR);
}

/*
handles ARGSIZE operator.
*/
static ret_code argsize_op(int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name)
{
	int argNo = 1;
	bool argFound = FALSE;
	struct dsym* param = NULL;

	if (CurrProc == NULL)
	{
		EmitErr(ARGSIZE_NOT_IN_PROC);
		return(invalid_operand(opnd2, GetResWName(oper, NULL), name));
	}

	if ((sym && sym->state == SYM_GRP) || opnd2->instr == T_SEG) {
		return(invalid_operand(opnd2, GetResWName(oper, NULL), name));
	}

	/* if operand is a constant value, error */
	if (opnd2->kind == EXPR_CONST) {
		return(invalid_operand(opnd2, GetResWName(oper, NULL), name));
	}
	if (opnd2->kind == EXPR_REG) {
		return(invalid_operand(opnd2, GetResWName(oper, NULL), name));
	}

	/* argidx operator accepts types, but returns always 0 */
	if (opnd2->is_type)
		opnd2->value = 0;

	/* Scan current proc parameters to find a match */
	param = CurrProc->e.procinfo->paralist;
	while (param)
	{
		if (strcmp(opnd2->sym->name, param->sym.name) == 0)
		{
			argFound = TRUE;
			break;
		}
		argNo++;
		param = param->nextparam;
	}

	/* If parameter not found, return 0 */
	if (!argFound)
		opnd2->value = 0;
	else
	{
		opnd2->value = param->sym.total_size;
	}

	TokenAssign(opnd1, opnd2);
	opnd1->instr = oper;
	opnd1->base_reg = NULL;
	opnd1->override = NULL;
	opnd1->idx_reg = NULL;
	opnd1->mem_type = MT_EMPTY;
	opnd1->kind = EXPR_CONST;

	return(NOT_ERROR);
}

/*
handles ARGTYPE operator.
*/
static ret_code argtype_op(int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name)
{
	int argNo = 1;
	bool argFound = FALSE;
	struct dsym* param = NULL;

	if (CurrProc == NULL)
	{
		EmitErr(ARGTYPE_NOT_IN_PROC);
		return(invalid_operand(opnd2, GetResWName(oper, NULL), name));
	}

	if ((sym && sym->state == SYM_GRP) || opnd2->instr == T_SEG) {
		return(invalid_operand(opnd2, GetResWName(oper, NULL), name));
	}

	/* if operand is a constant value, error */
	if (opnd2->kind == EXPR_CONST) {
		return(invalid_operand(opnd2, GetResWName(oper, NULL), name));
	}
	if (opnd2->kind == EXPR_REG) {
		return(invalid_operand(opnd2, GetResWName(oper, NULL), name));
	}

	/* argidx operator accepts types, but returns always 0 */
	if (opnd2->is_type)
		opnd2->value = 0;

	/* Scan current proc parameters to find a match */
	param = CurrProc->e.procinfo->paralist;
	while (param)
	{
		if (strcmp(opnd2->sym->name, param->sym.name) == 0)
		{
			argFound = TRUE;
			break;
		}
		argNo++;
		param = param->nextparam;
	}

	/* If parameter not found, return 0 */
	if (!argFound)
		opnd2->value = 0;
	else
	{
		opnd2->value = param->sym.mem_type;
	}

	TokenAssign(opnd1, opnd2);
	opnd1->instr = oper;
	opnd1->base_reg = NULL;
	opnd1->override = NULL;
	opnd1->idx_reg = NULL;
	opnd1->mem_type = MT_EMPTY;
	opnd1->kind = EXPR_CONST;

	return(NOT_ERROR);
}

/* handles offset operators:
 * OFFSET, LROFFSEG, IMAGEREL, SECTIONREL
 */

static ret_code offset_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
/*********************************************************************************************************/
{
    if ( oper == T_OFFSET ) {
        /* if operand is a constant value, skip OFFSET operator */
        if ( opnd2->kind == EXPR_CONST ) {
            TokenAssign( opnd1, opnd2 );
            return( NOT_ERROR );
        }
    }
    if ( (sym && sym->state == SYM_GRP) || opnd2->instr == T_SEG ) {
        return( invalid_operand( opnd2, GetResWName( oper, NULL ), name ) );
    }
    /* offset operator accepts types, but returns always 0 */
    if ( opnd2->is_type )
        opnd2->value = 0;

    TokenAssign( opnd1, opnd2 );
    opnd1->instr = oper;

    if ( opnd2->indirect ) {
        /* Masm v5.1 allows indirect operands, but Masm v6 with -Zm
         * won't accept it.
         */
        return( invalid_operand( opnd2, GetResWName( oper, NULL ), name ) );
    }
    /* skip memory type of operand, just address is needed */
    //opnd1->mem_type = MT_NEAR;
    opnd1->mem_type = MT_EMPTY;
    /* clear overrides ("offset SEG:xxx") */
    /* v2.01: override information is important for fixup creation!
     * the reason why it was cleared probably was to avoid creation
     * of a segment prefix. This case is now handled in the parser.
     */
    // opnd1->override = NULL;
    return( NOT_ERROR );
}

static ret_code lowword_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
/**********************************************************************************************************/
{
    TokenAssign( opnd1, opnd2 );
    if ( opnd2->kind == EXPR_ADDR && opnd2->instr != T_SEG ) {
        opnd1->instr = T_LOWWORD;
        //opnd1->mem_type = MT_WORD; /* v2.05 */
        opnd1->mem_type = MT_EMPTY;
    }
    opnd1->llvalue &= 0xffff;
    return( NOT_ERROR );
}

static ret_code highword_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
/***********************************************************************************************************/
{
    TokenAssign( opnd1, opnd2 );
    if ( opnd2->kind == EXPR_ADDR && opnd2->instr != T_SEG ) {
        opnd1->instr = T_HIGHWORD;
        //opnd1->mem_type = MT_WORD; /* v2.05 */
        opnd1->mem_type = MT_EMPTY;
    }
	opnd1->llvalue = (opnd1->value >> 16) & 0xFFFF; /* ASMC v2.14 (fix borrowed from nidud) */
    return( NOT_ERROR );
}

static ret_code low_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
/******************************************************************************************************/
{
    TokenAssign( opnd1, opnd2 );
    if ( opnd2->kind == EXPR_ADDR && opnd2->instr != T_SEG ) {
#if 0
        /* LOW works for OMF/BIN only */
        /* v2.07: don't check any format-specific rules in the
         * expression evaluator!
         */
        if ( Options.output_format != OFORMAT_OMF &&
            Options.output_format != OFORMAT_BIN && opnd2->sym ) {
            return( fnEmitErr( SYMBOL_TYPE_CONFLICT, opnd2->sym->name ) );
        }
#endif
        opnd1->instr = T_LOW;
        opnd1->mem_type = MT_EMPTY;
    }
    opnd1->llvalue &= 0xff;
    return( NOT_ERROR );
}

static ret_code high_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
/*******************************************************************************************************/
{
    TokenAssign( opnd1, opnd2 );
    if ( opnd2->kind == EXPR_ADDR && opnd2->instr != T_SEG ) {
        /* v2.07: don't check any format-specific rules in the
         * expression evaluator!
         */
#if 0
        if ( Options.output_format != OFORMAT_OMF &&
            Options.output_format != OFORMAT_BIN && opnd2->sym ) {
            return( fnEmitErr( SYMBOL_TYPE_CONFLICT, opnd2->sym->name ) );
        }
#endif
        opnd1->instr = T_HIGH;
        opnd1->mem_type = MT_EMPTY;
    }
    opnd1->value = opnd1->value >> 8;
    opnd1->llvalue &= 0xff;
    return( NOT_ERROR );
}

#if LOHI32

static ret_code low32_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
/********************************************************************************************************/
{
    /* v2.06: added support for double constants */
    if ( opnd2->kind == EXPR_FLOAT ) {
        if ( Options.strict_masm_compat )
            return( ConstError( opnd1, opnd2 ) );
        atofloat( &opnd2->llvalue, opnd2->float_tok->string_ptr, sizeof( opnd2->llvalue), opnd2->negative, opnd2->float_tok->floattype );
        opnd2->kind = EXPR_CONST;
        opnd2->float_tok = NULL;
    }
    TokenAssign( opnd1, opnd2 );
    if ( opnd2->kind == EXPR_ADDR && opnd2->instr != T_SEG ) {
        opnd1->instr = T_LOW32;
        //opnd1->mem_type = MT_DWORD; /* v2.10: changed - also see change in parser.c, idata_fixup() */
        opnd1->mem_type = MT_EMPTY;
    }
    opnd1->llvalue &= 0xffffffff;
    return( NOT_ERROR );
}

static ret_code high32_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
/*********************************************************************************************************/
{
    /* v2.06: added support for double constants */
    if ( opnd2->kind == EXPR_FLOAT ) {
        if ( Options.strict_masm_compat )
            return( ConstError( opnd1, opnd2 ) );
        atofloat( &opnd2->llvalue, opnd2->float_tok->string_ptr, sizeof( opnd2->llvalue), opnd2->negative, opnd2->float_tok->floattype );
        opnd2->kind = EXPR_CONST;
        opnd2->float_tok = NULL;
    }
    TokenAssign( opnd1, opnd2 );
    if ( opnd2->kind == EXPR_ADDR && opnd2->instr != T_SEG ) {
        opnd1->instr = T_HIGH32;
        //opnd1->mem_type = MT_DWORD; /* v2.10: changed - also see change in parser.c, idata_fixup() */
        opnd1->mem_type = MT_EMPTY;
    }
    opnd1->llvalue = opnd1->llvalue >> 32;
    return( NOT_ERROR );
}

#endif

static ret_code this_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
/*******************************************************************************************************/
{
    if ( opnd2->is_type == FALSE ) {
        return( fnEmitErr( INVALID_TYPE_EXPRESSION ) );
    }
    /* v2.06: won't work inside structs */
    if ( CurrStruct ) {
        return( fnEmitErr( MUST_BE_IN_SEGMENT_BLOCK ) );
    }
    /* v2.06: won't work outside segments */
    if ( CurrSeg == NULL ) {
        return( EmitErr( MUST_BE_IN_SEGMENT_BLOCK ) ); /* error displayed even in EQU, hence EmitErr()! */
    }

    if ( thissym == NULL ) {
        thissym = SymAlloc( "" );
        /* fixme: set thissym->variable? */
        thissym->state = SYM_INTERNAL;
        thissym->isdefined = TRUE;
    }

    DebugMsg1(("this_op: memtype=%Xh type=%s\n", opnd2->mem_type, opnd2->type ? opnd2->type->name : "NULL" ));
    opnd1->kind = EXPR_ADDR;

    /* v2.09: a label is not a valid argument */
    //if ( opnd2->sym && opnd2->sym->mem_type == MT_TYPE )
    //    thissym->type = opnd2->sym->type;
    /* v2.09: set structured type */
    thissym->type = opnd2->type;
    if ( opnd2->type ) {
        thissym->mem_type = MT_TYPE;
    } else
        thissym->mem_type = opnd2->mem_type;

    opnd1->sym  = thissym;
    SetSymSegOfs( thissym );
    opnd1->mem_type = thissym->mem_type;
    return( NOT_ERROR );
}

/* WIDTH and MASK operators */

static ret_code wimask_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
/*********************************************************************************************************/
{
    uint_64         dwRecIHi;
    uint_64         dwRecILo;
    uint_64         n = 1;
    struct          sfield *fl;
    struct          dsym *record;
    /* additional check needed if operand is a type */
    if ( opnd2->is_type ) {
        sym = opnd2->type;
        if (sym->typekind != TYPE_RECORD ) {
            return( fnEmitErr( OPERAND_MUST_BE_RECORD ) );
        }
    } else if ( opnd2->kind == EXPR_CONST ) {
        sym = opnd2->mbr;
    } else {
        sym = opnd2->sym;
    }
    if ( oper == T_MASK ) {
        int i;
        opnd1->value = 0;
        if ( opnd2->is_type ) { /* get mask of the RECORD? */
          if (0 == _memicmp(ModuleInfo.tokenarray[1].string_ptr, "xmm", 3)){
            record = (struct dsym *)sym;
            gmaskflag = FALSE;
            for (fl = record->e.structinfo->head; fl; fl = fl->next) {
              struct asym *rsym = &fl->sym;
              dwRecIHi = 0;  /* clear Hi 64 bit for the 128 bit RECORD */
              dwRecILo = 0;  /* clear Lo 64 bit for the 128 bit RECORD */
              for (i = rsym->offset; i < rsym->offset + rsym->total_size; i++){
              ShiftLeft(&dwRecIHi, &dwRecILo, n, i);
              opnd1->hlvalue |= dwRecIHi; /* OR Hi 64 bit for the 128 bit RECORD */
              opnd1->llvalue |= dwRecILo; /* clear Lo 64 bit for the 128 bit RECORD */
              }
            }
          }else
            opnd1->llvalue = GetRecordMask( (struct dsym *)sym );
        } else { /* get mask of the bitfield */
          if (0 == _memicmp(ModuleInfo.tokenarray[1].string_ptr, "xmm", 3)){
            gmaskflag = FALSE;
            dwRecIHi = 0;  /* clear Hi 64 bit for the 128 bit RECORD */
            dwRecILo = 0;  /* clear Lo 64 bit for the 128 bit RECORD */
            for (i = sym->offset; i < sym->offset + sym->total_size; i++){
              ShiftLeft(&dwRecIHi, &dwRecILo, n, i);
              opnd1->hlvalue |= dwRecIHi; /* OR Hi 64 bit for the 128 bit RECORD */
              opnd1->llvalue |= dwRecILo; /* clear Lo 64 bit for the 128 bit RECORD */
              }
            }
          else
              for ( i = sym->offset ;i < sym->offset + sym->total_size; i++ )
//#if AMD64_SUPPORT
#if defined(LLONG_MAX) || defined(__GNUC__) || defined(__TINYC__)
                opnd1->llvalue |= 1ULL << i;
#else
                opnd1->llvalue |= 1i64 << i;
#endif
//#else
//                opnd1->value |= 1 << i;
//#endif
        }
    } else {
        if ( opnd2->is_type ) { /* get width of the RECORD? */
            struct dsym *dir = (struct dsym *)sym;
            struct sfield *fl;
            for ( fl = dir->e.structinfo->head; fl; fl = fl->next )
                opnd1->value += fl->sym.total_size;
        } else
            opnd1->value = sym->total_size;
    }
    opnd1->kind = EXPR_CONST;
    return( NOT_ERROR );
}

#define  res(token, function) function ,
static ret_code (* const unaryop[])( int, struct expr *, struct expr *, struct asym *, char * ) = {
#include "unaryop.h" 
};
#undef res

/* plus_op() is called by [], () and + operator handlers */

static ret_code plus_op( struct expr *opnd1, struct expr *opnd2 )
/***************************************************************/
{
    DebugMsg1(("plus_op: kind=%d/%d memtype=%Xh-%Xh value=%d-%d sym=%s-%s mbr=%s-%s type=%s-%s\n",
               opnd1->kind, opnd2->kind,
               opnd1->mem_type, opnd2->mem_type, 
               opnd1->value, opnd2->value,
               opnd1->sym ? opnd1->sym->name : "NULL",
               opnd2->sym ? opnd2->sym->name : "NULL",
               opnd1->mbr ? opnd1->mbr->name : "NULL",
               opnd2->mbr ? opnd2->mbr->name : "NULL",
               opnd1->type ? opnd1->type->name : "NULL",
               opnd2->type ? opnd2->type->name : "NULL" ));
    /*
     * The formats allowed are (registers inside [] only!):
     *        constant + constant  CONST-CONST
     *        constant + address   CONST-ADDR
     *        register + constant  ADDR-CONST
     *        address + register   ADDR-ADDR
     *        register + register  ADDR-ADDR
     *        address  + address   ADDR-ADDR
     */

    if( check_direct_reg( opnd1, opnd2 ) == ERROR ) {
        DebugMsg(("plus_op: error direct register\n" ));
        return( fnEmitErr( INVALID_USE_OF_REGISTER ) );
    }
    /* v2.08: remove EXPR_REG variants */
    if ( opnd1->kind == EXPR_REG )
        opnd1->kind = EXPR_ADDR;
    if ( opnd2->kind == EXPR_REG )
        opnd2->kind = EXPR_ADDR;

    /* v2.07: don't allow multiple overrides */
    if ( opnd2->override ) {
        if ( opnd1->override ) {
            /* v2.07a: both T_REG or both T_ID is rejected */
            if ( opnd1->override->token == opnd2->override->token ) {
                DebugMsg(("plus_op: multiple overrides\n" ));
                return( fnEmitErr( MULTIPLE_OVERRIDES ) );
            }
        }
        opnd1->override = opnd2->override;
    }

    if( check_same( opnd1, opnd2, EXPR_CONST ) ) {

        DebugMsg1(("plus_op: CONST - CONST\n" ));
        opnd1->llvalue += opnd2->llvalue;

    } else if( check_same( opnd1, opnd2, EXPR_ADDR ) ) {

        DebugMsg1(("plus_op: ADDR - ADDR\n" ));
        fix_struct_value( opnd1 );
        fix_struct_value( opnd2 );
        if ( index_connect( opnd1, opnd2 ) == ERROR )
            return( ERROR );
        if( opnd2->sym != NULL ) {
            /* two relocatable labels not allowed */
            /* v2.05: changed */
            //if ( ( opnd1->sym != NULL ) && ( Parse_Pass > PASS_1 || error_msg == FALSE ) ) {
            if ( opnd1->sym != NULL &&
                opnd1->sym->state != SYM_UNDEFINED &&
                opnd2->sym->state != SYM_UNDEFINED ) {
                DebugMsg(("plus_op: two relocatable labels: %s - %s \n", opnd1->sym->name, opnd2->sym->name ));
                return( fnEmitErr( CANNOT_ADD_TWO_RELOCATABLE_LABELS ) );
            }
            opnd1->label_tok = opnd2->label_tok;
            opnd1->sym = opnd2->sym;
            /* v2.05: added */
            if ( opnd1->mem_type == MT_EMPTY )
                opnd1->mem_type = opnd2->mem_type;
            /* v2.10: copy qualifier ( [<reg>+imagerel xxx] */
            if ( opnd2->instr != EMPTY )
                opnd1->instr = opnd2->instr;
        }
        opnd1->llvalue += opnd2->llvalue;
        /* v2.08: added, test case [ecx+ebx.<struc>].<mbr> */
        if ( opnd2->type )
            opnd1->type = opnd2->type;

    } else if( check_both( opnd1, opnd2, EXPR_CONST, EXPR_ADDR ) ) {

        if( opnd1->kind == EXPR_CONST ) {
            DebugMsg1(("plus_op: CONST - ADDR\n" ));
            opnd2->llvalue += opnd1->llvalue;
            opnd2->indirect |= opnd1->indirect;

            if( opnd1->explicit == TRUE ) {
                opnd2->explicit = TRUE;
                opnd2->mem_type = opnd1->mem_type;
            } else if ( opnd2->mem_type == MT_EMPTY )
                opnd2->mem_type = opnd1->mem_type;

            /* v2.05: added. See dotop2.asm, "mov eax, v2.f1[ebx*2]" */
            if ( opnd2->mbr == NULL )
                opnd2->mbr = opnd1->mbr;

            /* v2.08: added, test case [4+ebx.<struc>].<mbr> */
            if ( opnd2->type )
                opnd1->type = opnd2->type; /* set <type> in op1! */

            TokenAssign( opnd1, opnd2 );

        } else {
            DebugMsg1(("plus_op: ADDR - CONST\n" ));
            opnd1->llvalue += opnd2->llvalue;
            /* v2.04: added. to make this case behave like
             * the CONST - REG case (see below).
             */
            /* v2.08: changed, test case [reg+struct] */
            //if ( opnd1->mem_type == MT_EMPTY )
            if ( opnd2->mbr ) { /* v2.10: added; regression test dotop5.asm */
                opnd1->mbr = opnd2->mbr;
                opnd1->mem_type = opnd2->mem_type;
            } else
            if ( opnd1->mem_type == MT_EMPTY && opnd2->is_type == FALSE )
                opnd1->mem_type = opnd2->mem_type;
        }
        fix_struct_value( opnd1 );
    } else {
        DebugMsg(("plus_op: error, unexpected format: %u - %u\n", opnd1->kind, opnd2->kind ));
        return( ConstError( opnd1, opnd2 ) );
    }
    return( NOT_ERROR );
}

static ret_code minus_op( struct expr *opnd1, struct expr *opnd2 )
/****************************************************************/
{
    struct asym      *sym;
    /*
     * The only formats allowed are:
     *        constant - constant
     *         address - constant       ( only in this order )
     *         address - address
     *        register - constant       ( only inside [] and in this
     *                                    order )
     */

    DebugMsg1(("minus_op: kind tok1=%u, tok2=%u\n", opnd1->kind, opnd2->kind ));

    if( check_direct_reg( opnd1, opnd2 ) == ERROR ) {
        DebugMsg(("minus_op: error direct register\n"));
        return( fnEmitErr( INVALID_USE_OF_REGISTER ) );
    }

    /* added for v1.94. It's related to the change done in MakeConst()!
     * todo: find out why flag no_error_msg was checked in v1.94-2.09.
     */
    if ( opnd1->kind == EXPR_ADDR &&
        opnd2->kind == EXPR_ADDR &&
        opnd2->sym &&
        opnd2->sym->state == SYM_UNDEFINED /* && !no_error_msg */ )
        ; /* don't convert token2 to a constant! */
    else
        MakeConst( opnd2 );

    if( check_same( opnd1, opnd2, EXPR_CONST ) ) {

        DebugMsg1(("minus_op: CONST-CONST\n" ));
        opnd1->llvalue -= opnd2->llvalue;

    } else if( opnd1->kind == EXPR_ADDR &&
              opnd2->kind == EXPR_CONST ) {

        DebugMsg1(("minus_op: ADDR-CONST\n" ));
        opnd1->llvalue -= opnd2->llvalue;
        fix_struct_value( opnd1 );

    } else if( check_same( opnd1, opnd2, EXPR_ADDR ) ){

        DebugMsg1(("minus_op: ADDR-ADDR\n" ));
        fix_struct_value( opnd1 );
        fix_struct_value( opnd2 );
        //if( opnd2->base_reg != NULL || opnd2->idx_reg != NULL ) { /* v2.09: just check 'indirect' */
        if( opnd2->indirect ) {
            DebugMsg(("minus_op error, opnd2->indirect==TRUE\n"));
            return( fnEmitErr( INVALID_USE_OF_REGISTER ) );
        }
        if( opnd2->label_tok == NULL ) {
            /* v2.06c: do 64-bit arithmetic (more rigid test in data.c) */
            //opnd1->value -= opnd2->value;
            opnd1->value64 -= opnd2->value64;
            opnd1->indirect |= opnd2->indirect;
        } else {
            if( opnd1->label_tok == NULL || opnd1->sym == NULL || opnd2->sym == NULL ) {
                DebugMsg(("minus_op error, label_tok=%X opnd1.sym=%X opnd2.sym=%X\n", opnd1->label_tok, opnd1->sym, opnd2->sym ));
                /* v2.05: error msg changed */
                //fnEmitErr( SYNTAX_ERROR );
                return( fnEmitErr( OPERAND_MUST_BE_RELOCATABLE ) );
            }
            /* handle first operand */
            sym = opnd1->sym;
            opnd1->value += sym->offset;

            /* handle second operand */
            sym = opnd2->sym;
            if( Parse_Pass > PASS_1 ) {
                /* if symbol is external, error - unless it's the same symbol */
                if ( ( sym->state == SYM_EXTERNAL ||
                     opnd1->sym->state == SYM_EXTERNAL) &&
                    sym != opnd1->sym ) {
                    DebugMsg(("minus_op error 6\n"));
                    return( fnEmitErr(INVALID_USE_OF_EXTERNAL_SYMBOL, opnd1->sym->name ) );
                }
                /* check if the 2 offsets belong to the same segment */
                if ( sym->segment != opnd1->sym->segment ) {
                    DebugMsg(("minus_op error, sym.segm=%X opnd1->sym.segm=%X\n", sym->segment, opnd1->sym->segment ));
                    return( fnEmitErr( OPERANDS_MUST_BE_IN_SAME_SEGMENT ) );
                }
            }

            /* the type changes from address to constant.
             * but only if both labels are defined and no indirect addressing.
             */
            opnd1->kind = EXPR_CONST;

            /* v2.05: if at least one label is undefined, assume result=1 */
            if ( opnd1->sym->state == SYM_UNDEFINED ||
                opnd2->sym->state == SYM_UNDEFINED ) {
                opnd1->value = 1;
                /* 2.09: make sure an undefined label is returned in opnd.sym.
                 * expression type has to be ADDR then; see equate22.aso.
                 * 2.11: returning EXPR_ADDR may cause problems -
                 * it may make the code longer than necessary, thus
                 * triggering an unnecessary jump extension.
                 * so it is returned only if the expression is used to define an equate.
                 */
                if ( opnd1->sym->state != SYM_UNDEFINED ) {
                    opnd1->sym = opnd2->sym;
                    opnd1->label_tok = opnd2->label_tok;
                }
                opnd1->kind = EXPR_ADDR;
            } else {
                /* v2.06c: do 64-bit arithmetic (more rigid test in data.c) */
                //opnd1->value -= sym->offset;
                //opnd1->value -= opnd2->value;
                opnd1->value64 -= sym->offset;
                opnd1->value64 -= opnd2->value64;
                opnd1->label_tok = NULL;
                opnd1->sym = NULL;
            }
            //if( opnd1->base_reg == NULL && opnd1->idx_reg == NULL ) { /* v2.09: just check 'indirect' */
            if( opnd1->indirect == FALSE ) {
                if( opnd1->instr == T_OFFSET && opnd2->instr == T_OFFSET )
                    opnd1->instr = EMPTY;
                //opnd1->indirect = FALSE; /* v2.09: not needed */
            } else {
                DebugMsg1(("minus_op, exit, ADDR, base=%X, idx=%X\n", opnd1->base_reg, opnd1->idx_reg ));
                opnd1->kind = EXPR_ADDR;
                //opnd1->indirect |= opnd2->indirect;  /* v2.09: op1->indirect is always 1, op2->indirect is always 0 */
            }
            opnd1->explicit = FALSE;
            opnd1->mem_type = MT_EMPTY;
        }

    } else if( opnd1->kind == EXPR_REG &&
              opnd2->kind == EXPR_CONST ) {

        opnd1->llvalue = -1 * opnd2->llvalue;
        opnd1->indirect |= opnd2->indirect;
        opnd1->kind = EXPR_ADDR;

    } else {
        DebugMsg(("minus_op, exit, error: kinds tok1=%u, tok2=%u\n", opnd1->kind, opnd2->kind ));
        return( ConstError( opnd1, opnd2 ) );
    }
    return( NOT_ERROR );
}

/* v2.10: don't emit "struct field expected" error if item is an operand of OPATTR */

static ret_code struct_field_error( struct expr *opnd )
/*****************************************************/
{
    if ( opnd->is_opattr ) {
        opnd->kind = EXPR_ERROR;
        return( NOT_ERROR );
    }
    return( fnEmitErr( STRUCTURE_FIELD_EXPECTED ) );
}

static ret_code dot_op( struct expr *opnd1, struct expr *opnd2 )
/**************************************************************/
{
    /* this code needs cleanup! some stuff is obsolete. */

    DebugMsg1(("dot_op: op1-op2 kind=%d/%d sym=%s-%s type=%s-%s mbr=%s-%s\n",
               opnd1->kind, opnd2->kind,
               opnd1->sym  ? opnd1->sym->name  : "NULL",
               opnd2->sym  ? opnd2->sym->name  : "NULL",
               opnd1->type ? opnd1->type->name : "NULL",
               opnd2->type ? opnd2->type->name : "NULL",
               opnd1->mbr  ? opnd1->mbr->name  : "NULL",
               opnd2->mbr  ? opnd2->mbr->name  : "NULL" ));

    /*
     * The formats allowed are:
     *        [register]      . (type) constant
     *        label           . (type) constant
     *        (type) constant . (type) constant
     *
     * with OPTION OLDSTRUCTS:
     *        [register]      . address
     *        address         . address
     */

    if( check_direct_reg( opnd1, opnd2 ) == ERROR ) {
        DebugMsg(("dot_op: error direct register\n"));
        return( fnEmitErr( INVALID_USE_OF_REGISTER ) );
    }

    /* v2.08: remove EXPR_REG variants */
    if ( opnd1->kind == EXPR_REG )
        opnd1->kind = EXPR_ADDR;
    if ( opnd2->kind == EXPR_REG )
        opnd2->kind = EXPR_ADDR;

    /* forward ref to a struct: [reg].<struct> */
    if ( opnd2->sym && opnd2->sym->state == SYM_UNDEFINED && Parse_Pass == PASS_1 ) {
        DebugMsg(("dot_op: forward reference %s, replaced by null struct type\n", opnd2->sym->name ));
        if ( !nullstruct )
            nullstruct = CreateTypeSymbol( NULL, "", FALSE );
        opnd2->type = nullstruct;
        opnd2->is_type = TRUE; /* v2.10: added */
        opnd2->sym = NULL;
        opnd2->kind = EXPR_CONST;
    }

    if( check_same( opnd1, opnd2, EXPR_ADDR ) ) {

        DebugMsg1(("dot_op, ADDR - ADDR, t1-t2 memtype=%X-%X sym=%s-%s\n",
                   opnd1->mem_type, opnd2->mem_type,
                   opnd1->sym  ? opnd1->sym->name  : "NULL",
                   opnd2->sym  ? opnd2->sym->name  : "NULL" ));

#if 1 /* v2.05: error */
        if ( opnd2->mbr == NULL && !ModuleInfo.oldstructs ) {
            DebugMsg(("dot_op: error, mbr 2 is NULL\n"));
            return( struct_field_error( opnd1 ) );
        }
#endif
        if ( index_connect( opnd1, opnd2 ) == ERROR )
            return( ERROR );

        if( opnd2->sym != NULL ) {
            if( opnd1->sym != NULL &&
                opnd1->sym->state != SYM_UNDEFINED &&
                opnd2->sym->state != SYM_UNDEFINED ) {
                DebugMsg(("dot_op: error, two relocatable labels: %s - %s \n", opnd1->sym->name, opnd2->sym->name ));
                return( fnEmitErr( CANNOT_ADD_TWO_RELOCATABLE_LABELS ) );
            }
            opnd1->label_tok = opnd2->label_tok;
            opnd1->sym = opnd2->sym;
        }
        if( opnd2->mbr != NULL ) {
            opnd1->mbr = opnd2->mbr;
        }
        opnd1->value += opnd2->value;
        if( opnd1->explicit == FALSE ) {
            opnd1->mem_type = opnd2->mem_type;
        }
        if ( opnd2->type )
            opnd1->type = opnd2->type;

    } else if( ( opnd1->kind == EXPR_CONST ) && ( opnd2->kind == EXPR_ADDR ) ) {

        DebugMsg1(("dot_op, CONST - ADDR: t1-t2 memtype=%Xh-%Xh istype=%u-%u\n",
                   opnd1->mem_type, opnd2->mem_type, opnd1->is_type, opnd2->is_type ));
        /* v2.08 added (copied from branch EXPR_ADDR-EXPR_REG )*/
        if ( opnd1->is_type && opnd1->type ) {
            opnd2->assumecheck = FALSE;
            opnd1->llvalue = 0;  /* v2.08: this was previously done in get_operand() */
        }
#if 1 /* v2.05: error */
        /* <structname>.<member>[<index_reg>] is ALWAYS ok! */
        if ( ( !ModuleInfo.oldstructs ) && ( opnd1->is_type == FALSE && opnd1->mbr == NULL ) )
            return( struct_field_error( opnd1 ) );
#endif
        /* for TYPE.xxx, return offset instead of size */
        if ( opnd1->mbr && opnd1->mbr->state == SYM_TYPE )
            opnd1->llvalue = opnd1->mbr->offset;
        opnd2->indirect |= opnd1->indirect;
        opnd2->llvalue += opnd1->llvalue;
        DebugMsg1(("dot_op, CONST - ADDR, t1.type=%X (%s), t2.type=%X (%s)\n",
                   opnd1->type,
                   opnd1->type ? opnd1->type->name : "",
                   opnd2->type,
                   opnd2->type ? opnd2->type->name : "" ));
        /* v2.06: added. test case: INVOKE struct.mbr[edx] ( mbr has a type ) */
        if ( opnd2->mbr )
            opnd1->type = opnd2->type;
        TokenAssign( opnd1, opnd2 );

    } else if( ( opnd1->kind == EXPR_ADDR ) && ( opnd2->kind == EXPR_CONST ) ) {

        DebugMsg1(("dot_op, ADDR - CONST: t1-t2 memtype=%Xh-%Xh t1.explicit=%u\n",
                   opnd1->mem_type, opnd2->mem_type, opnd1->explicit ));

        /* v2.08: changed to catch [ebx].<num> or [ebx].<simple type> */
        //if ( (!ModuleInfo.oldstructs) && opnd2->type == NULL && opnd2->mbr == NULL ) {
        if ( (!ModuleInfo.oldstructs) && ( opnd2->type == NULL || opnd2->is_type == FALSE ) && opnd2->mbr == NULL ) {
            DebugMsg(("dot_op: error, constant or simple type after dot\n"));
            return( struct_field_error( opnd1 ) );
        }

        /* v2.08 added (copied from branch EXPR_ADDR-EXPR_REG )*/
        if ( opnd2->is_type && opnd2->type ) {
            opnd1->assumecheck = FALSE;
            opnd2->llvalue = 0;  /* v2.08: this was previously done in get_operand() */
        }
        /* for [var].TYPE | STRUCT_FIELD, use offset instead of size */
        if ( opnd2->mbr && opnd2->mbr->state == SYM_TYPE )
            opnd2->llvalue = opnd2->mbr->offset;
        opnd1->llvalue += opnd2->llvalue;
        opnd1->mem_type = opnd2->mem_type; /* v2.08: now always done */
        if( opnd2->mbr != NULL ) {
            opnd1->mbr = opnd2->mbr;
#if 0 /* v2.07 */
            /* temp. disabled in v1.95, test case:
             * mov eax,(<struct> ptr [ebx]).F1
             * however: mov ax, word ptr var[bx].F1 ???
             * the condition can't be disabled. Instead the PTR
             * operator must NOT set the explicit flag if the
             * first operand is a structure.
             */
            if( opnd1->explicit == FALSE )
#endif
                //opnd1->mem_type = opnd2->mem_type; /* v2.08: obsolete */
        }

        DebugMsg1(("dot_op, ADDR - CONST, t1.type=%X (%s), t2.type=%X (%s)\n",
                   opnd1->type,
                   opnd1->type ? opnd1->type->name : "",
                   opnd2->type,
                   opnd2->type ? opnd2->type->name : "" ));
#if 0 /* v1.96 */
        if ( opnd2->type )
#endif
            opnd1->type = opnd2->type;

    } else if ( opnd1->kind == EXPR_CONST && opnd2->kind == EXPR_CONST ) {

        DebugMsg1(("dot_op, CONST - CONST, t1-t2 value=%u-%u, memtype=%Xh-%Xh istype=%u-%u\n",
                   opnd1->value, opnd2->value, opnd1->mem_type, opnd2->mem_type, opnd1->is_type, opnd2->is_type));
        if ( opnd2->mbr == NULL && !ModuleInfo.oldstructs ) {
            DebugMsg(("dot_op: error, opnd2.mbr=NULL\n" ));
            return( struct_field_error( opnd1 ) );
        }
        if ( opnd1->type != NULL ) {
            /*
             * v2.06: the token1 value must NOT be ignored if the token is a
             * struct member: mov ax, [offset] <struct>.<mbr>.<mbr>
             */
            if ( opnd1->mbr != NULL )
                opnd1->llvalue += opnd2->llvalue;
            else {
                /* old token is a type - the value (=size) is ignored then. */
                opnd1->llvalue = opnd2->llvalue;
            }
            opnd1->mbr = opnd2->mbr;
            /* v2.0: copy mem_type (test case: mov ds:[<struct>.<mbr>], 123) */
            opnd1->mem_type = opnd2->mem_type;
            /* v2.05: removed, it's still a type constant */
            //opnd1->is_type = FALSE;
            opnd1->is_type = opnd2->is_type;
            /* either clear <type> or use the renewed one */
            if ( opnd1->type != opnd2->type )
                opnd1->type = opnd2->type;
            else
                opnd1->type = NULL;
        } else {
            /* old token is NOT a type */
            /* most likely a number or an MT_ABS symbol! */
            /* so the TOTAL of both constants is required */
            opnd1->llvalue += opnd2->llvalue;
            opnd1->mbr = opnd2->mbr;
            opnd1->mem_type = opnd2->mem_type;
        }
    } else {
        DebugMsg(("dot_op: error, unknown kind combination, opnd1->kind=%d, opnd2->kind=%d\n", opnd1->kind, opnd2->kind ));
        return( struct_field_error( opnd1 ) );
    }
    return( NOT_ERROR );
}

static ret_code colon_op( struct expr *opnd1, struct expr *opnd2 )
/****************************************************************/
{
    int_32              temp;
    struct asym         *sym;
    /*
     * The only formats allowed are:
     *     seg_reg : const
     *     seg_reg : address
     *     seg_label : const
     *     seg_label : address
     *     ( seg_label = segment or group symbol )
     *     inside square brackets, seg_reg : register is not accepted
     *     if Masm-syntax is on.
     */
    DebugMsg1(("colon_op: t1-t2 kind=%d/%d type=%s-%s is_type=%u-%u\n",
               opnd1->kind, opnd2->kind,
               opnd1->type ? opnd1->type->name : "NULL",
               opnd2->type ? opnd2->type->name : "NULL",
               opnd1->is_type, opnd2->is_type ));
    if( opnd2->override != NULL ) {
        /* v2.07a: was too rigid */
        if ( ( opnd1->kind == EXPR_REG && opnd2->override->token == T_REG ) ||
            ( opnd1->kind == EXPR_ADDR && opnd2->override->token == T_ID ) ) {
            DebugMsg(("colon_op: multiple override=%s\n", opnd2->override->string_ptr ));
            return( fnEmitErr( MULTIPLE_OVERRIDES ) );
        }
    }
    switch ( opnd2->kind ) {
    case EXPR_REG:
        /* v2.05: register as second operand must be enclosed in [] */
        if ( opnd2->indirect == FALSE ) {
            DebugMsg(("colon_op: register after : not enclosed in []\n" ));
            return( fnEmitErr( INVALID_USE_OF_REGISTER ) );
        }
        break;
    case EXPR_FLOAT:
        return( fnEmitErr( REAL_OR_BCD_NUMBER_NOT_ALLOWED ) );
    }

    if( opnd1->kind == EXPR_REG ) {

        /* the item before the ':' must be a single register */
        if( opnd1->idx_reg != NULL ) {
            DebugMsg(("colon_op: register before ':' has idx_reg set!?\n"));
            return( fnEmitErr( INVALID_USE_OF_REGISTER ) );
        }
        /* segment override inside bracket not allowed with -Zne.
         * [ds:0] is ok, but [ds:ebx] is rejected.
         */
        /* v2.08: test moved here from get_operand() */
        /* v2.10: regression in v2.08-2.09: check was way too simple.
         * problem: indirect-flag isn't set for segment regs (anymore?).
         * error check moved back to get_operand().
         */
#if 0
        if ( Options.strict_masm_compat ) {
            return( fnEmitErr( INVALID_USE_OF_REGISTER ) );
        }
#endif
        /* make sure first operand is a segment register */
        temp = opnd1->base_reg->tokval;
        if ( ( GetValueSp( temp ) & OP_SR ) == 0 ) {
            return( fnEmitErr( SEGMENT_GROUP_OR_SEGREG_EXPECTED ) );
        }

        opnd2->override = opnd1->base_reg;
        opnd2->indirect |= opnd1->indirect;

        if ( opnd2->kind == EXPR_CONST ) {
            opnd2->kind = EXPR_ADDR;
            /* v2.05: type flag cleared HERE, not in dot_op()
             * v2.05rc17 problem: mov es:byte ptr <var>,0
             * so the flag isn't cleared at all now.
             */
            //opnd2->is_type = FALSE;
        }

        if( opnd1->explicit ) {
            opnd2->explicit = opnd1->explicit;
            opnd2->mem_type = opnd1->mem_type;
            opnd2->Ofssize  = opnd1->Ofssize;
        }
        TokenAssign( opnd1, opnd2 );

        /*
         * currently the <type> token isn't copied by
         * TokenAssign (which is probably just for historical reasons).
         * So copy it manually!
         * v1.95: only copy if it is != NULL!
         * Testcase: (<type> ptr DS:[0]).<struct_field> ...
         * In this case the DS:[] will clear the <type>, as a result
         * the dot operator won't have a valid assume and the code fails.
         */
        if ( opnd2->type )
            opnd1->type = opnd2->type;

    } else if( opnd1->kind == EXPR_ADDR &&
              /* opnd2->kind == EXPR_ADDR && */
              opnd1->override == NULL &&
              opnd1->instr == EMPTY &&
              opnd1->value == 0 &&
              opnd1->sym &&
              opnd1->base_reg == NULL &&
              opnd1->idx_reg == NULL ) {

        sym = opnd1->sym;

        if( sym->state == SYM_GRP || sym->state == SYM_SEG ) {
            opnd2->kind = EXPR_ADDR;
            opnd2->override = opnd1->label_tok;
            opnd2->indirect |= opnd1->indirect;
            if( opnd1->explicit ) {
                opnd2->explicit = opnd1->explicit;
                opnd2->mem_type = opnd1->mem_type;
                opnd2->Ofssize  = opnd1->Ofssize;
            }
            TokenAssign( opnd1, opnd2 );
            opnd1->type = opnd2->type;

        } else if( Parse_Pass > PASS_1 || sym->state != SYM_UNDEFINED ) {
            DebugMsg(("colon_op error 4\n"));
            return( fnEmitErr( SEGMENT_GROUP_OR_SEGREG_EXPECTED ) );
        }
    } else {
        DebugMsg(("colon_op error 5\n"));
        return( fnEmitErr( SEGMENT_GROUP_OR_SEGREG_EXPECTED ) );
    }
    return( NOT_ERROR );
}

static ret_code positive_op( struct expr *opnd1, struct expr *opnd2 )
/*******************************************************************/
{
    DebugMsg1(("positive_op: value=%" I64_SPEC "X high=%" I64_SPEC "X\n", opnd2->llvalue, opnd2->hlvalue ));
    /*
     * The formats allowed are:
     *        + constant
     *        + float
     * v2.06: unlike the other operators unary + will
     * handle 128-bit values (needed for TBYTE integers)
     */

    MakeConst( opnd2 );
    if( opnd2->kind == EXPR_CONST ) {
        opnd1->kind = EXPR_CONST;
        opnd1->llvalue = opnd2->llvalue;
        opnd1->hlvalue = opnd2->hlvalue; /* v2.06: added */
    } else if( opnd2->kind == EXPR_FLOAT ) {
        opnd1->kind = EXPR_FLOAT;
        opnd1->float_tok = opnd2->float_tok;
        opnd1->negative = opnd2->negative;
    } else {
        DebugMsg(("positive_op: error 1\n"));
        return( fnEmitErr( CONSTANT_EXPECTED ) );
    }
    return( NOT_ERROR );
}

static ret_code negative_op( struct expr *opnd1, struct expr *opnd2 )
/*******************************************************************/
{
    DebugMsg1(("negative_op: value=%" I64_SPEC "X high=%" I64_SPEC "X\n", opnd2->llvalue, opnd2->hlvalue ));
    /*
     * The formats allowed are:
     *        - constant
     *        - float
     */

    MakeConst( opnd2 );
    if( opnd2->kind == EXPR_CONST ) {
        opnd1->kind = EXPR_CONST;
        opnd1->llvalue = -opnd2->llvalue;
        /* v2.06: the unary '-' operator is to work with
         * magnitudes > 64-bit. Current implementation is
         * a bit hackish.
         */
        if ( opnd2->hlvalue )
            opnd1->hlvalue = -opnd2->hlvalue - 1;
        opnd1->negative = 1 - opnd2->negative; /* ??? supposed to be used for EXPR_FLOAT only! */
    } else if( opnd2->kind == EXPR_FLOAT ) {
        opnd1->kind = EXPR_FLOAT;
        opnd1->float_tok = opnd2->float_tok;
        opnd1->negative = 1 - opnd2->negative;
    } else {
        DebugMsg(("negative_op: unexpected opnd2.kind=%d\n", opnd2->kind ));
        return( fnEmitErr( CONSTANT_EXPECTED ) );
    }
    return( NOT_ERROR );
}

/* v2.07: moved out from get_operand, case T_REG
 * this function is now called from calculate() only.
 */
static void CheckAssume( struct expr *opnd )
/******************************************/
{
    struct asym *sym = NULL;

#if 1 /* v2.10: see regression test ptr2.asm */
    if ( opnd->explicit ) { /* perhaps check mem_type instead of explicit */
        if ( opnd->type && opnd->type->mem_type == MT_PTR ) {
            DebugMsg1(( "CheckAssume(%s, MT_PTR type=>%s< )\n", opnd->type->name ));
            if ( opnd->type->is_ptr == 1 ) { /* dereference only if indirection is 1 */
                opnd->mem_type = opnd->type->ptr_memtype;
                opnd->type = opnd->type->target_type;
                return; /* ignore assumes in this case */
            }
        }
    }
#endif
    /* in jwasm < v2.10, the idx_reg had higher priority than base_reg.
     * However, the base reg is supposed to have a higher priority.
     * This wasn't fully clear, because in Masm 6, if no register has
     * a scaling factor, the second one becomes base - something that
     * Uasm didn't do, unless -Zg was set.
     * Since v2.10, Uasm behaves like Masm v6+: base and index registers
     * are swapped, and assume for base has higher priority than assume for
     * index.
     */
    if ( opnd->base_reg ) {
        sym = GetStdAssumeEx( opnd->base_reg->bytval );
    }
    if (!sym && opnd->idx_reg ) {
        sym = GetStdAssumeEx( opnd->idx_reg->bytval );
    }
    if ( sym ) {
      if ( opnd->type != NULL ){ 
        DebugMsg1(( "CheckAssume(%s, type=>%s<, mbr=>%s<): assume=%s [memtype=%X isptr=%u type=%s target_type=%s ptr_memt=%X]\n",
                   GetResWName( ( opnd->idx_reg ? opnd->idx_reg->tokval : opnd->base_reg->tokval ), NULL ),
                   opnd->type ? opnd->type->name : "NULL",
                   opnd->mbr ? opnd->mbr->name : "NULL",
                   sym->name, sym->mem_type, sym->is_ptr,
                   sym->type ? sym->type->name : "NULL",
                   sym->target_type ? sym->target_type->name : "NULL",
                   sym->ptr_memtype ));
      }
        /* v2.08: skip ASSUMEd type if type or mbr is set */
        //if ( opnd->type || opnd->mbr )
        //    return;
        /* skip "alias" types */
        /* v2.05: obsolete */
        //for ( ; sym->type; sym = sym->type );
        /* v2.05: new */
        if ( sym->mem_type == MT_TYPE )
            opnd->type = sym->type;
        else if ( sym->is_ptr == 1 ) { /* v2.10: only dereference if indirection is 1 */
            opnd->type = sym->target_type;
            if ( sym->target_type )
                opnd->mem_type = sym->target_type->mem_type;
            else
                opnd->mem_type = sym->ptr_memtype;
        }
    }
}

/* get floating-point register index */

static ret_code check_streg( struct expr *opnd1, struct expr *opnd2 )
/*******************************************************************/
{
    if ( opnd1->scale > 0 ) {
        return( fnEmitErr( INVALID_USE_OF_REGISTER ) );
    }
    opnd1->scale++; /* make sure there's only ONE bracket pair */
    if ( opnd2->kind != EXPR_CONST ) {
        return( fnEmitErr( INVALID_COPROCESSOR_REGISTER ) );
    }
    opnd1->st_idx = opnd2->value;
    return( NOT_ERROR );
}

/* v2.10: comparison of type operands moved from calculate() to this function. */

static void cmp_types( struct expr *opnd1, struct expr *opnd2, int trueval )
/**************************************************************************/
{
    struct asym *type1;
    struct asym *type2;

    /* v2.10: special handling of pointer types. */
    //if ( opnd1->mem_type == MT_PTR && opnd2->mem_type == MT_PTR && opnd1->type && opnd2->type ) {
    if ( opnd1->mem_type == MT_PTR && opnd2->mem_type == MT_PTR ) {
        /*myassert( ( opnd1->type || opnd1->type_tok ) && ( opnd2->type || opnd2->type_tok ) );*/
        
        if(opnd1->type || opnd1->type_tok)
            type1 = ( opnd1->type ? opnd1->type : SymSearch( opnd1->type_tok->string_ptr ) );

        if(opnd2->type || opnd2->type_tok)
            type2 = ( opnd2->type ? opnd2->type : SymSearch( opnd2->type_tok->string_ptr ) );

        if (!type1 || !type2)
        {
            EmitError(INVALID_TYPE_EXPRESSION);
        }

        //opnd1->value64 = ( ( type1->is_ptr == type2->is_ptr &&
        opnd1->value64 = ( ( type1->is_ptr == type2->is_ptr &&
                            type1->ptr_memtype == type2->ptr_memtype &&
                            type1->target_type == type2->target_type ) ? trueval : ~trueval );
        DebugMsg1(("cmp_types: MT_PTR-MT_PTR is_ptr=%u-%u ptr_memtype=%X-%X target_type=%X-%X\n",
                   type1->is_ptr, type2->is_ptr,
                   type1->ptr_memtype, type2->ptr_memtype,
                   type1->target_type, type2->target_type ));
    } else {
        DebugMsg1(("cmp_types: memtype=%X-%X type=%X-%X\n",
                   opnd1->mem_type, opnd2->mem_type, opnd1->type, opnd2->type ));
        /* v2.09: include type member in comparison, but ignore typedef types */
        if ( opnd1->type && opnd1->type->typekind == TYPE_TYPEDEF && opnd1->type->is_ptr == 0 )
            opnd1->type = NULL;
        if ( opnd2->type && opnd2->type->typekind == TYPE_TYPEDEF && opnd2->type->is_ptr == 0 )
            opnd2->type = NULL;
        opnd1->value64 = ( ( opnd1->mem_type == opnd2->mem_type &&
                            opnd1->type == opnd2->type ) ? trueval : ~trueval );
    }
}

static ret_code calculate( struct expr *opnd1, struct expr *opnd2, const struct asm_tok *oper )
/*********************************************************************************************/
/* Performs operation <oper> with operands <opnd1> and <opnd2>.
 * the result will be returned in <opnd1>.
 * <oper> points to the item in tokenarray[] that contains the operator.
 * possible operators:
 *  T_OP_BRACKET       is (virtually) an alias for '+'
 *  T_OP_SQ_BRACKET    is (virtually) an alias for '+'
 *  '+' (unary + binary )
 *  '-' (unary + binary )
 *  '*'
 *  '/'
 *  T_DOT
 *  T_COLON
 *  T_BINARY_OPERATOR ( PTR, MOD, GE, GT, LE, GT, EQ, NE, also AND, OR, XOR, SHL, SHR )
 *  T_UNARY_OPERATOR ( OFFSET, SHORT, ... , also NOT )
 *
 * to be done: the code can be simplified because currently
 *             expression type is set to EXPR_REG when a
 *             register was found - even if it is inside [].
 *             A reg inside [] should ALWAYS give EXPR_ADDR!
 */
{
    int_32              temp;
    struct asym         *sym;
    char                *name;

    /* avoid to use the <string> member once it's part of an expression!
     * the <value> member is the one to be used then.
     * test case: db "a"+80h
     * v2.08: first: this is too early; second: the current operand is opnd2.
     * third: the space is also used by float_tok member, which cannot be cleared.
     * probably the best solution - at calculate()'s end:
     * if ( opnd1->kind == EXPR_CONST ) opnd1->quoted_string = NULL;
     */
    opnd1->quoted_string = NULL;

    /* v2.11: added check to ensure constant fits in 64-bits */
    if ( opnd2->hlvalue ) {
        /* opattr and unary +/- are ok, they can handle 128-bits */
        if ( opnd2->is_opattr || ( ( oper->token == '+' || oper->token == '-' ) && oper->specval == UNARY_PLUSMINUS ) )
            ;
        else {
            DebugMsg(("%u calculate(%s): value too large\n", evallvl, oper->string_ptr ));
            return( fnEmitErr( CONSTANT_VALUE_TOO_LARGE_EX, opnd2->hlvalue, opnd2->value64 ) );
        }
    }

    switch( oper->token ) {
    case T_OP_SQ_BRACKET:
        /* v2.07: the ASSUMEs are now checked only when operator [] is done.
         * this is compatible with Masm:
         *   assume ebx:ptr <struct>
         *   mov eax, [ebx.<member>]             ;is to fail
         *   mov eax, [ebx.<struct>.<member>]    ;is to be ok
         * previously both variants were accepted by jwasm.
         */
        if ( opnd2->assumecheck == TRUE ) {
            opnd2->assumecheck = FALSE;   /* check ONE time only! */
            if ( opnd1->sym == NULL ) /* v2.10: added; see assume10.asm */
                CheckAssume( opnd2 );
        }

        if ( opnd1->kind == EXPR_EMPTY ) {
            DebugMsg1(("%u calculate(%s): single item\n", evallvl, oper->string_ptr ));
            TokenAssign( opnd1, opnd2 );
            opnd1->type = opnd2->type;
			opnd1->isptr = FALSE;
			if (opnd1->kind == EXPR_CONST)
				opnd1->isptr = TRUE;
			else if (opnd2->kind == EXPR_CONST)
				opnd2->isptr = TRUE;
            if ( opnd1->is_type && opnd1->kind == EXPR_CONST )
                opnd1->is_type = 0;
            break;
        }

        /* v2.03: make Uasm reject syntax variants
         * "mov eax, DWORD [EBX]"
         * "mov eax, DWORD [var_name]"
         * variants still valid:
         * "mov eax, DWORD [WORD]"
         * "mov eax, DWORD [4]"
         * "mov eax, [DWORD][EBX]"
         */
        /* v2.08: structure/union names are ok: mov eax, S1[ebx] */
        //if ( opnd1->is_type == TRUE &&
        if ( opnd1->is_type == TRUE && opnd1->type == NULL &&
            (opnd2->kind == EXPR_ADDR || opnd2->kind == EXPR_REG ) ) {
            DebugMsg(("calculate(%s): incompatible usage of (simple) type\n", oper->string_ptr ));
            return( fnEmitErr( SYNTAX_ERROR_IN_EXPRESSION ) );
        }

        /* v2.08: moved here from get_operand() */
        if ( opnd1->base_reg && opnd1->base_reg->tokval == T_ST )
            return( check_streg( opnd1, opnd2 ) );

#ifdef DEBUG_OUT
        if ( plus_op( opnd1, opnd2 ) == ERROR )
            return( ERROR );
        break;
#else
        return( plus_op( opnd1, opnd2 ) );
#endif
    case T_OP_BRACKET:

        if ( opnd1->kind == EXPR_EMPTY ) {
            DebugMsg1(("%u calculate(%s): single item\n", evallvl, oper->string_ptr ));
            TokenAssign( opnd1, opnd2 );
            opnd1->type = opnd2->type;
            break;
        }
        /* v2.03: make Uasm reject syntax variants
         * "mov eax, DWORD (<label>)"
         */
        if ( opnd1->is_type == TRUE && opnd2->kind == EXPR_ADDR ) {
            DebugMsg(("calculate(%s): incompatible usage of (simple) type\n", oper->string_ptr ));
            return( fnEmitErr( SYNTAX_ERROR_IN_EXPRESSION ) );
        }

        /* v2.08: moved here from get_operand() */
        if ( opnd1->base_reg && opnd1->base_reg->tokval == T_ST )
            return( check_streg( opnd1, opnd2 ) );

        DebugMsg1(("calculate(%s): calling plus_op()\n", oper->string_ptr ));
#ifdef DEBUG_OUT
        if ( plus_op( opnd1, opnd2 ) == ERROR )
            return( ERROR );
        break;
#else
        return( plus_op( opnd1, opnd2 ) );
#endif
    case '+':
        if ( oper->specval == UNARY_PLUSMINUS ) /* unary op? */
            return( positive_op( opnd1, opnd2 ) );
#ifdef DEBUG_OUT
        if ( plus_op( opnd1, opnd2 ) == ERROR )
            return( ERROR );
        break;
#else
        return( plus_op( opnd1, opnd2 ) );
#endif
    case '-':
        if ( oper->specval == UNARY_PLUSMINUS ) /* unary op? */
            return( negative_op( opnd1, opnd2 ) );
#ifdef DEBUG_OUT
        if ( minus_op( opnd1, opnd2 ) == ERROR )
            return( ERROR );
        break;
#else
        return( minus_op( opnd1, opnd2 ) );
#endif
    case T_DOT:
#ifdef DEBUG_OUT
        if ( dot_op( opnd1, opnd2 ) == ERROR )
            return( ERROR );
        break;
#else
        return( dot_op( opnd1, opnd2 ) );
#endif
    case T_COLON:
#ifdef DEBUG_OUT
        if ( colon_op( opnd1, opnd2 ) == ERROR )
            return( ERROR );
        break;
#else
        return( colon_op( opnd1, opnd2 ) );
#endif
    case '*':
        /*
         * The only formats allowed are:
         *        constant * constant
         *        register * scaling factor ( 1, 2, 4 or 8 )
         *                   386 only
         */
        DebugMsg1(("calculate(*): kind=%d/%d value=%" I64_SPEC "d-%" I64_SPEC "d mbr=%X-%X\n",
                   opnd1->kind,    opnd2->kind,
                   opnd1->value64, opnd2->value64,
                   opnd1->mbr,     opnd2->mbr ));

        MakeConst( opnd1 );
        MakeConst( opnd2 );

        if( check_same( opnd1, opnd2, EXPR_CONST ) ) {
            opnd1->llvalue *= opnd2->llvalue;
        } else if( check_both( opnd1, opnd2, EXPR_REG, EXPR_CONST ) ) {
            if( check_direct_reg( opnd1, opnd2 ) == ERROR ) {
                DebugMsg(("calculate(*) error direct register\n"));
                return( fnEmitErr( INVALID_USE_OF_REGISTER ) );
            }
            /* scaling factor */
            if( opnd2->kind == EXPR_REG ) {
                /* scale * reg */
                opnd1->idx_reg = opnd2->base_reg;
                opnd1->scale = opnd1->value;
                opnd1->value = 0;
                //opnd2->base_reg = NULL;
            } else {
                /* reg * scale */
                opnd1->idx_reg = opnd1->base_reg;
                opnd1->scale = opnd2->value;
            }
            /* v2.08: check 0 (the default value) here */
            if ( opnd1->scale == 0 ) {
                return( fnEmitErr( SCALE_FACTOR_MUST_BE_1_2_4_OR_8 ) );
            }

            opnd1->base_reg = NULL;
            opnd1->indirect = TRUE;
            opnd1->kind = EXPR_ADDR;
        } else {
            DebugMsg(("calculate(*) error 2\n"));
            return( ConstError( opnd1, opnd2 ) );
        }
        break;
    case '/':
        /*
         * The only formats allowed are:
         *        constant / constant
         */
        DebugMsg1(("calculate(/): t1-t2 kind %u-%u values %" I64_SPEC "d-%" I64_SPEC "d\n",
                   opnd1->kind,    opnd2->kind,
                   opnd1->value64, opnd2->value64 ));
        MakeConst( opnd1 );
        MakeConst( opnd2 );

        if( check_same( opnd1, opnd2, EXPR_CONST ) == FALSE ) {
            DebugMsg(("calculate(/) error 1\n"));
            return( ConstError( opnd1, opnd2 ) );
        }

        if ( opnd2->llvalue == 0 ) {
            DebugMsg(("calculate(/) error 2\n"));
            return( fnEmitErr( DIVIDE_BY_ZERO_IN_EXPR ) );
        }

        opnd1->value64 /= opnd2->value64;
        break;
    case T_BINARY_OPERATOR:
        DebugMsg1(("calculate(%s [T_BINARY_OPERATOR] ): t1-t2 kind %d/%d memtype %X-%X sym %s-%s type %s-%s\n",
                   oper->string_ptr,
                   opnd1->kind, opnd2->kind,
                   opnd1->mem_type, opnd2->mem_type,
                   opnd1->sym  ? opnd1->sym->name  : "NULL",
                   opnd2->sym  ? opnd2->sym->name  : "NULL",
                   opnd1->type ? opnd1->type->name : "NULL",
                   opnd2->type ? opnd2->type->name : "NULL" ));

        if ( oper->tokval == T_PTR ) {
            if ( opnd1->is_type == FALSE ) {
                if ( opnd1->sym && opnd1->sym->state == SYM_UNDEFINED ) {
                    CreateTypeSymbol( opnd1->sym, NULL, TRUE );
                    opnd1->type = opnd1->sym;
                    opnd1->sym = NULL;
                    opnd1->is_type = TRUE;
                } else {
                    DebugMsg(("calculate(PTR), error 1: t1 is_type == FALSE\n"));
                    return( fnEmitErr( INVALID_TYPE_EXPRESSION ) );
                }
            }
            opnd2->explicit = TRUE;
            /* v2.02: if operand is a register, make sure
             * that invalid combinations ("DWORD PTR AX") are flagged.
             *
             * v2.10: must also be checked inside []. However, it's
             * a problem to properly handle this case, since opnd->indirect
             * is just a flag.
             * Curr. hackish fix: to query state of assumecheck if indirect==TRUE.
             * Proposed "good" fix: change EXPR_REG to EXPR_ADDR in
             * CheckAssume(), that is, when the terminating  ']' was found.
             */
            //if ( opnd2->kind == EXPR_REG && opnd2->indirect == FALSE ) {
            if ( opnd2->kind == EXPR_REG && ( opnd2->indirect == FALSE || opnd2->assumecheck == TRUE ) ) {
                temp = opnd2->base_reg->tokval;
                /* for segment registers, both size 2 and 4 is ok.*/
                if ( GetValueSp( temp ) & OP_SR ) {
                    if ( opnd1->value != 2 && opnd1->value != 4 ) {
                        DebugMsg(("calculate(PTR): segment register size (=2/4) doesn't match type size (=%u)\n", opnd1->value ));
                        return( fnEmitErr( INVALID_USE_OF_REGISTER ) );
                    }
				}

				else if ( (opnd1->mem_type == MT_REAL8 || opnd1->mem_type == MT_REAL4) && (GetValueSp(temp) & OP_XMM) ) {
					opnd2->mem_type = opnd1->mem_type;
					DebugMsg(("calculate(PTR): FLOAT/DOUBLE conversion of XMM register; %u != %u\n", SizeFromRegister(temp), opnd1->value));
				}
				else if ( opnd1->value != SizeFromRegister( temp ) ) {
                    DebugMsg(("calculate(PTR): register size doesn't match type size; %u != %u\n", SizeFromRegister( temp ), opnd1->value ));
                    return( fnEmitErr( INVALID_USE_OF_REGISTER ) );
                }
            } else if ( opnd2->kind == EXPR_FLOAT ) {
                if ( !( opnd1->mem_type & MT_FLOAT ) ) {
                    DebugMsg(("calculate(PTR): type memtype=%Xh ( MT_FLOAT not set, although right op is FLOAT )\n", opnd1->mem_type ));
                    return( fnEmitErr( REAL_OR_BCD_NUMBER_NOT_ALLOWED ) );
                }
            }
            opnd2->mem_type = opnd1->mem_type;
            opnd2->Ofssize  = opnd1->Ofssize;
            /* v2.04: added */
            if ( opnd2->is_type )
                opnd2->value  = opnd1->value;

            /* todo: describe which case is handled here. How is the left
             * operand of PTR supposed to get an override? And why is
             * it necessary to change kind to EXPR_ADDR here? */
            if ( opnd1->override != NULL ) {
                if ( opnd2->override == NULL )
                    opnd2->override = opnd1->override;
                opnd2->kind = EXPR_ADDR;
            }
            //if ( opnd1->mbr )
            //    opnd2->mbr = opnd1->mbr;
            //if ( opnd1->sym )
            //    opnd2->sym = opnd1->sym;
            //opnd2->instr = opnd1->instr;

            /* note: member type isn't copied, IOW: value of opnd1->type is kept. */
            TokenAssign( opnd1, opnd2 );
            break;
        }

        MakeConst( opnd1 );
        MakeConst( opnd2 );

        if ( check_same( opnd1, opnd2, EXPR_CONST ) )
            ;
        /* if it's EQ, NE, LE [, ...], operands may be either constants
         or relocatable labels */
        else if ( oper->precedence == CMP_PRECEDENCE &&
                 opnd1->kind != EXPR_CONST ) {
            if ( opnd1->kind == EXPR_ADDR && opnd1->indirect == FALSE && opnd1->sym )
                if ( opnd2->kind == EXPR_ADDR && opnd2->indirect == FALSE && opnd2->sym ) {
                    if ( MakeConst2( opnd1, opnd2 ) == ERROR ) {
                        DebugMsg(("calculate(%s) error 1\n", oper->string_ptr ));
                        return( ERROR );
                    }
                } else {
                    DebugMsg(("calculate(%s) error 2, token2.kind=%d indirect=%u sym=%s\n",
                              oper->string_ptr, opnd2->kind, opnd2->indirect,
                              opnd2->sym ? opnd2->sym->name : "NULL" ));
                    return( fnEmitErr( OPERAND_MUST_BE_RELOCATABLE ) );
                }
            else {
                DebugMsg(("calculate(%s) error 3\n", oper->string_ptr ));
                return( fnEmitErr( CONSTANT_OR_RELOCATABLE_LABEL_EXPECTED ) );
            }
        } else {
            DebugMsg(("calculate(%s) error 4\n", oper->string_ptr ));
            return( ConstError( opnd1, opnd2 ) );
        }

        DebugMsg1(("calculate(%s): values=%" I64_SPEC "d/%" I64_SPEC "d is_type=%u/%u memtypes=%X/%X\n", oper->string_ptr,
                   opnd1->value64, opnd2->value64, opnd1->is_type, opnd2->is_type, opnd1->mem_type, opnd2->mem_type  ));
        switch( oper->tokval ) {
        case T_EQ:
#if 1 /* v2.03: added */
            /* if both operands are types, do a more comprehensive comparison! */
            if ( opnd1->is_type && opnd2->is_type ) {
                cmp_types( opnd1, opnd2, -1 );
            } else
#endif
            opnd1->value64 = ( opnd1->value64 == opnd2->value64 ? -1:0 );
            break;
        case T_NE:
#if 1 /* v2.03: added */
            /* if both operands are types, do a more comprehensive comparison! */
            if ( opnd1->is_type && opnd2->is_type ) {
                cmp_types( opnd1, opnd2, 0 );
            } else
#endif
            opnd1->value64 = ( opnd1->value64 != opnd2->value64 ? -1:0 );
            break;
        case T_LT:
            opnd1->value64 = ( opnd1->value64 <  opnd2->value64 ? -1:0 );
            break;
        case T_LE:
            opnd1->value64 = ( opnd1->value64 <= opnd2->value64 ? -1:0 );
            break;
        case T_GT:
            opnd1->value64 = ( opnd1->value64 >  opnd2->value64 ? -1:0 );
            break;
        case T_GE:
            opnd1->value64 = ( opnd1->value64 >= opnd2->value64 ? -1:0 );
            break;
        case T_MOD:
            if ( opnd2->llvalue == 0 ) {
                return( fnEmitErr( DIVIDE_BY_ZERO_IN_EXPR ) );
            } else
                opnd1->llvalue %= opnd2->llvalue;
            break;
        case T_SHL:
            /* v2.04: check for shift count < 0 */
            DebugMsg1(("calculate(SHL): value=%" I64_SPEC "X << %" I32_SPEC "u (max=%u)\n", opnd1->llvalue, opnd2->value, 8 * sizeof( opnd1->llvalue ) ));
            if ( opnd2->value < 0 )
                fnEmitErr( COUNT_MUST_BE_POSITIVE_OR_ZERO );
            else if ( opnd2->value >= ( 8 * sizeof( opnd1->llvalue ) ) )
                opnd1->llvalue = 0;
            else
                opnd1->llvalue = opnd1->llvalue << opnd2->value;
            /* v2.01: result is 64-bit only if mode is USE64 */
            /* v2.06: for -Zm only. This is not entirely correct,
             * since Masm v6x also does 32-bit shifts, but since v2.06
             * Uasm intends to behave like Masm v8+.
             * Might be better to implement OPTION EXPR16|32|64.
             */
            //if ( ModuleInfo.Ofssize <= USE32 ) {
            if ( ModuleInfo.m510 ) {
                opnd1->hvalue = 0;
                opnd1->hlvalue = 0;
            }
            break;
        case T_SHR:
            /* Masm v8 works with unsigned 64-bit,
             * Masm v6 masks shift count with 0x3F.
             * v2.04: does behave like Masm v8+.
             * there is a problem with some compilers if shift
             * count is >= 64. So in this case the result is zeroed manually
             */
	            if ( opnd2->value < 0 )
		             fnEmitErr( COUNT_MUST_BE_POSITIVE_OR_ZERO );
	            else if ( opnd2->value >= ( 8 * sizeof( opnd1->llvalue ) ) )
		             opnd1->llvalue = 0;
	            else {
                /* Nidud fix v2.28*/
		            if ( opnd1->value == -1 && ModuleInfo.Ofssize == USE32 )
		              opnd1->llvalue = (unsigned long)opnd1->llvalue >> opnd2->value;
		           else
		             opnd1->llvalue = opnd1->llvalue >> opnd2->value;
	            }
	            break;
        case T_AND:
            opnd1->llvalue &= opnd2->llvalue;
            break;
        case T_OR:
            opnd1->llvalue |= opnd2->llvalue;
            break;
        case T_XOR:
            opnd1->llvalue ^= opnd2->llvalue;
            break;
        }
        break; /* end case T_BINARY_OPERATOR */
    case T_UNARY_OPERATOR:
        DebugMsg1(("calculate(%s [T_UNARY_OPERATOR]): opnd2 kind=%d sym=%s mbr=%s type=%s memtype=%X is_type=%u indirect=%u\n",
                   oper->string_ptr,
                   opnd2->kind,
                   opnd2->sym ? opnd2->sym->name : "NULL",
                   opnd2->mbr ? opnd2->mbr->name : "NULL",
                   opnd2->type ? opnd2->type->name : "NULL",
                   opnd2->mem_type, opnd2->is_type, opnd2->indirect ));
        /* NOT is an instruction and hence has no valid
         * value to be returned by GetValueSp() or GetSflagsSp()!
         */
        if( oper->tokval == T_NOT ) {
            MakeConst( opnd2 );
            if( opnd2->kind != EXPR_CONST ) {
                DebugMsg(("calculate(%s) error 1\n", oper->string_ptr ));
                return( fnEmitErr( CONSTANT_OPERAND_EXPECTED ) );
            }
            TokenAssign( opnd1, opnd2 );
            opnd1->llvalue = ~(opnd2->llvalue);
            break;
        }

        /* operator         accepts
         ----------------------------------------------
         SIZEOF/SIZE        label, type, struct field
         LENGTHOF/LENGTH    label, struct field
         TYPE               label, type, struct field, register, number
         LOW                constant, label (OMF+BIN only)
         HIGH               constant, label (OMF+BIN only)
         LOWWORD            constant, label
         HIGHWORD           constant
         LOW32              constant, label, float
         HIGH32             constant, float
         THIS               type
         OPATTR/.TYPE       label, type, struct field, register, number
         SHORT              label
         SEG                label
         OFFSET/LROFFSET    label, struct field, number
         IMAGEREL           label
         SECTIONREL         label
         WIDTH/MASK         bitfields or RECORD type
         */

        temp = GetValueSp( oper->tokval );

        sym = opnd2->sym;
        if( opnd2->mbr != NULL )
            sym = opnd2->mbr;

        /* for error displays, get the position of the operand that
         * caused the trouble.
         */
        if ( opnd2->instr != EMPTY )
            name = oper->tokpos + strlen( oper->string_ptr ) + 1;
        else if ( sym )
            name = sym->name;
        else if ( opnd2->base_reg != NULL && opnd2->indirect == FALSE )
            name = opnd2->base_reg->string_ptr;
        else
            name = oper->tokpos + strlen( oper->string_ptr ) + 1;

        switch ( opnd2->kind ) {
        case EXPR_CONST:
            /* v2.05: conditions "struct-field" and "istype" exchanged */
            /* is item a struct field? */
            /* v2.10: fixme: EXPR_CONST & mbr!=NULL - what's that supposed to be? */
            if ( opnd2->mbr != NULL && opnd2->mbr->state != SYM_TYPE ) {
                if ( opnd2->mbr->mem_type == MT_BITS ) { /* bitfield? */
                    if ( ( temp & AT_BF ) == 0 ) {
                        return( invalid_operand( opnd2, oper->string_ptr, name ) );
                    }
                } else {
                    if ( ( temp & AT_FIELD ) == 0 ) {
                        return( invalid_operand( opnd2, oper->string_ptr, name ) );
                    }
                }
            } else if ( opnd2->is_type ) { /* is item a type? */
                if ( ( temp & AT_TYPE ) == 0 ) {
                    return( invalid_operand( opnd2, oper->string_ptr, name ) );
                }
            } else { /*  or is it a number? */
                if ( ( temp & AT_NUM ) == 0 ) {
                    return( invalid_operand( opnd2, oper->string_ptr, name ) );
                }
            }
            break;
        case EXPR_ADDR:
            /* an indirect memory operand? (not an auto variable) */
            if ( opnd2->indirect == TRUE && opnd2->sym == NULL ) {
                if ( ( temp & AT_IND ) == 0 ) {
                    return( invalid_operand( opnd2, oper->string_ptr, name ) );
                }
            } else {
                if ( ( temp & AT_LABEL ) == 0 ) {
                    return( invalid_operand( opnd2, oper->string_ptr, name ) );
                }
            }
#if 0 /* v2.08: this if() obsolete? */
            if( opnd2->instr != EMPTY ) {
                /* if instr is set, it's not a full address */
                switch ( oper->tokval ) {
                case T_LOW:
                case T_HIGH:
                case T_LOWWORD:
                case T_HIGHWORD:
#if LOHI32
                case T_LOW32:
                case T_HIGH32:
#endif
                case T_TYPE:
                case T_OPATTR:
                case T_DOT_TYPE:
                case T_OFFSET: /* v2.08: added, to allow OFFSET OFFSET <addr> */
                    break;
                default:
                    /* remaining: OFFSET, LROFFSET, IMAGEREL, SECTIONREL, SEG,
                     * SHORT
                     * THIS (won't set opnd.instr)
                     * (SIZE, SIZEOF, LENGTH, LENGHTOF, MASK, WIDTH) -> EXPR_CONST
                     *
                     */
                    DebugMsg(("calculate %s error 2\n", oper->string_ptr ));
                    return( fnEmitErr( LABEL_EXPECTED ) );
                }
            }
#endif
            break;
        case EXPR_REG:
            if ( ( temp & AT_REG ) == 0 ) {
                return( invalid_operand( opnd2, oper->string_ptr, name ) );
            }
            break;
        case EXPR_FLOAT: /* v2.05: added */
            if ( ( temp & AT_FLOAT ) == 0 ) {
                DebugMsg(("calculate %s 'float' error\n", oper->string_ptr ));
                return( fnEmitErr( REAL_OR_BCD_NUMBER_NOT_ALLOWED ) );
            }
            break;
        }
#ifdef DEBUG_OUT
        if ( unaryop[ GetSflagsSp( oper->tokval ) ]( oper->tokval, opnd1, opnd2, sym, name ) == ERROR )
            return( ERROR );
        break;
#else
        return( unaryop[ GetSflagsSp( oper->tokval ) ]( oper->tokval, opnd1, opnd2, sym, name ) );
#endif
    //case T_RES_ID:
    default: /* shouldn't happen */
        DebugMsg(("calculate(%s): unknown operator\n", oper->string_ptr ));
        return( fnEmitErr( SYNTAX_ERROR_EX, oper->string_ptr ) );
    } /* end switch( oper->token ) */

#ifdef DEBUG_OUT
    if ( opnd1->hlvalue ) {
        DebugMsg1(("%u calculate(%s) exit, ok kind=%d value=0x%" I64_SPEC "X_%016" I64_SPEC "X memtype=0x%X indirect=%u type=>%s<\n",
                   evallvl,
                   oper->string_ptr,
                   opnd1->kind,
                   opnd1->hlvalue, opnd1->llvalue,
                   opnd1->mem_type,
                   opnd1->indirect, opnd1->type ? opnd1->type->name : "NULL" ));
    } else if ( opnd1->hvalue ) {
        DebugMsg1(("%u calculate(%s) exit, ok kind=%d value=%" I64_SPEC"d(0x%" I64_SPEC "X) memtype=0x%X indirect=%u type=>%s<\n",
                   evallvl,
                   oper->string_ptr,
                   opnd1->kind,
                   opnd1->llvalue, opnd1->llvalue,
                   opnd1->mem_type,
                   opnd1->indirect, opnd1->type ? opnd1->type->name : "NULL" ));
    } else {
        DebugMsg1(("%u calculate(%s) exit, ok kind=%d value=%d(0x%X) memtype=0x%X ind=%u exp=%u type=%s mbr=%s\n",
                   evallvl,
                   oper->string_ptr,
                   opnd1->kind,
                   opnd1->value, opnd1->value,
                   opnd1->mem_type,
                   opnd1->indirect, opnd1->explicit,
                   opnd1->type ? opnd1->type->name : "NULL",
                   opnd1->mbr ? opnd1->mbr->name : "NULL" ));
    }
#endif
    return( NOT_ERROR );
}

/* this code runs BEFORE the - right - operand of an operator is read */

static void PrepareOp( struct expr *opnd, const struct expr *old, const struct asm_tok *oper )
/********************************************************************************************/
{
    opnd->is_opattr = old->is_opattr;

    switch ( oper->token ) {
    case T_DOT:
        DebugMsg(("PrepareOp: DOT operator found, old.sym=%X, old.type=%s, expr=%s\n", old->sym, (old->type ? old->type->name : "NULL" ), oper->tokpos + strlen( oper->string_ptr ) ));
        if ( old->type ) {
            DebugMsg1(("PrepareOp: implicit type: %s\n", old->type->name));
            opnd->type = old->type;
            opnd->is_dot = TRUE;
#if 0
        /* v2.09 (type field is now set in get_operand();
         * it's problematic to use old->sym here, because this field
         * is not necessarily set by the operand just before the dot.
         */
        //} else if ( old->sym && old->sym->mem_type == MT_TYPE ) {
        } else if ( old->sym && old->sym->mem_type == MT_TYPE && old->instr == EMPTY ) {
            DebugMsg1(("PrepareOp: label %s, implicit type: %s\n", old->sym->name, old->sym->type->name));
            for ( opnd->type = old->sym->type; opnd->type->type; opnd->type = opnd->type->type );
#endif
        /* v2.07: changed */
        //} else if ( !ModuleInfo.oldstructs ) {
        /* v2.08: reverted, replaced by changes in dot_op() and get_operand(), case T_STYPE */
        //} else if ( old->sym && old->sym->mem_type == MT_EMPTY && !ModuleInfo.oldstructs ) {
        /* v2.11: nullstruct not used here. Set type to NULL and is_dot==TRUE */
        //} else if ( !ModuleInfo.oldstructs ) {
        } else if ( !ModuleInfo.oldstructs && old->sym && old->sym->state == SYM_UNDEFINED ) {
            DebugMsg1(("PrepareOp: forward ref to %s, type will be NULL\n", old->sym->name ));
            opnd->type = NULL;
            opnd->is_dot = TRUE;
        }
        break;
    case T_UNARY_OPERATOR:
        switch ( oper->tokval ) {
        case T_OPATTR:
        case T_DOT_TYPE:
            DebugMsg(("PrepareOp: OPATTR operator found, old.sym=%X, old.type=%s, expr=%s\n",
                      old->sym, (old->type ? old->type->name : "NULL" ), oper->tokpos + strlen( oper->string_ptr ) ));
            opnd->is_opattr = TRUE;
            break;
        }
        break;
    }
}

static void OperErr( int i, struct asm_tok tokenarray[] )
/*******************************************************/
{
    if ( tokenarray[i].token <= T_BAD_NUM ) {
        fnEmitErr( MISSING_OPERATOR_IN_EXPRESSION ); ERRLOC(i);
    } else
        fnEmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr );

    return;
}

#define IsCurrToken( tok )  ( tokenarray[*i].token == tok )

static ret_code evaluate( struct expr *opnd1, int *i, struct asm_tok tokenarray[], int end, const uint_8 flags )
/********************************************************************************************************************/
{
    ret_code rc = NOT_ERROR;
    char *p;
    char *p1;
	char clabel[100];
	struct asym *labelsym;
	struct asym *labelsym2;
	struct asm_tok tok;
    struct dsym *recordsym;
    
    DebugMsg1(("%u evaluate(i=%d, end=%d, flags=%X) enter [opnd1: kind=%d type=%s]\n",
               ++evallvl, *i, end, flags, opnd1->kind, opnd1->type ? opnd1->type->name : "NULL" ));

    /* v2.07: this function has been "simplified".
     * it's ensured now that if any operator is involved
     * - including () and [] - then calculate() will be called.
     * v2.10: removed the 'return( ERROR )' branches, to make
     * OPATTR work better.
     * v2.10: loop changed from 'do {} while' to 'while () {}'.
     * v2.10: 'flags' argument contains "inside []" information.
     */

	/* Allow .labelname to be used as an operand */
	if ( (tokenarray[*i].token == T_DOT && tokenarray[(*i) + 1].token == T_ID) && opnd1->kind != EXPR_REG )
	{
		// check that T_ID is a label
		sprintf(clabel, "%s%s", ".", tokenarray[(*i) + 1].string_ptr);
		labelsym = SymFind(clabel);
		labelsym2 = SymFind(tokenarray[(*i)+1].string_ptr);

		if ((*i) > 0)
		{
			tok = tokenarray[(*i) - 1];
		}
		if (labelsym != NULL || 
			(labelsym == NULL && tok.token != T_ID && tok.token != T_CL_SQ_BRACKET && tok.token != T_CL_BRACKET) ||
			(labelsym != NULL && labelsym->label))
		{
			(*i)++;
			strcpy(clabel, tokenarray[(*i)].string_ptr);
			sprintf(tokenarray[(*i)].string_ptr, "%s%s", ".", &clabel);
		}
		else if (labelsym == NULL && labelsym2 == NULL)
		{
			
		} 
	}
	if ((tokenarray[*i].tokval == T_SHORT || tokenarray[*i].tokval == T_OFFSET) && tokenarray[(*i) + 1].token == T_DOT && tokenarray[(*i) + 2].token == T_ID)
	{
		// check that T_ID is a label
		sprintf(clabel, "%s%s", ".", tokenarray[(*i) + 2].string_ptr);
		labelsym = SymFind(clabel);
		labelsym2 = SymFind(tokenarray[(*i) + 2].string_ptr);

		if ((*i) > 0)
		{
			tok = tokenarray[(*i) - 1];
		}
		if (labelsym != NULL ||
			(labelsym == NULL && tok.token != T_ID && tok.token != T_CL_SQ_BRACKET && tok.token != T_CL_BRACKET) ||
			(labelsym != NULL && labelsym->label))
		{
			//(*i)++;
			strcpy(clabel, tokenarray[(*i)+2].string_ptr);
			sprintf(tokenarray[(*i)+2].string_ptr, "%s%s", ".", &clabel);
			tokenarray[(*i) + 1].string_ptr = tokenarray[(*i) + 2].string_ptr;
			tokenarray[(*i) + 1].token = T_ID;
			tokenarray[(*i) + 2].token = T_FINAL;
			end--;
		}
		else if (labelsym == NULL && labelsym2 == NULL)
		{

		}
	}
	

	/*
	* First token may be either an unary operator or an operand
	*/
	if ( opnd1->kind == EXPR_EMPTY &&  !is_unary_op( tokenarray[*i].token ) ) {
        rc = get_operand( opnd1, i, tokenarray, flags );
    }
    /* now handle operators. */
    while ( rc == NOT_ERROR && *i < end && !IsCurrToken( T_CL_BRACKET ) && !IsCurrToken( T_CL_SQ_BRACKET ) ) {

        int curr_operator;
        struct expr opnd2;
        struct expr opnd3;
        curr_operator = *i;
        DebugMsg1(("%u evaluate loop, operator=>%s< opnd1->sym=%X, type=%s\n",
                   evallvl, tokenarray[curr_operator].string_ptr, opnd1->sym, (opnd1->type ? opnd1->type->name : "NULL") ));
        if ( opnd1->kind != EXPR_EMPTY ) {
            /* check operator behind operand. Must be binary or open bracket */
            if ( tokenarray[curr_operator].token == '+' || tokenarray[curr_operator].token == '-' )
                tokenarray[curr_operator].specval = BINARY_PLUSMINUS;
            else if( !is_operator( tokenarray[curr_operator].token ) || tokenarray[curr_operator].token == T_UNARY_OPERATOR ) {
                DebugMsg(("%u evaluate: unexpected token at idx=%u, token=%X >%s<\n", evallvl, curr_operator, tokenarray[curr_operator].token, tokenarray[curr_operator].tokpos ));
                rc = ERROR;
                //if ( !opnd2.is_opattr )  /* v2.11: opnd2 was accessed before initialization */
                if (!opnd1->is_opattr)
				{
					if (opnd1->type != NULL)
					{
						recordsym = SymSearch(opnd1->type->name);
						/* if it is a RECORD don't throw an error but decorate it with an actual value v2.41*/
						if (recordsym && recordsym->sym.typekind == TYPE_RECORD)
						{
							if (InitRecordVar(opnd1, curr_operator, tokenarray, recordsym) != ERROR)
								rc = NOT_ERROR;
							return(rc);
						}
						else
							OperErr(curr_operator, tokenarray);
					}
					else
						OperErr(curr_operator, tokenarray);
                }
                break;
            }
        }

        (*i)++;

        init_expr( &opnd2 );
        PrepareOp( &opnd2, opnd1, &tokenarray[curr_operator] );

        /* read the (next) operand.
         */

        if( tokenarray[curr_operator].token == T_OP_BRACKET ||
           tokenarray[curr_operator].token == T_OP_SQ_BRACKET ) {
            int exp_token = T_CL_BRACKET;
            if( tokenarray[curr_operator].token == T_OP_SQ_BRACKET ) {
                exp_token = T_CL_SQ_BRACKET;
#if 1 /* v2.10: slightly hackish; see regression test dotop5.asm */
            } else if ( opnd1->is_dot ) {
                opnd2.type = opnd1->type;
                opnd2.is_dot = TRUE;
#endif
            }

            rc = evaluate( &opnd2, i, tokenarray, end, ( flags | ( exp_token == T_CL_SQ_BRACKET ? EXPF_IN_SQBR : 0 ) ) & ~EXPF_ONEOPND );

            if( !IsCurrToken( exp_token ) ) {
                DebugMsg(("%u evaluate: error, missing '%c', i=%u\n", evallvl, exp_token, *i ));
                if ( rc != ERROR ) {
                    fnEmitErr( MISSING_RIGHT_PARENTHESIS_IN_EXPRESSION );
                    /* v2.12: if curr token is a comma, the intention might be to call a macro function
                     * - using an undefined ( or not yet defined ) macro. The problem is that the name
                     * of this undefined macro isn't displayed in pass one, making it hard to see the
                     * reason for the error msg. However, if a comma is found, then it's surely no valid
                     * expression - in this case an "undefined symbol" err msg may be helpful.
                     */
                    if ( IsCurrToken( T_COMMA ) && opnd1->sym && opnd1->sym->state == SYM_UNDEFINED )
                        fnEmitErr( SYMBOL_NOT_DEFINED, opnd1->sym->name );
                }
                rc = ERROR;
            } else {
                (*i)++;
            }

        } else if( is_unary_op( tokenarray[*i].token ) ) { /* brackets, +, -, T_UNARY_OPERATOR? */
            rc = evaluate( &opnd2, i, tokenarray, end, flags | EXPF_ONEOPND );
        } else {
            /* get either:
             * - operand of unary operator OR
             * - 2. operand of binary operator
             */
            rc = get_operand( &opnd2, i, tokenarray, flags );
        }

        /*
         * parse expression until either the end or an operator with a higher priority is found.
         */

        while( rc != ERROR && *i < end && !IsCurrToken( T_CL_BRACKET ) && !IsCurrToken( T_CL_SQ_BRACKET ) ) {
            
            if ( tokenarray[*i].token == '+' || tokenarray[*i].token == '-' )
                tokenarray[*i].specval = BINARY_PLUSMINUS;
            else if( !is_operator( tokenarray[*i].token ) || tokenarray[*i].token == T_UNARY_OPERATOR ) {
                DebugMsg(("%u evaluate: unexpected token at %u, token=%X >%s<\n", evallvl, *i, tokenarray[*i].token, tokenarray[*i].tokpos ));
                rc = ERROR;
                if ( !opnd2.is_opattr ) /* don't emit error if expression is OPATTR operand */
                    OperErr( *i, tokenarray );
                break;
            }

            if( get_precedence( &tokenarray[*i] ) >= get_precedence( &tokenarray[curr_operator] ) )
                break;

            rc = evaluate( &opnd2, i, tokenarray, end, flags | EXPF_ONEOPND );

        }

        /* v2.10: OPATTR special handling */
        if ( rc == ERROR && opnd2.is_opattr ) {
            /* skip tokens until the end */
            while( *i < end && !IsCurrToken( T_CL_BRACKET ) && !IsCurrToken( T_CL_SQ_BRACKET ) ) {
                (*i)++;
            }
            opnd2.kind = EXPR_EMPTY;
            rc = NOT_ERROR;
        }
        if (rc != ERROR){
            rc = calculate( opnd1, &opnd2, &tokenarray[curr_operator] );
          }
        /* here we get the mask 128 v2.45  */
          p1 = tokenarray[3].string_ptr;
          if ((*p1 & 0xdf) == 'M') {    
            if (0 == _memicmp(p1, "MASK", 4)) {
              if (0 == _memicmp(tokenarray[1].string_ptr, "xmm", 3)) {
                if (GetMask128(opnd1, 3, tokenarray) != ERROR)
                  rc = NOT_ERROR;
                opnd2.kind = EXPR_ADDR;
                opnd2.mem_type = MT_OWORD;
              }
            }
          }
        if( flags & EXPF_ONEOPND ) /* stop after one operand? */
           break;
    }

#ifdef DEBUG_OUT
    if ( opnd1->hvalue != -1 && opnd1->hvalue != 0 ) {
        DebugMsg1(("%u evaluate exit, rc=%d, kind=%d value=%" I64_SPEC "d(0x%" I64_SPEC "X) memtype=%Xh string=%s indirect=%u type=>%s<\n",
                   evallvl--, rc, opnd1->kind, opnd1->llvalue, opnd1->llvalue, opnd1->mem_type,
                   opnd1->quoted_string ? opnd1->quoted_string->string_ptr : "NULL",
                   opnd1->indirect,
                   opnd1->type ? opnd1->type->name : "NULL" ));
    } else {
        DebugMsg1(("%u evaluate exit, rc=%d, kind=%d value=%" I32_SPEC "d(0x%" I32_SPEC "X) memtype=%Xh string=%s ind=%u exp=%u ofssiz=%d instr=%s type=>%s<\n",
                   evallvl--, rc, opnd1->kind, opnd1->value, opnd1->value, opnd1->mem_type,
                   opnd1->quoted_string ? opnd1->quoted_string->string_ptr : "NULL",
                   opnd1->indirect, opnd1->explicit, opnd1->Ofssize,
                   opnd1->instr == EMPTY ? "" : GetResWName( opnd1->instr, NULL ),
                   opnd1->type ? opnd1->type->name : "NULL" ));
    }
#endif
    return( rc );
}

static bool is_expr_item( struct asm_tok *item )
/**********************************************/
/* Check if a token is a valid part of an expression.
 * chars + - * / . : [] and () are operators.
 * also done here:
 * T_INSTRUCTION  SHL, SHR, AND, OR, XOR changed to T_BINARY_OPERATOR
 * T_INSTRUCTION  NOT                    changed to T_UNARY_OPERATOR
 * T_DIRECTIVE    PROC                   changed to T_STYPE
 * for the new operators the precedence is set.
 * DUP, comma or other instructions or directives terminate the expression.
 */
{
    switch( item->token ) {
    case T_INSTRUCTION:
        switch( item->tokval ) {
        case T_SHL:
        case T_SHR:
            item->token = T_BINARY_OPERATOR;
            item->precedence = 8;
            return( TRUE );
        case T_NOT:
            item->token = T_UNARY_OPERATOR;
            item->precedence = 11;
            return( TRUE );
        case T_AND:
            item->token = T_BINARY_OPERATOR;
            item->precedence = 12;
            return( TRUE );
        case T_OR:
        case T_XOR:
            item->token = T_BINARY_OPERATOR;
            item->precedence = 13;
            return( TRUE );
        }
        return( FALSE );
    case T_RES_ID:
        if ( item->tokval == T_DUP ) /* DUP must terminate the expression */
            return( FALSE );
        break;
    case T_DIRECTIVE:
        /* PROC is converted to a type */
        if ( item->tokval == T_PROC ) {
            item->token = T_STYPE;
            /* v2.06: avoid to use ST_PROC */
            //item->bytval = ST_PROC;
            item->tokval = ( ( SIZE_CODEPTR & ( 1 << ModuleInfo.model ) ) ? T_FAR : T_NEAR );
            return( TRUE );
        }
        /* fall through. Other directives will end the expression */
    case T_COMMA:
    //case T_FLOAT: /* v2.05: floats are now handled */
    //case T_QUESTION_MARK: /* v2.08: no need to be handled here */
        return( FALSE );
    }
    return( TRUE );
}

static int noEmitErr( int msg, ... )
/**********************************/
{
    return( ERROR );
}

/* evaluate an operand
 * start_tok: index of first token of expression
 * end_tok:   index of last  token of expression
 */
ret_code EvalOperand( int *start_tok, struct asm_tok tokenarray[], int end_tok, struct expr *result, uint_8 flags )
/*****************************************************************************************************************/
{
    int         i;

    DebugMsg1(("EvalOperand(start=%u, end=%u, flags=%X) enter: >%s<\n", *start_tok, end_tok, flags, tokenarray[*start_tok].tokpos ));

    init_expr( result );

    for( i = *start_tok; ( i < end_tok ) && is_expr_item( &tokenarray[i] ); i++ );
    if ( i == *start_tok )
        return( NOT_ERROR );

    /* v2.10: global flag 'error_msg' replaced by 'fnEmitErr()' */
    fnEmitErr = ( ( flags & EXPF_NOERRMSG ) ? noEmitErr : EmitErr );
    return ( evaluate( result, start_tok, tokenarray, i, flags ) );
}

ret_code EmitConstError( const struct expr *opnd )
/************************************************/
{
    if ( opnd->hlvalue != 0 )
        EmitErr( CONSTANT_VALUE_TOO_LARGE_EX, opnd->hlvalue, opnd->value64 );
    else
        EmitErr( CONSTANT_VALUE_TOO_LARGE, opnd->value64 );
    return( ERROR );
}

/* global init (called once for each module) */

void ExprEvalInit( void )
/***********************/
{
    thissym = NULL;
    nullstruct = NULL;
    nullmbr = NULL;
}
