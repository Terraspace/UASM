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
* Description:  handle OMF fixups
*
****************************************************************************/

#include <stddef.h>

#include "globals.h"
#include "parser.h"
#include "segment.h"
#include "fixup.h"
#include "omfint.h"
#include "omfspec.h"
#include "myassert.h"

extern const char szNull[];
extern unsigned omf_GetGrpIdx( struct asym *sym );

/* logical data for fixup subrecord creation */
struct logref {
    uint_8  frame;          /* see enum frame_methods in omfspec.h      */
    uint_16 frame_datum;    /* datum for certain frame methods          */
    uint_8  is_secondary;   /* can write target in a secondary manner   */
    uint_8  target;         /* see enum target_methods in omfspec.h     */
    uint_16 target_datum;   /* datum for certain target methods         */
    int_32  target_offset;  /* offset of target for target method       */
};

static uint_8 *putIndex( uint_8 *p, uint_16 index )
/*************************************************/
{
    if( index > 0x7f ) {
        *p++ = 0x80 | ( index >> 8 );
    }
    *p++ = index;
    return( p );
}

static uint_8 *put16( uint_8 *p, uint_16 value )
/**********************************************/
{
    WriteU16( p, value );
    return( p + sizeof( uint_16 ) );
}

static uint_8 *put32( uint_8 *p, uint_32 value )
/**********************************************/
{
    WriteU32( p, value );
    return( p + sizeof( uint_32 ) );
}

static uint_8 *putFrameDatum( uint_8 *p, uint_8 method, uint_16 datum )
/*********************************************************************/
{
    switch( method ) {
    case FRAME_SEG:
    case FRAME_GRP:
    case FRAME_EXT:
        return( putIndex( p, datum ) );
#if 0  /* v2.12: FRAME_ABS is invalid according to TIS OMF docs. */
    case FRAME_ABS:
        return( put16( p, datum ) );
#endif
    }
    /* for FRAME_LOC & FRAME_TARG ( & FRAME_NONE ) there's no datum to write. */
    return( p );
}

static uint_8 *putTargetDatum( uint_8 *p, uint_8 method, uint_16 datum )
/**********************************************************************/
{
#if 0 /* v2.12: Uasm won't use TARGE_ABSxx; also, it's not defined for FIXUP sub-records */
    if( ( method & 0x03 ) == TARGET_ABSWD ) {
        return( put16( p, datum ) );
    }
#endif
    return( putIndex( p, datum ) );
}

/* translate logref to FIXUP subrecord ( without Locat field ).
 * fields written to buf:
 * - uint_8     Fix Data (type of frame and target)
 * - index      Frame Datum (optional, index of a SEGDEF, GRPDEF or EXTDEF)
 * - index      Target Datum (index of a SEGDEF, GRPDEF or EXTDEF)
 * - uint_16/32 Target Displacement (optional)
 *
 * type is FIX_GEN_INTEL or FIX_GEN_MS386
 * v2.12: new function OmfFixGetFixModend() replaced code in writeModend(),
 *        TranslateLogref() has become static.
 */

static unsigned TranslateLogref( const struct logref *lr, uint_8 *buf, enum fixgen_types type )
/*********************************************************************************************/
{
    uint_8  *p;
    uint_8  target;

    /**/myassert( lr != NULL );
    /**/myassert( buf != NULL );
    /**/myassert( type == FIX_GEN_INTEL || type == FIX_GEN_MS386 );

    /*
     * According to the discussion on p102 of the Intel OMF document, we
     * cannot just arbitrarily write fixups without a displacment if their
     * displacement field is 0.  So we use the is_secondary field.
     */
    target = lr->target;
    if( lr->target_offset == 0 && lr->is_secondary ) {
        target |= 0x04; /* P=1 -> no displacement field */
    }
    p = buf;
    /* write the "Fix Data" field, FfffTPtt:
     * F  : 0 = frame method is defined in fff field ( F0-F5)
     *      1 = frame is defined by a thread ( won't occur here )
     * fff: frame method
     * T  : 0 = target is defined by tt
     *      1 = target is defined by thread# in tt, P is used as bit 2 for method
     * P  : 0 = target displacement field is present
     *      1 = no displacement field
     * tt : target method
     */
    *p++ = ( lr->frame << 4 ) | ( target );
    p = putFrameDatum( p, lr->frame, lr->frame_datum );
    p = putTargetDatum( p, target, lr->target_datum );
    if( ( target & 0x04 ) == 0 ) {
        if( type == FIX_GEN_MS386 ) {
            p = put32( p, (uint_32)lr->target_offset );
        } else {
            p = put16( p, (uint_16)lr->target_offset );
        }
    }
    return( p - buf );
}

