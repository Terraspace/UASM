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
* Description:  instruction encoding, scans opcode table and emits code.
*
****************************************************************************/

#include <limits.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "codegen.h"
#include "fixup.h"
#include "fpfixup.h"
#include "segment.h"
#include "input.h"
#include "listing.h"
#include "reswords.h"

extern const struct opnd_class opnd_clstab[];
#if AVXSUPP
extern struct ReservedWord  ResWordTable[];
extern const uint_8               vex_flags[];
#endif

const char szNull[] = {"<NULL>"};

/* v2.03: OutputCodeByte no longer needed */
#define OutputCodeByte( x ) OutputByte( x )

/* segment order must match the one in special.h */
enum prefix_reg {
    PREFIX_ES = 0x26,
    PREFIX_CS = 0x2E,
    PREFIX_SS = 0x36,
    PREFIX_DS = 0x3E,
    PREFIX_FS = 0x64,
    PREFIX_GS = 0x65
};

/* Find size for Compressed byte displacement  */
uint_8 GetByteDisp(const struct code_info *CodeInfo)
{
    const uint_8 fvarr[2][2][3] = {{{16, 32, 64}, {4, 4, 4}},    // Full Vector (FV)
                                  {{16, 32, 64}, {8, 8, 8}}};
    const uint_8 hvarr[2][3]    =  {{8, 16, 32}, {4, 4, 4}};     // Half Vector (HV) 
    const uint_8 duparr[3]      =   {8, 32, 64};                 // VMOVDDUP    (DUP)
                                                  //RXBR00MM
    uint_8 n = 0;
    bool evexW            = (CodeInfo->evex_p1 & EVEX_P1WMASK) >> 7;
    enum ttypes   tuple   = CodeInfo->pinstr->prefix & 0x1F;
    bool evexB            = (CodeInfo->evex_p2 & EVEX_P2BMASK) >> 4;
    uint_8  vctln         = (CodeInfo->evex_p2 & EVEX_P2LLMASK) >> 5;
    

    switch(tuple) {
    case FV:         // Full Vector 
        n = fvarr[evexW][evexB][vctln];
        break;
    case HV:        // Half Vector 
        n = hvarr[evexB][vctln];
        break;
    case FVM:       // Full Vector Mem
        n = 1 << (vctln + 4);
        break;
    case T1S8:      // Tuple1 Scalar
    case T1S16: 
        n = tuple - T1S8 + 1;
        break;
    case T1S:
        n = evexW ? 8 : 4;
        break;
    case T1F32:    // Tuple1 Fixed
    case T1F64:
        n = (tuple == T1F32 ? 4 : 8);
        break;
    case T2:       // Tuple2
    case T4:       // Tuple4
    case T8:       // Tuple8
        if (vctln + 7 <= (evexW + 5) + (tuple - T2 + 1))
            n = 0;
        else
            n = 1 << (tuple - T2 + evexW + 3);
        break;
    case HVM:      // Half Mem
    case QVM:      // QuarterMem
    case OVM:      // OctMem
        n = 1 << (OVM - tuple + vctln + 1);
        break;
    case T128:     // Mem128
        n = 16;
        break;
    case DUP:      // MOVDDUP
        n = duparr[vctln];
        break;

    default:
        break;
    }
    return n;
}

 /* Check if compressed displacement is available and stored it in comprdsp */
bool Check4CompDisp8(const struct code_info *CodeInfo, int_8 *comprdsp,int *d, int disp)
{
    int_32 disp32           = disp;
    uint_8 n;
    int_32 disp8;
    if (CodeInfo->evex_flag){  //Do it only for EVEX instructions
      n = GetByteDisp(CodeInfo);
      *d = n;
      if (n && !(disp32 & (n - 1))) {
        disp8 = disp32 / n;
        /* if it fits in Disp8 */
        if (disp8 >= -128 && disp8 <= 127) {
          *comprdsp = disp8;
          return TRUE;
          }
        }
      }
    *comprdsp = 0;
    return FALSE;
}

static const char sr_prefix[] =
    { PREFIX_ES, PREFIX_CS, PREFIX_SS, PREFIX_DS, PREFIX_FS, PREFIX_GS };

static void output_opc(struct code_info *CodeInfo)
/**************************************************/
/*
 * - determine what code should be output and their order.
 * - output prefix bytes:
 *    - LOCK, REPxx,
 *    - FWAIT (not a prefix, but handled like one)
 *    - address size prefix 0x67
 *    - operand size prefix 0x66
 *    - segment override prefix, branch hints
 * - output opcode (1-3), "mod r/m" and "s-i-b" bytes.
 *
 * Note that jwasm follows Masm strictly here, even if it
 * contradicts Intel docs. For example, Masm always emits
 * the F2/F3/66 byte before a segment prefix, even if the
 * F2/F3/66 byte is a "mantadory prefix".
 */
{
  const struct instr_item *ins = CodeInfo->pinstr;
  uint_8           tmp;
  uint_8           fpfix = FALSE;
  int              rn;
  unsigned char    c;
  int_8            comprdsp = 0;

  DebugMsg1(("output_opc enter, ins.opc/rm=%X/%X, byte1_info=%X CodeInfo->rm=%X opsiz=%u\n", ins->opcode, ins->rm_byte, ins->byte1_info, CodeInfo->rm_byte, CodeInfo->prefix.opsiz));
  /*
   * Output debug info - line numbers
   */
  if (Options.line_numbers)
    AddLinnumDataRef(get_curr_srcfile(), GetLineNumber());
  /* if it's a FPU instr, reset opsiz */
  //if( ins->cpu & P_FPU_MASK ) {
  /* v2.02: if it's a FPU or MMX/SSE instr, reset opsiz!
   * [this code has been moved here from codegen()]
   */
  if (ins->cpu & (P_FPU_MASK | P_MMX | P_SSEALL)) {
#if SSE4SUPP
    /* there are 2 exceptions. how to avoid this ugly hack? */
    if (CodeInfo->token != T_CRC32 &&
      CodeInfo->token != T_POPCNT)
#endif
      CodeInfo->prefix.opsiz = FALSE;
  }
  if ((CodeInfo->token == T_RDRAND) || (CodeInfo->token == T_RDSEED)){
    if ((CodeInfo->opnd[OPND1].type == OP_R16) || (CodeInfo->opnd[OPND1].type == OP_AX))
      CodeInfo->prefix.opsiz = TRUE;
  } 
  /*
   * Check if CPU, FPU and extensions are within the limits
   */
  if ((ins->cpu & P_CPU_MASK) > (ModuleInfo.curr_cpu & P_CPU_MASK)
    || (ins->cpu & P_FPU_MASK) > (ModuleInfo.curr_cpu & P_FPU_MASK)
    || (ins->cpu & P_EXT_MASK) > (ModuleInfo.curr_cpu & P_EXT_MASK)) {
    DebugMsg(("output_opc: wrong cpu setting: instr.cpu=%X, ModuleInfo.cpu=%X\n",
      ins->cpu, ModuleInfo.curr_cpu));
    /* if instruction is valid for 16bit cpu, but operands aren't,
     then display a more specific error message! */
    if (ins->cpu == P_386 &&
      ((InstrTable[IndexFromToken(CodeInfo->token)].cpu & P_CPU_MASK) <= P_386))
      EmitError(INSTRUCTION_FORM_REQUIRES_80386);
    else
      EmitError(INSTRUCTION_OR_REGISTER_NOT_ACCEPTED_IN_CURRENT_CPU_MODE);
    //return( ERROR );
  }
    //if (CodeInfo->token == T_VMULSS)
    //  __debugbreak();

  /*
   * Output FP fixup if required
   * the OPs with NOWAIT are the instructions beginning with
   * FN, except FNOP.
   * the OPs with WAIT are the instructions:
   * FCLEX, FDISI, FENI, FINIT, FSAVEx, FSTCW, FSTENVx, FSTSW
   */
  if ((ModuleInfo.emulator == TRUE) &&
    (CodeInfo->Ofssize == USE16) &&
    (ins->cpu & P_FPU_MASK) &&
    (ins->allowed_prefix != AP_NO_FWAIT)) {
    fpfix = TRUE;
    /* v2.04: no error is returned */
    AddFloatingPointEmulationFixup(CodeInfo);
  }
#if AVXSUPP
      /* If VMOVSS or VMOVSD, AVX instructions should have 3 operands if registers used, fix for v2.31 */
    if (CodeInfo->token == T_VMOVSS || CodeInfo->token == T_VMOVSD){
      if (CodeInfo->reg3 == 0xff){
        if (CodeInfo->pinstr->opcode == 0x10 && (CodeInfo->opnd[OPND2].type & OP_M))
          ;/* that is good, there is no third operand for memory instruction */
        else if (CodeInfo->pinstr->opcode == 0x11 && (CodeInfo->opnd[OPND1].type & OP_M) )
            ;/* that is good, there is no third operand for memory instruction */
        else {
            EmitErr(INVALID_INSTRUCTION_OPERANDS);
           }
        }
      }
#endif
   /*
   * Output instruction prefix LOCK, REP or REP[N]E|Z
   */
  if (CodeInfo->prefix.ins != EMPTY && (CodeInfo->token < T_VPGATHERDD || CodeInfo->token > T_VGATHERQPS)) {
    tmp = InstrTable[IndexFromToken(CodeInfo->prefix.ins)].allowed_prefix;
    /* instruction prefix must be ok. However, with -Zm, the plain REP
     * is also ok for instructions which expect REPxx.
     */
    /* if (ModuleInfo.m510 == TRUE && tmp == AP_REP && ins->allowed_prefix == AP_REPxx) */
	/* UASM 2.50 Allow REP in all cases without -Zm */
	if (tmp == AP_REP && ins->allowed_prefix == AP_REPxx)
      tmp = AP_REPxx;

    if (ins->allowed_prefix != tmp) {
      EmitError(INSTRUCTION_PREFIX_NOT_ALLOWED);
    }
    else
      OutputCodeByte(InstrTable[IndexFromToken(CodeInfo->prefix.ins)].opcode);
  }
  /*
   * Output FP FWAIT if required
   */
  if (ins->cpu & P_FPU_MASK) {
    if (CodeInfo->token == T_FWAIT) {
      /* v2.04: Masm will always insert a NOP if emulation is active,
       * no matter what the current cpu is. The reason is simple: the
       * nop is needed because of the fixup which was inserted.
       */
      //if(( ModuleInfo.curr_cpu & P_CPU_MASK ) < P_386 ) {
      //    if(( ModuleInfo.emulator == TRUE ) && ( CodeInfo->Ofssize == USE16 )) {
      if (fpfix) {
        OutputCodeByte(OP_NOP);
      }
    }
    else if (fpfix || ins->allowed_prefix == AP_FWAIT) {
      OutputCodeByte(OP_WAIT);
    }
    else if (ins->allowed_prefix != AP_NO_FWAIT) {
      /* implicit FWAIT synchronization for 8087 (CPU 8086/80186) */
      if ((ModuleInfo.curr_cpu & P_CPU_MASK) < P_286)
        OutputCodeByte(OP_WAIT);
    }
  }
  /*
   * check if address/operand size prefix is to be set
   */
  switch (ins->byte1_info) {
  case F_16:
    if (CodeInfo->Ofssize >= USE32) CodeInfo->prefix.opsiz = TRUE;
    break;
  case F_32:
    if (CodeInfo->Ofssize == USE16) CodeInfo->prefix.opsiz = TRUE;
    break;
  case F_16A: /* 16-bit JCXZ and LOOPcc */
    /* doesnt exist for IA32+ */
    if (CodeInfo->Ofssize == USE32) CodeInfo->prefix.adrsiz = TRUE;
    break;
  case F_32A: /* 32-bit JECXZ and LOOPcc */
#if AMD64_SUPPORT
    /* in IA32+, the 32bit version gets an 0x67 prefix */
    if (CodeInfo->Ofssize != USE32)  CodeInfo->prefix.adrsiz = TRUE;
#else
    if( CodeInfo->Ofssize == USE16 ) CodeInfo->prefix.adrsiz = TRUE;
#endif
    break;
  case F_0FNO66:
    CodeInfo->prefix.opsiz = FALSE;
    break;
#if AMD64_SUPPORT
  case F_48:
  case F_480F:
    CodeInfo->prefix.rex |= REX_W;
    break;
#endif
  }


#if AVXSUPP  
      if ((CodeInfo->token >= T_VSHUFF32X4) && (CodeInfo->token <= T_VSHUFI64X2) &&
      ((CodeInfo->opnd[OPND1].type & OP_XMM) || (CodeInfo->opnd[OPND2].type & OP_XMM)))
      EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS); //Only YMM and ZMM alowed    
	/* John: removed once kn and decorator flag masks were determined not to be required as k0 is implicit */
	 if ((CodeInfo->token >= T_VBROADCASTF128) && (CodeInfo->token <= T_VPBROADCASTQ)) {
		if (decoflags == 0 && CodeInfo->r1type != OP_K)
        CodeInfo->evex_flag = 0;
	}
   /* check if NDS register is present, v2.46.11*/
    //if (CodeInfo->evex_flag == FALSE) {
      switch (CodeInfo->token){
        case   T_VADDPD:
        case   T_VADDSD:
        case   T_VDIVPD:
        case   T_VDIVSD:
        case   T_VMAXPD:
        case   T_VMAXSD:
        case   T_VMINPD:
        case   T_VMINSD:
        case   T_VMULPD:
        case   T_VMULSD:
        case   T_VSQRTSD:
        case   T_VSUBPD:
        case   T_VSUBSD:
        case   T_VADDPS:
        case   T_VADDSS:
        case   T_VDIVPS:
        case   T_VDIVSS:
        case   T_VMAXPS:
        case   T_VMAXSS:
        case   T_VMINPS:
        case   T_VMINSS:
        case   T_VMULPS:
        case   T_VMULSS:
        case   T_VSQRTSS:
        case   T_VSUBPS:
        case   T_VSUBSS:
        case   T_VCMPPD:
        case   T_VCMPSD:
        case   T_VCMPPS:
        case   T_VCMPSS:
        case   T_VXORPD: 
        case   T_VORPS: 
        case   T_VXORPS:
        /*case   T_VPSLLDQ:
          case   T_VPSRLDQ:
          case   T_VPSLLW:
          case   T_VPSLLD:
          case   T_VPSLLQ:
          case   T_VPSRAW:
          case   T_VPSRAD:
          case   T_VPSRAQ:
          case   T_VPSRLW:
          case   T_VPSRLD:
          case   T_VPSRLQ:*/
        if (CodeInfo->r2type == OP_XMM || CodeInfo->r2type == OP_YMM || CodeInfo->r2type == OP_ZMM)
          break;
          EmitError(INVALID_INSTRUCTION_OPERANDS);
        }
      //}
      /* AVX512 instructions only, the first parameter must be Kn register:
        VPCMPB,VPCMPUB,VPCMPD,VPCMPUD,VPCMPQ,VPCMPUQ,VPCMPW,VPCMPUW */
      switch (CodeInfo->token){
        case   T_VPCMPD:
        case   T_VPCMPUD:
        case   T_VPCMPQ:
        case   T_VPCMPUQ:
        case   T_VPCMPW:
        case   T_VPCMPUW:
        case   T_VPCMPB:
        case   T_VPCMPUB:
          if (CodeInfo->r1type == OP_K)
          break;
          EmitError(INVALID_INSTRUCTION_OPERANDS);
      }
   /*	if (CodeInfo->token >= T_VPORD && CodeInfo->token <= T_PSRLDQ){
		if (decoflags == 0 && CodeInfo->r1type != OP_K)
        CodeInfo->evex_flag = 0;
	}
  	if (CodeInfo->token == T_VCVTPH2PS || CodeInfo->token == T_VCVTPS2PD ||
        CodeInfo->token == T_VRANGEPD ||CodeInfo->token == T_VRANGEPS ||
        CodeInfo->token == T_VPTESTNMD ||CodeInfo->token == T_VPTESTNMQ ||
        CodeInfo->token == T_VPERM2I128) {

		if (decoflags == 0 && CodeInfo->r1type != OP_K)
	        CodeInfo->evex_flag = 0;

	}*/
      /* these are only EVEX instructions, v2.46 */
  if ((CodeInfo->pinstr->prefix & 0xF00) == IZSZ || (evexflag == TRUE))
	  CodeInfo->evex_flag = TRUE;
  if (!evex){
	  CodeInfo->evex_flag = FALSE;
    if (ResWordTable[CodeInfo->token].flags & RWF_VEX) {
      if ((CodeInfo->reg1 > 15 && CodeInfo->reg1 < 32) || 
          (CodeInfo->reg2 > 15 && CodeInfo->reg2 < 32) ||
          (CodeInfo->reg3 > 15 && CodeInfo->reg3 < 32) ||
          CodeInfo->r1type == OP_ZMM || CodeInfo->r2type == OP_ZMM)
          EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
      }
    }

  if (CodeInfo->evex_flag == TRUE) {
	  if (!(vex_flags[CodeInfo->token - VEX_START] & VX_LL))
		  EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
  }
    if (CodeInfo->token == T_VCMPSD || CodeInfo->token == T_VCMPSS){
      if ( (CodeInfo->r1type > OP_XMM || CodeInfo->r2type > OP_XMM) && CodeInfo->opnd[OPND1].type != OP_K )
          EmitError(INVALID_OPERAND_SIZE);
    }
    if ((CodeInfo->token >= T_VCMPEQSD && CodeInfo->token <= T_VCMPTRUE_USSD)||
      (CodeInfo->token >= T_VCMPEQSS && CodeInfo->token <= T_VCMPTRUE_USSS)){
      if ((CodeInfo->r1type > OP_XMM || CodeInfo->r2type > OP_XMM) && CodeInfo->opnd[OPND1].type != OP_K )
          EmitError(INVALID_OPERAND_SIZE);
  }

  if (!(ResWordTable[CodeInfo->token].flags & RWF_VEX)) {
#endif

	switch (ins->byte1_info) {
    case F_660F:
    case F_660F38:
    case F_660F3A:
      CodeInfo->prefix.opsiz = TRUE;
      break;
    case F_F20F:
    case F_F20F38: OutputCodeByte(0xF2); break;
    case F_F3: /* PAUSE instruction */
    case F_F30F:   OutputCodeByte(0xF3); break;
    }
#if AVXSUPP
  }
#endif
  /*
   * Output address and operand size prefixes.
   * These bytes are NOT compatible with FP emulation fixups,
   * which expect that the FWAIT/NOP first "prefix" byte is followed
   * by either a segment prefix or the opcode byte.
   * Neither Masm nor Uasm emit a warning, though.
   */
  
  if (CodeInfo->prefix.adrsiz == TRUE && (CodeInfo->token < T_VPGATHERDD || CodeInfo->token > T_VSCATTERQPD)&&
      CodeInfo->token != T_VCVTPH2PS && CodeInfo->token != T_VCVTPS2PD) {

	  if (CodeInfo->basereg == 0x10) /* RIP used for relative addressing v2.36 */
		  ;/* don't output 0x67 */
	  else
		  OutputCodeByte(ADRSIZ);
    
#ifdef DEBUG_OUT
    if (fpfix)
      DebugMsg(("output_opc: ERROR: FP emulation byte sequence destroyed by 32-bit address prefix!\n"));
#endif
  }
  if (CodeInfo->prefix.opsiz == TRUE) {
#if 1
    if ((ModuleInfo.curr_cpu & P_CPU_MASK) < P_386) {
      DebugMsg(("output_opc: instruction form requires 386\n"));
      EmitError(INSTRUCTION_FORM_REQUIRES_80386);
      //return( ERROR ); /* v2.06: don't skip instruction */
    }
#endif
	if (CodeInfo->token == T_MOVQ && CodeInfo->basereg != 0x10) {
		if (CodeInfo->opnd[OPND1].type == OP_XMM && (CodeInfo->opnd[OPND2].type & OP_MS)) {
			CodeInfo->prefix.opsiz = FALSE;
			OutputCodeByte(0xF3);
		}
		else if ((CodeInfo->opnd[OPND1].type & OP_MS) && CodeInfo->opnd[OPND2].type == OP_XMM) {
			CodeInfo->prefix.opsiz = TRUE;
			OutputCodeByte(OPSIZ);
		}
		else if ((CodeInfo->opnd[OPND1].type == OP_XMM) && (CodeInfo->opnd[OPND2].type & OP_R64)) {
			CodeInfo->prefix.opsiz = TRUE;
			OutputCodeByte(OPSIZ);
		}
		else if ((CodeInfo->opnd[OPND2].type == OP_XMM) && (CodeInfo->opnd[OPND1].type & OP_R64)) {
			CodeInfo->prefix.opsiz = TRUE;
			OutputCodeByte(OPSIZ);
		}
	}
	else
		OutputCodeByte(OPSIZ);
  }
  /*
   * Output segment prefix
   */
  if (CodeInfo->prefix.RegOverride != EMPTY) {
    OutputCodeByte(sr_prefix[CodeInfo->prefix.RegOverride]);
  }
  if (ins->opnd_dir) {
    /* The reg and r/m fields are backwards */
    tmp = CodeInfo->rm_byte;
    CodeInfo->rm_byte = (tmp & 0xc0) | ((tmp >> 3) & 0x7) | ((tmp << 3) & 0x38);
#if AMD64_SUPPORT
    tmp = CodeInfo->prefix.rex;
    CodeInfo->prefix.rex = (tmp & 0xFA) | ((tmp & REX_R) >> 2) | ((tmp & REX_B) << 2);
#endif
  }
    //if (CodeInfo->token == T_VGATHERPF0DPD)
    //  __debugbreak();

#if AVXSUPP
       if (CodeInfo->indextype == OP_XMM || CodeInfo->indextype == OP_YMM || CodeInfo->indextype == OP_ZMM) {
         if (CodeInfo->token >= T_VPGATHERDD && CodeInfo->token <= T_VSCATTERQPD)
           ;
        else
          EmitErr( AVX_INDEX_REGISTERS_NOT_ALLOWED_HERE );
        }
       /* ensure missuse of operand types v2.46 */
      if (CodeInfo->token >= T_VFMADD132PD && CodeInfo->token <= T_VFNMSUB231SS){
         if (CodeInfo->opnd[OPND1].type == CodeInfo->opnd[OPND2].type)
           ;/* that is OK */
         else if (CodeInfo->opnd[OPND2].type & OP_M_ANY)
           ;/* that is OK */
         else 
           EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
        }
