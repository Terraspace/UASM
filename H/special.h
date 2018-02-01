/****************************************************************************
*
* Description:  table of non-instruction reserved words:
*               - registers,
*               - predefined types
*               - operators (unary + binary),
*               - language types
*               for directives see directve.h!
*               for instructions see instruct.h!
*
****************************************************************************/

/* v1.96: items needn't be sorted anymore!
* The items are stored in structures of type special_item.
* If an item is inserted, moved or deleted, the project needs
* a full rebuild.
*/

/* field usage:
* type   = RWT_ value    SpecialTable.type   uint_8
* value  =      flags    SpecialTable.value  unsigned
* bytval =      value    SpecialTable.bytval uint_8
* flags  = RWF_ flags    ResWordTable.flags  uint_8
* cpu    = cpu  flags    SpecialTable.cpu    uint_16
* sflags =               SpecialTable.sflags unsigned
* for registers, the 'value' field contains OP_ flags.
* Since this field has type unsigned, it may be 16-bits wide only.
* This is no problem, since all register-related flags are in the low word.
*/
/* token str    type        value    bytval    flags  cpu     sflags */

/* registers AH-BH must be consecutive, start with AH and end with BH */

res(AL, al, RWT_REG, OP_AL, 0, 0, P_86, 1)
res(CL, cl, RWT_REG, OP_CL, 1, 0, P_86, 1)
res(DL, dl, RWT_REG, OP_R8, 2, 0, P_86, 1)
res(BL, bl, RWT_REG, OP_R8, 3, 0, P_86, 1)
res(AH, ah, RWT_REG, OP_R8, 4, 0, P_86, 1)
res(CH, ch, RWT_REG, OP_R8, 5, 0, P_86, 1)
res(DH, dh, RWT_REG, OP_R8, 6, 0, P_86, 1)
res(BH, bh, RWT_REG, OP_R8, 7, 0, P_86, 1)

res(AX, ax, RWT_REG, OP_AX,  0, 0, P_86, 2)
res(CX, cx, RWT_REG, OP_R16, 1, 0, P_86, 2)
res(DX, dx, RWT_REG, OP_DX,  2, 0, P_86, 2)
res(BX, bx, RWT_REG, OP_R16, 3, 0, P_86, SFR_IREG | 2)
res(SP, sp, RWT_REG, OP_R16, 4, 0, P_86, 2)
res(BP, bp, RWT_REG, OP_R16, 5, 0, P_86, SFR_SSBASED | SFR_IREG | 2)
res(SI, si, RWT_REG, OP_R16, 6, 0, P_86, SFR_IREG | 2)
res(DI, di, RWT_REG, OP_R16, 7, 0, P_86, SFR_IREG | 2)

res(EAX, eax, RWT_REG, OP_EAX, 0, 0, P_386, SFR_IREG | 4)
res(ECX, ecx, RWT_REG, OP_R32, 1, 0, P_386, SFR_IREG | 4)
res(EDX, edx, RWT_REG, OP_R32, 2, 0, P_386, SFR_IREG | 4)
res(EBX, ebx, RWT_REG, OP_R32, 3, 0, P_386, SFR_IREG | 4)
res(ESP, esp, RWT_REG, OP_R32, 4, 0, P_386, SFR_SSBASED | SFR_IREG | 4)
res(EBP, ebp, RWT_REG, OP_R32, 5, 0, P_386, SFR_SSBASED | SFR_IREG | 4)
res(ESI, esi, RWT_REG, OP_R32, 6, 0, P_386, SFR_IREG | 4)
res(EDI, edi, RWT_REG, OP_R32, 7, 0, P_386, SFR_IREG | 4)

/* registers ES-GS must be consecutive */
res(ES, es, RWT_REG, OP_SR86, 0, 0, P_86, 0)
res(CS, cs, RWT_REG, OP_SR86, 1, 0, P_86, 0)
res(SS, ss, RWT_REG, OP_SR86, 2, 0, P_86, 0)
res(DS, ds, RWT_REG, OP_SR86, 3, 0, P_86, 0)
res(FS, fs, RWT_REG, OP_SR386, 4, 0, P_386, 0)
res(GS, gs, RWT_REG, OP_SR386, 5, 0, P_386, 0)

res(ST, st, RWT_REG, OP_ST, 0, 0, P_87, 10)

