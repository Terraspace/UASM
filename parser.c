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
* Description:  Parser
*
****************************************************************************/
#include <ctype.h>
#include <limits.h>
#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "preproc.h"
#include "reswords.h"
#include "codegen.h"
#include "codegenv2.h"
#include "expreval.h"
#include "fixup.h"
#include "types.h"
#include "label.h"
#include "segment.h"
#include "assume.h"
#include "proc.h"
#include "myassert.h"
#include "input.h"
#include "tokenize.h"
#include "listing.h"
#include "data.h"
#include "fastpass.h"
#include "omf.h"
#include "omfspec.h"
#include "condasm.h"
#include "extern.h"
#include "atofloat.h"


#if defined(WINDOWSDDK)
#define PRIx64       "llx"
#else
#include <inttypes.h>
#endif

#define ADDRSIZE( s, x ) ( ( ( x ) ^ ( s ) ) ? TRUE : FALSE )
#define IS_ADDR32( s )  ( s->Ofssize ? ( s->prefix.adrsiz == FALSE ) : ( s->prefix.adrsiz == TRUE ))

#define OPSIZE32( s ) ( ( s->Ofssize ) ? FALSE : TRUE )
#define OPSIZE16( s ) ( ( s->Ofssize ) ? TRUE : FALSE )

#define InWordRange( val ) ( (val > 65535 || val < -65535) ? FALSE : TRUE )

extern ret_code (* const directive_tab[])( int, struct asm_tok[] );

/* parsing of branch instructions with imm operand is found in branch.c */
extern ret_code         process_branch( struct code_info *, unsigned, const struct expr * );

extern enum proc_status    ProcStatus;
extern const int_64        maxintvalues[];
extern const int_64        minintvalues[];
extern const struct opnd_class opnd_clstab[];
extern const uint_8        vex_flags[];
extern int_8			   Frame_Type;      /* Frame of current fixup */
extern uint_16			   Frame_Datum;     /* Frame datum of current fixup */
struct asym                *SegOverride;
static enum assume_segreg  LastRegOverride;	/* needed for CMPS */

struct asm_tok      xmmOver0;				/* xmmword override tokens for -Zg switch (masm compatibility) */
struct asm_tok      xmmOver1;
struct asm_tok      dsOver;

/* linked lists of:     index
 *--------------------------------
 * - undefined symbols  TAB_UNDEF
 * - externals          TAB_EXT
 * - segments           TAB_SEG
 * - groups             TAB_GRP
 * - procedures         TAB_PROC
 * - aliases            TAB_ALIAS */
struct symbol_queue SymTables[TAB_LAST];

/* =====================================================================
  Return true if register a simd register (xmm,ymm,zmm).
  ===================================================================== */
bool IsSimdReg(struct asm_tok *regTok)
{
	bool result = FALSE;
	if (regTok)
	{
		if (regTok->tokval >= T_XMM0 && regTok->tokval <= T_XMM7)
			result = TRUE;
		else if (regTok->tokval >= T_XMM8 && regTok->tokval <= T_XMM15)
			result = TRUE;
		else if (regTok->tokval >= T_XMM16 && regTok->tokval <= T_XMM23)
			result = TRUE;
		else if (regTok->tokval >= T_XMM24 && regTok->tokval <= T_XMM31)
			result = TRUE;
		else if (regTok->tokval >= T_YMM0 && regTok->tokval <= T_YMM7)
			result = TRUE;
		else if (regTok->tokval >= T_YMM8 && regTok->tokval <= T_YMM15)
			result = TRUE;
		else if (regTok->tokval >= T_YMM16 && regTok->tokval <= T_YMM23)
			result = TRUE;
		else if (regTok->tokval >= T_YMM24 && regTok->tokval <= T_YMM31)
			result = TRUE;
		else if (regTok->tokval >= T_ZMM0 && regTok->tokval <= T_ZMM7)
			result = TRUE;
		else if (regTok->tokval >= T_ZMM8 && regTok->tokval <= T_ZMM31)
			result = TRUE;
	}
	return result;
}

/* add item to linked list of symbols */
void sym_add_table( struct symbol_queue *queue, struct dsym *item )
/*****************************************************************/
{
#ifdef DEBUG_OUT
    if ( queue == &SymTables[TAB_UNDEF] )
        item->sym.fwdref = TRUE;
#endif
    if( queue->head == NULL ) {
        queue->head = queue->tail = item;
        item->next = item->prev = NULL;
    } else {
        item->prev = queue->tail;
        queue->tail->next = item;
        queue->tail = item;
        item->next = NULL;
    }
}

/* remove an item from a symbol queue.
 * this is called only for TAB_UNDEF and TAB_EXT,
 * segments, groups, procs or aliases never change their state. */
void sym_remove_table( struct symbol_queue *queue, struct dsym *item )
/********************************************************************/
{
    /* unlink the node */
    if( item->prev )
        item->prev->next = item->next;
    if( item->next )
        item->next->prev = item->prev;

    //if ( dir->next == NULL )
    //    dir->next = dir->prev;

    if ( queue->head == item )
        queue->head = item->next;
    if ( queue->tail == item )
        queue->tail = item->prev;

    item->next = NULL;
    item->prev = NULL;
}

void sym_ext2int( struct asym *sym )
/**********************************/
/* Change symbol state from SYM_EXTERNAL to SYM_INTERNAL.
 * called by:
 * - CreateConstant()             EXTERNDEF name:ABS           -> constant
 * - CreateAssemblyTimeVariable() EXTERNDEF name:ABS           -> assembly-time variable
 * - CreateLabel()                EXTERNDEF name:NEAR|FAR|PROC -> code label
 * - data_dir()                   EXTERNDEF name:typed memref  -> data label
 * - ProcDir()           PROTO or EXTERNDEF name:NEAR|FAR|PROC -> PROC
 */
{
    /* v2.07: GlobalQueue has been removed */
    if ( sym->isproc == FALSE && sym->ispublic == FALSE ) {
        sym->ispublic = TRUE;
        AddPublicData( sym );
    }
    sym_remove_table( &SymTables[TAB_EXT], (struct dsym *)sym );
    if ( sym->isproc == FALSE ) /* v2.01: don't clear flags for PROTO */
        sym->first_size = 0;
    sym->state = SYM_INTERNAL;
}

ret_code GetLangType( int *i, struct asm_tok tokenarray[], enum lang_type *plang )
/********************************************************************************/
{
    if( tokenarray[*i].token == T_RES_ID ) {
#if 1 /* v2.03: simplified */
        if ( tokenarray[(*i)].tokval >= T_C &&
            tokenarray[(*i)].tokval <= T_BORLAND ) { /* 2.15 implemented the VECTORCALL */
            *plang = tokenarray[(*i)].bytval;
            (*i)++;
            return( NOT_ERROR );
        }
#else
        switch( tokenarray[(*i)].tokval ) {
        case T_C:         *plang = LANG_C;          break;
        case T_SYSCALL:   *plang = LANG_SYSCALL;    break;
        case T_STDCALL:   *plang = LANG_STDCALL;    break;
        case T_PASCAL:    *plang = LANG_PASCAL;     break;
        case T_FORTRAN:   *plang = LANG_FORTRAN;    break;
        case T_BASIC:     *plang = LANG_BASIC;      break;
        case T_FASTCALL:  *plang = LANG_FASTCALL;   break;
        case T_VECTORCALL:*plang = LANG_VECTORCALL; break;
        case T_SYSVCALL:  *plang = LANG_SYSVCALL;   break;
        case T_BORLAND    *plang = LANG_DELPHICALL; break;
        default:
            return( ERROR );
        }
        (*i)++;
        return( NOT_ERROR );
#endif
    }
    return( ERROR );
}

/* get size of a register
 * v2.06: rewritten, since the sflags field
 * does now contain size for GPR, STx, MMX, XMM regs. */
int SizeFromRegister( int registertoken )
/***************************************/
{
    unsigned flags;
    if (((registertoken >= T_YMM0) && (registertoken <= T_YMM7 ))||
      ((registertoken >= T_YMM8) && (registertoken <= T_YMM31 )))
      flags = GetSflagsSp( registertoken ) & SFR_YMMMASK ;
    else if (((registertoken >= T_ZMM0) && (registertoken <= T_ZMM7 ))||
      ((registertoken >= T_ZMM8) && (registertoken <= T_ZMM31 )))
      flags = GetSflagsSp( registertoken ) & SFR_ZMMMASK ;
    else
      flags = GetSflagsSp( registertoken ) & SFR_SIZMSK;

    if ( flags )
        return( flags );

    flags = GetValueSp( registertoken );
    if ( flags & OP_SR )
        return( CurrWordSize );

    /* CRx, DRx, TRx remaining */
#if AMD64_SUPPORT
    return( ModuleInfo.Ofssize == USE64 ? 8 : 4 );
#else
    return( 4 );
#endif
}

/* get size from memory type */
/* MT_PROC memtype is set ONLY in typedefs ( state=SYM_TYPE, typekind=TYPE_TYPEDEF)
 * and makes the type a PROTOTYPE. Due to technical (obsolete?) restrictions the
 * prototype data is stored in another symbol and is referenced in the typedef's
 * target_type member. */
int SizeFromMemtype( enum memtype mem_type, int Ofssize, struct asym *type )
/**************************************************************************/
{
if ((mem_type & MT_SPECIAL) == 0){
#if AVXSUPP
  if (mem_type == MT_ZMMWORD )
    return (0x40);
  else
#endif
  return ((mem_type & MT_SIZE_MASK) + 1);
  }
    if ( Ofssize == USE_EMPTY )
        Ofssize = ModuleInfo.Ofssize;

    switch ( mem_type ) {
    case MT_NEAR:
        DebugMsg1(("SizeFromMemtype( MT_NEAR, Ofssize=%u )=%u\n", Ofssize, 2 << Ofssize ));
        return ( 2 << Ofssize );
    case MT_FAR:
        DebugMsg1(("SizeFromMemtype( MT_FAR, Ofssize=%u )=%u\n", Ofssize, ( 2 << Ofssize ) + 2 ));
        return ( ( 2 << Ofssize ) + 2 );
    case MT_PROC:
        DebugMsg1(("SizeFromMemtype( MT_PROC, Ofssize=%u, type=%s )=%u\n", Ofssize, type->name, ( 2 << Ofssize ) + ( type->isfar ? 2 : 0 ) ));
        /* v2.09: use type->isfar setting */
        //return( ( 2 << Ofssize ) + ( ( SIZE_CODEPTR & ( 1 << ModuleInfo.model ) ) ? 2 : 0 ) );
        return( ( 2 << Ofssize ) + ( type->isfar ? 2 : 0 ) );
    case MT_PTR:
        DebugMsg1(("SizeFromMemtype( MT_PTR, Ofssize=%u )=%u\n", Ofssize, ( 2 << Ofssize ) + ( ( SIZE_DATAPTR & ( 1 << ModuleInfo.model ) ) ? 2 : 0 ) ));
        return( ( 2 << Ofssize ) + ( ( SIZE_DATAPTR & ( 1 << ModuleInfo.model ) ) ? 2 : 0 ) );
    case MT_TYPE:
        if ( type )
          return( type->total_size );
    default:
        DebugMsg1(("SizeFromMemtype( memtype=%Xh, Ofssize=%u )=%u\n", mem_type, Ofssize, 0 ));
        return( 0 );
    }
}

/* get memory type from size */
ret_code MemtypeFromSize( int size, enum memtype *ptype )
/*******************************************************/
{
    int i;
    for ( i = T_BYTE; SpecialTable[i].type == RWT_STYPE; i++ ) {
        if( ( SpecialTable[i].bytval & MT_SPECIAL ) == 0 ) {
            /* the size is encoded 0-based in field mem_type */
#if AVXSUPP
          if (SpecialTable[i].bytval == MT_ZMMWORD){
            if (((SpecialTable[i].bytval & 0x3f) + 1) == size) {
              *ptype = SpecialTable[i].bytval;
              return(NOT_ERROR);
              }
            }
            else{
#endif
              if (((SpecialTable[i].bytval & MT_SIZE_MASK) + 1) == size) {
                *ptype = SpecialTable[i].bytval;
                return(NOT_ERROR);
                }
#if AVXSUPP
              }
#endif

        }
    }
    return( ERROR );
}

static bool IsScalarSimdInstr(enum instr_token instr)
{
	bool result = FALSE;
	switch (instr)
	{
	case T_ADDSS:
	case T_ADDSD:
	case T_CMPSD:
	case T_CMPSS:
	case T_COMISD:
	case T_COMISS:
	case T_CVTSD2SI:
	case T_CVTSD2SS:
	case T_CVTSI2SD:
	case T_CVTSI2SS:
	case T_CVTSS2SD:
	case T_CVTSS2SI:
	case T_CVTTSD2SI:
	case T_CVTTSS2SI:
	case T_DIVSD:
	case T_DIVSS:
	case T_INSERTPS:
	case T_MAXSD:
	case T_MAXSS:
	case T_MINSD:
	case T_MINSS:
	case T_MOVD:
	case T_MOVQ:
	case T_MOVDDUP:
	case T_MOVHPD:
	case T_MOVHPS:
	case T_MOVLPD:
	case T_MOVLPS:
	case T_MOVSD:
	case T_MOVSS:
	case T_MULSD:
	case T_MULSS:
	case T_RCPSS:
	case T_ROUNDSS:
	case T_ROUNDSD:
	case T_RSQRTSS:
	case T_SQRTSS:
	case T_SQRTSD:
	case T_SUBSS:
	case T_SUBSD:
	case T_UCOMISS:
	case T_UCOMISD:
	case T_PEXTRB:
	case T_PEXTRD:
	case T_PEXTRQ:
	case T_VPEXTRB:
	case T_VPEXTRD:
	case T_VPEXTRQ:
	case T_PEXTRW:
	case T_VPEXTRW:
	case T_PINSRB:
	case T_PINSRD:
	case T_PINSRQ:
	case T_VPINSRB:
	case T_VPINSRD:
	case T_VPINSRQ:
	case T_PINSRW:
	case T_VPINSRW:
	case T_VADDSS:
	case T_VADDSD:
	case T_VCMPSD:
	case T_VCMPSS:
	case T_VCOMISD:
	case T_VCOMISS:
	case T_VCVTSD2SI:
	case T_VCVTSD2SS:
	case T_VCVTSI2SD:
	case T_VCVTSI2SS:
	case T_VCVTSS2SD:
	case T_VCVTSS2SI:
	case T_VCVTTSD2SI:
	case T_VCVTTSS2SI:
	case T_VDIVSD:
	case T_VDIVSS:
	case T_VINSERTPS:
	case T_VMAXSD:
	case T_VMAXSS:
	case T_VMINSD:
	case T_VMINSS:
	case T_VMOVD:
	case T_VMOVQ:
	case T_VMOVDDUP:
	case T_VMOVHPD:
	case T_VMOVHPS:
	case T_VMOVLPD:
	case T_VMOVLPS:
	case T_VMOVSD:
	case T_VMOVSS:
	case T_VMULSD:
	case T_VMULSS:
	case T_VRCPSS:
	case T_VROUNDSS:
	case T_VROUNDSD:
	case T_VRSQRTSS:
	case T_VSQRTSS:
	case T_VSQRTSD:
	case T_VSUBSS:
	case T_VSUBSD:
	case T_VUCOMISS:
	case T_VUCOMISD:
    case T_VPBROADCASTD:
		result = TRUE;
		break;
	default:
		break;
	}
	return(result);
}

int OperandSize( enum operand_type opnd, const struct code_info *CodeInfo )
/*************************************************************************/
{
    /* v2.0: OP_M8_R8 and OP_M16_R16 have the DFT bit set! */
    if( opnd == OP_NONE ) {
        return( 0 );
    } else if( opnd == OP_M ) {
        return( SizeFromMemtype( CodeInfo->mem_type, CodeInfo->Ofssize, NULL ) );
    } else if( opnd & ( OP_R8 | OP_M08 | OP_I8 ) ) {
        return( 1 );
    } else if( opnd & ( OP_R16 | OP_M16 | OP_I16 | OP_SR ) ) {
        return( 2 );
    } else if( opnd & ( OP_R32 | OP_M32 | OP_I32 ) ) {
        return( 4 );
#if AMD64_SUPPORT
    } else if( opnd & ( OP_R64 | OP_M64 | OP_MMX | OP_I64 ) ) {
#else
    } else if( opnd & ( OP_M64 | OP_MMX ) ) {
#endif
        return( 8 );
//    } else if( opnd & ( OP_I | OP_I48 ) ) {
    } else if( opnd & ( OP_I48 | OP_M48 ) ) {
        return( 6 );
    } else if( opnd & ( OP_STI | OP_M80 ) ) {
        return( 10 );
    } else if( opnd & ( OP_XMM | OP_M128 ) ) {
        return( 16 );
#if AVXSUPP
    }else if (opnd & (OP_K | OP_M64)) {
      return(8);
    }else if (opnd & (OP_YMM | OP_M256)) {
        return( 32 );
    }else if (opnd & (OP_ZMM | OP_M512)) {
      return(64);
#endif
    } else if( opnd & OP_RSPEC ) {
#if AMD64_SUPPORT
        return( ( CodeInfo->Ofssize == USE64 ) ? 8 : 4 );
#else
        return( 4 );
#endif
    }
    DebugMsg1(("OperandSize: unhandled operand type %Xh!!!\n", opnd ));
    return( 0 );
}

static int comp_mem16( int reg1, int reg2 )
/*****************************************/
/*
- compare and return the r/m field encoding of 16-bit address mode;
- call by set_rm_sib() only;
*/
{
    switch( reg1 ) {
    case T_BX:
        switch( reg2 ) {
        case T_SI: return( RM_BX_SI ); /* 00 */
        case T_DI: return( RM_BX_DI ); /* 01 */
        }
        break;
    case T_BP:
        switch( reg2 ) {
        case T_SI: return( RM_BP_SI ); /* 02 */
        case T_DI: return( RM_BP_DI ); /* 03 */
        }
        break;
    default:
        return( EmitError( MULTIPLE_INDEX_REGISTERS_NOT_ALLOWED ) );
    }
    return( EmitError( MULTIPLE_BASE_REGISTERS_NOT_ALLOWED ) );
}

static void check_assume( struct code_info *CodeInfo, const struct asym *sym, enum assume_segreg default_reg )
/************************************************************************************************************/
/* Check if an assumed segment register is found, and
 * set CodeInfo->RegOverride if necessary.
 * called by seg_override().
 * at least either sym or SegOverride is != NULL.
 */
{
    enum assume_segreg     reg;
    struct asym            *assume;

    if( sym && sym->state == SYM_UNDEFINED )
        return;

    reg = GetAssume( SegOverride, sym, default_reg, &assume );
    /* set global vars Frame and Frame_Datum */
    DebugMsg1(("check_assume(%s): calling SetFixupFrame(%s, FALSE)\n", sym ? sym->name : "NULL", assume ? assume->name : "NULL" ));
    SetFixupFrame( assume, FALSE );

    if( reg == ASSUME_NOTHING ) {
        if ( sym ) {
            //if( sym->state != SYM_EXTERNAL && sym->state != SYM_STACK ) {
            /* v1.95: condition changed. Now there's an error msg only if
             * the symbol has an explicite segment.
             */
            if( sym->segment != NULL ) {
                DebugMsg1(("check_assume: no segment register available to access label %s\n", sym->name ));
                EmitErr( CANNOT_ACCESS_LABEL_THROUGH_SEGMENT_REGISTERS, sym->name );
            } else
                CodeInfo->prefix.RegOverride = default_reg;
        } else {
            DebugMsg1(("check_assume: no segment register available to access seg-label %s\n", SegOverride->name ));
            EmitErr( CANNOT_ACCESS_LABEL_THROUGH_SEGMENT_REGISTERS, SegOverride->name );
        }
    } else if( default_reg != EMPTY ) {
        CodeInfo->prefix.RegOverride = reg;
    }
}

static void seg_override( struct code_info *CodeInfo, int seg_reg, const struct asym *sym, bool direct )
/******************************************************************************************************/
/*
 * called by set_rm_sib(). determine if segment override is necessary
 * with the current address mode;
 * - seg_reg: register index (T_DS, T_BP, T_EBP, T_BX, ... )
 */
{
    enum assume_segreg  default_seg;
    struct asym         *assume;

    /* don't touch segment overrides for string instructions */
    //if ( InstrTable[optable_idx[CodeInfo->token]].allowed_prefix == AP_REP ||
    //     InstrTable[optable_idx[CodeInfo->token]].allowed_prefix == AP_REPxx )
    if ( CodeInfo->pinstr->allowed_prefix == AP_REP ||
         CodeInfo->pinstr->allowed_prefix == AP_REPxx )
        return;

    if( CodeInfo->token == T_LEA ) {
        CodeInfo->prefix.RegOverride = EMPTY; /* skip segment override */
        SetFixupFrame( sym, FALSE );
        return;
    }

    switch( seg_reg ) {
    //case T_SS: /* doesn't happen */
    case T_BP:
    case T_EBP:
    case T_ESP:
        /* todo: check why cases T_RBP/T_RSP aren't needed! */
        default_seg = ASSUME_SS;
        break;
    default:
        default_seg = ASSUME_DS;
    }

    if( CodeInfo->prefix.RegOverride != EMPTY ) {
        assume = GetOverrideAssume( CodeInfo->prefix.RegOverride );
        /* assume now holds assumed SEG/GRP symbol */
        if ( sym ) {
            DebugMsg1(("seg_override: sym=%s\n", sym->name ));
            SetFixupFrame( assume ? assume : sym, FALSE );
        } else if ( direct ) {
            /* no label attached (DS:[0]). No fixup is to be created! */
            if ( assume ) {
                DebugMsg1(("seg_override, direct addressing: prefix.adrsiz will be set, assume=%s CI->ofssize=%u\n", assume->name, CodeInfo->Ofssize ));
                CodeInfo->prefix.adrsiz = ADDRSIZE( CodeInfo->Ofssize, GetSymOfssize( assume ) );
                //DebugMsg1(("seg_override: CI->prefix.adrsiz=%u\n", CodeInfo->prefix.adrsiz ));
            } else {
                /* v2.01: if -Zm, then use current CS offset size.
                 * This isn't how Masm v6 does it, but it matches Masm v5.
                 */
                if ( ModuleInfo.m510 )
                    CodeInfo->prefix.adrsiz = ADDRSIZE( CodeInfo->Ofssize, ModuleInfo.Ofssize );
                else
                    CodeInfo->prefix.adrsiz = ADDRSIZE( CodeInfo->Ofssize, ModuleInfo.defOfssize );
            }
        }
    } else {
        if ( sym || SegOverride )
            check_assume( CodeInfo, sym, default_seg );
        if ( sym == NULL && SegOverride ) {
            CodeInfo->prefix.adrsiz = ADDRSIZE( CodeInfo->Ofssize, GetSymOfssize( SegOverride ) );
        }
    }

    if( CodeInfo->prefix.RegOverride == default_seg ) {
        CodeInfo->prefix.RegOverride = EMPTY;
    }
}

