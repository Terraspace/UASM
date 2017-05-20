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
* Description:  OMF basics
*
****************************************************************************/

#ifndef OMFSPEC_H
#define OMFSPEC_H 1

#if 0
/*
 *  INTEL Segment Alignment Specifiers - A field
 */
enum segment_alignment_specifiers {
    ALIGN_ABS           = 0,        /* absolute segment - no alignment  */
    ALIGN_BYTE          = 1,        /* relocatable seg - byte aligned   */
    ALIGN_WORD          = 2,        /* relocatable seg - word aligned   */
    ALIGN_PARA          = 3,        /* relocatable seg - para aligned   */
    ALIGN_PAGE          = 4,        /* relocatable seg - page aligned   */
    ALIGN_DWORD         = 5,        /* relocatable seg - dword aligned  */
    ALIGN_LTRELOC       = 6,        /* load-time relocatable segment    */
#if PAGE4K /* PharLab Easy OMF */
    ALIGN_4KPAGE        = 6,        /* relocatable seg - 4k page aligned*/
    ALIGN_PAGE4K        = 6,        /* relocatable seg - 4k page aligned*/
#endif
   /* this currently not supported by the linker. */
    //ALIGN_UNABS         = 5,        /* unnamed absolute segment         */
};
#endif

enum segdef_align_values {
    SEGDEF_ALIGN_ABS        = 0,/* absolute segment - no alignment          */
    SEGDEF_ALIGN_BYTE       = 1,/* relocatable seg  - byte aligned          */
    SEGDEF_ALIGN_WORD       = 2,/*                  - word aligned          */
    SEGDEF_ALIGN_PARA       = 3,/*                  - para aligned          */
    SEGDEF_ALIGN_PAGE       = 4,/*                  - page aligned          */
    SEGDEF_ALIGN_DWORD      = 5,/*                  - dword aligned         */
#if PAGE4K
    SEGDEF_ALIGN_4KPAGE     = 6 /*                  - 4k page aligned       */
#endif
};

/*
 *  INTEL Segment Combination Attributes - C field
 *  Uasm uses COMB_INVALID, COMB_ADDOFF, COMB_STACK & COMB_COMMON
 */

enum combine_attributes {
    COMB_INVALID        = 0,  /* PRIVATE attribute */
    COMB_ABOVEALL       = 1,  /* marked as "reserved" */
    COMB_ADDOFF         = 2,  /* PUBLIC attribute */
    COMB_BAD            = 3,  /* marked as "reserved" */
    COMB_FOUR           = 4,  /* comment: same as 2 */
    COMB_STACK          = 5,  /* STACK attribute */
    COMB_COMMON         = 6,  /* COMMON attribute */
    COMB_ALIGNTOP       = 7,  /* comment: same as 2 */
};

#if 0
#define SEGATTR_A( a )  (ALIGN_##a << 5)
#define SEGATTR_C( a )  (COMB_##a << 2)
enum {
    SEGATTR_BIG  =   1<< 1,   /* exactly 64k or 2**32 */
    SEGATTR_P    =   1,       /* use 32 */
};
#endif

/*
 *  INTEL Frame Specifiers
 *  FRAME_ABS[WD] not supported according to TIS OMF docs.
 *  FRAME_NONE should never appear in object modules, it's just
 *  a void used by jwasm internally.
 */
enum frame_methods {
    FRAME_SEG           = 0,        /* segment index                    */
    FRAME_GRP           = 1,        /* group index                      */
    FRAME_EXT           = 2,        /* external index                   */
    //FRAME_ABS           = 3,        /* absolute frame number            */
    FRAME_LOC           = 4,        /* segment index of last LEDATA     */
    FRAME_TARG          = 5,        /* frame same as target             */
    FRAME_NONE          = 6,        /* no frame                         */
};

/*
 *  INTEL Target Specifiers
 *  TARGET_ABS[WD] is supported for THREAD sub-records only, according to TIS OMF docs;
 *  Since Uasm won't write THREAD sub-records, those methods are invalid.
 */
