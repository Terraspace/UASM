/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  processes directive .SAFESEH
*
****************************************************************************/

#include <ctype.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"

#include "myassert.h"

#if COFF_SUPPORT

/* .SAFESEH works for coff format only.
 * syntax is: .SAFESEH handler
 * <handler> must be a PROC or PROTO
 */

ret_code SafeSEHDirective( int i, struct asm_tok tokenarray[] )
/*************************************************************/
{
    struct asym    *sym;
    struct qnode   *node;

    if ( Options.output_format != OFORMAT_COFF ) {
        if ( Parse_Pass == PASS_1)
            EmitWarn( 2, DIRECTIVE_IGNORED_WITHOUT_X, "coff" );
        return( NOT_ERROR );
    }
    if ( Options.safeseh == FALSE ) {
        if ( Parse_Pass == PASS_1)
            EmitWarn( 2, DIRECTIVE_IGNORED_WITHOUT_X, "safeseh" );
        return( NOT_ERROR );
    }
    i++;
    if ( tokenarray[i].token != T_ID ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
    }
    sym = SymSearch( tokenarray[i].string_ptr );

    /* make sure the argument is a true PROC */
    if ( sym == NULL || sym->state == SYM_UNDEFINED ) {
        if ( Parse_Pass != PASS_1 ) {
            return( EmitErr( SYMBOL_NOT_DEFINED, tokenarray[i].string_ptr ) );
        }
    } else if ( sym->isproc == FALSE ) {
        return( EmitErr( SAFESEH_ARGUMENT_MUST_BE_A_PROC, tokenarray[i].string_ptr ) );
    }

    if ( Parse_Pass == PASS_1 ) {
        if ( sym ) {
            for ( node = ModuleInfo.g.SafeSEHQueue.head; node; node = node->next )
                if ( node->elmt == sym )
                    break;
        } else {
            sym = SymCreate( tokenarray[i].string_ptr );
            node = NULL;
        }
        if ( node == NULL ) {
            sym->used = TRUE; /* make sure an external reference will become strong */
#if 0 /* v2.11: use QAddItem() */
            node = LclAlloc( sizeof( struct qnode ) );
            node->elmt = sym;
            node->next = NULL;
            if ( ModuleInfo.g.SafeSEHQueue.head == 0 )
                ModuleInfo.g.SafeSEHQueue.head = ModuleInfo.g.SafeSEHQueue.tail = node;
            else {
                ((struct qnode *)ModuleInfo.g.SafeSEHQueue.tail)->next = node;
                ModuleInfo.g.SafeSEHQueue.tail = node;
            }
#else
            QAddItem( &ModuleInfo.g.SafeSEHQueue, sym );
#endif
        }
    }
    i++;
    if ( tokenarray[i].token != T_FINAL ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].string_ptr ) );
    }

    return( NOT_ERROR );
}
#endif

