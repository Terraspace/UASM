; M01: VBMI byte permutation; expected bytes checked independently with LLVM.
.x64
.model flat
option evex:1
.code
vpermt2b xmm1, xmm2, xmm3
{evex} vpermt2b xmm4, xmm5, xmm6
vpermt2b xmm17{k3}, xmm22, xmm30
vpermt2b xmm31{k7}{z}, xmm16, xmm15
vpermt2b xmm8, xmm9, [r13]
vpermt2b xmm15{k1}, xmm31, [rbp]
vpermt2b xmm18{k2}{z}, xmm19, [r12+r14*2+2032]
vpermt2b xmm18{k2}{z}, xmm19, [r12+r14*2+2048]
vpermt2b xmm18{k2}{z}, xmm19, [r12+r14*2-2048]
vpermt2b xmm18{k2}{z}, xmm19, [r12+r14*2-2064]
vpermt2b xmm18{k2}{z}, xmm19, [r12+r14*2+1]
vpermt2b ymm1, ymm2, ymm3
{evex} vpermt2b ymm4, ymm5, ymm6
vpermt2b ymm17{k3}, ymm22, ymm30
vpermt2b ymm31{k7}{z}, ymm16, ymm15
vpermt2b ymm8, ymm9, [r13]
vpermt2b ymm15{k1}, ymm31, [rbp]
vpermt2b ymm18{k2}{z}, ymm19, [r12+r14*2+4064]
vpermt2b ymm18{k2}{z}, ymm19, [r12+r14*2+4096]
vpermt2b ymm18{k2}{z}, ymm19, [r12+r14*2-4096]
vpermt2b ymm18{k2}{z}, ymm19, [r12+r14*2-4128]
vpermt2b ymm18{k2}{z}, ymm19, [r12+r14*2+1]
vpermt2b zmm1, zmm2, zmm3
{evex} vpermt2b zmm4, zmm5, zmm6
vpermt2b zmm17{k3}, zmm22, zmm30
vpermt2b zmm31{k7}{z}, zmm16, zmm15
vpermt2b zmm8, zmm9, [r13]
vpermt2b zmm15{k1}, zmm31, [rbp]
vpermt2b zmm18{k2}{z}, zmm19, [r12+r14*2+8128]
vpermt2b zmm18{k2}{z}, zmm19, [r12+r14*2+8192]
vpermt2b zmm18{k2}{z}, zmm19, [r12+r14*2-8192]
vpermt2b zmm18{k2}{z}, zmm19, [r12+r14*2-8256]
vpermt2b zmm18{k2}{z}, zmm19, [r12+r14*2+1]
end