/* prepare fixup creation
 * called by:
 * - idata_fixup()
 * - process_branch() in branch.c
 * - data_item() in data.c */
void set_frame( const struct asym *sym )
/**************************************/
{
    SetFixupFrame( SegOverride ? SegOverride : sym, FALSE );
}

/* set fixup frame if OPTION OFFSET:SEGMENT is set and
 * OFFSET or SEG operator was used.
 * called by:
 * - idata_fixup()
 * - data_item() */
void set_frame2( const struct asym *sym )
/***************************************/
{
    SetFixupFrame( SegOverride ? SegOverride : sym, TRUE );
}

static ret_code set_rm_sib(struct code_info *CodeInfo, unsigned CurrOpnd, char ss, int index, int base, const struct asym *sym)
/*******************************************************************************************************************************/
/*
 * encode ModRM and SIB byte for memory addressing.
 * called by memory_operand().
 * in:  ss = scale factor (00=1,40=2,80=4,C0=8)
 *   index = index register (T_DI, T_ESI, ...)
 *    base = base register (T_EBP, ... )
 *     sym = symbol (direct addressing, displacement)
 * out: CodeInfo->rm_byte, CodeInfo->sib, CodeInfo->prefix.rex
 */
  {
  int                 temp;
  unsigned char       mod_field;
  unsigned char       rm_field;
  unsigned char       base_reg;
  unsigned char       idx_reg;
#if AMD64_SUPPORT
  unsigned char       bit3_base;
  unsigned char       bit3_idx;
  unsigned char       rex;
#endif
 // __debugbreak();
  DebugMsg1(("set_rm_sib(scale=%u, index=%d, base=%d, sym=%s) enter [CI.adrsiz=%u]\n", 1 << (ss >> 6), index, base, sym ? sym->name : "NULL", CodeInfo->prefix.adrsiz));

  /* clear mod */
  rm_field = 0;
  CodeInfo->basetype = base;
#if AMD64_SUPPORT
  bit3_base = 0;
  bit3_idx = 0;
  rex = 0;
#endif
  if (CodeInfo->opnd[CurrOpnd].InsFixup != NULL) { /* symbolic displacement given? */
    mod_field = MOD_10;
    }
  else if ((CodeInfo->opnd[CurrOpnd].data32l == 0) || (base == T_RIP)) { /* no displacement (or 0) */
    mod_field = MOD_00;
    }
  else if ((CodeInfo->opnd[CurrOpnd].data32l > SCHAR_MAX)
           || (CodeInfo->opnd[CurrOpnd].data32l < SCHAR_MIN)) {
    mod_field = MOD_10; /* full size displacement */
    }
  else {
    mod_field = MOD_01; /* byte size displacement */
    }
  /* In the case of suppressed base register it has to be swapped with index v2.38 */
  temp = GetValueSp( base );                                 /* get value from SpecialTable */
  if (temp == OP_XMM || temp == OP_YMM || temp == OP_ZMM){   /* base can be only GP register*/
    temp = index;                                            /* swap index with base */
    index = base;
    base = temp;
    temp = CodeInfo->indexreg;                                 /* register numbers need to be swapped as well*/
    CodeInfo->indexreg = CodeInfo->basereg;
    if (temp == 0xff)                                          /* if base is empty  */
    CodeInfo->basereg = 0x10;                                /* use RIP relative addressing RIP reg number is 0x10 */
  else                                                       /* temp contains register number from index */
    CodeInfo->basereg = temp;                                /* use reg number from index */
  }
    if( ( index == EMPTY ) && ( base == EMPTY ) ) {
        /* direct memory.
         * clear the rightmost 3 bits
         */
        CodeInfo->isdirect = TRUE;
        mod_field = MOD_00;

        /* default is DS:[], DS: segment override is not needed */
        seg_override( CodeInfo, T_DS, sym, TRUE );

        DebugMsg1(( "set_rm_sib: direct addressing, CI.Ofssize=%u / adrsize=%u / data=%" I32_SPEC "X\n",
                   CodeInfo->Ofssize, CodeInfo->prefix.adrsiz, CodeInfo->opnd[CurrOpnd].data32l ));
        //if( !IS_ADDR32( CodeInfo ) ) {
        if( ( CodeInfo->Ofssize == USE16 && CodeInfo->prefix.adrsiz == 0 ) ||
            ( CodeInfo->Ofssize == USE32 && CodeInfo->prefix.adrsiz == 1 )) {
            if( !InWordRange( CodeInfo->opnd[CurrOpnd].data32l ) ) {
                /* expect 16-bit but got 32-bit address */
                DebugMsg1(( "set_rm_sib: error, Ofssize=%u, adrsize=%u, data=%" I32_SPEC "X\n",
                        CodeInfo->Ofssize, CodeInfo->prefix.adrsiz, CodeInfo->opnd[CurrOpnd].data32l ));
                return( EmitError( MAGNITUDE_OF_OFFSET_EXCEEDS_16BIT ) );
            }
            rm_field = RM_D16; /* D16=110b */
        } else {
            rm_field = RM_D32; /* D32=101b */
#if AMD64_SUPPORT
	    if ( CodeInfo->Ofssize == USE64 ) {
		   if ( CodeInfo->opnd[CurrOpnd].InsFixup == NULL ) {				
		      rm_field = RM_SIB;    /* 64-bit non-RIP direct addressing */
		      CodeInfo->sib = 0x25; /* IIIBBB, base=101b, index=100b */		
		  } else if ( CodeInfo->opnd[CurrOpnd].InsFixup->type == FIX_OFF32 ) {
		      /* added v2.42 */
		      CodeInfo->opnd[CurrOpnd].InsFixup->type = FIX_RELOFF32;
            }
	    }
#endif
      }
      DebugMsg1(("set_rm_sib, direct, CodeInfo->prefix.adrsiz=%u\n", CodeInfo->prefix.adrsiz ));
    } else if( ( index == EMPTY ) && ( base != EMPTY ) ) {
        /* for SI, DI and BX: default is DS:[],
         * DS: segment override is not needed
         * for BP: default is SS:[], SS: segment override is not needed
         */
        switch( base ) {
        case T_SI:
            rm_field = RM_SI; /* 4 */
            break;
        case T_DI:
            rm_field = RM_DI; /* 5 */
            break;
        case T_BP:
            rm_field = RM_BP; /* 6 */
            if( mod_field == MOD_00 ) {
               if (base != T_RIP) mod_field = MOD_01;
            }
            break;
        case T_BX:
            rm_field = RM_BX; /* 7 */
            break;
        default: /* for 386 and up */
            base_reg = GetRegNo( base );
#if AMD64_SUPPORT
            if (base_reg == 16)
               base_reg=5;  //RIP bytval=16 but we need 5 added by habran
            bit3_base = base_reg >> 3;
            base_reg &= BIT_012;
#endif
            rm_field = base_reg;
            DebugMsg1(("set_rm_sib: base_reg is %u\n", base_reg ));
            if ( base_reg == 4 ) {
                /* 4 is RSP/ESP or R12/R12D, which must use SIB encoding.
                 * SSIIIBBB, ss = 00, index = 100b ( no index ), base = 100b ( ESP ) */
                CodeInfo->sib = 0x24;
            } else if ( base_reg == 5 && mod_field == MOD_00 ) {
                /* 5 is [E|R]BP or R13[D]. Needs displacement */
               // 5 is also RIP register but doesn't need MOD_01
                if (base != T_RIP)  //added by habran
                 mod_field = MOD_01; /* byte size displacement */
            }
#if AMD64_SUPPORT
            /* v2.02 */
            //rex = ( bit3_base << 2 ); /* set REX_R */
            rex = bit3_base; /* set REX_R */
#endif
        }
#if AMD64_SUPPORT
        DebugMsg1(("set_rm_sib, indirect with base, mod_field=%X, rm_field=%X, rex=%X\n", mod_field, rm_field, rex ));
#else
        DebugMsg1(("set_rm_sib, indirect with base, rm_field=%X\n", rm_field ));
#endif
        seg_override( CodeInfo, base, sym, FALSE );
    } else if( ( index != EMPTY ) && ( base == EMPTY ) ) {
        idx_reg = GetRegNo( index );
#if AVXSUPP
        CodeInfo->indextype = GetValueSp( index );
#endif
#if AMD64_SUPPORT
        bit3_idx = idx_reg >> 3;
        idx_reg &= BIT_012;
#endif
        /* mod field is 00 */
        mod_field = MOD_00;
        /* s-i-b is present ( r/m = 100b ) */
        rm_field = RM_SIB;
        /* scale factor, index, base ( 0x05 => no base reg ) */
        CodeInfo->sib = ( ss | ( idx_reg << 3 ) | 0x05 );
#if AMD64_SUPPORT
        rex = (bit3_idx << 1); /* set REX_X */
#endif
        /* default is DS:[], DS: segment override is not needed */
        seg_override( CodeInfo, T_DS, sym, FALSE );
    } else {
        /* base != EMPTY && index != EMPTY */
        base_reg = GetRegNo( base );
        idx_reg  = GetRegNo( index );
        if ( base == T_RIP)
          base_reg = 0x5;
#if AMD64_SUPPORT
        bit3_base = base_reg >> 3;
        bit3_idx  = idx_reg  >> 3;
        base_reg &= BIT_012;
        idx_reg  &= BIT_012;
#endif
        if ( ( GetSflagsSp( base ) & GetSflagsSp( index ) & SFR_SIZMSK ) == 0 ) {
#if AVXSUPP
           CodeInfo->indextype = GetValueSp( index );
           if (CodeInfo->indextype == OP_XMM || CodeInfo->indextype == OP_YMM || CodeInfo->indextype == OP_ZMM){
             ;
           }
          else
#endif
          return( EmitError( CANNOT_MIX_16_AND_32_BIT_REGISTERS ) );
        }
  
        switch( index ) {
        case T_BX:
        case T_BP:
            if( ( temp = comp_mem16( index, base ) ) == ERROR )
                return( ERROR );
            rm_field = temp;
            seg_override( CodeInfo, index, sym, FALSE );
            break;
        case T_SI:
        case T_DI:
            if( ( temp = comp_mem16( base, index ) ) == ERROR )
                return( ERROR );
            rm_field = temp;
            seg_override( CodeInfo, base, sym, FALSE );
            break;
#if AMD64_SUPPORT
        case T_RSP:
        case T_RIP:      //added by habran
#endif
        case T_ESP:
            //EmitErr( CANNOT_BE_USED_AS_INDEX_REGISTER, ??? );
            return( EmitError( INVALID_USE_OF_REGISTER ) );
        default:
            if( base_reg == 5 ) { /* v2.03: EBP/RBP/R13/R13D? */
                if( mod_field == MOD_00 ) {
                    if (base != T_RIP) mod_field = MOD_01;     //ADDED BY HABRAN
                }
            }

            /* s-i-b is present ( r/m = 100b ) */
            rm_field |= RM_SIB;
            CodeInfo->sib = ( ss | idx_reg << 3 | base_reg );
#if AMD64_SUPPORT
            rex = (bit3_idx << 1) + (bit3_base); /* set REX_X + REX_B */
#endif
            seg_override( CodeInfo, base, sym, FALSE );
        } /* end switch(index) */
#if AMD64_SUPPORT
        DebugMsg1(("set_rm_sib, indirect, base+index: mod_field=%X, rm_field=%X, rex=%X\n", mod_field, rm_field, rex ));
#else
        DebugMsg1(("set_rm_sib, indirect, base+index: rm_field=%X\n", rm_field ));
#endif
    }
    if( CurrOpnd == OPND2 ) {
        /* shift the register field to left by 3 bit */
       if ( base == T_RIP )      //added by habran
          mod_field &= BIT_012;
          CodeInfo->rm_byte = mod_field | ( rm_field << 3 ) | ( CodeInfo->rm_byte & BIT_012 );

#if AMD64_SUPPORT
        /* v2.02: exchange B and R, keep X */
        //CodeInfo->prefix.rex |= (rex >> 2 );
        CodeInfo->prefix.rex |= ( ( rex >> 2 ) | ( rex & REX_X ) | (( rex & 1) << 2 ) );
#endif
    } else if( CurrOpnd == OPND1 ) {
       if ( base == T_RIP )     //added by habran
          mod_field &= BIT_012;
        CodeInfo->rm_byte = mod_field | rm_field;
#if AMD64_SUPPORT
        CodeInfo->prefix.rex |= rex;
#endif
    }
    return( NOT_ERROR );
}

/* override handling
 * called by
 * - process_branch()
 * - idata_fixup()
 * - memory_operand() (CodeInfo != NULL)
 * - data_item()
 * 1. If it's a segment register, set CodeInfo->prefix.RegOverride.
 * 2. Set global variable SegOverride if it's a SEG/GRP symbol
 *    (or whatever is assumed for the segment register) */
ret_code segm_override( const struct expr *opndx, struct code_info *CodeInfo )
/****************************************************************************/
{
    struct asym      *sym;

    if( opndx->override != NULL ) {
        if( opndx->override->token == T_REG ) {
            int temp = GetRegNo( opndx->override->tokval );
            if ( SegAssumeTable[temp].error ) {
                DebugMsg(("segm_override: assume error, reg=%u\n", temp ));
                return( EmitError( USE_OF_REGISTER_ASSUMED_TO_ERROR ) );
            }
#if AMD64_SUPPORT
            /* ES,CS,SS and DS overrides are invalid in 64-bit */
			/* UASM 2.48 Allow movabs encoding of any segment register in 64bit */
            if ( CodeInfo && CodeInfo->Ofssize == USE64 && temp < ASSUME_FS && CodeInfo->token != T_MOVABS) {
                return( EmitError( ILLEGAL_USE_OF_SEGMENT_REGISTER ) );
            } 
#endif
            sym = GetOverrideAssume( temp );
            if ( CodeInfo ) {
                /* hack: save the previous reg override value (needed for CMPS) */
                LastRegOverride = CodeInfo->prefix.RegOverride;
                CodeInfo->prefix.RegOverride = temp;
            }
        } else {
            sym = SymSearch( opndx->override->string_ptr );
        }
        if ( sym && ( sym->state == SYM_GRP || sym->state == SYM_SEG ))
            SegOverride = sym;
    }
    return( NOT_ERROR );
}

/* UASM 2.56 - improved check if an immediate fits in 32bits */
static char fits32(int_64 val) {
    uint64_t top = ((uint64_t)val) >> 32;
    if (top == 0 || top == 0x00000000ffffffff)
        return TRUE;
    return FALSE;
}

/* get an immediate operand without a fixup.
 * output:
 * - ERROR: error
 * - NOT_ERROR: ok,
 *   CodeInfo->opnd_type[CurrOpnd] = OP_Ix
 *   CodeInfo->data[CurrOpnd]      = value
 *   CodeInfo->prefix.opsiz
 *   CodeInfo->iswide */
static ret_code idata_nofixup( struct code_info *CodeInfo, unsigned CurrOpnd, const struct expr *opndx )
/******************************************************************************************************/
{
    enum operand_type op_type;
    int_32      value;
    int         size;

    DebugMsg1(("idata_nofixup( CurrOpnd=%u ) enter [opnd kind=%u mem_type=%Xh value=%" I64_SPEC "X]\n", CurrOpnd, opndx->kind, opndx->mem_type, opndx->value64));

    /* jmp/call/jxx/loop/jcxz/jecxz? */
    if( IS_ANY_BRANCH( CodeInfo->token ) ) {
        return( process_branch( CodeInfo, CurrOpnd, opndx ) );
    }
    value = opndx->value;
    CodeInfo->opnd[CurrOpnd].data32l = value;

	/* 64bit immediates are restricted to MOV <reg>,<imm64> */
	if (fits32(opndx->value64)==0 && (CodeInfo->token != T_MOV || 
		(CodeInfo->token == T_MOV && (CodeInfo->opnd[OPND1].type & OP_R64) == 0) ))
	{ 
		/* magnitude > 64 bits? */
		DebugMsg1(("idata_nofixup: error, hlvalue=%" I64_SPEC "X\n", opndx->hlvalue));
		return(EmitConstError(opndx));
	}

    /* v2.03: handle QWORD type coercion here as well!
     * This change also reveals an old problem in the expression evaluator:
     * the mem_type field is set whenever a (simple) type token is found.
     * It should be set ONLY when the type is used in conjuction with the
     * PTR operator!
     * current workaround: query the 'explicit' flag.
     */

    /* use long format of MOV for 64-bit if value won't fit in a signed DWORD */
    if ( CodeInfo->Ofssize == USE64 && CodeInfo->token == T_MOV && CurrOpnd == OPND2 &&
        ( CodeInfo->opnd[OPND1].type & OP_R64 ) &&
        ( opndx->value64 > H_LONG_MAX || opndx->value64 < H_LONG_MIN ||
         (opndx->explicit && ( opndx->mem_type == MT_QWORD || opndx->mem_type == MT_SQWORD ) ) ) ) 
	{
        CodeInfo->opnd[CurrOpnd].type = OP_I64;
        CodeInfo->opnd[CurrOpnd].data32h = opndx->hvalue;
        return( NOT_ERROR );
    }

    /* v2.06: code simplified.
     * to be fixed: the "wide" bit should not be set here!
     * Problem: the "wide" bit isn't set in memory_operand(),
     * probably because of the instructions which accept both
     * signed and unsigned arguments (ADD, CMP, ... ). */
    if ( opndx->explicit ) 
	{
        /* size coercion for immediate value */
        CodeInfo->const_size_fixed = TRUE;
        size = SizeFromMemtype( opndx->mem_type,
                               opndx->Ofssize,
                               opndx->type );
        /* don't check if size and value are compatible. */
        switch ( size ) 
		{
			case 1: op_type = OP_I8;  break;
			case 2: op_type = OP_I16; break;
			case 4: op_type = OP_I32; break;
			default:
				DebugMsg1(("idata_nofixup: invalid size %d for immediate operand\n", size ));
				return( EmitError( INVALID_INSTRUCTION_OPERANDS ) );
        }
    } 
	else 
	{
        /* use true signed values for BYTE only! */
        if ( (int_8)value == value )
            op_type = OP_I8;
        else if( value <= USHRT_MAX && value >= 0L - USHRT_MAX )
            op_type = OP_I16;
        else 
            op_type = OP_I32;
    }

    switch ( CodeInfo->token ) 
	{
    case T_PUSH:
        if ( opndx->explicit == FALSE ) {
            if ( CodeInfo->Ofssize > USE16 && op_type == OP_I16 )
                op_type = OP_I32;
        }
        if ( op_type == OP_I16 )
            CodeInfo->prefix.opsiz = OPSIZE16( CodeInfo );
        else if ( op_type == OP_I32 )
            CodeInfo->prefix.opsiz = OPSIZE32( CodeInfo );
        break;
    case T_PUSHW:
        if ( op_type != OP_I32 ) {
            op_type = OP_I16;
            if( (int_8)value == (int_16)value ) {
                op_type = OP_I8;
            }
        }
        break;
    case T_PUSHD:
        if ( op_type == OP_I16 )
            op_type = OP_I32;
        break;
    }

    /* v2.11: set the wide-bit if a mem_type size of > BYTE is set???
     * actually, it should only be set if immediate is second operand
     * ( and first operand is a memory ref with a size > 1 ) */
    if (CurrOpnd == OPND2)
	{
        if ( CodeInfo->mem_type == MT_ZMMWORD ) 
			CodeInfo->iswide = 1;
        else 
          if ( !(CodeInfo->mem_type & MT_SPECIAL) && ( CodeInfo->mem_type & MT_SIZE_MASK ) )
            CodeInfo->iswide = 1;
    }
    CodeInfo->opnd[CurrOpnd].type = op_type;
    return( NOT_ERROR );
}

/* get an immediate operand with a fixup.
 * output:
 * - ERROR: error
 * - NOT_ERROR: ok,
 *   CodeInfo->opnd_type[CurrOpnd] = OP_Ix
 *   CodeInfo->data[CurrOpnd]      = value
 *   CodeInfo->InsFixup[CurrOpnd]  = fixup
 *   CodeInfo->mem_type
 *   CodeInfo->prefix.opsiz
 * to be fixed: don't modify CodeInfo->mem_type here! */