/* This is a fix for the memory type and register size v2.46 
   -----------------------------------------------------------------*/
     if ((CodeInfo->token >= T_ADDPD && CodeInfo->token <= T_SUBPS )||
           (CodeInfo->token >= T_VADDPD && CodeInfo->token <= T_VSUBPS )){
        if (CodeInfo->evex_flag == TRUE) {
          if (CodeInfo->opnd[OPND2].type & OP_M_ANY){
            CodeInfo->prefix.rex |= EVEX_P0XMASK;  /* set X in RXB */
            if (CodeInfo->opnd[OPND2].data32l){
              CodeInfo->rm_byte &= ~MOD_11;          /* clear MOD    */
              CodeInfo->rm_byte |= MOD_10;           /* set disp32   */
              }
            }
          }
      if (CodeInfo->opnd[OPND2].type !=  CodeInfo->opnd[OPND1].type){
          if (CodeInfo->opnd[OPND1].type & OP_M_ANY || CodeInfo->opnd[OPND2].type & OP_M_ANY)
            ;
          else
            EmitError(INVALID_OPERAND_SIZE);
        }
    }
  /* ---------------------------------------------------------------*/
  if (ResWordTable[CodeInfo->token].flags & RWF_VEX) {
    uint_8 lbyte = 0;
    if (CodeInfo->evex_flag){
      lbyte |= 0x4;              //bite 3 must be set in P2 WVVVV1PP 
    }
    switch (ins->byte1_info) {
    case F_660F:
    case F_660F38:
    case F_660F3A:
      lbyte |= 0x01;
      break;
    case F_F30F:
    case F_F30F38:
      lbyte |= 0x02;
      break;
    case F_F20F:
    case F_F20F38:
      lbyte |= 0x03;
      break;
    }
    if (CodeInfo->vexregop)
      lbyte |= ((16 - CodeInfo->vexregop) << 3);
    else {
      lbyte |= EVEX_P1VVVV;
      CodeInfo->evex_p2 |= EVEX_P2VMASK;
    }



  /* If there is no decoflags then it is AVX2 instruction with 3 parameters, Uasm 2.15 */
  if (CodeInfo->token >= T_VBROADCASTSS && CodeInfo->token <= T_VPBROADCASTMW2D)
      {
      if (decoflags == 0 && CodeInfo->r1type != OP_K){               /* added code bellow underlined v2.46 */
      if ((CodeInfo->reg1 <= 15 && CodeInfo->r1type != OP_ZMM) && ((CodeInfo->pinstr->prefix & 0xF00) != IZSZ))
        CodeInfo->evex_flag = 0;                                    /*---------------------------------------*/
      else{
        CodeInfo->evex_flag = 1;
        lbyte |= 4;
        }
      }
    }
  if (evexflag == TRUE)
	  CodeInfo->evex_flag = TRUE;

  /* If a Kn mask register not present than it is AVX2 instruction v2.38 */
    if (CodeInfo->token >= T_VPGATHERDD && CodeInfo->token <= T_VGATHERQPS)
    {
    if (decoflags == 0){
      if (CodeInfo->reg1 <= 15 && CodeInfo->reg3 <= 15 && CodeInfo->zreg == 0) /* fix for ZMM v2.38 */
        CodeInfo->evex_flag = 0;
      else EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
      /* Check if any pair of the index, mask, or destination registers are not the same,
        otherwise this instruction results a GP fault. v2.38 */
      if (CodeInfo->reg1 == CodeInfo->reg3 || CodeInfo->reg1 == CodeInfo->indexreg||
          CodeInfo->reg3 == CodeInfo->indexreg)
          EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
      }
    }
    /* All these instrctions need a Kn mask register present, v2.38 */
    if ((CodeInfo->token >= T_VGATHERPF0DPS && CodeInfo->token <= T_VSCATTERQPD)&&(decoflags == 0))
        EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);

    /* VCVTTSS2SI can only be used with XMM registers, Uasm 2.16 */
    if (CodeInfo->token == T_VCVTTSS2SI || CodeInfo->token == T_VCVTSS2SD){
      if (CodeInfo->r2type == OP_YMM || CodeInfo->r2type == OP_ZMM )
        EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
      }
    /* Check size of added missing instructions VRCP28SD, VRCP28SS, VRCP28PD, VRCP28PS 
     VRSQRT28PD, VRSQRT28PS, VRSQRT28SD, VRSQRT28SS, VEXP2PD, VEXP2PS Uasm 2.16  */
    switch (CodeInfo->token){
      case   T_VRCP28SD:
      case T_VRSQRT28SD:
        if (CodeInfo->mem_type != MT_EMPTY && CodeInfo->mem_type != MT_QWORD )
          goto error;
        if ((CodeInfo->r1type == OP_XMM && CodeInfo->r2type == OP_XMM) && 
            CodeInfo->opnd[OPND1].type == OP_XMM || CodeInfo->opnd[OPND1].type == OP_M)
            break;
        else goto error;
      case   T_VRCP28SS:
      case T_VRSQRT28SS:
        if (CodeInfo->mem_type != MT_EMPTY && CodeInfo->mem_type != MT_DWORD )
          goto error;
        if ((CodeInfo->r1type == OP_XMM && CodeInfo->r2type == OP_XMM) && 
            CodeInfo->opnd[OPND1].type == OP_XMM || CodeInfo->opnd[OPND1].type == OP_M)
            break;
      case T_VPCLMULQDQ:
      case T_VAESDECLAST:
      case T_VAESENCLAST:
      case T_VAESDEC:
      case T_VAESENC:
        if (CodeInfo->mem_type != MT_EMPTY && CodeInfo->mem_type != MT_OWORD )
          goto error;
        if ((CodeInfo->r1type == OP_XMM && CodeInfo->r2type == OP_XMM) && 
            CodeInfo->opnd[OPND1].type == OP_XMM || CodeInfo->opnd[OPND1].type == OP_M)
            break;
        else goto error;
      case T_VAESKEYGENASSIST:
        if (CodeInfo->mem_type != MT_EMPTY && CodeInfo->mem_type != MT_OWORD )
          goto error;
        if ((CodeInfo->r1type == OP_XMM) && 
            CodeInfo->opnd[OPND2].type == OP_XMM || CodeInfo->opnd[OPND2].type == OP_M128 ||
            CodeInfo->opnd[OPND2].type == OP_M)
            break;
        else goto error;
      case   T_VRCP28PD:
      case   T_VRCP28PS:
      case   T_VRSQRT28PD:
      case   T_VRSQRT28PS:
      case   T_VEXP2PD:
      case   T_VEXP2PS:
        if ((CodeInfo->r1type == OP_ZMM) && (CodeInfo->opnd[OPND2].type == OP_ZMM || 
          CodeInfo->opnd[OPND2].type & OP_M_ANY )) /* changed to '& OP_M_ANY' v2.46 */
          break;
        else  goto error;
      }
    switch (CodeInfo->token){
      case   T_VCVTSS2USI:
      case   T_VCVTSS2SI :
      case   T_VCVTSS2SD :
      case   T_VCVTSI2SS :
      case   T_VCVTSI2SD :
      case   T_VCVTSD2SS :
      case   T_VCVTSD2USI:
      case   T_VCVTSD2SI :
        if (CodeInfo->r1type == OP_YMM || CodeInfo->opnd[OPND2].type == OP_YMM) 
          goto error;
      }
  /* Validate use of proper GPR size for VPINSRB, VPINSRW, VPINSRD, VPINSRQ, VPEXTRB, VPEXTRW, VPEXTRD, VPEXTRQ, Uasm 2.16 
   * MT_EMPTY is OK because instructions mnemonics are teling the size
   */
  switch (CodeInfo->token){
    case T_VPINSRB:
      if ((CodeInfo->opnd[OPND2].type == OP_R32 || CodeInfo->mem_type == MT_BYTE || CodeInfo->mem_type == MT_EMPTY) &&
        (CodeInfo->r1type == OP_XMM && CodeInfo->r2type == OP_XMM))
        ;// That is correct 
      else goto error;
        break;
    case T_VPINSRW:
      if ((CodeInfo->opnd[OPND2].type == OP_R32 || CodeInfo->mem_type == MT_WORD || CodeInfo->mem_type == MT_EMPTY) &&
        (CodeInfo->r1type == OP_XMM && CodeInfo->r2type == OP_XMM))
        ;// That is correct
      else goto error;
        break;
    case T_VPINSRD:
      if ((CodeInfo->opnd[OPND2].type == OP_R32 || CodeInfo->mem_type == MT_DWORD || CodeInfo->mem_type == MT_EMPTY) &&
        (CodeInfo->r1type == OP_XMM && CodeInfo->r2type == OP_XMM))
        ;// That is correct
      else goto error;
        break;
    case T_VPINSRQ:   // only VPINSRQ can have OP_R64 or MT_QWORD
      if ((CodeInfo->opnd[OPND2].type == OP_R64 || CodeInfo->mem_type == MT_QWORD || CodeInfo->mem_type == MT_EMPTY) &&
        (CodeInfo->r1type == OP_XMM && CodeInfo->r2type == OP_XMM))
        ;// That is correct
      else goto error;
       break;
    case T_VPEXTRB:
     if ((CodeInfo->opnd[OPND1].type == OP_R32 || CodeInfo->mem_type == MT_BYTE || CodeInfo->mem_type == MT_EMPTY) &&
        (CodeInfo->r2type == OP_XMM ))
        ;//That is correct
     else goto error;
       break;
    case T_VPEXTRW:
     if ((CodeInfo->opnd[OPND1].type == OP_R32 || CodeInfo->mem_type == MT_WORD || CodeInfo->mem_type == MT_EMPTY) &&
        (CodeInfo->r2type == OP_XMM ))
        ;//That is correct
     else goto error;
       break;
    case T_VPEXTRD:      
     if ((CodeInfo->opnd[OPND1].type == OP_R32 || CodeInfo->mem_type == MT_DWORD || CodeInfo->mem_type == MT_EMPTY) &&
        (CodeInfo->r2type == OP_XMM ))
         ;//That is correct
     else goto error;
      break;
    case T_VPEXTRQ:
     if ((CodeInfo->opnd[OPND1].type == OP_R64 || CodeInfo->mem_type == MT_QWORD || CodeInfo->mem_type == MT_EMPTY) &&
        (CodeInfo->r2type == OP_XMM ))        
       ;//That is correct 
       else goto error;
     break;
   error:
     EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
    }
    /* emit 4 byte (0x62), 3 (0xC4) or 2 (0xC5) byte VEX prefix */
        if ((CodeInfo->token ==  T_VMOVMSKPD )||(CodeInfo->token ==  T_VMOVMSKPS )) 
          CodeInfo->prefix.rex &= ~REX_W;
        //if (CodeInfo->indexreg == EMPTY) tmp = 0xB4;
        if (( ins->byte1_info >= F_0F38) || ( CodeInfo->prefix.rex & ( REX_B | REX_X | REX_W ) )|| 
          (( ins->byte1_info == F_0F) && (CodeInfo->token ==  T_KMOVQ )) || (ins->byte1_info == F_660F) && 
           (CodeInfo->token ==  T_KMOVD )){
            uint_8 byte1 = 0;      //RXBR00MM
            /* first byte is 0xC4  in 3 byte VEX prefix */  
            if (CodeInfo->evex_flag) 
              OutputCodeByte( 0x62 ); //AVX512 EVEX first byte
            else{
              /* These instructions if, not 0x62, can be only 0xC5, Uasm 2.16 */
                if (CodeInfo->token == T_VPMOVMSKB){
                  if(ins->byte1_info == F_0F && (CodeInfo->prefix.rex & REX_B == 0)&& 
                     (CodeInfo->prefix.rex & REX_X == 0) && (CodeInfo->prefix.rex & REX_W == 8))
                        goto outC5;    // go handle 0xC5 instruction
                  //CodeInfo->prefix.rex &= ~REX_W; // clear the W bit.
                  if(CodeInfo->reg3 > 7) lbyte |= 1;
                }              
                if ((CodeInfo->token >= T_VPSLLDQ && CodeInfo->token <= T_VPSRLQ)||
                  (CodeInfo->token == T_VXORPD || CodeInfo->token ==T_VXORPS)){
                  /* first and second operand can not be memory, v2.46.11 */
                  if (CodeInfo->r1type < OP_XMM || CodeInfo->r2type < OP_XMM)    
                     EmitError(INVALID_INSTRUCTION_OPERANDS);
                  if ((CodeInfo->reg2 <= 7) && (CodeInfo->reg3 <= 7 || CodeInfo->reg3 == 255) && ((CodeInfo->opnd[OPND2].type & OP_M_ANY ) == 0))
                  goto outC5;    // go handle 0xC5 instruction

					/* John: Validate 3 operand vex form */
				  if (CodeInfo->opnd[OPND3].type == OP_NONE && CodeInfo->vexregop == 0 &&
					  (vex_flags[CodeInfo->token - VEX_START] & VX_NND) == 0 &&
					  (vex_flags[CodeInfo->token - VEX_START] & VX_NMEM) == 0)
				  {
					  EmitError(INVALID_INSTRUCTION_OPERANDS);
				  }
                  OutputCodeByte(0xC4);
                  CodeInfo->first_byte = 0xC4;
                }
				else
				{
					/* John: Validate 3 operand vex form */
					if (CodeInfo->opnd[OPND3].type == OP_NONE && CodeInfo->vexregop == 0 && 
						(vex_flags[CodeInfo->token - VEX_START] & VX_NND)==0 && 
						(vex_flags[CodeInfo->token - VEX_START] & VX_NMEM)==0)
					{
						EmitError(INVALID_INSTRUCTION_OPERANDS);
					}
					OutputCodeByte(0xC4);
          CodeInfo->first_byte = 0xC4;
				}
              if (CodeInfo->opnd[OPND1].type == OP_YMM || CodeInfo->opnd[OPND2].type == OP_YMM)
                 lbyte |= 0x04;
              else
                lbyte &= ~0x04;
              CodeInfo->tuple = 0;
              /* This fixes AVX  REX_W wide 32 <-> 64 instructions third byte bit W   || (CodeInfo->token == T_VMOVQ) */   
              if ((CodeInfo->token >= T_VADDPD && CodeInfo->token <= T_VMOVAPS) ||
				  (CodeInfo->token == T_VMOVD) ||(CodeInfo->token == T_VPANDN)||
          (CodeInfo->token == T_VMOVSD)|| (CodeInfo->token == T_VMOVSS)||(CodeInfo->token == T_VPAND))
                lbyte &= ~EVEX_P1WMASK;        //make sure it is not set if WIG
              else
                lbyte |= ((CodeInfo->pinstr->prefix) >> 8 & 0x80); // set only W bit if 64 bit
            }
            switch ( ins->byte1_info ) {                     
            case F_0F38:                                     
            case F_660F38:                                   
            case F_F20F38:
            case F_F30F38:
                byte1 |= 0x02;
                break;
            case F_0F3A:
            case F_660F3A:
            case F_F20F3A:
                byte1 |= 0x03;
                break;
            default:
                if ( ins->byte1_info >= F_0F )
                    byte1 |= 0x01;
            }

              byte1 |= ((CodeInfo->prefix.rex & REX_B) ? 0 : 0x20);/*  REX_B regno 0-7 <-> 8-15 of ModR/M or SIB base */
              byte1 |= ((CodeInfo->prefix.rex & REX_X) ? 0 : 0x40);/*  REX_X regno 0-7 <-> 8-15 of SIB index */
              byte1 |= ((CodeInfo->prefix.rex & REX_R) ? 0 : 0x80);/*  REX_R regno 0-7 <-> 8-15 of ModR/M REG */
              /* check that second operand is not memory operand, v2.46 */
              if (CodeInfo->opnd[OPND2].type & OP_M_ANY)
                ;/* skip */
              else if (CodeInfo->evex_flag && CodeInfo->reg2 <= 15)
                byte1 |= EVEX_P0R1MASK;
            /* second byte is RXBm mmmm of 3 byte  VEX prefix */    /*  REX_W wide 32 <-> 64 */
              if (CodeInfo->evex_flag) {
                if (CodeInfo->token == T_VEXTRACTPS)
                  ;/* skip */
                else{
                  if ((CodeInfo->opnd[OPND1].type & OP_M_ANY) || (CodeInfo->opnd[OPND2].type & OP_M_ANY) ||
                         (CodeInfo->opnd[OPND3].type & OP_M_ANY)) CodeInfo->tuple = TRUE;
                lbyte &= ~EVEX_P1WMASK;
                lbyte |= ((CodeInfo->pinstr->prefix) >> 8 & 0x80);
                if ((CodeInfo->opnd[OPND2].type == OP_M64) || (CodeInfo->opnd[OPND1].type == OP_M64))
                  lbyte |= EVEX_P1WMASK;
                if ((CodeInfo->opnd[OPND2].type == OP_R32) || (CodeInfo->opnd[OPND2].type == OP_EAX) ||
                    (CodeInfo->opnd[OPND1].type == OP_R32) || (CodeInfo->opnd[OPND1].type == OP_EAX)){
                  lbyte &= ~EVEX_P1WMASK;
                  }
                if (((CodeInfo->opnd[OPND1].type & OP_M_ANY) == 0) && CodeInfo->token != T_VPEXTRD &&
                    (CodeInfo->token != T_VCVTPS2PD) && CodeInfo->token != T_VPEXTRB &&
                    (CodeInfo->token != T_VCVTPS2PH) && CodeInfo->token != T_VPEXTRW &&
                    CodeInfo->token != T_VPEXTRQ) { //CodeInfo->token != T_VPMOVQB && 
                  if (CodeInfo->reg1 <= 15)
                    byte1 |= EVEX_P0R1MASK;
                  else
                    byte1 &= ~EVEX_P0R1MASK;
                  if ((CodeInfo->reg1 <= 7) || (CodeInfo->reg1 >= 16 && CodeInfo->reg1 <= 23))
                    byte1 |= EVEX_P0RMASK;
                  else
                    byte1 &= ~EVEX_P0RMASK;
                  if (CodeInfo->reg3 != 0xff) {
                    rn = CodeInfo->reg3;
                    }
                  else if (CodeInfo->basereg != 0xff)
                    rn = CodeInfo->basereg;
                  else rn = CodeInfo->reg2;
                  if (rn > 15){
                    rn -= 15;
                    byte1 &= ~EVEX_P0XMASK;
                    }
                  /* if third register is a mask register and not memory opperand than don't touch EVEX_P0BMASK v2.38 */
                  if (CodeInfo->reg3 != 0xff && CodeInfo->basereg == 0xff);
                  else if (rn <= 7)byte1 |= EVEX_P0BMASK;
                  else byte1 &= ~EVEX_P0BMASK;
                  }
                }
               }
            if (CodeInfo->token >= T_VPSCATTERDD && CodeInfo->token <= T_VSCATTERQPD){
              if (CodeInfo->reg2 <= 15) byte1 |= EVEX_P0R1MASK;
              else byte1 &= ~EVEX_P0R1MASK;
              if (CodeInfo->reg2 <= 7 )  byte1 |= EVEX_P0RMASK;
              else if (CodeInfo->reg2 >= 16 && CodeInfo->reg2 <= 23) byte1 |= EVEX_P0RMASK;
              else byte1 &= ~EVEX_P0RMASK;
            }
              if (((CodeInfo->token == T_VMOVHPS)||(CodeInfo->token == T_VMOVLPS)) && (CodeInfo->opnd[OPND2].type & OP_XMM)){
                if ((CodeInfo->reg2 > 7))
                    byte1 &= ~EVEX_P0RMASK;
                    lbyte &= ~EVEX_P1WMASK;
              }
              if ((CodeInfo->token == T_VMOVNTPD)||(CodeInfo->token == T_VMOVNTPS)||                                
                (CodeInfo->token >= T_VPMOVQB)&&(CodeInfo->token <= T_VPMOVUSWB)){
                if (CodeInfo->reg2 <= 15) byte1 |= EVEX_P0R1MASK;
                else byte1 &= ~EVEX_P0R1MASK;
                if ((CodeInfo->reg2 <= 7) || (CodeInfo->reg2 >= 16 && CodeInfo->reg2 <= 23))
                  byte1 |= EVEX_P0RMASK;
                else byte1 &= ~EVEX_P0RMASK;
                if (CodeInfo->opnd[OPND1].type & OP_M_ANY == 0){
                  if (CodeInfo->reg1 <= 15) byte1 |= EVEX_P0XMASK;
                  else byte1 &= ~EVEX_P0XMASK;
                  if ((CodeInfo->reg1 <= 7) || (CodeInfo->reg1 >= 16 && CodeInfo->reg1 <= 23))
                    byte1 |= EVEX_P0BMASK;
                  else byte1 &= ~EVEX_P0BMASK;
                  }
              }
              if (CodeInfo->opnd[OPND2].type & OP_I8_U){
                if ((CodeInfo->token >= T_VPSLLW) && (CodeInfo->token <= T_VPSRLQ) ||
                  (CodeInfo->token >= T_VPSLLVD) && (CodeInfo->token <= T_VPSRLVW)){
                  byte1 |= EVEX_P0R1MASK;
                  byte1 |= EVEX_P0RMASK;
                  if ((CodeInfo->opnd[OPND1].type == OP_R64) || (CodeInfo->opnd[OPND1].type == OP_RAX) ||
                    (CodeInfo->opnd[OPND1].type == OP_R32) || (CodeInfo->opnd[OPND1].type == OP_EAX)){
                      if (CodeInfo->basereg != 0xFF){
                        if (CodeInfo->basereg <= 7)   
                          byte1 |= EVEX_P0BMASK;
                        else
                          byte1 &= ~EVEX_P0BMASK;
                      }
                    if (CodeInfo->indexreg != 0xFF){
                      if (CodeInfo->indexreg <= 7)   
                        byte1 |= EVEX_P0XMASK;
                      else
                        byte1 &= ~EVEX_P0XMASK;
                    }
                  }
                  else if (!CodeInfo->evex_flag)
                    byte1 &= ~EVEX_P0R1MASK;
                }
              }
              if ((CodeInfo->token == T_VRNDSCALEPD) || (CodeInfo->token == T_VRNDSCALEPS)){
                if (((CodeInfo->r2type &= OP_R64)||(CodeInfo->r2type &= OP_R32))&&
                  (CodeInfo->vexconst)) { 
                  if (CodeInfo->indexreg != 0xff){
                    if (CodeInfo->reg1 <= 7)
                      byte1 |= EVEX_P0XMASK;
                    else
                      byte1 &= ~EVEX_P0XMASK;
                  }
                }
              }
              if (((CodeInfo->token == T_VEXTRACTF32x8)||(CodeInfo->token == T_VEXTRACTF64x4))
                && !(CodeInfo->opnd[OPND1].type & OP_M_ANY)) {
                if (CodeInfo->reg2 <= 15) byte1 |= EVEX_P0R1MASK;
                else byte1 &= ~EVEX_P0R1MASK;
                if ((CodeInfo->reg2 <= 7) || (CodeInfo->reg2 >= 16 && CodeInfo->reg2 <= 23))
                  byte1 |= EVEX_P0RMASK;
                else
                  byte1 &= ~EVEX_P0RMASK;
                if (CodeInfo->reg1 <= 15) byte1 |= EVEX_P0XMASK;
                else byte1 &= ~EVEX_P0XMASK;
              }
              if (((CodeInfo->token >= T_BEXTR)&&(CodeInfo->token <= T_SHRX)||(CodeInfo->token == T_BZHI)&&
                (CodeInfo->indexreg != 0xFF))){
                byte1 &= 0xE3;
                if (CodeInfo->indexreg > 7 && CodeInfo->indexreg <= 31)
                  byte1 &= ~0x10;
              }
              if (CodeInfo->token == T_VCVTPH2PS || CodeInfo->token == T_VCVTPD2UDQ || CodeInfo->token == T_VCVTQQ2PD||
                CodeInfo->token == T_VCVTPD2DQ || CodeInfo->token == T_VCVTDQ2PD){
                if ((CodeInfo->reg1 <= 7) || (CodeInfo->reg1 >= 16 && CodeInfo->reg1 <= 23))
                  byte1 |= EVEX_P0RMASK;
                else
                  byte1 &= ~EVEX_P0RMASK;
                if (CodeInfo->indexreg != 0xff){
                  if (CodeInfo->indexreg <= 7) byte1 |= EVEX_P0XMASK;
                  else byte1 &= ~EVEX_P0XMASK;
                  }
                if (CodeInfo->token == T_VCVTDQ2PD || CodeInfo->token == T_VCVTPS2PD)
                CodeInfo->evex_p2 &= ~EVEX_P2L1MASK;
              }
              if (CodeInfo->token == T_VPCMPEQQ || CodeInfo->token == T_VPCMPEQD ||
                  CodeInfo->token == T_VPCMPEQW || CodeInfo->token == T_VPCMPEQB){
                  if (CodeInfo->r1type == OP_ZMM)
                    EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
                } 
              /*  fix for P0 output v2.46 if (CodeInfo->opnd[OPND1].type == OP_XMM && CodeInfo->opnd[OPND2].type == OP_XMM) ins->opcode = 0x7E;*/
                if (CodeInfo->token == T_VMOVQ){
                  if (CodeInfo->opnd[OPND1].type & OP_R64){
                    if (CodeInfo->evex_flag){
                      if (CodeInfo->reg2 <= 15) byte1 |= EVEX_P0R1MASK;
                      else byte1 &= ~EVEX_P0R1MASK;
                      }
					          if ((CodeInfo->reg2 <= 7) || (CodeInfo->reg2 >= 16 && CodeInfo->reg2 <= 23))
						          byte1 |= EVEX_P0RMASK;
					          else byte1 &= ~EVEX_P0RMASK;
                    byte1 |= EVEX_P0XMASK;
                    }
                    else if (CodeInfo->opnd[OPND1].type & OP_M64){
                    if (CodeInfo->evex_flag){
                      if (CodeInfo->reg2 <= 15) byte1 |= EVEX_P0R1MASK;
                      else byte1 &= ~EVEX_P0R1MASK;
                      }
					          if ((CodeInfo->reg2 <= 7) || (CodeInfo->reg2 >= 16 && CodeInfo->reg2 <= 23))
						          byte1 |= EVEX_P0RMASK;
					          else byte1 &= ~EVEX_P0RMASK;
                    }
                  }
                /* fix v2.46 */
                if (CodeInfo->token == T_VCVTPS2PD || CodeInfo->token == T_VCVTPH2PS || 
                    CodeInfo->token == T_VCVTPS2PH | CodeInfo->token == T_VCVTQQ2PD){
                  /* don't check for memory to reg here */
                  if (CodeInfo->opnd[OPND2].type & OP_M_ANY || CodeInfo->opnd[OPND1].type & OP_M_ANY)
                    ; /* skip */
                  else {
                    /* this is for reg to reg */
                    if (CodeInfo->evex_flag){               /* don't let it happen for for 0xC4, v24.6.9 */
                      if (CodeInfo->reg2 <= 15) byte1 |= EVEX_P0R1MASK;
                      else byte1 &= ~EVEX_P0R1MASK;
                      if ((CodeInfo->reg2 <= 7) || (CodeInfo->reg2 >= 16 && CodeInfo->reg2 <= 23))
                        byte1 |= EVEX_P0RMASK;                                    /*   1000  for all      */
                      byte1 &= ~EVEX_P0XMASK | EVEX_P0BMASK | EVEX_P0R1MASK;      /*   1000  for 24 to 31 */
                      if (CodeInfo->reg2 <= 7)
                        byte1 |= EVEX_P0XMASK | EVEX_P0BMASK | EVEX_P0R1MASK;     /*   1111  for 0  to 7  */
                      else if (CodeInfo->reg2 <= 15)
                        byte1 |= EVEX_P0XMASK | EVEX_P0R1MASK;                    /*   1101  for 8  to 15 */
                      else if (CodeInfo->reg2 <= 23)
                        byte1 |= EVEX_P0BMASK;                                    /*   1010  for 16 to 23 */
                      }
                    }
                  }
                switch (CodeInfo->token){
                  case   T_VGATHERPF0DPD:
                  case   T_VGATHERPF0DPS: 
                  case   T_VGATHERPF0QPD: 
                  case   T_VGATHERPF0QPS:
                  case   T_VGATHERPF1DPD: 
                  case   T_VGATHERPF1DPS: 
                  case   T_VGATHERPF1QPD: 
                  case   T_VGATHERPF1QPS: 
                  case   T_VSCATTERPF0DPD:
                  case   T_VSCATTERPF1DPD:
                  case   T_VSCATTERPF1DPS:
                  case   T_VSCATTERPF1QPD:
                  case   T_VSCATTERPF1QPS:
                  case   T_VSCATTERPF0DPS: 
                  case   T_VSCATTERPF0QPS:
                  case   T_VSCATTERPF0QPD:
                  if (CodeInfo->opnd[OPND1].type == OP_M)
                    byte1 |= EVEX_P0RMASK;
                  }
				      if (!CodeInfo->evex_flag) {
					      if (CodeInfo->token == T_VCVTPH2PS || CodeInfo->token == T_VCVTPS2PH) {
						      if (CodeInfo->opnd[OPND1].type == OP_XMM && (CodeInfo->opnd[OPND2].type == OP_XMM || CodeInfo->opnd[OPND2].type == OP_YMM))
							      byte1 &= 0xEF;
						      if (CodeInfo->opnd[OPND1].type == OP_YMM && (CodeInfo->opnd[OPND2].type == OP_XMM || CodeInfo->opnd[OPND2].type == OP_YMM))
							      byte1 &= 0xEF;
					      }
				      }
              OutputCodeByte( byte1 );
              if (CodeInfo->opnd[OPND2].type & OP_I8_U){
                /* prevent immediate data for KMOV instruction v2.38 */
                if (CodeInfo->token >= T_KMOVB && CodeInfo->token <= T_KMOVW)
                  EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
                if ((CodeInfo->token >= T_VPSLLW) && (CodeInfo->token <= T_VPSRLQ) ||
                  (CodeInfo->token >= T_VPSLLVD) && (CodeInfo->token <= T_VPSRLVW)) {
                  c = CodeInfo->reg1;
                  lbyte &= 0x0f;
                  c = (c << 3);
                  c = ~c;
                  c &= EVEX_P1VVVV;
                  lbyte |= c;
                  if (CodeInfo->evex_flag || CodeInfo->r2type == OP_YMM)  /* fix for reg type v2.46.9 */
                  lbyte |= 4;
                  if (ins->byte1_info == F_660F) lbyte |= 0x1;
                  CodeInfo->tuple = TRUE;
                }
              }
            else
            lbyte |= ( ( CodeInfo->prefix.rex & REX_W ) ? 0x80 : 0 );

			  /* UASM 2.35 Fix vmovq encoding */
			  if (CodeInfo->token == T_VMOVQ && CodeInfo->opnd[OPND1].type == OP_XMM) {
				  if (CodeInfo->opnd[OPND2].type & OP_R64)
				  {
					  lbyte &= 0xfd;
					  lbyte |= 1;
				  }
			  }
			  /* KSHIFTLW KSHIFTLQ KSHIFTRW KSHIFTRQ */
            if ((CodeInfo->token == T_KSHIFTLW) || (CodeInfo->token == T_KSHIFTLQ)||
              (CodeInfo->token == T_KSHIFTRW) || (CodeInfo->token == T_KSHIFTRQ)){
              lbyte |= 0x80;
            }
            //Uasm13.1 VPGATHERDD, VPGATHERQD, VPGATHERDQ, VPGATHERQQ
            if (CodeInfo->token >= T_VPGATHERDD && CodeInfo->token <= T_VGATHERQPS){
              if ((CodeInfo->opnd[OPND3].type != CodeInfo->opnd[OPND1].type)&& 
                (CodeInfo->evex_flag == 0))
                EmitError( INVALID_USE_OF_REGISTER );
              CodeInfo->tuple = TRUE;       
              lbyte &= ~EVEX_P1VVVV;      // clear EVEX_P1VVVV
              if (CodeInfo->evex_flag){
                c = EVEX_P1VVVV;          // set all to ones : VVVV = 1111, we are not using it
              }
              else {
                c = CodeInfo->reg3 + 1;
                c = ((16 - c) << 3);
                //c = ~c;
              }
              c &= EVEX_P1VVVV;
              lbyte |= c;  
              if (CodeInfo->indextype == OP_YMM)    lbyte |= 4;
              if (( CodeInfo->prefix.rex & REX_W )) lbyte |= 0x80;
            }
            if ((CodeInfo->token >= T_KADDB) && (CodeInfo->token <= T_KUNPCKDQ)) {       //here pay atention
              /* third byte W vvvv Lpp   */
              c = CodeInfo->reg2;
              lbyte &= 0xc0;
              c = (c << 3);
              c = ~c;
              c &= EVEX_P1VVVV;
              lbyte |= c;
              lbyte |= 4;    
               if (ins->byte1_info == F_660F) lbyte |= 0x1;
            }
            else if ((CodeInfo->token >= T_KNOTB) && (CodeInfo->token <= T_KORTESTQ)) {
              /*  1 1111 0pp */
              /*  R vvvv Lpp */
              if (CodeInfo->reg2 <= 7)
                 lbyte |= 0x80;
              if (ins->byte1_info == F_660F) lbyte |= 0x01;
            }
            else if ((CodeInfo->token >= T_KMOVB) && (CodeInfo->token <= T_KMOVW)) {
              /*  1 1111 0pp */
              /*  R vvvv Lpp */
              if ((CodeInfo->token == T_KMOVD || CodeInfo->token == T_KMOVQ))
                lbyte |= 0x80;                                  /* W bit has to be set for KMOVD and KMOVQ v2.38*/
              if (ins->byte1_info == F_660F) lbyte |= 0x01;     /* set PP to 01 for 66.0F */
              else if (ins->byte1_info == F_0F) lbyte &= ~0x03; /* set PP t0 00 for 0F */
              else  lbyte |= 0x3;                               /* set PP to 11 for F2.0F */
              if (CodeInfo->token == T_KMOVB || CodeInfo->token == T_KMOVW || CodeInfo->token == T_KMOVD){
                switch (CodeInfo->opnd[OPND2].type){
                  case OP_R64:
                  case OP_RAX:
                  case OP_AX:
                  case OP_R16:
                  case OP_R8:
                  case OP_AL:
                  case OP_I8:
                  case OP_I16:
                  case OP_I32:
                  case OP_I64:
                  EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
                  }
              }
              if (CodeInfo->token == T_KMOVQ){
                switch (CodeInfo->opnd[OPND2].type){
                  case OP_R32:
                  case OP_EAX:
                  case OP_AX:
                  case OP_R16:
                  case OP_R8:
                  case OP_AL:
                  case OP_I8:
                  case OP_I16:
                  case OP_I32:
                  case OP_I64:
                  EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
                 }
              }
            }
            if (CodeInfo->token < T_VCVTDQ2PD && CodeInfo->token > T_VCVTTSS2SI){
              if (CodeInfo->reg2 > 15)lbyte |= EVEX_P1WMASK;
            }
            if ( CodeInfo->token == T_VPSCATTERQQ ||      //CodeInfo->token == T_VPSCATTERDQ ||
              CodeInfo->token == T_VSCATTERDPD || CodeInfo->token == T_VSCATTERQPD){
              lbyte |= 0x80;
            }
            /* if broadflags are prezent W = 0  in WVVVV1PP */
              if (CodeInfo->token == T_VPGATHERDQ || CodeInfo->token == T_VPGATHERQQ ||
                CodeInfo->token == T_VGATHERDPD || CodeInfo->token == T_VGATHERQPD){
                  lbyte |= EVEX_P1WMASK;
                }
            if (((CodeInfo->token <= T_VCOMPRESSPS))||((CodeInfo->token >= T_VCVTDQ2PD) &&
              (CodeInfo->token <= T_VCVTTSS2SI))|| (CodeInfo->token == T_VCVTPD2DQ)) 
              CodeInfo->evex_p2 &= ~EVEX_P1PPMASK;
            if ((CodeInfo->token == T_VPCMPB) || (CodeInfo->token == T_VPCMPUB ))lbyte &= ~EVEX_P1WMASK;
            if (CodeInfo->evex_flag){
              if ((CodeInfo->opnd[OPND2].type == OP_M64) || (CodeInfo->opnd[OPND1].type == OP_M64))
                lbyte |= EVEX_P1WMASK;
               if ((CodeInfo->opnd[OPND2].type == OP_R32) || (CodeInfo->opnd[OPND2].type == OP_EAX) ||
                 (CodeInfo->opnd[OPND1].type == OP_R32) || (CodeInfo->opnd[OPND1].type == OP_EAX)){
                 lbyte &= ~EVEX_P1WMASK;
               }
             }
            switch (CodeInfo->token){
              case   T_VMOVHPS: 
              case   T_VMOVLPS: 
              case   T_VCVTPH2PS:
              case   T_VCVTPS2PD:
              case   T_VPMOVQB:
              case   T_VPMOVSQB:
              case   T_VPMOVSWB:
              case   T_VPMOVWB:
              case   T_VPMOVUSWB:
              case   T_VPMOVUSQB :
              case   T_VGATHERQPS:
              case   T_VPGATHERQD:
              case   T_VGATHERDPS:
              case   T_VEXTRACTPS:
              case   T_VBROADCASTI32x2:
                  lbyte &= ~EVEX_P1WMASK;
            }
            switch (CodeInfo->token){
              case   T_VPSLLQ:
              case   T_VPSRLQ:
              case   T_VPSRAQ:
              case   T_VPROLQ:
              case   T_VPRORQ:
              case   T_VPBROADCASTQ:
              //case   T_VPBROADCASTD:
                if (CodeInfo->evex_flag)
                  lbyte |= EVEX_P1WMASK;
                else
                 lbyte &= ~EVEX_P1WMASK;
              }
             if ((CodeInfo->token >= T_BEXTR)&&(CodeInfo->token <= T_SHRX)||(CodeInfo->token == T_BZHI)){
              c = CodeInfo->reg3;
              lbyte &= 0x80;
              c = (c << 3);
              c = ~c;
              c &= EVEX_P1VVVV;
              lbyte |= c;
#if AMD64_SUPPORT
              lbyte |=0x80;
#endif
               if (ins->byte1_info == F_660F) lbyte |= 0x1;
               else if (ins->byte1_info == F_F30F38) lbyte |= 0x02;//SARX
               else if (ins->byte1_info == F_660F38) lbyte |= 0x01;//SHLX
               else if (ins->byte1_info == F_F20F38) lbyte |= 0x03;//SHRX
             }
             if ((CodeInfo->token == T_BLSMSK)||(CodeInfo->token == T_BLSI)||
               (CodeInfo->token == T_BLSR)){
              c = CodeInfo->reg1;
              lbyte &= 0x80;
              c = (c << 3);
              c = ~c;
              c &= EVEX_P1VVVV;
              lbyte |= c;
               if (ins->byte1_info == F_660F) lbyte |= 0x1;
               else if (ins->byte1_info == F_F20F38) lbyte |= 0x3;
             }
             if ((CodeInfo->token == T_PDEP)||(CodeInfo->token == T_PEXT)){ 
              c = CodeInfo->reg2;
              lbyte &= 0x80;
              c = (c << 3);
              c = ~c;
              c &= EVEX_P1VVVV;
              lbyte |= c;
               if (ins->byte1_info == F_F20F38) lbyte |= 0x3;
               else if (ins->byte1_info == F_F30F38)
                 lbyte |= 0x2;
             }
            if (CodeInfo->token == T_RORX)lbyte |= 0x3;
            if (CodeInfo->token == T_VEXTRACTF128){
              if (CodeInfo->r2type == OP_YMM)
                lbyte |= 0x04;
            }
          /* This prevents misuse of data size,   Uasm 2.16  */
          switch (CodeInfo->token){
            case T_VPMOVSXBW:
            case T_VPMOVSXWD:
            case T_VPMOVSXDQ:
            case T_VPMOVZXBW:
            case T_VPMOVZXWD:
            case T_VPMOVZXDQ:
              if((CodeInfo->r1type == OP_XMM && (CodeInfo->r2type == OP_XMM || CodeInfo->mem_type == MT_QWORD || CodeInfo->mem_type == MT_EMPTY))||
                 (CodeInfo->r1type == OP_YMM && (CodeInfo->r2type == OP_XMM || CodeInfo->mem_type == MT_OWORD || CodeInfo->mem_type == MT_EMPTY ))||
                 (CodeInfo->r1type == OP_ZMM && decoflags && (CodeInfo->r2type == OP_YMM || CodeInfo->mem_type == MT_YMMWORD || CodeInfo->mem_type == MT_EMPTY)))
                 lbyte &= ~EVEX_P1WMASK;  // make sure CodeInfo->evex_p1 W is not set
              else
                EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
              break;
            case T_VPMOVSXBD:
            case T_VPMOVSXWQ:
            case T_VPMOVZXBD:
            case T_VPMOVZXWQ:
              if((CodeInfo->r1type == OP_XMM && (CodeInfo->r2type == OP_XMM || CodeInfo->mem_type == MT_DWORD || CodeInfo->mem_type == MT_EMPTY))||
                 (CodeInfo->r1type == OP_YMM && (CodeInfo->r2type == OP_XMM || CodeInfo->mem_type == MT_QWORD || CodeInfo->mem_type == MT_EMPTY ))||
                 (CodeInfo->r1type == OP_ZMM && decoflags && (CodeInfo->r2type == OP_XMM || CodeInfo->mem_type == MT_OWORD || CodeInfo->mem_type == MT_EMPTY)))
                 lbyte &= ~EVEX_P1WMASK;  // make sure CodeInfo->evex_p1 W is not set
              else
                EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
              break;
            case T_VPMOVSXBQ:
            case T_VPMOVZXBQ:
              if((CodeInfo->r1type == OP_XMM && (CodeInfo->r2type == OP_XMM || CodeInfo->mem_type == MT_WORD || CodeInfo->mem_type == MT_EMPTY))||
                 (CodeInfo->r1type == OP_YMM && (CodeInfo->r2type == OP_XMM || CodeInfo->mem_type == MT_DWORD || CodeInfo->mem_type == MT_EMPTY ))||
                 (CodeInfo->r1type == OP_ZMM && decoflags && (CodeInfo->r2type == OP_XMM || CodeInfo->mem_type == MT_QWORD || CodeInfo->mem_type == MT_EMPTY)))
                 lbyte &= ~EVEX_P1WMASK;  // make sure CodeInfo->evex_p1 W is not set
              else
                EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
              break;
            }
            if(CodeInfo->token == T_VSCATTERQPS || CodeInfo->token == T_VPSCATTERQD ||
               CodeInfo->token == T_VCVTPS2PH || CodeInfo->token == T_VCVTPH2PS ||
               CodeInfo->token == T_VBROADCASTF32x2 || CodeInfo->token == T_VCVTPS2QQ ||
               CodeInfo->token == T_VCVTPS2UQQ ||
              (CodeInfo->token >= T_VPMOVQW && CodeInfo->token <= T_VPMOVUSDW))
              lbyte &= ~EVEX_P1WMASK;
			        switch (CodeInfo->token) {
			        //case T_VPCMPEQQ:
			        case T_VPSRLQ:
			        case T_VPSLLQ:
			        case T_VPSRLDQ:
			        //case T_VPSLLDQ:
                 lbyte |= EVEX_P1WMASK;
                 break;
			        case T_VPMULUDQ:
			        case T_VPERMILPD:
			        case T_VPADDQ:
				        if (CodeInfo->evex_flag == 0) lbyte &= ~EVEX_P1WMASK;
			      }
              if (CodeInfo->token == T_VPCMPEQQ || CodeInfo->token == T_VPSLLDQ||
                  CodeInfo->token == T_VPCMPGTQ ||  CodeInfo->token == T_VPMULDQ){
                if (CodeInfo->evex_flag == 0) lbyte &= ~EVEX_P1WMASK;
                else lbyte |= EVEX_P1WMASK;
                }


          /* this is a temporary fix v2.46 */
          if (CodeInfo->token == T_VMOVQ) {
            if (CodeInfo->opnd[OPND1].type == OP_XMM && (CodeInfo->opnd[OPND2].type == OP_XMM || (CodeInfo->opnd[OPND2].type == OP_M)) ){
              lbyte &= ~0x01;   /* we need here F_F30F */
              lbyte |= 0x02;    /* EVEX.pp should be 10  */
              }
            }
            CodeInfo->evex_p1 = lbyte;
            OutputCodeByte( lbyte );
            if (CodeInfo->evex_flag  ){
              CodeInfo->evex_p2 |= decoflags;
              /*Uasm 2.16 fixed error, replaed '&' with '==' */
            if ((CodeInfo->r1type  == OP_ZMM)|| (CodeInfo->r2type == OP_ZMM))
              CodeInfo->evex_p2 |= EVEX_P2L1MASK;
            else if ((CodeInfo->r1type == OP_YMM) || (CodeInfo->r2type == OP_YMM)) 
              CodeInfo->evex_p2 |= EVEX_P2LMASK;
            if (CodeInfo->evex_sae){
                CodeInfo->evex_p2 &= ~0x70;     //clear bites 6,5,4
                c = CodeInfo->evex_sae - 0x10;  //subtract SAE to get a proper decorator
                /* here we need to test for corect use of decorators  
                 * if it is {sae} c will be zero, in that case we need to add 0x10 to c
                 * if we need {sae}
                */   
                if (c == 0) c += 0x10;
                CodeInfo->evex_p2 |= c;
              }
              if (broadflags >= 0x10 && broadflags <= 0x47) CodeInfo->evex_p2 |= 0x10;
                if ((CodeInfo->token >= T_VCVTDQ2PD && CodeInfo->token <= T_VCVTTSS2SI)||
                (CodeInfo->token == T_VCVTSD2SS)){
                  if (!CodeInfo->evex_sae){
                  CodeInfo->evex_p2 &= ~0x60;   //clear bits 6 and 5
                  if (CodeInfo->opnd[OPND1].type & OP_XMM){
                    if (CodeInfo->r2type & (OP_XMM | OP_M64 | OP_M))
                      ;
                    else EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
                  }
                  else if (CodeInfo->opnd[OPND1].type & OP_YMM){
                    if (CodeInfo->r2type & (OP_XMM | OP_M128 | OP_M))
                      CodeInfo->evex_p2 |= EVEX_P2LMASK;
                    else EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
                  }
                  else if (CodeInfo->opnd[OPND1].type & OP_ZMM){
                    if (CodeInfo->r2type & OP_YMM | OP_M256 | OP_M)
                      CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                    else EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
                    }
                  }
                }
                /* Check for proper data and index size, Uasm 2.16 */
                switch (CodeInfo->token){
                  /*  xmmword,ymmword,zmmword  xmm1 {k1}, vm32x ; ymm1 {k1}, vm32x ; zmm1 {k1}, vm32y   */
                  case T_VPGATHERDQ:
                  case T_VGATHERDPD:
                    //if (CodeInfo->mem_type == MT_EMPTY || CodeInfo->mem_type == MT_DWORD);//that is good
                    //else if (CodeInfo->mem_type == MT_XMMWORD && CodeInfo->r1type == OP_XMM);//that is good
                    //else if (CodeInfo->mem_type == MT_YMMWORD && CodeInfo->r1type == OP_YMM);//that is good
                    //else if (CodeInfo->mem_type == MT_ZMMWORD && CodeInfo->r1type == OP_ZMM);//that is good
                    //else  goto error1;
                    if ((!CodeInfo->evex_flag)&& (CodeInfo->indextype == OP_ZMM || CodeInfo->r1type == OP_ZMM))
                       goto error1;
                    if (!CodeInfo->evex_flag && CodeInfo->indextype == OP_XMM);
                    else if ((CodeInfo->r1type == OP_XMM || CodeInfo->r1type == OP_YMM) && 
                          (CodeInfo->indextype == OP_XMM)); 
                    else if (CodeInfo->r1type == OP_ZMM && CodeInfo->indextype == OP_YMM)
                        ;//CodeInfo->evex_p2 |= EVEX_P2LMASK;
                    else  goto error1;
                        CodeInfo->tuple = TRUE;
                    break;
                  case T_VPGATHERDD:
                  case T_VGATHERDPS:
                  case T_VPGATHERQQ:
                  case T_VGATHERQPD:
                    //if (CodeInfo->mem_type == MT_EMPTY || CodeInfo->mem_type == MT_QWORD);//that is good
                    //else if (CodeInfo->mem_type == MT_XMMWORD && CodeInfo->r1type == OP_XMM);//that is good
                    //else if (CodeInfo->mem_type == MT_YMMWORD && CodeInfo->r1type == OP_YMM);//that is good
                    //else if (CodeInfo->mem_type == MT_ZMMWORD && CodeInfo->r1type == OP_ZMM);//that is good
                    //else  goto error1;
                    if ((!CodeInfo->evex_flag)&& (CodeInfo->indextype == OP_ZMM || CodeInfo->r1type == OP_ZMM))
                       goto error1;
                      if (CodeInfo->r1type == OP_XMM && CodeInfo->indextype == OP_XMM );//that is good
                      else if (CodeInfo->r1type == OP_YMM && CodeInfo->indextype == OP_YMM)
                           CodeInfo->evex_p2 |= EVEX_P2LMASK;
                      else if (CodeInfo->r1type == OP_ZMM && CodeInfo->indextype == OP_ZMM){
                         CodeInfo->evex_p2 &= ~EVEX_P2LMASK;
                         CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                        }
                      else goto error1;
                      CodeInfo->tuple = TRUE;
                    break;
                    /*    VGATHERQPS xmm1 {k1}, vm64x; VGATHERQPS xmm1 {k1}, vm64y; VGATHERQPS ymm1 {k1}, vm64z */
                    /*    VPGATHERQD xmm1 {k1}, vm64x; VPGATHERQD xmm1 {k1}, vm64y; VPGATHERQD ymm1 {k1}, vm64z*/
                  case T_VGATHERQPS:
                  case T_VPGATHERQD:
                    //if (CodeInfo->mem_type == MT_QWORD || CodeInfo->mem_type == MT_EMPTY);//that is good
                    //else if (CodeInfo->mem_type == MT_XMMWORD && CodeInfo->r1type == OP_XMM);//that is good
                    //else if (CodeInfo->mem_type == MT_YMMWORD && CodeInfo->r1type == OP_YMM);//that is good
                    //else if (CodeInfo->mem_type == MT_ZMMWORD && CodeInfo->r1type == OP_ZMM);//that is good
                    //else  goto error1;
                    if ((!CodeInfo->evex_flag)&& (CodeInfo->indextype == OP_ZMM || CodeInfo->r1type == OP_ZMM))
                       goto error1;
                      if (CodeInfo->indextype == OP_XMM && CodeInfo->r1type == OP_XMM);
                      else if (CodeInfo->indextype == OP_YMM && CodeInfo->r1type == OP_XMM)
                        CodeInfo->evex_p2 |= EVEX_P2LMASK;
                      else if (CodeInfo->indextype == OP_ZMM && CodeInfo->r1type == OP_YMM){
                        CodeInfo->evex_p2 &= ~EVEX_P2LMASK;
                        CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                        }
                      else goto error1;
                      CodeInfo->tuple = TRUE;
                    break; 
                    /*  VPSCATTERDD vm32x {k1}, xmm1; VPSCATTERDD vm32y {k1}, ymm1; VPSCATTERDD vm32z {k1}, zmm1
                    *   VPSCATTERQQ vm64x {k1}, xmm1; VPSCATTERQQ vm64y {k1}, ymm1; VPSCATTERQQ vm64z {k1}, zmm1
                    *   VSCATTERDPS vm32x {k1}, xmm1; VSCATTERDPS vm32y {k1}, ymm1; VSCATTERDPS vm32z {k1}, zmm1
                    *   VSCATTERQPD vm64x {k1}, xmm1; VSCATTERQPD vm64y {k1}, ymm1; VSCATTERQPD vm64z {k1}, zmm1 */
                  case T_VPSCATTERDD:
                  case T_VPSCATTERQQ:
                  case T_VSCATTERDPS:
                  case T_VSCATTERQPD:
                    //if (CodeInfo->mem_type == MT_EMPTY);//that is good
                    //else if (CodeInfo->mem_type == MT_XMMWORD && CodeInfo->r2type == OP_XMM);//that is good
                    //else if (CodeInfo->mem_type == MT_YMMWORD && CodeInfo->r2type == OP_YMM);//that is good
                    //else if (CodeInfo->mem_type == MT_ZMMWORD && CodeInfo->r2type == OP_ZMM);//that is good
                    //else  goto error1;
                      if (CodeInfo->indextype != CodeInfo->r2type) goto error1;
                      if (CodeInfo->indextype == OP_YMM) CodeInfo->evex_p2 |= EVEX_P2LMASK;
                      else if (CodeInfo->indextype == OP_ZMM){
                        CodeInfo->evex_p2 &= ~EVEX_P2LMASK;    /* Clear first EVEX_P2LMASK because it was set before */
                         CodeInfo->evex_p2 |= EVEX_P2L1MASK;   /* set L1 byte for ZMM index */
                        }
                    break;
                  //VSCATTERDPD vm32x {k1}, xmm1; VSCATTERDPD vm32x {k1}, ymm1; VSCATTERDPD vm32y {k1}, zmm
                  //VPSCATTERDQ vm32x {k1}, xmm1; VPSCATTERDQ vm32x {k1}, ymm1; VPSCATTERDQ vm32y {k1}, zmm
                  case T_VSCATTERDPD:
                  case T_VPSCATTERDQ:
                      if ((CodeInfo->indextype == OP_XMM) && (CodeInfo->r2type == OP_ZMM)) goto error1;
                      else if (CodeInfo->r2type == OP_ZMM && CodeInfo->indextype != OP_YMM) goto error1;
                      if (CodeInfo->r2type == OP_YMM) CodeInfo->evex_p2 |= EVEX_P2LMASK;
                      else if (CodeInfo->r2type == OP_ZMM){
                        CodeInfo->evex_p2 &= ~EVEX_P2LMASK;    /* Clear first EVEX_P2LMASK because it was set before */
                         CodeInfo->evex_p2 |= EVEX_P2L1MASK;   /* set L1 byte for ZMM index */
                        }
                    break;
                  //VPSCATTERQD vm64x {k1}, xmm1; VPSCATTERQD vm64y {k1}, xmm1; VPSCATTERQD vm64z {k1}, ymm1 
                  //VSCATTERQPS vm64x {k1}, xmm1; VSCATTERQPS vm64y {k1}, xmm1; VSCATTERQPS vm64z {k1}, ymm1
                  case T_VPSCATTERQD:
                  case T_VSCATTERQPS:
                    /* vm64x {k1}, xmm1 ;  vm64y {k1}, xmm1 ;  vm64z {k1}, ymm1 */
                    //if (CodeInfo->mem_type == MT_EMPTY || CodeInfo->mem_type == MT_QWORD);//that is good
                    //else if (CodeInfo->mem_type == MT_XMMWORD && CodeInfo->r1type == OP_XMM);//that is good
                    //else if (CodeInfo->mem_type == MT_YMMWORD && CodeInfo->r1type == OP_YMM);//that is good
                    //else if (CodeInfo->mem_type == MT_ZMMWORD && CodeInfo->r1type == OP_ZMM);//that is good
                    //else  goto error1;
                      if (CodeInfo->indextype == OP_XMM || CodeInfo->indextype == OP_YMM) 
                         if (CodeInfo->r2type != OP_XMM) goto error1;
                      else if (CodeInfo->r2type == OP_YMM && CodeInfo->indextype != OP_ZMM) goto error1;
                      if (CodeInfo->indextype == OP_YMM) CodeInfo->evex_p2 |= EVEX_P2LMASK;
                      else if (CodeInfo->indextype == OP_ZMM){
                        CodeInfo->evex_p2 &= ~EVEX_P2LMASK;    /* Clear first EVEX_P2LMASK because it was set before */
                         CodeInfo->evex_p2 |= EVEX_P2L1MASK;   /* set L1 byte for ZMM index */
                        }

                    break;
                 error1:
                   EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
                  }
                /* This is a fix in Uasm 2.16 */
                if (CodeInfo->token >= T_VPSCATTERDD && CodeInfo->token <= T_VSCATTERQPD){
                    CodeInfo->tuple = TRUE;
                }
                if (CodeInfo->token == T_VEXTRACTPS || CodeInfo->token == T_VCVTSD2USI || CodeInfo->token == T_VCVTTSD2USI){
                  if (!CodeInfo->evex_sae)
                  CodeInfo->evex_p2 &= ~EVEX_P2L1MASK;
                  }
                  if ((CodeInfo->token == T_VEXTRACTF32x4) || (CodeInfo->token == T_VEXTRACTF64x2)||
                    (CodeInfo->token == T_VEXTRACTF64x4)|| (CodeInfo->token == T_VEXTRACTF32x8)||
                    (CodeInfo->token == T_VEXTRACTI32x4)||(CodeInfo->token == T_VEXTRACTI64x4)||
                    (CodeInfo->token == T_VEXTRACTI64x2)|| (CodeInfo->token == T_VEXTRACTI32x8)||
                  (CodeInfo->token == T_VEXTRACTPS))
				  {
                    CodeInfo->evex_p2 &= ~EVEX_P2BMASK;
                    if (CodeInfo->r2type == OP_YMM)
                      CodeInfo->evex_p2 |= EVEX_P2LMASK;
                    else if (CodeInfo->r2type == OP_ZMM){
                      CodeInfo->evex_p2 &= ~EVEX_P2LMASK;
                      CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                      }
                  }
                  if (CodeInfo->evex_flag){
                    if (CodeInfo->token >= T_VPSLLVD && CodeInfo->token <= T_VPSRLVW);
                    else if (CodeInfo->token >= T_VPSLLW && CodeInfo->token <= T_VPSRLDQ);
                    else if (CodeInfo->token >= T_VPSLLDQ && CodeInfo->token <= T_VPSRLQ);
                    else if (CodeInfo->vexregop){
                      if (CodeInfo->reg2 <= 15) CodeInfo->evex_p2 |= EVEX_P2VMASK;
                      else CodeInfo->evex_p2 &= ~EVEX_P2VMASK;
                      }
                    /* Fixed index size in CodeInfo->evex_p2 ~EVEX_P2VMASK, Uasm 2.16 */
                    else if ((CodeInfo->opnd[OPND2].type == OP_M || CodeInfo->opnd[OPND1].type == OP_M) && CodeInfo->indexreg != 0xFF) {
                      if (CodeInfo->indexreg != 0xFF && CodeInfo->indexreg <= 15 ) CodeInfo->evex_p2 |= EVEX_P2VMASK;   
                      else CodeInfo->evex_p2 &= ~EVEX_P2VMASK;
                    }
              if ((CodeInfo->token == T_VRNDSCALEPD) || (CodeInfo->token == T_VRNDSCALEPS)||
                   (CodeInfo->token ==  T_VCVTPS2PH))
                    CodeInfo->evex_p2 |= EVEX_P2VMASK;
                CodeInfo->evex_p2 |= decoflags;
                if (CodeInfo->token == T_VCVTDQ2PD){
                  if (CodeInfo->opnd[OPND1].type != OP_ZMM)
                   CodeInfo->evex_p2 &= ~EVEX_P2L1MASK;
                  }
              /*  v2.46 fixed EVEX_P2VMASK  */
                if ((CodeInfo->token >= T_VPSLLW) && (CodeInfo->token <= T_VPSRLQ) ||
                  (CodeInfo->token >= T_VPSLLVD) && (CodeInfo->token <= T_VPSRLVW)||
                  (CodeInfo->token >= T_VPSLLVD && CodeInfo->token <= T_VPSRLVW)){ 
                  if (CodeInfo->opnd[OPND2].type & OP_I8_U) {
                    if (CodeInfo->reg1 <= 15)
                      CodeInfo->evex_p2 |= EVEX_P2VMASK;
                    }
                  else{
                    if (CodeInfo->reg2 <= 15)
                      CodeInfo->evex_p2 |= EVEX_P2VMASK;
                    }
                }
            switch (CodeInfo->token){ 
              case T_VGATHERPF0DPD: 
              case T_VGATHERPF1DPD:
              case T_VSCATTERPF0DPD:
              case T_VSCATTERPF1DPD:
              CodeInfo->evex_p2 |= EVEX_P2L1MASK;
              if (CodeInfo->indexreg > 15 && CodeInfo->indexreg <= 31) 
                CodeInfo->evex_p2 &= ~EVEX_P2VMASK;
              if (CodeInfo->indextype != OP_YMM)
                EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
              }
            switch (CodeInfo->token){
              case T_VGATHERPF0DPS: 
              case T_VGATHERPF0QPS:
              case T_VGATHERPF0QPD:
              case T_VGATHERPF1DPS: 
              case T_VGATHERPF1QPS:
              case T_VGATHERPF1QPD:
              case T_VSCATTERPF0DPS: 
              case T_VSCATTERPF0QPS:
              case T_VSCATTERPF0QPD:
              case T_VSCATTERPF1DPS: 
              case T_VSCATTERPF1QPS:
              case T_VSCATTERPF1QPD:
              if (CodeInfo->indexreg > 15 && CodeInfo->indexreg <= 31)
                CodeInfo->evex_p2 &= ~EVEX_P2VMASK;
              CodeInfo->evex_p2 |= EVEX_P2L1MASK;
              if (CodeInfo->indextype != OP_ZMM)
                EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
              }
            /* fix v2.46 */
            if (CodeInfo->token == T_VCVTPD2DQ || CodeInfo->token == T_VCVTTPD2DQ || 
                CodeInfo->token == T_VCVTPD2PS|| CodeInfo->token == T_VCVTTPD2UDQ){
              if (CodeInfo->opnd[OPND1].type == OP_YMM && CodeInfo->opnd[OPND2].type == OP_M512){
                 CodeInfo->evex_p2 &= ~EVEX_P2LMASK;
                CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                }
              }
              if (CodeInfo->token == T_VCVTPD2UDQ){
                  if (CodeInfo->r1type == OP_XMM ){
                    CodeInfo->evex_p2 &= ~EVEX_P2L1MASK;
                    CodeInfo->evex_p2 |= EVEX_P2LMASK;
                    }
                  else if (CodeInfo->r1type == OP_YMM && (!CodeInfo->evex_sae )){
                    CodeInfo->evex_p2 &= ~EVEX_P2LMASK;
                    CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                    }
                }
              if (CodeInfo->token == T_VFPCLASSPD || CodeInfo->token == T_VFPCLASSPS){
                if (CodeInfo->mem_type == MT_ZMMWORD)
                  CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                else if (CodeInfo->mem_type == MT_YMMWORD)
                  CodeInfo->evex_p2 |= EVEX_P2LMASK;
                }
               OutputCodeByte(CodeInfo->evex_p2);
              }
           }
		}
		else {
			lbyte |= ((CodeInfo->prefix.rex & REX_R) ? 0 : EVEX_P1WMASK);
			/* first byte is 0xC5  in 2 byte version  */
      if (CodeInfo->token == T_VCVTPD2PS || CodeInfo->token == T_VCVTPS2PD){
          if (CodeInfo->opnd[OPND2].type == OP_M512)CodeInfo->evex_flag = 1;
          lbyte |= 4;
          CodeInfo->evex_p2 |= EVEX_P2L1MASK;
        }
			if (CodeInfo->evex_flag) {
				OutputCodeByte(0x62);
				if ((CodeInfo->opnd[OPND1].type & OP_M_ANY) || (CodeInfo->opnd[OPND2].type & OP_M_ANY) ||
					(CodeInfo->opnd[OPND3].type & OP_M_ANY)) CodeInfo->tuple = TRUE;
				lbyte &= ~EVEX_P1WMASK;
				lbyte |= ((CodeInfo->pinstr->prefix) >> 8 & EVEX_P1WMASK);
				if ((CodeInfo->opnd[OPND2].type == OP_M64) || (CodeInfo->opnd[OPND1].type == OP_M64))
					lbyte |= EVEX_P1WMASK;
				if ((CodeInfo->opnd[OPND2].type == OP_R32) || (CodeInfo->opnd[OPND2].type == OP_EAX) ||
					(CodeInfo->opnd[OPND1].type == OP_R32) || (CodeInfo->opnd[OPND1].type == OP_EAX) ||
					(CodeInfo->token == T_VMOVD)) {
					lbyte &= ~EVEX_P1WMASK;
				}
				switch (ins->byte1_info) {
				case F_0F38:
				case F_660F38:
				case F_F20F38:
					CodeInfo->evex_p0 |= 0x02;
					break;
				case F_0F3A:
				case F_660F3A:
					CodeInfo->evex_p0 |= 0x03;
					break;
				default:
					if (ins->byte1_info >= F_0F) {
						CodeInfo->evex_p0 |= 0x01;
					}
				}
        if (CodeInfo->opnd[OPND1].type & OP_M_ANY) {
          if (CodeInfo->indexreg != 0xff){
            if (CodeInfo->indexreg <= 7) 
            CodeInfo->evex_p0 |= EVEX_P0XMASK;
            else
              CodeInfo->evex_p0 &= ~EVEX_P0XMASK;
            }
          if (CodeInfo->basereg != 0xFF){
            if (CodeInfo->basereg <= 7)   
              CodeInfo->evex_p0 |= EVEX_P0BMASK;
            else
              CodeInfo->evex_p0 &= ~EVEX_P0BMASK;
          }
        }
        /* if it is EVEX and VX_NND not present then it must 3 registers */
				else if ((vex_flags[CodeInfo->token - VEX_START] & VX_NND) == 0){
          CodeInfo->evex_p0 &= ~0x20;    // clear REX_B
          if (CodeInfo->reg3 <= 7) CodeInfo->evex_p0 |= EVEX_P0XMASK;
          CodeInfo->evex_p0 |= ((CodeInfo->prefix.rex & REX_B) ? 0 : 0x20);/*  REX_B regno 0-7 <-> 8-15 of ModR/M or SIB base */
				}
				else { 
          /* only 2 registers */
          CodeInfo->evex_p0 &= ~0x20;  // clear REX_B
					if (CodeInfo->reg2 <= 7) CodeInfo->evex_p0 |= EVEX_P0XMASK;
          CodeInfo->evex_p0 |= ((CodeInfo->prefix.rex & REX_B) ? 0 : 0x20);/*  REX_B regno 0-7 <-> 8-15 of ModR/M or SIB base */
				}
          if (CodeInfo->basereg != 0xFF){
            if (CodeInfo->basereg <= 7)   
              CodeInfo->evex_p0 |= EVEX_P0BMASK;
            else
              CodeInfo->evex_p0 &= ~EVEX_P0BMASK;
            }
				if ((CodeInfo->token >= T_VMOVLHPS) && (CodeInfo->token <= T_VMOVLPS) ||
					(CodeInfo->token == T_VMOVNTDQ) || CodeInfo->token == T_VCVTTPS2UDQ ||
          CodeInfo->token == T_VCVTTPD2UDQ||
					(CodeInfo->token == T_VMOVUPD) || (CodeInfo->token == T_VMOVAPD) ||
					(CodeInfo->token >= T_VMOVDQA32) && (CodeInfo->token <= T_VMOVDQU64) ||
					(CodeInfo->token == T_VMOVAPS) || (CodeInfo->token == T_VMOVUPS)) {
					if ((CodeInfo->opnd[OPND1].type & OP_XMM) || (CodeInfo->opnd[OPND1].type & OP_YMM) ||
						(CodeInfo->opnd[OPND1].type & OP_ZMM)) {
						if ((CodeInfo->reg1 <= 7) || (CodeInfo->reg1 >= 16 && CodeInfo->reg1 <= 23))
							CodeInfo->evex_p0 |= EVEX_P0RMASK;
						else CodeInfo->evex_p0 &= ~EVEX_P0RMASK;
						if (CodeInfo->reg1 <= 15) 
              CodeInfo->evex_p0 |= EVEX_P0R1MASK;
						else CodeInfo->evex_p0 &= ~EVEX_P0R1MASK;
						if (CodeInfo->opnd[OPND1].type & OP_YMM) CodeInfo->evex_p2 |= EVEX_P2LMASK;
						if (CodeInfo->opnd[OPND1].type & OP_ZMM) CodeInfo->evex_p2 |= EVEX_P2L1MASK;
					}
					else if ((CodeInfo->opnd[OPND2].type & OP_XMM) || (CodeInfo->opnd[OPND2].type & OP_YMM) ||
						(CodeInfo->opnd[OPND2].type & OP_ZMM)) {
						if ((CodeInfo->reg2 <= 7) || (CodeInfo->reg2 >= 16 && CodeInfo->reg2 <= 23))
							CodeInfo->evex_p0 |= EVEX_P0RMASK;
						else CodeInfo->evex_p0 &= ~EVEX_P0RMASK;
						if (CodeInfo->reg2 <= 15)
							CodeInfo->evex_p0 |= EVEX_P0R1MASK;
						else CodeInfo->evex_p0 &= ~EVEX_P0R1MASK;
						if (CodeInfo->opnd[OPND2].type & OP_YMM) CodeInfo->evex_p2 |= EVEX_P2LMASK;
						if (CodeInfo->opnd[OPND2].type & OP_ZMM) CodeInfo->evex_p2 |= EVEX_P2L1MASK;
					}
#if AMD64_SUPPORT         /* This is a fix for memory without indexreg v2.38*/
					if ((CodeInfo->opnd[OPND2].type & OP_M_ANY) || (CodeInfo->opnd[OPND1].type & OP_M_ANY) ||
						(CodeInfo->token == T_VCVTTPS2UDQ) || (CodeInfo->token == T_VCVTTPD2UDQ))
						CodeInfo->evex_p0 |= EVEX_P0XMASK;  /* if 64 bit set X in RXB */
#endif
				}
				else {  // this is a fix for VMOVSS when first operand is RIP memory, Uasm 2.16
					if (CodeInfo->opnd[OPND1].type & OP_M_ANY) {
						if (CodeInfo->reg2 <= 15) CodeInfo->evex_p0 |= EVEX_P0R1MASK;
						else CodeInfo->evex_p0 &= ~EVEX_P0R1MASK;
						if ((CodeInfo->reg2 <= 7) || (CodeInfo->reg2 >= 16 && CodeInfo->reg2 <= 23))
							CodeInfo->evex_p0 |= EVEX_P0RMASK;
						else CodeInfo->evex_p0 &= ~EVEX_P0RMASK;
					}
					else if ((CodeInfo->opnd[OPND2].type & OP_M_ANY)||(CodeInfo->opnd[OPND1].type & OP_M_ANY)) {
						if (CodeInfo->reg1 <= 15) CodeInfo->evex_p0 |= EVEX_P0R1MASK;
						else CodeInfo->evex_p0 &= ~EVEX_P0R1MASK;
						if ((CodeInfo->reg1 <= 7) || (CodeInfo->reg1 >= 16 && CodeInfo->reg1 <= 23))
							CodeInfo->evex_p0 |= EVEX_P0RMASK;
						else CodeInfo->evex_p0 &= ~EVEX_P0RMASK;
#if AMD64_SUPPORT         /* This is a fix for memory without indexreg v2.38*/
                          CodeInfo->evex_p0 |= EVEX_P0XMASK;  /* if 64 bit set X in RXB */
#endif
					}
					else {
						if (CodeInfo->reg1 <= 15) CodeInfo->evex_p0 |= EVEX_P0R1MASK;
						else CodeInfo->evex_p0 &= ~EVEX_P0R1MASK;
						if ((CodeInfo->reg1 <= 7) || (CodeInfo->reg1 >= 16 && CodeInfo->reg1 <= 23))
							CodeInfo->evex_p0 |= EVEX_P0RMASK;
						else CodeInfo->evex_p0 &= ~EVEX_P0RMASK;
            CodeInfo->evex_p0 &= ~0x20;  // clear REX_B
            CodeInfo->evex_p0 |= ((CodeInfo->prefix.rex & REX_B) ? 0 : 0x20);/*  REX_B regno 0-7 <-> 8-15 of ModR/M or SIB base */
            }
				}
				if ((CodeInfo->token == T_VMOVNTPD) || (CodeInfo->token == T_VMOVNTPS)|| (CodeInfo->token == T_VMOVUPD)) {
        if (CodeInfo->opnd[OPND1].type & OP_M_ANY ){  /* fix v2.46   */
					if (CodeInfo->reg2 <= 15) CodeInfo->evex_p0 |= EVEX_P0R1MASK;
					else CodeInfo->evex_p0 &= ~EVEX_P0R1MASK;
					if ((CodeInfo->reg2 <= 7) || (CodeInfo->reg2 >= 16 && CodeInfo->reg2 <= 23))
						CodeInfo->evex_p0 |= EVEX_P0RMASK;
					else CodeInfo->evex_p0 &= ~EVEX_P0RMASK;
          }
        else{
					if (CodeInfo->reg1 <= 15) CodeInfo->evex_p0 |= EVEX_P0R1MASK;
					else CodeInfo->evex_p0 &= ~EVEX_P0R1MASK;
					if ((CodeInfo->reg1 <= 7) || (CodeInfo->reg1 >= 16 && CodeInfo->reg1 <= 23))
						CodeInfo->evex_p0 |= EVEX_P0RMASK;
					else CodeInfo->evex_p0 &= ~EVEX_P0RMASK;
          }
				}
				if ((CodeInfo->token >= T_VMOVLHPS) && (CodeInfo->token <= T_VMOVLPS)) {
					if ((CodeInfo->opnd[OPND1].type == OP_YMM) || (CodeInfo->opnd[OPND2].type == OP_YMM) ||
						(CodeInfo->opnd[OPND1].type == OP_ZMM) || (CodeInfo->opnd[OPND2].type == OP_ZMM))
						EmitError(INVALID_INSTRUCTION_OPERANDS);
				}
        if (CodeInfo->basereg == 0x10)        /* for RIP relative addressing it is actually 0x05 for base displacement */
          CodeInfo->evex_p0 |= EVEX_P0BMASK;  /* so EVEX_P0BMASK has to be set, v2.38 */
        /* fix for P0 v2.46 */
          if (CodeInfo->token >= T_VPSLLDQ && CodeInfo->token <= T_VPSRLQ){
          if (CodeInfo->opnd[OPND1].type == OP_XMM || CodeInfo->opnd[OPND1].type == OP_YMM ||
              CodeInfo->opnd[OPND1].type == OP_ZMM){
            if (CodeInfo->opnd[OPND2].type & OP_I8_U){                              /*   RXBR'              */
              CodeInfo->evex_p0 |= EVEX_P0RMASK;                                    /*   1000  for all      */
                CodeInfo->evex_p0 &= ~EVEX_P0XMASK|EVEX_P0BMASK|EVEX_P0R1MASK;      /*   1000  for 24 to 31 */
                if (CodeInfo->reg2 <= 7)
                  CodeInfo->evex_p0 |= EVEX_P0XMASK|EVEX_P0BMASK|EVEX_P0R1MASK;     /*   1111  for 0  to 7  */
                else if (CodeInfo->reg2 <= 15) 
                  CodeInfo->evex_p0 |= EVEX_P0XMASK|EVEX_P0R1MASK;                  /*   1101  for 8  to 15 */
                else if (CodeInfo->reg2 <= 23) 
                  CodeInfo->evex_p0 |= EVEX_P0BMASK;                                /*   1010  for 16 to 23 */
                }
              }
          }
        if (CodeInfo->token == T_VMOVD){
          if (CodeInfo->opnd[OPND1].type & OP_R32){
					  if (CodeInfo->reg2 <= 15) CodeInfo->evex_p0 |= EVEX_P0R1MASK;
					  else CodeInfo->evex_p0 &= ~EVEX_P0R1MASK;
					  if ((CodeInfo->reg2 <= 7) || (CodeInfo->reg2 >= 16 && CodeInfo->reg2 <= 23))
						  CodeInfo->evex_p0 |= EVEX_P0RMASK;
					  else CodeInfo->evex_p0 &= ~EVEX_P0RMASK;
            CodeInfo->evex_p0 |= EVEX_P0XMASK;
            }
          if (CodeInfo->opnd[OPND1].type & OP_M32){
					  if (CodeInfo->reg2 <= 15) CodeInfo->evex_p0 |= EVEX_P0R1MASK;
					  else CodeInfo->evex_p0 &= ~EVEX_P0R1MASK;
					  if ((CodeInfo->reg2 <= 7) || (CodeInfo->reg2 >= 16 && CodeInfo->reg2 <= 23))
						  CodeInfo->evex_p0 |= EVEX_P0RMASK;
					  else CodeInfo->evex_p0 &= ~EVEX_P0RMASK;
            CodeInfo->evex_p0 |= EVEX_P0XMASK;
            }
          }
        if (CodeInfo->token == T_VMOVQ || CodeInfo->token == T_VMOVSD || CodeInfo->token == T_VMOVSS){
          if (CodeInfo->opnd[OPND2].type == OP_XMM && (CodeInfo->opnd[OPND1].type & OP_M_ANY))
          CodeInfo->evex_p0 |= EVEX_P0XMASK;
          }
        else if (CodeInfo->token == T_VMOVDQU8 || CodeInfo->token == T_VMOVDQU16 || 
                  CodeInfo->token == T_VMOVNTPD || CodeInfo->token == T_VMOVNTPS ||
                  CodeInfo->token == T_VCVTTPD2UQQ || CodeInfo->token == T_VCVTTPS2UQQ){
          if (CodeInfo->opnd[OPND2].type == OP_XMM || CodeInfo->opnd[OPND2].type == OP_YMM||
              CodeInfo->opnd[OPND2].type == OP_ZMM)
          CodeInfo->evex_p0 |= EVEX_P0XMASK;
          }
        else if (CodeInfo->token == T_VCVTUDQ2PD || CodeInfo->token == T_VCVTUQQ2PD || CodeInfo->token == T_VCVTUDQ2PS){
          if (CodeInfo->opnd[OPND1].type == OP_XMM || CodeInfo->opnd[OPND1].type == OP_YMM||
              CodeInfo->opnd[OPND1].type == OP_ZMM)
          CodeInfo->evex_p0 |= EVEX_P0XMASK;
          }
        OutputCodeByte(CodeInfo->evex_p0);
			}
			else {
			outC5:
				/* John: Validate 3 operand vex form */
				if (CodeInfo->opnd[OPND3].type == OP_NONE && CodeInfo->vexregop == 0 &&
					(vex_flags[CodeInfo->token - VEX_START] & VX_NND) == 0 &&
					(vex_flags[CodeInfo->token - VEX_START] & VX_NMEM) == 0)
				{
          if(CodeInfo->opnd[OPND1].type & OP_M_ANY || CodeInfo->opnd[OPND2].type & OP_M_ANY )
            ;
          else{
            c = CodeInfo->reg1;
            lbyte &= ~EVEX_P1VVVV;
            c = (c << 3);
            c = ~c;
            c &= EVEX_P1VVVV;
            lbyte |= c;
            if (Parse_Pass == PASS_1)
	            EmitWarn( 2, AVX_REQUIRES_THREE_REGISTERS);
            }
				}

				OutputCodeByte(0xC5);
        CodeInfo->first_byte = 0xC5;
				if (CodeInfo->opnd[OPND1].type == OP_YMM || CodeInfo->opnd[OPND2].type == OP_YMM || CodeInfo->token == T_VZEROALL) /* VZEROALL is 256 bits VZEROUPPER is 128 bits */
					lbyte |= 0x04;  /* set L: Vector Length */
				else
					lbyte &= ~0x04;
				CodeInfo->tuple = 0;
			}
      if (CodeInfo->token == T_VCVTPD2DQ || CodeInfo->token == T_VCVTTPD2DQ) {
          if (CodeInfo->opnd[OPND2].type & OP_M256)
          lbyte |= 0x04;  /* set L: Vector Length */
        }
			/* second byte R vvvv Lpp   */
			if ((CodeInfo->token == T_LZCNT) || (CodeInfo->token == T_TZCNT))
				lbyte |= 0x80;
			if (CodeInfo->token == T_VMASKMOVDQU ) {
				/*  1 1111 0pp */
				/*  R vvvv Lpp */
				lbyte |= 0xF8;
				if (ins->byte1_info == F_660F) lbyte |= 0x01;
				else if (ins->byte1_info == F_0F) lbyte |= 0x3;
			}  //WVVVV1PP
			/* if broadflags are prezent W = 0  in WVVVV1PP */
			if (CodeInfo->token == T_VPGATHERDQ || CodeInfo->token == T_VPGATHERQQ ||
				CodeInfo->token == T_VGATHERDPD || CodeInfo->token == T_VGATHERQPD) {
				lbyte |= 0x80;
			}
			if (CodeInfo->token == T_VGATHERDPS || CodeInfo->token == T_VCVTTPS2QQ || CodeInfo->token == T_VCVTTPS2UQQ)
        lbyte &= ~0x80;
			if (CodeInfo->evex_flag) {
				if ((CodeInfo->opnd[OPND2].type == OP_R32) || (CodeInfo->opnd[OPND2].type == OP_EAX))
					lbyte &= ~EVEX_P1WMASK;
			}
			if ((CodeInfo->token >= T_KADDB) && (CodeInfo->token <= T_KUNPCKDQ)) {       //here pay atention
				c = CodeInfo->reg2;
				lbyte &= 0x83;
				c = (c << 3);
				c = ~c;
				c &= EVEX_P1VVVV;
				lbyte |= c;
				if (vex_flags[CodeInfo->token - VEX_START] & VX_L) lbyte |= c;
			}
			else if ((CodeInfo->token >= T_KNOTB) && (CodeInfo->token <= T_KORTESTQ)) {
				/*  1 1111 0pp */
				/*  R vvvv Lpp */
              if (CodeInfo->reg1 <= 0x07)
				lbyte |= 0x80;
				if (ins->byte1_info == F_660F) lbyte |= 0x01;
			}
			else if ((CodeInfo->token >= T_KMOVB) && (CodeInfo->token <= T_KMOVW)) {
        /* prevent immediate data for KMOV instruction v2.38 */
          switch (CodeInfo->opnd[OPND2].type){
            case OP_R64:
            case OP_RAX:
            case OP_AX:
            case OP_R16:
            case OP_R8:
            case OP_AL:
            case OP_I8:
            case OP_I16:
            case OP_I32:
            case OP_I64:
            EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
            }
				/*  1 1111 0pp */
				/*  R vvvv Lpp */
              if (CodeInfo->reg1 <= 0x07)
				lbyte |= 0x80;
				if (ins->byte1_info == F_660F) lbyte |= 0x01;
				else if (ins->byte1_info == F_F20F) lbyte |= 0x3;
			}  //WVVVV1PP
			if ((CodeInfo->token == T_VMOVHPD) || (CodeInfo->token == T_VMOVNTDQ) ||
				(CodeInfo->token >= T_VFPCLASSPD) && (CodeInfo->token <= T_VFPCLASSSS)) {
				if (CodeInfo->vexregop) {
					lbyte &= ~0x78;
					lbyte |= ((16 - CodeInfo->vexregop) << 3);
				}
				else lbyte |= 0x78;
			}
			if (CodeInfo->evex_flag) {
				if (CodeInfo->token == T_VMOVHPS || CodeInfo->token == T_VMOVLPS ||
            CodeInfo->token == T_VCVTPS2QQ || CodeInfo->token == T_VCVTPS2UQQ)
					lbyte &= ~EVEX_P1WMASK;
			}

        //if (CodeInfo->token == T_VPSLLDQ ||CodeInfo->token == T_VPSRLDQ)   // 
        //  lbyte |= EVEX_P1WMASK;
        if (  CodeInfo->token == T_VPSRAQ || CodeInfo->token == T_VPROLQ ||
          CodeInfo->token == T_VPRORQ){
          if (CodeInfo->evex_flag)
            lbyte |= EVEX_P1WMASK;
          else
            lbyte &= ~EVEX_P1WMASK;
          }
		   //if first byte is VEX 0xC5 then there is two byte folowing 
		   /* set L: Vector Length for all instructions between KADDB and  KUNPCKDQ  Uasm 2.16 */
			if ((CodeInfo->token >= T_KADDB) && (CodeInfo->token <= T_KUNPCKDQ)) lbyte |= 0x04;
			/* That is where is fixed problem with the VEX registers size, Uasm 2.16 */
			if (CodeInfo->token == T_VPMOVMSKB) {
				lbyte |= EVEX_P1WMASK;    // 2 byte vex_p1 R must be set
				if (CodeInfo->opnd[OPND1].type == OP_YMM)
					lbyte |= 0x04;         // for YMM register bit 2 byte VEX L bit is set
				else if (CodeInfo->opnd[OPND1].type == OP_XMM)
					lbyte &= ~0x04;                     // for XMM register bit 2 byte VEX L bit is cleared
				  lbyte &= ~0x03;                     // clear vex_p1 PP 
				  lbyte |= 0x01;                      // set vex_p1 01: 66
			}
			if (CodeInfo->token == T_VCVTPS2PD)
			{				
        if (CodeInfo->evex_flag){
          /* EVEX VCVTPS2PD must be W0*/
          CodeInfo->evex_p1 &= ~EVEX_P1WMASK;
					CodeInfo->evex_p1 |= 0xf0;    // EVEX.vvvv is reserved and must be 1111b
          }
        else{
          /* AVX are both WIG */
          lbyte &= ~EVEX_P1WMASK;
          lbyte |= 0xf0;               // VEX.vvvv is reserved and must be 1111b
          if ((CodeInfo->opnd[OPND2].type == OP_XMM)|| (CodeInfo->opnd[OPND2].type & OP_M_ANY))
              ;
            else EmitError(INVALID_INSTRUCTION_OPERANDS);
          }
			  }
			if (CodeInfo->token == T_VCVTPD2PS)
			{			
        if (CodeInfo->evex_flag){
          /* EVEX VCVTPD2PS must be W1 */
          CodeInfo->evex_p1 |= EVEX_P1WMASK;
					CodeInfo->evex_p1 |= 0xf0;    // EVEX.vvvv is reserved and must be 1111b
          }
        else{
          /* AVX are both WIG */
          lbyte &= ~EVEX_P1WMASK;
          lbyte |= 0xf0;               // VEX.vvvv is reserved and must be 1111b
          if (CodeInfo->opnd[OPND1].type != OP_XMM) 
            EmitError(INVALID_INSTRUCTION_OPERANDS);
          if (CodeInfo->opnd[OPND2].type == OP_M256)
            lbyte |= 0x4;              // L bit
          }
			  }	
        /* for vmovq xmm1,xmm2 PP  has to be F_F30F which is 02  v2.46 */
        if (CodeInfo->token == T_VMOVQ && (CodeInfo->evex_flag == 0)){
          if ((CodeInfo->opnd[OPND1].type == OP_XMM && CodeInfo->opnd[OPND2].type & OP_XMM)||
               (CodeInfo->opnd[OPND1].type == OP_XMM && CodeInfo->opnd[OPND2].type & OP_M)){
            lbyte &= ~0x01;
            lbyte |= 0x02;
            }
          }
        if (CodeInfo->token == T_VPEXTRW){
         if ((CodeInfo->opnd[OPND1].type == OP_R32 || CodeInfo->mem_type == MT_WORD || CodeInfo->mem_type == MT_EMPTY) &&
            (CodeInfo->r2type == OP_XMM ))
            lbyte |= 0x01;
          }
          CodeInfo->evex_p1 = lbyte;
          OutputCodeByte( lbyte );
          if (CodeInfo->evex_flag) {
            if (broadflags >= 0x10 && broadflags <= 0x47){ 
              CodeInfo->evex_p2 |= 0x10;
              if (CodeInfo->vexregop){                 
                if (CodeInfo->reg2 <= 15) CodeInfo->evex_p2 |= EVEX_P2VMASK;
                else CodeInfo->evex_p2 &= ~EVEX_P2VMASK;
              }
              else CodeInfo->evex_p2 |= EVEX_P2VMASK;
              if ((CodeInfo->r2type == OP_XMM || CodeInfo->r1type == OP_XMM) && 
                  (broadflags & ~EVEX_P2AAAMASK) == 0x10){   //{1to2}
                  if ((CodeInfo->mem_type != MT_QWORD) && (CodeInfo->mem_type != MT_EMPTY))
                    EmitError( INVALID_OPERAND_SIZE );
                  if ((CodeInfo->pinstr->prefix & 0xE0) == QSIZE)
                    CodeInfo->mem_type = MT_QWORD;
                  else
                    EmitError( MISMATCH_IN_THE_NUMBER_OF_BROADCASTING_ELEMENTS );
              }
              else if ((CodeInfo->r2type == OP_XMM ||CodeInfo->r1type == OP_XMM) && 
                       (broadflags & ~EVEX_P2AAAMASK) == 0x20){ //{1to4} 
                  if ((CodeInfo->mem_type != MT_DWORD) && (CodeInfo->mem_type != MT_EMPTY))
                    EmitError( INVALID_OPERAND_SIZE );
                  if ((CodeInfo->pinstr->prefix & 0xE0) == DSIZE)
                    CodeInfo->mem_type = MT_DWORD;
                  else
                    EmitError( MISMATCH_IN_THE_NUMBER_OF_BROADCASTING_ELEMENTS );
              }
              else if ((CodeInfo->r2type == OP_YMM || CodeInfo->r1type == OP_YMM) && 
                       (broadflags & ~EVEX_P2AAAMASK) == 0x20){ //{1to4}
                  if ((CodeInfo->mem_type != MT_QWORD) && (CodeInfo->mem_type != MT_EMPTY))
                    EmitError( INVALID_OPERAND_SIZE );
                  if ((CodeInfo->pinstr->prefix & 0xE0) == QSIZE){
                    CodeInfo->mem_type = MT_QWORD;
                    CodeInfo->evex_p2 |= 0x20;
                  }
                  else 
                    EmitError( MISMATCH_IN_THE_NUMBER_OF_BROADCASTING_ELEMENTS );
              }
              else if ((CodeInfo->r2type == OP_YMM || CodeInfo->r1type == OP_YMM) &&
                       (broadflags & ~EVEX_P2AAAMASK) == 0x30){ //{1to8}
                if ((CodeInfo->mem_type != MT_DWORD) && (CodeInfo->mem_type != MT_EMPTY) &&
                    (CodeInfo->mem_type != MT_QWORD) && (CodeInfo->mem_type != MT_OWORD)){
                  EmitError(INVALID_OPERAND_SIZE);
                  }
                  if ((CodeInfo->pinstr->prefix & 0xE0) == DSIZE){
                    CodeInfo->mem_type = MT_DWORD;
                    CodeInfo->evex_p2 |= 0x20;
                  }
                  else if ((CodeInfo->pinstr->prefix & 0xE0) == QSIZE){
                    CodeInfo->mem_type = MT_QWORD;
                    CodeInfo->evex_p2 |= 0x40;
                  }
                  else 
                    EmitError( MISMATCH_IN_THE_NUMBER_OF_BROADCASTING_ELEMENTS );
              }
              else if (( CodeInfo->r2type == OP_ZMM || CodeInfo->r1type == OP_ZMM)&& 
                (broadflags & ~EVEX_P2AAAMASK) == 0x30){ //{1to8}
                  if ((CodeInfo->pinstr->prefix & 0xE0) == QSIZE){
                    CodeInfo->mem_type = MT_QWORD;
                    CodeInfo->evex_p2 |= 0x40;
                  }
                  else if ((CodeInfo->pinstr->prefix & 0xE0) == DSIZE){
                    CodeInfo->mem_type = MT_DWORD;
                    CodeInfo->evex_p2 |= 0x40;
                  }
                  else 
                    EmitError( MISMATCH_IN_THE_NUMBER_OF_BROADCASTING_ELEMENTS );
              }
              else if ((CodeInfo->r2type == OP_ZMM ||CodeInfo->r1type == OP_ZMM)&& 
                (broadflags & ~EVEX_P2AAAMASK) == 0x40){ //{1to16}
                  if ((CodeInfo->pinstr->prefix & 0xE0) == DSIZE){
                    CodeInfo->mem_type = MT_DWORD;
                    CodeInfo->evex_p2 |= 0x40;
                  }
                  else 
                    EmitError(MISMATCH_IN_THE_NUMBER_OF_BROADCASTING_ELEMENTS);
              }
            }
              else{   //check all for size
                if (CodeInfo->r2type == OP_YMM){              
                  if (CodeInfo->mem_type == MT_YMMWORD || (CodeInfo->mem_type == MT_EMPTY)){
                    CodeInfo->evex_p2 |= 0x20;
                    if ((CodeInfo->opnd[OPND3].data32h > 0x20)||(CodeInfo->opnd[OPND3].data32h > ~0x20)) 
                      CodeInfo->tuple = TRUE;  
                  }
                  
                  else{
                    if (CodeInfo->token < T_VPSLLD && CodeInfo->token > T_VPRORVQ)
                    EmitError(INVALID_OPERAND_SIZE);
                    }
                }
                else if (CodeInfo->r2type == OP_XMM){
                  if ((CodeInfo->mem_type == MT_OWORD && CodeInfo->mem_type == MT_EMPTY)){
                    if ((CodeInfo->opnd[OPND3].data32h > 0x10)||(CodeInfo->opnd[OPND3].data32h > ~0x10))
                      CodeInfo->tuple = TRUE;
                  }
                  else if ((CodeInfo->token >= T_VCMPEQSD && CodeInfo->token <= T_VCMPTRUE_USSD) &&
                    (CodeInfo->mem_type == MT_QWORD)){
                      if ((CodeInfo->opnd[OPND3].data32h > 8)||(CodeInfo->opnd[OPND3].data32h > ~8))
                      CodeInfo->tuple = TRUE;
                  }
                  else if ((CodeInfo->token >= T_VCMPEQSS && CodeInfo->token <= T_VCMPTRUE_USSS) &&
                    (CodeInfo->mem_type == MT_DWORD)){
                      if ((CodeInfo->opnd[OPND3].data32h > 4)||(CodeInfo->opnd[OPND3].data32h > ~4))
                      CodeInfo->tuple = TRUE;
                  }
                }
                else if (CodeInfo->r2type == OP_ZMM){
                  if (CodeInfo->mem_type == MT_ZMMWORD || CodeInfo->mem_type == MT_EMPTY ||
                      CodeInfo->mem_type == MT_OWORD || CodeInfo->mem_type == MT_QWORD){
                    CodeInfo->evex_p2 |= 0x40;
                    if ((CodeInfo->opnd[OPND3].data32h > 0x40)||(CodeInfo->opnd[OPND3].data32h > ~0x40))
                      CodeInfo->tuple = TRUE;
                  }
                }
                if (CodeInfo->opnd[OPND3].data32l != -1){
                  if ((CodeInfo->r2type == OP_YMM) && (CodeInfo->opnd[OPND3].type != OP_ZMM)){
                    if ((CodeInfo->token >= T_VCMPEQPD) && (CodeInfo->token <= T_VCMPTRUE_USSS))
                      CodeInfo->evex_p2 |= 0x40;
                    if (CodeInfo->opnd[OPND3].data32l >= 0x20)
                      CodeInfo->tuple = TRUE;
                  }
                }
              }
              if (CodeInfo->evex_sae){
                CodeInfo->evex_p2 &= ~0x70;     //clear bites 6,5,4
                c = CodeInfo->evex_sae - 0x10;  //subtract SAE to get a proper decorator
                /* here we need to test for corect use of decorators  
                 * if it is {sae} c will be zero, in that case we need to add 0x10 to c
                 * if we need {sae}
                */  
                if (c == 0) c = 0x10;
                CodeInfo->evex_p2 |= c;
              }
                if (CodeInfo->r2type == OP_YMM) CodeInfo->evex_p2 |= EVEX_P2LMASK;
                else if (CodeInfo->opnd[OPND3].type == OP_ZMM)CodeInfo->evex_p2 |= EVEX_P2L1MASK; 
                if ((CodeInfo->token >= T_VPGATHERDD && CodeInfo->token <= T_VGATHERQPS)){
                  CodeInfo->evex_p2 &= ~EVEX_P2L1MASK;
                  CodeInfo->evex_p2 &= ~EVEX_P2LMASK;
                  if (CodeInfo->r1type == OP_YMM) CodeInfo->evex_p2 |= EVEX_P2LMASK;
                  else if (CodeInfo->r1type == OP_ZMM) CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                  }
                  if ((CodeInfo->token == T_VEXTRACTPS)||(CodeInfo->token == T_VCVTSD2USI)||     // 1598    1599
                    (CodeInfo->token >= T_VMOVHPD)&&(CodeInfo->token <= T_VMOVSS))               // 1936    1937
                    CodeInfo->evex_p2 &= ~EVEX_P2L1MASK;
                  if (CodeInfo->token == T_VCVTSS2USI || CodeInfo->token == T_VCVTSD2USI){
                    if (CodeInfo->evex_sae){
                        CodeInfo->evex_p2 &= ~0x70;     //clear bites 6,5,4
                        c = CodeInfo->evex_sae - 0x10;  //subtract SAE to get a proper decorator
                        /* here we need to test for corect use of decorators  
                         * if it is {sae} c will be zero, in that case we need to add 0x10 to c
                         * if we need {sae}
                        */   
                        if (c == 0) c += 0x10;
                        CodeInfo->evex_p2 |= c;
                      }
                    }
                if (CodeInfo->evex_flag){
                  if (CodeInfo->vexregop){
                    if (CodeInfo->vexregop <= 16) CodeInfo->evex_p2 |= EVEX_P2VMASK;
                    else CodeInfo->evex_p2 &= ~EVEX_P2VMASK;
                  }
                  else CodeInfo->evex_p2 |= EVEX_P2VMASK;
                  CodeInfo->tuple = TRUE;
                  CodeInfo->evex_p2 |= decoflags;
                  if (CodeInfo->token == T_VCVTDQ2PD || CodeInfo->token == T_VCVTPS2PD ||
                    CodeInfo->token == T_VMOVDQA || CodeInfo->token == T_VMOVDQU || 
                    CodeInfo->token == T_VCVTPD2PS){ 
                     CodeInfo->evex_p2 &= ~EVEX_P2LMASK;
                     CodeInfo->evex_p2 &= ~EVEX_P2L1MASK;
                    if (CodeInfo->r1type == OP_YMM || CodeInfo->r2type == OP_YMM) 
                      CodeInfo->evex_p2 |= EVEX_P2LMASK;
                    else if (CodeInfo->r1type == OP_ZMM || CodeInfo->r2type == OP_ZMM)
                      CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                  }
                  if (!CodeInfo->evex_sae){
                    switch (CodeInfo->token){
                    case T_VCVTPD2DQ:
                    case T_VCVTTPD2DQ:
                    case T_VCVTPD2PS:
                    case T_VCVTPD2UDQ:
                      if (CodeInfo->r1type == OP_YMM){
                        CodeInfo->evex_p2 &= ~EVEX_P2LMASK;
                        CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                        }
                      else if (CodeInfo->mem_type == MT_YMMWORD)
                        CodeInfo->evex_p2 |= EVEX_P2LMASK;
                      break;
                    case T_VCVTPS2UDQ:
                      if (CodeInfo->r1type == OP_YMM)
                        CodeInfo->evex_p2 |= EVEX_P2LMASK;
                      else if (CodeInfo->r1type == OP_ZMM)
                        CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                      break;
                      /* set EVEX_P2L1MASK  for VCVTDQ2PD, v2.46 */
                    case T_VCVTDQ2PD:
                      if (CodeInfo->r1type == OP_ZMM){
                        CodeInfo->evex_p2 &= ~EVEX_P2LMASK;
                        CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                        }
                      break;
                    case  T_VCVTDQ2PS:
                    case  T_VPSHUFD:
                    case T_VCVTPS2DQ:
                    case T_VCVTPD2QQ:
                    case T_VCVTPD2UQQ:
                    case T_VCVTPS2UQQ:
                    case T_VCVTQQ2PD:
                    case T_VCVTTPS2DQ:
                    case T_VMOVDDUP:
                      CodeInfo->evex_p2 &= ~EVEX_P2LMASK;
                      CodeInfo->evex_p2 &= ~EVEX_P2L1MASK;
                      if (CodeInfo->r1type == OP_YMM || CodeInfo->r2type == OP_YMM)
                        CodeInfo->evex_p2 |= EVEX_P2LMASK;
                      else if (CodeInfo->r1type == OP_ZMM || CodeInfo->r2type == OP_ZMM)
                        CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                      }
                  }
                  if (CodeInfo->token == T_VCVTPS2PD || CodeInfo->token == T_VCVTUDQ2PD || 
                      CodeInfo->token == T_VCVTUDQ2PS ||CodeInfo->token == T_VCVTUQQ2PD){
                    if (CodeInfo->r1type == OP_ZMM && CodeInfo->r2type == OP_YMM){
                      CodeInfo->evex_p2 &= ~EVEX_P2LMASK;
                      CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                      }
                    }
                  if (CodeInfo->token == T_VCVTPS2QQ || CodeInfo->token == T_VCVTPS2UQQ || 
                      CodeInfo->token == T_VCVTTPD2QQ || CodeInfo->token == T_VCVTTPD2UQQ ||
                      CodeInfo->token == T_VMOVSHDUP || CodeInfo->token == T_VMOVSLDUP ||
                      CodeInfo->token == T_VCVTTPS2UQQ ||CodeInfo->token == T_VCVTTPS2QQ){ 
                    if (CodeInfo->r1type == OP_YMM ){
                      CodeInfo->evex_p2 &= ~EVEX_P2L1MASK;
                      CodeInfo->evex_p2 |= EVEX_P2LMASK;
                      }
                    else if (CodeInfo->r1type == OP_ZMM ){
                      CodeInfo->evex_p2 &= ~EVEX_P2LMASK;
                      CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                      }
                    }
                if ((CodeInfo->token >= T_ADDPD && CodeInfo->token <= T_SUBPS) || 
                    CodeInfo->token == T_VCVTUDQ2PD || CodeInfo->token == T_VCVTUQQ2PD || CodeInfo->token == T_VCVTUDQ2PS||
                    (CodeInfo->token >= T_VADDPD && CodeInfo->token <= T_VSUBPS)||
                    CodeInfo->token == T_VMOVDQU8 || CodeInfo->token == T_VMOVDQU16){
                  if (CodeInfo->evex_flag == TRUE) {
                    if (CodeInfo->opnd[OPND2].type & OP_M_ANY){
                      if (CodeInfo->r1type == OP_YMM)CodeInfo->evex_p2 |= EVEX_P2LMASK;
                      else if (CodeInfo->r1type == OP_ZMM)CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                      }
                    }
                  }
                if (CodeInfo->token == T_VCVTQQ2PS ||                                        /*  was here CodeInfo->token == T_VCVTPD2UDQ || */
                  CodeInfo->token == T_VCVTUQQ2PD || CodeInfo->token == T_VCVTUDQ2PS ||
                    CodeInfo->token == T_VCVTUDQ2PD || CodeInfo->token == T_VCVTTPD2UDQ ||
                    CodeInfo->token == T_VCVTUQQ2PS){
                    if (CodeInfo->r1type == OP_XMM ){
                      if ((CodeInfo->token == T_VCVTTPD2UDQ  || CodeInfo->token == T_VCVTUDQ2PD ||
                        CodeInfo->token == T_VCVTQQ2PS)&&
                        CodeInfo->opnd[OPND2].type & OP_M128) 
                        ;/* skip */
                      else if (CodeInfo->opnd[OPND2].type & OP_M256){
                        CodeInfo->evex_p2 &= ~EVEX_P2L1MASK;
                        CodeInfo->evex_p2 |= EVEX_P2LMASK;
                        }
                      }
                    else if (CodeInfo->r1type == OP_YMM ){
                      if ((CodeInfo->token == T_VCVTUDQ2PD || CodeInfo->token == T_VCVTUDQ2PS||
                        CodeInfo->token == T_VCVTUQQ2PD) && (CodeInfo->opnd[OPND2].type & OP_M128))
                          ;/* skip */
                      else if (CodeInfo->token == T_VCVTUDQ2PD && CodeInfo->opnd[OPND2].type == OP_XMM)
                          CodeInfo->evex_p2 |= EVEX_P2LMASK;
                      else if (CodeInfo->token == T_VCVTUDQ2PD && CodeInfo->opnd[OPND2].type == OP_YMM)
                        ;//CodeInfo->evex_p2 |= EVEX_P2LMASK;
                      else if ((CodeInfo->token == T_VCVTUQQ2PD||CodeInfo->token == T_VCVTUDQ2PS) &&
                        CodeInfo->opnd[OPND2].type == OP_YMM)   /*ymm1{k1}{z},ymm2*/
                            CodeInfo->evex_p2 |= EVEX_P2LMASK;
                      else{
                        CodeInfo->evex_p2 &= ~EVEX_P2LMASK;
                        CodeInfo->evex_p2 |= EVEX_P2L1MASK;
                        }
                      }

                  }
                  OutputCodeByte(CodeInfo->evex_p2);
                }
            }
        }
    } else {
#endif

#if AMD64_SUPPORT
    /* the REX prefix must be located after the other prefixes */
    if( CodeInfo->prefix.rex != 0 ) {
        if ( CodeInfo->Ofssize != USE64 ) {
            EmitError( INVALID_OPERAND_SIZE );
        }
        OutputCodeByte( CodeInfo->prefix.rex | 0x40 );
    }
#endif

    /*
     * Output extended opcode
     * special case for some 286 and 386 instructions
     * or 3DNow!, MMX and SSEx instructions
     */
    if ( ins->byte1_info >= F_0F ) {
        OutputCodeByte( EXTENDED_OPCODE );
        switch ( ins->byte1_info ) {
        case F_0F0F:   OutputCodeByte( EXTENDED_OPCODE ); break;
        case F_0F38:
        case F_F20F38:
        case F_660F38: OutputCodeByte( 0x38 );            break;
        case F_0F3A:
        case F_660F3A: OutputCodeByte( 0x3A );            break;
        }
    }

#if AVXSUPP
    }