res(MM0, mm0, RWT_REG, OP_MMX, 0, 0, P_MMX, 8)
res(MM1, mm1, RWT_REG, OP_MMX, 1, 0, P_MMX, 8)
res(MM2, mm2, RWT_REG, OP_MMX, 2, 0, P_MMX, 8)
res(MM3, mm3, RWT_REG, OP_MMX, 3, 0, P_MMX, 8)
res(MM4, mm4, RWT_REG, OP_MMX, 4, 0, P_MMX, 8)
res(MM5, mm5, RWT_REG, OP_MMX, 5, 0, P_MMX, 8)
res(MM6, mm6, RWT_REG, OP_MMX, 6, 0, P_MMX, 8)
res(MM7, mm7, RWT_REG, OP_MMX, 7, 0, P_MMX, 8)

res(XMM0, xmm0, RWT_REG, OP_XMM, 0, 0, P_SSE1, 16)
res(XMM1, xmm1, RWT_REG, OP_XMM, 1, 0, P_SSE1, 16)
res(XMM2, xmm2, RWT_REG, OP_XMM, 2, 0, P_SSE1, 16)
res(XMM3, xmm3, RWT_REG, OP_XMM, 3, 0, P_SSE1, 16)
res(XMM4, xmm4, RWT_REG, OP_XMM, 4, 0, P_SSE1, 16)
res(XMM5, xmm5, RWT_REG, OP_XMM, 5, 0, P_SSE1, 16)
res(XMM6, xmm6, RWT_REG, OP_XMM, 6, 0, P_SSE1, 16)
res(XMM7, xmm7, RWT_REG, OP_XMM, 7, 0, P_SSE1, 16)
#if AVXSUPP
/*token str type     value  bytval  flags     cpu  sflags */
res(K0, k0, RWT_REG, OP_K,    0,      0,    P_AVX, 8)
res(K1, k1, RWT_REG, OP_K,    1,      0,    P_AVX, 8)
res(K2, k2, RWT_REG, OP_K,    2,      0,    P_AVX, 8)
res(K3, k3, RWT_REG, OP_K,    3,      0,    P_AVX, 8)
res(K4, k4, RWT_REG, OP_K,    4,      0,    P_AVX, 8)
res(K5, k5, RWT_REG, OP_K,    5,      0,    P_AVX, 8)
res(K6, k6, RWT_REG, OP_K,    6,      0,    P_AVX, 8)
res(K7, k7, RWT_REG, OP_K,    7,      0,    P_AVX, 8)

res(BND0, bnd0, RWT_REG, OP_BND,    0,      0,    P_686, 8)
res(BND1, bnd1, RWT_REG, OP_BND,    1,      0,    P_686, 8)
res(BND2, bnd2, RWT_REG, OP_BND,    2,      0,    P_686, 8)
res(BND3, bnd3, RWT_REG, OP_BND,    3,      0,    P_686, 8)


res(YMM0, ymm0, RWT_REG, OP_YMM, 0, 0, P_AVX, 32)
res(YMM1, ymm1, RWT_REG, OP_YMM, 1, 0, P_AVX, 32)
res(YMM2, ymm2, RWT_REG, OP_YMM, 2, 0, P_AVX, 32)
res(YMM3, ymm3, RWT_REG, OP_YMM, 3, 0, P_AVX, 32)
res(YMM4, ymm4, RWT_REG, OP_YMM, 4, 0, P_AVX, 32)
res(YMM5, ymm5, RWT_REG, OP_YMM, 5, 0, P_AVX, 32)
res(YMM6, ymm6, RWT_REG, OP_YMM, 6, 0, P_AVX, 32)
res(YMM7, ymm7, RWT_REG, OP_YMM, 7, 0, P_AVX, 32)

res(ZMM0, zmm0, RWT_REG, OP_ZMM, 0, 0, P_AVX, 64)
res(ZMM1, zmm1, RWT_REG, OP_ZMM, 1, 0, P_AVX, 64)
res(ZMM2, zmm2, RWT_REG, OP_ZMM, 2, 0, P_AVX, 64)
res(ZMM3, zmm3, RWT_REG, OP_ZMM, 3, 0, P_AVX, 64)
res(ZMM4, zmm4, RWT_REG, OP_ZMM, 4, 0, P_AVX, 64)
res(ZMM5, zmm5, RWT_REG, OP_ZMM, 5, 0, P_AVX, 64)
res(ZMM6, zmm6, RWT_REG, OP_ZMM, 6, 0, P_AVX, 64)
res(ZMM7, zmm7, RWT_REG, OP_ZMM, 7, 0, P_AVX, 64)
#endif

