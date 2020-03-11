/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  implements the "fastpass" handling.
*               "fastpass" is an optimization which increases
*               assembly time speed by storing preprocessed lines
*               in memory during the first pass. In further passes,
*               those lines are "read" instead of the original assembly
*               source files.
*               Speed increase is significant if there's a large include
*               file at the top of an assembly source which contains
*               just equates and type definitions, because there's no need
*               to save such lines during pass one.
*
****************************************************************************/

#include <ctype.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "input.h"
#include "segment.h"
#include "fastpass.h"

#if FASTPASS

extern uint_32 list_pos;  /* current LST file position */

static struct mod_state modstate; /* struct to store assembly status */
static struct {
    struct line_item *head;
    struct line_item *tail;
} LineStore;
struct line_item *LineStoreCurr; /* must be global! */
bool StoreState;
bool UseSavedState;

/*
 * save the current status (happens in pass one only) and
 * switch to "save precompiled lines" mode.
 * the status is then restored in further passes,
 * and the precompiled lines are used for assembly then.
 */

static void SaveState( void )
/***************************/
{
    DebugMsg1(("SaveState enter\n" ));
    StoreState = TRUE;
    UseSavedState = TRUE;
    modstate.init = TRUE;
    modstate.Equ.head = modstate.Equ.tail = NULL;

    memcpy( &modstate.modinfo, (uint_8 *)&ModuleInfo + sizeof( struct module_vars ), sizeof( modstate.modinfo ) );

    SegmentSaveState();
    AssumeSaveState();
    ContextSaveState(); /* save pushcontext/popcontext stack */

    DebugMsg(( "SaveState exit\n" ));
}

void StoreLine( const char *srcline, int flags, uint_32 lst_position )
/********************************************************************/
{
    int i,j;
    char *p;

#ifdef DEBUG_OUT
    if ( Options.nofastpass )
        return;
#endif
    if ( ModuleInfo.GeneratedCode ) /* don't store generated lines! */
        return;
    if ( StoreState == FALSE ) /* line store already started? */
        SaveState();

    i = strlen( srcline );
    j = ( ( ( flags & 1 ) && ModuleInfo.CurrComment ) ? strlen( ModuleInfo.CurrComment ) : 0 );
    LineStoreCurr = LclAlloc( i + j + sizeof( struct line_item ) );
    LineStoreCurr->next = NULL;
    LineStoreCurr->lineno = GetLineNumber();
    if ( MacroLevel ) {
        LineStoreCurr->srcfile = 0xfff;
    } else {
        LineStoreCurr->srcfile = get_curr_srcfile();
    }
    LineStoreCurr->list_pos = ( lst_position ? lst_position : list_pos );
    if ( j ) {
        memcpy( LineStoreCurr->line, srcline, i );
        memcpy( LineStoreCurr->line + i, ModuleInfo.CurrComment, j + 1 );
    } else
        memcpy( LineStoreCurr->line, srcline, i + 1 );

    DebugMsg1(("StoreLine(>%s<, lst_position=%u): cur=%X\n", LineStoreCurr->line, lst_position, LineStoreCurr ));

    /* v2.08: don't store % operator at pos 0 */
    for ( p = LineStoreCurr->line; *p && isspace(*p); p++ );
    if (*p == '%' && ( _memicmp( p+1, "OUT", 3 ) || is_valid_id_char( *(p+4) ) ) )
        *p = ' ';

#ifdef DEBUG_OUT
    if ( Options.print_linestore )
        printf("%s\n", LineStoreCurr->line );
#endif
    if ( LineStore.head )
        LineStore.tail->next = LineStoreCurr;
    else
        LineStore.head = LineStoreCurr;
    LineStore.tail = LineStoreCurr;
}

/* an error has been detected in pass one. it should be
 reported in pass 2, so ensure that a full source scan is done then
 */

void SkipSavedState( void )
/*************************/
{
    DebugMsg(("SkipSavedState enter\n"));
    UseSavedState = FALSE;
}

