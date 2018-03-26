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
* Description:  Uasm conditional processing routines. Handles directives
*               [ELSE]IF[E], ELSE, ENDIF
*               [ELSE]IFB, [ELSE]IFNB
*               [ELSE]IFDEF, [ELSE]IFNDEF
*               [ELSE]IFDIF[I], [ELSE]IFIDN[I]
*               [ELSE]IF1, [ELSE]IF2
*               .ERR, .ERRNZ, .ERRE
*               .ERRB, .ERRNB
*               .ERRDEF, .ERRNDEF
*               .ERRDIF[I], .ERRIDN[I]
*               .ERR1, .ERR2
****************************************************************************/


#include <ctype.h>

#include "globals.h"
#include "parser.h"
#include "condasm.h"
#include "reswords.h"
#include "expreval.h"
#include "listing.h"
#include "input.h"
#include "macro.h"
#include "types.h"
#include "fastpass.h"

/*
 the current if-block can be in one of 3 states:
  state              assembly     possible state change to
 ---------------------------------------------------------
  inactive           off          active
  active             on           done
  done               off          -
  --------------------------------------------------------
  up to v2.04, there was a fourth state:
  condition check    on           active, inactive
  it was necessary because lines may have been tokenized multiple times.
*/

enum if_state CurrIfState;
static int blocknestlevel;
static int falseblocknestlevel;
static uint_32 elseoccured; /* 2.06: bit field, magnitude must be >= MAX_IF_NESTING */

#ifdef DEBUG_OUT
static const char *GetCurrIfStatString( void )
/********************************************/
{
    switch ( CurrIfState ) {
    case BLOCK_ACTIVE:   return( "BLOCK_ACTIVE" );
    case BLOCK_INACTIVE: return( "BLOCK_INACTIVE" );
    default:             return( "BLOCK_DONE" );
    }
}
#endif

/*
 * this code runs after the first token has been scanned,
 * if it is a IFx, ELSEx or ENDIF.
 * updates variables <blocknestlevel> and <falseblocknestlevel>.
*/

void conditional_assembly_prepare( int directive )
/************************************************/
{
    DebugMsg1(("condasm_prepare(%s), old status: %s, lvl=%u, falselvl=%u\n",
               GetResWName( directive, NULL), GetCurrIfStatString(), blocknestlevel, falseblocknestlevel));
    switch( directive ) {
    case T_IF:
    case T_IF1:
    case T_IF2:
    case T_IFB:
    case T_IFDEF:
    case T_IFDIF:
    case T_IFDIFI:
    case T_IFE:
    case T_IFIDN:
    case T_IFIDNI:
    case T_IFNB:
    case T_IFNDEF:
        if( CurrIfState != BLOCK_ACTIVE ) {
            falseblocknestlevel++;
            break;
        }
        if( blocknestlevel == MAX_IF_NESTING ) {
            EmitError( NESTING_LEVEL_TOO_DEEP );
            break;
        }
        elseoccured &= ~( 1 << blocknestlevel ); /* v2.06: added */
        blocknestlevel++;
        break;
    case T_ELSE:
    case T_ELSEIF:
    case T_ELSEIF1:
    case T_ELSEIF2:
    case T_ELSEIFB:
    case T_ELSEIFDEF:
    case T_ELSEIFDIF:
    case T_ELSEIFDIFI:
    case T_ELSEIFE:
    case T_ELSEIFIDN:
    case T_ELSEIFIDNI:
    case T_ELSEIFNB:
    case T_ELSEIFNDEF:
        if ( blocknestlevel ) { /* v2.04: do nothing if there was no IFx */
            if ( falseblocknestlevel > 0 ) {
                break;
            }
            /* v2.06: check added to detect multiple ELSE branches */
            if ( elseoccured & ( 1 << ( blocknestlevel - 1 ) ) ) {
                EmitError( ELSE_CLAUSE_ALREADY_OCCURED_IN_THIS_IF_BLOCK );
                break;
            }
            /* status may change:
             * inactive -> active
             * active   -> done
             */
            CurrIfState = (( CurrIfState == BLOCK_INACTIVE ) ? BLOCK_ACTIVE : BLOCK_DONE );
            /* v2.06: no further ELSEx once ELSE was detected */
            if ( directive == T_ELSE )
                elseoccured |= ( 1 << ( blocknestlevel - 1 ) );
        } else {
            EmitErr( BLOCK_NESTING_ERROR, GetResWName( directive, NULL ) );
        }
        break;
    case T_ENDIF:
        if ( blocknestlevel ) {
            if ( falseblocknestlevel > 0 ) {
                falseblocknestlevel--;
                break;
            }
            blocknestlevel--;
            CurrIfState = BLOCK_ACTIVE; /* v2.04: added */
        } else {
            EmitErr( BLOCK_NESTING_ERROR, GetResWName( directive, NULL ) );
        }
        break;
    }
    DebugMsg1(("condasm_prepare(%s), new status: %s, lvl=%u, falselvl=%u\n",
               GetResWName( directive, NULL ), GetCurrIfStatString(), blocknestlevel, falseblocknestlevel));
    return;
}

