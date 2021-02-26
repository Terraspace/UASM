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
* Description:  tokenizer.
*
****************************************************************************/

#include <ctype.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "condasm.h"
#include "reswords.h"
#include "input.h"
#include "segment.h"
#include "listing.h"
#include "tokenize.h"
#include "fastpass.h"
#include "myassert.h"
#include "pseudoFilter.h"

#define CONCATID 0 /* 0=most compatible (see backsl.asm) */
#define MASMNUMBER 1 /* 1=Masm-compatible number scanning */
#ifdef __I86__
#define TOKSTRALIGN 0 /* 0=don't align token strings */
#else
#define TOKSTRALIGN 1 /* 1=align token strings to sizeof(uint_32) */
#endif
#define T_CLWB clwb
#ifndef DOTNAMEX /* v2.08: added */
/* set DOTNAMEX to 1 if support for Intel C++ generated assembly code
 * is to be enabled.
 */
#define DOTNAMEX 0
#endif

extern struct ReservedWord  ResWordTable[];

#ifdef DEBUG_OUT
int_32 cnttok0;
int_32 cnttok1;
extern struct asm_tok *end_tokenarray;
extern char           *end_stringbuf;
#endif

extern char    *token_stringbuf;  /* start token string buffer */
extern char    *commentbuffer;

/* v2.08: moved to struct line_status */
//static uint_8 g_flags; /* directive flags for current line */

#if !defined(__GNUC__) && !defined(__POCC__)
#define tolower(c) ((c >= 'A' && c <= 'Z') ? c | 0x20 : c )
#endif

/* strings for token 0x28 - 0x2F */
static const short stokstr1[] = {
    '(',')','*','+',',','-','.','/'};
/* strings for token 0x5B - 0x5D */
static const short stokstr2[] = {
    '[',0,']'};
/* test line concatenation if last token is a comma.
 * dont concat EQU, macro invocations or
 * - ECHO
 * - FORC/IRPC (v2.0)
 * - INCLUDE (v2.8)
 * lines!
 * v2.05: don't concat if line's an instruction.
 */
static bool IsMultiLine( struct asm_tok tokenarray[] )
/****************************************************/
{
    struct asym *sym;
    int i;

    if ( tokenarray[1].token == T_DIRECTIVE && tokenarray[1].tokval == T_EQU )
        return( FALSE );
    i = ( tokenarray[1].token == T_COLON ? 2 : 0 );
    /* don't concat macros */
    if ( tokenarray[i].token == T_ID ) {
        sym = SymSearch( tokenarray[i].string_ptr );
        if ( sym && ( sym->state == SYM_MACRO )
#if VARARGML
            && sym->mac_multiline == FALSE  /* v2.11: added */
#endif
           )
            return( FALSE );
    } else if ( tokenarray[i].token == T_INSTRUCTION ||
               ( tokenarray[i].token == T_DIRECTIVE &&
               ( tokenarray[i].tokval == T_ECHO ||
                tokenarray[i].tokval == T_INCLUDE ||
                tokenarray[i].tokval == T_FORC ||
                tokenarray[i].tokval == T_IRPC ) ) ) {
        return( FALSE );
    }
    return( TRUE );
}
/* EVEX Broadcast decorators are handled here */
void get_broads(struct line_status *p) {
	/************************************************/
	if (!evex)
		EmitError(UNAUTHORISED_USE_OF_EVEX_ENCODING);
  
	if (_memicmp(p->input, "1to2", 4) == 0) {
		broadflags = 0x10;           /*  ZLLBVAAA  */
		p->input += 4;               /*  00010000  */
	}
	else if (_memicmp(p->input, "1to4", 4) == 0){
      broadflags = 0x20;             /*  ZLLBVAAA  */
      p->input += 4;                 /*  00100000  */
    }
    else if (_memicmp(p->input, "1to8", 4) == 0){
      broadflags = 0x30;             /*  ZLLBVAAA  */
      p->input += 4;                 /*  00110000  */
    }
    else if (_memicmp(p->input, "1to16", 5) == 0){
      broadflags = 0x40;             /*  ZLLBVAAA  */
      p->input += 5;                 /*  01000000  */
    }
    else
      EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
    while ( isspace( *p->input )) p->input++;
    if (*p->input++ != '}')
      EmitError(DECORATOR_OR_BRACE_EXPECTED);
  }

/* EVEX Mask decorators are handled here: {k1) or {k1){z} or {z}{k1) or {z} */
void get_decos(struct line_status *p,bool zdeclined) 
{
	unsigned char c;
	struct        asym *sym = NULL;
	char          buff[32];
	char         *p1 = buff;

	if (!evex)
		EmitError(UNAUTHORISED_USE_OF_EVEX_ENCODING);
     while ( isspace( *p->input )) p->input++;
	c = (*p->input | 0x20);
  while ( isspace( *p->input )) p->input++;
	p->input++;
	/* if first decorator is {z}  */
  if (c == 'z' && *p->input == '}'){               /*  ZLLBVAAA  */
    if (!zdeclined)
      decoflags |= 0x80;                           /*  10000000  */
    else
      EmitError(Z_MASK_NOT_PERMITTED_WHEN_FIRST_OPERATOR_IS_MEMORY);
     c = *p->input;
     if (c != '}'){
       EmitError(DECORATOR_OR_BRACE_EXPECTED);
       return;
     }
     p->input++;
     while ( isspace( *p->input )) p->input++;
     c = *p->input;
     if (c != '{'){
       return;
     }
     p->input++;
     while ( isspace( *p->input )) p->input++;
     c = (*p->input | 0x20);
       p->input++;
     if (c != 'k')
         goto checkifvar;
     else if (*p->input > '7' || *p->input < '1')
         goto checkifvar;
     else{
       c = *p->input;
       if (c > '7' || c < '1'){
         EmitError(WRONG_MASK_REGISTER_NUBER);
         return;
       }
       decoflags |= (c & 0x7);
       p->input++;
       while ( isspace( *p->input )) p->input++;
       c = *p->input;
       if (c != '}'){
         EmitError(DECORATOR_OR_BRACE_EXPECTED);
         return;
       }
       p->input++;
     }
   }
   /* if first decorator is the mask register */
   else if (c == 'k'){
   c = *p->input;
     if (c > '7' || c < '1')
           goto checkifvar;
writenum:
     if (c > '7' || c < '1'){
       EmitError(WRONG_MASK_REGISTER_NUBER);
       return;
     }
     decoflags |= (c & 0x7);
     p->input++;
     while ( isspace( *p->input )) p->input++;
     c = *p->input;
     if (c != '}'){
       EmitError(DECORATOR_OR_BRACE_EXPECTED);
       return;
     }
     p->input++;
     /* check if there is more decorators */
     while ( isspace( *p->input )) p->input++;
     c = *p->input;
     if (c == '{'){
       p->input++;
       while ( isspace( *p->input )) p->input++;
       c = (*p->input | 0x20);
       if (c == 'z'){
          if (!zdeclined)
            decoflags |= 0x80;                           /*  10000000  */
          else
            EmitError(Z_MASK_NOT_PERMITTED_WHEN_FIRST_OPERATOR_IS_MEMORY);
         p->input++;
         while ( isspace( *p->input )) p->input++;
         c = *p->input;
         if (c != '}'){
           EmitError(DECORATOR_OR_BRACE_EXPECTED);
           return;
         }
         p->input++;
       }
       else {
         EmitError(TOO_MANY_DECORATORS);
         return;
       }
     }
   }
   /* check if equate or variable is used v2.46 */
    else { 
checkifvar:
      --p->input;                  /* return to the start of string */
      while (*p->input != '}'){    
        *p1++ = *p->input++;       /* copy the string to the buffer (alowed 32 chars ) */
        }
      *p1 = '\0';                  /* make it C string */
      sym = SymSearch(buff);       /* check if the variable is declared */
        if (sym == NULL){
          if (Parse_Pass)
          EmitError(TOO_MANY_DECORATORS);
          return;
          }
        else {
          p1 = sym->string_ptr;    /* sym->string_ptr contains the mask register */
          c = *p1++ | 0x20;
          if (c != 'k'){           /* if it is not the mask register throw an error */
          EmitError(TOO_MANY_DECORATORS);
          return;
            }
          else {                  
            c = *p1;               /* copy the reg number */
            --p->input;            /* ajust the pointer   */
            goto writenum;         /* go to write it      */
          }
        }
    }
}