#endif
    switch (ins->rm_info) {
      case R_in_OP:
        OutputCodeByte(ins->opcode | (CodeInfo->rm_byte & NOT_BIT_67));
        break;
      case no_RM:
        if (CodeInfo->token == T_CLAC)
          OutputCodeByte(0x01);
        OutputCodeByte(ins->opcode | CodeInfo->iswide);
        break;
      case no_WDS:
        CodeInfo->iswide = 0;
        /* no break */
      default: /* opcode (with w d s bits), rm-byte */
        if (ins->byte1_info != F_0F0F) {
          if ((CodeInfo->token >= T_KADDB) && (CodeInfo->token <= T_KMOVW)){
            if ((CodeInfo->token >= T_KMOVB) && (CodeInfo->token <= T_KMOVW)){
              const  struct instr_item *p = CodeInfo->pinstr;
              int cnt;
              int type1 = CodeInfo->opnd[OPND1].type;
              int type2 = CodeInfo->opnd[OPND2].type;
              CodeInfo->tuple = 0;
              /* at least one operand must be K register */
              if (type1 == OP_K || type2 == OP_K)
                ;    //OK
              else
                EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
              /* find the proper opcode for the command movw KREG,GP_REG */
              /* it could be AL, AX, EAX or RAX, make them GP reg v2.38*/
              type1 &= ~0x200;    /* clear bit 2 in that case */
              type2 &= ~0x200;
              for (cnt = 0; cnt < 5; cnt++, p++){
                if ((opnd_clstab[p->opclsidx].opnd_type[OPND1] == type1) &&
                    (opnd_clstab[p->opclsidx].opnd_type[OPND2] == type2))
                    break;
                }
              if (cnt < 5) {   //there are 5 combinations
                OutputCodeByte(p->opcode);
                }
              else
                OutputCodeByte(ins->opcode);
              }
            else
              OutputCodeByte(ins->opcode);
            }
          else{
            if (CodeInfo->token == T_VMOVDQA || CodeInfo->token == T_VMOVDQU ||
                CodeInfo->token == T_VMOVDQA32 || CodeInfo->token == T_VMOVDQU32 ||
                CodeInfo->token == T_VMOVDQA64 || CodeInfo->token == T_VMOVDQU64){
              if (CodeInfo->opnd[OPND1].type & OP_M_ANY || CodeInfo->opnd[OPND2].type & OP_M_ANY){
                if (CodeInfo->indexreg == 0xFF && CodeInfo->basereg == 0xFF){  // fix for RIP displacement v2.44 && CodeInfo->basetype != 0xFE 
                  CodeInfo->rm_byte &= ~MOD_11;
                  CodeInfo->rm_byte |= MOD_10;
                  CodeInfo->tuple = 0;
                  }
                }
              else if (CodeInfo->opnd[OPND1].type & OP_M_ANY){
                if (CodeInfo->mem_type == MT_EMPTY);
                else if (CodeInfo->opnd[OPND1].type == OP_M128 &&  CodeInfo->opnd[OPND2].type & OP_XMM);
                else if (CodeInfo->opnd[OPND1].type == OP_M256 &&  CodeInfo->opnd[OPND2].type == OP_YMM);
                else if (CodeInfo->opnd[OPND1].type == OP_M512 &&  CodeInfo->opnd[OPND2].type == OP_ZMM);
                else
                  EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
                }

              }
            /* prevent producing incorrect code for VMOVD, v2.39 */
            if (CodeInfo->token == T_VMOVD){
              if (CodeInfo->opnd[OPND1].type == OP_XMM && CodeInfo->opnd[OPND2].type == OP_XMM)
                EmitError(INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS);
              }
            if (CodeInfo->token == T_ADOX) {
              OutputCodeByte(ins->opcode);
              OutputCodeByte(0xF6);
              }
            else if (CodeInfo->token == T_VMOVQ){
              if (CodeInfo->opnd[OPND1].type == OP_XMM && (CodeInfo->opnd[OPND2].type == OP_XMM || CodeInfo->opnd[OPND2].type == OP_M)) {
                OutputCodeByte(0x7E);
                }
              else if (CodeInfo->first_byte == 0xC5){
                if (CodeInfo->basereg == 0x10){
                    OutputCodeByte(0xD6);
                  }
                else if (CodeInfo->opnd[OPND1].type == OP_XMM && CodeInfo->opnd[OPND2].type & OP_M)
                  OutputCodeByte(0x7E);
                else if (CodeInfo->opnd[OPND1].type & OP_M64 && CodeInfo->opnd[OPND2].type == OP_XMM)
                  OutputCodeByte(0xD6);
                }
              else
                OutputCodeByte(ins->opcode | CodeInfo->iswide | CodeInfo->opc_or);
              }
            else if (CodeInfo->token == T_MOVQ && CodeInfo->basereg != 0x10){
                  if (CodeInfo->opnd[OPND1].type == OP_XMM && (CodeInfo->opnd[OPND2].type & OP_MS))
                    OutputCodeByte(0x7E);
                  else if ((CodeInfo->opnd[OPND1].type & OP_MS) && CodeInfo->opnd[OPND2].type == OP_XMM)
                    OutputCodeByte(0xD6);
                  else 
                    OutputCodeByte(ins->opcode | CodeInfo->iswide | CodeInfo->opc_or);
            }
            else
              OutputCodeByte(ins->opcode | CodeInfo->iswide | CodeInfo->opc_or);
            }
          }
        /* emit ModRM byte; bits 7-6 = Mod, bits 5-3 = Reg, bits 2-0 = R/M */
        if ((CodeInfo->token == T_VRNDSCALEPD) || (CodeInfo->token == T_VRNDSCALEPS))CodeInfo->tuple = TRUE;
        if ((CodeInfo->token >= T_KADDB) && (CodeInfo->token <= T_KUNPCKDQ)) {       //here pay atention
          c = CodeInfo->reg1;
          tmp = MOD_11;           //bits 7-6 = Mod
          c = (c << 3);           //bits 5-3 = Reg,
          tmp |= c;
          tmp |= CodeInfo->reg3;  //bits 2-0 = R/M
          }
        else if ((CodeInfo->token >= T_KNOTB) && (CodeInfo->token <= T_KORTESTQ)) {
          tmp = MOD_11;                 //bits 7-6 = Mod
          tmp |= (CodeInfo->reg1 << 3); //bits 5-3 = Reg,
          tmp |= CodeInfo->reg2;        //bits 2-0 = R/M
          }
        else
          tmp = ins->rm_byte | CodeInfo->rm_byte;
        if (CodeInfo->token == T_VCVTPS2PH){//(!CodeInfo->evex_flag) && 
          //tmp &= 0xC0;
          c = CodeInfo->reg2;
          if (c > 15)c -= 16;
          if (c > 7)c -= 8;
          c = (c << 3);
          tmp |= c;
          }
        if (CodeInfo->basetype == T_RIP){
          tmp &= ~MOD_10;
          CodeInfo->tuple = 0;   /* for a RIP relative addressing tuple can not be used */
          }
        if (CodeInfo->token == T_VEXTRACTPS){ /* fix for missing tuple, v2.46 */
          if ((CodeInfo->opnd[OPND1].type & OP_M_ANY) && (CodeInfo->basetype != T_RIP))
            CodeInfo->tuple = TRUE;
          }
        /* use only if TypleType is present  */
        if (CodeInfo->tuple){
          int index = -1;
          int d;
          if ((CodeInfo->opnd[OPND1].type & OP_M_ANY) &&
              (CodeInfo->opnd[OPND1].data32l != -1))  index = OPND1;
          else if ((CodeInfo->opnd[OPND2].type & OP_M_ANY) &&
                   (CodeInfo->opnd[OPND1].data32l != -1))
                   index = OPND2;
          if ((index != -1) && ((Check4CompDisp8(CodeInfo, &comprdsp, &d, CodeInfo->opnd[index].data32l)) && comprdsp)){
            CodeInfo->opnd[index].data32l = comprdsp;
            tmp &= ~MOD_10;     /* if        mod = 10, r/m = 100, s-i-b is present */
            tmp |= MOD_01;      /* change to mod = 01, r/m = 100, s-i-b is present */
            }
          else if (CodeInfo->opnd[OPND2].type & OP_I8_U){
            if ((CodeInfo->token >= T_VPSLLW) && (CodeInfo->token <= T_VPSRLQ) ||
                (CodeInfo->token == T_VRNDSCALEPD) || (CodeInfo->token == T_VRNDSCALEPS) ||
                (CodeInfo->token >= T_VPSLLVD) && (CodeInfo->token <= T_VPSRLVW)){
              if ((CodeInfo->vexconst) && ((Check4CompDisp8(CodeInfo, &comprdsp, &d, CodeInfo->vexconst)) && comprdsp)){
                CodeInfo->opnd[OPND1].data32l = comprdsp;
                tmp &= ~MOD_10;     /* if        mod = 10, r/m = 100, s-i-b is present */
                tmp |= MOD_01;      /* change to mod = 01, r/m = 100, s-i-b is present */
                if ((CodeInfo->token == T_VRNDSCALEPD) || (CodeInfo->token == T_VRNDSCALEPS)){
                  c = CodeInfo->reg2;
                  if (c > 15) c -= 16;
                  if (c > 7) c -= 8;
                  tmp |= c;
                  }
                }
              else{
                CodeInfo->tuple = 0;
                if (CodeInfo->indexreg != 0xff){
                  tmp &= ~NOT_BIT_345;
                  tmp &= ~BIT_012;
                  tmp |= MOD_10;
                  tmp |= RM_SIB;
                  c = CodeInfo->indexreg;
                  c = (c &= 0x7) << 3;
                  CodeInfo->sib |= c;
                  c = CodeInfo->basereg;
                  c &= 0x7;
                  CodeInfo->sib |= c;
                  CodeInfo->rm_byte = tmp;
                  CodeInfo->sib |= MOD_11;
                  CodeInfo->opnd[OPND1].data32l = CodeInfo->vexconst;
                  }
                else {
                  if ((CodeInfo->opnd[OPND1].type == OP_R64) || (CodeInfo->opnd[OPND1].type == OP_RAX) ||
                      (CodeInfo->opnd[OPND1].type == OP_R32) || (CodeInfo->opnd[OPND1].type == OP_EAX)){
                    tmp &= ~MOD_11;
                    if (CodeInfo->vexconst){
                      tmp |= MOD_10;
                      CodeInfo->rm_byte = tmp;
                      CodeInfo->opnd[OPND1].data32l = CodeInfo->vexconst;
                      }
                    }
                  else if ((CodeInfo->opnd[OPND1].type == OP_XMM) || (CodeInfo->opnd[OPND1].type == OP_YMM) ||
                           (CodeInfo->opnd[OPND1].type == OP_ZMM)){
                    CodeInfo->tuple = 0;
                    if (CodeInfo->vexconst){
                      tmp &= ~NOT_BIT_345;
                      tmp &= ~BIT_012;
                      tmp |= MOD_10;
                      tmp |= RM_SIB;
                      if (CodeInfo->indexreg != 0xFF){
                        c = CodeInfo->indexreg;
                        c = (c &= 0x07) << 3;
                        CodeInfo->sib |= c;
                        c = CodeInfo->basereg;
                        c &= 0x7;
                        CodeInfo->sib |= c;
                        CodeInfo->sib &= 0xf0;
                        }
                      else{
                        tmp &= ~0x07;
                        tmp |= (CodeInfo->reg2 & 0x07);
                        }
                      CodeInfo->rm_byte = tmp;
                      CodeInfo->opnd[OPND1].data32l = CodeInfo->vexconst;
                      }
                    else {
                      if ((CodeInfo->r2type) && ((CodeInfo->token == T_VRNDSCALEPD) || (CodeInfo->token == T_VRNDSCALEPS)))
                        tmp &= ~0xc0;
                      if ((CodeInfo->token >= T_VPSLLW) && (CodeInfo->token <= T_VPSRLQ) ||
                          (CodeInfo->token >= T_VPSLLVD) && (CodeInfo->token <= T_VPSRLVW)) {
                        tmp &= ~7;
                        if ((CodeInfo->r2type == OP_R64) || (CodeInfo->r2type == OP_R32)) tmp &= ~0xc0;
                        }
                      c = CodeInfo->reg2;
                      if (c > 15) c -= 16;
                      if (c > 7) c -= 8;
                      tmp |= c;
                      }
                    }
                  }
                }
              }
            }
          else{
            CodeInfo->tuple = 0;
            if (CodeInfo->token >= T_VPGATHERDD && CodeInfo->token <= T_VSCATTERQPD){
              if (CodeInfo->token != T_VGATHERDPD && CodeInfo->token != T_VGATHERQPD &&
                  CodeInfo->token != T_VPGATHERDQ && CodeInfo->token != T_VPGATHERQQ&&
                  CodeInfo->token != T_VGATHERDPS && CodeInfo->token != T_VPGATHERDD&&
                  CodeInfo->token != T_VGATHERQPS && CodeInfo->token != T_VPGATHERQD) 
                  tmp &= ~0xc0;
                  CodeInfo->rm_byte = tmp;
              }
            }
          }
        if (CodeInfo->token == T_VCVTPS2PH || CodeInfo->token == T_VCVTSI2SS){
          if (!comprdsp) CodeInfo->tuple = 0;
          if (CodeInfo->indexreg != 0xFF){
            c = CodeInfo->indexreg;
            c = (c &= 0x07) << 3;
            CodeInfo->sib |= c;
            c = CodeInfo->basereg;
            c &= 0x7;
            CodeInfo->sib |= c;
            CodeInfo->sib = 0xf0;
            tmp |= RM_SIB;
            }
          CodeInfo->rm_byte = tmp;
          }
        if (CodeInfo->token == T_BLSMSK){
          tmp &= ~0x38;
          tmp |= 0x10;
          }
        if (CodeInfo->token == T_BLSR){
          tmp &= ~0x38;
          tmp |= 0x08;
          }
        /* ModR/M.mod (bit 7:6) = 0 specifies the scale factor [Scaled Vector Register] + Disp32, Uasm 2.16 */
        if ((CodeInfo->basetype == 0xfe) && ((CodeInfo->indextype == OP_XMM) ||
          (CodeInfo->indextype == OP_YMM) || (CodeInfo->indextype == OP_ZMM))){
          if (CodeInfo->basereg != 0xff)
            tmp &= ~0xC0; // we need the scale field to be 00 for VSIB without base register EG: [XMM4+1*8]
          }
        if (CodeInfo->isptr)
          tmp &= 0xfe;
        if (CodeInfo->token == T_RDPID){
          tmp = NOT_BIT_012;
          tmp |= CodeInfo->reg1;
          }
        /* UASM 2.43 - Use signed byte displacement form optimisation and remove 0 displacement */
        if (CodeInfo->token == T_VMOVDQA || CodeInfo->token == T_VMOVDQU)
          {
          if ((CodeInfo->opnd[OPND2].type & OP_M_ANY) && (CodeInfo->opnd[OPND2].data32l >= -128) &&
              (CodeInfo->opnd[OPND2].data32l < 128) && (CodeInfo->basereg != 0xff))    // fix for RIP displacement v2.44
            {
            tmp &= NOT_BIT_67;
            tmp |= MOD_01;
            if (CodeInfo->opnd[OPND2].data32l == 0)
              tmp &= NOT_BIT_6;
            }
          else if ((CodeInfo->opnd[OPND1].type & OP_M_ANY) && (CodeInfo->opnd[OPND1].data32l >= -128) && (CodeInfo->opnd[OPND1].data32l < 128))
            {
            tmp &= NOT_BIT_67;
            tmp |= MOD_01;
            if (CodeInfo->opnd[OPND1].data32l == 0)
              tmp &= NOT_BIT_6;
            }
          }
        /* UASM 2.46 prevent evex instructions trying to use 1byte displacement when k-mask register used */
        switch (CodeInfo->token){
              case T_VGATHERDPD: 
              case T_VGATHERDPS: 
              case T_VPGATHERDQ: 
              case T_VGATHERPF0DPS: 
              case T_VGATHERPF0QPD: 
              case T_VGATHERPF1DPD: 
              case T_VGATHERPF1QPD: 
              case T_VSCATTERPF0DPD: 
              case T_VSCATTERPF0QPD: 
              case T_VSCATTERPF1DPD: 
              case T_VSCATTERPF1QPD: 
              case T_VSCATTERDPD: 
              case T_VSCATTERQPD: 
              case T_VPSCATTERDQ: 
              case T_VGATHERQPD:
              case T_VPGATHERDD:
              case T_VGATHERPF0DPD:
              case T_VPGATHERQQ:
              case T_VGATHERPF0QPS:
              case T_VGATHERPF1DPS:
              case T_VGATHERPF1QPS:
              case T_VSCATTERPF0DPS:
              case T_VSCATTERPF0QPS:
              case T_VSCATTERPF1DPS:
              case T_VSCATTERPF1QPS:
              case T_VSCATTERDPS:
              case T_VPSCATTERDD:
              case T_VPSCATTERQQ:
				  if (CodeInfo->evex_flag && CodeInfo->tuple == 0 )/* && decoflags != 0 */
				  {
            if (((CodeInfo->opnd[OPND1].type & OP_M_ANY) && (CodeInfo->opnd[OPND1].data32l)) ||
                ((CodeInfo->opnd[OPND2].type & OP_M_ANY) && (CodeInfo->opnd[OPND2].data32l)))
             {
              tmp &= NOT_BIT_67;
              tmp |= MOD_10;                    /* use dword displacement */
              CodeInfo->rm_byte = tmp;
             }
				  }
				  break;
			  case T_VMOVUPD:
			  case T_VMOVAPD:
			  case T_VMOVUPS:
			  case T_VMOVAPS:
				if (((CodeInfo->opnd[OPND1].type & OP_M_ANY) && CodeInfo->opnd[OPND1].data64 != 0) || 
					((CodeInfo->opnd[OPND2].type & OP_M_ANY) && CodeInfo->opnd[OPND2].data64 != 0))
				{
					if (CodeInfo->evex_flag && CodeInfo->tuple == 0) /* && decoflags != 0 */
					{
						tmp &= NOT_BIT_67;
            tmp |= MOD_10;               /* use long word displacement */
						CodeInfo->rm_byte = tmp;
					}
				}

            }
		    OutputCodeByte( tmp );

        //if( ( CodeInfo->Ofssize == USE16 && CodeInfo->prefix.adrsiz == 0 ) ||
        //   ( CodeInfo->Ofssize == USE32 && CodeInfo->prefix.adrsiz == 1 ) )
        //    return; /* no SIB for 16bit */
        if ( CodeInfo->Ofssize == USE16 && CodeInfo->prefix.adrsiz == 0 ) 
            return; /* no SIB for 16bit */

        switch ( tmp & NOT_BIT_345 ) {
        case 0x04: /* mod = 00, r/m = 100, s-i-b is present */
        case 0x44: /* mod = 01, r/m = 100, s-i-b is present */
        case 0x84: /* mod = 10, r/m = 100, s-i-b is present */
            /* emit SIB byte; bits 7-6 = Scale, bits 5-3 = Index, bits 2-0 = Base */
			if (CodeInfo->isptr)
				OutputCodeByte(0x25);
			else
				OutputCodeByte( CodeInfo->sib );

        }
    }
    return;
}

