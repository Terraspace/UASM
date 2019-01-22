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
* Description:  Parser items
*
****************************************************************************/

#ifndef PARSER_H
#define PARSER_H

#include "operands.h"
#include "symbols.h"
#include "token.h"

/* define tokens for SpecialTable (registers, operators, ... ) */
enum special_token {
    T_NULL,
#define  res(token, string, type, value, bytval, flags, cpu, sflags) T_ ## token ,
#include "special.h"
#undef res
/* define tokens for SpecialTable (directives) */
#define  res(token, string, value, bytval, flags, cpu, sflags) T_ ## token ,
#include "directve.h"
#undef res
SPECIAL_LAST
};

/* define tokens for instruction table (InstrTable[] in reswords.c) */

enum instr_token {
    INS_FIRST_1 = SPECIAL_LAST - 1, /* to ensure tokens are unique */
#define  ins(token, string, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix ) T_ ## token ,
#define insx(token, string, opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix,flgs ) T_ ## token ,
#define insn(tok, suffix,   opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix)
#define insm(tok, suffix,   opcls, byte1_info,op_dir,rm_info,opcode,rm_byte,cpu,prefix)
#include "instruct.h"
#undef insm
#undef insn
#undef insx
#undef ins
#if AVXSUPP
#define VEX_START  T_VBROADCASTSS  /* first VEX encoded item */
#define avxins(token, string, cpu, flgs ) T_V ## token ,
#include "instravx.h"
#undef avxins
#endif
};

/*---------------------------------------------------------------------------*/

/* queue of symbols */
struct symbol_queue {
    struct dsym *head;
    struct dsym *tail;
};

enum queue_type {
    TAB_UNDEF = 0,
    TAB_EXT,      /* externals (EXTERNDEF, EXTERN, COMM, PROTO ) */
    TAB_SEG,      /* SEGMENT items */
    TAB_GRP,      /* GROUP items */
    TAB_PROC,     /* PROC items */
    TAB_ALIAS,    /* ALIAS items */
    TAB_LAST,
};

/* several lists, see enum queue_type above */
extern struct symbol_queue SymTables[];

/*
 values for <rm_info> (3 bits)
 000            -> has rm_byte with w-, d- and/or s-bit in opcode
 001( no_RM   ) -> no rm_byte - may have w-bit
 010( no_WDS  ) -> has rm_byte, but w-bit, d-bit, s-bit of opcode are absent
 011( R_in_OP ) -> no rm_byte, reg field (if any) is included in opcode
 */
enum rm_info {
    no_RM   = 0x1,
    no_WDS  = 0x2,
    R_in_OP = 0x3,
};

/* values for <allowed_prefix> (3 bits) */
enum allowed_prefix {
    // AP_NO_PREFIX= 0x00, /* value 0 means "normal" */
    AP_LOCK     = 0x01,
    AP_REP      = 0x02,
    AP_REPxx    = 0x03,
    AP_FWAIT    = 0x04,
    AP_NO_FWAIT = 0x05,
	AP_BND      = 0x06
};

/* values for field type in special_item.
 * it should match order of T_REGISTER - T_RES_ID in token.h
 */

enum special_type {
    RWT_REG = 2,  /* same value as for T_REG */
    RWT_DIRECTIVE,
    RWT_UNARY_OP,
    RWT_BINARY_OP,
    RWT_STYPE,
    RWT_RES_ID
};

