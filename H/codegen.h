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
* Description:  definitions for code generator interface
*
****************************************************************************/

#ifndef _CODEGEN_H_INCLUDED
#define _CODEGEN_H_INCLUDED

#define BIT_012         0x07
#define BIT_345         0x38
#define BIT_67          0xC0
#define NOT_BIT_012     0xF8
#define NOT_BIT_345     0xC7 /* mask to filter Mod- and R/M-bits for ModRM-byte */
#define NOT_BIT_67      0x3F
#define NOT_BIT_6       0xBF

#define MOD_00          0x00
#define MOD_01          0x40
#define MOD_10          0x80
#define MOD_11          0xC0

/* opcode bits:
 * 0: w/ide bit, operand size BYTE <-> D/WORD
 * 1: s/ign bit, sign extended immediate
 * 1: d/irection bit
 */

#define W_BIT           0x01
#define NOT_W_BIT       0xFE

#define ADRSIZ          0x67
#define OPSIZ           0x66
#define OP_WAIT         0x9B
#define EXTENDED_OPCODE 0x0F
#define OP_NOP          0x90

#define RM_BX_SI        0x00
#define RM_BX_DI        0x01
#define RM_BP_SI        0x02
#define RM_BP_DI        0x03
#define RM_SI           0x04
#define RM_DI           0x05
#define RM_BP           0x06
#define RM_BX           0x07

#define RM_SIB          0x04
#define RM_D32          0x05  /* direct 32 */
#define RM_D16          0x06  /* direct 16 */

#define SCALE_FACTOR_1  0x00
#define SCALE_FACTOR_2  0x40
#define SCALE_FACTOR_4  0x80
#define SCALE_FACTOR_8  0xC0

#define FPE_MIN         0xD8
#define FPE_MAX         0xDF

#define IS_MEM_TYPE( op, typ ) ( (op) == MT_##typ || (op) == MT_S##typ )
#define IS_MEMTYPE_SIZ( op, siz ) ( ( ( (op) & MT_SPECIAL_MASK ) < MT_SPECIAL ) && ( ( (op) & MT_SIZE_MASK ) == ( siz - 1 ) ) )

/*
 * values for <byte1_info>
 * 000  : the first byte is opcode, follow by rm_byte
 * F_16 : the first byte is OPSIZ prefix if in use32 segment
 * F_32 : the first byte is OPSIZ prefix if in use16 segment
 * F_0F : the first byte is 0x0F, follow by opcode and rm_byte
 * the entries must be sorted related to F_0F prefix:
 * entries < F_0F emit NO 0F prefix, entries >= F_0F emit one.
 * v2.06: magnitude of this field extended to 8 (previously 4).
 * the entries with 38/3A must be last in the 0F group!
 */
enum byte1_info {
    F_16 = 1,      /* 16bit variant, 66h switches */
    F_32,          /* 32bit variant, 66h switches */
    F_16A,         /* 16bit variant, 67h switches */
    F_32A,         /* 32bit variant, 67h switches */
    F_F3,          /* F3 prefix (pause: F3 90)    */
#if AMD64_SUPPORT
    F_48,          /* REX.W prefix                */
#endif
    F_0F = 16,     /* 0F escape                   */
    F_0F0F,        /* AMD 3DNow "prefix"          */
    F_660F,        /* SSEx prefix 1               */
    F_F20F,        /* SSEx prefix 2               */
    F_F30F,        /* SSEx prefix 3               */
    F_0FNO66,      /* 0F escape, no size prefix   */
#if AMD64_SUPPORT
    F_480F,        /* REX.W + 0F prefix ( cmpxchg16b ) */
#endif
    F_0F38,        /* must be first of 38/3A variants */
    F_0F3A,
    F_660F38,
    F_660F3A,
    F_F20F38,
    F_F30F38,
    F_F20F3A,
};

#if AVXSUPP
/* VX_NND is only needed if instruction has more than 2 operands */
enum vex_info {
    VX_L     = 0x01,    /* VEX.L supported */
    VX_NND   = 0x02,    /* VEX.NDS/NDD not supported */
    VX_DST   = 0x04,    /* VEX.NDD (if op3 is an immediate) */
    VX_IMM   = 0x08,    /* no VEX.NDS if op3 is an immediate */
    VX_NMEM  = 0x10,    /* no VEX.NDS if op1 is a mem ref (vmovs[d|s], vmov[h|l]p[d|s] ) */
    VX_HALF  = 0x20,    /* op2 is half-sized */
    VX_LL    = 0x40,    /* EVEX.LL supported */
};

#endif
extern ret_code         codegen( struct code_info *, uint_32 );

#endif