/* handle [ELSE]IF[N]DEF
 * <string> is
 * - the value of a T_ID item!
 * - "" (item is T_FINAL)
 */

static bool check_defd( const char *name )
/****************************************/
{
    struct asym      *sym;
    if ( *name ) {
        sym = SymSearch( name );
        if( sym ) {
            DebugMsg1(("check_defd(%s): state=%u defined=%u\n", name, sym->state, sym->isdefined ));
            /* v2.04: changed. the "defined" flag is active for ALL symbols */
            //if ( sym->state == SYM_INTERNAL || sym->state == SYM_MACRO || sym->state == SYM_TMACRO || sym->state == SYM_UNDEFINED ) {
            return( sym->isdefined );
        }
        DebugMsg1(("check_defd(%s): sym=NULL\n", name ));
    }
    return( FALSE );
}

/* handle [ELSE]IF[N]B
 */
static bool check_blank( const char *string )
/*******************************************/
{
    for ( ;*string; string++ )
        if ( isspace(*string) == FALSE )
            return FALSE;
    return( TRUE );
}

/* Are two strings different?
 * Used by [ELSE]IFDIF[I] and [ELSE]IFIDN[I]
 */

static bool check_dif( const char *string1, const char *string2, bool sensitive )
/*******************************************************************************/
{
    if( sensitive ) {
        return( strcmp( string1, string2 ) != 0 );
    } else {
        return( _stricmp( string1, string2 ) != 0 );
    }
}

