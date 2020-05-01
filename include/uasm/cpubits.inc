
; / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
; / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
; / /                                                                               / /
; / /    Copyright 2020 UASM macro library for the Open Source Initiative           / /
; / /                                                                               / /
; / /    Licensed under the Apache License, Version 2.0 (the "License");            / /
; / /    you may not use this file except in compliance with the License.           / /
; / /    You may obtain a copy of the License at                                    / /
; / /                                                                               / /
; / /        http://www.apache.org/licenses/LICENSE-2.0                             / /
; / /                                                                               / /
; / /    Unless required by applicable law or agreed to in writing, software        / /
; / /    distributed under the License is distributed on an "AS IS" BASIS,          / /
; / /    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   / /
; / /    See the License for the specific language governing permissions and        / /
; / /    limitations under the License.                                             / /
; / /                                                                               / /
; / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
; / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /

    IFNDEF CPUBITS_INC
    CPUBITS_INC EQU 1
    
    IFDEF WITHMACROLIB

    IFNDEF MACROLIB_INC
    .ERR <"CPUBITS_INC must be included by MACROLIB_INC">
    ENDIF
    
    IFNDEF X86ORX64
    .ERR <"CPUBITS_INC requires one x86 or x64 platform type">
    ENDIF

   ;/ EFLAGS %eax=00H, %ebx=00H */
    IFNDEF BIT_CPUID
    BIT_CPUID EQU 0x00200000      ;/1 << 21*/
    ENDIF

   ;/ %eax=00H, %ecx %ebx */
    IFNDEF BIT_NTEL
    BIT_NTEL EQU 0x6c65746e       ;/'GenuineIntel'*/
    ENDIF
    IFNDEF BIT_CAMD
    BIT_CAMD EQU 0x444d4163       ;/'AuthenticAMD'*/
    ENDIF

   ;/ %eax=00H, %ebx */
    IFNDEF BIT_CENT
    BIT_CENT EQU 0x746e6543       ;/'CentaurHauls'*/
    ENDIF
    IFNDEF BIT_VIA
    BIT_VIA EQU 0x20414956        ;/'VIA VIA VIA'*/
    ENDIF
    IFNDEF BIT_CYRI
    BIT_CYRI EQU 0x69727943       ;/'CyrixInstead'*/
    ENDIF
    IFNDEF BIT_NEXG
    BIT_NEXG EQU 0x4778654e       ;/'NexGenDriven'*/
    ENDIF

   ;/ %eax=01H, %ecx */
    IFNDEF BIT_SSE3
    BIT_SSE3 EQU 0x00000001       ;/1 << 0*/
    ENDIF
    IFNDEF BIT_PCLMULQDQ
    BIT_PCLMULQDQ EQU 0x00000002  ;/1 << 1*/
    ENDIF
    IFNDEF BIT_MONITOR
    BIT_MONITOR EQU 0x00000008    ;/1 << 3*/
    ENDIF
    IFNDEF BIT_SSSE3
    BIT_SSSE3 EQU 0x00000200      ;/1 << 9*/
    ENDIF
    IFNDEF BIT_FMA
    BIT_FMA EQU 0x00001000        ;/1 << 12*/
    ENDIF
    IFNDEF BIT_CMPXCHG16B
    BIT_CMPXCHG16B EQU 0x00002000 ;/1 << 13*/
    ENDIF
    IFNDEF BIT_SSE41
    BIT_SSE41 EQU 0x00080000      ;/1 << 19*/
    ENDIF
    IFNDEF BIT_SSE42
    BIT_SSE42 EQU 0x00100000      ;/1 << 20*/
    ENDIF
    IFNDEF BIT_MOVBE
    BIT_MOVBE EQU 0x00400000      ;/1 << 22*/
    ENDIF
    IFNDEF BIT_POPCNT
    BIT_POPCNT EQU 0x00800000     ;/1 << 23*/
    ENDIF
    IFNDEF BIT_AES
    BIT_AES EQU 0x02000000        ;/1 << 25*/
    ENDIF
    IFNDEF BIT_XSAVE
    BIT_XSAVE EQU 0x04000000      ;/1 << 26*/
    ENDIF
    IFNDEF BIT_OSXSAVE
    BIT_OSXSAVE EQU 0x08000000    ;/1 << 27*/
    ENDIF
    IFNDEF BIT_AVX
    BIT_AVX EQU 0x10000000        ;/1 << 28*/
    ENDIF
    IFNDEF BIT_F16C
    BIT_F16C EQU 0x20000000       ;/1 << 29*/
    ENDIF
    IFNDEF BIT_RDRAND
    BIT_RDRAND EQU 0x40000000     ;/1 << 30*/
    ENDIF
    
    IFNDEF BIT_AVX_FMA
    BIT_AVX_FMA EQU 0x18001000    ;/1 << 12 | 1 << 27 | 1 << 28*/
    ENDIF
    IFNDEF BIT_OSXSAVE_AVX
    BIT_OSXSAVE_AVX EQU 0x18000000  ;/*1 << 27 | 1 << 28*/
    ENDIF
    IFNDEF BIT_AVX_F16C
    BIT_AVX_F16C EQU 0x38000000   ;/1 << 27 | 1 << 28 | 1 << 29*/
    ENDIF
    IFNDEF
    
    IFNDEF BIT_SSE3_AES
    BIT_SSE3_AES EQU 0x02000001   ;/1 << 0 | 1 << 25*/
    ENDIF
    IFNDEF BIT_SSSE3_AES
    BIT_SSSE3_AES EQU 0x02000200  ;/1 << 9 | 1 << 25*/
    ENDIF
    IFNDEF BIT_SSE41_AES
    BIT_SSE41_AES EQU 0x02080000  ;/1 << 19 | 1 << 25*/
    ENDIF
    IFNDEF BIT_SSE42_AES
    BIT_SSE42_AES EQU 0x02100000  ;/1 << 20 | 1 << 25*/
    ENDIF

    IFNDEF BIT_SSE3_PCLMULQDQ
    BIT_SSE3_PCLMULQDQ EQU 0x00000003 ;/1 << 1 | 1 << 1*/
    ENDIF
    IFNDEF BIT_SSSE3_PCLMULQDQ
    BIT_SSSE3_PCLMULQDQ EQU 0x00000202  ;/*1 << 1 | 1 << 9*/
    ENDIF
    IFNDEF BIT_SSE41_PCLMULQDQ
    BIT_SSE41_PCLMULQDQ EQU 0x00080002  ;/*1 << 1 | 1 << 19*/
    ENDIF
    IFNDEF BIT_SSE42_PCLMULQDQ
    BIT_SSE42_PCLMULQDQ EQU 0x00100002  ;/*1 << 1 | 1 << 20*/
    ENDIF

   ;/ %eax=01H, %edx */
    IFNDEF BIT_FPU
    BIT_FPU EQU 0x00000001            ;/1 << 0*/
    ENDIF
    IFNDEF BIT_TSC
    BIT_TSC EQU 0x00000010            ;/1 << 4*/
    ENDIF
    IFNDEF BIT_MSR
    BIT_MSR EQU 0x00000020            ;/1 << 5*/
    ENDIF
    IFNDEF BIT_CMPXCHG8B
    BIT_CMPXCHG8B EQU 0x00000100      ;/1 << 8*/
    ENDIF
    IFNDEF BIT_SEP
    BIT_SEP EQU 0x00000800            ;/1 << 11*/
    ENDIF
    IFNDEF BIT_CMOV
    BIT_CMOV EQU 0x00008000           ;/1 << 15*/
    ENDIF
    IFNDEF BIT_CLFSH
    BIT_CLFSH EQU 0x00080000      ;/1 << 19*/
    ENDIF
    IFNDEF BIT_MMX
    BIT_MMX EQU 0x00800000        ;/1 << 23*/
    ENDIF
    IFNDEF BIT_FXSR
    BIT_FXSR EQU 0x01000000       ;/1 << 24*/
    ENDIF
    IFNDEF BIT_SSE
    BIT_SSE EQU 0x02000000        ;/1 << 25*/
    ENDIF
    IFNDEF BIT_SSE2
    BIT_SSE2 EQU 0x04000000       ;/1 << 26*/
    ENDIF

   ;/ %eax=07H, %ebx */
    IFNDEF BIT_FSGSBASE
    BIT_FSGSBASE EQU 0x00000001       ;/1 << 0*/
    ENDIF
    IFNDEF BIT_SGX
    BIT_SGX EQU 0x00000004            ;/1 << 2*/
    ENDIF
    IFNDEF BIT_BMI1
    BIT_BMI1 EQU 0x00000008           ;/1 << 3*/
    ENDIF
    IFNDEF BIT_HLE
    BIT_HLE EQU 0x00000010            ;/1 << 4*/
    ENDIF
    IFNDEF BIT_AVX2
    BIT_AVX2 EQU 0x00000020           ;/1 << 5*/
    ENDIF
    IFNDEF BIT_SMEP
    BIT_SMEP EQU 0x00000080           ;/1 << 7*/
    ENDIF
    IFNDEF BIT_BMI2
    BIT_BMI2 EQU 0x00000100           ;/1 << 8*/
    ENDIF
    IFNDEF BIT_ERMS
    BIT_ERMS EQU 0x00000200           ;/1 << 9*/
    ENDIF
    IFNDEF BIT_INVPCID
    BIT_INVPCID EQU 0x00000400        ;/1 << 10*/
    ENDIF
    IFNDEF BIT_RTM
    BIT_RTM EQU 0x00000800            ;/1 << 11*/
    ENDIF
    IFNDEF BIT_MPX
    BIT_MPX EQU 0x00004000        ;/1 << 14*/
    ENDIF
    IFNDEF BIT_AVX512F
    BIT_AVX512F EQU 0x00010000    ;/1 << 16*/
    ENDIF
    IFNDEF BIT_AVX512DQ
    BIT_AVX512DQ EQU 0x00020000   ;/1 << 17*/
    ENDIF
    IFNDEF BIT_RDSEED
    BIT_RDSEED EQU 0x00040000     ;/1 << 18*/
    ENDIF
    IFNDEF BIT_ADX
    BIT_ADX EQU 0x00080000        ;/1 << 19*/
    ENDIF
    IFNDEF BIT_SMAP
    BIT_SMAP EQU 0x00100000       ;/1 << 20*/
    ENDIF
    IFNDEF BIT_AVX512_IFMA
    BIT_AVX512_IFMA EQU 0x00200000  ;/*1 << 21*/
    ENDIF
    IFNDEF BIT_CLFLUSHOPT
    BIT_CLFLUSHOPT EQU 0x00800000 ;/1 << 23*/
    ENDIF
    IFNDEF BIT_CLWB
    BIT_CLWB EQU 0x01000000       ;/1 << 24*/
    ENDIF
    IFNDEF BIT_AVX512PF
    BIT_AVX512PF EQU 0x04000000   ;/1 << 26*/
    ENDIF
    IFNDEF BIT_AVX512ER
    BIT_AVX512ER EQU 0x08000000   ;/1 << 27*/
    ENDIF
    IFNDEF BIT_AVX512CD
    BIT_AVX512CD EQU 0x10000000   ;/1 << 28*/
    ENDIF
    IFNDEF BIT_SHA
    BIT_SHA EQU 0x20000000        ;/1 << 29*/
    ENDIF
    IFNDEF BIT_AVX512BW
    BIT_AVX512BW EQU 0x40000000   ;/1 << 30*/
    ENDIF
    IFNDEF BIT_AVX512VL
    BIT_AVX512VL EQU 0x80000000   ;/1 << 31*/
    ENDIF
    
    IFNDEF BIT_AVX512F_DQ
    BIT_AVX512F_DQ EQU 0x00030000     ;/1 << 16 | 1 << 17*/
    ENDIF
    IFNDEF BIT_AVX512F_DQ_VL
    BIT_AVX512F_DQ_VL EQU 0x80030000  ;/1 << 16 | 1 << 17 | 1 << 31*/
    ENDIF
    IFNDEF BIT_AVX512F_IFMA
    BIT_AVX512F_IFMA EQU 0x00210000   ;/1 << 16 | 1 << 21*/
    ENDIF
    IFNDEF BIT_AVX512F_IFMA_VL
    BIT_AVX512F_IFMA_VL EQU 0x80210000  ;/*1 << 16 | 1 << 21 | 1 << 31*/
    ENDIF
    IFNDEF BIT_AVX512F_PF
    BIT_AVX512F_PF EQU 0x04010000     ;/1 << 16 | 1 << 26*/
    ENDIF
    IFNDEF BIT_AVX512F_ER
    BIT_AVX512F_ER EQU 0x08010000     ;/1 << 16 | 1 << 27*/
    ENDIF
    IFNDEF BIT_AVX512F_CD
    BIT_AVX512F_CD EQU 0x10010000     ;/1 << 16 | 1 << 28*/
    ENDIF
    IFNDEF BIT_AVX512F_CD_VL
    BIT_AVX512F_CD_VL EQU 0x90010000  ;/1 << 16 | 1 << 28 | 1 << 31*/
    ENDIF
    IFNDEF BIT_AVX512F_BW
    BIT_AVX512F_BW EQU 0x40010000     ;/1 << 16 | 1 << 30*/
    ENDIF
    IFNDEF BIT_AVX512F_BW_VL
    BIT_AVX512F_BW_VL EQU 0xC0010000  ;/1 << 16 | 1 << 30 | 1 << 31*/
    ENDIF
    IFNDEF BIT_AVX512F_VL
    BIT_AVX512F_VL EQU 0x80010000     ;/1 << 16 | 1 << 31*/
    ENDIF

   ;/ %eax=07H, %ecx */
    IFNDEF BIT_PREFETCHWT1
    BIT_PREFETCHWT1 EQU 0x00000001    ;/1 << 0*/
    ENDIF
    IFNDEF BIT_AVX512_VBMI
    BIT_AVX512_VBMI EQU 0x00000002    ;/1 << 1*/
    ENDIF
    IFNDEF BIT_UMIP
    BIT_UMIP EQU 0x00000004           ;/1 << 2*/
    ENDIF
    IFNDEF BIT_PKU
    BIT_PKU EQU 0x00000008            ;/1 << 3*/
    ENDIF
    IFNDEF BIT_OSPKE
    BIT_OSPKE EQU 0x00000010          ;/1 << 4*/
    ENDIF
    IFNDEF BIT_AVX512_VBMI2
    BIT_AVX512_VBMI2 EQU 0x00000040   ;/1 << 6*/
    ENDIF
    IFNDEF BIT_GFNI
    BIT_GFNI EQU 0x00000100           ;/1 << 8*/
    ENDIF
    IFNDEF BIT_VAES
    BIT_VAES EQU 0x00000200           ;/1 << 9*/
    ENDIF
    IFNDEF BIT_VPCLMULQDQ
    BIT_VPCLMULQDQ EQU 0x00000400     ;/1 << 10*/
    ENDIF
    IFNDEF BIT_AVX512_VNNI
    BIT_AVX512_VNNI EQU 0x00000800    ;/1 << 11*/
    ENDIF
    IFNDEF BIT_AVX512_BITALG
    BIT_AVX512_BITALG EQU 0x00001000  ;/1 << 12*/
    ENDIF
    IFNDEF BIT_AVX512_VPOPCNTDQ
    BIT_AVX512_VPOPCNTDQ EQU 0x00004000  ;/*1 << 14*/
    ENDIF
    IFNDEF BIT_RDPID
    BIT_RDPID EQU 0x00400000          ;/1 << 22*/
    ENDIF

   ;/ %eax=07H, %edx */
    IFNDEF BIT_AVX512_4VNNIW
    BIT_AVX512_4VNNIW EQU 0x00000004  ;/1 << 2*/
    ENDIF
    IFNDEF BIT_AVX512_4FMAPS
    BIT_AVX512_4FMAPS EQU 0x00000008  ;/1 << 3*/
    ENDIF

   ;/ %eax=80000001H, %ecx */
    IFNDEF BIT_LAHF
    BIT_LAHF EQU 0x00000001           ;/1 << 0*/
    ENDIF
    IFNDEF BIT_LZCNT
    BIT_LZCNT EQU 0x00000020          ;/1 << 5*/
    ENDIF
    IFNDEF BIT_ABM
    BIT_ABM EQU 0x00000020            ;/1 << 5*/
    ENDIF
    IFNDEF BIT_SSE4A
    BIT_SSE4A EQU 0x00000040          ;/1 << 6*/
    ENDIF
    IFNDEF BIT_PREFETCHW
    BIT_PREFETCHW EQU 0x00000100      ;/1 << 8*/
    ENDIF
    IFNDEF BIT_XOP
    BIT_XOP EQU 0x00000800            ;/1 << 11*/
    ENDIF
    IFNDEF BIT_LWP
    BIT_LWP EQU 0x00008000            ;/1 << 15*/
    ENDIF
    IFNDEF BIT_FMA4
    BIT_FMA4 EQU 0x00010000           ;/1 << 16*/
    ENDIF
    IFNDEF BIT_TBM
    BIT_TBM EQU 0x00200000            ;/1 << 21*/
    ENDIF
    IFNDEF BIT_MWAITX
    BIT_MWAITX EQU 0x20000000         ;/1 << 29*/
    ENDIF

   ;/ %eax=80000001H, %edx */
    IFNDEF BIT_SYSCALL
    BIT_SYSCALL EQU 0x00000800        ;/1 << 11*/
    ENDIF
    IFNDEF BIT_MMXEXT
    BIT_MMXEXT EQU 0x00400000         ;/1 << 22*/
    ENDIF
    IFNDEF BIT_RDTSCP
    BIT_RDTSCP EQU 0x08000000         ;/1 << 27*/
    ENDIF
    IFNDEF BIT_3DNOWEXT
    BIT_3DNOWEXT EQU 0x40000000       ;/1 << 30*/
    ENDIF
    IFNDEF BIT_3DNOW
    BIT_3DNOW EQU 0x80000000          ;/1 << 31*/
    ENDIF
    