static void output_data(struct code_info *CodeInfo, enum operand_type determinant, int index)
/***************************************************************************************************/
/*
 * output address displacement and immediate data;
 */
{
  int       size = 0;

  /* John: Fixed specially typed INS/OUTS instructions where the operands MUST be ignored, they're purely for documentation purposes */
  if ( (CodeInfo->token == T_INS && CodeInfo->opnd[OPND1].type != OP_NONE) ||
	  (CodeInfo->token == T_OUTS && CodeInfo->opnd[OPND2].type != OP_NONE) )
	  return;
  
  /* Different forms of xlat, but all memory types assume byte to ds:ebx */
  if (CodeInfo->token == T_XLAT || CodeInfo->token == T_XLATB)
	  return;

  /* Never output immediate data for a lods, movs or stos */
  if (CodeInfo->token == T_LODS || CodeInfo->token == T_MOVS || CodeInfo->token == T_STOS)
	  return;

#if AVXSUPP
    if (CodeInfo->token >= VEX_START){
      if ((CodeInfo->token == T_ANDN) || (CodeInfo->token == T_MULX) ||
        (CodeInfo->token == T_PDEP) || (CodeInfo->token == T_PEXT)){
        if ((CodeInfo->opnd[OPND2].data32l == 0) || (index == 2))
          return;
      }
      if ((CodeInfo->token >= T_BEXTR) && (CodeInfo->token <= T_SHRX) || (CodeInfo->token == T_BZHI)) {
        if (CodeInfo->opnd[OPND2].data32l == 0) return;
        if ((index == 0) || (index == 2))
          return;
      }
      if (CodeInfo->opnd[OPND2].type == OP_I8 && CodeInfo->evex_flag){
        if ((CodeInfo->token >= T_VPSLLW) && (CodeInfo->token <= T_VPSRLQ) ||
          (CodeInfo->token >= T_VPSLLVD) && (CodeInfo->token <= T_VPSRLVW) ||
          (CodeInfo->token == T_VRNDSCALEPD) || (CodeInfo->token == T_VRNDSCALEPS))
        {
          if (((CodeInfo->rm_byte) >> 6) == 2)size = 4;
          else if (((CodeInfo->rm_byte) >> 6) == 1)size = 2;
        }
      }
    } 
    else
#endif
    /* skip the memory operand for XLAT/XLATB and string instructions! */
    if ( CodeInfo->token == T_XLAT || CodeInfo->token == T_XLATB ||
        CodeInfo->pinstr->allowed_prefix == AP_REP ||
        CodeInfo->pinstr->allowed_prefix == AP_REPxx ) {
        /* v2.06: no need anymore to modify the fixup field, it's
         * used inside OutputBytes() only.
         */
        //CodeInfo->InsFixup[index] = NULL;

        ;//return;
    }
#ifdef DEBUG_OUT
    if ( CodeInfo->opnd[index].InsFixup )
        DebugMsg1(("output_data(idx=%u, op=%" I32_SPEC "X [data=%" I32_SPEC "X fixup=%p typ=%u] ) enter [rm=%X]\n", index, determinant, CodeInfo->opnd[index].data32l, CodeInfo->opnd[index].InsFixup, CodeInfo->opnd[index].InsFixup->type ,CodeInfo->rm_byte ));
    else
        DebugMsg1(("output_data(idx=%u, op=%" I32_SPEC "X [data=%" I32_SPEC "X fixup=NULL] ) enter [rm=%X]\n", index, determinant, CodeInfo->opnd[index].data32l, CodeInfo->rm_byte ));
#endif
/* determine size */
    if ( (determinant & OP_R64 || determinant & OP_R32) && CodeInfo->opnd[index].data32l != 0) {
        size = 1;
        if (CodeInfo->indexreg != 0 || decoflags != 0){
          if (CodeInfo->tuple == 0) size = 4;
          }
    }
    if( determinant & OP_I8 ) {
        size = 1;
    } else if( determinant & OP_I16 ) {
        size = 2;
    } else if( determinant & OP_I32 ) {
        size = 4;
    } else if( determinant & OP_I48 ) {
        size = 6;
#if AMD64_SUPPORT
    } else if( determinant & OP_I64 ) {
        size = 8;
#endif
    } else if( determinant & OP_M_ANY ) {
        /* switch on the mode ( the leftmost 2 bits ) */
        switch( CodeInfo->rm_byte & BIT_67 ) {
        case MOD_01:  /* 8-bit displacement */
            size = 1;
            break;
        case MOD_00: /* direct; base and/or index with no disp */
            if( ( CodeInfo->Ofssize == USE16 && CodeInfo->prefix.adrsiz == 0 ) ||
               ( CodeInfo->Ofssize == USE32 && CodeInfo->prefix.adrsiz == 1 ) ) {
                if( ( CodeInfo->rm_byte & BIT_012 ) == RM_D16 ) {
                     size = 2; /* = size of displacement */
                }
            } else {
#if AMD64_SUPPORT
                /* v2.11: special case, 64-bit direct memory addressing, opcodes 0xA0 - 0xA3 */
				if (CodeInfo->Ofssize == USE64 && (CodeInfo->pinstr->opcode & 0xFC) == 0xA0 && CodeInfo->pinstr->byte1_info == 0)
				{
					size = 8;
				}
                else
#endif
                switch( CodeInfo->rm_byte & BIT_012 ) {
                case RM_SIB: /* 0x04 (equals register # for ESP) */
                    if( ( CodeInfo->sib & BIT_012 ) != RM_D32 ) {
                        break;  /* size = 0 */
                    }
                    /* no break */
                case RM_D32: /* 0x05 (equals register # for EBP) */
                    size = 4; /* = size of displacement */
#if AMD64_SUPPORT
                    /* v2.11: overflow check for 64-bit added */
                      if ( CodeInfo->Ofssize == USE64 && CodeInfo->opnd[index].data64 >= 0x80000000 && CodeInfo->opnd[index].data64 < 0xffffffff80000000 )
                        EmitErr( INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS );  // proveri

#endif
                }
            }
            break;
        case MOD_10:  /* 16- or 32-bit displacement */
            if( ( CodeInfo->Ofssize == USE16 && CodeInfo->prefix.adrsiz == 0 ) ||
               ( CodeInfo->Ofssize == USE32 && CodeInfo->prefix.adrsiz == 1 ) && (CodeInfo->evex_flag == 0)) {
                size = 2;
            } else {
                size = 4;
            }
        }
    }
#ifdef DEBUG_OUT
    if ( size > 4 )
        DebugMsg1(( "output_data: size=%u cont=%" I64_SPEC "X\n", size, CodeInfo->opnd[index].data64 ));
    else if ( size )
        DebugMsg1(( "output_data: size=%u cont=%" I32_SPEC "X\n", size, CodeInfo->opnd[index].data32l ));
    else
        DebugMsg1(( "output_data: size=0\n" ));
#endif
    if (size) {
      if (CodeInfo->opnd[index].InsFixup) {
        /* v2.07: fixup type check moved here */
        if (Parse_Pass > PASS_1)
          if ((1 << CodeInfo->opnd[index].InsFixup->type) & ModuleInfo.fmtopt->invalid_fixup_type) {
            EmitErr(UNSUPPORTED_FIXUP_TYPE,
              ModuleInfo.fmtopt->formatname,
              CodeInfo->opnd[index].InsFixup->sym ? CodeInfo->opnd[index].InsFixup->sym->name : szNull);
            /* don't exit! */
          }
        if (write_to_file) {
  			CodeInfo->opnd[index].InsFixup->locofs = GetCurrOffset();
			if(CodeInfo->isptr)
				OutputBytes((unsigned char *)&CodeInfo->opnd[index].data32l, size, NULL);
            else
                OutputBytes((unsigned char*)&CodeInfo->opnd[index].data32l, size, CodeInfo->opnd[index].InsFixup);
          return;
        }
      }
    }
        /* if the TupleType is present output only 1 byte for the multiplier */
        if ((CodeInfo->tuple)&&(CodeInfo->opnd[OPND2].type != OP_I8)) {
          OutputByte(CodeInfo->opnd[index].data32l);
        }
		else
		{
			/* UASM 2.43 in the event of optimised signed byte displacement, only output single low byte */
			if (CodeInfo->token == T_VMOVDQA || CodeInfo->token == T_VMOVDQU)
			{
				if ((CodeInfo->opnd[OPND2].type & OP_M_ANY) && (CodeInfo->opnd[OPND2].data32l >= -128) && (CodeInfo->opnd[OPND2].data32l < 128))
				{
					if(CodeInfo->opnd[OPND2].data32l != 0)
						OutputBytes((unsigned char *)&CodeInfo->opnd[index].data32l, 1, NULL);
				}
				else if ((CodeInfo->opnd[OPND1].type & OP_M_ANY) && (CodeInfo->opnd[OPND1].data32l >= -128) && (CodeInfo->opnd[OPND1].data32l < 128))
				{
					if (CodeInfo->opnd[OPND1].data32l != 0)
						OutputBytes((unsigned char *)&CodeInfo->opnd[index].data32l, 1, NULL);
				}					
				else
					OutputBytes((unsigned char *)&CodeInfo->opnd[index].data32l, size, NULL);
			}
			else
				OutputBytes((unsigned char *)&CodeInfo->opnd[index].data32l, size, NULL);
		}
       
    return;
}