ret_code CondAsmDirective( int i, struct asm_tok tokenarray[] )
/*************************************************************/
{
    int directive = tokenarray[i].tokval;
    const char *string1;
    const char *string2;
    enum if_state NextIfState;
    struct expr opndx;

    if ( CurrIfState != BLOCK_ACTIVE ) {
        DebugMsg1(("CondAsmDirective(%s), CurrIfState=%u(%s), lvl=%u, falselvl=%u\n",
                   GetResWName(directive, NULL), CurrIfState, GetCurrIfStatString(), blocknestlevel, falseblocknestlevel));
        if ( i || ModuleInfo.listif ) {
            LstWriteSrcLine();
        }
        return( NOT_ERROR );
    }

    if ( ModuleInfo.list == TRUE ) {
        if ( MacroLevel == 0 ||
            ModuleInfo.list_macro == LM_LISTMACROALL ||
            ModuleInfo.listif )
            LstWriteSrcLine();
    }

    DebugMsg1(("CondAsmDirective(%s), BLOCK_ACTIVE, lvl=%u, falselvl=%u [%s]\n", GetResWName(directive, NULL), blocknestlevel, falseblocknestlevel, tokenarray[i].tokpos ));

    i++; /* go past IFx, ELSEx, ENDIF */

    /* check params and call appropriate test routine */

    switch( GetSflagsSp(directive) ) {
    case CC_NUMARG: /* [ELSE]IF[E] */
        /* no forward reference allowed, symbol must be defined */
        if ( ( ERROR == EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) ) ) {
            DebugMsg(("CondAsmDirective(%s), EvalOperand returned with ERROR\n", GetResWName(directive, NULL) ));
            /* v2.11: don't exit, assume 0 */
            //return( ERROR );
            opndx.kind = EXPR_CONST;
            opndx.value = 0;
            i = Token_Count;
        }
#if 0 /* v2.05: obsolete */
        if ( opndx.sym && opndx.sym->state == SYM_UNDEFINED ) {
            EmitErr( SYMBOL_NOT_DEFINED, opndx.sym->name );
        } else
#endif
        if ( opndx.kind == EXPR_CONST )
            ;
        else if ( opndx.kind == EXPR_ADDR && opndx.indirect == FALSE ) {
            opndx.value += opndx.sym->offset;
            /* v2.07: Masm doesn't accept a relocatable item,
             * so emit at least a warning!
             */
            EmitWarn( 2, CONSTANT_EXPECTED );
        } else {
            return( EmitError( CONSTANT_EXPECTED ) );
        }
        if ( directive == T_IF || directive == T_ELSEIF )
            NextIfState = ( opndx.value ) ? BLOCK_ACTIVE : BLOCK_INACTIVE;
        else
            NextIfState = ( !opndx.value ) ? BLOCK_ACTIVE : BLOCK_INACTIVE;
        break;
    case CC_LITARG: /*  [ELSE]IFDIF[I], [ELSE]IFIDN[I] */
        string1 = tokenarray[i].string_ptr;
        if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' ) {
            if ( tokenarray[i].token == T_ID && SymSearch( string1 ) == NULL )
                EmitErr( SYMBOL_NOT_DEFINED, string1 );
            else
                EmitError( TEXT_ITEM_REQUIRED );
            return( ERROR );
        }
        i++;
        if ( tokenarray[i].token != T_COMMA ) {
            return( EmitErr( EXPECTING_COMMA, tokenarray[i].tokpos ) );
        }
        i++;
        string2 = tokenarray[i].string_ptr;
        if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' ) {
            if ( tokenarray[i].token == T_ID && SymSearch( string2 ) == NULL )
                EmitErr( SYMBOL_NOT_DEFINED, string2 );
            else
                EmitError( TEXT_ITEM_REQUIRED );
            return( ERROR );
        }
        i++;
        DebugMsg1(("CondAsmDirective(%s), cmp >%s< and >%s<\n", GetResWName(directive, NULL), string1, string2 ));
        switch ( directive ) {
        case T_IFDIF:
        case T_ELSEIFDIF:
            NextIfState = check_dif( string1, string2, TRUE ) ? BLOCK_ACTIVE : BLOCK_INACTIVE;
            break;
        case T_IFDIFI:
        case T_ELSEIFDIFI:
            NextIfState = check_dif( string1, string2, FALSE ) ? BLOCK_ACTIVE : BLOCK_INACTIVE;
            break;
        case T_IFIDN:
        case T_ELSEIFIDN:
            NextIfState = !check_dif( string1, string2, TRUE ) ? BLOCK_ACTIVE : BLOCK_INACTIVE;
            break;
        default:
            NextIfState = !check_dif( string1, string2, FALSE ) ? BLOCK_ACTIVE : BLOCK_INACTIVE;
        }
        break;
    case CC_BLKARG: /* [ELSE]IF[N]B */
        string1 = tokenarray[i].string_ptr;

        if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' ) {
            if ( tokenarray[i].token == T_ID && SymSearch( string1 ) == NULL )
                EmitErr( SYMBOL_NOT_DEFINED, string1 );
            else
                EmitError( TEXT_ITEM_REQUIRED );
            return( ERROR );
        }
        i++;
        if ( directive == T_IFB || directive == T_ELSEIFB ) {
            NextIfState = check_blank( string1 ) ? BLOCK_ACTIVE : BLOCK_INACTIVE;
        } else {
            NextIfState = !check_blank( string1 ) ? BLOCK_ACTIVE : BLOCK_INACTIVE;
        }
        break;
    case CC_PASS1: /* [ELSE]IF1 */
        /* v2.04: changed */
        //NextIfState = ((Parse_Pass == PASS_1) ? BLOCK_ACTIVE : BLOCK_INACTIVE);
        NextIfState = BLOCK_ACTIVE;
        break;
    case CC_PASS2: /* [ELSE]IF2 */
        if ( ModuleInfo.setif2 == FALSE ) {
            EmitError( IF2_NOT_ALLOWED );
            break;
        }
        /* v2.04: changed */
        //NextIfState = ((Parse_Pass == PASS_1) ? BLOCK_INACTIVE : BLOCK_ACTIVE);
        NextIfState = BLOCK_ACTIVE;
        break;
    case CC_SYMARG: /* [ELSE]IF[N]DEF */
        NextIfState = BLOCK_INACTIVE;
        /* Masm's implementation works with IDs as arguments only. The rest
         * will return FALSE. However, it's nice to be able to check whether
         * a reserved word is defined or not.
         */
        /* v2.0: [ELSE]IF[N]DEF is valid *without* an argument! */
        //if ( tokenarray[i].token == T_ID && tokenarray[i+1].token == T_FINAL) {
        if ( tokenarray[i].token == T_FINAL ) {
        } else if ( tokenarray[i].token == T_ID  ) {
            /* v2.07: handle structs + members (if -Zne is NOT set) */
            struct asym *sym;
            if ( Options.strict_masm_compat == FALSE &&
                tokenarray[i+1].token == T_DOT &&
                ( sym = SymSearch( tokenarray[i].string_ptr ) ) &&
                ( ( sym->state == SYM_TYPE ) || sym->type ) ) {
                uint_32 value;
                value = 0;
                do {
                    i += 2;
                    /* if it's a structured variable, use its type! */
                    if ( sym->state != SYM_TYPE )
                        sym = sym->type;
                    sym = SearchNameInStruct( sym, tokenarray[i].string_ptr, &value, 0 );
                } while ( sym && tokenarray[i+1].token == T_DOT );
                NextIfState = ( sym ? BLOCK_ACTIVE : BLOCK_INACTIVE );
            } else {
                NextIfState = ( check_defd( tokenarray[i].string_ptr )  ? BLOCK_ACTIVE : BLOCK_INACTIVE );
            }
            i++;
        } else if ( tokenarray[i].token == T_RES_ID && tokenarray[i].tokval == T_FLAT ) {
            /* v2.09: special treatment of FLAT added */
            NextIfState = (( ModuleInfo.flat_grp && ModuleInfo.flat_grp->sym.isdefined ) ? BLOCK_ACTIVE : BLOCK_INACTIVE );
            i++;
        } else if ( Options.strict_masm_compat == FALSE && (
                    tokenarray[i].token == T_RES_ID ||
                    tokenarray[i].token == T_STYPE ||
                    tokenarray[i].token == T_INSTRUCTION ||
                    tokenarray[i].token == T_DIRECTIVE ||
                    //tokenarray[i].token == T_UNARY_OP ||
                    //tokenarray[i].token == T_BINARY_OP ||
                    tokenarray[i].token == T_REG ) &&
                   tokenarray[i+1].token == T_FINAL ) {
            NextIfState = BLOCK_ACTIVE;
            i++;
        }
        if ( tokenarray[i].token != T_FINAL ) {
          if (Options.strict_masm_compat  == TRUE)  /* Zne */
            goto escape;
          else{
               EmitErr( IFDEF_EXPECTS_SYMBOL_ARGUMENT, tokenarray[i-1].tokpos );
               while ( tokenarray[i].token != T_FINAL )  i++;
            }
        }
        if ( directive == T_IFNDEF || directive == T_ELSEIFNDEF )
            NextIfState = ( ( NextIfState == BLOCK_ACTIVE ) ? BLOCK_INACTIVE : BLOCK_ACTIVE );
        break;
    default: /* ELSE and ENDIF */
        NextIfState = BLOCK_ACTIVE;
        break;
    }

    if ( tokenarray[i].token != T_FINAL ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
    }
