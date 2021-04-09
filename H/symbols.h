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
* Description:  defines symbol structures asym and dsym,
*               and prototypes of functions in symbols.c.
*               This file is included by parser.h.
*
****************************************************************************/


#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

/*
 * SYM_LIB  - library paths are no longer added to the symbol table
 * SYM_LNAME has been removed. It was used for the null-entry in the LNAME table only
 * v2.01: SYM_PROC has been removed.
 * v2.01: SYM_LIB has been removed.
 */
enum sym_state {
    SYM_UNDEFINED,
    SYM_INTERNAL,       /*  1 internal label */
    SYM_EXTERNAL,       /*  2 external       */
    SYM_SEG,            /*  3 segment        */
    SYM_GRP,            /*  4 group          */
    SYM_STACK,          /*  5 stack variable - in local symbol tables only */
    SYM_STRUCT_FIELD,   /*  6 struct member - not in symbol table - except record fields */
    SYM_TYPE,           /*  7 structure, union, typedef, record */
    SYM_ALIAS,          /*  8 alias name     */
    SYM_MACRO,          /*  9 macro          */
    SYM_TMACRO,         /* 10 text macro     */
    SYM_CLASS_LNAME     /* 11 lname item for segm class - not in symbol table */
};

/* v2.04: MT_SHORT removed */
/* v2.07: MT_ABS (0xC2) removed */

enum memtype {
  /* 0x1F changed to 0x3F to cover ZMM registers, Uasm 2.16 */
    MT_SIZE_MASK = 0x1F, /* if MT_SPECIAL==0 then bits 0-4 = size - 1 */
    MT_FLOAT  = 0x20, /* bit 5=1 */
    MT_SIGNED = 0x40, /* bit 6=1 */
    MT_BYTE  = 1 - 1,
    MT_SBYTE = MT_BYTE | MT_SIGNED,
    MT_WORD  = 2 - 1,
    MT_SWORD = MT_WORD | MT_SIGNED, 
    MT_REAL2 = MT_WORD | MT_FLOAT,
    MT_DWORD = 4 - 1,                 
    MT_SDWORD= MT_DWORD | MT_SIGNED,  
    MT_REAL4 = MT_DWORD | MT_FLOAT,   
    MT_FWORD = 6 - 1,                 
    MT_QWORD = 8 - 1,                 
    MT_SQWORD= MT_QWORD | MT_SIGNED,
    MT_REAL8 = MT_QWORD | MT_FLOAT,
    MT_TBYTE = 10 - 1,
    MT_REAL10= MT_TBYTE | MT_FLOAT,
    MT_OWORD = 16 - 1,
    MT_REAL16 = MT_OWORD | MT_FLOAT,
    MT_YMMWORD  = 32 - 1,
    MT_ZMMWORD  = 64 - 1,
    MT_YWORD = 32 - 1,
    MT_ZWORD = 64 - 1,
    MT_PROC  = 0x80,   /* symbol is a TYPEDEF PROTO, state=SYM_TYPE, typekind=TYPE_TYPEDEF, prototype is stored in target_type */
    MT_NEAR  = 0x81,
    MT_FAR   = 0x82,
    MT_EMPTY = 0xC0,
    MT_BITS  = 0xC1,   /* record field */
    MT_ABS   = 0xC2,   
    MT_PTR   = 0xC3,   /* v2.05: changed, old value 0x83 */
    MT_TYPE  = 0xC4,   /* symbol has user-defined type (struct, union, record) */
    MT_SPECIAL = 0x80, /* bit 7 */
    MT_SPECIAL_MASK = 0xC0, /* bit 6+7 */
    MT_ADDRESS = 0x80, /* bit 7=1, bit 6 = 0 */
};

#define IS_SIGNED(x)  (((x) & MT_SPECIAL_MASK) == MT_SIGNED)

/* UASM 2.34 added return type from proc enum */
enum returntype {
	RT_SIGNED = 0x40,
	RT_FLOAT = 0x20,
	RT_BYTE = 0,
	RT_SBYTE = RT_BYTE | RT_SIGNED,
	RT_WORD = 1,
	RT_SWORD = RT_WORD | RT_SIGNED,
	RT_DWORD = 2,
	RT_SDWORD = RT_DWORD | RT_SIGNED,
	RT_QWORD = 3,
	RT_SQWORD = RT_QWORD | RT_SIGNED,
	RT_REAL4 = RT_DWORD | RT_FLOAT,
	RT_REAL8 = RT_QWORD | RT_FLOAT,
	RT_REAL10 = RT_FLOAT,
	RT_XMM = 6,
	RT_YMM = 7,
	RT_ZMM = 8,
	RT_PTR = 0xc3,
	RT_NONE = 0x100
};

