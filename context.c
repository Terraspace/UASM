/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:  Processing of PUSHCONTEXT and POPCONTEXT directives.
*
****************************************************************************/

#include <ctype.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "assume.h"
#include "expreval.h"
#include "fastpass.h"
#include "listing.h"

/* v2.10: static variables moved to ModuleInfo */
#define ContextStack ModuleInfo.g.ContextStack
#define ContextFree  ModuleInfo.g.ContextFree
#if FASTPASS
#define cntSavedContexts ModuleInfo.g.cntSavedContexts
#define SavedContexts ModuleInfo.g.SavedContexts
#endif

enum context_type {
    CONT_ASSUMES   = 0x01,
    CONT_RADIX     = 0x02,
    CONT_LISTING   = 0x04,
    CONT_CPU       = 0x08,
    CONT_ALIGNMENT = 0x10, /* new for v2.0, specific for Uasm */
    CONT_ALL       = CONT_ASSUMES | CONT_RADIX | CONT_LISTING | CONT_CPU,
};

static const enum context_type typetab[] = {
    CONT_ASSUMES, CONT_RADIX, CONT_LISTING, CONT_CPU, CONT_ALIGNMENT, CONT_ALL
};

static const char * const contextnames[] = {
    "ASSUMES", "RADIX", "LISTING", "CPU", "ALIGNMENT", "ALL"
};

#if AMD64_SUPPORT
#define NUM_STDREGS 16
#else
#define NUM_STDREGS 8
#endif

/* Masm has a max context nesting level of 10.
 * Uasm has no restriction currently.
 */

struct assumes_context {
    struct assume_info SegAssumeTable[NUM_SEGREGS];
    struct assume_info StdAssumeTable[NUM_STDREGS];
    struct stdassume_typeinfo type_content[NUM_STDREGS];
};

struct listing_context {
    enum listmacro list_macro;
    unsigned char list:1;
    unsigned char cref:1;
    unsigned char listif:1;
    unsigned char list_generated_code:1;
};

struct cpu_context {
    short cpu;              /* saved ModuleInfo.cpu      */
    enum cpu_info curr_cpu; /* saved ModuleInfo.curr_cpu */
};

struct radix_context {
    uint_8 radix; /* saved ModuleInfo.radix */
};

struct alignment_context {
    uint_8 fieldalign; /* saved ModuleInfo.fieldalign */
    uint_8 procalign;  /* saved ModuleInfo.procalign */
};

/* v2.10: the type-specific data is now declared as a union;
 * and PUSH|POPCONTEXT ALL will push/pop 4 single items.
 * all items are equal in size, this made it possible to implement
 * a "free items" heap.
 */
struct context {
    struct context *next;
    enum context_type type;
    union {
        struct radix_context   rc;
        struct alignment_context alc;
        struct listing_context lc;
        struct cpu_context     cc;
        struct assumes_context ac;
    };
};

extern struct asym *sym_Cpu;

/* v2.10: major rewrite of this function */

