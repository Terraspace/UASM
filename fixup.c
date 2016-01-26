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
* Description:  handles fixups
*
****************************************************************************/

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "fixup.h"
#include "segment.h"
#include "omfspec.h"
#include "myassert.h"

#define GNURELOCS 1

extern struct asym *SegOverride;

int_8   Frame_Type;   /* curr fixup frame type: SEG|GRP|EXT|ABS|NONE; see omfspec.h */
uint_16 Frame_Datum;  /* curr fixup frame value */

struct fixup *CreateFixup( struct asym *sym, enum fixup_types type, enum fixup_options option )
/*********************************************************************************************/
/*
 * called when an instruction operand or a data item is relocatable:
 * - Parser.idata_fixup()
 * - Parser.memory_operand()
 * - branch.process_branch()
 * - data.data_item()
 * - dbgcv()
 * - fpfixup()
 * creates a new fixup item and initializes it using symbol <sym>.
 * put the correct target offset into the link list when forward reference of
 * relocatable is resolved;
 * Global vars Frame_Type and Frame_Datum "should" be set.
 */
{
#ifdef DEBUG_OUT
    static uint_32 cnt = 0;
#endif
    struct fixup     *fixup;

    fixup = LclAlloc( sizeof( struct fixup ) );
#ifdef TRMEM
    fixup->marker = 'XF';
    DebugMsg1(("CreateFixup, pass=%u: fix=%p sym=%s\n", Parse_Pass+1, fixup, sym ? sym->name : "NULL" ));
#endif

    /* add the fixup to the symbol's linked list (used for backpatch)
     * this is done for pass 1 only.
     */
    if ( Parse_Pass == PASS_1 ) {
#ifdef DEBUG_OUT
        if ( Options.nobackpatch == FALSE )
#endif
        if ( sym ) { /* changed v1.96 */
            fixup->nextbp = sym->bp_fixup;
            sym->bp_fixup = fixup;
        }
        /* v2.03: in pass one, create a linked list of
         * fixup locations for a segment. This is to improve
         * backpatching, because it allows to adjust fixup locations
         * after a distance has changed from short to near
         */
#ifdef DEBUG_OUT
        if ( Options.nobackpatch == FALSE )
#endif
        if ( CurrSeg ) {
            fixup->nextrlc = CurrSeg->e.seginfo->FixupList.head;
            CurrSeg->e.seginfo->FixupList.head = fixup;
        }
    }
    /* initialize locofs member with current offset.
     * It's unlikely to be the final location, but sufficiently exact for backpatching.
     */
    fixup->locofs = GetCurrOffset();
    fixup->offset = 0;
    fixup->type = type;
    fixup->option = option;
    fixup->flags = 0;
    fixup->frame_type = Frame_Type;     /* this is just a guess */
    fixup->frame_datum = Frame_Datum;
    fixup->def_seg = CurrSeg;           /* may be NULL (END directive) */
    fixup->sym = sym;

    DebugMsg1(("CreateFixup(sym=%s type=%u, opt=%u) cnt=%" I32_SPEC "X, loc=%" I32_SPEC "Xh\n",
        sym ? sym->name : "NULL", type, option, ++cnt, fixup->locofs ));
    return( fixup );
}

/* remove a fixup from the segment's fixup queue */

void FreeFixup( struct fixup *fixup )
/***********************************/
{
    struct dsym *dir;
    struct fixup *fixup2;

    if ( Parse_Pass == PASS_1 ) {
        dir = fixup->def_seg;
        if ( dir ) {
            if ( fixup == dir->e.seginfo->FixupList.head ) {
                dir->e.seginfo->FixupList.head = fixup->nextrlc;
            } else {
                for ( fixup2 = dir->e.seginfo->FixupList.head; fixup2; fixup2 = fixup2->nextrlc ) {
                    if ( fixup2->nextrlc == fixup ) {
                        fixup2->nextrlc = fixup->nextrlc;
                        break;
                    }
                }
            }
        }
    }
    LclFree( fixup );
}

/*
 * Set global variables Frame_Type and Frame_Datum.
 * segment override with a symbol (i.e. DGROUP )
 * it has been checked in the expression evaluator that the
 * symbol has type SYM_SEG/SYM_GRP.
 */

void SetFixupFrame( const struct asym *sym, char ign_grp )
/********************************************************/
{
    struct dsym *grp;

    if( sym ) {
        switch ( sym->state ) {
        case SYM_INTERNAL:
        case SYM_EXTERNAL:
            if( sym->segment != NULL ) {
                if( ign_grp == FALSE && ( grp = (struct dsym *)GetGroup( sym ) ) ) {
                    Frame_Type = FRAME_GRP;
                    Frame_Datum = grp->e.grpinfo->grp_idx;
                } else {
                    Frame_Type = FRAME_SEG;
                    Frame_Datum = GetSegIdx( sym->segment );
                }
            }
            break;
        case SYM_SEG:
            Frame_Type = FRAME_SEG;
            Frame_Datum = GetSegIdx( sym->segment );
            break;
        case SYM_GRP:
            Frame_Type = FRAME_GRP;
            Frame_Datum = ((struct dsym *)sym)->e.grpinfo->grp_idx;
            break;
#ifdef DEBUG_OUT
        case SYM_UNDEFINED:
        case SYM_STACK:
            break;
        default:
            DebugMsg(("SetFixupFrame(%s): unexpected state=%u\n", sym->name, sym->state ));
            /**/myassert( 0 );
            break;
#endif
        }
    }
}