/* symbols can be
 * - "labels" (data or code, internal, external, stack)
 *   mem_type is MT_BYTE..MT_OWORD, MT_NEAR, MT_FAR, MT_PTR
 * - constants (EQU) or assembly time variables ("="),
 *   mem_type "usually" is MT_EMPTY.
 * - types (STRUCT, UNION, TYPEDEF, RECORD), mem_type = MT_TYPE
 * - preprocessor items (macros and text macros), which have no
 *   mem_type (MT_EMPTY).
 */
struct macro_instance;

typedef void (* internal_func)( struct asym *, void * );

struct debug_info {
    uint_32 start_line;  /* procs's start line */
    uint_32 end_line;    /* procs's last line */
    uint_32 ln_fileofs;  /* file offset to line numbers */
    uint_16 line_numbers;/* line numbers in function */
    uint_16 file;        /* proc's start file */
    unsigned next_proc;  /* index next proc */
    unsigned next_file;  /* index next file */
};

struct asym {
    struct asym     *nextitem;       /* next symbol in hash line */
    char            *name;           /* symbol name */
	char           *string_ptr;  /* used by SYM_TMACRO */
	union {
        int_32         offset;       /* used by SYM_INTERNAL (labels), SYM_TYPE, SYM_STACK, v2.11: SYM_SEG */
        int_32         value;        /* used by SYM_INTERNAL (equates) */
        uint_32        uvalue;       /* v2.01: equates (they are 33-bit!) */
        struct asym    *substitute;  /* v2.04b: used by SYM_ALIAS */
                                     /* func_ptr: used by SYM_MACRO if predefined==1 */
        ret_code (* func_ptr)( struct macro_instance *, char *, struct asm_tok * );
        int_32         class_lname_idx; /* used by SYM_CLASS_LNAME */
    };
	unsigned int    tokval;			/* Used to track a PROC parameter symbol that has an assigned register */
	struct asym     *segment;       /* used by SYM_INTERNAL, SYM_EXTERNAL */
    enum sym_state  state;
    enum memtype    mem_type;
    unsigned char   used:1,       /* symbol has been referenced */
                    isdefined:1,  /* symbol is "defined" in this pass */
                    scoped:1,     /* symbol is local label or SYM_STACK */
#if DLLIMPORT
                    iat_used:1,   /* v2.07: IAT entry of symbol used (SYM_EXTERNAL + isproc==1 only) */
#endif
                    isequate:1,   /* symbol has been defined with EQU */
                    predefined:1, /* symbol is predefined */
                    variable:1,   /* symbol is variable (defined by '=' directive) */
                    ispublic:1;   /* symbol has been added to the publics queue */
    unsigned char   list:1,       /* symbol is to be listed */
                    isarray:1,    /* symbol is an array (total_length is valid) */
                    isdata:1,     /* field first_size is valid */
                    isproc:1,     /* symbol is PROC or PROTO; has proc_info extension */
#if FASTPASS
                    issaved:1,    /* assembly-time variables only: symbol has been saved */
#endif
                    fwdref:1,     /* symbol was forward referenced */
                    included:1,   /* COFF: static symbol added to public queue. ELF:symbol added to symbol table (SYM_INTERNAL) */
                    isparam:1;    /* symbol is local parametar above rsp */
    union {
        /* for SYM_INTERNAL (data labels, memtype != NEAR|FAR), SYM_STRUCT_FIELD */
        uint_32         first_size;   /* size of 1st initializer's dimension in bytes */
        /* for SYM_INTERNAL (memtype == NEAR|FAR),
         * SYM_GRP (Ofssize),
         * SYM_EXTERNAL (Ofssize, comm, weak, isfar, is_ptr, ptr_memtype),
         * SYM_STACK (Ofssize, isfar, is_vararg, is_ptr, ptr_memtype ),
         * SYM_TYPE, TYPE_TYPEDEF (Ofssize, isfar, is_ptr, ptr_memtype )
         */
        struct {
            unsigned char   Ofssize;   /* offset size (USE16, USE32) */
            unsigned char   is_ptr;    /* PTR indirection */
            union {
                unsigned char ptr_memtype;/* pointer target type */
                unsigned char asmpass;    /* SYM_INTERNAL (mem_type NEAR|FAR) */
            };
            unsigned char   seg_ofssize:2;    /* SYM_EXTERNAL only */
            unsigned char   iscomm:1;  /* is communal */
            unsigned char   weak:1;    /* 1 if an unused "externdef" */
            unsigned char   isfar:1;   /* SYM_EXTERNAL, SYM_TYPE, SYM_STACK */
            unsigned char   is_vararg:1;/* SYM_STACK, VARARG param */
        };
        /* for SYM_MACRO */
        struct {
            unsigned char   mac_vararg:1,/* accept additional params */
                            isfunc:1,   /* it's a macro function */
#if MACROLABEL
                            label:1,    /* macro is "label-aware" */
#endif
#if VARARGML
                            mac_multiline:1, /* v2.11: vararg arguments may be on multiple lines */
#endif
                            purged:1;   /* macro has been PURGEd */
        };
    };
    union {
        /* for SYM_INTERNAL (data labels only), SYM_STRUCT_FIELD */
        uint_32         first_length; /* size of 1st initializer's dimension in item units */
        /* SYM_TYPE (TYPEKIND_STRUCT or TYPEKIND_UNION) */
        uint_32         max_mbr_size; /* max size members */
        /* SYM_STACK, SYM_TYPE (TYPEKIND_TYPEDEF), SYM_EXTERNAL, SYM_INTERNAL (code labels) */
        struct asym     *target_type; /* set if ptr_memtype is MT_TYPE */
        /* SYM_TMACRO (if it's a register variable for FASTCALL) */
        uint_16         regist[2];
    };
    union {
        /* for SYM_INTERNAL, SYM_STRUCT_FIELD,
         * SYM_TYPE, SYM_STACK,
         * SYM_EXTERNAL (comm=1)
         * SYM_TMACRO: size of buffer allocated for the text in string_ptr
         */
        uint_32         total_size;   /* total number of bytes (sizeof) */
        /* for SYM_INTERNAL, isequate=1 (numeric equates) */
        int_32          value3264;    /* high bits for equates */
#if DLLIMPORT
        struct dll_desc *dll;         /* SYM_EXTERNAL (isproc=1) */
#endif
        /* for SYM_SEG; v2.11: moved here to make segment's offset field contain "local start offset" (=0) */
        int_32          max_offset;
    };
    union {
        /* SYM_INTERNAL, SYM_STRUCT_FIELD,
         * SYM_STACK, SYM_EXTERNAL (comm==1):
         * total number of elements (LENGTHOF)
         */
        uint_32        total_length;
        struct asym    *altname;     /* SYM_EXTERNAL (comm==0): alternative name */
        struct debug_info *debuginfo;/* SYM_INTERNAL (isproc==1): debug info (COFF) */
        internal_func  sfunc_ptr;    /* SYM_INTERNAL+predefined */
        struct { /* SYM_TYPE */
            /* codeview type index (used after assembly steps)
             * v2.04: moved from first_length, were it didn't work anymore
             * since the addition of field max_mbr_size.
             */
            uint_16        cvtyperef;
            uint_16         typekind;
        };
    };
#if (MAX_ID_LEN <= 255)
    uint_8          name_size;
#else
    uint_16         name_size;
#endif
    uint_16  langtype; //enum lang_type
	union {
        /* SYM_INTERNAL, SYM_UNDEFINED, SYM_EXTERNAL: backpatching fixup */
        struct fixup *bp_fixup;
        /* for SYM_EXTERNAL */
        unsigned     ext_idx;     /* table index ( for coff and elf ) */
        struct {
            /* omf indices are 16-bit only! */
            uint_16  ext_idx1;    /* omf: (external definition) index */
            uint_16  ext_idx2;    /* omf: (external definition) index for weak external */
        };
    };
	union {
		struct asym *type;        /* set if memtype is MT_TYPE */
		struct dsym *ttype;       /* for easier debugging */
	};
	bool isClass;
	bool isCOM;
	bool isPtrTable;
	struct asym* procptr;
};