ret_code idata_fixup( struct code_info *CodeInfo, unsigned CurrOpnd, struct expr *opndx )
/***************************************************************************************/
{
    //struct fixup      *fixup;
    enum fixup_types    fixup_type;
    enum fixup_options  fixup_option = OPTJ_NONE;
    int                 size;
    uint_8              Ofssize; /* 1=32bit, 0=16bit offset for fixup */

    DebugMsg1(("idata_fixup( CurrOpnd=%u ) enter [opndx.kind=%u mem_type=%Xh, CodeInfo.mem_type=%Xh]\n", CurrOpnd, opndx->kind, opndx->mem_type, CodeInfo->mem_type));

    /* jmp/call/jcc/loopcc/jxcxz? */
    if( IS_ANY_BRANCH( CodeInfo->token ) ) {
        return( process_branch( CodeInfo, CurrOpnd, opndx ) );
    }
    CodeInfo->opnd[CurrOpnd].data32l = opndx->value;

    if ( opndx->Ofssize != USE_EMPTY ) {
        Ofssize = opndx->Ofssize;
    } else if( ( opndx->sym->state == SYM_SEG )
        || ( opndx->sym->state == SYM_GRP )
        || ( opndx->instr == T_SEG ) ) {
        Ofssize = USE16;
    } else if( opndx->is_abs ) {  /* an (external) absolute symbol? */
        Ofssize = USE16;
    } else {
        Ofssize = GetSymOfssize( opndx->sym );
    }

    if( opndx->instr == T_SHORT ) {
        /* short works for branch instructions only */
        return( EmitErr( INVALID_INSTRUCTION_OPERANDS ) );
    }

    /* the code below should be rewritten.
     * - an address operator ( OFFSET, LROFFSET, IMAGEREL, SECTIONREL,
     *   LOW, HIGH, LOWWORD, HIGHWORD, LOW32, HIGH32, SEG ) should not
     *   force a magnitude, but may set a minimal magnitude - and the
     *   fixup type, of course.
     * - check if Codeinfo->mem_type really has to be set here!
     */

    /* v2.06: added */
    /* v2.10: modified */
    //if ( opndx->explicit ) {
    if ( opndx->explicit && !opndx->is_abs ) {
        CodeInfo->const_size_fixed = TRUE;
        if ( CodeInfo->mem_type == MT_EMPTY )
            CodeInfo->mem_type = opndx->mem_type;
    }
    /* v2.03: don't ignore a "NEAR32 ptr" qualifier */
    //if ( CodeInfo->mem_type == MT_EMPTY && CurrOpnd > OPND1 ) {
    if ( CodeInfo->mem_type == MT_EMPTY && CurrOpnd > OPND1 && opndx->Ofssize == USE_EMPTY ) {
        size = OperandSize( CodeInfo->opnd[OPND1].type, CodeInfo );
        /* may be a forward reference, so wait till pass 2 */
        if( Parse_Pass > PASS_1 && opndx->instr != EMPTY ) {
            switch ( opndx->instr ) {
            case T_SEG: /* v2.04a: added */
                if( size && (size < 2 ) ) {
                    return( EmitErr( OPERANDS_MUST_BE_THE_SAME_SIZE, size, 2 ) );
                }
                break;
            case T_OFFSET:
            case T_LROFFSET:
#if IMAGERELSUPP
            case T_IMAGEREL:
#endif
#if SECTIONRELSUPP
            case T_SECTIONREL:
#endif
                if( size && (size < 2 || ( Ofssize && size < 4 ))) {
                    return( EmitErr( OPERANDS_MUST_BE_THE_SAME_SIZE, size, ( 2 << Ofssize ) ) );
                }
            }
        }
        switch ( size ) {
        case 1:
            /* v2.05: if () added */
            if ( opndx->is_abs || opndx->instr == T_LOW || opndx->instr == T_HIGH )
                CodeInfo->mem_type = MT_BYTE;
            break;
        case 2:
            /* v2.05: if () added */
            if ( opndx->is_abs ||
                CodeInfo->Ofssize == USE16 ||
                opndx->instr == T_LOWWORD ||
                opndx->instr == T_HIGHWORD )
                CodeInfo->mem_type = MT_WORD;
            break;
        case 4:
            CodeInfo->mem_type = MT_DWORD;
            break;
#if AMD64_SUPPORT
        case 8:
            /* v2.05: it's questionable if size 8 is a good assumption for an
             * immediate constant. It's valid for MOV <reg>, <imm> only.
             */
            //case 8: CodeInfo->mem_type = MT_QWORD;break;
            /* v2.05a: added */
            if ( Ofssize == USE64 ) {
                if ( CodeInfo->token == T_MOV &&
                    ( CodeInfo->opnd[OPND1].type & OP_R64 ) )
                    CodeInfo->mem_type = MT_QWORD;
                else if ( opndx->instr == T_LOW32 || opndx->instr == T_HIGH32 )
                    /* v2.10:added; LOW32/HIGH32 in expreval.c won't set mem_type anymore. */
                    CodeInfo->mem_type = MT_DWORD;
            }
            break;
#endif
        }
    }
    if ( CodeInfo->mem_type == MT_EMPTY ) {
        if( opndx->is_abs ) {
            //if( opndx->mem_type != MT_EMPTY && opndx->mem_type != MT_ABS ) {
            if( opndx->mem_type != MT_EMPTY ) {
                CodeInfo->mem_type = opndx->mem_type;
            } else if ( CodeInfo->token == T_PUSHW ) { /* v2.10: special handling PUSHW */
                CodeInfo->mem_type = MT_WORD;
            } else {
                CodeInfo->mem_type = ( IS_OPER_32( CodeInfo ) ? MT_DWORD : MT_WORD );
            }
        } else {
            switch ( CodeInfo->token ) {
            case T_PUSHW:
            case T_PUSHD:
            case T_PUSH:
                /* for forward reference, assume BYTE */
                /* v2.02: don't assume BYTE if it is SEG/GRP */
                //if ( opndx->mem_type == MT_EMPTY ) {
                /* v2.07: added cases IMAGEREL and SECTIONREL */
                if ( opndx->mem_type == MT_EMPTY  ) {
                    switch( opndx->instr ) {
                    case EMPTY:
                    case T_LOW:
                    case T_HIGH:
                        opndx->mem_type = MT_BYTE;
                        break;
                    case T_LOW32: /* v2.10: added - low32_op() doesn't set mem_type anymore. */
#if IMAGERELSUPP
                    case T_IMAGEREL:
#endif
#if SECTIONRELSUPP
                    case T_SECTIONREL:
#endif
                        opndx->mem_type = MT_DWORD;
                        break;
                    };
                }
                /* default: push offset only */
                /* for PUSH + undefined symbol, assume BYTE */
                if ( opndx->mem_type == MT_FAR && ( opndx->explicit == FALSE ) )
                    opndx->mem_type = MT_NEAR;
                /* v2.04: curly brackets added */
                if ( CodeInfo->token == T_PUSHW ) {
                    if ( SizeFromMemtype( opndx->mem_type, Ofssize, opndx->type ) < 2 )
                        opndx->mem_type = MT_WORD;
                } else if ( CodeInfo->token == T_PUSHD ) {
                    if ( SizeFromMemtype( opndx->mem_type, Ofssize, opndx->type ) < 4 )
                        opndx->mem_type = MT_DWORD;
                }
                break;
            }
            /* if a WORD size is given, don't override it with */
            /* anything what might look better at first glance */
            if( opndx->mem_type != MT_EMPTY )
                CodeInfo->mem_type = opndx->mem_type;
            /* v2.04: assume BYTE size if symbol is undefined */
            else if ( opndx->sym->state == SYM_UNDEFINED ) {
                CodeInfo->mem_type = MT_BYTE;
                fixup_option = OPTJ_PUSH;
            } else
#if AMD64_SUPPORT
                /* v2.06d: changed */
                   CodeInfo->mem_type = ( Ofssize == USE64 ? MT_QWORD : Ofssize == USE32 ? MT_DWORD : MT_WORD );
#else
                CodeInfo->mem_type = ( Ofssize > USE16 ? MT_DWORD : MT_WORD );
#endif
        }
    }
    size = SizeFromMemtype( CodeInfo->mem_type, Ofssize, NULL );
    switch( size ) {
    case 1:
        CodeInfo->opnd[CurrOpnd].type = OP_I8;
        CodeInfo->prefix.opsiz = FALSE; /* v2.10: reset opsize is not really a good idea - might have been set by previous operand */
        break;
    case 2:  CodeInfo->opnd[CurrOpnd].type = OP_I16; CodeInfo->prefix.opsiz = OPSIZE16( CodeInfo );  break;
    case 4:  CodeInfo->opnd[CurrOpnd].type = OP_I32; CodeInfo->prefix.opsiz = OPSIZE32( CodeInfo );  break;
#if AMD64_SUPPORT
    case 8:
        /* v2.05: do only assume size 8 if the constant won't fit in 4 bytes. */
        if ( opndx->value64 > H_LONG_MAX || opndx->value64 < H_LONG_MIN ||
            (opndx->explicit && ( opndx->mem_type & MT_SIZE_MASK ) == 7 ) ) {
            CodeInfo->opnd[CurrOpnd].type = OP_I64;
            CodeInfo->opnd[CurrOpnd].data32h = opndx->hvalue;
        //} else if ( Ofssize == USE64 ) { /* v2.11: assume 64-bit only for OFFSET or MOV r64, xxx */
        } else if ( Ofssize == USE64 && ( opndx->instr == T_OFFSET || ( CodeInfo->token == T_MOV && ( CodeInfo->opnd[OPND1].type & OP_R64 ) ) ) ) {
            /* v2.06d: in 64-bit, ALWAYS set OP_I64, so "mov m64, ofs" will fail,
             * This was accepted in v2.05-v2.06c)
             */
            CodeInfo->opnd[CurrOpnd].type = OP_I64;
            CodeInfo->opnd[CurrOpnd].data32h = opndx->hvalue;
        } else {
            CodeInfo->opnd[CurrOpnd].type = OP_I32;
        }
        CodeInfo->prefix.opsiz = OPSIZE32( CodeInfo );
        break;
#endif
#ifdef DEBUG_OUT
    default:
        DebugMsg1(("idata_fixup, unexpected size %u\n", size ));
        /**/myassert( 0 );
#endif
    }

    /* set fixup_type */

    if( opndx->instr == T_SEG ) {
        fixup_type = FIX_SEG;
    } else if( CodeInfo->mem_type == MT_BYTE ) {
        DebugMsg1(("idata_fixup, mem_type=BYTE\n" ));
        if ( opndx->instr == T_HIGH ) {
            DebugMsg1(("idata_fixup, FIX_HIBYTE\n" ));
            fixup_type = FIX_HIBYTE;
        } else {
            DebugMsg1(("idata_fixup, FIX_OFF8\n" ));
            fixup_type = FIX_OFF8;
        }
#if 0
    } else if( CodeInfo->mem_type == MT_FAR ) {
        /* v2.04: to be tested. this code is most likely obsolete.
         * There's never a PTR16|PTR32 fixup here. Far JMP/CALL are handled
         * elsewhere, and data items also.
         */
        /* temporary */
        printf("idata_fixup: MT_FAR occured at %s:%" I32_SPEC "u\n", CurrFName[ASM], LineNumber );
        fixup_type = ( Ofssize ) ? FIX_PTR32 : FIX_PTR16;
        CodeInfo->isfar = TRUE; /* needed for mark_fixupp() */
        if ( opndx->Ofssize != USE_EMPTY )
            CodeInfo->Ofssize = opndx->Ofssize;
#endif
    } else if( IS_OPER_32( CodeInfo ) ) {
#if AMD64_SUPPORT
        /* v2.06: changed */
        //if ( Ofssize == USE64 && CodeInfo->mem_type == MT_QWORD )
        /* v2.10: changed */
        //if ( CodeInfo->opnd[CurrOpnd].type == OP_I64 )
        if ( CodeInfo->opnd[CurrOpnd].type == OP_I64 && ( opndx->instr == EMPTY || opndx->instr == T_OFFSET ) )
            fixup_type = FIX_OFF64;
        else
#endif
            /* v2.04: changed, no longer depends on OfsSize */
            /* v2.05a: changed, so size==8 won't get a FIX_OFF16 type */
            //if ( size == 4 )
            if ( size >= 4 && opndx->instr != T_LOWWORD ) {
                /* v2.06: added branch for PTR16 fixup.
                 * it's only done if type coercion is FAR (Masm-compat)
                 */
                if ( opndx->explicit && Ofssize == USE16 && opndx->mem_type == MT_FAR )
                    fixup_type = FIX_PTR16;
                else
                    fixup_type = FIX_OFF32;
            } else
                fixup_type = FIX_OFF16;
    } else {
        /* v2.04: changed, no longer depends on OfsSize */
        //if ( CodeInfo->mem_type == MT_DWORD ) {
            /* fixme !!!! warning
             * operand size is 16bit
             * but fixup is 32-bit */
        //    fixup_type = FIX_OFF32;
        //} else
            fixup_type = FIX_OFF16;
    }
    /* v2.04: 'if' added, don't set W bit if size == 1
     * code example:
     *   extern x:byte
     *   or al,x
     * v2.11: set wide bit only if immediate is second operand.
     * and first operand is a memory reference with size > 1
     */
    //if ( size != 1 )
    if ( CurrOpnd == OPND2 && size != 1 )
        CodeInfo->iswide = 1;

    segm_override( opndx, NULL ); /* set SegOverride global var */

    /* set frame type in variables Frame_Type and Frame_Datum for fixup creation */
    if ( ModuleInfo.offsettype == OT_SEGMENT &&
        ( opndx->instr == T_OFFSET || opndx->instr == T_SEG ))
        set_frame2( opndx->sym );
    else
        set_frame( opndx->sym );

    //DebugMsg1(("idata_fixup: calling CreateFixup(%s, %u)\n", opndx->sym->name, fixup_type ));
    CodeInfo->opnd[CurrOpnd].InsFixup = CreateFixup( opndx->sym, fixup_type, fixup_option );

    if ( opndx->instr == T_LROFFSET )
        CodeInfo->opnd[CurrOpnd].InsFixup->loader_resolved = TRUE;

#if IMAGERELSUPP
    if ( opndx->instr == T_IMAGEREL && fixup_type == FIX_OFF32 )
        CodeInfo->opnd[CurrOpnd].InsFixup->type = FIX_OFF32_IMGREL;
#endif
#if SECTIONRELSUPP
    if ( opndx->instr == T_SECTIONREL && fixup_type == FIX_OFF32 )
        CodeInfo->opnd[CurrOpnd].InsFixup->type = FIX_OFF32_SECREL;
#endif
    DebugMsg1(("idata_fixup exit [CodeInfo.mem_type=%Xh Ofssize=%u opsiz=%u fixup.type=%u fixup.frame=%d]\n",
               CodeInfo->mem_type, CodeInfo->Ofssize, CodeInfo->prefix.opsiz,
               CodeInfo->opnd[CurrOpnd].InsFixup->type, CodeInfo->opnd[CurrOpnd].InsFixup->frame_type ));

    return( NOT_ERROR );
}

/* convert MT_PTR to MT_WORD, MT_DWORD, MT_FWORD, MT_QWORD.
 * MT_PTR cannot be set explicitely (by the PTR operator),
 * so this value must come from a label or a structure field.
 * (above comment is most likely plain wrong, see 'PF16 ptr [reg]'!
 * This code needs cleanup! */
static void SetPtrMemtype( struct code_info *CodeInfo, struct expr *opndx )
/*************************************************************************/
{
    struct asym *sym = opndx->sym;
    int size = 0;

    if ( opndx->mbr )  /* the mbr field has higher priority */
        sym = opndx->mbr;

    /* v2.10: the "explicit" condition is now handled FIRST */
#if 1 /* v2.0: handle PF16 ptr [ebx], which didn't work in v1.96 */
    if ( opndx->explicit && opndx->type ) {
        size = opndx->type->total_size;
        CodeInfo->isfar = opndx->type->isfar;
    } else
#endif
    if ( sym ) {
        if ( sym->type ) {
            size = sym->type->total_size;
            CodeInfo->isfar = sym->type->isfar;

            /* there's an ambiguity with pointers of size DWORD,
             since they can be either NEAR32 or FAR16 */
            if ( size == 4 && sym->type->Ofssize != CodeInfo->Ofssize )
                opndx->Ofssize = sym->type->Ofssize;

        } else if ( sym->mem_type == MT_PTR ) {
            size = SizeFromMemtype( sym->isfar ? MT_FAR : MT_NEAR, sym->Ofssize, NULL );
            CodeInfo->isfar = sym->isfar;
        } else  {
            if ( sym->isarray )
                size = sym->total_size / sym->total_length;
            else
                size = sym->total_size;
        }
    } else {
        if ( SIZE_DATAPTR & ( 1 << ModuleInfo.model ) ) {
            DebugMsg1(("SetPtrMemtype: model with FAR data pointers\n" ));
            size = 2;
        }
        size += (2 << ModuleInfo.defOfssize );
    }
    if ( size )
        MemtypeFromSize( size, &opndx->mem_type );
    DebugMsg1(("SetPtrMemtype: size=%u, new memtype=0x%x\n", size, opndx->mem_type ));
}

/*
 * set fields in CodeInfo:
 * - mem_type
 * - prefix.opsiz
 * - prefix.rex REX_W
 * called by memory_operand() */
static void Set_Memtype( struct code_info *CodeInfo, enum memtype mem_type )
/**************************************************************************/
{
    if( CodeInfo->token == T_LEA )
        return;
    /* v2.05: changed. Set "data" types only. */
    if( mem_type == MT_EMPTY || mem_type == MT_TYPE ||
       mem_type == MT_NEAR || mem_type == MT_FAR )
        return;

    CodeInfo->mem_type = mem_type;

    if( CodeInfo->Ofssize > USE16 ) {
        /* if we are in use32 mode, we have to add OPSIZ prefix for
         * most of the 386 instructions when operand has type WORD.
         * Exceptions ( MOVSX and MOVZX ) are handled in check_size().
         */
        if ( IS_MEM_TYPE( mem_type, WORD ) )
            CodeInfo->prefix.opsiz = TRUE;
#if AMD64_SUPPORT
        /*
         * set rex Wide bit if a QWORD operand is found (not for FPU/MMX/SSE instr).
         * This looks pretty hackish now and is to be cleaned!
         * v2.01: also had issues with SSE2 MOVSD/CMPSD, now fixed!
         */
        /* v2.06: with AVX, SSE tokens may exist twice, one
         * for "legacy", the other for VEX encoding!
         */
        else if ( IS_MEMTYPE_SIZ( mem_type, sizeof( uint_64 ) ) ) {
            switch( CodeInfo->token ) {
            case T_PUSH: /* for PUSH/POP, REX_W isn't needed (no 32-bit variants in 64-bit mode) */
            case T_POP:
            case T_CMPXCHG8B:
#if VMXSUPP
            case T_VMPTRLD:
            case T_VMPTRST:
            case T_VMCLEAR:
            case T_VMXON:
#endif
                break;
            default:
                /* don't set REX for opcodes that accept memory operands
                 * of any size.
                 */
                if ( opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type[OPND1] == OP_M_ANY ) {
                    //printf( "Set_Memtype: OP_M_ANY detected, file=%s, instr=%s\n", CurrFName[ASM], GetResWName( CodeInfo->token, NULL ) );
                    break;
                }
                /* don't set REX for FPU opcodes */
                if ( CodeInfo->pinstr->cpu & P_FPU_MASK )
                    break;
                /* don't set REX for - most - MMX/SSE opcodes */
                if ( CodeInfo->pinstr->cpu & P_EXT_MASK ) {
                    switch ( CodeInfo->token ) {
                        /* [V]CMPSD and [V]MOVSD are also candidates,
                         * but currently they are handled in HandleStringInstructions()
                         */
                    case T_CVTSI2SD: /* v2.06: added */
                    case T_CVTSI2SS: /* v2.06: added */
                    case T_PEXTRQ: /* v2.06: added */
                    case T_PINSRQ: /* v2.06: added */
                    case T_MOVD:
#if AVXSUPP
                    case T_VCVTSI2SD:
                    case T_VCVTSI2SS:
                    case T_VPEXTRQ:
                    case T_VPINSRQ:
                    case T_VMOVD:
#endif
                        CodeInfo->prefix.rex |= REX_W;
                        break;
                    default:
                        break;
                    }
                }
                else
                    CodeInfo->prefix.rex |= REX_W;
            }
        }
#endif

    /* v2.05: IS_MEM_TYPE() doesn't work with MT_REALx */
    //} else if( CodeInfo->Ofssize == USE16 && ( IS_MEM_TYPE( mem_type, DWORD ) ) ) {
    } else {
        if( IS_MEMTYPE_SIZ( mem_type, sizeof(uint_32) ) ) {

            /* in 16bit mode, a DWORD memory access usually requires an OPSIZ
             * prefix. A few instructions, which access m16:16 operands,
             * are exceptions.
             */
            switch( CodeInfo->token ) {
            case T_LDS:
            case T_LES:
            case T_LFS:
            case T_LGS:
            case T_LSS:
            case T_CALL: /* v2.0: added */
            case T_JMP:  /* v2.0: added */
                /* in these cases, opsize does NOT need to be changed  */
                break;
            default:
                CodeInfo->prefix.opsiz = TRUE;
                break;
            }
        }
#if AMD64_SUPPORT
        /* v2.06: added because in v2.05, 64-bit memory operands were
         * accepted in 16-bit code
         */
        else if ( IS_MEMTYPE_SIZ( mem_type, sizeof(uint_64) ) ) {
            if ( opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type[OPND1] == OP_M_ANY ) {
                //printf( "Set_Memtype: OP_M_ANY detected, file=%s, instr=%s\n", CurrFName[ASM], GetResWName( CodeInfo->token, NULL ) );
            } else if ( CodeInfo->pinstr->cpu & ( P_FPU_MASK | P_EXT_MASK ) ) {
                ;
            } else if ( CodeInfo->token != T_CMPXCHG8B )
                /* setting REX.W will cause an error in codegen */
                CodeInfo->prefix.rex |= REX_W;
        }
#endif
    }
    return;
}

