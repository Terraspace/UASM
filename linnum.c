/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  handles line numbers if -Zd or -Zi is set.
*
****************************************************************************/

#include <ctype.h>
#include <time.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "input.h"
#include "tokenize.h"
#include "segment.h"
#include "assume.h"
#include "proc.h"
#include "expreval.h"
#include "extern.h"
#include "fastpass.h"
#include "msgtext.h"
#include "myassert.h"
#include "linnum.h"
#include "omf.h"

extern struct qdesc   LinnumQueue;    /* queue of line_num_info items ( OMF only ) */
extern int            procidx;

#if COFF_SUPPORT
static struct asym    *dmyproc;
#endif
static uint_32        lastLineNumber;

static void AddLinnumData( struct line_num_info *data )
/*****************************************************/
{
    struct qdesc *q;
#if COFF_SUPPORT
    if ( Options.output_format == OFORMAT_COFF ) {
        q = (struct qdesc *)CurrSeg->e.seginfo->LinnumQueue;
        if ( q == NULL ) {
            q = LclAlloc( sizeof( struct qdesc ) );
            CurrSeg->e.seginfo->LinnumQueue = q;
            q->head = NULL;
        }
    } else
#endif
        q = &LinnumQueue;

    data->next = NULL;
    if ( q->head == NULL)
        q->head = q->tail = data;
    else {
        ((struct line_num_info *)q->tail)->next = data;
        q->tail = data;
    }
}

/* store a reference for the current line at the current address
 * called by
 * - codegen.output_opc()
 * - proc.ProcDir() - in COFF, line_num is 0 then
 */