static ret_code check_3rd_operand( struct code_info *CodeInfo )
/*************************************************************/
{
    if( ( opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type_3rd == OP3_NONE ) ||
       ( opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type_3rd == OP3_HID ) )
        return( ( CodeInfo->opnd[OPND3].type == OP_NONE ) ? NOT_ERROR : ERROR );
    
    /* current variant needs a 3rd operand */
    DebugMsg1(("check_3rd_operand: tab=%X <-> codeinfo=%X\n", opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type_3rd, CodeInfo->opnd[OPND3].type ));

    switch ( opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type_3rd ) {
    case OP3_CL:
        if ( CodeInfo->opnd[OPND3].type == OP_CL )
            return( NOT_ERROR );
        break;
    case OP3_I8_U: /* IMUL, SHxD, a few MMX/SSE */
        /* for IMUL, the operand is signed! */
        if ( ( CodeInfo->opnd[OPND3].type & OP_I ) && CodeInfo->opnd[OPND3].data32l >= -128 ) {
            if ( ( CodeInfo->token == T_IMUL && CodeInfo->opnd[OPND3].data32l < 128 ) ||
                ( CodeInfo->token != T_IMUL && CodeInfo->opnd[OPND3].data32l < 256 ) ) {
                CodeInfo->opnd[OPND3].type = OP_I8;
                return( NOT_ERROR );
            }
        }
        break;
    case OP3_I: /* IMUL */
        if ( CodeInfo->opnd[OPND3].type & OP_I )
            return( NOT_ERROR );
        break;
    case OP3_XMM0:
#if AVXSUPP
        /* for VEX encoding, XMM0 has the meaning: any K/XMM/YMM/ZMM register */
        if ( CodeInfo->token >= VEX_START ) {
               return( NOT_ERROR );
        } else
#endif
        if ( CodeInfo->opnd[OPND3].type == OP_XMM &&
            CodeInfo->opnd[OPND3].data32l == 0 )
            return( NOT_ERROR );
        break;
    }
    return( ERROR );
}