#if 0 /* v2.11: obsolete */

static uint TranslatePhysref( const struct physref *ref, uint_8 *buf, enum fixgen_types type )
/********************************************************************************************/
{
    uint_8  *p;

    /**/myassert( ref != NULL );
    /**/myassert( buf != NULL );
    /**/myassert( type == FIX_GEN_INTEL || type == FIX_GEN_MS386 );

    p = put16( buf, ref->frame );
    p = put16( p, ref->offset );
    return( p - buf );
}

/* used when the MODEND record is written.
 * is_logical is always 1 then.
 * v2.11: obsolete. TranslateLogref() is now called directly by writeModend() in omfint.c
 */

unsigned TranslateRef( const union logphys *ref, int is_logical, uint_8 *buf, enum fixgen_types type )
/****************************************************************************************************/
{
    return( is_logical ? TranslateLogref( &ref->log, buf, type ) : TranslatePhysref( &ref->phys, buf, type ) );
}

#endif

/* generate start address subfield for MODEND */

unsigned OmfFixGenFixModend( const struct fixup *fixup, uint_8 *buf, uint_32 displ, enum fixgen_types type )
/**********************************************************************************************************/
{
    struct asym *sym = fixup->sym;
    struct logref lr;

    lr.is_secondary = FALSE;
    lr.target_offset = sym->offset + displ;

    lr.frame_datum = fixup->frame_datum;

    /* symbol is always a code label (near or far), internal or external */
    /* now set Target and Frame */

    if( sym->state == SYM_EXTERNAL ) {
        DebugMsg(("omf_write_modend(%p): fixup->frame_type/datum=%u/%u, EXTERNAL sym=%s\n",
                  fixup, fixup->frame_type, fixup->frame_datum, sym->name));

        lr.target = TARGET_EXT & TARGET_WITH_DISPL;
        lr.target_datum = sym->ext_idx1;

        if( fixup->frame_type == FRAME_GRP && fixup->frame_datum == 0 ) {
            /* set the frame to the frame of the corresponding segment */
            lr.frame_datum = omf_GetGrpIdx( sym );
        }
    } else { /* SYM_INTERNAL */
        DebugMsg(("OmfFixGenFixModend(%p): fixup->frame_type/datum=%u/%u sym->name=%s state=%X segm=%s\n",
                  fixup, fixup->frame_type, fixup->frame_datum, sym->name, sym->state, sym->segment ? sym->segment->name : "NULL" ));
        /**/myassert( sym->state == SYM_INTERNAL );

        lr.target = TARGET_SEG & TARGET_WITH_DISPL;
        lr.target_datum = GetSegIdx( sym->segment );
    }

    if( fixup->frame_type != FRAME_NONE && fixup->frame_type != FRAME_SEG ) {
        lr.frame = (uint_8)fixup->frame_type;
    } else {
        lr.frame = FRAME_TARG;
    }
    return( TranslateLogref( &lr, buf, type ) );
}

/* fill a logref from a fixup's info */