/*---------------------------------------------------------------------------*/
/* Structures for grpdef, segdef, externdef, pubdef, included library,       */
/* procedure and symbolic integer constants.                                 */
/*---------------------------------------------------------------------------*/

struct seg_item {
    struct seg_item     *next;
    struct dsym         *seg;
};

struct grp_info {
    struct seg_item     *seglist;       /* list of segments in the group */
    int                 grp_idx;        /* its group index (OMF) */
    int                 lname_idx;      /* LNAME index (OMF only) */
    unsigned            numseg;         /* OMF: number of segments in the group */
};

typedef uint_8 * (* FlushSegFunc)( struct dsym *, uint_8 *, unsigned, void * );

struct seg_info {
    struct asym         *group;         /* segment's group or NULL */
    uint_32             start_loc;      /* starting offset of current ledata or lidata */
    union {
        uint_32         current_loc;    /* current offset in current ledata or lidata */
        uint_32         reloc_offset;   /* ELF: reloc file offset */
        uint_32         start_offset;   /* BIN: start offset in group */
    };
#ifdef __I86__
    uint_8 huge         *CodeBuffer;
#else
    uint_8              *CodeBuffer;
#endif
    uint_32             bytes_written;  /* initialized bytes in segment */
    union {
        struct asym     *label_list;    /* linked list of labels in this seg */
        FlushSegFunc    flushfunc;      /* to flush the segment buffer */
    };
    struct {
        struct fixup    *head;          /* fixup queue head */
        struct fixup    *tail;          /* fixup queue tail */
    } FixupList;
    union {
        void            *LinnumQueue;   /* for COFF line numbers */
        uint_32         fileoffset;     /* used by BIN + ELF */
        uint_32         num_linnums;    /* used by COFF (after LinnumQueue has been read) */
    };
    uint_32             num_relocs;     /* used by COFF/ELF */
    unsigned            seg_idx;        /* segment #; v2.12: changed from short to unsigned */
    enum seg_type       segtype;        /* segment's type (code, data, ...) */
    int                 lname_idx;      /* segment's name LNAME index (OMF only) */
    struct asym         *clsym;         /* segment's class name (stored in an asym item) */
    union {
        uint_16         abs_frame;      /* ABS seg, frame number (OMF,BIN) */
#if COMDATSUPP
        uint_16         comdat_number;  /* associated COMDAT segno (COFF) */
        uint_16         comdat_idx;     /* lname index of COMDAT symbol (OMF) */
#endif
    };
    union {
        uint_32         abs_offset;     /* ABS seg, offset (OMF only) */
        char            *aliasname;     /* ALIAS name (COFF/ELF only) */
    };
    unsigned char       Ofssize;        /* segment's offset size */
    unsigned char       characteristics;/* used by COFF/ELF/PE */
    unsigned char       alignment;      /* is value 2^x */