/*
 * process direct or indirect memory operand
 * in: opndx=operand to process
 * in: CurrOpnd=no of operand (0=first operand, 1=second operand)
 * out: CodeInfo->data[]
 * out: CodeInfo->opnd_type[] */
static ret_code memory_operand( struct code_info *CodeInfo, unsigned CurrOpnd, struct expr *opndx, bool with_fixup )
/******************************************************************************************************************/
{
    char                ss = SCALE_FACTOR_1;
    int                 index;
    int                 base;
    int                 temp;
    bool                swapped = FALSE;
    int                 j;
    struct asym         *sym;
    uint_8              Ofssize;
    enum fixup_types    fixup_type;

    /* v211: use full 64-bit value */
    CodeInfo->opnd[CurrOpnd].data64 = opndx->value64;
    CodeInfo->opnd[CurrOpnd].type = OP_M;

    sym = opndx->sym;

    segm_override( opndx, CodeInfo );

    /* change pointer types ( MT_NEAR, MT_FAR, MT_PTR */
    /* v2.04a: should not be called if OFFSET was used */
    if ( opndx->mem_type == MT_PTR )
        SetPtrMemtype( CodeInfo, opndx );
    else if ( ( opndx->mem_type & MT_SPECIAL_MASK ) == MT_ADDRESS ) 
	{
        int size;
        if ( opndx->Ofssize == USE_EMPTY && sym )
            opndx->Ofssize = GetSymOfssize( sym );

		size = SizeFromMemtype( opndx->mem_type, opndx->Ofssize, opndx->type );
        MemtypeFromSize( size, &opndx->mem_type );
    }

    Set_Memtype( CodeInfo, opndx->mem_type );
    if( opndx->mbr != NULL ) 
	{
        /* if the struct field is just another struct, use it's total size
         * to set CodeInfo->mem_type. */
        if ( opndx->mbr->mem_type == MT_TYPE && opndx->mem_type == MT_EMPTY ) 
		{
            enum memtype mem_type;
            if (CodeInfo->token == T_VMOVSS)
			{
			  // MemtypeFromSize returns OP_M128
              mem_type = MT_DWORD;                  //but we need MT_DWORD
              Set_Memtype(CodeInfo, mem_type);
			}
			else
			{
				if (MemtypeFromSize(opndx->mbr->total_size, &mem_type) == NOT_ERROR)
					Set_Memtype(CodeInfo, mem_type);
			}
        }

		if ( opndx->mbr->state == SYM_UNDEFINED )
            CodeInfo->undef_sym = TRUE;
    }

    /* instruction-specific handling */
    switch ( CodeInfo->token ) 
	{
    case T_JMP:
    case T_CALL:
        /* the 2 branch instructions are peculiar because they
         * will work with an unsized label.
         */
        /* v1.95: convert MT_NEAR/MT_FAR and display error if no type.
         * For memory operands, expressions of type MT_NEAR/MT_FAR are
         * call [bx+<code_label>]
         */
        if ( CodeInfo->mem_type == MT_EMPTY ) 
		{
            /* with -Zm, no size needed for indirect CALL/JMP */
            if ( ModuleInfo.m510 == FALSE &&
                ( Parse_Pass > PASS_1 && opndx->sym == NULL ) ) 
			{
                return( EmitError( INSTRUCTION_OPERAND_MUST_HAVE_SIZE ) );
            }

            opndx->mem_type = (CodeInfo->Ofssize == USE64) ? MT_QWORD : (CodeInfo->Ofssize == USE32) ? MT_DWORD : MT_WORD;
            Set_Memtype( CodeInfo, opndx->mem_type );
        }
        j = SizeFromMemtype( CodeInfo->mem_type, CodeInfo->Ofssize, NULL );
        if ( ( j == 1 || j > 6 ) && ( CodeInfo->Ofssize != USE64 )) 
		{
            /* CALL/JMP possible for WORD/DWORD/FWORD memory operands only */
            return( EmitError( INVALID_OPERAND_SIZE ) );
        }

        if( opndx->mem_type == MT_FAR || CodeInfo->mem_type == MT_FWORD ||
           ( CodeInfo->mem_type == MT_TBYTE && CodeInfo->Ofssize == USE64 ) ||
            ( CodeInfo->mem_type == MT_DWORD &&
              (( CodeInfo->Ofssize == USE16 && opndx->Ofssize != USE32 ) ||
               ( CodeInfo->Ofssize == USE32 && opndx->Ofssize == USE16 )))) 
		{
            CodeInfo->isfar = TRUE;
        }
        break;
    }

    if ( ( CodeInfo->mem_type & MT_SPECIAL) == 0 ) 
	{

        if ((CodeInfo->mem_type & 0x3f) == MT_YMMWORD)
          CodeInfo->opnd[CurrOpnd].type = OP_M256;
        else if ((CodeInfo->mem_type & 0x3f) == MT_ZMMWORD)
          CodeInfo->opnd[CurrOpnd].type = OP_M512;
        else 
		{

          switch (CodeInfo->mem_type & MT_SIZE_MASK) 
		  {
            /* size is encoded 0-based */
            case  MT_BYTE:    CodeInfo->opnd[CurrOpnd].type = OP_M08;  break;
            case  MT_WORD:    CodeInfo->opnd[CurrOpnd].type = OP_M16;  break;
            case  MT_DWORD:   CodeInfo->opnd[CurrOpnd].type = OP_M32;  break;
            case  MT_FWORD:   CodeInfo->opnd[CurrOpnd].type = OP_M48;  break;
            case  MT_QWORD:   CodeInfo->opnd[CurrOpnd].type = OP_M64;  break;
            case  MT_TBYTE:   CodeInfo->opnd[CurrOpnd].type = OP_M80;  break;
            case  MT_OWORD:   CodeInfo->opnd[CurrOpnd].type = OP_M128; break;
          }

        }
    } 
	else if ( CodeInfo->mem_type == MT_EMPTY ) 
	{
        /* v2.05: added */
        switch ( CodeInfo->token ) 
		{
        case T_INC:
        case T_DEC:
            /* Uasm v1.94-v2.04 accepted unsized operand for INC/DEC */
            if ( opndx->sym == NULL ) 
                return( EmitError( INSTRUCTION_OPERAND_MUST_HAVE_SIZE ) );
            break;
        case T_PUSH:
        case T_POP:
            if ( opndx->mem_type == MT_TYPE )
                return( EmitError( INVALID_INSTRUCTION_OPERANDS ) );
            break;
        }
    }
    base = ( opndx->base_reg ? opndx->base_reg->tokval : EMPTY );
    index = ( opndx->idx_reg ? opndx->idx_reg->tokval : EMPTY );

    /* swap registers if base is AVX register, v2.38 */
    if (GetValueSp(base) == OP_XMM || GetValueSp(base) == OP_YMM || GetValueSp(base) == OP_ZMM)
	{
      temp    = base;
      base    = index;
      index   = temp;
      swapped = TRUE; /* this flag is on only for AVX regisres v2.38 */
    }
     
	if (index != EMPTY) CodeInfo->indexreg = GetRegNo(index);
    if (base != EMPTY)  CodeInfo->basereg = GetRegNo(base);
    
	/* use base + index from here - don't use opndx-> base_reg/idx_reg! */
    if (index != EMPTY && base == EMPTY && swapped)
	{
		base = 0x87;     /* VEX index with omitted base EG: [+ymm1] */
        CodeInfo->basereg = GetRegNo(base);
        CodeInfo->indexreg = GetRegNo(index);
    }
    
    /* UASM 2.53 check for use of register assumed to ERROR in an EA */
    if (base != EMPTY && StdAssumeTable[GetRegNo(base)].error)
    {
        return(EmitError(USE_OF_REGISTER_ASSUMED_TO_ERROR));
    }
    if (index != EMPTY && GetValueSp(index) & OP_XMM == 0 && GetValueSp(index) & OP_YMM == 0 && StdAssumeTable[GetRegNo(index)].error)
    {
        return(EmitError(USE_OF_REGISTER_ASSUMED_TO_ERROR));
    }

    /* check for base registers */
    if ( base != EMPTY ) 
	{
        if ( ( ( GetValueSp( base ) & OP_R32) && CodeInfo->Ofssize == USE32 ) ||
            ( ( GetValueSp( base ) & OP_R64) && CodeInfo->Ofssize == USE64 ) ||
            ( ( GetValueSp( base ) & OP_R16) && CodeInfo->Ofssize == USE16 ) )
            CodeInfo->prefix.adrsiz = FALSE;
        else 
		{
            CodeInfo->prefix.adrsiz = TRUE;
            /* 16bit addressing modes don't exist in long mode */
            if ( ( GetValueSp( base ) & OP_R16) && CodeInfo->Ofssize == USE64 )
                return( EmitError( INVALID_ADDRESSING_MODE_WITH_CURRENT_CPU_SETTING ) );
        }
    }

    /* check for index registers */
    if( index != EMPTY ) 
	{
        if ( ( ( GetValueSp( index ) & OP_R32) && CodeInfo->Ofssize == USE32 ) ||
            ( ( GetValueSp( index ) & OP_R64) && CodeInfo->Ofssize == USE64 ) ||
            ( ( GetValueSp( index ) & OP_R16) && CodeInfo->Ofssize == USE16 ) || 
			( ( GetValueSp( index ) & OP_XMM) && CodeInfo->Ofssize == USE32 ) || // UASM 2.48 missing support base+xmm/ymm vsib addressing.
			( ( GetValueSp( index ) & OP_YMM) && CodeInfo->Ofssize == USE32 )
			) 
		{
            CodeInfo->prefix.adrsiz = FALSE;
        } 
		else 
		{
            CodeInfo->prefix.adrsiz = TRUE;
        }

        /* v2.10: register swapping has been moved to expreval.c, index_connect().
         * what has remained here is the check if R/ESP is used as index reg. */
		if ((GetRegNo(index) == 4)&& GetValueSp( index ) < OP_XMM ) 
		{ 
            if( opndx->scale ) 
			{
				/* no scale must be set */
                EmitErr( CANNOT_BE_USED_AS_INDEX_REGISTER, GetResWName( index, NULL ) );
            } 
			else 
			{
                EmitErr( MULTIPLE_BASE_REGISTERS_NOT_ALLOWED );
            }
            return( ERROR );
        }

        /* 32/64 bit indirect addressing? */
        if( ( CodeInfo->Ofssize == USE16 && CodeInfo->prefix.adrsiz == 1 ) || CodeInfo->Ofssize == USE64  ||
			(CodeInfo->Ofssize == USE32 && (CodeInfo->prefix.adrsiz == 0) || (CodeInfo->evex_flag == 1))) 
		{
            if( ( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_386 ) 
			{
                /* scale, 0 or 1->00, 2->40, 4->80, 8->C0 */
                switch( opndx->scale ) 
				{
                case 0:
                case 1:  break; /* ss = 00 */
                case 2: ss = SCALE_FACTOR_2; break; /* ss = 01 */
                case 4: ss = SCALE_FACTOR_4; break; /* ss = 10 */
                case 8: ss = SCALE_FACTOR_8; break; /* ss = 11 */
                default: /* must be * 1, 2, 4 or 8 */
                    return( EmitError( SCALE_FACTOR_MUST_BE_1_2_4_OR_8 ) );
                }
            } 
			else 
			{
                /* 286 and down cannot use this memory mode */
                return( EmitError( INVALID_ADDRESSING_MODE_WITH_CURRENT_CPU_SETTING ) );
            }
        } 
		else 
		{
            /* v2.01: 16-bit addressing mode. No scale possible */
            if ( opndx->scale )
                return( EmitError( INVALID_USE_OF_REGISTER ) );
        }
    }

    if( with_fixup ) 
	{

        if( opndx->is_abs ) 
		{
            Ofssize = IS_ADDR32( CodeInfo );
        } 
		else if ( sym ) 
		{
            Ofssize = GetSymOfssize( sym );
        } 
		else if ( SegOverride ) 
		{
            Ofssize = GetSymOfssize( SegOverride );
        } 
		else
            Ofssize = CodeInfo->Ofssize;

        /* now set fixup_type.
         * for direct addressing, the fixup type can easily be set by
         * the symbol's offset size. */
        if( base == EMPTY && index == EMPTY ) 
		{
            CodeInfo->prefix.adrsiz = ADDRSIZE( CodeInfo->Ofssize, Ofssize );
            if ( Ofssize == USE64 )
                /* v2.03: override with a segment assumed != FLAT? */
                if ( opndx->override != NULL && SegOverride != &ModuleInfo.flat_grp->sym )
                    fixup_type = FIX_OFF32;
                else
                    fixup_type = FIX_RELOFF32;
            else
                fixup_type = ( Ofssize ) ? FIX_OFF32 : FIX_OFF16;
        } 
		else 
		{
            if( Ofssize == USE64 ) 
			{
                fixup_type = FIX_OFF32;
            } 
			else if( IS_ADDR32( CodeInfo ) ) 
			{ 
				/* address prefix needed? */
                /* changed for v1.95. Probably more tests needed!
                 * test case:
                 *   mov eax,[ebx*2-10+offset var] ;code and var are 16bit!
                 * the old code usually works fine because HiWord of the
                 * symbol's offset is zero. However, if there's an additional
                 * displacement which makes the value stored at the location
                 * < 0, then the target's HiWord becomes <> 0.
                 */
                //fixup_type = ( Ofssize ) ? FIX_OFF32 : FIX_OFF16;
                fixup_type = FIX_OFF32;
            } 
			else 
			{
                fixup_type = FIX_OFF16;
                if( Ofssize && Parse_Pass == PASS_2 ) 
				{
                    /* address size is 16bit but label is 32-bit.
                     * example: use a 16bit register as base in FLAT model:
                     *   test buff[di],cl */
                    EmitWarn( 2, WORD_FIXUP_FOR_32BIT_LABEL, sym->name );
                }
            }
        }
		
		/* v2.10: added; IMAGEREL/SECTIONREL for indirect memory operands */
		#if IMAGERELSUPP || SECTIONRELSUPP 
        if ( fixup_type == FIX_OFF32 )
            if ( opndx->instr == T_IMAGEREL )
                fixup_type = FIX_OFF32_IMGREL;
            else if ( opndx->instr == T_SECTIONREL )
                fixup_type = FIX_OFF32_SECREL;
		#endif

        /* no fixups are needed for memory operands of string instructions and XLAT/XLATB.
         * However, CMPSD and MOVSD are also SSE2 opcodes, so the fixups must be generated
         * anyways.
         */
        if (CodeInfo->token != T_XLAT && CodeInfo->token != T_XLATB) {
            CodeInfo->opnd[CurrOpnd].InsFixup = CreateFixup(sym, fixup_type, OPTJ_NONE);
        }
    }

    if( set_rm_sib( CodeInfo, CurrOpnd, ss, index, base, sym ) == ERROR ) 
        return( ERROR );
    
    /* set frame type/data in fixup if one was created */
    if ( CodeInfo->opnd[CurrOpnd].InsFixup ) 
	{
        CodeInfo->opnd[CurrOpnd].InsFixup->frame_type = Frame_Type;
        CodeInfo->opnd[CurrOpnd].InsFixup->frame_datum = Frame_Datum;
    }

    return( NOT_ERROR );
}

static ret_code process_address( struct code_info *CodeInfo, unsigned CurrOpnd, struct expr *opndx )
/**************************************************************************************************/
/* parse the memory reference operand */
{
    if( opndx->indirect ) 
	{  
		/* indirect register operand or stack var */
        /* if displacement doesn't fit in 32-bits:
         * Masm (both ML and ML64) just truncates.
         * Uasm throws an error in 64bit mode and
         * warns (level 3) in the other modes.
         * todo: this check should also be done for direct addressing! */
        if ( opndx->hvalue && ( opndx->hvalue != -1 || opndx->value >= 0 ) ) 
		{
            if ( ModuleInfo.Ofssize == USE64 ) 
			    return( EmitConstError( opndx ) );
            EmitWarn( 3, DISPLACEMENT_OUT_OF_RANGE, opndx->value64 );
        }
        if( opndx->sym == NULL || opndx->sym->state == SYM_STACK ) 
            return( memory_operand( CodeInfo, CurrOpnd, opndx, FALSE ) );
        /* do default processing */
    } 
	else if( opndx->instr != EMPTY ) 
	{
        /* instr is OFFSET | LROFFSET | SEG | LOW | LOWWORD, ... */
        if( opndx->sym == NULL ) 
		{ 
			/* better to check opndx->type? */
            return( idata_nofixup( CodeInfo, CurrOpnd, opndx ) );
        } 
		else 
		{
            /* allow "lea <reg>, [offset <sym>]" */
            if( CodeInfo->token == T_LEA && opndx->instr == T_OFFSET )
                return( memory_operand( CodeInfo, CurrOpnd, opndx, TRUE ) );
            return( idata_fixup( CodeInfo, CurrOpnd, opndx ) );
        }
    } 
	else if( opndx->sym == NULL ) 
	{ 
		/* direct operand without symbol */
        if( opndx->override != NULL ) 
		{
            /* direct absolute memory without symbol.
             DS:[0] won't create a fixup, but
             DGROUP:[0] will create one! */
            /* for 64bit, always create a fixup, since RIP-relative addressing is used
             * v2.11: don't create fixup in 64-bit. */
            if ( opndx->override->token == T_REG || CodeInfo->Ofssize == USE64 )
                return( memory_operand( CodeInfo, CurrOpnd, opndx, FALSE ) );
            else
                return( memory_operand( CodeInfo, CurrOpnd, opndx, TRUE ) );
        } 
		else if (opndx->isptr)
		{

		}
		else 
		{
            return( idata_nofixup( CodeInfo, CurrOpnd, opndx ) );
        }
    } 
	else if( ( opndx->sym->state == SYM_UNDEFINED ) && !opndx->explicit ) 
	{
        /* undefined symbol, it's not possible to determine
         * operand type and size currently. However, for backpatching
         * a fixup should be created. */
        /* assume a code label for branch instructions! */
        if( IS_ANY_BRANCH( CodeInfo->token ) )
            return( process_branch( CodeInfo, CurrOpnd, opndx ) );

        switch( CodeInfo->token ) 
		{
        case T_PUSH:
        case T_PUSHW:
        case T_PUSHD:
            /* v2.0: don't assume immediate operand if cpu is 8086 */
            if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) > P_86 ) 
                return( idata_fixup( CodeInfo, CurrOpnd, opndx ) );
            break;
        default:
            /* v2.04: if operand is the second argument (and the first is NOT
             * a segment register!), scan the
             * instruction table if the instruction allows an immediate!
             * If so, assume the undefined symbol is a constant. */
            if ( CurrOpnd == OPND2 && (( CodeInfo->opnd[OPND1].type & OP_SR ) == 0 ) ) 
			{
                const struct instr_item  *p = CodeInfo->pinstr;
                do 
				{
                    if ( opnd_clstab[p->opclsidx].opnd_type[OPND2] & OP_I ) 
                        return( idata_fixup( CodeInfo, CurrOpnd, opndx ) );
                    p++;
                } while ( p->first == FALSE );
            }
            /* v2.10: if current operand is the third argument, always assume an immediate */
            if ( CurrOpnd == OPND3 )
                return( idata_fixup( CodeInfo, CurrOpnd, opndx ) );
        }
        /* do default processing */
    } 
	else if( ( opndx->sym->state == SYM_SEG ) || ( opndx->sym->state == SYM_GRP ) ) 
	{
        /* SEGMENT and GROUP symbol is converted to SEG symbol for next processing */
        opndx->instr = T_SEG;
        return( idata_fixup( CodeInfo, CurrOpnd, opndx ) );
    } 
	else 
	{
        /* symbol external, but absolute? */
        if( opndx->is_abs ) 
            return( idata_fixup( CodeInfo, CurrOpnd, opndx ) );

        /* CODE location is converted to OFFSET symbol */
        if ( opndx->mem_type == MT_NEAR || opndx->mem_type == MT_FAR ) 
		{
            if( CodeInfo->token == T_LEA ) 
			{
                return( memory_operand( CodeInfo, CurrOpnd, opndx, TRUE ) );
            } 
			else if( opndx->mbr != NULL ) 
			{ 
				/* structure field? */
                return( memory_operand( CodeInfo, CurrOpnd, opndx, TRUE ) );
            } 
			else 
			{
                return( idata_fixup( CodeInfo, CurrOpnd, opndx ) );
            }
        }
    }
    
	/* default processing: memory with fixup */
    return( memory_operand( CodeInfo, CurrOpnd, opndx, TRUE ) );
}

/* Handle constant operands.
 * These never need a fixup. Externals - even "absolute" ones -
 * are always labeled as EXPR_ADDR by the expression evaluator. */
static ret_code process_const( struct code_info *CodeInfo, unsigned CurrOpnd, struct expr *opndx )
/************************************************************************************************/
{
    /* v2.11: don't accept an empty string */
    if ( opndx->quoted_string && opndx->quoted_string->stringlen == 0 )
        return( EmitError( EMPTY_STRING ) );

    /* optimization: skip <value> if it is 0 and instruction
     * is RET[W|D|N|F]. */
    /* v2.06: moved here and checked the opcode directly, so
     * RETD and RETW are also handled. */
    if ( ( ( CodeInfo->pinstr->opcode & 0xf7 ) == 0xc2 ) && CurrOpnd == OPND1 && opndx->value == 0 ) 
	{
        return( NOT_ERROR );
    }
    return( idata_nofixup( CodeInfo, CurrOpnd, opndx ) );
}