res(CR0, cr0, RWT_REG, OP_RIP, 0, 0, P_386, 0)
res(CR2, cr2, RWT_REG, OP_RIP, 2, 0, P_386, 0)
res(CR3, cr3, RWT_REG, OP_RSPEC, 3, 0, P_386, 0)
res(CR4, cr4, RWT_REG, OP_RSPEC, 4, 0, P_586, 0)

res(DR0, dr0, RWT_REG, OP_RSPEC, 0 | 0x10, 0, P_386, 0)
res(DR1, dr1, RWT_REG, OP_RSPEC, 1 | 0x10, 0, P_386, 0)
res(DR2, dr2, RWT_REG, OP_RSPEC, 2 | 0x10, 0, P_386, 0)
res(DR3, dr3, RWT_REG, OP_RSPEC, 3 | 0x10, 0, P_386, 0)
res(DR6, dr6, RWT_REG, OP_RSPEC, 6 | 0x10, 0, P_386, 0)
res(DR7, dr7, RWT_REG, OP_RSPEC, 7 | 0x10, 0, P_386, 0)
/* v2.11: add RWF_IA32 to TRx registers */
res(TR3, tr3, RWT_REG, OP_RSPEC, 3 | 0x20, RWF_IA32, P_486, 0)
res(TR4, tr4, RWT_REG, OP_RSPEC, 4 | 0x20, RWF_IA32, P_486, 0)
res(TR5, tr5, RWT_REG, OP_RSPEC, 5 | 0x20, RWF_IA32, P_486, 0)
res(TR6, tr6, RWT_REG, OP_RSPEC, 6 | 0x20, RWF_IA32, P_386, 0)
res(TR7, tr7, RWT_REG, OP_RSPEC, 7 | 0x20, RWF_IA32, P_386, 0)
#if AMD64_SUPPORT

/* for simplicity, all x64 reserved words must be consecutive
* ( see Set64Bit() in parser.c ).
*/

res(SPL,  spl,  RWT_REG, OP_R8, 4,  RWF_X64, P_64, 1)
res(BPL,  bpl,  RWT_REG, OP_R8, 5,  RWF_X64, P_64, 1)
res(SIL,  sil,  RWT_REG, OP_R8, 6,  RWF_X64, P_64, 1)
res(DIL,  dil,  RWT_REG, OP_R8, 7,  RWF_X64, P_64, 1)
res(R8B,  r8b,  RWT_REG, OP_R8, 8,  RWF_X64, P_64, 1)
res(R9B,  r9b,  RWT_REG, OP_R8, 9,  RWF_X64, P_64, 1)
res(R10B, r10b, RWT_REG, OP_R8, 10, RWF_X64, P_64, 1)
res(R11B, r11b, RWT_REG, OP_R8, 11, RWF_X64, P_64, 1)
res(R12B, r12b, RWT_REG, OP_R8, 12, RWF_X64, P_64, 1)
res(R13B, r13b, RWT_REG, OP_R8, 13, RWF_X64, P_64, 1)
res(R14B, r14b, RWT_REG, OP_R8, 14, RWF_X64, P_64, 1)
res(R15B, r15b, RWT_REG, OP_R8, 15, RWF_X64, P_64, 1)

res(R8W,  r8w,  RWT_REG, OP_R16, 8,  RWF_X64, P_64, 2)
res(R9W,  r9w,  RWT_REG, OP_R16, 9,  RWF_X64, P_64, 2)
res(R10W, r10w, RWT_REG, OP_R16, 10, RWF_X64, P_64, 2)
res(R11W, r11w, RWT_REG, OP_R16, 11, RWF_X64, P_64, 2)
res(R12W, r12w, RWT_REG, OP_R16, 12, RWF_X64, P_64, 2)
res(R13W, r13w, RWT_REG, OP_R16, 13, RWF_X64, P_64, 2)
res(R14W, r14w, RWT_REG, OP_R16, 14, RWF_X64, P_64, 2)
res(R15W, r15w, RWT_REG, OP_R16, 15, RWF_X64, P_64, 2)