static void output_3rd_operand( struct code_info *CodeInfo )
/**********************************************************/
{
    if( opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type_3rd == OP3_I8_U ) {
        DebugMsg1(("output_3rd_operand, expected I8, op3=%" I32_SPEC "X\n", CodeInfo->opnd[OPND3].type ));
        /* v2.06: the type has been checked already! */
        //if( CodeInfo->opnd_type[OPND3] & OP_I ) {
        output_data( CodeInfo, OP_I8, OPND3 );
        //} else {
        //    EmitError( INVALID_INSTRUCTION_OPERANDS );
        //    return;
        //}
    } else if( opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type_3rd == OP3_I ) {
        output_data( CodeInfo, CodeInfo->opnd[OPND3].type, OPND3 );
    }
    else if (opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type_3rd == OP3_HID) {
      DebugMsg1(("output_3rd_operand, expected OP3_HID, op3=%" I32_SPEC "X\n", CodeInfo->opnd[OPND3].type));
      /* v2.06: to avoid having to add 3*8 operand categories there's a
       * hard-wired peculiarity for the "hidden" 3rd operand: it's calculated
       * directly from the instruction token. in instruct.h, CMPEQPD must
       * be first and the order of the following CMP entries must not be
       * changed.
       */
      //CodeInfo->data[OPND3] = opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type_3rd & ~OP3_HID;
      switch (CodeInfo->token){
        case T_PCLMULLQLQDQ:
             CodeInfo->opnd[OPND3].InsFixup = NULL;
             OutputCodeByte(0x00);
          return;
        case T_PCLMULHQLQDQ:
             CodeInfo->opnd[OPND3].InsFixup = NULL;
             OutputCodeByte(0x01);
          return;
        case T_PCLMULLQHQDQ:
             CodeInfo->opnd[OPND3].InsFixup = NULL;
             OutputCodeByte(0x10);
          return;
        case T_PCLMULHQHQDQ:
             CodeInfo->opnd[OPND3].InsFixup = NULL;
             OutputCodeByte(0x11);
          return;
        }
#if AVXSUPP
      if (CodeInfo->token >= VEX_START){
      switch (CodeInfo->token){
        case T_VPCLMULLQLQDQ:
             CodeInfo->opnd[OPND3].InsFixup = NULL;
             OutputCodeByte(0x00);
          return;
        case T_VPCLMULHQLQDQ:
             CodeInfo->opnd[OPND3].InsFixup = NULL;
             OutputCodeByte(0x01);
          return;
        case T_VPCLMULLQHQDQ:
             CodeInfo->opnd[OPND3].InsFixup = NULL;
             OutputCodeByte(0x10);
          return;
        case T_VPCLMULHQHQDQ:
             CodeInfo->opnd[OPND3].InsFixup = NULL;
             OutputCodeByte(0x11);
          return;
        }

        if (CodeInfo->token >= T_VCMPEQPD && CodeInfo->token <= T_VCMPTRUE_USSS){
          CodeInfo->opnd[OPND3].InsFixup = NULL;
          OutputCodeByte((CodeInfo->token - T_VCMPEQPD) & 0x1F);
          return;
        }
        else if (CodeInfo->token >= T_VPCMPEQD && CodeInfo->token <= T_VPCMPTRUED){
          CodeInfo->opnd[OPND3].InsFixup = NULL;
          OutputCodeByte((CodeInfo->token - T_VPCMPEQD) & 0x07);
          return;
        }
        else if (CodeInfo->token >= T_VPCMPEQUD && CodeInfo->token <= T_VPCMPTRUEUD){
          CodeInfo->opnd[OPND3].InsFixup = NULL;
          OutputCodeByte((CodeInfo->token - T_VPCMPEQUD) & 0x07);
          return;
        }
        else if (CodeInfo->token >= T_VPCMPEQQ && CodeInfo->token <= T_VPCMPTRUEQ){
          CodeInfo->opnd[OPND3].InsFixup = NULL;
          OutputCodeByte((CodeInfo->token - T_VPCMPEQQ) & 0x07);
          return;
        }
        else if (CodeInfo->token >= T_VPCMPEQUQ && CodeInfo->token <= T_VPCMPTRUEUQ){
          CodeInfo->opnd[OPND3].InsFixup = NULL;
          OutputCodeByte((CodeInfo->token - T_VPCMPEQUQ) & 0x07);
          return;
        }
        else if (CodeInfo->token >= T_VPCMPEQW && CodeInfo->token <= T_VPCMPTRUEW){
          CodeInfo->opnd[OPND3].InsFixup = NULL;
          OutputCodeByte((CodeInfo->token - T_VPCMPEQW) & 0x07);
          return;
        }
        else if (CodeInfo->token >= T_VPCMPEQUW && CodeInfo->token <= T_VPCMPTRUEUW){
          CodeInfo->opnd[OPND3].InsFixup = NULL;
          OutputCodeByte((CodeInfo->token - T_VPCMPEQUW) & 0x07);
          return;
        }
        else if (CodeInfo->token >= T_VPCMPEQB && CodeInfo->token <= T_VPCMPTRUEB){
          CodeInfo->opnd[OPND3].InsFixup = NULL;
          OutputCodeByte((CodeInfo->token - T_VPCMPEQB) & 0x07);
          return;
        }
        else if (CodeInfo->token >= T_VPCMPEQUB && CodeInfo->token <= T_VPCMPTRUEUB){
          CodeInfo->opnd[OPND3].InsFixup = NULL;
          OutputCodeByte((CodeInfo->token - T_VPCMPEQUB) & 0x07);
          return;
      }
    }
    else
#endif
          CodeInfo->opnd[OPND3].data32l = ( CodeInfo->token - T_CMPEQPD ) % 8;
          CodeInfo->opnd[OPND3].InsFixup = NULL;
          output_data( CodeInfo, OP_I8, OPND3 );
    }
#if AVXSUPP
    else if( ((CodeInfo->token >= VEX_START) && (CodeInfo->token < T_VPGATHERDD)|| 
      (CodeInfo->token > T_VGATHERQPS))&&
       opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type_3rd == OP3_XMM0 ) {
        CodeInfo->opnd[OPND3].data32l = ( CodeInfo->opnd[OPND3].data32l << 4 );
        if (CodeInfo->opnd[OPND3].type != OP_K)
        output_data( CodeInfo, OP_I8, OPND3 );
    }
#endif
    return;
}