static ret_code get_float( struct asm_tok *buf, struct line_status *p )
/*********************************************************************/
{
    /* valid floats look like:  (int)[.(int)][e(int)]
     * Masm also allows hex format, terminated by 'r' (3F800000r)
     */

    char    got_decimal = FALSE;
    char    got_e = FALSE;
    char    *ptr = p->input;

    for( ; *ptr != NULLC; ptr++ ) {
        char c = *ptr;
        if( isdigit( c ) ) {
            ;
        } else if ( c == '.' && got_decimal == FALSE ) {
            got_decimal = TRUE;
        } else if ( tolower( c ) == 'e' && got_e == FALSE ) {
            got_e = TRUE;
            /* accept e+2 / e-4 /etc. */
            if ( *(ptr+1) == '+' || *(ptr+1) == '-' )
                ptr++;
            /* it's accepted if there's no digit behind 'e' */
            //if ( !isdigit( *(ptr+1) ) )
            //    break;
        } else
            break;
    }

    buf->token = T_FLOAT;
    buf->floattype = NULLC;
    memcpy( p->output, p->input, ptr - p->input );
    p->output += ( ptr - p->input );
    *p->output++ = NULLC;
    p->input = ptr;

    /* the binary value isn't used currently */
    //*((float *)(&buf->value)) = atof( buf->string_ptr );

    return( NOT_ERROR );
}

static ret_code ConcatLine( char *src, int cnt, char *out, struct line_status *ls )
/*********************************************************************************/
{
    char *p = src+1;
    int max;

    while ( isspace(*p) ) p++;
    if ( *p == NULLC || *p == ';' ) {
        //char *buffer = GetAlignedPointer( out, strlen( out ) );
        char *buffer = out;
        if( GetTextLine( buffer ) ) {
            p = buffer;
            /* skip leading spaces */
            while ( isspace( *p ) ) p++;
            max = strlen( p );
            if ( cnt == 0 )
                *src++ = ' ';
            if ( ( src - ls->start ) + max >= MAX_LINE_LEN ) {
                EmitError( LINE_TOO_LONG );
                max = MAX_LINE_LEN - ( src - ls->start + 1 );
                *(p+max) = NULLC;
            }
            memcpy( src, p, max+1 );
            return( NOT_ERROR );
        }
    }
    return( EMPTY );
}