res(R8D,  r8d,  RWT_REG, OP_R32, 8,  RWF_X64, P_64, SFR_IREG | 4)
res(R9D,  r9d,  RWT_REG, OP_R32, 9,  RWF_X64, P_64, SFR_IREG | 4)
res(R10D, r10d, RWT_REG, OP_R32, 10, RWF_X64, P_64, SFR_IREG | 4)
res(R11D, r11d, RWT_REG, OP_R32, 11, RWF_X64, P_64, SFR_IREG | 4)
res(R12D, r12d, RWT_REG, OP_R32, 12, RWF_X64, P_64, SFR_IREG | 4)
res(R13D, r13d, RWT_REG, OP_R32, 13, RWF_X64, P_64, SFR_IREG | 4)
res(R14D, r14d, RWT_REG, OP_R32, 14, RWF_X64, P_64, SFR_IREG | 4)
res(R15D, r15d, RWT_REG, OP_R32, 15, RWF_X64, P_64, SFR_IREG | 4)

res(RAX, rax, RWT_REG, OP_RAX, 0,  RWF_X64, P_64, SFR_IREG | 8)
res(RCX, rcx, RWT_REG, OP_R64, 1,  RWF_X64, P_64, SFR_IREG | 8)
res(RDX, rdx, RWT_REG, OP_R64, 2,  RWF_X64, P_64, SFR_IREG | 8)
res(RBX, rbx, RWT_REG, OP_R64, 3,  RWF_X64, P_64, SFR_IREG | 8)
res(RSP, rsp, RWT_REG, OP_R64, 4,  RWF_X64, P_64, SFR_SSBASED | SFR_IREG | 8)
res(RBP, rbp, RWT_REG, OP_R64, 5,  RWF_X64, P_64, SFR_SSBASED | SFR_IREG | 8)
res(RSI, rsi, RWT_REG, OP_R64, 6,  RWF_X64, P_64, SFR_IREG | 8)
res(RDI, rdi, RWT_REG, OP_R64, 7,  RWF_X64, P_64, SFR_IREG | 8)
res(R8,  r8,  RWT_REG, OP_R64, 8,  RWF_X64, P_64, SFR_IREG | 8)
res(R9,  r9,  RWT_REG, OP_R64, 9,  RWF_X64, P_64, SFR_IREG | 8)
res(R10, r10, RWT_REG, OP_R64, 10, RWF_X64, P_64, SFR_IREG | 8)
res(R11, r11, RWT_REG, OP_R64, 11, RWF_X64, P_64, SFR_IREG | 8)
res(R12, r12, RWT_REG, OP_R64, 12, RWF_X64, P_64, SFR_IREG | 8)
res(R13, r13, RWT_REG, OP_R64, 13, RWF_X64, P_64, SFR_IREG | 8)
res(R14, r14, RWT_REG, OP_R64, 14, RWF_X64, P_64, SFR_IREG | 8)
res(R15, r15, RWT_REG, OP_R64, 15, RWF_X64, P_64, SFR_IREG | 8)
res(RIP, rip, RWT_REG, OP_RIP, 16, RWF_X64, P_64, SFR_IREG | 8)  //added by habran

res(XMM8,  xmm8,  RWT_REG, OP_XMM, 8,  RWF_X64, P_64, 16)
res(XMM9,  xmm9,  RWT_REG, OP_XMM, 9,  RWF_X64, P_64, 16)
res(XMM10, xmm10, RWT_REG, OP_XMM, 10, RWF_X64, P_64, 16)
res(XMM11, xmm11, RWT_REG, OP_XMM, 11, RWF_X64, P_64, 16)
res(XMM12, xmm12, RWT_REG, OP_XMM, 12, RWF_X64, P_64, 16)
res(XMM13, xmm13, RWT_REG, OP_XMM, 13, RWF_X64, P_64, 16)
res(XMM14, xmm14, RWT_REG, OP_XMM, 14, RWF_X64, P_64, 16)
res(XMM15, xmm15, RWT_REG, OP_XMM, 15, RWF_X64, P_64, 16)
res(XMM16, xmm16, RWT_REG, OP_XMM, 16, RWF_X64, P_64, 16)
res(XMM17, xmm17, RWT_REG, OP_XMM, 17, RWF_X64, P_64, 16)
res(XMM18, xmm18, RWT_REG, OP_XMM, 18, RWF_X64, P_64, 16)
res(XMM19, xmm19, RWT_REG, OP_XMM, 19, RWF_X64, P_64, 16)
res(XMM20, xmm20, RWT_REG, OP_XMM, 20, RWF_X64, P_64, 16)
res(XMM21, xmm21, RWT_REG, OP_XMM, 21, RWF_X64, P_64, 16)
res(XMM22, xmm22, RWT_REG, OP_XMM, 22, RWF_X64, P_64, 16)
res(XMM23, xmm23, RWT_REG, OP_XMM, 23, RWF_X64, P_64, 16)
res(XMM24, xmm24, RWT_REG, OP_XMM, 24, RWF_X64, P_64, 16)
res(XMM25, xmm25, RWT_REG, OP_XMM, 25, RWF_X64, P_64, 16)
res(XMM26, xmm26, RWT_REG, OP_XMM, 26, RWF_X64, P_64, 16)
res(XMM27, xmm27, RWT_REG, OP_XMM, 27, RWF_X64, P_64, 16)
res(XMM28, xmm28, RWT_REG, OP_XMM, 28, RWF_X64, P_64, 16)
res(XMM29, xmm29, RWT_REG, OP_XMM, 29, RWF_X64, P_64, 16)
res(XMM30, xmm30, RWT_REG, OP_XMM, 30, RWF_X64, P_64, 16)
res(XMM31, xmm31, RWT_REG, OP_XMM, 31, RWF_X64, P_64, 16)