escape:
    CurrIfState = NextIfState;

    DebugMsg1(("CondAsmDirective(%s) exit, state=%s, lvl=%u, falselvl=%u\n",
               GetResWName(directive, NULL), GetCurrIfStatString(), blocknestlevel, falseblocknestlevel));
    return( NOT_ERROR );
}

static char * GetErrText( int i, struct asm_tok tokenarray[] )
/************************************************************/
{
    *StringBufferEnd = NULLC;
    if ( i ) {
        if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' ) {
            TextItemError( &tokenarray[i] );
        } else {
            *(StringBufferEnd+0) = ':';
            *(StringBufferEnd+1) = ' ';
            //GetLiteralValue( buffer+2, text->string_ptr );
            strcpy( StringBufferEnd+2, tokenarray[i].string_ptr );
        }
    }
    return( StringBufferEnd );

}

/* v2.05: the error directives are no longer handled in the
 * preprocessor, because the errors are displayed in pass 2 only
 * - .err        [<text>]
 * - .err<1|2>   [<text>]
 * - .err<e|nz>  expression [, <text>]
 * - .errdif[i]  literal1, literal2 [, <text>]
 * - .erridn[i]  literal1, literal2 [, <text>]
 * - .err[n]b    text_literal [, <text>]
 * - .err[n]def  symbol [, <text>]
 */