    unsigned char       readonly:1;     /* if segment is readonly */
    unsigned char       info:1;         /* if segment is info only (COFF/ELF) */
    unsigned char       force32:1;      /* force 32bit segdef (OMF only) */
    unsigned char       data_in_code:1; /* data items in code segm (OMF only) */
    unsigned char       internal:1;     /* internal segment with private buffer */
    unsigned char       written:1;      /* code/data just written */
    unsigned char       linnum_init:1;  /* v2.10: linnum data emitted for segment? */
    unsigned char       combine:3;      /* combine type, see omfspec.h */
#if COMDATSUPP
    unsigned char       comdat_selection:3; /* if > 0, it's a COMDAT (COFF/OMF) */
#endif
};

#define MAX_SEGALIGNMENT 0xFF

/* PROC item */

struct proc_info {
    uint_16             *regslist;      /* PROC: list of registers to be saved */
    struct dsym         *paralist;      /* list of parameters */
    struct dsym         *locallist;     /* PROC: list of local variables */
    struct dsym         *labellist;     /* PROC: list of local labels */
    unsigned            parasize;       /* total no. of bytes used by parameters */
    unsigned            localsize;      /* PROC: total no. of bytes used by local variables */
    unsigned            locals;
    unsigned             vsize;
    char                *prologuearg;   /* PROC: prologuearg attribute */
    unsigned char       vecregs[6];
    unsigned char       vecregsize[6];
    unsigned char       vregs[6];
    unsigned char       xyzused[6];
    unsigned char       delregsused[3]; /* added for delphi used registers v.29 */
    unsigned char       vecused;
	