static ret_code get_string(struct asm_tok *buf, struct line_status *p)
/**********************************************************************/
{
  char    symbol_o;
  char    symbol_c;
  char    c;
  char    *src = p->input;
  char    *dst = p->output;
  char    *input1 = NULL;
  int     count = 0;
  int     level;

  symbol_o = *src;

  switch (symbol_o) {
  case '"':
  case '\'':
    buf->string_delim = symbol_o;
    *dst++ = symbol_o;
    src++;
    for (; count < MAX_STRING_LEN; src++, count++) {
      c = *src;
      if (c == symbol_o) { /* another quote? */
        *dst++ = c; /* store it */
        src++;
        if (*src != c)
          break; /* exit loop */
      /* a pair of quotes inside the string is
       * handled as a single quote */
      }
      else if (c == NULLC) {
        /* missing terminating quote, change to undelimited string */
        buf->string_delim = NULLC;
        count++; /* count the first quote */
        break;
      }
      else {
        *dst++ = c;
      }
    }
    break;  /* end of string marker is the same */
  case '{':
    input1 = p->input + 1;
    while (isspace(*input1)) input1++;
    if ((*input1 | 0x20) == 'z') {
      p->input++;
      get_decos(p, FALSE);    // mask decorators
      while (isspace(*p->input)) p->input++;
      if (*p->input == ',') {
        p->input++;
        buf->token = T_COMMA;
        return(NOT_ERROR);
      }
    }
    else if ((*input1 | 0x20) == 'k') {
      p->input++;
      get_decos(p, TRUE);    // mask decorators
      while (isspace(*p->input)) p->input++;
      if (*p->input == ',') {
        p->input++;
        buf->token = T_COMMA;
        return(NOT_ERROR);
      }
      //else 
      //  EmitError(TOO_MANY_DECORATORS);
    }
    else if (p->flags & TOK_NOCURLBRACES)
      goto undelimited_string;
  case '<':
    buf->string_delim = symbol_o;
    symbol_c = (symbol_o == '<' ? '>' : '}');
    src++;
    for (level = 0; count < MAX_STRING_LEN; ) {
      c = *src;
      if (c == symbol_o) { /* < or { ? */
        level++;
        *dst++ = c; src++;
        count++;
      }
      else if (c == symbol_c) { /* > or }? */
        if (level) {
          level--;
          *dst++ = c; src++;
          count++;
        }
        else {
          /* store the string delimiter unless it is <> */
          /* v2.08: don't store delimiters for {}-literals */
          //if (symbol_o != '<')
          //    *dst++ = c;
          src++;
          break; /* exit loop */
        }
#if 1
        /*
         a " or ' inside a <>/{} string? Since it's not a must that
         [double-]quotes are paired in a literal it must be done
         directive-dependant!
         see: IFIDN <">,<">
         */
      }
      else if ((c == '"' || c == '\'') && (p->flags2 & DF_STRPARM) == 0) {
        char delim = c;
        char *tdst;
        char *tsrc;
        int tcount;
        *dst++ = c; src++;
        count++;
        tdst = dst;
        tsrc = src;
        tcount = count;
        while (*src != delim && *src != NULLC && count < MAX_STRING_LEN - 1) {
          if (symbol_o == '<' && *src == '!' && *(src + 1) != NULLC)
            src++;
          *dst++ = *src++;
          count++;
        }
        if (*src == delim) {
          *dst++ = *src++;
          count++;
          continue;
        }
        else {
          /* restore values */
          src = tsrc;
          dst = tdst;
          count = tcount;
        }
#endif
      }
      else if (c == '!' && symbol_o == '<' && *(src + 1)) {
        /* handle literal-character operator '!'.
         * it makes the next char to enter the literal uninterpreted.
         */
         /* v2.09: don't store the '!' */
         //*dst++ = c; src++;
         //count++;
         //if ( count == MAX_STRING_LEN )
         //    break;
        src++;
        *dst++ = *src++;
        count++;
      }
      else if (c == '\\' &&  ConcatLine(src, count, dst, p) != EMPTY) {
        p->flags3 |= TF3_ISCONCAT;
      }
      else if (c == NULLC || (c == ';' && symbol_o == '{')) {
        if (p->flags == TOK_DEFAULT && ((p->flags2 & DF_NOCONCAT) == 0)) { /* <{ */
            /* if last nonspace character was a comma
             * get next line and continue string scan
             */
          char *tmp = dst - 1;
          while (isspace(*tmp)) tmp--;
          if (*tmp == ',') {
            DebugMsg1(("Tokenize.get_string: comma concatenation: %s\n", src));
            tmp = GetAlignedPointer(p->output, strlen(p->output));
            if (GetTextLine(tmp)) {
              /* skip leading spaces */
              while (isspace(*tmp)) tmp++;
              /* this size check isn't fool-proved yet */
              if (strlen(tmp) + count >= MAX_LINE_LEN) {
                EmitError(LINE_TOO_LONG);
                return(ERROR);
              }
              strcpy(src, tmp);
              continue;
            }
          }
        }
        src = p->input;
        dst = p->output;
        *dst++ = *src++;
        count = 1;
        goto undelimited_string;
      }
      else {
        *dst++ = c; src++;
        count++;
      }
    }
    break;
  default:
  undelimited_string:
    buf->string_delim = NULLC;
    /* this is an undelimited string,
     * so just copy it until we hit something that looks like the end.
     * this format is used by the INCLUDE directive, but may also
     * occur inside the string macros!
     */
     /* v2.05: also stop if a ')' is found - see literal2.asm regression test */
     //for( count = 0 ; count < MAX_STRING_LEN && *src != NULLC && !isspace( *src ) && *src != ',' && *src != ';'; ) {
    for (; count < MAX_STRING_LEN &&
      /* v2.08: stop also at < and % */
      //*src != NULLC && !isspace( *src ) && *src != ',' && *src != ';' && *src != ')'; ) {
      //*src && !isspace( *src ) && *src != ',' && *src != ')' && *src != '<' && *src != '%'; ) {
      *src && !islspace(*src) && *src != ',' && *src != ')' && *src != '%'; ) {
      if (*src == ';' && p->flags == TOK_DEFAULT)
        break;
      /* v2.11: handle '\' also for expanded lines */
      //if (  *src == '\\' && !( p->flags & TOK_NOCURLBRACES ) ) {
      if (*src == '\\' && (p->flags == TOK_DEFAULT || (p->flags & TOK_LINE))) {
        if (ConcatLine(src, count, dst, p) != EMPTY) {
          DebugMsg1(("Tokenize.get_string: backslash concatenation: >%s<\n", src));
          p->flags3 |= TF3_ISCONCAT;
          if (count)
            continue;
          return(EMPTY);
        }
      }
      /* v2.08: handle '!' operator */
      if (*src == '!' && *(src + 1) && count < MAX_STRING_LEN - 1)
        *dst++ = *src++;
      *dst++ = *src++;
      count++;
    }
    break;
  }

  if (count == MAX_STRING_LEN) {
    EmitError(STRING_OR_TEXT_LITERAL_TOO_LONG);
    return(ERROR);
  }
  *dst++ = NULLC;
  buf->token = T_STRING;
  buf->stringlen = count;
  p->input = src;
  p->output = dst;
  return(NOT_ERROR);
}