static ret_code match_phase_3( struct code_info *CodeInfo, enum operand_type opnd1 )
/***********************************************************************************
 * - this routine will look up the assembler opcode table and try to match
 *   the second operand with what we get;
 * - if second operand match then it will output code; if not, pass back to
 *   codegen() and continue to scan InstrTable;
 * - possible return codes: NOT_ERROR (=done), ERROR (=nothing found)
 */
{
    enum operand_type    determinant = opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type[OPND1]; /* remember first op type */
    enum operand_type    opnd2 = CodeInfo->opnd[OPND2].type;
    enum operand_type    tbl_op2;

    DebugMsg1(("match_phase_3 enter, opnd1=%" I32_SPEC "X, searching op2=%" I32_SPEC "X\n", opnd1, opnd2 ));
    
#if AVXSUPP 
                               
    if ( CodeInfo->token >= VEX_START && ( vex_flags[ CodeInfo->token - VEX_START ] & VX_L ) ) {
        if ( CodeInfo->opnd[OPND1].type & (OP_K | OP_YMM | OP_ZMM | OP_M256) ) {
            if ( opnd2 & OP_ZMM || opnd2 & OP_YMM || opnd2 & OP_K)
                opnd2 |= OP_XMM;
            else if ( opnd2 & OP_M256 )
                opnd2 |= OP_M128;
            else if ( opnd2 & OP_M128 )
                opnd2 |= OP_M64;               //should be: ins->prefix & VX_HALF)
            else if ( ( opnd2 & OP_XMM ) && !( vex_flags[ CodeInfo->token - VEX_START ] & VX_HALF ) ) {
                EmitError( INSTRUCTION_OR_REGISTER_NOT_ACCEPTED_IN_CURRENT_CPU_MODE );
                return( ERROR );
            }
        }
#if 1
        /* may be necessary to cover the cases where the first operand is a memory operand
         * "without size" and the second operand is a ymm register
         */
        else if ( CodeInfo->opnd[OPND1].type == OP_M ) {
            if ( opnd2 & OP_YMM || opnd2 & OP_ZMM)
                opnd2 |= OP_XMM;
        }
#endif
    }
#endif
    do  {
        tbl_op2 = opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type[OPND2];
        DebugMsg1(("match_phase_3: instr table op2=%" I32_SPEC "X\n", tbl_op2 ));
        switch( tbl_op2 ) {
        case OP_I: /* arith, MOV, IMUL, TEST */
            if( opnd2 & tbl_op2 ) {
                DebugMsg1(("match_phase_3: matched OP_I\n"));
                /* This branch exits with either ERROR or NOT_ERROR.
                 * So it can modify the CodeInfo fields without harm.
                 */
                if( opnd1 & OP_R8 ) {
                    /* 8-bit register, so output 8-bit data */
                    /* v2.04: the check has already happened in check_size() or idata_xxx() */
                    //if( Parse_Pass == PASS_1 && !InRange( operand, 1 ) ) {
                    //    DebugMsg(("imm const too large (08): %X\n", operand));
                    //    EmitWarn( 1, IMMEDIATE_CONSTANT_TOO_LARGE );
                    //}
                    CodeInfo->prefix.opsiz = FALSE;
                    opnd2 = OP_I8;
                    if( CodeInfo->opnd[OPND2].InsFixup != NULL ) {
                    /* v1.96: make sure FIX_HIBYTE isn't overwritten! */
                        if ( CodeInfo->opnd[OPND2].InsFixup->type != FIX_HIBYTE )
                            CodeInfo->opnd[OPND2].InsFixup->type = FIX_OFF8;
                    }
                } else if( opnd1 & OP_R16 ) {
                    /* v2.04: the check has already happened in check_size() or idata_xxx() */
                    //if( Parse_Pass == PASS_1 && !InRange( operand, 2 ) ) {
                    //    DebugMsg(("imm const too large (16): %X\n", operand));
                    //    EmitWarn( 1, IMMEDIATE_CONSTANT_TOO_LARGE );
                    //}
                    /* 16-bit register, so output 16-bit data */
                    opnd2 = OP_I16;
#if AMD64_SUPPORT
                } else if( opnd1 & (OP_R32 | OP_R64 ) ) {
#else
                } else if( opnd1 & OP_R32 ) {
#endif
                    /* 32- or 64-bit register, so output 32-bit data */
                    CodeInfo->prefix.opsiz = CodeInfo->Ofssize ? 0 : 1;/* 12-feb-92 */
                    opnd2 = OP_I32;
                } else if( opnd1 & OP_M ) {
                    /* there is no reason this should be only for T_MOV */
                    switch( OperandSize( opnd1, CodeInfo ) ) {
                    case 1:
                        opnd2 = OP_I8;
                        CodeInfo->prefix.opsiz = FALSE;
                        break;
                    case 2:
                        opnd2 = OP_I16;
                        CodeInfo->prefix.opsiz = CodeInfo->Ofssize ? 1 : 0;
                        break;
#if AMD64_SUPPORT
                        /* mov [mem], imm64 doesn't exist. It's ensured that
                         * immediate data is 32bit only
                         */
                    case 8:
#endif
                    case 4:
                        opnd2 = OP_I32;
                        CodeInfo->prefix.opsiz = CodeInfo->Ofssize ? 0 : 1;
                        break;
                    default:
                        EmitError( INVALID_COMBINATION_OF_OPCODE_AND_OPERANDS );
                        //return( ERROR ); /* v2.06: don't exit */
                    }
                }
                output_opc( CodeInfo );
                output_data( CodeInfo, opnd1, OPND1 );
                output_data( CodeInfo, opnd2, OPND2 );
                return( NOT_ERROR );
            }
            break;
        case OP_I8_U: /* shift+rotate, ENTER, BTx, IN, PSxx[D|Q|W] */
            if( opnd2 & tbl_op2 ) {
                DebugMsg1(("match_phase_3: matched OP_I8_U\n"));
                if ( CodeInfo->const_size_fixed && opnd2 != OP_I8 )
                    break;
                /* v2.03: lower bound wasn't checked */
                /* range of unsigned 8-bit is -128 - +255 */
                if( CodeInfo->opnd[OPND2].data32l <= UCHAR_MAX && CodeInfo->opnd[OPND2].data32l >= SCHAR_MIN ) {
                    /* v2.06: if there's an external, adjust the fixup if it is > 8-bit */
                    if ( CodeInfo->opnd[OPND2].InsFixup != NULL ) {
                        if ( CodeInfo->opnd[OPND2].InsFixup->type == FIX_OFF16 ||
                            CodeInfo->opnd[OPND2].InsFixup->type == FIX_OFF32 )
                            CodeInfo->opnd[OPND2].InsFixup->type = FIX_OFF8;
                    }
                    /* the SSE4A EXTRQ instruction will need this! */
                    //if( check_3rd_operand( CodeInfo ) == ERROR )
                    //  break;
                    output_opc( CodeInfo );
                    output_data( CodeInfo, opnd1, OPND1 );
                    output_data( CodeInfo, OP_I8, OPND2 );
                    //if( CodeInfo->pinstr->opnd_type_3rd != OP3_NONE )
                    //output_3rd_operand( CodeInfo );
                    return( NOT_ERROR );
                }
            }
            break;
        case OP_I8: /* arith, IMUL */
            /* v2.06: this case has been rewritten */

            /* v2.04: added */
            if( ModuleInfo.NoSignExtend &&
               ( CodeInfo->token == T_AND ||
                CodeInfo->token == T_OR ||
                CodeInfo->token == T_XOR ) )
                break;

            /* v2.11: skip externals - but don't skip undefines; forward8.asm */
            //if ( CodeInfo->opnd[OPND2].InsFixup != NULL ) /* external? then skip */
            if ( CodeInfo->opnd[OPND2].InsFixup != NULL && CodeInfo->opnd[OPND2].InsFixup->sym && CodeInfo->opnd[OPND2].InsFixup->sym->state != SYM_UNDEFINED ) /* external? then skip */
                break;

            if ( CodeInfo->const_size_fixed == FALSE )
                if ( ( opnd1 & ( OP_R16 | OP_M16 ) ) && (int_8)CodeInfo->opnd[OPND2].data32l == (int_16)CodeInfo->opnd[OPND2].data32l )
                    tbl_op2 |= OP_I16;
                else if ( ( opnd1 & ( OP_RGT16 | OP_MGT16 ) ) && (int_8)CodeInfo->opnd[OPND2].data32l == (int_32)CodeInfo->opnd[OPND2].data32l )
                    tbl_op2 |= OP_I32;

            if( opnd2 & tbl_op2 ) {
                DebugMsg1(("match_phase_3: matched OP_I8\n"));
                output_opc( CodeInfo );
                output_data( CodeInfo, opnd1, OPND1 );
                output_data( CodeInfo, OP_I8, OPND2 );
                return( NOT_ERROR );
            }
            break;
        case OP_I_1: /* shift ops */
            if( opnd2 & tbl_op2 ) {
               if ( CodeInfo->opnd[OPND2].data32l == 1 ) {
                   DebugMsg1(("match_phase_3: matched OP_I_1\n"));
                   output_opc( CodeInfo );
                   output_data( CodeInfo, opnd1, OPND1 );
                   /* the immediate is "implicite" */
                   return( NOT_ERROR );
               }
            }
            break;
        default:
            /* v2.06: condition made more restrictive */
            if (CodeInfo->token < T_VBROADCASTSS)(CodeInfo->evex_flag = 0);
            //if( ( opnd2 & tbl_op2 ) || (CodeInfo->mem_type == MT_EMPTY && (opnd2 & OP_M_ANY) || (tbl_op2 & OP_M_ANY) )) {
              if ((opnd2 & tbl_op2) || (CodeInfo->mem_type == MT_EMPTY && opnd2 == OP_I8 && CodeInfo->opnd[OPND1].type == OP_XMM) ||
                  ((CodeInfo->evex_flag)&&(CodeInfo->token < T_VPBROADCASTB) || (CodeInfo->token > T_VPBROADCASTQ))) {     // 
                if( check_3rd_operand( CodeInfo ) == ERROR )
                    break;
                DebugMsg1(("match_phase_3: matched opnd2\n" ));
                output_opc( CodeInfo );
                if ( opnd1 & (OP_I_ANY | OP_M_ANY ) )
                    output_data( CodeInfo, opnd1, OPND1 );
                if ( opnd2 & (OP_I_ANY | OP_M_ANY ) )
                    output_data( CodeInfo, opnd2, OPND2 );
                //if( CodeInfo->pinstr->opnd_type_3rd != OP3_NONE )
                if( opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type_3rd != OP3_NONE )
                    output_3rd_operand( CodeInfo );
                if( CodeInfo->pinstr->byte1_info == F_0F0F ) /* output 3dNow opcode? */
                    OutputCodeByte( CodeInfo->pinstr->opcode | CodeInfo->iswide );
                return( NOT_ERROR );
            }
            break;
        }
        CodeInfo->pinstr++;
    } while ( opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type[OPND1] == determinant && CodeInfo->pinstr->first == FALSE );
    CodeInfo->pinstr--; /* pointer will be increased in codegen() */
    DebugMsg(("match_phase_3: returns EMPTY\n"));
    return( ERROR );
}