/* for FASTPASS, just pass 1 is a full pass, the other passes
 don't start from scratch and they just assemble the preprocessed
 source. To be able to restart the assembly process from a certain
 location within the source, it's necessary to save the value of
 assembly time variables.
 However, to reduce the number of variables that are saved, an
 assembly-time variable is only saved when
 - it is changed
 - it was defined when StoreState() is called
 */

void SaveVariableState( struct asym *sym )
/****************************************/
{
    struct equ_item *p;

    DebugMsg1(( "SaveVariableState(%s)=%d\n", sym->name, sym->value ));
    sym->issaved = TRUE; /* don't try to save this symbol (anymore) */
    p = LclAlloc( sizeof( struct equ_item ) );
    p->next = NULL;
    p->sym = sym;
    p->lvalue    = sym->value;
    p->hvalue    = sym->value3264; /* v2.05: added */
    p->mem_type  = sym->mem_type;  /* v2.07: added */
    p->isdefined = sym->isdefined;
    if ( modstate.Equ.tail ) {
        modstate.Equ.tail->next = p;
        modstate.Equ.tail = p;
    } else {
        modstate.Equ.head = modstate.Equ.tail = p;
    }
//    printf("state of symbol >%s< saved, value=%u, defined=%u\n", sym->name, sym->value, sym->defined);
}

struct line_item *RestoreState( void )
/************************************/
{
    DebugMsg1(("RestoreState enter\n"));
    if ( modstate.init ) {
        struct equ_item *curr;
        /* restore values of assembly time variables */
        for ( curr = modstate.Equ.head; curr; curr = curr->next ) {
            DebugMsg1(("RestoreState: sym >%s<, value=%Xh (hvalue=%Xh), defined=%u\n", curr->sym->name, curr->lvalue, curr->hvalue, curr->isdefined ));
            /* v2.07: MT_ABS is obsolete */
            //if ( curr->sym->mem_type == MT_ABS ) {
                curr->sym->value     = curr->lvalue;
                curr->sym->value3264 = curr->hvalue;
                curr->sym->mem_type  = curr->mem_type; /* v2.07: added */
                curr->sym->isdefined = curr->isdefined;
            //}
        }
        /* fields in module_vars are not to be restored.
         * v2.10: the module_vars fields are not saved either.
         */
        //memcpy( &modstate.modinfo.g, &ModuleInfo.g, sizeof( ModuleInfo.g ) );
        memcpy( (char *)&ModuleInfo + sizeof( struct module_vars ), &modstate.modinfo, sizeof( modstate.modinfo ) );
        SetOfssize();
        SymSetCmpFunc();
    }

#if 0
    /* v2.05: AFAICS this can't happen anymore. */
    if ( LineStore.head == NULL ) {
        struct line_item *endl = LclAlloc( sizeof( struct line_item ) + 3 );
        endl->next = NULL;
        endl->srcfile = 0;
        endl->lineno = GetLineNumber();
        endl->list_pos = 0;
        strcpy( endl->line, "END");
        LineStore.head = endl;
        DebugMsg(("RestoreState: LineStore.head was NULL !!!\n" ));
    }
#endif
    return( LineStore.head );
}

#if FASTMEM==0
/* this is debugging code only. Usually FASTPASS and FASTMEM
 * are both either TRUE or FALSE.
 * It's active if both DEBUG and TRMEM is set in Makefile.
 */
void FreeLineStore( void )
/************************/
{
    struct line_item *next;
    for ( LineStoreCurr = LineStore.head; LineStoreCurr; ) {
        next = LineStoreCurr->next;
        LclFree( LineStoreCurr );
        LineStoreCurr = next;
    }
}
#endif

void FastpassInit( void )
/***********************/
{
    StoreState = FALSE;
    modstate.init = FALSE;
    LineStore.head = NULL;
    LineStore.tail = NULL;
    UseSavedState = FALSE;
}

#endif