#if AVXSUPP
res(YMM8,  ymm8,  RWT_REG, OP_YMM, 8,  RWF_X64, P_AVX | P_64, 32)
res(YMM9,  ymm9,  RWT_REG, OP_YMM, 9,  RWF_X64, P_AVX | P_64, 32)
res(YMM10, ymm10, RWT_REG, OP_YMM, 10, RWF_X64, P_AVX | P_64, 32)
res(YMM11, ymm11, RWT_REG, OP_YMM, 11, RWF_X64, P_AVX | P_64, 32)
res(YMM12, ymm12, RWT_REG, OP_YMM, 12, RWF_X64, P_AVX | P_64, 32)
res(YMM13, ymm13, RWT_REG, OP_YMM, 13, RWF_X64, P_AVX | P_64, 32)
res(YMM14, ymm14, RWT_REG, OP_YMM, 14, RWF_X64, P_AVX | P_64, 32)
res(YMM15, ymm15, RWT_REG, OP_YMM, 15, RWF_X64, P_AVX | P_64, 32)
res(YMM16, ymm16, RWT_REG, OP_YMM, 16, RWF_X64, P_AVX | P_64, 32)
res(YMM17, ymm17, RWT_REG, OP_YMM, 17, RWF_X64, P_AVX | P_64, 32)
res(YMM18, ymm18, RWT_REG, OP_YMM, 18, RWF_X64, P_AVX | P_64, 32)
res(YMM19, ymm19, RWT_REG, OP_YMM, 19, RWF_X64, P_AVX | P_64, 32)
res(YMM20, ymm20, RWT_REG, OP_YMM, 20, RWF_X64, P_AVX | P_64, 32)
res(YMM21, ymm21, RWT_REG, OP_YMM, 21, RWF_X64, P_AVX | P_64, 32)
res(YMM22, ymm22, RWT_REG, OP_YMM, 22, RWF_X64, P_AVX | P_64, 32)
res(YMM23, ymm23, RWT_REG, OP_YMM, 23, RWF_X64, P_AVX | P_64, 32)
res(YMM24, ymm24, RWT_REG, OP_YMM, 24, RWF_X64, P_AVX | P_64, 32)
res(YMM25, ymm25, RWT_REG, OP_YMM, 25, RWF_X64, P_AVX | P_64, 32)
res(YMM26, ymm26, RWT_REG, OP_YMM, 26, RWF_X64, P_AVX | P_64, 32)
res(YMM27, ymm27, RWT_REG, OP_YMM, 27, RWF_X64, P_AVX | P_64, 32)
res(YMM28, ymm28, RWT_REG, OP_YMM, 28, RWF_X64, P_AVX | P_64, 32)
res(YMM29, ymm29, RWT_REG, OP_YMM, 29, RWF_X64, P_AVX | P_64, 32)
res(YMM30, ymm30, RWT_REG, OP_YMM, 30, RWF_X64, P_AVX | P_64, 32)
res(YMM31, ymm31, RWT_REG, OP_YMM, 31, RWF_X64, P_AVX | P_64, 32)