// values for sflags if register
enum op1_flags {
    SFR_SIZMSK  = 0x1F, /* size in bits 0-4 */
    SFR_IREG    = 0x20,
    SFR_SSBASED = 0x40, /* v2.11: added */
    SFR_YMMMASK = 0x3F, /* added by habran */
    SFR_ZMMMASK = 0x7F, /* added by habran */
};
/* --        Reserved    P0[3 : 2] Must be 0
 * --        Fixed Value P1[10]    Must be 1
 * EVEX.mm   Compressed legacy escape P[1: 0] Identical to low two bits of VEX.mmmmm
 * EVEX.pp   Compressed legacy prefix P[9 : 8] Identical to VEX.pp
 * EVEX.RXB  Next-8 register specifier modifier P[7 : 5] Combine with ModR/M.reg, ModR/M.rm (base, index/vidx)
 * EVEXR     High-16 register specifier modifier P[4] Combine with EVEX.R and ModR/M.reg
 * EVEXX     High-16 register specifier modifier P[6] Combine with EVEX.B and ModR/M.rm, when SIB/VSIB absent
 * EVEX.vvvv NDS register specifier P[14 : 11] Same as VEX.vvvv
 * EVEXV     High-16 NDS/VIDX register specifier P[19] Combine with EVEX.vvvv or when VSIB present
 * EVEX.aaa  Embedded opmask register specifier P[18 : 16]
 * EVEX.W    Osize promotion/Opcode extension P[15]
 * EVEX.b    Broadcast/RC/SAE Context P[20]
 * EVEX.LL  Vector length/RC P[22 : 21]
 * EVEX.z    Zeroing/Merging P[23]
 */
#define EVEX_P0RMASK    0x80 
#define EVEX_P0XMASK    0x40 
#define EVEX_P0BMASK    0x20 
#define EVEX_P0R1MASK   0x10 
#define EVEX_P0MMMASK   0x03 
#define EVEX_P1WMASK    0x80
#define EVEX_P1VVVV     0x78 
#define EVEX_P1PPMASK   0x03 
#define EVEX_P2ZMASK    0x80 
#define EVEX_P2L1MASK   0x40 
#define EVEX_P2LMASK    0x20 
#define EVEX_P2BMASK    0x10 
#define EVEX_P2VMASK    0x08 
#define EVEX_P2AAAMASK  0x07
#define EVEX_P2LLMASK   0x60
#define W1            0x8000
 /* RXBR00MM,  WVVVV1PP,  ZLLBVAAA, MDREGR/M */
#if AMD64_SUPPORT
enum rex_bits {
    REX_B = 1,  /* regno 0-7 <-> 8-15 of ModR/M or SIB base */
    REX_X = 2,  /* regno 0-7 <-> 8-15 of SIB index */
    REX_R = 4,  /* regno 0-7 <-> 8-15 of ModR/M REG */
    REX_W = 8   /* wide 32 <-> 64 */
};
#endif

/* operand classes. this table is defined in reswords.c.
 * index into this array is member opclsidx in instr_item.
 * v2.06: data removed from struct instr_item.
 */
struct opnd_class {
    enum operand_type opnd_type[2];  /* operands 1 + 2 */
    unsigned char opnd_type_3rd;     /* operand 3 */
};

/* instr_item is the structure used to store instructions
 * in InstrTable (instruct.h).
 * Most compilers will use unsigned type for enums, just OW
 * allows to use the smallest size possible.
 */
struct instr_item {
    unsigned short	opclsidx;			/* v2.06: index for opnd_clstab */
    unsigned char	byte1_info;			/* flags for 1st byte */
    unsigned short	allowed_prefix;		/* allowed prefix */
    unsigned char	first;		        /* 1=opcode's first entry */
    unsigned char	rm_info;	        /* info on r/m byte */
    unsigned char	opnd_dir;	        /* operand direction */
    unsigned short	prefix;				/* used for EVEX */
    unsigned short	cpu;
    unsigned char	opcode;		        /* opcode byte */
    unsigned char	rm_byte;	        /* mod_rm_byte */
};
/* special_item is the structure used to store directives and
 * other reserved words in SpecialTable (special.h).
 */
struct special_item {
    unsigned     value;
    unsigned     sflags;
#ifdef __WATCOMC__
    enum cpu_info   cpu;     /* CPU type */
#else
    uint_16         cpu;     /* CPU type */
#endif
    uint_8          bytval;
#ifdef __WATCOMC__
    enum special_type type;
#else
    uint_8            type;
#endif
};

