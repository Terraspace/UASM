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
* Description:  FP fixups for 16-bit code. These fixups allow the linker
* or program loader to replace FP instructions by calls to an FP emulation
* library.
*
****************************************************************************/

#include "globals.h"
#include "parser.h"
#include "extern.h"
#include "fixup.h"
#include "mangle.h"
#include "myassert.h"
#include "segment.h"
#include "omf.h"
#include "omfspec.h"

enum fp_patches {
    FPP_WAIT,
    FPP_NORMAL,
    FPP_ES, /* last 6 entries match order of ASSUME_ES, ... */
    FPP_CS,
    FPP_SS,
    FPP_DS,
    FPP_FS,
    FPP_GS
};

/* FP 16-bit fixup names.
 * Known by MS VC, Open Watcom, Borland and Digital Mars:
 *  FIWRQQ, FIDRQQ, FIERQQ, FICRQQ, FISRQQ, FIARQQ, FIFRQQ, FIGRQQ,
 *                          FJCRQQ, FJSRQQ, FJARQQ, FJFRQQ, FJGRQQ
 */

static const uint_16 patchmask = 0xF8FF;

static const char patchchr2[] = {
    'W', 'D', 'E', 'C', 'S', 'A', 'F', 'G'
};

void AddFloatingPointEmulationFixup( struct code_info *CodeInfo )
/***************************************************************/
{
    int i;
    enum fp_patches patch;
    struct asym *sym[2];
    struct fixup *fixup;
    int_32 data;
    char name[8] = "F__RQQ";

    DebugMsg(("AddFloatingPointEmulationFixup enter, token=%u, regoverride=%d\n", CodeInfo->token, CodeInfo->prefix.RegOverride ));

    if( CodeInfo->token == T_FWAIT ) {
        patch = FPP_WAIT;
    } else if ( CodeInfo->prefix.RegOverride == EMPTY ) {
        patch = FPP_NORMAL;
    } else {
        patch = CodeInfo->prefix.RegOverride + 2;
    }

    /* emit 1-2 externals for the patch if not done already */
    for ( i = 0; i < 2; i++ ) {
        sym[i] = NULL;
        if ( patchmask & ( 1 << ( i*8+patch ) ) ) {
            name[1] = 'I' + i;
            name[2] = patchchr2[patch];
            sym[i] = SymSearch( name );
            if( sym[i] == NULL || sym[i]->state == SYM_UNDEFINED ) {
                sym[i] = MakeExtern( name, MT_FAR, NULL, sym[i], USE16 );
                sym[i]->langtype = LANG_NONE;
            }
        }
    }

    /* no need for fixups if no object file is written */
    if ( write_to_file == FALSE )
        return;

    /* make sure the next 3 bytes in code stream aren't separated.
     * The first fixup covers bytes $+0 and $+1, the (possible) second
     * fixup covers bytes $+1 and $+2.
     */
    if( Options.output_format == OFORMAT_OMF &&
       ( CurrSeg->e.seginfo->current_loc - CurrSeg->e.seginfo->start_loc + 3 ) > MAX_LEDATA_THRESHOLD )
        omf_FlushCurrSeg();

    for ( i = 0; i < 2 ; i++ ) {
        if ( sym[i] ) {
            fixup = CreateFixup( sym[i], FIX_OFF16, OPTJ_NONE );
            fixup->frame_type = FRAME_TARG;
            /* assume locofs has been set inside CreateFixup() */
            //fixup->locofs = CurrSeg->e.seginfo->current_loc + i;
            fixup->locofs += i;
            data = 0;
            store_fixup( fixup, CurrSeg, &data );
        }
    }
    return;
}