static ret_code check_operand_2( struct code_info *CodeInfo, enum operand_type opnd1 )
/*************************************************************************************
 * check if a second operand has been entered.
 * If yes, call match_phase_3();
 * else emit opcode and optional data.
 * possible return codes: ERROR (=nothing found), NOT_ERROR (=done)
 */
{
	/* UASM 2.37: force 64bit immediate indirect addressing conversion */
	if (( (CodeInfo->token == T_MOV && CodeInfo->opnd[OPND2].type == OP_R64) || CodeInfo->opnd[OPND2].type == OP_R32 || CodeInfo->opnd[OPND2].type == OP_R16 || CodeInfo->opnd[OPND2].type == OP_R8) && CodeInfo->isptr && CodeInfo->opnd[OPND2].data32h > 0)
	{
		CodeInfo->opnd[OPND2].type = OP_A;
	}


    if( CodeInfo->opnd[OPND2].type == OP_NONE ) {
      if (opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type[OPND2] != OP_NONE){
        if (CodeInfo->token == T_VGETEXPPD || CodeInfo->token == T_VGETEXPPS)
          ;
        else
        return(ERROR); /* doesn't match */
      }
        /* 1 opnd instruction found */

        /* v2.06: added check for unspecified size of mem op */
        if ( opnd1 == OP_M ) {
            const struct instr_item *next = CodeInfo->pinstr+1;
            if ( ( opnd_clstab[next->opclsidx].opnd_type[OPND1] & OP_M ) &&
                next->first == FALSE )
                /* skip error if mem op is a forward reference */
                /* v2.06b: added "undefined" check */
                if ( CodeInfo->undef_sym == FALSE &&
                    ( CodeInfo->opnd[OPND1].InsFixup == NULL ||
                     CodeInfo->opnd[OPND1].InsFixup->sym == NULL ||
                     CodeInfo->opnd[OPND1].InsFixup->sym->state != SYM_UNDEFINED ) ) {
                    DebugMsg(("check_operand_2: error: undef_sym=%u Fixup[0]=%X [%s]\n",
                              CodeInfo->undef_sym, CodeInfo->opnd[OPND1].InsFixup,
                              CodeInfo->opnd[OPND1].InsFixup ? CodeInfo->opnd[OPND1].InsFixup->sym ? CodeInfo->opnd[OPND1].InsFixup->sym->name : "NULL" : "NULL" ));
                    EmitErr( INSTRUCTION_OPERAND_MUST_HAVE_SIZE );
                }
        }

        output_opc( CodeInfo );
        output_data( CodeInfo, opnd1, OPND1 );

        if ( CodeInfo->Ofssize == USE64 && CodeInfo->opnd[OPND1].InsFixup && CodeInfo->opnd[OPND1].InsFixup->type == FIX_RELOFF32 )
            CodeInfo->opnd[OPND1].InsFixup->addbytes = GetCurrOffset() - CodeInfo->opnd[OPND1].InsFixup->locofs;

        return( NOT_ERROR );
    }

    /* check second operand */
    if ( match_phase_3( CodeInfo, opnd1 ) == NOT_ERROR ) {
#if AMD64_SUPPORT
        /* for rip-relative fixups, the instruction end is needed */
        if ( CodeInfo->Ofssize == USE64 ) {
            if ( CodeInfo->opnd[OPND1].InsFixup && CodeInfo->opnd[OPND1].InsFixup->type == FIX_RELOFF32 )
                CodeInfo->opnd[OPND1].InsFixup->addbytes = GetCurrOffset() - CodeInfo->opnd[OPND1].InsFixup->locofs;
            if ( CodeInfo->opnd[OPND2].InsFixup && CodeInfo->opnd[OPND2].InsFixup->type == FIX_RELOFF32 )
                CodeInfo->opnd[OPND2].InsFixup->addbytes = GetCurrOffset() - CodeInfo->opnd[OPND2].InsFixup->locofs;
        }
#endif
        return( NOT_ERROR );
    }
    return( ERROR );
}

ret_code codegen( struct code_info *CodeInfo, uint_32 oldofs )
/*************************************************************
 * - codegen() will look up the assembler opcode table and try to find
 *   a matching first operand;
 * - if one is found then it will call check_operand_2() to determine
 *   if further operands also match; else, it must be error.
 */
{
    ret_code           retcode = ERROR;
    enum operand_type  opnd1;
    enum operand_type  tbl_op1;
    /* privileged instructions ok? */
    if( ( CodeInfo->pinstr->cpu & P_PM ) > ( ModuleInfo.curr_cpu & P_PM ) ) {
        EmitError( INSTRUCTION_OR_REGISTER_NOT_ACCEPTED_IN_CURRENT_CPU_MODE );
        return( ERROR );
    }
    opnd1 = CodeInfo->opnd[OPND1].type;
    /* if first operand is immediate data, set compatible flags */
    if( opnd1 & OP_I ) {
        if( opnd1 == OP_I8 ) {
            opnd1 = OP_IGE8;
        } else if( opnd1 == OP_I16 ) {
            opnd1 = OP_IGE16;
        }
    }
#if AVXSUPP 
	if (CodeInfo->token >= VEX_START) {
		if (vex_flags[CodeInfo->token - VEX_START] & VX_L) {
			if (opnd1 & (OP_K | OP_ZMM | OP_YMM | OP_M256 | OP_M512)) {
				if (CodeInfo->opnd[OPND2].type & OP_XMM && !(vex_flags[CodeInfo->token - VEX_START] & VX_HALF)) {
					EmitErr(INVALID_INSTRUCTION_OPERANDS);
					return(ERROR);
				}
				if (opnd1 & OP_XMM || opnd1 & OP_YMM || opnd1 & OP_K || opnd1 & OP_ZMM)
					opnd1 |= OP_XMM;
        else{
					opnd1 |= OP_M128;
          opnd1 |= OP_M;
          }
			}
		}
		/* Here is probably possible to find better solution     */
     if ((CodeInfo->token >= T_VCMPPD && CodeInfo->token <= T_VCMPTRUE_USSS) ||          //1754        1885                  
        (CodeInfo->token >= T_VPCMPD) && (CodeInfo->token <= T_VINSERTI64x4) ||          //1446        1635         
        (CodeInfo->token >= T_VPMOVSXBD) && (CodeInfo->token <= T_VUNPCKLPS) ||          //2007        2077            
        (CodeInfo->token >= T_VPBROADCASTB && CodeInfo->token <= T_VBROADCASTF64x4) ||   //1294        1306
        (CodeInfo->token == T_VCVTPS2PH) || (CodeInfo->token == T_VCVTPH2PS) ||          //1428        1427
        (CodeInfo->token == T_VMOVDDUP) ||                                               //1339        
        (CodeInfo->token >= T_VDBPSADBW) && (CodeInfo->token <= T_VFPCLASSSS) ||         //1642        1646
        (CodeInfo->token >= T_VCVTPD2DQ) && (CodeInfo->token <= T_VMOVDDUP) ||           //1334        1339 
        (CodeInfo->token >= T_VPGATHERDD) && (CodeInfo->token <= T_VSCATTERQPD))
        opnd1 |= OP_XMM;
    }

#endif

#if AMD64_SUPPORT
    DebugMsg1(("codegen(ofs=%X): %s opnd1=%X codeinfo: ofssize=%u wide=%u rm=%Xh sib=%Xh rex=%Xh opsiz=%u\n",
               CurrSeg->sym.offset, GetResWName( CodeInfo->token, NULL ),
               opnd1, CodeInfo->Ofssize, CodeInfo->iswide,
               CodeInfo->rm_byte, CodeInfo->sib,
               CodeInfo->prefix.rex, CodeInfo->prefix.opsiz ));
#endif

    /* UASM 2.56 - Validate the proper usage of SARX,SHLX, SHRX */
    if (CodeInfo->token == T_SARX || CodeInfo->token == T_SHLX || CodeInfo->token == T_SHRX)
    {
        if((CodeInfo->opnd[0].type & OP_R) == 0)
            EmitError(INVALID_INSTRUCTION_OPERANDS);
        if (((CodeInfo->opnd[1].type & OP_R) == 0) && ((CodeInfo->opnd[1].type & OP_M) == 0))
            EmitError(INVALID_INSTRUCTION_OPERANDS);
        if ((CodeInfo->opnd[2].type & OP_I) == 0)
            EmitError(INVALID_INSTRUCTION_OPERANDS);
    }

    /* UASM 2.56 - Validate proper usage of VPBROADCASTn as legacy CODEGEN only handles AVX2 (not 512) */
    if (CodeInfo->token == T_VPBROADCASTB ||
        CodeInfo->token == T_VPBROADCASTW ||
        CodeInfo->token == T_VPBROADCASTD ||
        CodeInfo->token == T_VPBROADCASTQ) {
        if (CodeInfo->opnd[1].type & OP_R) {
            EmitError(INVALID_INSTRUCTION_OPERANDS);
        }
    }

    /* UASM 2.55 - Validate the proper usage of CRC32 and warn of no memory sizing */
    if (CodeInfo->token == T_CRC32)
    {
        if ( ((CodeInfo->opnd[0].type & OP_R64) != 0 && (CodeInfo->opnd[1].type & OP_R16) != 0) || 
             ((CodeInfo->opnd[0].type & OP_R64) != 0 && (CodeInfo->opnd[1].type & OP_R32) != 0))
        {
            EmitError(INVALID_INSTRUCTION_OPERANDS);
        }
        if (CodeInfo->opnd[1].type == OP_M) 
        {
            EmitWarn(2, SIZE_NOT_SPECIFIED_ASSUMING, "BYTE");
        }
    }

    /* UASM 2.50 error for movq xmmN,r32 */
    if (CodeInfo->token == T_MOVQ && CodeInfo->opnd[0].type == OP_XMM)
    {
        if (CodeInfo->opnd[1].type == OP_R32 || CodeInfo->opnd[1].type == OP_EAX)
        {
            EmitError(INVALID_INSTRUCTION_OPERANDS);
            return(ERROR);
        }
    }
	/* UASM 2.47 force non-sized jmp to match current word size */
	if (CodeInfo->token == T_JMP && CodeInfo->mem_type == MT_EMPTY)
	{
		if (CodeInfo->opnd[0].type == OP_IGE8)
		{
			if (CurrWordSize == 2)
				CodeInfo->mem_type = MT_WORD;
			else if (CurrWordSize == 4)
				CodeInfo->mem_type = MT_DWORD;
			else if (CurrWordSize == 8)
				CodeInfo->mem_type = MT_QWORD;
		}
	}

	/* UASM 2.37: force immediate indirect addressing conversion */
	if (( (CodeInfo->token == T_MOV && CodeInfo->opnd[OPND1].type == OP_R64) || CodeInfo->opnd[OPND1].type == OP_R32 || CodeInfo->opnd[OPND1].type == OP_R16 || CodeInfo->opnd[OPND1].type == OP_R8) && CodeInfo->isptr && CodeInfo->opnd[OPND1].data32h > 0)
	{
		CodeInfo->opnd[OPND1].type = OP_A;
		opnd1 = OP_A;
	}
  /*  if all 3 operans are not mask registers emit an error v2.46 */
  if ((CodeInfo->token >= T_KADDB) && (CodeInfo->token <= T_KUNPCKDQ)) {       
    if (CodeInfo->opnd[OPND1].type == OP_K && CodeInfo->opnd[OPND2].type == OP_K && CodeInfo->opnd[OPND3].type == OP_K)
      ;/* that is fine */
    else {
      EmitError(INVALID_INSTRUCTION_OPERANDS);
      return(ERROR);
      }
    }
    /* scan the instruction table for a matching first operand */
    do  {
        tbl_op1 = opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type[OPND1];

        //DebugMsg1(("codegen: table.op1=%X\n", tbl_op1 ));
        /* v2.06: simplified */
        if ( tbl_op1 == OP_NONE && opnd1 == OP_NONE ) {
            output_opc( CodeInfo );
            if ( CurrFile[LST] )
                LstWrite( LSTTYPE_CODE, oldofs, NULL );
            return( NOT_ERROR );
        } else if ( opnd1 & tbl_op1 ) {
            /* for immediate operands, the idata type has sometimes
             * to be modified in opnd_type[OPND1], to make output_data()
             * emit the correct number of bytes. */
            switch( tbl_op1 ) {
            case OP_I32: /* CALL, JMP, PUSHD */
            case OP_I16: /* CALL, JMP, RETx, ENTER, PUSHW */
                retcode = check_operand_2( CodeInfo, tbl_op1 );
                break;
            case OP_I8_U: /* INT xx; OUT xx, AL */
                if( CodeInfo->opnd[OPND1].data32l <= UCHAR_MAX && CodeInfo->opnd[OPND1].data32l >= SCHAR_MIN ) {
                    retcode = check_operand_2( CodeInfo, OP_I8 );
                }
                break;
            case OP_I_3: /* INT 3 */
                if ( CodeInfo->opnd[OPND1].data32l == 3 ) {
                    retcode = check_operand_2( CodeInfo, OP_NONE );
                }
                break;
            default:
                retcode = check_operand_2( CodeInfo, CodeInfo->opnd[OPND1].type );
                break;
            }
            if(retcode == NOT_ERROR) {
                if (CurrFile[LST])
                {
                    LstWrite(LSTTYPE_CODE, oldofs, NULL);
                }
                return( NOT_ERROR );
            }
        }
        CodeInfo->pinstr++;
    } while ( CodeInfo->pinstr->first == FALSE );

    DebugMsg(("codegen: no matching format found\n"));
    EmitError( INVALID_INSTRUCTION_OPERANDS );
    return( ERROR );
}