ret_code ErrorDirective( int i, struct asm_tok tokenarray[] )
/***********************************************************/
{
    struct expr opndx;
    unsigned direct;
    const char *string1;
    const char *string2;
    int errmsg = EMPTY;
    int erridx = 0;
    struct asym *sym;
    int idloc;

    direct = tokenarray[i].tokval;

    i++; /* go past directive */

    /* get an expression if necessary */
    switch( GetSflagsSp( direct) ) {
    case CC_NUMARG: /* .ERR[E|NZ] */

        if (( ERROR == EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) ))
            return( ERROR );
        if ( opndx.kind == EXPR_CONST )
            ;
        else if ( opndx.kind == EXPR_ADDR && opndx.indirect == FALSE && opndx.sym && opndx.sym->state == SYM_UNDEFINED )
            ;//opndx.value += opndx.sym->offset;
        else {
            return( EmitError( CONSTANT_EXPECTED ) );
        }
        if ( tokenarray[i].token == T_COMMA && tokenarray[i+1].token != T_FINAL ) {
            i++;
            erridx = i++;
        }
        if ( Parse_Pass == PASS_1 )
            break;
        if ( direct == T_DOT_ERRNZ && opndx.value ) {
            errmsg = FORCED_NOT_ZERO;
        } else if ( direct == T_DOT_ERRE && !opndx.value ) {
            errmsg = FORCED_EQUAL;
        }

        if ( errmsg != EMPTY )
            EmitErr( errmsg, opndx.value, GetErrText( erridx, tokenarray ) );
        break;
    case CC_SYMARG: /* .ERR[N]DEF */
        /* there's a special handling of these directives in ExpandLine()! */
        if ( tokenarray[i].token != T_ID ) {
            return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
        }
        idloc = i;
        /* skip the next param */
        do {
            i++;
        } while ( tokenarray[i].token == T_DOT || tokenarray[i].token == T_ID );
        if ( tokenarray[i].token == T_COMMA && tokenarray[i+1].token != T_FINAL ) {
            /* v2.05: added */
            /* v2.08: obsolete, the expansion occurs in the preprocessor.
             * See ExpandLine() in expans.c
             */
            //ExpandLineItems( tokenarray[i].tokpos, i, tokenarray, TRUE, FALSE );
            i++;
            erridx = i++;  /* Masm seems to accept anything as text */
        }

        //if ( tokenarray[i].token != T_FINAL )
        //    break;

        /* should run on pass 2 only! */
        if ( Parse_Pass == PASS_1 )
            break;

        /* don't use check_defd()! */
        /* v2.07: check for structured variables */
        if ( Options.strict_masm_compat == FALSE &&
            tokenarray[idloc+1].token == T_DOT &&
            ( sym = SymSearch( tokenarray[idloc].string_ptr ) ) &&
            ( ( sym->state == SYM_TYPE ) || sym->type ) ) {
            uint_32 value;
            int j = idloc;
            int size;
            value = 0;
            do {
                j += 2;
                /* if it's a structured variable, use its type! */
                if ( sym->state != SYM_TYPE )
                    sym = sym->type;
                sym = SearchNameInStruct( sym, tokenarray[j].string_ptr, &value, 0 );
            } while ( sym && tokenarray[j+1].token == T_DOT );
            if ( tokenarray[j].token == T_ID )
                j++;
            else if ( tokenarray[j].token != T_FINAL && tokenarray[j].token != T_COMMA ) {
                return( EmitErr( SYNTAX_ERROR_EX, tokenarray[j].string_ptr ) );
            }
            size = tokenarray[j].tokpos - tokenarray[idloc].tokpos;
            memcpy( StringBufferEnd, tokenarray[idloc].tokpos, size );
            *(StringBufferEnd+size) = NULLC;
        } else {
            sym = SymSearch( tokenarray[idloc].string_ptr );
            strcpy( StringBufferEnd, tokenarray[idloc].string_ptr );
        }
        if ( sym && sym->state == SYM_UNDEFINED )
            sym = NULL;

        /* Masm "usually" ignores the optional errtxt! */
        if( direct == T_DOT_ERRDEF && sym != NULL )
            EmitErr( FORCED_DEF, StringBufferEnd );
        else if( direct == T_DOT_ERRNDEF && sym == NULL )
            EmitErr( FORCED_NOT_DEF, StringBufferEnd );
        break;
    case CC_BLKARG: /* .ERR[N]B */
        string1 = tokenarray[i].string_ptr;
        if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' ) {
            return( TextItemError( &tokenarray[i] ) );
        }
        i++;
        if ( tokenarray[i].token == T_COMMA && tokenarray[i+1].token != T_FINAL ) {
            i++;
            erridx = i++;
        }
        if ( Parse_Pass == PASS_1 )
            break;
        if ( direct == T_DOT_ERRB && check_blank( string1 ) )
            errmsg = FORCED_BLANK;
        else if ( direct == T_DOT_ERRNB && !check_blank( string1 ) )
            errmsg = FORCED_NOT_BLANK;
        if ( errmsg != EMPTY )
            EmitErr( errmsg, string1, GetErrText( erridx, tokenarray ) );
        break;
    case CC_LITARG: /* .ERRDIF[I], .ERRIDN[I] */
        string1 = tokenarray[i].string_ptr;
        if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' ) {
            return( TextItemError( &tokenarray[i] ) );
        }
        i++;
        if ( tokenarray[i].token != T_COMMA ) {
            return( EmitErr( EXPECTING_COMMA, tokenarray[i].tokpos ) );
        }
        i++;
        string2 = tokenarray[i].string_ptr;
        if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' ) {
            return( TextItemError( &tokenarray[i] ) );
        }
        i++;
        if ( tokenarray[i].token == T_COMMA && tokenarray[i+1].token != T_FINAL ) {
            i++;
            erridx = i++;
        }
        if ( Parse_Pass == PASS_1 )
            break;

        switch ( direct ) {
        case T_DOT_ERRDIF:
            if ( check_dif( string1, string2, TRUE ) )
                errmsg = FORCED_DIF;
            break;
        case T_DOT_ERRDIFI:
            if ( check_dif( string1, string2, FALSE ) )
                errmsg = FORCED_DIF;
            break;
        case T_DOT_ERRIDN:
            if ( !check_dif( string1, string2, TRUE ) )
                errmsg = FORCED_IDN;
            break;
        default:
            if ( !check_dif( string1, string2, FALSE ) )
                errmsg = FORCED_IDN;
        }
        if ( errmsg != EMPTY )
            EmitErr( errmsg, string1, string2, GetErrText( erridx, tokenarray ) );
        break;
    case CC_PASS2: /* .ERR2 */
        if ( ModuleInfo.setif2 == FALSE ) {
            return( EmitError( IF2_NOT_ALLOWED ) );
        }
    case CC_PASS1: /* .ERR1 */
    default: /* .ERR */
        if ( tokenarray[i].token != T_FINAL ) {
            erridx = i++;
        }
        if ( Parse_Pass == PASS_1 )
            break;
        EmitErr( FORCED_ERR, GetErrText( erridx, tokenarray ) );
        break;
    }
    if ( tokenarray[i].token != T_FINAL ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
    }
    return( NOT_ERROR );
}

void CondCheckOpen( void )
/************************/
{
    if( blocknestlevel > 0 ) {
        EmitErr( BLOCK_NESTING_ERROR, "if-else" );
    }
    return;
}

int GetIfNestLevel( void )
/************************/
{
    return( blocknestlevel );
}

void SetIfNestLevel( int newlevel )
/*********************************/
{
    blocknestlevel = newlevel;
    return;
}

/* init (called once per module) */

void CondInit( void )
/*******************/
{
    CurrIfState = BLOCK_ACTIVE;
    blocknestlevel = 0;
    falseblocknestlevel = 0;
}