static ret_code process_register( struct code_info *CodeInfo, unsigned CurrOpnd, const struct expr opndx[] )
/**********************************************************************************************************/
/*
 * parse and encode direct register operands. Modifies:
 * - CodeInfo->opnd_type
 * - CodeInfo->rm_byte (depending on CurrOpnd)
 * - CodeInfo->iswide
 * - CodeInfo->x86hi_used/x64lo_used
 * - CodeInfo->prefix.rex
 */
{
    enum special_token regtok;
    int                regno;
    uint_32            flags;

    regtok = opndx[CurrOpnd].base_reg->tokval;
    regno = GetRegNo( regtok );
    /* the register's "OP-flags" are stored in the 'value' field */
    flags = GetValueSp( regtok );
    CodeInfo->opnd[CurrOpnd].type = flags;

	if (CodeInfo->opnd[CurrOpnd].type == OP_XMM || CodeInfo->opnd[CurrOpnd].type == OP_YMM)
	{
		if (!evex && regno > 15)
			return(EmitError(UNAUTHORISED_USE_OF_EVEX_REGISTERS));
        /* this fixes suppressed Kn mask register if evex on v2.38 */
        else if (evex && regno > 15)
          CodeInfo->evex_flag = TRUE;
	}
	if (CodeInfo->opnd[CurrOpnd].type == OP_ZMM) 
	{
		if (evex)
			CodeInfo->evex_flag = TRUE;
		else
			return(EmitError(UNAUTHORISED_USE_OF_EVEX_REGISTERS));
	}
	if (CodeInfo->opnd[CurrOpnd].type == OP_K && regno > 7) 
	{
		return(EmitError(USE_OF_REGISTER_ASSUMED_TO_ERROR));
	}

	if ( flags & OP_R8 ) 
	{
        /* it's probably better to not reset the wide bit at all */
        if ( flags != OP_CL )      /* problem: SHL AX|AL, CL */
            CodeInfo->iswide = 0;

#if AMD64_SUPPORT
        if ( CodeInfo->Ofssize == USE64 && regno >=4 && regno <=7 )
            if ( SpecialTable[regtok].cpu == P_86 )
                CodeInfo->x86hi_used = 1; /* it's AH,BH,CH,DH */
            else
                CodeInfo->x64lo_used = 1; /* it's SPL,BPL,SIL,DIL */
#endif
        if ( StdAssumeTable[regno].error & (( regtok >= T_AH && regtok <= T_BH ) ? RH_ERROR : RL_ERROR ) ) 
		{
            DebugMsg(("process_register: assume error, reg=%u\n", regno ));
            return( EmitError( USE_OF_REGISTER_ASSUMED_TO_ERROR ) );
        }
    } 
	else if ( flags & OP_R ) 
	{ 
		/* 16-, 32- or 64-bit GPR? */
        CodeInfo->iswide = 1;
        if ( StdAssumeTable[regno].error & flags & OP_R ) 
		{
            DebugMsg(("process_register: assume error, reg=%u\n", regno ));
            return( EmitError( USE_OF_REGISTER_ASSUMED_TO_ERROR ) );
        }
        if ( flags & OP_R16 ) {
            if ( CodeInfo->Ofssize > USE16 )
                CodeInfo->prefix.opsiz = TRUE;
        } 
		else 
		{
            if( CodeInfo->Ofssize == USE16 )
                CodeInfo->prefix.opsiz = TRUE;
        }
    } 
	else if ( flags & OP_SR ) 
	{
        if( regno == 1 ) 
		{ 
			/* 1 is CS */
            /* POP CS is not allowed */
            if( CodeInfo->token == T_POP ) 
                return( EmitError( POP_CS_IS_NOT_ALLOWED ) );
        }
    } 
	else if ( flags & OP_ST ) 
	{
        regno = opndx[CurrOpnd].st_idx;
        if ( regno > 7 ) 
            return( EmitError( INVALID_COPROCESSOR_REGISTER ) );

        CodeInfo->rm_byte |= regno;
        if( regno != 0 )
            CodeInfo->opnd[CurrOpnd].type = OP_ST_REG;

		/* v2.06: exit, rm_byte is already set. */
        return( NOT_ERROR );

    } 
	else if ( flags & OP_RSPEC ) 
	{ 
		/* CRx, DRx, TRx */
        if( CodeInfo->token != T_MOV ) 
            return( EmitError( ONLY_MOV_CAN_USE_SPECIAL_REGISTER ) );

		/* v2.04: previously there were 3 flags, OP_CR, OP_DR and OP_TR.
         * this was summoned to one flag OP_RSPEC to free 2 flags, which
         * are needed if AVC ( new YMM registers ) is to be supported.
         * To distinguish between CR, DR and TR, the register number is
         * used now: CRx are numbers 0-F, DRx are numbers 0x10-0x1F and
         * TRx are 0x20-0x2F. */
		if (regno >= 0x20) 
		{ 
			/* TRx? */
			CodeInfo->opc_or |= 0x04;
			if ((ModuleInfo.curr_cpu & P_CPU_MASK) >= P_686) 
			{
				return(EmitErr(CANNOT_USE_TRN_TO_TRM_WITH_CURRENT_CPU_SETTING, regno > 0x25 ? 6 : 3, regno > 0x25 ? 7 : 5));
			}
		}
		else if (regno >= 0x10) 
		{ 
			/* DRx? */
			CodeInfo->opc_or |= 0x01;
		}
		regno &= 0x0F;
	}

    /* if it's a x86-64 register (SIL, R8W, R8D, RSI, ... */
    if ( ( SpecialTable[regtok].cpu & P_CPU_MASK ) == P_64 ) 
	{
        CodeInfo->prefix.rex |= 0x40;
        if ( flags & OP_R64 )
            CodeInfo->prefix.rex |= REX_W;
    }

    if( CurrOpnd == OPND1 ) 
	{
        /* the first operand
         * r/m is treated as a 'reg' field */
        CodeInfo->rm_byte |= MOD_11;
        CodeInfo->prefix.rex |= (regno & 8 ) >> 3; /* set REX_B */
        regno &= BIT_012;

        /* fill the r/m field */
        CodeInfo->rm_byte |= regno;
    } 
	else 
	{
        /* the second operand
         * XCHG can use short form if op1 is AX/EAX/RAX */
        if( ( CodeInfo->token == T_XCHG ) && ( CodeInfo->opnd[OPND1].type & OP_A ) &&
             ( 0 == (CodeInfo->opnd[OPND1].type & OP_R8 ) ) ) 
		{
            CodeInfo->prefix.rex |= (regno & 8 ) >> 3; /* set REX_B */
            regno &= BIT_012;

            CodeInfo->rm_byte = ( CodeInfo->rm_byte & BIT_67 ) | regno;
        } 
		else 
		{
            /* fill reg field with reg */
            CodeInfo->prefix.rex |= (regno & 8 ) >> 1; /* set REX_R */
            regno &= BIT_012;
            CodeInfo->rm_byte = ( CodeInfo->rm_byte & ~BIT_345 ) | ( regno << 3 );
        }
    }
    return( NOT_ERROR );
}

/* special handling for string instructions
 * CMPS[B|W|D|Q]
 *  INS[B|W|D]
 * LODS[B|W|D|Q]
 * MOVS[B|W|D|Q]
 * OUTS[B|W|D]
 * SCAS[B|W|D|Q]
 * STOS[B|W|D|Q]
 * the peculiarity is that these instructions ( optionally )
 * have memory operands, which aren't used for code generation
 * <opndx> contains the last operand. */
static void HandleStringInstructions( struct code_info *CodeInfo, const struct expr opndx[] )
/*******************************************************************************************/
{
    int opndidx = OPND1;
    int op_size;

    switch( CodeInfo->token ) {
#if AVXSUPP
    case T_VCMPSD:
    case T_VPCMPD:
    case T_VPCMPB:
    case T_VPCMPUD:
    case T_VPCMPUB:
#endif
    case T_CMPSD:
        /* filter SSE2 opcode CMPSD */
        if ( CodeInfo->opnd[OPND1].type & (OP_XMM | OP_MMX)) {
            /* v2.01: QWORD operand for CMPSD/MOVSD may have set REX_W! */
#if AMD64_SUPPORT
            CodeInfo->prefix.rex &= ~REX_W;
#endif
            return;
        }
        /* fall through */
    case T_CMPS:
    case T_CMPSB:
    case T_CMPSW:
#if AMD64_SUPPORT
    case T_CMPSQ:
#endif
         /* cmps allows prefix for the first operand (=source) only */
        if ( CodeInfo->prefix.RegOverride != EMPTY ) {
            if ( opndx[OPND2].override != NULL ) {
                if ( CodeInfo->prefix.RegOverride == ASSUME_ES ) {
                    /* content of LastRegOverride is valid if
                     * CodeInfo->RegOverride is != EMPTY.
                     */
                    if ( LastRegOverride == ASSUME_DS )
                        CodeInfo->prefix.RegOverride = EMPTY;
                    else
                        CodeInfo->prefix.RegOverride = LastRegOverride;
                } else {
                    DebugMsg1(("HandleStringInstructions: CMPS: CodeInfo->RegOverride=%X, opndx->override=%s\n", CodeInfo->prefix.RegOverride, opndx[OPND2].override->string_ptr ));
                    EmitError( INVALID_INSTRUCTION_OPERANDS );
                }
            } else if ( CodeInfo->prefix.RegOverride == ASSUME_DS ) {
                /* prefix for first operand? */
                CodeInfo->prefix.RegOverride = EMPTY;
            }
        }
        break;
#if AVXSUPP
    case T_VMOVSD:
    case T_VMOVUPS:
#endif
    case T_MOVSD:
    case T_MOVUPS:

        /* filter SSE2 opcode MOVSD */
        if ( ( CodeInfo->opnd[OPND1].type & (OP_XMM | OP_MMX | OP_YMM | OP_ZMM) ) ||
            ( CodeInfo->opnd[OPND2].type & (OP_XMM | OP_MMX | OP_YMM | OP_ZMM) ) ) {
            /* v2.01: QWORD operand for CMPSD/MOVSD may have set REX_W! */
#if AMD64_SUPPORT
            CodeInfo->prefix.rex &= ~REX_W;
#endif
            return;
        }
        /* fall through */
    case T_MOVS:
    case T_MOVSB:
    case T_MOVSW:
#if AMD64_SUPPORT
    case T_MOVSQ:
    case T_MOVQ:
#endif
        /* movs allows prefix for the second operand (=source) only */
        if ( CodeInfo->prefix.RegOverride != EMPTY )
            if ( opndx[OPND2].override == NULL )
                EmitError( INVALID_INSTRUCTION_OPERANDS );
            else if ( CodeInfo->prefix.RegOverride == ASSUME_DS )
                CodeInfo->prefix.RegOverride = EMPTY;
        break;
    case T_OUTS:
    case T_OUTSB:
    case T_OUTSW:
    case T_OUTSD:
        /* v2.01: remove default DS prefix */
        if ( CodeInfo->prefix.RegOverride == ASSUME_DS )
            CodeInfo->prefix.RegOverride = EMPTY;
        opndidx = OPND2;
        break;
    case T_LODS:
    case T_LODSB:
    case T_LODSW:
    case T_LODSD:
#if AMD64_SUPPORT
    case T_LODSQ:
#endif
        /* v2.10: remove unnecessary DS prefix ( Masm-compatible ) */
        if ( CodeInfo->prefix.RegOverride == ASSUME_DS )
            CodeInfo->prefix.RegOverride = EMPTY;
        break;
    default: /*INS[B|W|D], SCAS[B|W|D|Q], STOS[B|W|D|Q] */
        /* INSx, SCASx and STOSx don't allow any segment prefix != ES
         for the memory operand.
         */
        if ( CodeInfo->prefix.RegOverride != EMPTY )
            if ( CodeInfo->prefix.RegOverride == ASSUME_ES )
                CodeInfo->prefix.RegOverride = EMPTY;
            else
                EmitError( INVALID_INSTRUCTION_OPERANDS );
    }

    if ( opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type[opndidx] == OP_NONE ) {
        CodeInfo->iswide = 0;
        CodeInfo->prefix.opsiz = FALSE;
    }

    /* if the instruction is the variant without suffix (MOVS, LODS, ..),
     * then use the operand's size to get further info.
     */
    //if ( CodeInfo->pinstr->opnd_type[opndidx] != OP_NONE &&
    if ( opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type[opndidx] != OP_NONE &&
        CodeInfo->opnd[opndidx].type != OP_NONE ) {
        if (CodeInfo->token == T_KMOVB) op_size = 1;
        else if (CodeInfo->token == T_KMOVW) op_size = 2;
        else if (CodeInfo->token == T_KMOVD) op_size = 4;
        else if (CodeInfo->token == T_KMOVQ) op_size = 8;
        else op_size = OperandSize( CodeInfo->opnd[opndidx].type, CodeInfo );
        /* v2.06: added. if memory operand has no size */
        if ( op_size == 0 )
          op_size = OperandSize( CodeInfo->opnd[opndidx+1].type, CodeInfo );
        if ( op_size == 0 ) {
            if ( CodeInfo->opnd[opndidx].InsFixup == NULL || CodeInfo->opnd[opndidx].InsFixup->sym->state != SYM_UNDEFINED )
                EmitError( INSTRUCTION_OPERAND_MUST_HAVE_SIZE );
            op_size = 1; /* assume shortest format */
        }
        switch( op_size ) {
        case 1:
            CodeInfo->iswide = 0;
            //if( CodeInfo->Ofssize )
                CodeInfo->prefix.opsiz = FALSE;
            break;
        case 2:
            CodeInfo->iswide = 1;
            CodeInfo->prefix.opsiz = CodeInfo->Ofssize ? TRUE : FALSE;
            break;
        case 4:
            CodeInfo->iswide = 1;
            CodeInfo->prefix.opsiz = CodeInfo->Ofssize ? FALSE : TRUE;
            break;
#if AMD64_SUPPORT
        case 8:
            if ( CodeInfo->Ofssize == USE64 ) {
                CodeInfo->iswide = 1;
                CodeInfo->prefix.opsiz = FALSE;
                CodeInfo->prefix.rex = REX_W;
            }
            break;
#endif
        }
    }
    return;
}