#define GetRegNo( x )    SpecialTable[x].bytval
#define GetSflagsSp( x ) SpecialTable[x].sflags
#define GetValueSp( x )  SpecialTable[x].value
#define GetMemtypeSp( x ) SpecialTable[x].bytval
#define GetCpuSp( x )    SpecialTable[x].cpu

/* values for <value> if type == RWT_DIRECTIVE */
enum directive_flags {
    DF_CEXPR    = 0x01, /* avoid '<' being used as string delimiter (.IF, ...) */
    DF_STRPARM  = 0x02, /* directive expects string param(s) (IFB, IFDIF, ...) */
                        /* enclose strings in <> in macro expansion step */
    DF_NOEXPAND = 0x04, /* don't expand params for directive (PURGE, FOR, IFDEF, ...) */
    DF_LABEL    = 0x08, /* directive requires a label */
    DF_NOSTRUC  = 0x10, /* directive not allowed inside structs/unions */
    DF_NOCONCAT = 0x20, /* don't concat line */
    DF_PROC     = 0x40, /* directive triggers prologue generation */
    DF_STORE    = 0x80, /* FASTPASS: directive triggers line store */
    DF_CGEN     = 0x100 /* directive generates lines */
};

/* values for <bytval> if type == RWT_DIRECTIVE */
#define  res(token, function) DRT_ ## token ,
enum directive_type {
#include "dirtype.h"
};
#undef  res

#define MAX_OPND 4

struct opnd_item {
    enum operand_type type;
    union {
        struct {
            int_32    data32l;
            int_32    data32h; /* needed for OP_I48 and OP_I64 */
        };
        uint_64       data64;
    };
    struct fixup      *InsFixup;
	const char        *tokenPtr;
};

/* compressed tuple types upper bits 4,3,2,1,0 of resw_strings[].prefix : tuple & 0x1F  */
enum ttypes {
    FV    =  1,
    HV    =  2,
    FVM   =  3,
    T1S8  =  4,
    T1S16 =  5,
    T1S   =  6,
    T1F32 =  7,
    T1F64 = 10,
    T2    = 11,
    T4    = 12,
    T8    = 13,
    HVM   = 14,
    QVM   = 15,
    OVM   = 16,
    T128  = 17,
    DUP   = 20
};
/* compressed memory size bits 7,6,5 of resw_strings[].prefix: first 5 >> xSIZE and than 1 << xSIZE  */
enum mtypes {
    BSIZE  = 0x00, //  1
    WSIZE  = 0x20, //  2
    DSIZE  = 0x40, //  4 
    QSIZE  = 0x60, //  8 
    XSIZE  = 0x80, // 16 
    YSIZE  = 0xA0, // 32 
    ZSIZE  = 0xC0  // 64 
};
enum indextypes {
    IXSZ  = 0x0000,
    IYSZ  = 0x0100,
    IZSZ  = 0x0200,
};
/* code_info describes the current instruction. It's the communication
 * structure between parser and code generator.
 */