;/*
; * Compare predicates for scalar and packed compare intrinsic functions
; */
   ;/No AVX*/
    IFNDEF CMPP_EQ
    CMPP_EQ EQU 0x0
    ENDIF
    IFNDEF CMPP_LT
    CMPP_LT EQU 0x1
    ENDIF
    IFNDEF CMPP_LE
    CMPP_LE EQU 0x2
    ENDIF
    IFNDEF CMPP_UNORD
    CMPP_UNORD EQU 0x3
    ENDIF
    IFNDEF CMPP_NEQ
    CMPP_NEQ EQU 0x4
    ENDIF
    IFNDEF CMPP_NLT
    CMPP_NLT EQU 0x5
    ENDIF
    IFNDEF CMPP_NLE
    CMPP_NLE EQU 0x6
    ENDIF
    IFNDEF CMPP_ORD
    CMPP_ORD EQU 0x7
    ENDIF

   ;/With AVX*/
    IFNDEF CMP_EQ_OQ
    CMP_EQ_OQ EQU 0x00    ;/ Equal (ordered, nonsignaling)               */
    ENDIF
    IFNDEF CMP_LT_OS
    CMP_LT_OS EQU 0x01    ;/ Less-than (ordered, signaling)              */
    ENDIF
    IFNDEF CMP_LE_OS
    CMP_LE_OS EQU 0x02    ;/ Less-than-or-equal (ordered, signaling)     */
    ENDIF
    IFNDEF CMP_UNORD_Q
    CMP_UNORD_Q EQU 0x03  ;/ Unordered (nonsignaling)                    */
    ENDIF
    IFNDEF CMP_NEQ_UQ
    CMP_NEQ_UQ EQU 0x04   ;/ Not-equal (unordered, nonsignaling)         */
    ENDIF
    IFNDEF CMP_NLT_US
    CMP_NLT_US EQU 0x05   ;/ Not-less-than (unordered, signaling)        */
    ENDIF
    IFNDEF CMP_NLE_US
    CMP_NLE_US EQU 0x06   ;/ Not-less-than-or-equal (unordered, signaling) */
    ENDIF
    IFNDEF CMP_ORD_Q
    CMP_ORD_Q EQU 0x07    ;/ Ordered (nonsignaling)                      */
    ENDIF
    IFNDEF CMP_EQ_UQ
    CMP_EQ_UQ EQU 0x08    ;/ Equal (unordered, non-signaling)            */
    ENDIF
    IFNDEF CMP_NGE_US
    CMP_NGE_US EQU 0x09   ;/ Not-greater-than-or-equal (unordered, signaling) */
    ENDIF
    IFNDEF CMP_NGT_US
    CMP_NGT_US EQU 0x0A   ;/ Not-greater-than (unordered, signaling)     */
    ENDIF
    IFNDEF CMP_FALSE_OQ
    CMP_FALSE_OQ EQU 0x0B ;/ False (ordered, nonsignaling)               */
    ENDIF
    IFNDEF CMP_NEQ_OQ
    CMP_NEQ_OQ EQU 0x0C   ;/ Not-equal (ordered, non-signaling)          */
    ENDIF
    IFNDEF CMP_GE_OS
    CMP_GE_OS EQU 0x0D    ;/ Greater-than-or-equal (ordered, signaling)  */
    ENDIF
    IFNDEF CMP_GT_OS
    CMP_GT_OS EQU 0x0E    ;/ Greater-than (ordered, signaling)           */
    ENDIF
    IFNDEF CMP_TRUE_UQ
    CMP_TRUE_UQ EQU 0x0F  ;/ True (unordered, non-signaling)             */
    ENDIF
    IFNDEF CMP_EQ_OS
    CMP_EQ_OS EQU 0x10    ;/ Equal (ordered, signaling)                  */
    ENDIF
    IFNDEF CMP_LT_OQ
    CMP_LT_OQ EQU 0x11    ;/ Less-than (ordered, nonsignaling)           */
    ENDIF
    IFNDEF CMP_LE_OQ
    CMP_LE_OQ EQU 0x12    ;/ Less-than-or-equal (ordered, nonsignaling)  */
    ENDIF
    IFNDEF CMP_UNORD_S
    CMP_UNORD_S EQU 0x13  ;/ Unordered (signaling)                       */
    ENDIF
    IFNDEF CMP_NEQ_US
    CMP_NEQ_US EQU 0x14   ;/ Not-equal (unordered, signaling)            */
    ENDIF
    IFNDEF CMP_NLT_UQ
    CMP_NLT_UQ EQU 0x15   ;/ Not-less-than (unordered, nonsignaling)     */
    ENDIF
    IFNDEF CMP_NLE_UQ
    CMP_NLE_UQ EQU 0x16   ;/ Not-less-than-or-equal (unordered, nonsignaling) */
    ENDIF
    IFNDEF CMP_ORD_S
    CMP_ORD_S EQU 0x17    ;/ Ordered (signaling)                         */
    ENDIF
    IFNDEF CMP_EQ_US
    CMP_EQ_US EQU 0x18    ;/ Equal (unordered, signaling)                */
    ENDIF
    IFNDEF CMP_NGE_UQ
    CMP_NGE_UQ EQU 0x19   ;/ Not-greater-than-or-equal (unordered, nonsignaling) */
    ENDIF
    IFNDEF CMP_NGT_UQ
    CMP_NGT_UQ EQU 0x1A   ;/ Not-greater-than (unordered, nonsignaling)  */
    ENDIF
    IFNDEF CMP_FALSE_OS
    CMP_FALSE_OS EQU 0x1B ;/ False (ordered, signaling)                  */
    ENDIF
    IFNDEF CMP_NEQ_OS
    CMP_NEQ_OS EQU 0x1C   ;/ Not-equal (ordered, signaling)              */
    ENDIF
    IFNDEF CMP_GE_OQ
    CMP_GE_OQ EQU 0x1D    ;/ Greater-than-or-equal (ordered, nonsignaling) */
    ENDIF
    IFNDEF CMP_GT_OQ
    CMP_GT_OQ EQU 0x1E    ;/ Greater-than (ordered, nonsignaling)        */
    ENDIF
    IFNDEF CMP_TRUE_US
    CMP_TRUE_US EQU 0x1F  ;/ True (unordered, signaling)                 */
    ENDIF

    IFDEF CASEMAPNONE

   ;/* EFLAGS %eax=00H, %ebx=00H */
    IFDEF BIT_CPUID
    bit_cpuid EQU BIT_CPUID          ;/*1 << 21*/
    ENDIF

   ;/* %eax=00H, %ecx %ebx */
    IFDEF BIT_NTEL
    bit_ntel EQU BIT_NTEL            ;/*'GenuineIntel'*/
    ENDIF
    IFDEF BIT_CAMD
    bit_camd EQU BIT_CAMD            ;/*'AuthenticAMD'*/
    ENDIF

   ;/* %eax=00H, %ebx */
    IFDEF BIT_CENT
    bit_cent EQU BIT_CENT            ;/*'CentaurHauls'*/
    ENDIF
    IFDEF BIT_VIA
    bit_via EQU BIT_VIA              ;/*'VIA VIA VIA'*/
    ENDIF
    IFDEF BIT_CYRI
    bit_cyri EQU BIT_CYRI            ;/*'CyrixInstead'*/
    ENDIF
    IFDEF BIT_NEXG
    bit_nexg EQU BIT_NEXG            ;/*'NexGenDriven'*/
    ENDIF

   ;/* %eax=01H, %ecx */
    IFDEF BIT_SSE3
    bit_sse3 EQU BIT_SSE3            ;/*1 << 0*/
    ENDIF
    IFDEF BIT_PCLMULQDQ
    bit_pclmulqdq EQU BIT_PCLMULQDQ  ;/*1 << 1*/
    ENDIF
    IFDEF BIT_MONITOR
    bit_monitor EQU BIT_MONITOR      ;/*1 << 3*/
    ENDIF
    IFDEF BIT_SSSE3
    bit_ssse3 EQU BIT_SSSE3          ;/*1 << 9*/
    ENDIF
    IFDEF BIT_FMA
    bit_fma EQU BIT_FMA              ;/*1 << 12*/
    ENDIF
    IFDEF BIT_CMPXCHG16B
    bit_cmpxchg16b EQU BIT_CMPXCHG16B  ;/*1 << 13*/
    ENDIF
    IFDEF BIT_SSE41
    bit_sse41 EQU BIT_SSE41          ;/*1 << 19*/
    ENDIF
    IFDEF BIT_SSE42
    bit_sse42 EQU BIT_SSE42          ;/*1 << 20*/
    ENDIF
    IFDEF BIT_MOVBE
    bit_movbe EQU BIT_MOVBE          ;/*1 << 22*/
    ENDIF
    IFDEF BIT_POPCNT
    bit_popcnt EQU BIT_POPCNT        ;/*1 << 23*/
    ENDIF
    IFDEF BIT_AES
    bit_aes EQU BIT_AES              ;/*1 << 25*/
    ENDIF
    IFDEF BIT_XSAVE
    bit_xsave EQU BIT_XSAVE          ;/*1 << 26*/
    ENDIF
    IFDEF BIT_OSXSAVE
    bit_osxsave EQU BIT_OSXSAVE      ;/*1 << 27*/
    ENDIF
    IFDEF BIT_AVX
    bit_avx EQU BIT_AVX              ;/*1 << 28*/
    ENDIF
    IFDEF BIT_F16C
    bit_f16c EQU BIT_F16C            ;/*1 << 29*/
    ENDIF
    IFDEF BIT_RDRAND
    bit_rdrand EQU BIT_RDRAND        ;/*1 << 30*/
    ENDIF
    
    IFDEF BIT_AVX_FMA
    bit_avx_fma EQU BIT_AVX_FMA            ;/*1 << 12 | 1 << 27 | 1 << 28*/
    ENDIF
    IFDEF BIT_OSXSAVE_AVX
    bit_osxsave_avx EQU BIT_OSXSAVE_AVX    ;/*1 << 27 | 1 << 28*/
    ENDIF
    IFDEF BIT_AVX_F16C
    bit_avx_f16c EQU BIT_AVX_F16C          ;/*1 << 27 | 1 << 28 | 1 << 29*/
    ENDIF
    
    IFDEF BIT_SSE3_AES
    bit_sse3_aes EQU BIT_SSE3_AES          ;/*1 << 0 | 1 << 25*/
    ENDIF
    IFDEF BIT_SSSE3_AES
    bit_ssse3_aes EQU BIT_SSSE3_AES        ;/*1 << 9 | 1 << 25*/
    ENDIF
    IFDEF BIT_SSE41_AES
    bit_sse41_aes EQU BIT_SSE41_AES        ;/*1 << 19 | 1 << 25*/
    ENDIF
    IFDEF BIT_SSE42_AES
    bit_sse42_aes EQU BIT_SSE42_AES        ;/*1 << 20 | 1 << 25*/
    ENDIF
    
    IFDEF BIT_SSE3_PCLMULQDQ
    bit_sse3_pclmulqdq EQU BIT_SSE3_PCLMULQDQ         ;/*1 << 1 | 1 << 1*/
    ENDIF
    IFDEF BIT_SSSE3_PCLMULQDQ
    bit_ssse3_pclmulqdq EQU BIT_SSSE3_PCLMULQDQ       ;/*1 << 1 | 1 << 9*/
    ENDIF
    IFDEF BIT_SSE41_PCLMULQDQ
    bit_sse41_pclmulqdq EQU BIT_SSE41_PCLMULQDQ       ;/*1 << 1 | 1 << 19*/
    ENDIF
    IFDEF BIT_SSE42_PCLMULQDQ
    bit_sse42_pclmulqdq EQU BIT_SSE42_PCLMULQDQ       ;/*1 << 1 | 1 << 20*/
    ENDIF

   ;/* %eax=01H, %edx */
    IFDEF BIT_FPU
    bit_fpu EQU BIT_FPU              ;/*1 << 0*/
    ENDIF
    IFDEF BIT_TSC
    bit_tsc EQU BIT_TSC              ;/*1 << 4*/
    ENDIF
    IFDEF BIT_MSR
    bit_msr EQU BIT_MSR              ;/*1 << 5*/
    ENDIF
    IFDEF BIT_CMPXCHG8B
    bit_cmpxchg8b EQU BIT_CMPXCHG8B  ;/*1 << 8*/
    ENDIF
    IFDEF BIT_SEP
    bit_sep EQU BIT_SEP              ;/*1 << 11*/
    ENDIF
    IFDEF BIT_CMOV
    bit_cmov EQU BIT_CMOV            ;/*1 << 15*/
    ENDIF
    IFDEF BIT_CLFSH
    bit_clfsh EQU BIT_CLFSH          ;/*1 << 19*/
    ENDIF
    IFDEF BIT_MMX
    bit_mmx EQU BIT_MMX              ;/*1 << 23*/
    ENDIF
    IFDEF BIT_FXSR
    bit_fxsr EQU BIT_FXSR            ;/*1 << 24*/
    ENDIF
    IFDEF BIT_SSE
    bit_sse EQU BIT_SSE              ;/*1 << 25*/
    ENDIF
    IFDEF BIT_SSE2
    bit_sse2 EQU BIT_SSE2            ;/*1 << 26*/
    ENDIF

   ;/* %eax=07H, %ebx */
    IFDEF BIT_FSGSBASE
    bit_fsgsbase EQU BIT_FSGSBASE    ;/*1 << 0*/
    ENDIF
    IFDEF BIT_SGX
    bit_sgx EQU BIT_SGX              ;/*1 << 2*/
    ENDIF
    IFDEF BIT_BMI1
    bit_bmi1 EQU BIT_BMI1            ;/*1 << 3*/
    ENDIF
    IFDEF BIT_HLE
    bit_hle EQU BIT_HLE              ;/*1 << 4*/
    ENDIF
    IFDEF BIT_AVX2
    bit_avx2 EQU BIT_AVX2            ;/*1 << 5*/
    ENDIF
    IFDEF BIT_SMEP
    bit_smep EQU BIT_SMEP            ;/*1 << 7*/
    ENDIF
    IFDEF BIT_BMI2
    bit_bmi2 EQU BIT_BMI2            ;/*1 << 8*/
    ENDIF
    IFDEF BIT_ERMS
    bit_erms EQU BIT_ERMS            ;/*1 << 9*/
    ENDIF
    IFDEF BIT_INVPCID
    bit_invpcid EQU BIT_INVPCID      ;/*1 << 10*/
    ENDIF
    IFDEF BIT_RTM
    bit_rtm EQU BIT_RTM              ;/*1 << 11*/
    ENDIF
    IFDEF BIT_MPX
    bit_mpx EQU BIT_MPX              ;/*1 << 14*/
    ENDIF
    IFDEF BIT_AVX512F
    bit_avx512f EQU BIT_AVX512F      ;/*1 << 16*/
    ENDIF
    IFDEF BIT_AVX512DQ
    bit_avx512DQ EQU BIT_AVX512DQ    ;/*1 << 17*/
    ENDIF
    IFDEF BIT_RDSEED
    bit_rdseed EQU BIT_RDSEED        ;/*1 << 18*/
    ENDIF
    IFDEF BIT_ADX
    bit_adx EQU BIT_ADX              ;/*1 << 19*/
    ENDIF
    IFDEF BIT_SMAP
    bit_smap EQU BIT_SMAP            ;/*1 << 20*/
    ENDIF
    IFDEF BIT_AVX512_IFMA
    bit_avx512_Ifma EQU BIT_AVX512_IFMA  ;/*1 << 21*/
    ENDIF
    IFDEF BIT_CLFLUSHOPT
    bit_clflushopt EQU BIT_CLFLUSHOPT    ;/*1 << 23*/
    ENDIF
    IFDEF BIT_CLWB
    bit_clwb EQU BIT_CLWB            ;/*/*1 << 24*/
    ENDIF
    IFDEF BIT_AVX512PF
    bit_avx512pf EQU BIT_AVX512PF    ;/*1 << 26*/
    ENDIF
    IFDEF BIT_AVX512ER
    bit_avx512er EQU BIT_AVX512ER    ;/*1 << 27*/
    ENDIF
    IFDEF BIT_AVX512CD
    bit_avx512cd EQU BIT_AVX512CD    ;/*1 << 28*/
    ENDIF
    IFDEF BIT_SHA
    bit_sha EQU BIT_SHA              ;/*1 << 29*/
    ENDIF
    IFDEF BIT_AVX512BW
    bit_avx512bw EQU BIT_AVX512BW    ;/*1 << 30*/
    ENDIF
    IFDEF BIT_AVX512VL
    bit_avx512vl EQU BIT_AVX512VL    ;/*1 << 31*/
    ENDIF
    
    IFDEF BIT_AVX512F_DQ
    bit_avx512f_dq EQU BIT_AVX512F_DQ            ;/*1 << 16 | 1 << 17*/
    ENDIF
    IFDEF BIT_AVX512F_DQ_VL
    bit_avx512f_dq_vl EQU BIT_AVX512F_DQ_VL      ;/*1 << 16 | 1 << 17 | 1 << 31*/
    ENDIF
    IFDEF BIT_AVX512F_IFMA
    bit_avx512f_ifma EQU BIT_AVX512F_IFMA        ;/*1 << 16 | 1 << 21*/
    ENDIF
    IFDEF BIT_AVX512F_IFMA_VL
    bit_avx512f_ifma_vl EQU BIT_AVX512F_IFMA_VL  ;/*1 << 16 | 1 << 21 | 1 << 31*/
    ENDIF
    IFDEF BIT_AVX512F_PF
    bit_avx512f_pf EQU BIT_AVX512F_PF            ;/*1 << 16 | 1 << 26*/
    ENDIF
    IFDEF BIT_AVX512F_ER
    bit_avx512f_er EQU BIT_AVX512F_ER            ;/*1 << 16 | 1 << 27*/
    ENDIF
    IFDEF BIT_AVX512F_CD
    bit_avx512f_cd EQU BIT_AVX512F_CD            ;/*1 << 16 | 1 << 28*/
    ENDIF
    IFDEF BIT_AVX512F_CD_VL
    bit_avx512f_cd_vl EQU BIT_AVX512F_CD_VL      ;/*1 << 16 | 1 << 28 | 1 << 31*/
    ENDIF
    IFDEF BIT_AVX512F_BW
    bit_avx512f_bw EQU BIT_AVX512F_BW            ;/*1 << 16 | 1 << 30*/
    ENDIF
    IFDEF BIT_AVX512F_BW_VL
    bit_avx512f_bw_vl EQU BIT_AVX512F_BW_VL      ;/*1 << 16 | 1 << 30 | 1 << 31*/
    ENDIF
    IFDEF BIT_AVX512F_VL
    bit_avx512f_vl EQU BIT_AVX512F_VL            ;/*1 << 16 | 1 << 31*/
    ENDIF

   ;/* %eax=07H, %ecx */
    IFDEF BIT_PREFETCHWT1
    bit_prefetchwt1 EQU BIT_PREFETCHWT1       ;/*1 << 0*/
    ENDIF
    IFDEF BIT_AVX512_VBMI
    bit_avx512_vbmi EQU BIT_AVX512_VBMI       ;/*1 << 1*/
    ENDIF
    IFDEF BIT_UMIP
    bit_unip EQU BIT_UMIP                     ;/*1 << 2*/
    ENDIF
    IFDEF BIT_PKU
    bit_pku EQU BIT_PKU                       ;/*1 << 3*/
    ENDIF
    IFDEF BIT_OSPKE
    bit_ospke EQU BIT_OSPKE                   ;/*1 << 4*/
    ENDIF
    IFDEF BIT_AVX512_VBMI2
    bit_avx512_vbmi2 EQU BIT_AVX512_VBMI2     ;/*1 << 6*/
    ENDIF
    IFDEF BIT_GFNI
    bit_gfni EQU BIT_GFNI                     ;/*1 << 8*/
    ENDIF
    IFDEF BIT_VAES
    bit_vaes EQU BIT_VAES                     ;/*1 << 9*/
    ENDIF
    IFDEF BIT_VPCLMULQDQ
    bit_vpclmulqdq EQU BIT_VPCLMULQDQ         ;/*1 << 10*/
    ENDIF
    IFDEF BIT_AVX512_VNNI
    bit_avx512_vnni EQU BIT_AVX512_VNNI       ;/*1 << 11*/
    ENDIF
    IFDEF BIT_AVX512_BITALG
    bit_avx512_bitalg EQU BIT_AVX512_BITALG   ;/*1 << 12*/
    ENDIF
    IFDEF BIT_AVX512_VPOPCNTDQ
    bit_avx512_vpopcntdq EQU BIT_AVX512_VPOPCNTDQ  ;/*1 << 14*/
    ENDIF
    IFDEF BIT_RDPID
    bit_rdpid EQU BIT_RDPID                        ;/*1 << 22*/
    ENDIF

   ;/* %eax=07H, %edx */
    IFDEF BIT_AVX512_4VNNIW
    bit_avx512_4vnniw EQU BIT_AVX512_4VNNIW       ;/*1 << 2*/
    ENDIF
    IFDEF BIT_AVX512_4FMAPS
    bit_avx512_4fmaps EQU BIT_AVX512_4FMAPS       ;/*1 << 3*/
    ENDIF

   ;/* %eax=80000001H, %ecx */
    IFDEF BIT_LAHF
    bit_lahf EQU BIT_LAHF             ;/*/*1 << 0*/
    ENDIF
    IFDEF BIT_LZCNT
    bit_lzcnt EQU BIT_LZCNT           ;/*1 << 5*/
    ENDIF
    IFDEF BIT_ABM
    bit_abm EQU BIT_ABM               ;/*1 << 5*/
    ENDIF
    IFDEF BIT_SSE4A
    bit_sse4a EQU BIT_SSE4A           ;/*1 << 6*/
    ENDIF
    IFDEF BIT_PREFETCHW
    bit_prefetchw EQU BIT_PREFETCHW   ;/*1 << 8*/
    ENDIF
    IFDEF BIT_XOP
    bit_xop EQU BIT_XOP               ;/*1 << 11*/
    ENDIF
    IFDEF BIT_LWP
    bit_lwp EQU BIT_LWP               ;/*1 << 15*/
    ENDIF
    IFDEF BIT_FMA4
    bit_fma4 EQU BIT_FMA4             ;/*/*1 << 16*/
    ENDIF
    IFDEF BIT_TBM
    bit_tbm EQU BIT_TBM               ;/*1 << 21*/
    ENDIF
    IFDEF BIT_MWAITX
    bit_mwaitx EQU BIT_MWAITX         ;/*1 << 29*/
    ENDIF

   ;/* %eax=80000001H, %edx */
    IFDEF BIT_SYSCALL
    bit_syscall EQU BIT_SYSCALL       ;/*1 << 11*/
    ENDIF
    IFDEF BIT_MMXEXT
    bit_mmxext EQU BIT_MMXEXT         ;/*1 << 22*/
    ENDIF
    IFDEF BIT_RDTSCP
    bit_rdtscp EQU BIT_RDTSCP         ;/*1 << 27*/
    ENDIF
    IFDEF BIT_3DNOWEXT
    bit_3dnowext EQU BIT_3DNOWEXT     ;/*1 << 30*/
    ENDIF
    IFDEF BIT_3DNOW
    bit_3dnow EQU BIT_3DNOW           ;/*1 << 31*/
    ENDIF
    
   ;/*
   ; * Compare predicates for scalar and packed compare intrinsic functions
   ; */
   ;/*No AVX*/
    IFDEF CMPP_EQ
    cmpp_eq EQU CMPP_EQ
    ENDIF
    IFDEF CMPP_LT
    cmpp_lt EQU CMPP_LT
    ENDIF
    IFDEF CMPP_LE
    cmpp_le EQU CMPP_LE
    ENDIF
    IFDEF CMPP_UNORD
    cmpp_unord EQU CMPP_UNORD
    ENDIF
    IFDEF CMPP_NEQ
    cmpp_neq EQU CMPP_NEQ
    ENDIF
    IFDEF CMPP_NLT
    cmpp_nlt EQU CMPP_NLT
    ENDIF
    IFDEF CMPP_NLE
    cmpp_nle EQU CMPP_NLE
    ENDIF
    IFDEF CMPP_ORD
    cmpp_ord EQU CMPP_ORD
    ENDIF

   ;/*With AVX*/
    IFDEF CMP_EQ_OQ
    cmp_eq_oq EQU CMP_EQ_OQ            ;/* Equal (ordered, nonsignaling)               */
    ENDIF
    IFDEF CMP_LT_OS
    cmp_lt_os EQU CMP_LT_OS            ;/* Less-than (ordered, signaling)              */
    ENDIF
    IFDEF CMP_LE_OS
    cmp_le_os EQU CMP_LE_OS            ;/* Less-than-or-equal (ordered, signaling)     */
    ENDIF
    IFDEF CMP_UNORD_Q
    cmp_unord_q EQU CMP_UNORD_Q        ;/* Unordered (nonsignaling)                    */
    ENDIF
    IFDEF CMP_NEQ_UQ
    cmp_neq_uq EQU CMP_NEQ_UQ          ;/* Not-equal (unordered, nonsignaling)         */
    ENDIF
    IFDEF CMP_NLT_US
    cmp_nlt_us EQU CMP_NLT_US          ;/* Not-less-than (unordered, signaling)        */
    ENDIF
    IFDEF CMP_NLE_US
    cmp_nle_us EQU CMP_NLE_US          ;/* Not-less-than-or-equal (unordered, signaling) */
    ENDIF
    IFDEF CMP_ORD_Q
    cmp_ord_q EQU CMP_ORD_Q            ;/* Ordered (nonsignaling)                      */
    ENDIF
    IFDEF CMP_EQ_UQ
    cmp_eq_uq EQU CMP_EQ_UQ            ;/* Equal (unordered, non-signaling)            */
    ENDIF
    IFDEF CMP_NGE_US
    cmp_nge_us EQU CMP_NGE_US          ;/* Not-greater-than-or-equal (unordered, signaling) */
    ENDIF
    IFDEF CMP_NGT_US
    cmp_ngt_us EQU CMP_NGT_US          ;/* Not-greater-than (unordered, signaling)     */
    ENDIF
    IFDEF CMP_FALSE_OQ
    cmp_false_oq EQU CMP_FALSE_OQ      ;/* False (ordered, nonsignaling)               */
    ENDIF
    IFDEF CMP_NEQ_OQ
    cmp_neq_oq EQU CMP_NEQ_OQ          ;/* Not-equal (ordered, non-signaling)          */
    ENDIF
    IFDEF CMP_GE_OS
    cmp_ge_os EQU CMP_GE_OS            ;/* Greater-than-or-equal (ordered, signaling)  */
    ENDIF
    IFDEF CMP_GT_OS
    cmp_gt_os EQU CMP_GT_OS            ;/* Greater-than (ordered, signaling)           */
    ENDIF
    IFDEF CMP_TRUE_UQ
    cmp_true_uq EQU CMP_TRUE_UQ        ;/* True (unordered, non-signaling)             */
    ENDIF
    IFDEF CMP_EQ_OS
    cmp_eq_os EQU CMP_EQ_OS            ;/* Equal (ordered, signaling)                  */
    ENDIF
    IFDEF CMP_LT_OQ
    cmp_lt_oq EQU CMP_LT_OQ            ;/* Less-than (ordered, nonsignaling)           */
    ENDIF
    IFDEF CMP_LE_OQ
    cmp_le_oq EQU CMP_LE_OQ            ;/* Less-than-or-equal (ordered, nonsignaling)  */
    ENDIF
    IFDEF CMP_UNORD_S
    cmp_unord_s EQU CMP_UNORD_S        ;/* Unordered (signaling)                       */
    ENDIF
    IFDEF CMP_NEQ_US
    cmp_neq_us EQU CMP_NEQ_US          ;/* Not-equal (unordered, signaling)            */
    ENDIF
    IFDEF CMP_NLT_UQ
    cmp_nlt_uq EQU CMP_NLT_UQ          ;/* Not-less-than (unordered, nonsignaling)     */
    ENDIF
    IFDEF CMP_NLE_UQ
    cmp_nle_uq EQU CMP_NLE_UQ          ;/* Not-less-than-or-equal (unordered, nonsignaling) */
    ENDIF
    IFDEF CMP_ORD_S
    cmp_ord_s EQU CMP_ORD_S            ;/* Ordered (signaling)                         */
    ENDIF
    IFDEF CMP_EQ_US
    cmp_eq_us EQU CMP_EQ_US            ;/* Equal (unordered, signaling)                */
    ENDIF
    IFDEF CMP_NGE_UQ
    cmp_nge_uq EQU CMP_NGE_UQ          ;/* Not-greater-than-or-equal (unordered, nonsignaling) */
    ENDIF
    IFDEF CMP_NGT_UQ
    cmp_ngt_uq EQU CMP_NGT_UQ          ;/* Not-greater-than (unordered, nonsignaling)  */
    ENDIF
    IFDEF CMP_FALSE_OS
    cmp_false_os EQU CMP_FALSE_OS      ;/* False (ordered, signaling)                  */
    ENDIF
    IFDEF CMP_NEQ_OS
    cmp_neq_os EQU CMP_NEQ_OS          ;/* Not-equal (ordered, signaling)              */
    ENDIF
    IFDEF CMP_GE_OQ
    cmp_ge_oq EQU CMP_GE_OQ            ;/* Greater-than-or-equal (ordered, nonsignaling) */
    ENDIF
    IFDEF CMP_GT_OQ
    cmp_gt_oq EQU CMP_GT_OQ            ;/* Greater-than (ordered, nonsignaling)        */
    ENDIF
    IFDEF CMP_TRUE_US
    cmp_true_us EQU CMP_TRUE_US        ;/* True (unordered, signaling)                 */
    ENDIF
    
    ENDIF ;CASEMAPNONE

    ENDIF ;WITHMACROLIB

    ENDIF    ;CPUBITS_INC