static int omf_fill_logref( const struct fixup *fixup, struct logref *lr )
/************************************************************************/
{
    struct asym      *sym;

    sym = fixup->sym; /* may be NULL! */

    DebugMsg1(("omf_fill_logref: sym=%s, state=%d, fixup->type=%u\n",
               sym ? sym->name : "NULL", sym ? sym->state : -1, fixup->type ));

    /*------------------------------------*/
    /* Determine the Target and the Frame */
    /*------------------------------------*/

    if( sym == NULL ) {

        DebugMsg(("omf_fill_logref: sym is NULL, frame_type=%u\n", fixup->frame_type ));
        if ( fixup->frame_type == FRAME_NONE ) /* v1.96: nothing to do without a frame */
            return( 0 );
        lr->target = fixup->frame_type;
        lr->target_datum = fixup->frame_datum;
        lr->frame = FRAME_TARG;

    } else if( sym->state == SYM_UNDEFINED ) { /* shouldn't happen */

        DebugMsg(("omf_fill_logref: sym->state is SYM_UNDEFINED\n" ));
        EmitErr( SYMBOL_NOT_DEFINED, sym->name );
        return( 0 );

    } else if( sym->state == SYM_GRP ) {

        DebugMsg1(("omf_fill_logref: sym->state is SYM_GRP\n" ));
        lr->target = TARGET_GRP;
        lr->target_datum = ((struct dsym *)sym)->e.grpinfo->grp_idx;
        if( fixup->frame_type != FRAME_NONE ) {
            lr->frame = fixup->frame_type;
            lr->frame_datum = fixup->frame_datum;
        } else {
            lr->frame = FRAME_GRP;
            lr->frame_datum = lr->target_datum;
        }

    } else if( sym->state == SYM_SEG ) {

        DebugMsg1(("omf_fill_logref: sym->state is SYM_SEG %s\n" ));
        lr->target = TARGET_SEG;
        lr->target_datum = GetSegIdx( sym );
        if( fixup->frame_type != FRAME_NONE ) {
            lr->frame = fixup->frame_type;
            lr->frame_datum = fixup->frame_datum;
        } else {
            lr->frame = FRAME_SEG;
            lr->frame_datum = lr->target_datum;
        }

    } else {

        /* symbol is a label */

        lr->frame_datum = fixup->frame_datum;
        if( sym->state == SYM_EXTERNAL ) {
            DebugMsg1(("omf_fill_logref: sym->state is SYM_EXTERNAL, fixup->frame_type/datum=%u/%u\n",
                      fixup->frame_type, fixup->frame_datum ));
            lr->target = TARGET_EXT;
            lr->target_datum = sym->ext_idx1;

            if( fixup->frame_type == FRAME_GRP && fixup->frame_datum == 0 ) {
                /* set the frame to the frame of the corresponding segment */
                lr->frame_datum = omf_GetGrpIdx( sym );
            }
        } else {
            /* must be SYM_INTERNAL */
            /**/myassert( sym->state == SYM_INTERNAL );
            DebugMsg1(("omf_fill_logref: sym->state is SYM_INTERNAL, sym->segment=%s, fixup->frame/datum=%u/%u\n",
                       sym->segment ? sym->segment->name : "NULL", fixup->frame_type, fixup->frame_datum ));
            /* v2.08: don't use info from assembly-time variables */
            if ( sym->variable ) {
                lr->target = ( fixup->frame_type == FRAME_GRP ? TARGET_GRP : TARGET_SEG );
                lr->target_datum = fixup->frame_datum;
            } else if ( sym->segment == NULL ) { /* shouldn't happen */
                EmitErr( SEGMENT_MISSING_FOR_FIXUP, sym->name );
                return ( 0 );
#if COMDATSUPP
            } else if ( ( (struct dsym *)sym->segment)->e.seginfo->comdat_selection ) {
                lr->target = TARGET_EXT;
                lr->target_datum = ((struct dsym *)sym->segment)->e.seginfo->seg_idx;
                lr->frame = FRAME_TARG;
                return( 1 );
#endif
            } else {
                lr->target = TARGET_SEG;
                lr->target_datum = GetSegIdx( sym->segment );
            }
        }

        if( fixup->frame_type != FRAME_NONE ) {
            lr->frame = (uint_8)fixup->frame_type;
        } else {
            lr->frame = FRAME_TARG;
        }
    }

    /*--------------------*/
    /* Optimize the fixup */
    /*--------------------*/

    if( lr->frame == ( lr->target - TARGET_SEG ) ) {
        lr->frame = FRAME_TARG;
    }

    return( 1 );
}