void AddLinnumDataRef( unsigned srcfile, uint_32 line_num )
/*********************************************************/
{
    struct line_num_info    *curr;

#if COFF_SUPPORT
    /* COFF line number info is related to functions/procedures. Since
     * assembly allows code lines outside of procs, "dummy" procs must
     * be generated. A dummy proc lasts until
     * - a true PROC is detected or
     * - the source file changes or
     * - the segment/section changes ( added in v2.11 )
     */
    if ( Options.output_format == OFORMAT_COFF &&
        CurrProc == NULL &&
        ( dmyproc == NULL ||
        dmyproc->debuginfo->file != srcfile ||
        dmyproc->segment != (struct asym *)CurrSeg ) ) {
        char procname[12];
        if ( dmyproc ) {
            /**/myassert( dmyproc->segment );
            dmyproc->total_size =
                ((struct dsym *)dmyproc->segment)->e.seginfo->current_loc -
                dmyproc->offset;
        }
        sprintf( procname, "$$$%05u", procidx );
        DebugMsg1(("AddLinnumDataRef(src=%u.%u): CurrProc==NULL, dmyproc=%s searching proc=%s\n", srcfile, line_num, dmyproc ? dmyproc->name : "NULL", procname ));
        dmyproc = SymSearch( procname );

        /* in pass 1, create the proc */
        if ( dmyproc == NULL ) {
            dmyproc = CreateProc( NULL, procname, SYM_INTERNAL );
            DebugMsg1(("AddLinnumDataRef: new proc %s created\n", procname ));
            dmyproc->isproc = TRUE; /* flag is usually set inside ParseProc() */
            dmyproc->included = TRUE;
            AddPublicData( dmyproc );
        } else
            procidx++; /* for passes > 1, adjust procidx */

        /* if the symbols isn't a PROC, the symbol name has been used
         * by the user - bad! A warning should be displayed */
        if ( dmyproc->isproc == TRUE ) {
            SetSymSegOfs( dmyproc );
            dmyproc->Ofssize = ModuleInfo.Ofssize;
            dmyproc->langtype = ModuleInfo.langtype;
            if ( write_to_file == TRUE ) {
                curr = LclAlloc( sizeof( struct line_num_info ) );
                curr->sym = dmyproc;
                curr->line_number = GetLineNumber();
                curr->file = srcfile;
                curr->number = 0;
                DebugMsg1(("AddLinnumDataRef: CURRPROC=NULL, sym=%s, calling AddLinnumData(src=%u.%u)\n", curr->sym->name, curr->file, curr->line_number ));
                AddLinnumData( curr );
            }
        }
    }
#endif

    if(  line_num && ( write_to_file == FALSE || lastLineNumber == line_num )) {
#ifdef DEBUG_OUT
        if ( write_to_file == TRUE )
            DebugMsg1(("AddLinnumDataRef(src=%u.%u) line skipped, lastline=%u\n", srcfile, line_num, lastLineNumber ));
#endif
        return;
    }
    DebugMsg1(("AddLinnumDataRef(src=%u.%u): currofs=%Xh, CurrProc=%s, GeneratedCode=%u\n", srcfile, line_num, GetCurrOffset(), CurrProc ? CurrProc->sym.name : "NULL", ModuleInfo.GeneratedCode ));

    curr = LclAlloc( sizeof( struct line_num_info ) );
    curr->number = line_num;
#if COFF_SUPPORT
    if ( line_num == 0 ) { /* happens for COFF only */
        /* changed v2.03 (CurrProc might have been NULL) */
        /* if ( Options.output_format == OFORMAT_COFF && CurrProc->sym.public == FALSE ) { */
        /* v2.09: avoid duplicates, check for pass 1 */
        //if ( Options.output_format == OFORMAT_COFF && CurrProc && CurrProc->sym.public == FALSE ) {
        if ( Parse_Pass == PASS_1 &&
            Options.output_format == OFORMAT_COFF && CurrProc && CurrProc->sym.ispublic == FALSE ) {
            CurrProc->sym.included = TRUE;
            AddPublicData( (struct asym *)CurrProc );
        }
        /* changed v2.03 */
        /* curr->sym = (struct asym *)CurrProc; */
        curr->sym = ( CurrProc ? (struct asym *)CurrProc : dmyproc );
        curr->line_number = GetLineNumber();
        curr->file        = srcfile;
        /* set the function's size! */
        if ( dmyproc ) {
            /**/myassert( dmyproc->segment );
            dmyproc->total_size =
                ((struct dsym *)dmyproc->segment)->e.seginfo->current_loc -
                dmyproc->offset;
            dmyproc = NULL;
        }
        /* v2.11: write a 0x7fff line item if prologue exists */
        if ( CurrProc && CurrProc->e.procinfo->size_prolog ) {
            DebugMsg1(("AddLinnumDataRef: calling AddLinnumData(src=%u.%u) sym=%s\n", curr->file, curr->line_number, curr->sym->name ));
            AddLinnumData( curr );
            curr = LclAlloc( sizeof( struct line_num_info ) );
            curr->number = GetLineNumber();
            curr->offset = GetCurrOffset();
            curr->srcfile = srcfile;
        }
    } else {
#endif
        curr->offset = GetCurrOffset();
        curr->srcfile = srcfile;
#if COFF_SUPPORT
    }
#endif
    lastLineNumber = line_num;

    /* v2.11: added, improved multi source support for CV.
     * Also, the size of line number info could have become > 1024,
     * ( even > 4096, thus causing an "internal error in omfint.c" )
     */
    if ( Options.output_format == OFORMAT_OMF )
        omf_check_flush( curr );

    /* v2.10: warning if line-numbers for segments without class code! */
    if ( CurrSeg->e.seginfo->linnum_init == FALSE ) {
        CurrSeg->e.seginfo->linnum_init = TRUE;
        if ( TypeFromClassName( CurrSeg, CurrSeg->e.seginfo->clsym ) != SEGTYPE_CODE ) {
            EmitWarn( 2, LINNUM_INFO_FOR_SEGMENT_WITHOUT_CLASS_CODE, CurrSeg->sym.name );
        }
    }
    DebugMsg1(("AddLinnumDataRef: calling AddLinnumData(src=%u.%u ofs=%X)\n", curr->number == 0 ? curr->file : curr->srcfile, curr->number, curr->offset ));
    AddLinnumData( curr );

    return;
}

void QueueDeleteLinnum( struct qdesc *queue )
/*******************************************/
{
    struct line_num_info    *curr;
    struct line_num_info    *next;

    if ( queue == NULL )
        return;
    curr = queue->head;
    for( ; curr ; curr = next ) {
        next = curr->next;
        LclFree( curr );
    }
    return;
}

/* if -Zd is set and there is trailing code not inside
 * a function, set the dummy function's length now.
 */
void LinnumFini( void )
/*********************/
{
#if COFF_SUPPORT
    if ( dmyproc ) {
        dmyproc->total_size =
            ((struct dsym *)dmyproc->segment)->e.seginfo->current_loc -
            dmyproc->offset;
        DebugMsg(("LinnumFini: last dummy proc size=%Xh\n"));
    }
#endif
}

void LinnumInit( void )
/*********************/
{
    lastLineNumber = 0;
#if COFF_SUPPORT
    dmyproc = NULL;
#endif
}