enum target_methods {
    TARGET_SEGWD        = 0,        /* segment index with displacement  */
    TARGET_GRPWD        = 1,        /* group index with displacement    */
    TARGET_EXTWD        = 2,        /* external index with displacement */
    //TARGET_ABSWD        = 3,        /* abs frame num with displacement  */

    TARGET_SEG          = 4,        /* segment index, no displacement   */
    TARGET_GRP          = 5,        /* group index, no displacement     */
    TARGET_EXT          = 6,        /* external index, no displacement  */
    //TARGET_ABS          = 7,        /* abs frame num, no displacement   */

    TARGET_WITH_DISPL   = ~4,       /* frame with displacement          */
};

/*  Bits in FIXUPP records */

enum {
    FIXUPP_FIXUP        = 0x80,

    FIXDAT_FTHREAD      = 0x80,
    FIXDAT_TTHREAD      = 8,
    FIXDAT_PBIT         = 4,
    FIXDAT_MBIT         = 0x40,
    TRDDAT_DBIT         = 0x40,

/*
 *  INTEL Group Specifiers
 */

    GRP_SEGIDX          = 0xff,     /* group segment index              */
    GRP_EXTIDX          = 0xfe,     /* group external index             */
    GRP_FULLNAME        = 0xfd,     /* full name indices                */
    GRP_LTLDATA         = 0xfb,     /* load time data info              */
    GRP_ADDR            = 0xfa,     /* load time addr for the group     */
};

/*
 *  INTEL Object Record Types
 */

enum cmd_omf {
#if 0 /* these cmds aren't used (and ignored by MS link) */
    CMD_MIN_CMD         = 0x6e,     /* minimum cmd enum                  */
    CMD_RHEADR          = 0x6e,     /* R-Module Header                   */
    CMD_REGINT          = 0x70,     /* Register Initialization           */
    CMD_REDATA          = 0x72,     /* Relocatable Enumerated Data       */
    CMD_RIDATA          = 0x74,     /* Relocatable Iterated Data         */
    CMD_OVLDEF          = 0x76,     /* Overlay Definition                */
    CMD_ENDREC          = 0x78,     /* End                               */
    CMD_BLKDEF          = 0x7a,     /* block definition                  */
    //CMD_BLKD32          = 0x7b,     /* weird extension for QNX MAX assembler */
    CMD_BLKEND          = 0x7c,     /* block end                         */
    //CMD_BLKE32          = 0x7d,     /* _might_ be used by QNX MAX assembler */
    CMD_DEBSYM          = 0x7e,     /* Debug Symbols                     */
#else
    CMD_MIN_CMD         = 0x80,     /* minimum cmd enum                 */
#endif
    CMD_THEADR          = 0x80,     /* translator header                */
    CMD_LHEADR          = 0x82,     /* library header                   */
//  CMD_PEDATA          = 0x84,     /* physical enumerated data         */
//  CMD_PIDATA          = 0x86,     /* physical iterated data           */
    CMD_COMENT          = 0x88,     /* comment record                   */
    CMD_MODEND          = 0x8a,     /* end of module record             */
    CMD_EXTDEF          = 0x8c,     /* import names record              */
    CMD_TYPDEF          = 0x8e,     /* type definition record           */
    CMD_PUBDEF          = 0x90,     /* public names record              */
//  CMD_LOCSYM          = 0x92,     /* local symbols                    */
    CMD_LINNUM          = 0x94,     /* line number record               */
    CMD_LNAMES          = 0x96,     /* list of names record             */
    CMD_SEGDEF          = 0x98,     /* segment definition record        */
    CMD_GRPDEF          = 0x9a,     /* group definition record          */
    CMD_FIXUPP          = 0x9c,     /* relocation record                */
    CMD_LEDATA          = 0xa0,     /* logical enumerated data          */
    CMD_LIDATA          = 0xa2,     /* logical iterated data            */
//  CMD_LIBHED          = 0xa4,     /* library header                   */
//  CMD_LIBNAM          = 0xa6,     /* library module names             */
//  CMD_LIBLOC          = 0xa8,     /* library module locations         */
//  CMD_LIBDIC          = 0xaa,     /* library dictionary               */
    CMD_COMDEF          = 0xb0,     /* communal definition              */
    CMD_BAKPAT          = 0xb2,     /* backpatch record (for Quick C)   */