static ret_code check_size( struct code_info *CodeInfo, const struct expr opndx[] )
/*********************************************************************************/
/*
 * - use to make sure the size of first operand match the size of second operand;
 * - optimize MOV instruction;
 * - opndx contains last operand
 * todo: BOUND second operand check ( may be WORD/DWORD or DWORD/QWORD ).
 * tofix: add a flag in instr_table[] if there's NO check to be done.
 */
{
    enum operand_type op1 = CodeInfo->opnd[OPND1].type;
    enum operand_type op2 = CodeInfo->opnd[OPND2].type;
    ret_code    rc = NOT_ERROR;
    int         op1_size;
    int         op2_size;
    //int         op_size = 0;
    DebugMsg1(("check_size enter, optype1=%" I32_SPEC "X, optype2=%" I32_SPEC "X\n", op1, op2 ));
    if (CodeInfo->token >= T_KADDB && CodeInfo->token <= T_KUNPCKDQ){
      //int op3_size;
      if ((CodeInfo->opnd[OPND1].type != OP_K) && (CodeInfo->opnd[OPND2].type != OP_K) &&
        (CodeInfo->opnd[OPND3].type != OP_K))
        return(EmitError(INVALID_INSTRUCTION_OPERANDS));
      CodeInfo->indextype = OP_K;
      CodeInfo->basetype = OP_K;

      op1_size = CodeInfo->pinstr->prefix;
      op2_size = CodeInfo->pinstr->prefix;
      goto def_check;
    }

    switch( CodeInfo->token ) {
    case T_IN:
        if( op2 == OP_DX ) {
            /* wide and size is NOT determined by DX, but
             * by the first operand, AL|AX|EAX
             */
            switch( op1 ) {
            case OP_AX:
                break;
            case OP_AL:
                CodeInfo->iswide = 0;         /* clear w-bit */
            case OP_EAX:
                if( CodeInfo->Ofssize ) {
                    CodeInfo->prefix.opsiz = FALSE;
                }
                break;
            }
        }
        break;
    case T_OUT:
        if( op1 == OP_DX ) {
            switch( op2 ) {
            case OP_AX:
                break;
            case OP_AL:
                CodeInfo->iswide = 0;         /* clear w-bit */
            case OP_EAX:
                if( CodeInfo->Ofssize ) {
                    CodeInfo->prefix.opsiz = FALSE;
                }
            }
        }
        break;
    case T_LEA:
#if 0
        /* first op must be 16/32 register, but this condition is checked
         in CodeGen. operands 1 and 2 can be mixed:
         lea cx,[bp]
         lea cx,[ebp]
         lea ecx,[bp]
         lea ecx,[ebp]
         are all valid. However, Masm sometimes complains
         "cannot use 16-bit register with a 32-bit address"
         */
        switch( OperandSize( op1, CodeInfo ) ) {
        case 2:
        case 4:
            break;
        default:
            
            EmitErr( OPERANDS_MUST_BE_THE_SAME_SIZE, OperandSize( op1, CodeInfo ), ModuleInfo.Ofssize ? 4 : 2);
            rc = ERROR;
        }
#endif
        break;
    case T_RCL:
    case T_RCR:
    case T_ROL:
    case T_ROR:
    case T_SAL:
    case T_SAR:
    case T_SHL:
    case T_SHR:
        /* v2.11: added */
        if ( CodeInfo->opnd[OPND1].type == OP_M && CodeInfo->undef_sym == FALSE &&
            ( opndx[OPND1].sym == NULL || opndx[OPND1].sym->state != SYM_UNDEFINED ) ) {
            EmitErr( INSTRUCTION_OPERAND_MUST_HAVE_SIZE );
            rc = ERROR;
            break;
        }
        //if ( CodeInfo->opnd[OPND1].type == OP_M && Parse_Pass == PASS_2 )
        //    EmitWarn( 2, SIZE_NOT_SPECIFIED_ASSUMING, "BYTE" );

        /* v2.0: if second argument is a forward reference,
         * change type to "immediate 1"
         */
        if ( opndx[OPND2].kind == EXPR_ADDR &&
            Parse_Pass == PASS_1 &&
            opndx[OPND2].indirect == FALSE &&
            opndx[OPND2].sym &&
            opndx[OPND2].sym->state == SYM_UNDEFINED ) {
            CodeInfo->opnd[OPND2].type = OP_I8;
            CodeInfo->opnd[OPND2].data32l = 1;
        }
        /* v2.06: added (because if first operand is memory, wide bit
         * isn't set!)
         */
        if ( OperandSize( op1, CodeInfo ) > 1 )
            CodeInfo->iswide = 1;
        /* v2.06: makes the OP_CL_ONLY case in codegen.c obsolete */
        if ( op2 == OP_CL ) {
            /* CL is encoded in bit 345 of rm_byte, but we don't need it
             * so clear it here */
            CodeInfo->rm_byte &= NOT_BIT_345;
        }
        break;
    case T_LDS:
    case T_LES:
    case T_LFS:
    case T_LGS:
    case T_LSS:
        op1_size = OperandSize( op1, CodeInfo ) + 2; /* add 2 for the impl. segment register */
        op2_size = OperandSize( op2, CodeInfo );
        if ( op2_size != 0 && op1_size != op2_size ) {
            return( EmitError( INVALID_OPERAND_SIZE ) );
        }
        break;
    case T_ENTER:
#if 0 /* v2.11: operand sizes are checked in codegen */
        /* ENTER has to be OP_I16, OP_I8_U */
        if( op1 == OP_I32 ) {
            /* parse_phase_1 will treat 16-bit data as OP_I32 if CPU is 386 */
            if( CodeInfo->opnd[OPND1].data32l > (int_32)USHRT_MAX ) {
                /* if op1 is really 32-bit data, then error */
                EmitError( INVALID_OPERAND_SIZE );
                rc = ERROR;
            }
        }
        /* type cast op1 to OP_I16 */
        CodeInfo->opnd[OPND1].type = OP_I16;
        /* op2 have to be 8-bit data */
        if( op2 >= OP_I16 ) {
            if( CodeInfo->opnd[OPND2].data32l > UCHAR_MAX ) {
                EmitError( INVALID_OPERAND_SIZE );
                rc = ERROR;
            }
            CodeInfo->opnd[OPND2].type = OP_I8;
        }
#endif
        break;
    case T_MOVSX:
    case T_MOVZX:
        CodeInfo->iswide = 0;
        op1_size = OperandSize( op1, CodeInfo );
        op2_size = OperandSize( op2, CodeInfo );
        DebugMsg1(("check_size, MOVZX/MOVSX: op2_size=%u, opndx.memtype=%Xh, opndx.sym=%X\n", op2_size, opndx[OPND2].mem_type, opndx[OPND2].sym ));
        if ( op2_size == 0 && Parse_Pass == PASS_2 )
            if ( op1_size == 2 ) {
                EmitWarn( 2, SIZE_NOT_SPECIFIED_ASSUMING, "BYTE" );
            } else
                EmitErr( INSTRUCTION_OPERAND_MUST_HAVE_SIZE );
        switch( op1_size ) {
#if AMD64_SUPPORT
        case 8:
            //if ( CodeInfo->Ofssize == USE64 )
            //    break;
#endif
        case 4:
            if (op2_size < 2)
                ;
            else if (op2_size == 2)
                CodeInfo->iswide = 1;
            else {
                EmitError( OP2_TOO_BIG );
                rc = ERROR;
            }
            CodeInfo->prefix.opsiz = CodeInfo->Ofssize ? FALSE : TRUE;
            break;
        case 2:
            if( op2_size >= 2 ) {
                EmitError( OP2_TOO_BIG );
                rc = ERROR;
            }
            CodeInfo->prefix.opsiz = CodeInfo->Ofssize ? TRUE : FALSE;
            break;
        default:
            /* op1 must be r16/r32/r64 */
            EmitError( OP1_TOO_SMALL );
            rc = ERROR;
        }
        break;
#if AMD64_SUPPORT
    case T_MOVSXD:
        break;
#endif
    case T_ARPL: /* v2.06: new, avoids the OP_R16 hack in codegen.c */
        CodeInfo->prefix.opsiz = 0;
        goto def_check;
        break;
#if AMD64_SUPPORT
    case T_LAR: /* v2.04: added */
    case T_LSL: /* 19-sep-93 */
#if 1 /* v2.04: changed */
        if ( ModuleInfo.Ofssize != USE64 || ( ( op2 & OP_M ) == 0 ) )
            goto def_check;
        /* in 64-bit, if second argument is memory operand,
         * ensure it has size WORD ( or 0 if a forward ref )
         */
        op2_size = OperandSize( op2, CodeInfo );
        if ( op2_size != 2 && op2_size != 0 ) {
            return( EmitError( INVALID_OPERAND_SIZE ) );
        }
        /* the opsize prefix depends on the FIRST operand only! */
        op1_size = OperandSize( op1, CodeInfo );
        if ( op1_size != 2 )
            CodeInfo->prefix.opsiz = FALSE;
#else
        op1_size = OperandSize( op1, CodeInfo );
        switch( op1_size ) {
        case 2:
            if( CodeInfo->Ofssize )
                CodeInfo->prefix.opsiz = TRUE;
            break;
        case 4:
            if( CodeInfo->Ofssize )
                CodeInfo->prefix.opsiz = FALSE;
            break;
        default:
            return( EmitError( INVALID_OPERAND_SIZE ) );
        }
        op2_size = OperandSize( op2, CodeInfo );
        switch( op2_size ) {
        case 2:
        case 4:
            break;
        default:
            EmitError( INVALID_OPERAND_SIZE );
            rc = ERROR;
            break;
        }
#endif
        break;
#endif
    case T_IMUL: /* v2.06: check for 3rd operand must be done here */
        if ( CodeInfo->opnd[OPND3].type != OP_NONE ) {
            int op3_size;
            op1_size = OperandSize( op1, CodeInfo );
            op3_size = OperandSize( CodeInfo->opnd[OPND3].type, CodeInfo );
            /* the only case which must be checked here
             * is a WORD register as op1 and a DWORD immediate as op3 */
            if ( op1_size == 2 && op3_size > 2 ) {
                EmitErr( OPERANDS_MUST_BE_THE_SAME_SIZE, op1_size, op3_size );
                rc = ERROR;
                break;
            }
            if ( CodeInfo->opnd[OPND3].type & ( OP_I16 | OP_I32 ) )
                CodeInfo->opnd[OPND3].type = ( op1_size == 2 ? OP_I16 : OP_I32 );
        }
        goto def_check;
        break;
    case T_CVTSD2SI:
    case T_CVTTSD2SI:
    case T_CVTSS2SI:
    case T_CVTTSS2SI:
    //case T_MOVNTI: /* v2.05: removed */
#if AVXSUPP
    case T_VBROADCASTSD:
    case T_VBROADCASTF128:
    case T_VEXTRACTF128:
    case T_VINSERTF128:
    case T_VCVTSD2SI:
    case T_VCVTTSD2SI:
    case T_VCVTSS2SI:
    case T_VCVTTSS2SI:
#endif
#if VMXSUPP /* v2.09: added */
    case T_INVEPT:
    case T_INVVPID:
#endif
#if SVMSUPP /* v2.09: added */
    case T_INVLPGA:
#endif
        break;
#if AVXSUPP
    case T_VCVTSD2USI:
          CodeInfo->evex_flag = TRUE;
          break;
    case T_VCVTPD2DQ:
    case T_VCVTTPD2DQ:
    case T_VCVTPD2PS:
      if ((op2 == OP_M) && opndx[OPND2].indirect) {
        if (!broadflags) /* v2.49 fix for bcst */
          return(EmitError(INSTRUCTION_OPERAND_MUST_HAVE_SIZE));
      }
      break;
    case T_VMOVDDUP:
        if ( !( op1 & OP_YMM ) )
            break;
        /* fall through */
    case T_VPERM2F128: /* has just one memory variant, and VX_L isnt set */
        if ( op2 == OP_M )
            CodeInfo->opnd[OPND2].type |= OP_M256;
        break;
#endif
#if SSE4SUPP
    case T_CRC32:
        /* v2.02: for CRC32, the second operand determines whether an
         * OPSIZE prefix byte is to be written.
         */
        op2_size = OperandSize( op2, CodeInfo );
        if ( op2_size < 2)
            CodeInfo->prefix.opsiz = FALSE;
        else if ( op2_size == 2 )
            CodeInfo->prefix.opsiz = CodeInfo->Ofssize ? TRUE : FALSE;
        else
            CodeInfo->prefix.opsiz = CodeInfo->Ofssize ? FALSE : TRUE;
        break;
        /* size for BND instructions can not be less then DWORD v2.31 */
     case T_BNDMK:
     case T_BNDCL:
     case T_BNDCU:
     case T_BNDCN:
     case T_BNDMOV:
     case T_BNDLDX:
     case T_BNDSTX:
         if (CodeInfo->mem_type == MT_BYTE || CodeInfo->mem_type == MT_WORD ){
           EmitError( INVALID_OPERAND_SIZE );
           rc = ERROR;
           }
           break;
#endif
    case T_MOVD:
#if 0
        op1_size = OperandSize( op1, CodeInfo );
        op2_size = OperandSize( op2, CodeInfo );
        if( ( op1_size != 0 ) && ( op1_size != 4 )
            || ( op2_size != 0 ) && ( op2_size != 4 ) ) {
            EmitErr( OPERANDS_MUST_BE_THE_SAME_SIZE, op1_size, op2_size );
            rc = ERROR;
        }
#endif
        break;
    case T_MOV:
        if( op1 & OP_SR ) { /* segment register as op1? */
            op2_size = OperandSize( op2, CodeInfo );
            if( ( op2_size == 2 ) || ( op2_size == 4 )
#if AMD64_SUPPORT
               || ( op2_size == 8 && ModuleInfo.Ofssize == USE64 )
#endif
              ) {
                return( NOT_ERROR );
            }
        } else if( op2 & OP_SR ) {
            op1_size = OperandSize( op1, CodeInfo );
            if( ( op1_size == 2 ) || ( op1_size == 4 )
#if AMD64_SUPPORT
               || ( op1_size == 8 && ModuleInfo.Ofssize == USE64 )
#endif
              ) {
                return( NOT_ERROR );
            }
        } else if( ( op1 & OP_M ) && ( op2 & OP_A ) ) { /* 1. operand memory reference, 2. AL|AX|EAX|RAX? */

            if ( CodeInfo->isdirect == FALSE ) {
                /* address mode is indirect.
                 * don't use the short format (opcodes A0-A3) - it exists for direct
                 * addressing only. Reset OP_A flag!
                 */
                CodeInfo->opnd[OPND2].type &= ~OP_A;
                DebugMsg1(("check_size: OP_A flag reset, new op2=%X\n", CodeInfo->opnd[OPND2].type ));
#if AMD64_SUPPORT
            } else if ( CodeInfo->Ofssize == USE64 && ( CodeInfo->opnd[OPND1].data64 < 0x80000000 || CodeInfo->opnd[OPND1].data64 >= 0xffffffff80000000 ) ) {
                /* for 64bit, opcodes A0-A3 ( direct memory addressing with AL/AX/EAX/RAX )
                 * are followed by a full 64-bit moffs. This is only used if the offset won't fit
                 * in a 32-bit signed value.
                 */
                CodeInfo->opnd[OPND2].type &= ~OP_A;
                DebugMsg1(("check_size: OP_A flag reset, new op2=%X\n", CodeInfo->opnd[OPND2].type ));
#endif
            }

        } else if( ( op1 & OP_A ) && ( op2 & OP_M ) ) { /* 2. operand memory reference, 1. AL|AX|EAX|RAX? */

            if ( CodeInfo->isdirect == FALSE ) {
                CodeInfo->opnd[OPND1].type &= ~OP_A;
                DebugMsg1(("check_size: OP_A flag reset, new op1=%X\n", CodeInfo->opnd[OPND1].type ));
#if AMD64_SUPPORT
            } else if ( CodeInfo->Ofssize == USE64 && ( CodeInfo->opnd[OPND2].data64 < 0x80000000 || CodeInfo->opnd[OPND2].data64 >= 0xffffffff80000000 ) ) {
                CodeInfo->opnd[OPND1].type &= ~OP_A;
                DebugMsg1(("check_size: OP_A flag reset, new op2=%X\n", CodeInfo->opnd[OPND1].type ));
#endif
            }
        }
        /* fall through */
    default:
//#if AMD64_SUPPORT
    def_check:
//#endif
        /* make sure the 2 opnds are of the same type */
        op1_size = OperandSize( op1, CodeInfo );
        op2_size = OperandSize( op2, CodeInfo );
        DebugMsg1(("check_size default: op1_size1=%u, op2_size=%u\n", op1_size, op2_size));
        if( op1_size > op2_size ) {
            if( ( op2 >= OP_I8 ) && ( op2 <= OP_I32 ) ) {     /* immediate */
                op2_size = op1_size;    /* promote to larger size */
            }
        }
#if 1
        /* v2.04: check in idata_nofixup was signed,
         * so now add -256 - -129 and 128-255 to acceptable byte range.
         * Since Masm v8, the check is more restrictive, -255 - -129
         * is no longer accepted.
         */
        if( ( op1_size == 1 ) && ( op2 == OP_I16 ) &&
            ( CodeInfo->opnd[OPND2].data32l <= UCHAR_MAX ) &&
            ( CodeInfo->opnd[OPND2].data32l >= -128 ) ) {
            //( CodeInfo->opnd[OPND2].data32l >= -255 ) ) {

            return( rc ); /* OK cause no sign extension */
        }
#endif
#if 0
        /* v2.03: this "if" made Uasm accept any 32-bit constant
         *        for 16-bit destinations, which is Masm compatibel,
         *      "mov ax, 12345h"
         * the test is a bit too liberal here, IMO, because
         * it makes Uasm accept "mov ax, near32 ptr var",
         * which is rejected by Masm.
         */
        if( ( op1_size == 2 ) && ( op2 == OP_I32 )
            && ( CodeInfo->data[OPND2] <= USHRT_MAX ) ) {
            return( rc ); /* OK cause no sign extension */
        }
#endif
        if( op1_size != op2_size ) {
            /* if one or more are !defined, set them appropriately */
#if AVXSUPP
            if( ( op1 | op2 ) & ( OP_MMX | OP_XMM | OP_YMM | OP_K | OP_ZMM ) ) {
#else
            if( ( op1 | op2 ) & ( OP_MMX | OP_XMM ) ) {
#endif
            }
            else if( ( op1_size != 0 ) && ( op2_size != 0 ) ) {
              if ((CodeInfo->token == T_VCVTSD2USI)||(CodeInfo->token == T_VCVTSS2USI)||
                (CodeInfo->token == T_VCVTTSD2USI)||(CodeInfo->token == T_VCVTTSS2USI))
                CodeInfo->evex_flag = TRUE;
              else{
                if (CodeInfo->token >= T_BNDMK && CodeInfo->token <= T_BNDSTX){
                  switch (CodeInfo->token){
                    case T_BNDMK:
                    case T_BNDCL:
                    case T_BNDCU:
                    case T_BNDCN:
                                if (CodeInfo->mem_type == MT_DWORD || CodeInfo->mem_type == MT_QWORD ||
                                    CodeInfo->mem_type ==  MT_EMPTY)
                                  ;
                                else{
                                   EmitErr(OPERANDS_MUST_BE_THE_SAME_SIZE, op1_size, op2_size);
                                   rc = ERROR;
                                  }
                                break;
                    case T_BNDMOV:
                                if (CodeInfo->mem_type == MT_DWORD || CodeInfo->mem_type == MT_QWORD ||
                                    CodeInfo->mem_type == MT_OWORD || CodeInfo->mem_type ==  MT_EMPTY)
                                  ;
                                else{
                                   EmitErr(OPERANDS_MUST_BE_THE_SAME_SIZE, op1_size, op2_size);
                                   rc = ERROR;
                                  }
                                break;
                    case T_BNDLDX:
                    case T_BNDSTX:
                                if (CodeInfo->mem_type == MT_DWORD || CodeInfo->mem_type == MT_QWORD ||
                                    CodeInfo->mem_type ==  MT_EMPTY)
                                  ;
                                else{
                                   EmitErr(OPERANDS_MUST_BE_THE_SAME_SIZE, op1_size, op2_size);
                                   rc = ERROR;
                                  }
                                break;
                    }
                  }
                else{
                 EmitErr(OPERANDS_MUST_BE_THE_SAME_SIZE, op1_size, op2_size);
                 rc = ERROR;
                  }
              }
            }
            /* size == 0 is assumed to mean "undefined", but there
             * is also the case of an "empty" struct or union. The
             * latter case isn't handled correctly.
             */
            if( op1_size == 0 ) {
                if( ( op1 & OP_M_ANY ) && ( op2 & OP_I ) ) {
                    char *p = "WORD";
                    if( (uint_32)CodeInfo->opnd[OPND2].data32l > USHRT_MAX || op2_size == 4 ) {
                        CodeInfo->iswide = 1;
                        DebugMsg1(("check_size: op1=%X op1_size=0, op2=%X, op2_size=%u CodeInfo->data[2]=%X\n", op1, op2, op2_size, CodeInfo->opnd[OPND2].data32l ));
#if 1 /* added v1.95: in 16bit code, 'mov [di],8000h' should warn: assuming WORD */
                        if ( ModuleInfo.Ofssize == USE16 && op2_size > 2 && InWordRange( CodeInfo->opnd[OPND2].data32l ) )
                            op2_size = 2;
#endif
                        if (op2_size <= 2 && CodeInfo->opnd[OPND2].data32l > SHRT_MIN && ModuleInfo.Ofssize == USE16 ) {
                            CodeInfo->mem_type = MT_WORD;
                            CodeInfo->opnd[OPND2].type = OP_I16;
                        } else {
                            CodeInfo->mem_type = MT_DWORD;
                            CodeInfo->opnd[OPND2].type = OP_I32;
                            p = "DWORD";
                        }
                    } else if( (uint_32)CodeInfo->opnd[OPND2].data32l > UCHAR_MAX  ) {//|| op2_size == 2
                         CodeInfo->mem_type = MT_WORD;
                         CodeInfo->iswide = 1;
                         CodeInfo->opnd[OPND2].type = OP_I16;
                    } else {
                         CodeInfo->mem_type = MT_BYTE;
                         CodeInfo->opnd[OPND2].type = OP_I8;
						             CodeInfo->opnd[OPND1].type = OP_M08;
                         p = "BYTE";
                    }
                    if( opndx[OPND2].explicit == FALSE ) {
                        /* v2.06: emit warning at pass one if mem op isn't a forward ref */
                        /* v2.06b: added "undefined" check */
                        if ( ( CodeInfo->opnd[OPND1].InsFixup == NULL && Parse_Pass == PASS_1 && CodeInfo->undef_sym == FALSE ) ||
                            ( CodeInfo->opnd[OPND1].InsFixup && Parse_Pass == PASS_2 ) )
                                EmitWarn( 1, SIZE_NOT_SPECIFIED_ASSUMING, p );  //ovde je greska
                    }
                } else if( ( op1 & OP_M_ANY ) && ( op2 & ( OP_R | OP_SR ) ) ) {
                } else if( ( op1 & ( OP_MMX | OP_XMM ) ) && ( op2 & OP_I ) ) {
                    if( (uint_32)CodeInfo->opnd[OPND2].data32l > USHRT_MAX ) {
                         CodeInfo->opnd[OPND2].type = OP_I32;
                    } else if( (uint_32)CodeInfo->opnd[OPND2].data32l > UCHAR_MAX ) {
                         CodeInfo->opnd[OPND2].type = OP_I16;
                    } else {
                         CodeInfo->opnd[OPND2].type = OP_I8;
                    }
                } else if( ( op1 | op2 ) & ( OP_MMX | OP_XMM ) ) {
                } else {
                    //AsmIntErr( 1 ); /* printf("internal error = %u", 1 ) */
                    switch( op2_size ) {
                    case 1:
                        CodeInfo->mem_type = MT_BYTE;
                        if( ( Parse_Pass == PASS_1 ) && ( op2 & OP_I ) ) {
                            EmitWarn( 1, SIZE_NOT_SPECIFIED_ASSUMING, "BYTE" );
                        }
                        break;
                    case 2:
                        CodeInfo->mem_type = MT_WORD;
                        CodeInfo->iswide = 1;
                        if( ( Parse_Pass == PASS_1 ) && ( op2 & OP_I ) ) {
                            EmitWarn( 1, SIZE_NOT_SPECIFIED_ASSUMING, "WORD" );
                        }
                        if( CodeInfo->Ofssize )
                            CodeInfo->prefix.opsiz = TRUE;
                        break;
                    case 4:
                        CodeInfo->mem_type = MT_DWORD;
                        CodeInfo->iswide = 1;
                        if( ( Parse_Pass == PASS_1 ) && ( op2 & OP_I ) ) {
                            EmitWarn( 1, SIZE_NOT_SPECIFIED_ASSUMING, "DWORD" );
                        }
                        break;
                    }
                }
            }
        }
    }
    DebugMsg1(("check_size exit [CodeInfo->mem_type=%Xh]\n", CodeInfo->mem_type));
    return( rc );
}

static struct asym *IsType( const char *name )
/********************************************/
{
    struct asym *sym;

    sym = SymSearch( name );
    if ( sym && (sym->state == SYM_TYPE ) )
        return( sym );
    return( NULL );
}

/*
 * ParseLine() is the main parser function.
 * It scans the tokens in tokenarray[] and does:
 * - for code labels: call CreateLabel()
 * - for data items and data directives: call data_dir()
 * - for other directives: call directive[]()
 * - for instructions: fill CodeInfo and call codegen() */
ret_code ParseLine(struct asm_tok tokenarray[]) {
	int                i;
	int                j;
	unsigned           dirflags;
	unsigned           CurrOpnd;
	ret_code           temp;
	struct asym        *sym;
	uint_32            oldofs;
	enum special_token regtok;
	int                c0;
	int                c1;
	unsigned           flags;
	char               *pnlbl;
	int                alignCheck = 16;
	int                infSize    = 0;
	int                oldi       = 0;
	struct dsym        *recsym    = 0;
	struct code_info   CodeInfo;
	struct expr        opndx[MAX_OPND + 1];
	// We create copies of these structures for now as the old codegen has a very ugly way of working with additional vex 3 opnd forms, by
	// adding them as extra values in codeinfo and removing them as true operands. For V2 this is no longer the case, however we don't want
	// the existing codegen to break until it's completely replaced.
	struct code_info   CodeInfoV2;
	struct expr        opndxV2[MAX_OPND + 1];
	const char         *opcodePtr = NULL;
	int                opndCount  = 0;
	char               *instr     = NULL;
    bool               doDataInProc = FALSE;

	memset(&opndx, 0, sizeof(opndx));
	memset(&CodeInfo, 0, sizeof(CodeInfo));
	memset(&opndxV2, 0, sizeof(opndx));
	memset(&CodeInfoV2, 0, sizeof(CodeInfo));

	i = 0;
  
	/* ************************************************************** */
	/* Support direct usage of USE16, USE32, USE64 for UASM Flat Mode */
	/* ************************************************************** */
	if (tokenarray[0].token == T_ID && strcasecmp(tokenarray[0].string_ptr, "use16") == 0) {
		ModuleInfo.frame_auto = 0;
		ModuleInfo.win64_flags = 0;
		ModuleInfo.offsettype = OT_GROUP;
		ModuleInfo.Ofssize = USE16;
		ModuleInfo.wordsize = 2;
		ModuleInfo.defOfssize = USE16;
		ModuleInfo.sub_format = SFORMAT_NONE;
		ModuleInfo.basereg[ModuleInfo.Ofssize] = T_SP;
		if (ModuleInfo.currseg)
		{
			ModuleInfo.currseg->e.seginfo->Ofssize = USE16;
			ModuleInfo.currseg->e.seginfo->segtype = SEGTYPE_CODE;
			ModuleInfo.currseg->sym.segment->Ofssize = USE16;
		}
		if (CurrSeg)
		{
			CurrSeg->e.seginfo->Ofssize = USE16;
			CurrSeg->e.seginfo->segtype = SEGTYPE_CODE;
			CurrSeg->sym.segment->Ofssize = USE16;
			CurrSeg->sym.Ofssize = USE16;
		}
		sym = SymCheck("_flat");
		if (sym)
		{
			sym->isdefined = TRUE;
			UpdateCurrSegVars();
			SetOfssize();
		}
		FStoreLine(1);
		return(NOT_ERROR);
	}
	else if (tokenarray[0].token == T_ID && strcasecmp(tokenarray[0].string_ptr, "use32") == 0) {
		ModuleInfo.frame_auto = 0;
		ModuleInfo.win64_flags = 0;
		ModuleInfo.offsettype = OT_GROUP;
		ModuleInfo.Ofssize = USE32;
		ModuleInfo.wordsize = 4;
		ModuleInfo.defOfssize = USE32;
		ModuleInfo.sub_format = SFORMAT_NONE;
		ModuleInfo.basereg[ModuleInfo.Ofssize] = T_ESP;
		if (ModuleInfo.currseg)
		{
			ModuleInfo.currseg->e.seginfo->Ofssize = USE32;
			ModuleInfo.currseg->e.seginfo->segtype = SEGTYPE_CODE;
			ModuleInfo.currseg->sym.segment->Ofssize = USE32;
		}
		if (CurrSeg)
		{
			CurrSeg->e.seginfo->Ofssize = USE32;
			CurrSeg->e.seginfo->segtype = SEGTYPE_CODE;
			CurrSeg->sym.segment->Ofssize = USE32;
			CurrSeg->sym.Ofssize = USE32;
		}
		sym = SymCheck("_flat");
		if (sym)
		{
			sym->isdefined = TRUE;
			UpdateCurrSegVars();
			SetOfssize();
		}
		FStoreLine(1);
		return(NOT_ERROR);
	}
	else if (tokenarray[0].token == T_ID && strcasecmp(tokenarray[0].string_ptr, "use64") == 0) {
		ModuleInfo.frame_auto = 1;
		ModuleInfo.win64_flags = 11;
		ModuleInfo.offsettype = OT_FLAT;
		ModuleInfo.Ofssize = USE64;
		ModuleInfo.wordsize = 8;
		ModuleInfo.defOfssize = USE64;
		ModuleInfo.langtype = LANG_FASTCALL;
		ModuleInfo.sub_format = SFORMAT_NONE;
		ModuleInfo.basereg[ModuleInfo.Ofssize] = T_RSP;
		if (ModuleInfo.currseg)
		{
			ModuleInfo.currseg->e.seginfo->Ofssize = USE64;
			ModuleInfo.currseg->e.seginfo->segtype = SEGTYPE_CODE;
			ModuleInfo.currseg->sym.segment->Ofssize = USE64;
			ModuleInfo.currseg->e.seginfo->alignment = 12;
		}
		if (CurrSeg)
		{
			CurrSeg->e.seginfo->Ofssize = USE64;
			CurrSeg->e.seginfo->segtype = SEGTYPE_CODE;
			CurrSeg->sym.segment->Ofssize = USE64;
			CurrSeg->sym.Ofssize = USE64;
			CurrSeg->e.seginfo->alignment = 12;
		}
		sym = SymCheck("_flat");
		if (sym)
		{
			sym->isdefined = TRUE;
			UpdateCurrSegVars();
			SetOfssize();
		}
		FStoreLine(1);
		return(NOT_ERROR);
	}
	/* ************************************************************** */

	/* ************************************************************** */
	/* Does line start with a code label?                             */
	/* ************************************************************** */
	if (tokenarray[0].token == T_ID && (tokenarray[1].token == T_COLON || tokenarray[1].token == T_DBL_COLON)) 
	{
		i = 2;

		if (ProcStatus & PRST_PROLOGUE_NOT_DONE) 
			write_prologue(tokenarray);

		/* create a global or local code label */
		if (CreateLabel(tokenarray[0].string_ptr, MT_NEAR, NULL,(ModuleInfo.scoped && CurrProc && tokenarray[1].token != T_DBL_COLON)) == NULL) 
			return(ERROR);

		if (tokenarray[i].token == T_FINAL) 
		{
			FStoreLine(0);
			if (CurrFile[LST]) 
				LstWrite(LSTTYPE_LABEL, 0, NULL);

			return(NOT_ERROR);
		}
	}

	/* ************************************************************** */
	/* handle directives and (anonymous) data items                   */
	/* ************************************************************** */
	if (tokenarray[i].token != T_INSTRUCTION) 
	{
		/* a code label before a data item is only accepted in Masm5 compat mode */
		Frame_Type = FRAME_NONE;
		SegOverride = NULL;
		
		if (i == 0 && tokenarray[0].token == T_ID) 
		{
			/* token at pos 0 may be a label.
			* it IS a label if:
			* 1. token at pos 1 is a directive (lbl dd ...)
			* 2. token at pos 0 is NOT a userdef type ( lbl DWORD ...)
			* 3. inside a struct and token at pos 1 is a userdef type or a predefined type. (usertype DWORD|usertype ... )
			*    the separate namespace allows this syntax here. */
			if (tokenarray[1].token == T_DIRECTIVE)
				i++;
			else {
				sym = IsType(tokenarray[0].string_ptr);
				if (sym == NULL)
					i++;
				else if (CurrStruct && ((tokenarray[1].token == T_STYPE) || (tokenarray[1].token == T_ID && (IsType(tokenarray[1].string_ptr)))))
					i++;
			}
		}
        
		switch (tokenarray[i].token) 
		{
			case T_DIRECTIVE:
                
                if (tokenarray[i].dirtype == DRT_DATADIR)
                {
                    /* UASM 2.51 - Don't write anonymous data items in Procs before the prologue is done */
                    if (!(ProcStatus & PRST_PROLOGUE_NOT_DONE) || !ProcStatus)
                        return(data_dir(i, tokenarray, NULL));
                    else {
                       doDataInProc = TRUE;
                        goto dataInProc;
                    }
                }

				dirflags = GetValueSp(tokenarray[i].tokval);
				if (CurrStruct && (dirflags & DF_NOSTRUC)) 
				{
					return(EmitError(STATEMENT_NOT_ALLOWED_INSIDE_STRUCTURE_DEFINITION));
				}
			    /* label allowed for directive? */
				if (dirflags & DF_LABEL) 
				{
					if (i && tokenarray[0].token != T_ID) 
						return(EmitErr(SYNTAX_ERROR_EX, tokenarray[0].string_ptr));
				}
				else if (i && tokenarray[i - 1].token != T_COLON && tokenarray[i - 1].token != T_DBL_COLON) 
					return(EmitErr(SYNTAX_ERROR_EX, tokenarray[i - 1].string_ptr));
				
				/* must be done BEFORE FStoreLine()! */
				if ((ProcStatus & PRST_PROLOGUE_NOT_DONE) && (dirflags & DF_PROC)) 
					write_prologue(tokenarray);
                
         		if (StoreState || (dirflags & DF_STORE)) 
				{
					if ((dirflags & DF_CGEN) && ModuleInfo.CurrComment && ModuleInfo.list_generated_code) 
						FStoreLine(1);
					else
						FStoreLine(0);
				}

				if (tokenarray[i].dirtype > DRT_DATADIR) 
					temp = directive_tab[tokenarray[i].dirtype](i, tokenarray);
				else 
				{
					temp = ERROR;
					/* ENDM, EXITM and GOTO directives should never be seen here */
					switch (tokenarray[i].tokval) 
					{
						case T_ENDM:
							EmitError(UNMATCHED_MACRO_NESTING);
							break;
						case T_EXITM:
						case T_GOTO:
							EmitError(DIRECTIVE_MUST_APPEAR_INSIDE_A_MACRO);
							break;
						default:
							/* this error may happen if CATSTR, SUBSTR, MACRO, ...a ren't at pos 1 */
                            EmitErr(SYNTAX_ERROR_EX, tokenarray[i].string_ptr);
							break;
					}
				}

				/* v2.0: for generated code it's important that list file is written in ALL passes, to update file position! */
				if (ModuleInfo.list && (Parse_Pass == PASS_2 || ModuleInfo.GeneratedCode || UseSavedState == FALSE))
					LstWriteSrcLine();
				return(temp);

			case T_STYPE:
      
				return(data_dir(i, tokenarray, NULL));

			case T_ID:
      
				if (sym = IsType(tokenarray[i].string_ptr)) {
					return(data_dir(i, tokenarray, sym));
				}
				break;

			default:
				if (tokenarray[i].token == T_COLON) 
				{
					return(EmitError(SYNTAX_ERROR_UNEXPECTED_COLON));
				}
				break;
		} /* end switch (tokenarray[i].token) */

		if (i && tokenarray[i - 1].token == T_ID)
			i--;
		return(EmitErr(SYNTAX_ERROR_EX, tokenarray[i].string_ptr));

	} /* end of != T_INSTRUCTION */

dataInProc:

	if (CurrStruct)
		return(EmitError(STATEMENT_NOT_ALLOWED_INSIDE_STRUCTURE_DEFINITION));

	if (ProcStatus & PRST_PROLOGUE_NOT_DONE) 
		write_prologue(tokenarray);
    
    if (doDataInProc)
    {
        doDataInProc = FALSE;
        return(data_dir(i, tokenarray, NULL));
    }

	/* v2.07: moved because special handling is needed for RET/IRET */
	if (CurrFile[LST]) oldofs = GetCurrOffset();

	/* ************************************************************** */
	/* INIT: CodeInfo                                                 */
	/* ************************************************************** */
	CodeInfo.prefix.ins         = EMPTY;
	CodeInfo.prefix.RegOverride = EMPTY;
	CodeInfo.prefix.rex         = 0;
	CodeInfo.prefix.adrsiz      = FALSE;
	CodeInfo.prefix.opsiz       = FALSE;
	CodeInfo.mem_type           = MT_EMPTY;
	for (j = 0; j < MAX_OPND; j++)
		CodeInfo.opnd[j].type = OP_NONE;
	CodeInfo.rm_byte   = 0;
	CodeInfo.sib       = 0;
	CodeInfo.Ofssize   = ModuleInfo.Ofssize;
	CodeInfo.opc_or    = 0;
	CodeInfo.basetype  = 0;
	CodeInfo.indextype = 0;
	CodeInfo.evex_sae  = 0;
	CodeInfo.vexregop  = 0;
	CodeInfo.tuple     = 0;
	CodeInfo.isptr     = FALSE;
	CodeInfo.vexconst  = 0;
	CodeInfo.evex_flag = FALSE;  /* if TRUE will output 0x62 */
	CodeInfo.reg1      = 0;
	CodeInfo.reg2      = 0;
	CodeInfo.reg3      = 0xff;   /* if not reg3 make it negative  */
	CodeInfo.basereg   = 0xff;
	CodeInfo.indexreg  = 0xff;
	CodeInfo.zreg      = 0;
	if (tokenarray[0].tokval >= T_KADDB && tokenarray[0].tokval <= T_KTESTQ)
		CodeInfo.evex_flag = FALSE;
	else 
	{
		// Init EVEX three bytes
		CodeInfo.evex_p0 = 0;      /* P0[3 : 2] Must be 0 */
		CodeInfo.evex_p1 = 0x4;    /* P1[2]     Must be 1 */
		CodeInfo.evex_p2 = 0;
		if (broadflags || decoflags || evexflag)
			CodeInfo.evex_flag = TRUE;   /* if TRUE will output 0x62 */
	}
	CodeInfo.flags = 0;

	/* ******************************************************************* */
	/* instruction prefix? T_LOCK, T_REP, T_REPE, T_REPNE, T_REPNZ, T_REPZ */
	/* ******************************************************************* */
	if (tokenarray[i].tokval >= T_LOCK && tokenarray[i].tokval <= T_REPZ) 
	{
		CodeInfo.prefix.ins = tokenarray[i].tokval;
		i++;
		/* prefix has to be followed by an instruction */
		if (tokenarray[i].token != T_INSTRUCTION) 
			return(EmitError(PREFIX_MUST_BE_FOLLOWED_BY_AN_INSTRUCTION));
	};

	/* ************************************************************** */
	/* Handle RETURNS inside CurrProc                                 */
	/* ************************************************************** */
	if (CurrProc) 
	{
		switch (tokenarray[i].tokval) 
		{
			case T_RETN:
			case T_RET:
			case T_IRET:  /* IRET is always 16-bit; OTOH, IRETW doesn't exist */
			case T_IRETD:
		    case T_IRETQ:
				if ( (!(ProcStatus & PRST_INSIDE_EPILOGUE) && ModuleInfo.epiloguemode != PEM_NONE && tokenarray[i].tokval != T_RETN) ||
					 (!(ProcStatus & PRST_INSIDE_EPILOGUE) && (CurrProc->e.procinfo->basereg == T_ESP || CurrProc->e.procinfo->basereg == T_RSP) )) 
				{
					/* v2.07: special handling for RET/IRET */
					FStoreLine((ModuleInfo.CurrComment && ModuleInfo.list_generated_code) ? 1 : 0);
					ProcStatus |= PRST_INSIDE_EPILOGUE;
					temp = RetInstr(i, tokenarray, Token_Count);
					ProcStatus &= ~PRST_INSIDE_EPILOGUE;
					return(temp);
				}
				/* default translation: just RET to RETF if proc is far */
				/* v2.08: this code must run even if PRST_INSIDE_EPILOGUE is set */
				if (tokenarray[i].tokval == T_RET && CurrProc->sym.mem_type == MT_FAR)
					tokenarray[i].tokval = T_RETF;
		}
	}

	FStoreLine(0); /* must be placed AFTER write_prologue() */

	CodeInfo.token = tokenarray[i].tokval;
	opcodePtr      = tokenarray[i].string_ptr; // Copy a pointer to the mnemonic string for CodeGenV2.

	/* get the instruction's start position in InstrTable[] */
	CodeInfo.pinstr = &InstrTable[IndexFromToken(CodeInfo.token)];
	i++;

	if (CurrSeg == NULL)
		return(EmitError(MUST_BE_IN_SEGMENT_BLOCK));
	if (CurrSeg->e.seginfo->segtype == SEGTYPE_UNDEF)
		CurrSeg->e.seginfo->segtype = SEGTYPE_CODE;
	if (ModuleInfo.CommentDataInCode)
		omf_OutSelect(FALSE);

	/* UASM 2.37: Calculate an inferred memory size if any operand is a register, this can be used when no memory size info is available */
	/* ********************************************************************************************************************************* */
	oldi = i;
	for (j = 0; j < sizeof(opndx) / sizeof(opndx[0]) && tokenarray[i].token != T_FINAL; j++) 
	{
		if (j) 
		{
			if (tokenarray[i].token != T_COMMA)
				break;
			i++;
		}
		if (EvalOperand(&i, tokenarray, Token_Count, &opndx[j], 0) == ERROR)
			return(ERROR);
	
		if (opndx[j].kind == EXPR_REG)
		{
			infSize = SizeFromRegister(opndx[j].base_reg->tokval);
			break;
		}
	}
	i = oldi;

	/* ************************************************************** */
    /* Get Instruction Arguments (Up to 4 with AVXSUPP)               */
    /* ************************************************************** */
	for (j = 0; j < sizeof(opndx) / sizeof(opndx[0]) && tokenarray[i].token != T_FINAL; j++) 
	{
		if (j) 
		{
			if (tokenarray[i].token != T_COMMA)
				break;
			i++;
		}
		
		if (EvalOperand(&i, tokenarray, Token_Count, &opndx[j], 0) == ERROR) 
			return(ERROR);

		/* ********************************************************************************************************************************* */
		/* UASM 2.37: For immediate indirect memory addresses, allow DS override assumption in 32 and 64bit, and apply memory size info      */
		/* ********************************************************************************************************************************* */
		if (opndx[j].kind == EXPR_CONST && opndx[j].isptr) 
		{
			CodeInfo.isptr = TRUE;
			if (opndx[j].mem_type == MT_EMPTY)
			{
				switch (infSize)
				{
					case 1:
						opndx[j].mem_type = MT_BYTE;
						break;
					case 2:
						opndx[j].mem_type = MT_WORD;
						break;
					case 4:
						opndx[j].mem_type = MT_DWORD;
						break;
					case 8:
						opndx[j].mem_type = MT_QWORD;
						break;
					case 16:
						opndx[j].mem_type = MT_OWORD;
						break;
					case 32:
						opndx[j].mem_type = MT_YMMWORD;
						break;
					case 64:
						opndx[j].mem_type = MT_ZMMWORD;
						break;
				}
			}
			opndx[j].kind = EXPR_ADDR;
			if(ModuleInfo.Ofssize != USE64)
				opndx[j].override = &dsOver;
		}

		if (j == 2 && (opndx[j].kind == EXPR_REG)) 
		{
			regtok = opndx[OPND3].base_reg->tokval;
			CodeInfo.reg3 = GetRegNo(regtok);
		}

		switch (opndx[j].kind) 
		{
			case EXPR_FLOAT:
				/* v2.06: accept float constants for PUSH */
				if (j == OPND2 || CodeInfo.token == T_PUSH || CodeInfo.token == T_PUSHD) 
				{
					#if FPIMMEDIATE
					if (Options.strict_masm_compat == FALSE) 
					{
						/* convert to REAL4, unless REAL8 coercion is requested */
						atofloat(&opndx[j].fvalue, opndx[j].float_tok->string_ptr, opndx[j].mem_type == MT_REAL8 ? 8 : 4, opndx[j].negative, opndx[j].float_tok->floattype);
						opndx[j].kind = EXPR_CONST;
						opndx[j].float_tok = NULL;
						break;
					}
					#endif
					/* Masm message is: real or BCD number not allowed */
					return(EmitError(FP_INITIALIZER_IGNORED));
				}

			/* Handle EVEX Static Rounding Mode {sae}, {rn-sae}, {rd-sae}, {ru-sae}, {rz-sae} */
			case EXPR_DECORATOR:
				if (opndx[j - 1].indirect || opndx[j - 2].indirect)
					return(EmitError(EMBEDDED_ROUNDING_IS_AVAILABLE_ONLY_WITH_REG_REG_OP));
				CodeInfo.evex_sae = opndx[j].saeflags;
				CodeInfo.evex_flag = TRUE;  /* {sae} must set evex_flag v247.2 */
				j--;
				break;

			case EXPR_EMPTY:
				if (i == Token_Count)
					i--;  /* v2.08: if there was a terminating comma, display it */
      
		    case EXPR_ERROR:
				return(EmitErr(SYNTAX_ERROR_EX, tokenarray[i].string_ptr));
		}

		opndCount = j;
	}
	opndCount++; // Track the number of operands for CodeGenV2.

	if (tokenarray[i].token != T_FINAL) 
	{
		return(EmitErr(SYNTAX_ERROR_EX, tokenarray[i].tokpos));
	}

	/* ********************************************************* */
	/* UASM 2.36 SIMD aligned check                              */
	/* ********************************************************* */
	if (opndx[0].kind == EXPR_REG && (GetValueSp(opndx[0].base_reg->tokval) == OP_XMM || 
		GetValueSp(opndx[0].base_reg->tokval) == OP_YMM|| GetValueSp(opndx[0].base_reg->tokval) == OP_ZMM)) 
	{

		if (GetValueSp(opndx[0].base_reg->tokval) == OP_XMM)
			alignCheck = 16;
		else if (GetValueSp(opndx[0].base_reg->tokval) == OP_YMM)
			alignCheck = 32;
		else if (GetValueSp(opndx[0].base_reg->tokval) == OP_ZMM) 
		{
			CodeInfo.zreg = 1;
			alignCheck = 64;
		}

		if (opndx[1].kind == EXPR_ADDR && opndx[1].sym) 
		{
			/* Check the symbol size, if it's compatible force xmmword/ymmword type */
			if (opndx[1].sym->total_size == alignCheck && !IsScalarSimdInstr(CodeInfo.token) )
			{
				if (alignCheck == 16)
					opndx[1].mem_type = MT_OWORD;
				else if (alignCheck == 32)
					opndx[1].mem_type = MT_YMMWORD;
				else
					opndx[1].mem_type = MT_ZMMWORD;
			}

			if (CodeInfo.token == T_MOVAPS || CodeInfo.token == T_VMOVAPS || CodeInfo.token == T_MOVDQA || 
				CodeInfo.token == T_VMOVDQA || CodeInfo.token == T_MOVAPD || CodeInfo.token == T_VMOVAPD || CodeInfo.token == T_MOVNTDQA || CodeInfo.token == T_VMOVNTDQA) 
			{
				if (opndx[1].sym->state != SYM_STACK && (opndx[1].sym->offset % alignCheck != 0) && Parse_Pass == PASS_2)
					EmitWarn(2, UNALIGNED_SIMD_USE);
			}
		}
		else if (opndx[2].kind == EXPR_ADDR && opndx[2].sym) 
		{
			/* Check the symbol size, if it's compatible force xmmword/ymmword type */
			if (opndx[2].sym->total_size == alignCheck && !IsScalarSimdInstr(CodeInfo.token))
			{
				if (alignCheck == 16)
					opndx[2].mem_type = MT_OWORD;
	 			else if (alignCheck == 32)
  					opndx[2].mem_type = MT_YMMWORD;
				else
					opndx[2].mem_type = MT_ZMMWORD;
			}
		}

	}
	else if (opndx[0].kind == EXPR_ADDR && opndx[0].sym) 
	{
		if (opndx[1].kind == EXPR_REG && (GetValueSp(opndx[1].base_reg->tokval) == OP_XMM ||
			GetValueSp(opndx[1].base_reg->tokval) == OP_YMM|| GetValueSp(opndx[1].base_reg->tokval) == OP_ZMM)) 
		{
	        if (GetValueSp(opndx[1].base_reg->tokval) == OP_XMM)
				alignCheck = 16;
			else if (GetValueSp(opndx[1].base_reg->tokval) == OP_YMM)
				alignCheck = 32;
			else if (GetValueSp(opndx[1].base_reg->tokval) == OP_ZMM) 
			{
				CodeInfo.zreg = 1;
				alignCheck = 64;
			}

			/* Check the symbol size, if it's compatible force xmmword/ymmword type */
			if (opndx[0].sym->total_size == alignCheck && !IsScalarSimdInstr(CodeInfo.token)) 
			{
				if (alignCheck == 16)
					opndx[0].mem_type = MT_OWORD;
				else if (alignCheck == 32)
					opndx[0].mem_type = MT_YMMWORD;
				else
					opndx[0].mem_type = MT_ZMMWORD;
			}

			if (CodeInfo.token == T_MOVAPS || CodeInfo.token == T_VMOVAPS || CodeInfo.token == T_MOVDQA ||
				CodeInfo.token == T_VMOVDQA || CodeInfo.token == T_MOVAPD || CodeInfo.token == T_VMOVAPD || CodeInfo.token == T_MOVNTDQA || CodeInfo.token == T_VMOVNTDQA) 
			{
				if (opndx[0].sym->state != SYM_STACK && (opndx[0].sym->offset % alignCheck != 0) && Parse_Pass == PASS_2)
					EmitWarn(2, UNALIGNED_SIMD_USE);
			}
		}
	}

	/* ********************************************************* */
	/* Make copy of Code Generation structures for V2 CodeGen.   */
	/* ********************************************************* */
	memcpy(&opndxV2, &opndx, sizeof(opndx));

	/* ********************************************************* */
	/* Process CodeInfo and opndx for legacy CodeGen VEX support */
	/* ********************************************************* */
	for (CurrOpnd = 0; CurrOpnd < j && CurrOpnd < MAX_OPND; CurrOpnd++) 
	{
		Frame_Type = FRAME_NONE;
		SegOverride = NULL; /* segreg prefix is stored in RegOverride */
		CodeInfo.opnd[CurrOpnd].data32l = 0;
		CodeInfo.opnd[CurrOpnd].InsFixup = NULL;

	    /* if encoding is VEX and destination op is XMM, YMM or memory,
		 * the second argument may be stored in the vexregop field. */
		if (CodeInfo.token >= VEX_START && CurrOpnd == OPND2 &&
		   (CodeInfo.opnd[OPND1].type & (OP_XMM | OP_YMM | OP_M | OP_M256 | OP_R32 | OP_R64 | OP_K | OP_ZMM | OP_M64 | OP_M512))) 
		{
			
			CodeInfo.r1type = 10000000;
			CodeInfo.r2type = 10000000;
			if (CodeInfo.token == T_VMOVSD || CodeInfo.token == T_VMOVSS) 
			{
				if (opndx[1].kind == EXPR_CONST)
					return(EmitErr(INVALID_INSTRUCTION_OPERANDS));       
			}
			if (opndx[OPND1].kind == EXPR_REG) 
			{
				regtok = opndx[OPND1].base_reg->tokval;
				CodeInfo.reg1 = GetRegNo(regtok);
				if (opndx[OPND1].idx_reg) 
					CodeInfo.indexreg = opndx[OPND1].idx_reg->bytval;
				if (CodeInfo.reg1 > 15 && IsSimdReg(opndx[OPND1].base_reg))
					CodeInfo.evex_flag = TRUE;
				CodeInfo.r1type = GetValueSp(opndx[OPND1].base_reg->tokval);
				if (CodeInfo.r1type == OP_ZMM) 
				{
					CodeInfo.zreg = 1;
					CodeInfo.evex_flag = TRUE;
				}
			}
			if (opndx[OPND2].kind == EXPR_REG) 
			{
				regtok = opndx[OPND2].base_reg->tokval;
				CodeInfo.reg2 = GetRegNo(regtok);
				if (opndx[OPND2].idx_reg) 
					CodeInfo.indexreg = opndx[OPND2].idx_reg->bytval;
				if (CodeInfo.reg2 > 15 && IsSimdReg(opndx[OPND2].base_reg))
					CodeInfo.evex_flag = TRUE;
				CodeInfo.r2type = GetValueSp(opndx[OPND2].base_reg->tokval);
				if (CodeInfo.r2type == OP_ZMM) 
				{
					CodeInfo.zreg = 1;
					CodeInfo.evex_flag = TRUE;
				}
			}

			if (( (CodeInfo.token == T_ANDN) || (CodeInfo.token == T_MULX) || (CodeInfo.token == T_PEXT) || (CodeInfo.token == T_PDEP)) && (CurrOpnd == OPND2)) goto putinvex;
      
			if (vex_flags[CodeInfo.token - VEX_START] & VX_NND)
				;
			else if ((vex_flags[CodeInfo.token - VEX_START] & VX_IMM) && (opndx[OPND3].kind == EXPR_CONST) && (j > 2))
				;
			else if ((vex_flags[CodeInfo.token - VEX_START] & VX_NMEM) && ((CodeInfo.opnd[OPND1].type & OP_M) ||
				/* v2.11: VMOVSD and VMOVSS always have 2 ops if a memory op is involved */
				((CodeInfo.token == T_VMOVSD || CodeInfo.token == T_VMOVSS) &&
				(opndx[OPND2].kind != EXPR_REG || opndx[OPND2].indirect == TRUE))))
				;
			else 
			{
				if (opndx[OPND2].kind != EXPR_REG || (!(GetValueSp(opndx[CurrOpnd].base_reg->tokval) & (OP_R32 | OP_R64 |OP_K | OP_XMM | OP_YMM | OP_ZMM)))) 
				{
					if ((CodeInfo.token < T_KMOVB) && (CodeInfo.token > T_KMOVW))
						return(EmitErr(INVALID_INSTRUCTION_OPERANDS));
				}
				if (j <= 2) 
				{
					DebugMsg(("ParseLine(%s,%u): avx not enough operands (%u)\n", instr, CurrOpnd, opndx[OPND2].kind, j));
				}
				else

					/* flag VX_DST is set if an immediate is expected as operand 3 */
					if ((vex_flags[CodeInfo.token - VEX_START] & VX_DST) && (opndx[OPND3].kind == EXPR_CONST)) 
					{
						if (opndx[OPND2].idx_reg)
							CodeInfo.indexreg = opndx[OPND2].idx_reg->bytval;
						if (opndx[OPND2].base_reg)
							CodeInfo.basereg = opndx[OPND2].base_reg->bytval;

						/* third operand data goes in CodeInfo.vexconst used in codegen.c */
						CodeInfo.vexconst = opndx[CurrOpnd].value;
						if (opndx[OPND1].base_reg) 
						{
							/* first operand register is moved to vexregop */
							/* handle VEX.NDD */
							CodeInfo.vexregop = opndx[OPND1].base_reg->bytval + 1;
							memcpy(&opndx[OPND1], &opndx[CurrOpnd], sizeof(opndx[0]) * 3);
							CodeInfo.rm_byte = 0;
							if (process_register(&CodeInfo, OPND1, opndx) == ERROR)
								return(ERROR);
						}
					}

					else if (CodeInfo.token < T_VGETMANTPD || CodeInfo.token > T_VGETMANTPS )  
					{
						if (opndx[CurrOpnd].base_reg == NULL)
							return(EmitErr(INVALID_INSTRUCTION_OPERANDS));
            
						flags = GetValueSp(opndx[CurrOpnd].base_reg->tokval);

						if (CodeInfo.opnd[OPND1].type == OP_M)
							; 
						else
			              if ((flags & (OP_XMM | OP_M128)) && (CodeInfo.opnd[OPND1].type & (OP_YMM | OP_M256)) ||
							 (flags & (OP_YMM | OP_M256)) && (CodeInfo.opnd[OPND1].type & (OP_XMM | OP_M128))) 
						  {
								return(EmitErr(INVALID_INSTRUCTION_OPERANDS));
						  }
            
						/* second operand register is moved to vexregop */
						/* to be fixed: CurrOpnd is always OPND2, so use this const here */
						// CodeInfo.vexdata contains I_U8 data of EXPR_CONST
					putinvex:
            
						CodeInfo.vexconst = opndx[CurrOpnd].value;
						if(opndx[CurrOpnd].base_reg)
							CodeInfo.vexregop = opndx[CurrOpnd].base_reg->bytval + 1;
						memcpy(&opndx[CurrOpnd], &opndx[CurrOpnd + 1], sizeof(opndx[0]) * 2);
					}
					else
					{
						CodeInfo.vexconst = opndx[CurrOpnd + 1].value;
						j++;
					}
				j--;
			}
		}

		switch (opndx[CurrOpnd].kind) 
		{
			case EXPR_DECORATOR:
				CodeInfo.evex_sae = opndx[CurrOpnd].saeflags;
				return( codegen( &CodeInfo, oldofs ) );
		
			case EXPR_ADDR:
				if (process_address(&CodeInfo, CurrOpnd, &opndx[CurrOpnd]) == ERROR)
					return(ERROR);
				break;

			case EXPR_CONST:
				if (process_const(&CodeInfo, CurrOpnd, &opndx[CurrOpnd]) == ERROR)
					return(ERROR);
				break;

			case EXPR_REG:
				if (opndx[CurrOpnd].indirect) 
				{ 
					// indirect operand ( "[EBX+...]" )? 
					if (process_address(&CodeInfo, CurrOpnd, &opndx[CurrOpnd]) == ERROR)
						return(ERROR);
				}
				else 
				{
					/* process_register() can't handle 3rd operand */
					if (!CodeInfo.vexregop) 
					{
						if (CurrOpnd == OPND1) 
						{
							regtok = opndx[OPND1].base_reg->tokval;
							CodeInfo.reg1 = GetRegNo(regtok);
							if (CodeInfo.reg1 > 15 && IsSimdReg(opndx[OPND1].base_reg))
								CodeInfo.evex_flag = TRUE;
						}
						else if (CurrOpnd == OPND2) 
						{
							regtok = opndx[OPND2].base_reg->tokval;
							CodeInfo.reg2 = GetRegNo(regtok);
							if (CodeInfo.reg2 > 15 && IsSimdReg(opndx[OPND2].base_reg))
								CodeInfo.evex_flag = TRUE;
						}
					}

					if (CurrOpnd == OPND3) 
					{
						CodeInfo.opnd[OPND3].type = GetValueSp(opndx[OPND3].base_reg->tokval);
						CodeInfo.opnd[OPND3].data32l = opndx[OPND3].base_reg->bytval;
						regtok = opndx[OPND3].base_reg->tokval;
						CodeInfo.reg3 = GetRegNo(regtok);
						if (CodeInfo.reg3 > 15 && IsSimdReg(opndx[OPND3].base_reg))
							CodeInfo.evex_flag = TRUE;
					}

					else if (process_register(&CodeInfo, CurrOpnd, opndx) == ERROR)
						return(ERROR);
				}
				break;
			}
	} /* end for */

	memcpy(&CodeInfoV2, &CodeInfo, sizeof(CodeInfo));
	
	/* If the above loop removed the NDS register for VEX (opnd1[reg], opnd2[nds reg], opnd3[mem/reg], opnd4[imm]) */
	if (CodeInfo.vexregop > 0)
	{
		memcpy(&CodeInfoV2.opnd[OPND4], &CodeInfoV2.opnd[OPND3], sizeof(struct opnd_item));
		memcpy(&CodeInfoV2.opnd[OPND3], &CodeInfoV2.opnd[OPND2], sizeof(struct opnd_item));
		if (process_register(&CodeInfoV2, OPND2, opndxV2) == ERROR)
			return(ERROR);
	}

	/* ******************************************************* */
	/* 4 arguments are valid for AVX only                      */
	/* ******************************************************* */
	if (CurrOpnd != j) 
	{
		for (; tokenarray[i].token != T_COMMA; i--);
    if (CodeInfo.token < VEX_START) {
      return(EmitErr(SYNTAX_ERROR_EX, tokenarray[i].tokpos));
    }
		else
			if ((CodeInfo.token == T_VMASKMOVPS || CodeInfo.token == T_VMASKMOVPD) && (j < 3))
				return(EmitErr(MISSING_OPERATOR_IN_EXPRESSION));
	}
	if (CodeInfo.token == T_VBLENDVPS || CodeInfo.token == T_VBLENDVPD) 
	{
		if (CodeInfo.opnd[OPND3].type == OP_NONE)
			return (EmitErr(MISSING_OPERATOR_IN_EXPRESSION));
	}

	/* ******************************************************* */
	/* for FAR calls/jmps some special handling is required:
	* in the instruction tables, the "far" entries are located BEHIND
	* the "near" entries, that's why it's needed to skip all items
	* until the next "first" item is found. */
	/* ******************************************************* */
	if (CodeInfo.isfar) 
	{
		if (CodeInfo.token == T_CALL || CodeInfo.token == T_JMP) 
		{
			do 
			{
				CodeInfo.pinstr++;
			} while (CodeInfo.pinstr->first == FALSE);
		}
	}

	/* ******************************************************* */
	/* special handling for string instructions                */
	/* ******************************************************* */
	if (CodeInfo.pinstr->allowed_prefix == AP_REP || CodeInfo.pinstr->allowed_prefix == AP_REPxx) 
	{
		HandleStringInstructions(&CodeInfo, opndx);
	#if SVMSUPP /* v2.09, not active because a bit too hackish yet - it "works", though. */
	} 
	else if ( CodeInfo.token >= T_VMRUN && CodeInfo.token <= T_INVLPGA && CodeInfo.pinstr->opclsidx ) {
		/* the size of the first operand is to trigger the address size byte 67h,
		* not the operand size byte 66h! */
		CodeInfo.prefix.adrsiz = CodeInfo.prefix.opsiz;
		CodeInfo.prefix.opsiz = 0;
		/* the first op must be EAX/AX or RAX/EAX. The operand class
		* used in the instruction table is OP_A ( which is AL/AX/EAX/RAX ). */
		if ( ( CodeInfo.opnd[OPND1].type & ( CodeInfo.Ofssize == USE64 ? OP_R64 | OP_R32 : OP_R32 | OP_R16 ) ) == 0 ) {
			DebugMsg(("ParseLine(%s): opnd1 unexpected type=%X\n", instr, CodeInfo.opnd[OPND1].type ));
			return( EmitErr( INVALID_INSTRUCTION_OPERANDS ) );
		}
		/* the INVLPGA instruction has a fix second operand (=ECX). However, there's no
		 * operand class for ECX alone. So it has to be ensured here that the register IS ecx. */
		if ( CodeInfo.token == T_INVLPGA )
			if ( ( CodeInfo.rm_byte & BIT_345 ) != ( 1 << 3 ) ) { /* ECX is register 1 */
				DebugMsg(("ParseLine(%s): opnd2 is not ecx\n", instr ));
				return( EmitErr( INVALID_INSTRUCTION_OPERANDS ) );
			}
	#endif
	}
	else 
	{
		if (CurrOpnd > 1) 
		{
			/* v1.96: check if a third argument is ok */
			if (CurrOpnd > 2) 
			{
				do 
				{
					if ((opnd_clstab[CodeInfo.pinstr->opclsidx].opnd_type_3rd != OP3_NONE) || (opndx[CurrOpnd].kind == EXPR_DECORATOR)) 
					{
						if (opndx[CurrOpnd].kind == EXPR_DECORATOR)
							CodeInfo.evex_sae = opndx[CurrOpnd].saeflags;
						break;
					}
          /* workaround for codegenv2 because there is no CodeInfo.pinstr, we have only instruction token 
           * To do: find the way to avoid CodeInfo.pinstr */
          if (CodeInfo.opnd[OPND3].type == OP_I8) {
            switch (CodeInfo.token) {
            case T_CMPPD:
            case T_CMPPS:
            case T_CMPSD:
            case T_CMPSS:
            case T_DPPD:
            case T_DPPS:
            case T_EXTRACTPS:
			case T_INSERTPS:
            case T_VCMPPD:
            case T_VCMPPS:
            case T_VCMPSD:
            case T_VCMPSS:
            case T_VDPPD:
            case T_VDPPS:
            case T_PCLMULQDQ:
            case T_VPCLMULQDQ:
            case T_VEXTRACTPS:
			case T_VINSERTPS:
              goto noterror;
            }
          }
					CodeInfo.pinstr++; 
					if ((CodeInfo.pinstr->first == TRUE)) 
					{
						for (; tokenarray[i].token != T_COMMA; i--);
						return(EmitErr(SYNTAX_ERROR_EX, tokenarray[i].tokpos));
					}
				} while (1);
			}
   noterror:   
			/* v2.06: moved here from process_const() */
			if (CodeInfo.token == T_IMUL) 
			{

				/* the 2-operand form with an immediate as second op
				 * is actually a 3-operand form. That's why the rm byte
				 * has to be adjusted. */
				if (CodeInfo.opnd[OPND3].type == OP_NONE && (CodeInfo.opnd[OPND2].type & OP_I)) 
				{
					CodeInfo.prefix.rex |= ((CodeInfo.prefix.rex & REX_B) ? REX_R : 0);
			        CodeInfo.rm_byte = (CodeInfo.rm_byte & ~BIT_345) | ((CodeInfo.rm_byte & BIT_012) << 3);
				}
				else if ((CodeInfo.opnd[OPND3].type != OP_NONE) && (CodeInfo.opnd[OPND2].type & OP_I) && CodeInfo.opnd[OPND2].InsFixup &&
						 CodeInfo.opnd[OPND2].InsFixup->sym->state == SYM_UNDEFINED)
					CodeInfo.opnd[OPND2].type = OP_M;
			}

			if (check_size(&CodeInfo, opndx) == ERROR) 
				return(ERROR);

		}

		if (CodeInfo.Ofssize == USE64) 
		{

			if (CodeInfo.x86hi_used && CodeInfo.prefix.rex)
				EmitError(INVALID_USAGE_OF_AHBHCHDH);

		  /* for some instructions, the "wide" flag has to be removed selectively.
		   * this is to be improved - by a new flag in struct instr_item. */
			switch (CodeInfo.token) 
			{
				case T_PUSH:
				case T_POP:
					/* v2.06: REX.W prefix is always 0, because size is either 2 or 8 */
					CodeInfo.prefix.rex &= 0x7;
					break;
				case T_CALL:
				case T_JMP:
			#if VMXSUPP /* v2.09: added */
				case T_VMREAD:
				case T_VMWRITE:
			#endif
					/* v2.02: previously rex-prefix was cleared entirely,
					* but bits 0-2 are needed to make "call rax" and "call r8"
					* distinguishable! */
					CodeInfo.prefix.rex &= 0x7;
					break;
				case T_MOV:
					/* don't use the Wide bit for moves to/from special regs */
					if (CodeInfo.opnd[OPND1].type & OP_RSPEC || CodeInfo.opnd[OPND2].type & OP_RSPEC)
						CodeInfo.prefix.rex &= 0x7;
					break;
				case  T_POR:
				case T_VPOR:
					if (gmaskflag)
						goto nopor;
					break;
			}
		}
	}
    
    /* UASM 2.56 prevent RIP+REG encodings */
    for (i = 0; i < 4; i++) {
        if (opndx[i].base_reg != NULL && opndx[i].idx_reg != NULL) {
            if (opndx[i].base_reg->tokval == T_RIP && opndx[i].idx_reg != NULL) {
                return EmitErr(RIP_ONLY);
            }
        }
    }

    /* *********************************************************** */
	/* Use the V2 CodeGen, else fallback to the standard CodeGen   */
	/* *********************************************************** */
	if (ModuleInfo.Ofssize == USE32 || ModuleInfo.Ofssize == USE64)
	{
		temp = CodeGenV2(opcodePtr, &CodeInfoV2, oldofs, opndCount, opndxV2);
		if (temp == EMPTY)
			temp = codegen(&CodeInfo, oldofs);
	}
	else
		temp = codegen(&CodeInfo, oldofs);

nopor:
	/* now reset EVEX maskflags for the next line */
	decoflags  = 0;
	broadflags = 0;
	evexflag   = 0;

	return( temp );
}

/* process a file. introduced in v2.11 */
void ProcessFile( struct asm_tok tokenarray[] )
/*********************************************/
{
	/* Initialize xmmword override tokens each pass */
	xmmOver0.token = 6;
	xmmOver0.specval = 15;
	xmmOver0.floattype = 15;
	xmmOver0.numbase = 15;
	xmmOver0.string_delim = 15;
	xmmOver0.precedence = 15;
	xmmOver0.bytval = 15;
	xmmOver0.dirtype = 15;
	xmmOver0.tokval = T_XMMWORD;
	xmmOver0.string_ptr = "xmmword";
	xmmOver0.stringlen = T_XMMWORD;
	xmmOver0.idarg = T_XMMWORD;
	xmmOver0.itemlen = T_XMMWORD;
	xmmOver0.lastidx = T_XMMWORD;

	xmmOver1.token = 5;
	xmmOver1.specval = 4;
	xmmOver1.floattype = 4;
	xmmOver1.numbase = 4;
	xmmOver1.string_delim = 4;
	xmmOver1.precedence = 4;
	xmmOver1.bytval = 4;
	xmmOver1.dirtype = 4;
	xmmOver1.tokval = T_PTR;
	xmmOver1.string_ptr = "ptr";
	xmmOver1.stringlen = T_PTR;
	xmmOver1.idarg = T_PTR;
	xmmOver1.itemlen = T_PTR;
	xmmOver1.lastidx = T_PTR;

	dsOver.token = 2;
	dsOver.dirtype = 3;
	dsOver.bytval = 3;
	dsOver.precedence = 3;
	dsOver.string_delim = 3;
	dsOver.floattype = 3;
	dsOver.numbase = 3;
	dsOver.specval = 3;
	dsOver.string_ptr = "ds";
	dsOver.tokval = 0x0000001c;
	dsOver.stringlen = 0x0000001c;
	dsOver.idarg = 0x0000001c;
	dsOver.itemlen = 0x0000001c;
	dsOver.lastidx = 0x0000001c;

    if ( ModuleInfo.EndDirFound == FALSE && GetTextLine( CurrSource ) ) 
	{
		if (CurrSource[0] == 0xEF && CurrSource[1] == 0xBB && CurrSource[2] == 0xBF)
			strcpy(CurrSource, &CurrSource[3]);
		do
		{
			if (PreprocessLine(CurrSource, tokenarray))
			{
				ParseLine(tokenarray);
				if (Options.preprocessor_stdout == TRUE && Parse_Pass == PASS_1)
					WritePreprocessedLine(CurrSource);
			}
		} while (ModuleInfo.EndDirFound == FALSE && GetTextLine(CurrSource));
    }
    return;
}