static ret_code get_special_symbol( struct asm_tok *buf, struct line_status *p )
/******************************************************************************/
{
    char    symbol;
    char    c;
    char    a=0;

    symbol = *p->input;
	buf->tokval = 0;
	switch( symbol ) {
    case ':' : /* T_COLON binary operator (0x3A) */
        p->input++;
        if ( *p->input == ':' ) {
            p->input++;
            buf->token = T_DBL_COLON;
            buf->string_ptr = "::";
        } else {
            buf->token = T_COLON;
            buf->string_ptr = ":";
        }
        break;
	case '-': 
		p->input++;
		if (*p->input == '>') {
			p->input++;
			buf->token = T_POINTER;
			buf->string_ptr = "->";
		}
		else {
			p->input--;
			goto minuslbl; // Handle a - binary operator the normal way.
		}
		break;
    case '%' : /* T_PERCENT (0x25) */
#if PERCENT_OUT
        /* %OUT directive? */
        if ( ( _memicmp( p->input+1, "OUT", 3 ) == 0 ) && !is_valid_id_char( *(p->input+4) ) ) {
            buf->token = T_DIRECTIVE;
            buf->tokval = T_ECHO;
            buf->dirtype = DRT_ECHO;
            memcpy( p->output, p->input, 4 );
            p->input += 4;
            p->output += 4;
            *(p->output)++ = NULLC;
            break;
        }
#endif
        p->input++;
        if ( p->flags == TOK_DEFAULT && p->index == 0 ) {
            p->flags3 |= TF3_EXPANSION;
            return( EMPTY );
        }
        buf->token = T_PERCENT;
        buf->string_ptr = "%";
        break;
    case '(' : /* 0x28: T_OP_BRACKET operator - needs a matching ')' */
        /* v2.11: reset c-expression flag if a macro function call is detected */
        if ( ( p->flags2 & DF_CEXPR ) && p->index && (buf-1)->token == T_ID ) {
            struct asym *sym = SymSearch( (buf-1)->string_ptr );
            if ( sym && ( sym->state == SYM_MACRO ) && sym->isfunc )
                p->flags2 &= ~DF_CEXPR;
        }
        /* no break */
    case ')' : /* 0x29: T_CL_BRACKET */
    case '*' : /* 0x2A: binary operator */
    case '+' : /* 0x2B: unary|binary operator */
    case ',' : /* 0x2C: T_COMMA */
    //case '-' : /* 0x2D: unary|binary operator */
    case '.' : /* 0x2E: T_DOT binary operator */
    case '/' : /* 0x2F: binary operator */
        minuslbl:
		/* all of these are themselves a token */
        p->input++;
        buf->token = symbol;
        buf->specval = 0; /* initialize, in case the token needs extra data */
        /* v2.06: use constants for the token string */
        buf->string_ptr = (char *)&stokstr1[symbol - '('];
        break;
    case '[' : /* T_OP_SQ_BRACKET operator - needs a matching ']' (0x5B) */
      a = '[';
    case ']' : /* T_CL_SQ_BRACKET (0x5D) */
        p->input++;
#if AVXSUPP
        while ( isspace( *p->input )) p->input++; 
        c = *p->input;
#endif
        buf->token = symbol;
        /* v2.06: use constants for the token string */
        buf->string_ptr = (char *)&stokstr2[symbol - '['];
#if AVXSUPP
        /* Intercept here '{' for EVEX mask or broadcast events 
         * it could be {k1}, ]{k1}{z}, {1to2},{1to4},{1to8},{1to16}
        */
        if (c == '{')
        {
          p->input++;
           while ( isspace( *p->input )) p->input++;
           if ((*p->input | 0x20) == 'z'){
            EmitError(Z_MASK_NOT_PERMITTED_WHEN_FIRST_OPERATOR_IS_MEMORY);
             return ERROR;
             }
          else if ((*p->input | 0x20) == 'k')
            get_decos( p, FALSE ) ;    // mask decorators
          else
            get_broads( p ) ;   // broadcast decorators
        }
        /* skip '+' if RIP is suppressed and index only used EG: [+xmm] v2.38 */
        else if (c == '+' && a == '[') p->input++;
#endif
        break;
    case '=' : /* (0x3D) */
        if ( *(p->input+1) != '=' ) {
            buf->token = T_DIRECTIVE;
            buf->tokval = T_EQU;
            buf->dirtype = DRT_EQUALSGN; /* to make it differ from EQU directive */
            buf->string_ptr = "=";
            p->input++;
            break;
        }
        /* fall through */
    default:
        /* detect C style operators.
         * DF_CEXPR is set if .IF, .WHILE, .ELSEIF or .UNTIL
         * has been detected in the current line.
         * will catch: '!', '<', '>', '&', '==', '!=', '<=', '>=', '&&', '||'
         * A single '|' will also be caught, although it isn't a valid
         * operator - it will cause a 'operator expected' error msg later.
         * the tokens are stored as one- or two-byte sized "strings".
         */
      if ( ( p->flags2 & DF_CEXPR ) && strchr( "=!<>&|", symbol ) ) {  
            *(p->output)++ = symbol;
            p->input++;
            buf->stringlen = 1;
            if ( symbol == '&' || symbol == '|' ) {
                if ( *p->input == symbol ) {
                    *(p->output)++ = symbol;
                    p->input++;
                    buf->stringlen = 2;
                }
            } else if ( *p->input == '=' ) {
                *(p->output)++ = '=';
                p->input++;
                buf->stringlen = 2;
            }
            buf->token = T_STRING;
            buf->string_delim = NULLC;
            *(p->output)++ = NULLC;
            break;
        }
        /* v2.08: ampersand is a special token */
        if ( symbol == '&' ) {
            p->input++;
            buf->token = '&';
            buf->string_ptr = "&";
            break;
        }
        /* anything we don't recognise we will consider a string,
         * delimited by space characters, commas, newlines or nulls
         */
        return( get_string( buf, p ) );
    }
    return( NOT_ERROR );
}

#if 0
static void array_mul_add( unsigned char *buf, unsigned base, unsigned num, unsigned size )
/*****************************************************************************************/
{
    while( size-- > 0 ) {
        num += *buf * base;
        *(buf++) = num;
        num >>= 8;
    }
}
#endif

/* read in a number.
 * check the number suffix:
 * b or y: base 2
 * d or t: base 10
 * h: base 16
 * o or q: base 8
 */
