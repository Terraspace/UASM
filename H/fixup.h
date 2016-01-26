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
* Description:  fixup related variables and routines
*
****************************************************************************/

#ifndef FIXUP_H
#define FIXUP_H

/* RELOFF8 - RELOFF32 must be consecutive */

enum fixup_types {
        FIX_VOID = 0,       /*  0, fixup is to be ignored */
        FIX_RELOFF8,        /*  1, 1 byte */
        FIX_RELOFF16,       /*  2, 2 byte */
        FIX_RELOFF32,       /*  3, 4 byte */
        FIX_OFF8,           /*  4, 1 byte, OMF, BIN + GNU-ELF only */
        FIX_OFF16,          /*  5, 2 byte */
        FIX_OFF32,          /*  6, 4 byte */
#if AMD64_SUPPORT
        FIX_OFF64,          /*  7, 8 byte, COFF64, ELF64 + BIN only */
#endif
        FIX_SEG = 8,        /*  8, 2 byte */
        FIX_PTR16,          /*  9, 4 byte, OMF+BIN-MZ only */
        FIX_PTR32,          /* 10, 6 byte, OMF+BIN-MZ only */
        FIX_HIBYTE,         /* 11, 1 byte, OMF+BIN-MZ only */
        FIX_OFF32_IMGREL,   /* 12, 4 byte, COFF+ELF only */
        FIX_OFF32_SECREL,   /* 13, 4 byte, COFF+ELF only */
        FIX_LAST
};

/*  OMF: nothing (7, 12, 13 can't happen)
 * COFF: set bit 1, 4, 9, 10, 11
 *  ELF: set bit 8, 9, 10, 11
 */
#if BIN_SUPPORT
#define BIN_DISALLOWED 0x0000
#endif
#define OMF_DISALLOWED 0x0000
#if COFF_SUPPORT
/* exclude RELOFF8, OFF8, PTR16, PTR32, HIBYTE */
#define COFF32_DISALLOWED 0x0E12
/* exclude RELOFF8, OFF8, PTR16, PTR32, HIBYTE */
#define COFF64_DISALLOWED 0x0E12
#endif
#if ELF_SUPPORT
/* exclude SEG, PTR16, PTR32, HIBYTE */
#define ELF32_DISALLOWED  0x0F00
/* exclude SEG, PTR16, PTR32, HIBYTE */
#define ELF64_DISALLOWED  0x0F00
#endif

/* fixups are also used for backpatching of forward references in pass one.
 * the instructions which depend on the distance are CALL, JMP, PUSH <imm>.
 * OPTJ_EXPLICIT: JMP SHORT <label> or Jcc SHORT <label>, size cannot change
 * OPTJ_EXTEND:   Jcc <label> for cpu < 80386, size may change (2 -> 5/7 or 8/10)
 * OPTJ_JXX:      Jcc <label> for cpu >= 80386, size may change (2 -> 5 )
 * OPTJ_CALL:     call <label>, may become push cs, call NEAR or call FAR
 * OPTJ_PUSH:     push <label>, assumed byte, may become variable or label.
 */

enum fixup_options {
        OPTJ_NONE,      /* normal jump */
        OPTJ_EXPLICIT,
        OPTJ_EXTEND,
        OPTJ_JXX,
        OPTJ_CALL,
        OPTJ_PUSH      /* PUSH */
};

struct fixup {
    struct fixup         *nextbp;       /* PASS 1: linked list backpatch */
    struct fixup         *nextrlc;      /* PASS >1: linked list relocs */
#ifdef TRMEM
    uint_16              marker;
#endif
    uint_32              offset;        /* symbol's offset */
    uint_32              locofs;        /* location of fixup */
    enum fixup_types     type;
    enum fixup_options   option;
    union {
        uint_16 flags;
        struct {
#if AMD64_SUPPORT
            /* the IP relative addressing needs to know where the instruction ends.
             * the result <end of instruction> - <fixup location> is stored here.
             */
            uint_8        addbytes;
#endif
            unsigned char loader_resolved:1;        /* operator LROFFSET */
            unsigned char orgoccured:1;             /* v2.04 ORG occured behind this fix */
        };
    };
    union {
        struct {
            int_8           frame_type;     /* frame specifier (SEG=0,GRP=1,,...) */
            uint_16         frame_datum;    /* additional data, usually index */
        };
        struct asym         *segment_var;   /* symbol's segment if assembly time var */
    };
    struct dsym             *def_seg;       /* segment the fixup is in - pass 1 only */
    struct asym             *sym;
};

extern struct fixup  *CreateFixup( struct asym *sym, enum fixup_types fixup_type, enum fixup_options fixup_option );
extern void          SetFixupFrame( const struct asym *sym, char );
extern void          FreeFixup( struct fixup * );
extern void          store_fixup( struct fixup *, struct dsym *, int_32 * );

extern ret_code      BackPatch( struct asym *sym );

#endif