struct code_info {
    struct {
        enum instr_token ins;          /* prefix before instruction, e.g. lock, rep, repnz */
        enum assume_segreg RegOverride;/* segment override (0=ES,1=CS,2=SS,3=DS,...) */
#if AMD64_SUPPORT
        unsigned char   rex;
#endif
        unsigned char   adrsiz:1;      /* address size prefix 0x67 is to be emitted */
        unsigned char   opsiz:1;       /* operand size prefix 0x66 is to be emitted */
    } prefix;
    const struct instr_item *pinstr;   /* current pointer into InstrTable */
    enum instr_token token;
    enum memtype    mem_type;          /* byte / word / etc. NOT near/far */
    struct opnd_item opnd[MAX_OPND];
    unsigned char   rm_byte;
    unsigned char   sib;
    unsigned char   Ofssize;
    unsigned char   opc_or;
    unsigned char   first_byte;        /* added for 2.46  for 0xC4 or 0xC5 */
    /* habran */
#if AVXSUPP
    unsigned char   basetype;
    unsigned char   reg1;
    unsigned char   reg2;
    unsigned char   reg3;
    unsigned char   indexreg;
    unsigned char   basereg;
    unsigned int    r1type;
    unsigned int    r2type;
          int_32   vexconst;
    unsigned char   vexregop;   /* in based-1 format (0=empty) */
    /* habran */
    unsigned int   indextype;  /* Used for EVEX */
    unsigned char   evex_flag; /* for EVEX instructions */
    unsigned char   evex_p0;
    unsigned char   evex_p1;
    unsigned char   evex_p2;
    unsigned char   zreg;
             bool   tuple;     /* For EVEX Compressed Disp8*N Encoding */
			 bool   isptr;
    unsigned char   evex_sae;  /* EVEX Static Rounding Mode */
#endif
    union {
        unsigned char flags;
        struct {
            unsigned char   iswide:1;       /* 0=byte, 1=word/dword/qword */
            unsigned char   isdirect:1;     /* 1=direct addressing mode */
            unsigned char   isfar:1;        /* CALL/JMP far */
            unsigned char   const_size_fixed:1; /* v2.01 */
#if AMD64_SUPPORT
            unsigned char   x86hi_used:1;   /* AH,BH,CH,DH used */
            unsigned char   x64lo_used:1;   /* SPL,BPL,SIL,DIL used */
#endif
            unsigned char   undef_sym:1;    /* v2.06b: struct member is forward ref */
        };
    };
};

#define OPND1 0
#define OPND2 1
#define OPND3 2
#define OPND4 3

/* branch instructions are still sorted:
 * CALL, JMP, Jcc, J[e|r]CXZ, LOOP, LOOPcc
 */

#define IS_CALL( inst )       ( inst == T_CALL )
#define IS_JMPCALL( inst )    ( inst == T_CALL || inst == T_JMP    )
#define IS_JMP( inst )        ( inst >= T_JMP  && inst < T_LOOP  )
#define IS_JCC( inst )        ( inst >  T_JMP  && inst < T_JCXZ  )
#define IS_BRANCH( inst )     ( inst >= T_CALL && inst < T_LOOP  )
#define IS_ANY_BRANCH( inst ) ( inst >= T_CALL && inst <= T_LOOPNZW )
#define IS_XCX_BRANCH( inst ) ( inst >= T_JCXZ && inst <= T_LOOPNZW )

#define IS_OPER_32( s )   ( s->Ofssize ? ( s->prefix.opsiz == FALSE ) : ( s->prefix.opsiz == TRUE ))

/* globals */
//extern struct asym           WordSize;
//#define CurrWordSize WordSize.value
extern const struct instr_item   InstrTable[];   /* instruction table */
extern const struct special_item SpecialTable[]; /* rest of res words */
extern uint_16                   optable_idx[];  /* helper, access thru IndexFromToken() only */

#define IndexFromToken( tok )  optable_idx[ ( tok ) - SPECIAL_LAST ]

extern int        SizeFromMemtype( enum memtype, int, struct asym * );
extern ret_code   MemtypeFromSize( int, enum memtype * );
extern int        SizeFromRegister( int );
extern ret_code   GetLangType( int *, struct asm_tok[], enum lang_type * );

extern void       sym_add_table( struct symbol_queue *, struct dsym * );
extern void       sym_remove_table( struct symbol_queue *, struct dsym * );
extern void       sym_ext2int( struct asym * );

extern int        OperandSize( enum operand_type, const struct code_info * );
extern void       set_frame( const struct asym *sym );
extern void       set_frame2( const struct asym *sym );
extern ret_code   ParseLine( struct asm_tok[] );
extern void       ProcessFile( struct asm_tok[] );

extern void       WritePreprocessedLine( const char * );

#endif