static ret_code get_number( struct asm_tok *buf, struct line_status *p )
/**********************************************************************/
{
    char                *ptr = p->input;
    char                *dig_start;
    char                *dig_end;
    unsigned            base = 0;
    unsigned            len;
    uint_32             digits_seen;
    char                last_char;

#define VALID_BINARY    0x0003
#define VALID_OCTAL     0x00ff
#define VALID_DECIMAL   0x03ff
#define OK_NUM( t )     ((digits_seen & ~VALID_##t) == 0)

    digits_seen = 0;
#if CHEXPREFIX
    if( *ptr == '0' && (tolower( *(ptr+1) ) == 'x' ) ) {
        ptr += 2;
        base = 16;
    }
#endif
    dig_start = ptr;
    for( ;; ptr++ ) {
        if (*ptr >= '0' && *ptr <= '9')
            digits_seen |= 1 << (*ptr - '0');
        else {
            last_char = tolower( *ptr );
            if ( last_char >= 'a' && last_char <= 'f' )
                digits_seen |= 1 << ( last_char + 10 - 'a' );
            else
                break;
        }
    }

    /* note that a float MUST contain a dot.
     * 1234e78 is NOT a valid float
     */
    if ( last_char == '.' )
        return( get_float( buf, p ) );

#if 0
    /* v2.08: if suffix isn't followed by a non-id char, don't use it! */
    if ( last_char && is_valid_id_char( *(ptr+1) ) ) {
        last_char = NULLC;
        while ( *(ptr-1) > '9' )
            ptr--;
        digits_seen &= 0x3FF;

    }
#endif

#if CHEXPREFIX
    if ( base != 0 ) {
        dig_end = ptr;
        if ( digits_seen == 0 )
            base = 0;
    } else
#endif
    switch( last_char ) {
    case 'r': /* a float with the "real number designator" */
        buf->token = T_FLOAT;
        buf->floattype = 'r';
        ptr++;
        goto number_done;
    case 'h':
        base = 16;
        dig_end = ptr;
        ptr++;
        break;
    //case 'b':
    case 'y':
        if( OK_NUM( BINARY ) ) {
            base = 2;
            dig_end = ptr;
            ptr++;
        }
        break;
    //case 'd':
    case 't':
        if( OK_NUM( DECIMAL ) ) {
            base = 10;
            dig_end = ptr;
            ptr++;
        }
        break;
    case 'q':
    case 'o':
        if( OK_NUM( OCTAL ) ) {
            base = 8;
            dig_end = ptr;
            ptr++;
        }
        break;
    default:
        last_char = tolower( *(ptr-1) );
        if ( ( last_char == 'b' || last_char == 'd' ) && digits_seen >= ( 1UL << ModuleInfo.radix ) ) {
            char *tmp = dig_start;
            char max = ( last_char == 'b' ? '1' : '9' );
            for ( dig_end = ptr-1; tmp < dig_end && *tmp <= max; tmp++ );
            if ( tmp == dig_end ) {
                base = ( last_char == 'b' ? 2 : 10 );
                break;
            }
        }
        dig_end = ptr;
#if COCTALS
        if( Options.allow_c_octals && *dig_start == '0' ) {
            if( OK_NUM( OCTAL ) ) {
                base = 8;
                break;
            }
        }
#endif
        /* radix      max. digits_seen
         -----------------------------------------------------------
         2            3      2^2-1  (0,1)
         8            255    2^8-1  (0,1,2,3,4,5,6,7)
         10           1023   2^10-1 (0,1,2,3,4,5,6,7,8,9)
         16           65535  2^16-1 (0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f)
         */
        if ( digits_seen < (1UL << ModuleInfo.radix) )
            base = ModuleInfo.radix;
        break;
    }

#if MASMNUMBER
    /* Masm doesn't swallow alphanum chars which may follow the
     * number!
     */
    if ( base != 0 ) {
#else
    if ( base != 0 && is_valid_id_char( *ptr ) == FALSE ) {
#endif
        buf->token = T_NUM;
        buf->numbase = base;
        buf->itemlen = dig_end - dig_start;
        //DebugMsg(("get_number: inp=%s, value=%" I32_SPEC "X\n", p->input, buf->value64 ));
    } else {
        buf->token = T_BAD_NUM;
        DebugMsg(("get_number: BAD_NUMBER (%s), radix=%u, base=%u, ptr=>%s<, digits_seen=%Xh\n", dig_start, ModuleInfo.radix, base, ptr, digits_seen ));
        /* swallow remainder of token */
        while( is_valid_id_char( *ptr ) ) ++ptr;
    }
number_done:
    len = ptr - p->input;
    memcpy( p->output, p->input, len );

    p->output += len;
    *p->output++ = NULLC;
    p->input = ptr;

    return( NOT_ERROR );
}

#if BACKQUOTES
static ret_code get_id_in_backquotes( struct asm_tok *buf, struct line_status *p )
/********************************************************************************/
{
    char *optr = p->output;
    buf->token = T_ID;
    buf->idarg = 0;

    p->input++;         /* strip off the backquotes */
    for( ; *p->input != '`'; ) {
        if( *p->input == NULLC || *p->input == ';' ) {
            *p->output = NULLC;
            EmitErr( BACKQUOTE_MISSING, p->output );
            return( ERROR );
        }
        *optr++ = *p->input++;
    }
    p->input++;         /* skip the terminating '`' */
    *optr++ = NULLC;
    p->output = optr;
    return( NOT_ERROR );
}
#endif

/* get an ID. will always return NOT_ERROR. */
static ret_code get_id( struct asm_tok *buf, struct line_status *p )
/******************************************************************/
{
    //struct ReservedWord *resw;
    char *src = p->input;
    char *dst = p->output;
    char *p1  = p->input;
    int  index;
    unsigned size;
	int len = 0;
	int i = 0;
#if CONCATID || DOTNAMEX
continue_scan:
#endif
    do {
        *dst++ = *src++;
    } while ( fast_is_valid_id_char( *src ) );
#if CONCATID
    /* v2.05: in case there's a backslash right behind
     * the ID, check if a line concatenation is to occur.
     * If yes, and the first char of the concatenated line
     * is also a valid ID char, continue to scan the name.
     * Problem: it's ok for EQU, but less good for other directives.
     */
    if ( *src == '\\' ) {
        if ( ConcatLine( src, src - p->input, dst, p ) != EMPTY ) {
            p->concat = TRUE;
            if (fast_is_valid_id_char( *src ) )
                goto continue_scan;
        }
    }
#endif
#if DOTNAMEX
    /* if the name starts with a dot or underscore, then accept dots
     * within the name (though not as last char). OPTION DOTNAME
     * must be on.
     */
    if ( *src == '.' && ModuleInfo.dotname &&
        ( *(p->output) == '.' || *(p->output) == '_' ) &&
        (fast_is_valid_id_char(*(src+1)) || *(src+1) == '.' ) )
        goto continue_scan;
#endif
    /* v2.04: check added */
    size = dst - p->output;
    if ( size > MAX_ID_LEN ) {
        EmitErr( IDENTIFIER_TOO_LONG );
        dst = p->output + MAX_ID_LEN;
    }
    *dst++ = NULLC;

    /* now decide what to do with it */

    if( size == 1 && *p->output == '?' ) {
        p->input = src;
        buf->token = T_QUESTION_MARK;
        buf->string_ptr = "?";
        return( NOT_ERROR );
    }
    index = FindResWord( p->output, size );
    if( index == 0 ) {
        /* if ID begins with a DOT, check for OPTION DOTNAME.
         * if not set, skip the token and return a T_DOT instead!
         */
        if ( *p->output == '.' && ModuleInfo.dotname == FALSE ) {
           buf->token = T_DOT;
           buf->string_ptr = (char *)&stokstr1['.' - '('];
           p->input++;
           return( NOT_ERROR );
        }
        p->input = src;
        p->output = dst;
        buf->token = T_ID;
        buf->idarg = 0;
        return( NOT_ERROR );
    }
    /* filter pseudo instructions */
	if (!inMacroBody)
	{
		if (index >= T_CMPEQPD && index <= T_CMPORDSS) {
			index = get_pseudoCMPXX(dst, p->input, index);
			strcpy(buf[0].string_ptr, dst);
		}
		else if (index >= T_VCMPEQPD && index <= T_VCMPTRUE_USSS) {
			index = get_pseudoVCMPXX(dst, p->input, index);
			strcpy(buf[0].string_ptr, dst);
		}
		else if (index >= T_PCLMULLQLQDQ && index <= T_PCLMULHQHQDQ) {
			index = get_pseudoPCLMULXX(dst, p->input, index);
			strcpy(buf[0].string_ptr, dst);
		}
		else if (index >= T_VPCLMULLQLQDQ && index <= T_VPCLMULHQHQDQ) {
			index = get_pseudoVPCLMULXX(dst, p->input, index);
			strcpy(buf[0].string_ptr, dst);
		}
	}
    /* end of filter pseudo instructions */

    p->input = src;
    p->output = dst;
    buf->tokval = index; /* is a enum instr_token value */
    /* v2.11: RWF_SPECIAL now obsolete */
    //if ( ! ( ResWordTable[index].flags & RWF_SPECIAL ) ) {
    if ( index >= SPECIAL_LAST ) {

        //  DebugMsg(("found item >%s< in instruction table, rm=%X\n", buf->string_ptr, InstrTable[index].rm_byte));

        /* if -Zm is set, the following from the Masm docs is relevant:
         *
         * Reserved Keywords Dependent on CPU Mode with OPTION M510
         *
         * With OPTION M510, keywords and instructions not available in the
         * current CPU mode (such as ENTER under .8086) are not treated as
         * keywords. This also means the USE32, FLAT, FAR32, and NEAR32 segment
         * types and the 80386/486 registers are not keywords with a processor
         * selection less than .386.
         * If you remove OPTION M510, any reserved word used as an identifier
         * generates a syntax error. You can either rename the identifiers or
         * use OPTION NOKEYWORD. For more information on OPTION NOKEYWORD, see
         * OPTION NOKEYWORD, later in this appendix.
         *
         * The current implementation of this rule below is likely to be improved.
         */
        if ( ModuleInfo.m510 ) {
            /* checking the cpu won't give the expected results currently since
             * some instructions in the table (i.e. MOV) start with a 386 variant!
             */
            index = IndexFromToken( buf->tokval );
#if 0 /* changed for v1.96 */
            if (( InstrTable[index].cpu & P_EXT_MASK ) > ( ModuleInfo.curr_cpu & P_EXT_MASK )) {
#else
            if (( InstrTable[index].cpu & P_CPU_MASK ) > ( ModuleInfo.curr_cpu & P_CPU_MASK ) ||
                ( InstrTable[index].cpu & P_EXT_MASK ) > ( ModuleInfo.curr_cpu & P_EXT_MASK )) {
#endif
                buf->token = T_ID;
                buf->idarg = 0;
                return( NOT_ERROR );
            }
        }
        buf->token = T_INSTRUCTION;
        return( NOT_ERROR );
    }
    index = buf->tokval;

    /* for RWT_SPECIAL, field <bytval> contains further infos:
     - RWT_REG:             register number (regnum)
     - RWT_DIRECTIVE:       type of directive (dirtype)
     - RWT_UNARY_OPERATOR:  operator precedence
     - RWT_BINARY_OPERATOR: operator precedence
     - RWT_STYPE:           memtype
     - RWT_RES_ID:          for languages, LANG_xxx value
                            for the rest, unused.
     */
    buf->bytval = SpecialTable[index].bytval;

    switch ( SpecialTable[index].type ) {
    case RWT_REG:
        buf->token = T_REG;
#if AVXSUPP 
		if (!inMacroBody)
		{
			/* Intercept here '{' for EVEX mask  {k1}{z} */
			while (isspace(*p->input)) p->input++;
			if (*p->input == '{') {
				p->input++;
				get_decos(p,FALSE); // mask decorators
			}
		}
		else
		{
			while (isspace(*p->input)) p->input++;
			if (*p->input == '{') {
				while ((*p->input) != '}') {
					p->input++;
				}
				p->input++;
				//*buf->string_ptr = "{k0}";
			}
		}
#endif        
        break;
    case RWT_DIRECTIVE:
        buf->token = T_DIRECTIVE;
        if ( p->flags2 == 0 )
            p->flags2 = SpecialTable[index].value;
        break;
    case RWT_UNARY_OP: /* OFFSET, LOW, HIGH, LOWWORD, HIGHWORD, SHORT, ... */
        buf->token  = T_UNARY_OPERATOR;
        break;
    case RWT_BINARY_OP: /* GE, GT, LE, LT, EQ, NE, MOD, PTR */
        buf->token = T_BINARY_OPERATOR;
        break;
    case RWT_STYPE:  /* BYTE, WORD, FAR, NEAR, FAR16, NEAR32 ... */
        buf->token = T_STYPE;
        break;
    case RWT_RES_ID: /* DUP, ADDR, FLAT, VARARG, language types [, FRAME (64-bit)] */
        buf->token = T_RES_ID;
        break;
    default: /* shouldn't happen */
        DebugMsg(("get_id: error, unknown type in SpecialTable[%u]=%u\n", index, SpecialTable[index].type ));
        /**/myassert( 0 );
        buf->token = T_ID;
        buf->idarg = 0;
        break;
    }
    return( NOT_ERROR );
}

/* get one token.
 * possible return values: NOT_ERROR, ERROR, EMPTY.
 *
 * names beginning with '.' are difficult to detect,
 * because the dot is a binary operator. The rules to
 * accept a "dotted" name are:
 * 1.- a valid ID char is to follow the dot
 * 2.- if buffer index is > 0, then the previous item
 *     must not be a reg, ), ] or an ID.
 * [bx.abc]    -> . is an operator
 * ([bx]).abc  -> . is an operator
 * [bx].abc    -> . is an operator
 * varname.abc -> . is an operator
 */

#define is_valid_id_start( ch )  ( islalpha(ch) || ch=='_' || ch=='@' || ch=='$' || ch=='?' )

ret_code GetToken( struct asm_tok token[], struct line_status *p )
/****************************************************************/
{
    if( isldigit( *p->input ) ) {
        return( get_number( token, p ) );
    } else if( is_valid_id_start( *p->input ) ) {
        return( get_id( token, p ) );
    } else if( *p->input == '.' &&
#if DOTNAMEX /* allow dots within identifiers */
              (fast_is_valid_id_char(*(p->input+1)) || *(p->input+1) == '.' ) &&
#else
		fast_is_valid_id_char(*(p->input+1)) &&
#endif
              /* v2.11: member last_token has been removed */
              //( p->last_token != T_REG &&  p->last_token != T_CL_BRACKET && p->last_token != T_CL_SQ_BRACKET && p->last_token != T_ID ) ) {
              ( p->index == 0 || ( token[-1].token != T_REG && token[-1].token != T_CL_BRACKET && token[-1].token != T_CL_SQ_BRACKET && token[-1].token != T_ID ) ) ) {
        return( get_id( token, p ) );
#if BACKQUOTES
    } else if( *p->input == '`' && Options.strict_masm_compat == FALSE ) {
        return( get_id_in_backquotes( token, p ) );
#endif
    }
    return( get_special_symbol( token, p ) );
}

// fixme char *IfSymbol;        /* save symbols in IFDEF's so they don't get expanded */

static void StartComment( const char *p )
/***************************************/
{
    while ( isspace( *p ) ) p++;
    if ( *p == NULLC ) {
        EmitError( COMMENT_DELIMITER_EXPECTED );
        return;
    }
    ModuleInfo.inside_comment = *p++;
    if( strchr( p, ModuleInfo.inside_comment ) )
        ModuleInfo.inside_comment = NULLC;
    return;
}

int Tokenize( char *line, unsigned int start, struct asm_tok tokenarray[], unsigned int flags )
/*********************************************************************************************/
/*
 * create tokens from a source line.
 * line:  the line which is to be tokenized
 * start: where to start in the token buffer. If start == 0,
 *        then some variables are additionally initialized.
 * flags: 1=if the line has been tokenized already.
 */
{
    int                rc;
    struct line_status p;
	  char*  input1 = NULL;
    char*  p1 = NULL;
    int    cnt = 0;
    p.input = line;
    p.start = line;
    p.index = start;
    p.flags = flags;
    p.flags2 = 0;
    p.flags3 = 0;
    char* buff[256];
    if ( p.index == 0 ) 
	{
#ifdef DEBUG_OUT
        cnttok0++;
#endif
        p.output = token_stringbuf;
        if( ModuleInfo.inside_comment ) 
		{
            DebugMsg1(("COMMENT active, delim is >%c<, line is >%s<\n", ModuleInfo.inside_comment, line));
            if( strchr( line, ModuleInfo.inside_comment ) != NULL ) {
                DebugMsg1(("COMMENT mode exited\n"));
                ModuleInfo.inside_comment = NULLC;
            }
            goto skipline;
        }
    } 
	else 
	{
#ifdef DEBUG_OUT
        cnttok1++;
#endif
        p.output = StringBufferEnd;
    }

    for( ;; ) {

        while( isspace( *p.input ) ) p.input++;

        if ( *p.input == ';' && flags == TOK_DEFAULT ) {
            while ( p.input > line && isspace( *(p.input-1) ) ) p.input--; /* skip */
            strcpy( commentbuffer, p.input );
            ModuleInfo.CurrComment = commentbuffer;
            *p.input = NULLC;
        }
        /* Next to routines will work only if option evex: 1 */
        if (evex) {
          /* UASM 2.48 Handle {evex} promotion decorator */
          if (*p.input == '{')
          {
            input1 = p.input + 1;      /* skip '{' */
            while (isspace(*input1))
              input1++;
            if ((_memicmp(input1, "evex", 4) == 0))
            {
              evexflag = TRUE;
              while (*input1 != '}')
                input1++;
              input1++;                /* skip '}' */
              while (isspace(*input1))
                input1++;
              p.input = input1;        /* skip '{evex}' */
              goto nobcst;
            }
          }
		  else if (*p.input == 'v' || *p.input == 'V') {
            /* Implement ml64 BCST for broadcast */
            for (p1 = p.input; *p1 != 0; p1++) {     /* start from the beginning of string */
              if (*p1 == ';')
                break;
              if (*p1 == 'b' || *p1 == 'B') {        /* found  'b' */
                if ((_memicmp(p1, "bcst", 4) == 0))  /* found "bcst" ? */
                  break;                             /* found "bcst" */
              }                                      /* if it was {kn} or {z} search till end */
            }
            if (*p1 != 0 && *p1 != ';') {                        /* if 'bcst' present p1 is pointing to "bcst" */
              input1 = p1 + 4;                     /* skip "bcst" and save location in input1 */
              while (isspace(*input1)) input1++;   /* skip the space, now pointing to address  */
              p1 = p.input;                        /* start again from begining of string */
              while (*p1 > ' ') p1++;               /* skip instruction */
              while (isspace(*p1)) p1++;
              /* find which register is used */
              if (*p1 == 'k' || *p1 == 'K') {      /* check if it is mask register */
                if ((*(p1 + 1) >= '1') && (*(p1 + 1) <= '7')) {
                  p1++;                            /* skip register number */
                  while (*p1 != ',') p1++;          /* find the comma  */
                  p1++;                            /* skip the comma  */
                  while (isspace(*p1)) p1++;       /* skip the space  */
                }
              }
              if (0 == _memicmp(p1, "xmm", 3))
                cnt = 2;                           /* 2 qword for xmm registers */
              else if (0 == _memicmp(p1, "ymm", 3))
                cnt = 4;                           /* 4 qword for ymm registers */
              else if (0 == _memicmp(p1, "zmm", 3))
                cnt = 8;                           /* 8 qword for zmm registers */
              else
                goto nobcst;                       /* let parser throw error */
              /* find is it dword or qword */
              for (; *p1 != 0; p1++)
              {
                if (0 == _memicmp(p1, "word", 4))    /* it is faster to find "word" first */
                  break;
              }
              if (*p1 == 0)goto nobcst;            /* let parser throw error */
              p1--;                                /* get the 'q' or 'd' */
              if (*p1 == 'd' || *p1 == 'D')
                cnt += cnt;                        /* double it for dword */
              else if (*p1 == 'q' || *p1 == 'Q')   /* incorret size? */
                ;//OK QWORD
              else
                goto nobcst;                       /* let parser throw error */
              if (*input1 != '\[') {               /* if address is not inside [] */
                *p1++ = '\[';                      /* force it   */
                for (; *input1 > ','; p1++, input1++) {  /* input1 points to [address] */
                  if (*input1 == ';') 
                    break;
                  *p1 = *input1;                     /* copy first memory part over 'qword bcst */
                }
                *p1++ = '\]';
                if (*input1 == ';')
                  *input1 = 0;
                while (isspace(*input1)) input1++;   /* skip the space, now pointing to address  */
              }
              else {
                for (; *input1 != '\]'; p1++, input1++) /* input1 points to [address] */
                  *p1 = *input1;                     /* copy first memory part over 'qword bcst */
                *p1++ = *input1++;                   /* copy ']' */
              }
              /* now add broadcast size */
              if (cnt == 2)       strcpy(p1, "\{1to2\}");
              else if (cnt == 4)  strcpy(p1, "\{1to4\}");
              else if (cnt == 8)  strcpy(p1, "\{1to8\}");
              else if (cnt == 16) strcpy(p1, "\{1to16\}");
              else goto nobcst;                   /* let parser throw error */
              strcat(p1, input1);
            }
            else {
              /* here force '[]' around a variable */
              for (p1 = p.input; *p1 != 0; p1++) {     /* start from the beginning of string */
                if (*p1 == ';') {                        /* found  ';' */
                  *p1 = 0;                             /* that means '{' is in comment */
                }
                if (*p1 == '\{') {                     /* found  '{' */
                  if ((_memicmp(p1, "\{1to", 4) == 0))
                    break;                             /* found "bcst" */
                }                                      /* if it was {kn} or {z} search till end */
              }
              if (*p1 == '\{') {                       /* if found {1toN} */
                p1--;                                  /* go back 1 byte to check if ']' is present */
                while (isspace(*p1)) --p1;             /* skip the space  */
                if (*p1 != '\]') {                     /* if not present insert it  */
                  while (*p1 != ',') --p1;             /* step backwards till the comma */
                  p1++;                                /* skip the comma forward  */
                  input1 = p1;                         /* save that location in input1  */
                  while (isspace(*p1)) p1++;           /* skip the space  */
                  strcpy(buff, p1);                    /* copy to the buffer from variable on  */
                  *input1++ = '\[';                    /* skip the space  */
                  for (p1 = buff; *p1 != '\{'; p1++, input1++) /* till the end of var  */
                    *input1 = *p1;                      /* copy it back to input string  */
                  *input1++ = '\]';                    /* insert ']' before '{' */
                  strcpy(input1, p1);                  /* now copy the rest of string from buffer */
                }
              }
            }
          }
        }
    nobcst:
        tokenarray[p.index].tokpos = p.input;
        if( *p.input == NULLC ) {
            /* if a comma is last token, concat lines ... with some exceptions
             * v2.05: moved from PreprocessLine(). Moved because the
             * concatenation may be triggered by a comma AFTER expansion.
             */
            if ( p.index > 1 &&
                tokenarray[p.index-1].token == T_COMMA
#if FASTPASS
                && ( Parse_Pass == PASS_1 || UseSavedState == FALSE ) /* is it an already preprocessed line? */
#endif
                && start == 0 ) {
                DebugMsg1(("Tokenize: calling IsMultiLine()\n" ));
                if ( IsMultiLine( tokenarray ) ) {
                    char *ptr = GetAlignedPointer( p.output, strlen( p.output ) );
                    DebugMsg1(("Tokenize: IsMultiLine(%s)=TRUE\n", line ));
                    if ( GetTextLine( ptr ) ) {
                        while ( isspace( *ptr ) ) ptr++;
                        if ( *ptr ) {
                            strcpy( p.input, ptr );
                            if ( strlen( p.start ) >= MAX_LINE_LEN ) {
                                EmitError( LINE_TOO_LONG );
                                p.index = start;
                                break;
                            }
                            DebugMsg1(("Tokenize: line concatenation, line=%s\n", line ));
                            continue;
                        }
                    }
                }
            }
            break;
        }
        tokenarray[p.index].string_ptr = p.output;
        rc = GetToken( &tokenarray[p.index], &p );
        if ( rc == EMPTY )
            continue;
        if ( rc == ERROR ) {
            p.index = start; /* skip this line */
            break;
        }
        /* v2.04: this has been moved here from condasm.c to
         * avoid problems with (conditional) listings. It also
         * avoids having to search for the first token twice.
         * Note: a conditional assembly directive within an
         *    inactive block and preceded by a label isn't detected!
         *    This is an exact copy of the Masm behavior, although
         *    it probably is just a bug!
         */
        if ( !(flags & TOK_RESCAN) ) {
            if ( p.index == 0 || ( p.index == 2 && ( tokenarray[1].token == T_COLON || tokenarray[1].token == T_DBL_COLON) ) ) {
                if ( tokenarray[p.index].token == T_DIRECTIVE &&
                    tokenarray[p.index].bytval == DRT_CONDDIR ) {
                    if ( tokenarray[p.index].tokval == T_COMMENT ) {
                        DebugMsg1(("tokenize: COMMENT starting, delim is >%c<\n", ModuleInfo.inside_comment));
                        StartComment( p.input );
                        break; /* p.index is 0 or 2 */
                    }
                    conditional_assembly_prepare( tokenarray[p.index].tokval );
                    if ( CurrIfState != BLOCK_ACTIVE ) {
                        p.index++;
                        break; /* p.index is 1 or 3 */
                    }
                } else if( CurrIfState != BLOCK_ACTIVE ) {
                    /* further processing skipped. p.index is 0 */
                    break;
                }
            }
        }
        p.index++;
        if( p.index >= MAX_TOKEN ) {
            DebugMsg1(("tokenize: token index %u >= MAX_TOKEN (=%u), line=>%s<\n", p.index, MAX_TOKEN, line ));
            EmitError( TOO_MANY_TOKENS );
            p.index = start;
            goto skipline;
        }

#if TOKSTRALIGN
        p.output = GetAlignedPointer( token_stringbuf, p.output - token_stringbuf );
#endif

    }
#if TOKSTRALIGN
    p.output = GetAlignedPointer( token_stringbuf, p.output - token_stringbuf );
#endif
    StringBufferEnd = p.output;
skipline:
    tokenarray[p.index].token  = T_FINAL;
    tokenarray[p.index].bytval = p.flags3;
    tokenarray[p.index].string_ptr = "";
    return( p.index );
}