    /* the following types are used to make local names known to the linker */
    CMD_LEXTDEF         = 0xb4,     /* local import names record        */
    CMD_STATIC_EXTDEF   = 0xb4,
    CMD_LPUBDEF         = 0xb6,     /* local public names def record    */
    CMD_LCOMDEF         = 0xb8,     /* local communal names def record  */
    CMD_STATIC_COMDEF   = 0xb8,

    CMD_CEXTDEF         = 0xbc,     /* external reference to a COMDAT   */
    CMD_COMDAT          = 0xc2,     /* initialized communal data record */
    CMD_LINSYM          = 0xc4,     /* symbol line numbers              */
    CMD_ALIAS           = 0xc6,     /* alias definition record          */
    CMD_NBKPAT          = 0xc8,     /* named backpatch record (quick c?) */
    CMD_LLNAMES         = 0xca,     /* a "local" lnames                 */
    CMD_MAX_CMD         = 0xca,     /* maximum cmd enum                 */
#if 0
    CMD_VERNUM          = 0xcc,     /* TIS version number record        */
    CMD_VENDEXT         = 0xce,     /* TIS vendor extension record      */
    CMD_MAX_CMD         = 0xce,     /* maximum cmd enum                 */
#endif
#if 0 /* 32-bit versions */
    CMD_MODE32          = CMD_MODEND+1,
    CMD_PUBD32          = CMD_PUBDEF+1,
    CMD_LINN32          = CMD_LINNUM+1,
    CMD_SEGD32          = CMD_SEGDEF+1,
    CMD_FIXU32          = CMD_FIXUP+1,
    CMD_LEDA32          = CMD_LEDATA+1,
    CMD_LIDA32          = CMD_LIDATA+1,
    CMD_BAKP32          = CMD_BAKPAT+1,
    CMD_LEXTDEF32       = CMD_LEXTDEF+1,
    CMD_STATIC_EXTD32   = CMD_STATIC_EXTDEF+1,
    CMD_LPUBDEF32       = CMD_LPUBDEF+1,
    CMD_COMD32          = CMD_COMDAT+1,
    CMD_LINS32          = CMD_LINSYM+1,
    CMD_NBKP32          = CMD_NBKPAT+1,
#endif
};

/* OMF fixup types; 4-bit-"location"-field in FIXUP sub-records; see omffixup.c.
 */
enum omf_fixup_types {
    LOC_OFFSET_LO       = 0,    /* 8-bit (lowbyte) offset             */
    LOC_OFFSET          = 1,    /* 16-bit offset                      */
    LOC_BASE            = 2,    /* segment (always 16-bit)            */
    LOC_BASE_OFFSET     = 3,    /* 16-bit offset & 16-bit segment     */
    LOC_OFFSET_HI       = 4,    /* 8-bit (hibyte) offset              */
#if 0
    LOC_PL_OFFSET_32      = 5,  /* 32-bit offset (PharLab)                  */
    LOC_PL_BASE_OFFSET_32 = 6,  /* 32-bit offset & 16-bit segment (PharLab) */
#endif
    LOC_MS_LINK_OFFSET   =  5,  /* 16-bit "loader-resolved" offset (MS) */
    LOC_MS_OFFSET_32     =  9,  /* 32-bit offset (MS)                   */
    LOC_MS_BASE_OFFSET_32= 11,  /* 32-bit offset & 16-bit segment (MS)  */
    LOC_MS_LINK_OFFSET_32= 13   /* 32-bit "loader-resolved" offset (MS) */
};

/* Comment Type */