res(ZMM8,  zmm8,  RWT_REG, OP_ZMM, 8,  RWF_X64, P_AVX | P_64, 64)
res(ZMM9,  zmm9,  RWT_REG, OP_ZMM, 9,  RWF_X64, P_AVX | P_64, 64)
res(ZMM10, zmm10, RWT_REG, OP_ZMM, 10, RWF_X64, P_AVX | P_64, 64)
res(ZMM11, zmm11, RWT_REG, OP_ZMM, 11, RWF_X64, P_AVX | P_64, 64)
res(ZMM12, zmm12, RWT_REG, OP_ZMM, 12, RWF_X64, P_AVX | P_64, 64)
res(ZMM13, zmm13, RWT_REG, OP_ZMM, 13, RWF_X64, P_AVX | P_64, 64)
res(ZMM14, zmm14, RWT_REG, OP_ZMM, 14, RWF_X64, P_AVX | P_64, 64)
res(ZMM15, zmm15, RWT_REG, OP_ZMM, 15, RWF_X64, P_AVX | P_64, 64)
res(ZMM16, zmm16, RWT_REG, OP_ZMM, 16, RWF_X64, P_AVX | P_64, 64)
res(ZMM17, zmm17, RWT_REG, OP_ZMM, 17, RWF_X64, P_AVX | P_64, 64)
res(ZMM18, zmm18, RWT_REG, OP_ZMM, 18, RWF_X64, P_AVX | P_64, 64)
res(ZMM19, zmm19, RWT_REG, OP_ZMM, 19, RWF_X64, P_AVX | P_64, 64)
res(ZMM20, zmm20, RWT_REG, OP_ZMM, 20, RWF_X64, P_AVX | P_64, 64)
res(ZMM21, zmm21, RWT_REG, OP_ZMM, 21, RWF_X64, P_AVX | P_64, 64)
res(ZMM22, zmm22, RWT_REG, OP_ZMM, 22, RWF_X64, P_AVX | P_64, 64)
res(ZMM23, zmm23, RWT_REG, OP_ZMM, 23, RWF_X64, P_AVX | P_64, 64)
res(ZMM24, zmm24, RWT_REG, OP_ZMM, 24, RWF_X64, P_AVX | P_64, 64)
res(ZMM25, zmm25, RWT_REG, OP_ZMM, 25, RWF_X64, P_AVX | P_64, 64)
res(ZMM26, zmm26, RWT_REG, OP_ZMM, 26, RWF_X64, P_AVX | P_64, 64)
res(ZMM27, zmm27, RWT_REG, OP_ZMM, 27, RWF_X64, P_AVX | P_64, 64)
res(ZMM28, zmm28, RWT_REG, OP_ZMM, 28, RWF_X64, P_AVX | P_64, 64)
res(ZMM29, zmm29, RWT_REG, OP_ZMM, 29, RWF_X64, P_AVX | P_64, 64)
res(ZMM30, zmm30, RWT_REG, OP_ZMM, 30, RWF_X64, P_AVX | P_64, 64)
res(ZMM31, zmm31, RWT_REG, OP_ZMM, 31, RWF_X64, P_AVX | P_64, 64)


#endif

res(CR8, cr8, RWT_REG, OP_RSPEC, 8, RWF_X64, P_64, 0)

#endif

/* predefined types. BYTE must be first! */
/* token    str      type      value     bytval   flags  cpu    sflags */