	enum returntype     ret_type;		/* return type from proc */
	bool                isleaf;

#if SYSV_SUPPORT
	unsigned char       firstGPR;		/* Added for systemv call vararg to track the first available registers that can be used */
	unsigned char       firstVEC;
	unsigned char       vararg_vecs;	/* Count of vector registers used in vararg */
	char                stackOps[64][MAX_LINE_LEN];
	unsigned            stackOpCount;
	unsigned            stackOfs;
	unsigned            stackAdj;
#endif

#if AMD64_SUPPORT
    struct asym         *exc_handler;   /* PROC: exc handler set by FRAME */
    int                 ReservedStack;  /* PROC: win64: additional reserved stack */
    int                 stored_reg;     /* number of stored general registers in home spaces */
    int					pushed_reg;		/* number of pushed registers */
    int                 home_taken;     /* number of taken spaces in a home space */
    int                 xmmsize;        /* size of saved xmm registers */
    char                home_used[6];   /* used shadows home space */
#endif
    uint_32             prolog_list_pos;/* PROC: prologue list pos */
    union {
        unsigned char   flags;
        struct {
            unsigned char  has_vararg:1;/* last param is VARARG */
            unsigned char  pe_type:1;   /* PROC: prolog-epilog type, 1=use LEAVE */
            unsigned char  isexport:1;  /* PROC: EXPORT attribute set */
            unsigned char  forceframe:1;/* PROC: FORCEFRAME prologuearg? */
            unsigned char  loadds:1;    /* PROC: LOADDS prologuearg? */
            unsigned char  stackparam:1;/* PROC: 1=stack params exists ( not just register params ) */
#if AMD64_SUPPORT
            unsigned char  isframe:1;   /* PROC: FRAME attribute set? */
#endif
#if STACKBASESUPP
            unsigned char  fpo:1;
#endif
        };
    };
    uint_8              size_prolog;    /* PROC: v2.10: prologue size */
#if STACKBASESUPP
    uint_16             basereg;        /* PROC: v2.11: stack base register */
#endif
	uint_8              NoSub;
	int                frameofs;		/* Optimise 1byte displace to access locals from RBP by using a frame offset */
    bool               prologueDone;    /* UASM 2.51 check when prologue has been completed */
};

/* macro parameter */

struct mparm_list {
    //const char          *label;         /* name of parameter */
    char                *deflt;         /* optional default parm */
    unsigned char       required:1;     /* is parm required (REQ) */
};

/* macro line */

struct srcline {
    struct srcline      *next;
    uint_8              ph_count; /* placeholders contained in this line */
    char                line[1];
};

/* macro item */

struct macro_info {
    uint_16             parmcnt;    /* no of params */
    union {
        uint_16         localcnt;   /* no of locals */
        uint_16         autoexp;    /* auto-expansion flags if predefined macro */
    };
    struct mparm_list   *parmlist;  /* array of parameter items */
    struct srcline      *data;      /* prepared macro source lines */
#ifdef DEBUG_OUT
    uint_32             count;      /* no of times the macro was invoked */
#endif
    unsigned            srcfile;    /* sourcefile index */
};

/* STRUCT field */

struct sfield {
    struct asym         sym;        /* field symbol ( state=SYM_STRUCT_FIELD ) */
    struct sfield       *next;      /* next field in STRUCT,UNION,RECORD */
    //char                *init_dir; /* v2.09: removed ; previously: not used by record fields */
    char                ivalue[1];  /* v2.09: type changed from char * to char[] */
};
//struct svecfield {
//    struct dsym         sym;        /* field symbol ( state=SYM_STRUCT_FIELD ) */
//    struct svecfield       *next;      /* next field in STRUCT,UNION,RECORD */
//    //char                *init_dir; /* v2.09: removed ; previously: not used by record fields */
//    char                ivalue[1];  /* v2.09: type changed from char * to char[] */
//};

enum type_kind {
    TYPE_NONE,
    TYPE_STRUCT,
    TYPE_UNION,
    TYPE_TYPEDEF,
    TYPE_RECORD
};


enum struct_simd
{
       NOVEC,
       MM128,
       MM256,
       MM512
}; 
struct struct_info {
    struct sfield       *head; /* STRUCT/UNION/RECORD: start of field list */
    struct sfield       *tail; /* STRUCT/UNION/RECORD: current/next field */
    /* v2.08: typekind moved to struct asym */
    //#ifdef __WATCOMC__
    //    enum type_kind      typekind;
    //#else
    //    uint_8              typekind;
    //#endif
    enum struct_simd    stype;       /* indicates if the structure is a valid SIMD vector type */
    uint_8              isHomogenous;
    uint_8              isHVA;
    uint_8              isHFA;
    uint_32             memberCount;
    uint_8              alignment;   /* STRUCT: 1,2,4,8,16 or 32 */
    union {
        uint_8          flags;
        struct {
            unsigned char   isInline:1;  /* STRUCT/UNION: inline (unused) */
            unsigned char   isOpen:1;    /* STRUCT/UNION: set until the matching ENDS is found */
            unsigned char   OrgInside:1; /* STRUCT: struct contains an ORG */
        };
    };
};
/* dsym originally was a "directive_node"
 * However, currently all symbols except SYM_STRUCT_FIELDs are allocated as a dsym.
 * the additional 3 fields are used differently depending on symbol's type.
 */