/*
 * Store fixup information in segment's fixup linked list.
 * please note: forward references for backpatching are written in PASS 1 -
 * they no longer exist when store_fixup() is called.
 */

void store_fixup( struct fixup *fixup, struct dsym *seg, int_32 *pdata )
/**********************************************************************/
{
    //struct fixup     *fixup;

    //fixup = CodeInfo->InsFixup[index];

    //CodeInfo->data[index] = CodeInfo->data[index] - fixup->sym->offset;
    //fixup->offset = CodeInfo->data[index];
    fixup->offset = *pdata;

#ifdef DEBUG_OUT
    if ( fixup->sym )
        DebugMsg1(("store_fixup: type=%u, loc=%s.%" I32_SPEC "X, target=%s(%" I32_SPEC "X+% " I32_SPEC "X)\n",
                fixup->type, seg->sym.name, fixup->locofs, fixup->sym->name, fixup->sym->offset, fixup->offset ));
    else
        DebugMsg1(("store_fixup: type=%u, loc=%s.%" I32_SPEC "X, target=%" I32_SPEC "X\n",
                fixup->type, seg->sym.name, fixup->locofs, fixup->offset));
#endif

    fixup->nextrlc = NULL;
#if 0
    /* v2.07: no error checks here! store_fixup() is called only if pass > 1
     * and as long as write_to_file is true! This check is now done in
     * codegen() and data_item().
     */
    if ( ( 1 << fixup->type ) & ModuleInfo.fmtopt->invalid_fixup_type ) {
        EmitErr( UNSUPPORTED_FIXUP_TYPE,
               ModuleInfo.fmtopt->formatname,
               fixup->sym ? fixup->sym->name : szNull );
        return( ERROR );
    }
#endif
    if ( Options.output_format == OFORMAT_OMF ) {

        /* for OMF, the target's offset is stored at the fixup's location. */
        if( fixup->type != FIX_SEG && fixup->sym ) {
            *pdata += fixup->sym->offset;
        }

    } else {

#if ELF_SUPPORT
        if ( Options.output_format == OFORMAT_ELF ) {
            /* v2.07: inline addend for ELF32 only.
             * Also, in 64-bit, pdata may be a int_64 pointer (FIX_OFF64)!
             */
#if AMD64_SUPPORT
            if ( ModuleInfo.defOfssize == USE64 ) {
#if 0
                /* this won't work currently because fixup.offset may have to
                 * save *(int_64) pdata, but it is 32-bit only!
                 */
                if ( fixup->type == FIX_OFF64 )
                    *(int_64 *)pdata = 0;
                else
                    *pdata = 0;
#endif
            } else
#endif
            if ( fixup->type == FIX_RELOFF32 )
                *pdata = -4;
#if GNURELOCS /* v2.04: added */
            else if ( fixup->type == FIX_RELOFF16 )
                *pdata = -2;
            else if ( fixup->type == FIX_RELOFF8 )
                *pdata = -1;
#endif
        }
#endif
#if DJGPP_SUPPORT
        /* Djgpp's COFF variant needs special handling for
         * - at least - relative and direct 32-bit offsets.
         */
        if ( fixup->sym && ModuleInfo.sub_format == SFORMAT_DJGPP ) {
            if ( fixup->type == FIX_RELOFF32 ) { /* probably also for 16-bit */
                *pdata -= ( fixup->locofs + 4 );
            } else if ( fixup->type == FIX_OFF32 ) {
                *pdata += fixup->sym->offset;
                fixup->offset += fixup->sym->offset; /* ok? */
                fixup->segment = fixup->sym->segment;/* ok? */
            }
        } else
#endif
        /* special handling for assembly time variables needed */
        if ( fixup->sym && fixup->sym->variable ) {
            /* add symbol's offset to the fixup location and fixup's offset */
            *pdata += fixup->sym->offset;
            fixup->offset         += fixup->sym->offset;
            /* and save symbol's segment in fixup */
            fixup->segment_var = fixup->sym->segment;
        }
#if 0   /* fixup without symbol: this is to be resolved internally! */
        else if ( fixup->sym == NULL && fixup->frame == EMPTY ) {
            DebugMsg(("store_fixup: fixup skipped, symbol=0, no frame\n" ));
            return( NOT_ERROR );
        }
#endif
    }
    if( seg->e.seginfo->FixupList.head == NULL ) {
        seg->e.seginfo->FixupList.tail = seg->e.seginfo->FixupList.head = fixup;
    } else {
        seg->e.seginfo->FixupList.tail->nextrlc = fixup;
        seg->e.seginfo->FixupList.tail = fixup;
    }
    return;
}