res(BYTE,   byte,    RWT_STYPE,   0,     MT_BYTE,    0,  P_86, USE_EMPTY)
res(SBYTE,  sbyte,   RWT_STYPE,   0,     MT_SBYTE,   0,  P_86, USE_EMPTY)
res(WORD,   word,    RWT_STYPE,   0,     MT_WORD,    0,  P_86, USE_EMPTY)
res(SWORD,  sword,   RWT_STYPE,   0,     MT_SWORD,   0,  P_86, USE_EMPTY)
res(DWORD,  dword,   RWT_STYPE,   0,     MT_DWORD,   0,  P_86, USE_EMPTY)
res(SDWORD, sdword,  RWT_STYPE,   0,     MT_SDWORD,  0,  P_86, USE_EMPTY)
res(REAL4,  real4,   RWT_STYPE,   0,     MT_REAL4,   0,  P_86, USE_EMPTY)
res(FWORD,  fword,   RWT_STYPE,   0,     MT_FWORD,   0,  P_86, USE_EMPTY)
res(QWORD,  qword,   RWT_STYPE,   0,     MT_QWORD,   0,  P_86, USE_EMPTY)
res(SQWORD, sqword,  RWT_STYPE,   0,     MT_SQWORD,  0,  P_86, USE_EMPTY)
res(REAL8,  real8,   RWT_STYPE,   0,     MT_REAL8,   0,  P_86, USE_EMPTY)
res(TBYTE,  tbyte,   RWT_STYPE,   0,     MT_TBYTE,   0,  P_86, USE_EMPTY)
res(REAL10, real10,  RWT_STYPE,   0,     MT_REAL10,  0,  P_86, USE_EMPTY)
res(OWORD,  oword,   RWT_STYPE,   0,     MT_OWORD,   0,  P_86, USE_EMPTY)
#if AVXSUPP
res(YMMWORD, ymmword, RWT_STYPE, 0, MT_YMMWORD, 0, P_AVX, USE_EMPTY)
res(ZMMWORD, zmmword, RWT_STYPE, 0, MT_ZMMWORD, 0, P_AVX, USE_EMPTY)
/* 2.15 used for VECTORCALL functions*/
#endif
/* NEAR must be first, FAR32 must be last, all contiguous */
res(NEAR, near, RWT_STYPE, 0, MT_NEAR, 0, P_86, USE_EMPTY)
res(FAR, far, RWT_STYPE, 0, MT_FAR, 0, P_86, USE_EMPTY)
res(NEAR16, near16, RWT_STYPE, 0, MT_NEAR, 0, P_386, USE16)
res(NEAR32, near32, RWT_STYPE, 0, MT_NEAR, 0, P_386, USE32)
res(FAR16, far16, RWT_STYPE, 0, MT_FAR, 0, P_386, USE16)
res(FAR32, far32, RWT_STYPE, 0, MT_FAR, 0, P_386, USE32)
#if XMMWORD
res(MMWORD, mmword, RWT_STYPE, 0, MT_QWORD, 0, P_586 | P_MMX, USE_EMPTY)
res(XMMWORD, xmmword, RWT_STYPE, 0, MT_OWORD, 0, P_686 | P_SSE1, USE_EMPTY)
#endif

/* unary operators. bytval contains priority */
/* token        str           type          value   bytval flags cpu  sflags */
res(DOT_TYPE, .type, RWT_UNARY_OP, AT_ALL, 14, 0, P_86, UOT_DOT_TYPE)
res(HIGH, high, RWT_UNARY_OP, AT_TLN, 6, 0, P_86, UOT_HIGH)
#if LOHI32
res(HIGH32, high32, RWT_UNARY_OP, AT_CONST | AT_FLOAT, 6, 0, P_86, UOT_HIGH32)
#endif
res(HIGHWORD, highword, RWT_UNARY_OP, AT_CONST, 6, 0, P_86, UOT_HIGHWORD)
#if IMAGERELSUPP
/* v2.10: changed AT_TLN to AT_LABEL */
//res(IMAGEREL,   imagerel,     RWT_UNARY_OP, AT_TLN,     5,  0,   P_86,  UOT_IMAGEREL  )
res(IMAGEREL, imagerel, RWT_UNARY_OP, AT_LABEL, 5, 0, P_86, UOT_IMAGEREL)
#endif
res(LENGTH, length, RWT_UNARY_OP, AT_LF, 3, 0, P_86, UOT_LENGTH)
res(LENGTHOF, lengthof, RWT_UNARY_OP, AT_LF, 3, 0, P_86, UOT_LENGTHOF)
res(LOW, low, RWT_UNARY_OP, AT_TLN, 6, 0, P_86, UOT_LOW)
#if LOHI32
res(LOW32, low32, RWT_UNARY_OP, AT_TLN | AT_FLOAT, 6, 0, P_86, UOT_LOW32)
#endif
res(FRAMEOFS, frameofs, RWT_UNARY_OP, AT_ALL, 5, 0, P_86, UOT_FRAMEOFS)
res(ARGIDX, argidx, RWT_UNARY_OP, AT_ALL, 5, 0, P_86, UOT_ARGIDX)
res(ARGSIZE, argsize, RWT_UNARY_OP, AT_ALL, 5, 0, P_86, UOT_ARGSIZE)
res(ARGTYPE, argtype, RWT_UNARY_OP, AT_ALL, 5, 0, P_86, UOT_ARGTYPE)
res(LOWWORD, lowword, RWT_UNARY_OP, AT_TLN, 6, 0, P_86, UOT_LOWWORD)
res(LROFFSET, lroffset, RWT_UNARY_OP, AT_LFN, 5, 0, P_86, UOT_LROFFSET)
res(MASK, mask, RWT_UNARY_OP, AT_TBF, 3, 0, P_86, UOT_MASK)
res(OFFSET, offset, RWT_UNARY_OP, AT_TLFN, 5, 0, P_86, UOT_OFFSET)
res(OPATTR, opattr, RWT_UNARY_OP, AT_ALL, 14, 0, P_86, UOT_OPATTR)
#if SECTIONRELSUPP
res(SECTIONREL, sectionrel, RWT_UNARY_OP, AT_LABEL, 5, 0, P_86, UOT_SECTIONREL)
#endif
res(SEG, seg, RWT_UNARY_OP, AT_LABEL, 5, 0, P_86, UOT_SEG)
res(SHORT, short, RWT_UNARY_OP, AT_LABEL, 14, 0, P_86, UOT_SHORT)
res(SIZE, size, RWT_UNARY_OP, AT_TLF, 3, 0, P_86, UOT_SIZE)
res(SIZEOF, sizeof, RWT_UNARY_OP, AT_TLF, 3, 0, P_86, UOT_SIZEOF)
res(THIS, this, RWT_UNARY_OP, AT_TYPE, 5, 0, P_86, UOT_THIS)
res(TYPE, type, RWT_UNARY_OP, AT_ALL, 5, 0, P_86, UOT_TYPE)
res(WIDTH, width, RWT_UNARY_OP, AT_TBF, 3, 0, P_86, UOT_WIDTH)