enum {
    CMT_TNP = 0x80,   /* no purge bit */
    CMT_TNL = 0x40,   /* no list bit */
};
/*
 * Comment classes. Uasm uses:
 * - CMT_DOSSEG           : dosseg directive
 * - CMT_DEFAULT_LIBRARY  : includelib directive
 * - CMT_OMF_EXT          : PROC's EXPORT attribute
 * - CMT_MS_OMF           : codeview debug info version
 * - CMT_MS_END_PASS_1    : end of pass one
 * - CMT_WKEXT            : extern directive with altname
 * - CMT_DEPENDENCY       : include directive, Borland specific
 * - CMT_DISASM_DIRECTIVE : wdis special
 * - CMT_LINKER_DIRECTIVE : wlink specials
 */
enum omf_comment_classes {
    //CMT_LANGUAGE_TRANS  = 0x00, /* Language translator comment          */
    //CMT_INTEL_COPYRIGHT = 0x01, /* INTEL Copyright record               */
    //CMT_MS_PADDING      = 0x01, /* Microsoft uses this for padding      */
    //CMT_WAT_PROC_MODEL  = 0x9b, /* Watcom processor & model info        */
    //CMT_MS_DOS_VERSION  = 0x9c, /* obsolete                             */
    //CMT_MS_PROC_MODEL   = 0x9d, /* Microsoft processor & model info     */
    CMT_DOSSEG          = 0x9e, /* DOSSEG directive                     */
    CMT_DEFAULT_LIBRARY = 0x9f, /* Default library cmd                  */
    CMT_OMF_EXT         = 0xa0, /* OMF extension                        */
    CMT_MS_OMF          = 0xa1, /* MS codeview debug info included      */
    CMT_MS_END_PASS_1   = 0xa2, /* MS end of linker pass 1              */
    //CMT_LIBMOD          = 0xa3, /* Record specifying name of object     */
    //CMT_EXESTR          = 0xa4, /* Executable string                    */
    //CMT_INCERR          = 0xa6, /* Incremental Compilation Error        */
    //CMT_NOPAD           = 0xa7, /* No segment padding                   */
    CMT_WKEXT           = 0xa8, /* Weak external record                 */
    //CMT_LZEXT           = 0xa9, /* Lazy external record                 */
    //CMT_EASY_OMF        = 0xaa, /* Easy OMF signature record            */
    CMT_SRCFILE         = 0xe8, /* Borland source file record           */
    CMT_DEPENDENCY      = 0xe9, /* Borland dependency record            */
    CMT_DISASM_DIRECTIVE= 0xfd, /* Directive to disassemblers           */
    CMT_LINKER_DIRECTIVE= 0xfe, /* Linker directive                     */
    //CMT_COMPILER_OPTIONS= 0xff, /* Microsoft: incremental compiler opts */
    //CMT_SOURCE_NAME     = 0xff  /* name of the source file              */
};

/*
 * Comment Class Subtype for CMT_OMF_EXT
 */
enum omf_ext_subtype {
    CMT_EXT_IMPDEF  = 0x01, /* Subtype IMPDEF of OMF extension class    */
    CMT_EXT_EXPDEF  = 0x02, /* Subtype EXPDEF of OMF extension class    */
    CMT_EXT_INCDEF  = 0x03, /* Subtype INCDEF of OMF extension class    */
    CMT_EXT_PMLIB   = 0x04, /* Protected Memory Library (OMF extension) */
    CMT_EXT_LNKDIR  = 0x05, /* Subtype LNKDIR of OMF extension class    */
    CMT_EXT_BIGEND  = 0x06,
    CMT_EXT_PRECOMP = 0x07,
};

//#define EASY_OMF_SIGNATURE  "80386"

/*
 *  Linker directives ( CMT_LINKER_DIRECTIVE - mostly WLINK directives )
 *  Uasm uses LDIR_OPT_FAR_CALLS only
 */
