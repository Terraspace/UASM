/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  preprocessor
*
****************************************************************************/

#include <ctype.h>
#include <stdarg.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "condasm.h"
#include "tokenize.h"
#include "equate.h"
#include "macro.h"
#include "input.h"
#include "fastpass.h"
#include "listing.h"

#define REMOVECOMENT 0 /* 1=remove comments from source       */

extern ret_code (* const directive_tab[])( int, struct asm_tok[] );

#ifdef DEBUG_OUT
int_32 cntppl0;    /* count preprocessed lines 1 */
int_32 cntppl1;    /* count preprocessed lines 2 */
int_32 cntppl2;    /* count lines NOT handled by preprocessor */
#endif

/* preprocessor directive or macro procedure is preceded
 * by a code label.
 */
ret_code WriteCodeLabel( char *line, struct asm_tok tokenarray[] )
/****************************************************************/
{
    int oldcnt;
    int oldtoken;
    char oldchar;

    if ( tokenarray[0].token != T_ID ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[0].string_ptr ) );
    }
    /* ensure the listing is written with the FULL source line */
    if ( CurrFile[LST] ) LstWrite( LSTTYPE_LABEL, 0, NULL );
    /* v2.04: call ParseLine() to parse the "label" part of the line */
    oldcnt = Token_Count;
    oldtoken = tokenarray[2].token;
    oldchar = *tokenarray[2].tokpos;
    Token_Count = 2;
    tokenarray[2].token = T_FINAL;
    *tokenarray[2].tokpos = NULLC;
    ParseLine( tokenarray );
    if ( Options.preprocessor_stdout == TRUE )
        WritePreprocessedLine( line );
    Token_Count = oldcnt;
    tokenarray[2].token = oldtoken;
    *tokenarray[2].tokpos = oldchar;
    return( NOT_ERROR );
}

/* PreprocessLine() is the "preprocessor".
 * 1. the line is tokenized with Tokenize(), Token_Count set
 * 2. (text) macros are expanded by ExpandLine()
 * 3. "preprocessor" directives are executed
 */
int PreprocessLine( char *line, struct asm_tok tokenarray[] )
/***********************************************************/
{
    int i;

    /* v2.11: GetTextLine() removed - this is now done in ProcessFile() */

    /* v2.08: moved here from GetTextLine() */
    ModuleInfo.CurrComment = NULL;
    /* v2.06: moved here from Tokenize() */
    ModuleInfo.line_flags = 0;
    /* Token_Count is the number of tokens scanned */
    Token_Count = Tokenize( line, 0, tokenarray, TOK_DEFAULT );

#ifdef DEBUG_OUT
    cntppl0++;
    if ( ModuleInfo.GeneratedCode )
        DebugMsg1(("PreprocessLine: >%s<\n", line ));
    else
        DebugMsg1(("PreprocessLine(%s): >%s< cmt=%s\n", GetTopSrcName(), line, ModuleInfo.CurrComment ? ModuleInfo.CurrComment : "" ));
#endif

#if REMOVECOMENT == 0
    if ( Token_Count == 0 && ( CurrIfState == BLOCK_ACTIVE || ModuleInfo.listif ) )
        LstWriteSrcLine();
#endif

    if ( Token_Count == 0 )
        return( 0 );

#ifdef DEBUG_OUT
    /* option -np, skip preprocessor? */
    if ( Options.skip_preprocessor )
        return( Token_Count );
#endif

    /* CurrIfState != BLOCK_ACTIVE && Token_Count == 1 | 3 may happen
     * if a conditional assembly directive has been detected by Tokenize().
     * However, it's important NOT to expand then */
    if ( CurrIfState == BLOCK_ACTIVE ) {
        if ( ( tokenarray[Token_Count].bytval & TF3_EXPANSION ? ExpandText( line, tokenarray, TRUE ) : ExpandLine( line, tokenarray ) ) < NOT_ERROR )
            return( 0 );
    }

    DebugCmd( cntppl1++ );

    i = 0;
    if ( Token_Count > 2 && ( tokenarray[1].token == T_COLON || tokenarray[1].token == T_DBL_COLON ) )
        i = 2;

    /* handle "preprocessor" directives:
     * IF, ELSE, ENDIF, ...
     * FOR, REPEAT, WHILE, ...
     * PURGE
     * INCLUDE
     * since v2.05, error directives are no longer handled here!
     */
    if ( tokenarray[i].token == T_DIRECTIVE &&
        tokenarray[i].dirtype <= DRT_INCLUDE ) {

        /* if i != 0, then a code label is located before the directive */
        if ( i > 1 ) {
            if ( ERROR == WriteCodeLabel( line, tokenarray ) )
                return( 0 );
        }
        directive_tab[tokenarray[i].dirtype]( i, tokenarray );
        return( 0 );
    }

    /* handle preprocessor directives which need a label */

    if ( tokenarray[0].token == T_ID && tokenarray[1].token == T_DIRECTIVE ) {
        struct asym *sym;
        switch ( tokenarray[1].dirtype ) {
        case DRT_EQU:
            /*
             * EQU is a special case:
             * If an EQU directive defines a text equate
             * it MUST be handled HERE and 0 must be returned to the caller.
             * This will prevent further processing, nothing will be stored
             * if FASTPASS is on.
             * Since one cannot decide whether EQU defines a text equate or
             * a number before it has scanned its argument, we'll have to
             * handle it in ANY case and if it defines a number, the line
             * must be stored and, if -EP is set, written to stdout.
             */
            if ( sym = CreateConstant( tokenarray ) ) {
                if ( sym->state != SYM_TMACRO ) {
#if FASTPASS
                    if ( StoreState ) FStoreLine( 0 );
#endif
                    if ( Options.preprocessor_stdout == TRUE )
                        WritePreprocessedLine( line );
                }
                /* v2.03: LstWrite() must be called AFTER StoreLine()! */
                if ( ModuleInfo.list == TRUE ) {
                    LstWrite( sym->state == SYM_INTERNAL ? LSTTYPE_EQUATE : LSTTYPE_TMACRO, 0, sym );
                }
            }
            return( 0 );
        case DRT_MACRO:
        case DRT_CATSTR: /* CATSTR + TEXTEQU directives */
        case DRT_SUBSTR:
            directive_tab[tokenarray[1].dirtype]( 1, tokenarray );
            return( 0 );
        }
    }

    DebugCmd( cntppl2++ );
    return( Token_Count );
}