/* binary operators. bytval contains priority */

/* token        str        type         value  bytval flags   cpu    sflags */
res(EQ,         eq,      RWT_BINARY_OP,  0,    10,      0,    P_86,    0)
res(NE,         ne,      RWT_BINARY_OP,  0,    10,      0,    P_86,    0)
res(GE,         ge,      RWT_BINARY_OP,  0,    10,      0,    P_86,    0)
res(GT,         gt,      RWT_BINARY_OP,  0,    10,      0,    P_86,    0)
res(LE,         le,      RWT_BINARY_OP,  0,    10,      0,    P_86,    0)
res(LT,         lt,      RWT_BINARY_OP,  0,    10,      0,    P_86,    0)
res(MOD,        mod,     RWT_BINARY_OP,  0,    8,       0,    P_86,    0)
res(PTR,        ptr,     RWT_BINARY_OP,  0,    4,       0,    P_86,    0)

/* DUP is also a binary operator, but must be handled differently. */

res(DUP, dup, RWT_RES_ID, 0, 0, 0, P_86, 0)
res(ADDR, addr, RWT_RES_ID, 0, 0, 0, P_86, 0)
res(FLAT, flat, RWT_RES_ID, 0, 0, 0, P_86, 0)
res(VARARG, vararg, RWT_RES_ID, 0, 0, 0, P_86, 0)
#if AMD64_SUPPORT
res(FRAME, frame, RWT_RES_ID, 0, 0, RWF_X64, P_64, 0)
#endif

/* languages, must be in this order! */
/* token      str          type       value bytval        flags     cpu  sflags */
res(C, c, RWT_RES_ID, 0, LANG_C, 0, P_86, 0)
res(SYSCALL, syscall, RWT_RES_ID, 0, LANG_SYSCALL, 0, P_86, 0)
res(STDCALL, stdcall, RWT_RES_ID, 0, LANG_STDCALL, 0, P_86, 0)
res(PASCAL, pascal, RWT_RES_ID, 0, LANG_PASCAL, 0, P_86, 0)
res(FORTRAN, fortran, RWT_RES_ID, 0, LANG_FORTRAN, 0, P_86, 0)
res(BASIC, basic, RWT_RES_ID, 0, LANG_BASIC, 0, P_86, 0)
res(FASTCALL, fastcall, RWT_RES_ID, 0, LANG_FASTCALL, 0, P_64, 0)
/* 2.15 implemented the VECTORCALL */
res(VECTORCALL, vectorcall, RWT_RES_ID, 0, LANG_VECTORCALL, 0, P_64, 0)
/* 2.24 system v and delphi 32 */
res(SYSVCALL, systemv, RWT_RES_ID, 0, LANG_SYSVCALL, 0, P_64, 0)
res(BORLAND, borland, RWT_RES_ID, 0, LANG_DELPHICALL, 0, P_86, 0)
/* 2.46.9 support VOID return type */
res(VOIDARG,   voidarg,    RWT_RES_ID, 0, 0, 0, P_86, 0)