enum linker_directives {
    LDIR_SOURCE_LANGUAGE= 'D',  /* dbg maj/min and source language      */
    LDIR_DEFAULT_LIBRARY= 'L',  /* default library cmd                  */
    LDIR_OPT_FAR_CALLS  = 'O',  /* optimize far calls/jmps for this seg */
    //LDIR_OPT_UNSAFE     = 'U',  /* far call optimization unsafe for fixup*/
    //LDIR_VF_TABLE_DEF   = 'V',  /* virtual function table lazy extdef   */
    //LDIR_VF_PURE_DEF    = 'P',  /* as above for pure functions */
    //LDIR_VF_REFERENCE   = 'R',  /* virtual function reference */
    //LDIR_PACKDATA       = '7',  /* amount to pack far data */
    //LDIR_FLAT_ADDRS     = 'F',  /* debug addresses are flat */
    //LDIR_OBJ_TIMESTAMP  = 'T'   /* file timestamp of object in a library */
};

/*
 *  Disasm directives ( CMT_DISASM_DIRECTIVE )
 *  this is a feature supported by OW WDis.
 */
enum disasm_directives {
/*
 *  DDIR_SCAN_TABLE is used by the code generator to indicate data in a
 *  code segment.  i.e., scan tables generated for switch()s, floating point
 *  constants and string constants.  The 'S' is followed by a segment index,
 *  then the start and end+1 offsets into the segment which are 16-bit in
 *  regular object files, and 32-bit in EasyOMF and Microsoft 386.
 *  If the segment index is zero, then it is followed by a LNAME index which
 *  identifies the COMDAT symbol that the scan table belongs to.
 */
    DDIR_SCAN_TABLE_32  = 'S',
    DDIR_SCAN_TABLE     = 's'
};

/*
 *  COMDEF types
 */
enum comdef_types {
    COMDEF_FAR          = 0x61, /* FAR variable                         */
    COMDEF_NEAR         = 0x62, /* NEAR variable                        */
    COMDEF_LEAF_SIZE    = 0x80, /* bit set if size > 0x7f               */
    COMDEF_LEAF_2       = 0x81, /* 2 byte size field                    */
    COMDEF_LEAF_3       = 0x84, /* 3 byte size field                    */
    COMDEF_LEAF_4       = 0x88  /* 4 byte size field                    */
};

/* COMDAT (initialized communal data);
 * record type 0xC2/0xC3;
 * MS extension introduced for MSC 7.
 */
enum comdat_flags {
/*
 *  COMDAT flags 
 */
    COMDAT_CONTINUE     = 0x01, /* continuation of previous COMDAT */
    COMDAT_ITERATED     = 0x02, /* LIDATA form of COMDAT */
    COMDAT_LOCAL        = 0x04, /* COMDAT is local to this module */
    COMDAT_DATAINCODE   = 0x08, /* data in code segment */
/*
 *  COMDAT allocation type ( low-order 4 bits of attributes field )
 */
    COMDAT_ALLOC_MASK   = 0x0f,
    COMDAT_EXPLICIT     = 0x00, /* in given segment ( base grp, seg and frame ) */
    COMDAT_FAR_CODE     = 0x01, /* allocate CODE use16 segment */
    COMDAT_FAR_DATA     = 0x02, /* allocate DATA use16 segment */
    COMDAT_CODE32       = 0x03, /* allocate CODE use32 segment */
    COMDAT_DATA32       = 0x04, /* allocate DATA use32 segment */
/*
 *  COMDAT selection criteria ( high-order 4 bits of attributes field )
 */
    COMDAT_MATCH_MASK   = 0xf0,
    COMDAT_MATCH_NONE   = 0x00, /* don't match anyone - only 1 instance allowed */
    COMDAT_MATCH_ANY    = 0x10, /* pick any instance */
    COMDAT_MATCH_SAME   = 0x20, /* must be same size - or linker will emit an error */
    COMDAT_MATCH_EXACT  = 0x30, /* pick any instance - but checksums must match */
/*
 *  COMDAT alignment
 */
    COMDAT_ALIGN_SEG    = 0x00, /* align from SEGDEF */
    COMDAT_ALIGN_BYTE   = 0x01,
    COMDAT_ALIGN_WORD   = 0x02,
    COMDAT_ALIGN_PARA   = 0x03,
    COMDAT_ALIGN_4K     = 0x04,
    COMDAT_ALIGN_DWORD  = 0x05
};

#endif