struct dsym {
    struct asym sym;
    union {
        struct seg_info     *seginfo;   /* SYM_SEG (segments) */
        struct grp_info     *grpinfo;   /* SYM_GRP (groups) */
        struct proc_info    *procinfo;  /* SYM_INTERNAL|SYM_EXTERNAL (procs, isproc=1) */
        struct struct_info  *structinfo;/* SYM_TYPE (structs, unions, records [, typedefs]) */
        struct macro_info   *macroinfo; /* SYM_MACRO (macros) */
        /* SYM_STACK, SYM_INTERNAL (code labels, isproc=0)
         * used to save the local hash table (contains PROC locals: params,
         * locals, labels). Details see SymGetLocal(), SymSetLocal() in symbols.c
         */
        struct dsym *nextll;
    } e;
    /* next item in linked lists of certain symbol types.
     * - SYM_UNDEFINED -> TAB_UNDEF
     * - SYM_EXTERNAL  -> TAB_EXT
     * - SYM_SEG       -> TAB_SEG
     * - SYM_GRP       -> TAB_GRP
     * - SYM_ALIAS:    -> TAB_ALIAS
     * for SYM_INTERNAL:
     * linked list of labels for current segment (used for BackPatch)
     */
    struct dsym *next;
    union {
        /* for SYM_UNDEFINED, SYM_EXTERNAL, SYM_ALIAS and SYM_GRP:
         * predecessor of current symbol with the same state, to allow fast removes.
         * Actually, the only symbols which may change the state and thus
         * have a chance to be removed are SYM_UNDEFINED and SYM_EXTERNAL ( weak=TRUE )
         * during pass one.
         */
        struct dsym *prev;
        /* used by PROC symbols (SYM_INTERNAL) for linked list, TAB_PROC */
        struct dsym *nextproc;
        /* used by PROC locals (SYM_STACK) for linked list */
        struct dsym *nextlocal;
        /* used by PROC params (SYM_STACK) for linked list */
        struct dsym *nextparam;
        /* used by SYM_EXTERNAL (weak=FALSE) if altname is set */
        /* v2.11: removed; member is in use for SYM_EXTERNAL */
        //struct dsym *nextext;
    };
};

extern  struct asym     *SymAlloc( const char * );
extern  void            SymFree( struct asym * );
extern  struct asym     *SymCreate( const char * );
extern  struct asym     *SymLCreate( const char * );
extern  struct asym     *SymAddGlobal( struct asym * );
extern  struct asym     *SymAddLocal( struct asym *, const char * );
extern  struct asym     *SymLookup( const char * );
extern  struct asym     *SymLookupLocal( const char * );

extern  struct asym     *SymFind( const char *name );
extern  struct asym     *SymCheck(const char *name);
extern  struct asym     *SymFindLocal( const char *name );
extern  struct asym     *SymFindDeclare( const char *name );
#define SymSearch(x) SymFind(x)

extern  void            SymInit( void );
extern  void            SymFini( void );
extern  void            SymPassInit( int pass );
extern  void            SymMakeAllSymbolsPublic( void );
extern  void            SymGetAll( struct asym ** );
extern  struct asym     *SymEnum( struct asym *, int * );
extern  uint_32         SymGetCount( void );

extern  void            WriteSymbols( void );

#if defined(__WATCOMC__)
typedef int (__watcall * StrCmpFunc)(const void *, const void *, size_t);
#elif defined(_MSC_VER)
typedef int(__cdecl * StrCmpFunc)(const void *, const void *, size_t);
#else
typedef int(*StrCmpFunc)(const void *, const void *, size_t);
#endif
extern StrCmpFunc SymCmpFunc;

extern  void            SymSetCmpFunc( void );
extern  void            SymClearLocal( void );
extern  void            SymSetLocal( struct asym * );
extern  void            SymGetLocal( struct asym * );

#endif