/* translate a fixup into its binary representation,
 * which is a "FIXUPP subrecord" according to OMF docs.
 * structure:
 * - WORD, Locat: 1MLLLLDD DDDDDDDD, is
 *   1 = indicates FIXUP, no THREAD subrecord
 *   M = mode: 1=segment relative, 0=self relative
 *   L = location, see LOC_ entries in omfspec.h
 *   D = data record offset, 10 bits for range 0-3FFh
 * - BYTE, Fix Data: FRRRTPGG, is
 *   F = 0=frame defined in fixup, 1=frame defined in frame thread
 *   R = Frame
 *   T = 0=target defined in fixup, 1=Target defined in target thread
 *   P = 0=target displacement is present
 *   G = lower bits of target method (F=0), target thread number (F=1)
 * - void/BYTE/WORD, Frame Datum
 * - BYTE/WORD, Target Datum
 * - WORD/DWORD, Target Displacement
 */

unsigned OmfFixGenFix( const struct fixup *fixup, uint_32 start_loc, uint_8 *buf, enum fixgen_types type )
/********************************************************************************************************/
{
    uint_8  locat1;
    uint_8  self_relative = FALSE;
    unsigned data_rec_offset;
    struct logref lr;

    /**/myassert( fixup != NULL );
    /**/myassert( buf != NULL );
    /**/myassert( type == FIX_GEN_INTEL || type == FIX_GEN_MS386 );

    lr.is_secondary = TRUE;
    lr.target_offset = 0;

    switch( fixup->type ) {
    case FIX_RELOFF8:
        self_relative = TRUE;
        /* no break */
    case FIX_OFF8:
        locat1 = ( LOC_OFFSET_LO << 2 );
        break;
    case FIX_RELOFF16:
        self_relative = TRUE;
        /* no break */
    case FIX_OFF16:
        locat1 = ( fixup->loader_resolved ? LOC_MS_LINK_OFFSET << 2 : LOC_OFFSET << 2 );
        break;
    case FIX_RELOFF32:
        self_relative = TRUE;
        /* no break */
    case FIX_OFF32:
        locat1 = ( fixup->loader_resolved ? LOC_MS_LINK_OFFSET_32 << 2 : LOC_MS_OFFSET_32 << 2 );
        break;
    case FIX_HIBYTE:
        locat1 = ( LOC_OFFSET_HI << 2 );
        break;
    case FIX_SEG:
        locat1 = ( LOC_BASE << 2 );
        break;
    case FIX_PTR16:
        locat1 = ( LOC_BASE_OFFSET << 2 );
        break;
    case FIX_PTR32:
        locat1 = ( LOC_MS_BASE_OFFSET_32 << 2 );
        break;
    default: /* shouldn't happen. Check for valid fixup has already happened */
        EmitErr( UNSUPPORTED_FIXUP_TYPE,
               ModuleInfo.fmtopt->formatname,
               fixup->sym ? fixup->sym->name : szNull );
        return( 0 );
    }
    locat1 |= self_relative ? 0x80 : 0xc0; /* bit 7: 1=is a fixup subrecord */

    if ( omf_fill_logref( fixup, &lr ) == 0 )
        return( 0 );

    /* magnitude of fixup's position is 10! */
    /**/myassert( fixup->locofs - start_loc < 1024 );

    /* calculate the fixup's position in current LEDATA */
    data_rec_offset = fixup->locofs - start_loc;

    locat1 |= data_rec_offset >> 8;
    *buf = locat1;
    *(buf+1) = (uint_8)data_rec_offset;
    return( 2 + TranslateLogref( &lr, buf+2, type ) );
}