ret_code ContextDirective( int i, struct asm_tok tokenarray[] )
/*************************************************************/
{
    int start = i;
    int directive = tokenarray[i].tokval;
    enum context_type type;
    int j;
    struct context *curr;

    DebugMsg(( "%s directive enter\n", tokenarray[i].string_ptr ));

    i++; /* skip CONTEXT keyword */

    while ( tokenarray[i].token == T_ID ) {
        for ( j = 0, type = -1; j < ( sizeof(typetab) / sizeof(typetab[0]) ); j++ ) {
            if ( _stricmp( contextnames[j], tokenarray[i].string_ptr ) == 0 ) {
                type = typetab[j];
                break;
            }
        }

        if ( type == -1 )
            break;

        /* reject ALIGNMENT if strict masm compat is on */
        if ( Options.strict_masm_compat ) {
            if ( type == CONT_ALIGNMENT )
                break;
            else
                type &= ~CONT_ALIGNMENT; /* in case ALIGNMENT is again included in ALL */
        }

        if ( directive == T_POPCONTEXT ) {
            struct context *prev;
            struct context *next;
            DebugMsg(( "POPCONTEXT type=%X\n", type ));
            /* for POPCONTEXT, check if appropriate items are on the stack */
            for ( prev = NULL, curr = ContextStack; curr && type; curr = next ) {

                DebugMsg(( "POPCONTEXT: found item with type=%X\n", curr->type ));
                next = curr->next;
                /* matching item on the stack? */
                if ( !( curr->type & type ) ) {
                    prev = curr;
                    continue;
                }

                type &= ~curr->type;
                if ( prev )
                    prev->next = next;
                else
                    ContextStack = next;

                curr->next = ContextFree;
                ContextFree = curr;

                /* restore the values */
                switch ( curr->type ) {
                case CONT_ASSUMES:
                    SetSegAssumeTable( curr->ac.SegAssumeTable );
                    SetStdAssumeTable( curr->ac.StdAssumeTable, curr->ac.type_content );
                    break;
                case CONT_RADIX:
                    ModuleInfo.radix = curr->rc.radix;
                    break;
                case CONT_ALIGNMENT:
                    ModuleInfo.fieldalign = curr->alc.fieldalign;
                    ModuleInfo.procalign  = curr->alc.procalign;
                    break;
                case CONT_LISTING:
                    ModuleInfo.list_macro = curr->lc.list_macro;
                    ModuleInfo.list       = curr->lc.list;
                    ModuleInfo.cref       = curr->lc.cref;
                    ModuleInfo.listif     = curr->lc.listif;
                    ModuleInfo.list_generated_code = curr->lc.list_generated_code;
                    break;
                case CONT_CPU:
                    ModuleInfo.cpu      = curr->cc.cpu;
                    if ( sym_Cpu )
                        sym_Cpu->value  = curr->cc.cpu;
                    ModuleInfo.curr_cpu = curr->cc.curr_cpu;
                }
            }
            if ( type ) {
                DebugMsg(( "POPCONTEXT error, remaining type flags=%X\n", type ));
                return( EmitErr( UNMATCHED_BLOCK_NESTING, tokenarray[start].tokpos ) );
            }
        } else {
            DebugMsg(( "PUSHCONTEXT type=%X\n", type ));
            for ( j = 0; j < ( sizeof(typetab) / sizeof(typetab[0] ) ) && type; j++ ) {
                if ( type & typetab[j] ) {

                    type &= ~typetab[j];

                    if ( ContextFree ) {
                        curr = ContextFree;
                        ContextFree = curr->next;
                    } else
                        curr = LclAlloc( sizeof( struct context ) );

                    curr->type = typetab[j];
                    curr->next = ContextStack;
                    ContextStack = curr;

                    switch ( typetab[j] ) {
                    case CONT_ASSUMES:
                        GetSegAssumeTable( curr->ac.SegAssumeTable );
                        GetStdAssumeTable( curr->ac.StdAssumeTable, curr->ac.type_content );
                        break;
                    case CONT_RADIX:
                        curr->rc.radix = ModuleInfo.radix;
                        break;
                    case CONT_ALIGNMENT:
                        curr->alc.fieldalign = ModuleInfo.fieldalign;
                        curr->alc.procalign  = ModuleInfo.procalign;
                        break;
                    case CONT_LISTING:
                        curr->lc.list_macro = ModuleInfo.list_macro;
                        curr->lc.list       = ModuleInfo.list;
                        curr->lc.cref       = ModuleInfo.cref;
                        curr->lc.listif     = ModuleInfo.listif;
                        curr->lc.list_generated_code = ModuleInfo.list_generated_code;
                        break;
                    case CONT_CPU:
                        curr->cc.cpu      = ModuleInfo.cpu;
                        curr->cc.curr_cpu = ModuleInfo.curr_cpu;
                        break;
                    }
                }
            }
        }

        i++;
        if ( tokenarray[i].token == T_COMMA && tokenarray[i+1].token != T_FINAL )
            i++;
    }

    if ( tokenarray[i].token != T_FINAL || type == -1 ) {
        return( EmitErr( SYNTAX_ERROR_EX, tokenarray[i].tokpos ) );
    }

    return( NOT_ERROR );
}

#if FASTPASS

/* save current context status */

void ContextSaveState( void )
/***************************/
{
    int i;
    struct context *src;
    struct context *dst;

    for ( i = 0, src = ContextStack ; src ; i++, src = src->next );

    if ( i ) {
        cntSavedContexts = i;
        SavedContexts = LclAlloc( i * sizeof( struct context ) );
        DebugMsg(( "ContextSaveState: SavedContexts=%X\n", SavedContexts ));
        for ( src = ContextStack, dst = SavedContexts ; src ; src = src->next, dst++ ) {
            memcpy( dst, src, sizeof( struct context ) );
        }
    }
}

/* restore context status */

static void ContextRestoreState( void )
/*************************************/
{
    int i;
    struct context *dst;

    for ( i = cntSavedContexts ; i ; i-- ) {
        if ( ContextFree ) {
            dst = ContextFree;
            ContextFree = dst->next;
        } else
            dst = LclAlloc( sizeof( struct context ) );
        memcpy( dst, &SavedContexts[i-1], sizeof( struct context ) );
        dst->next = ContextStack;
        ContextStack = dst;
    }
}

#endif

/* init context, called once per pass */

void ContextInit( int pass )
/**************************/
{
    /* if ContextStack isn't NULL, then at least one PUSHCONTEXT
     * didn't have a matching POPCONTEXT. No need to reset it to NULL -
     * but might be ok to move the items to the ContextFree heap.
     */
    //ContextStack = NULL;
#if FASTPASS
    if ( pass > PASS_1 ) {
        ContextRestoreState();
    }
#endif
}
#if FASTMEM==0
void ContextFini( void )
/**********************/
{
    struct context *curr;
    struct context *next;
    /* release the items in the ContextFree heap.
     * there might also be some left in ContextStack...
     */
    for ( curr = ContextFree; curr; curr = next ) {
        next = curr->next;
        LclFree( curr );
    }
}
#endif

