; D04: VEX/EVEX widths, high registers and full-vector displacement boundaries.
; Bytes independently checked against LLVM.
.x64
.model flat
option evex:1
.code
vaesenc xmm1, xmm2, xmm3
vaesenc xmm8, xmm9, [r13]
{evex} vaesenc xmm1, xmm2, xmm3
vaesenc xmm17, xmm22, xmm30
vaesenc xmm31, xmm16, [r13]
{evex} vaesenc xmm4, xmm5, [rax+2032]
vaesenc xmm18, xmm19, [r12+2048]
vaesenc xmm18, xmm19, [r12-2048]
vaesenc ymm1, ymm2, ymm3
vaesenc ymm8, ymm9, [r13]
{evex} vaesenc ymm1, ymm2, ymm3
vaesenc ymm17, ymm22, ymm30
vaesenc ymm31, ymm16, [r13]
{evex} vaesenc ymm4, ymm5, [rax+4064]
vaesenc ymm18, ymm19, [r12+4096]
vaesenc ymm18, ymm19, [r12-4096]
{evex} vaesenc zmm1, zmm2, zmm3
vaesenc zmm17, zmm22, zmm30
vaesenc zmm31, zmm16, [r13]
{evex} vaesenc zmm4, zmm5, [rax+8128]
vaesenc zmm18, zmm19, [r12+8192]
vaesenc zmm18, zmm19, [r12-8192]
vaesenclast xmm1, xmm2, xmm3
vaesenclast xmm8, xmm9, [r13]
{evex} vaesenclast xmm1, xmm2, xmm3
vaesenclast xmm17, xmm22, xmm30
vaesenclast xmm31, xmm16, [r13]
{evex} vaesenclast xmm4, xmm5, [rax+2032]
vaesenclast xmm18, xmm19, [r12+2048]
vaesenclast xmm18, xmm19, [r12-2048]
vaesenclast ymm1, ymm2, ymm3
vaesenclast ymm8, ymm9, [r13]
{evex} vaesenclast ymm1, ymm2, ymm3
vaesenclast ymm17, ymm22, ymm30
vaesenclast ymm31, ymm16, [r13]
{evex} vaesenclast ymm4, ymm5, [rax+4064]
vaesenclast ymm18, ymm19, [r12+4096]
vaesenclast ymm18, ymm19, [r12-4096]
{evex} vaesenclast zmm1, zmm2, zmm3
vaesenclast zmm17, zmm22, zmm30
vaesenclast zmm31, zmm16, [r13]
{evex} vaesenclast zmm4, zmm5, [rax+8128]
vaesenclast zmm18, zmm19, [r12+8192]
vaesenclast zmm18, zmm19, [r12-8192]
vaesdec xmm1, xmm2, xmm3
vaesdec xmm8, xmm9, [r13]
{evex} vaesdec xmm1, xmm2, xmm3
vaesdec xmm17, xmm22, xmm30
vaesdec xmm31, xmm16, [r13]
{evex} vaesdec xmm4, xmm5, [rax+2032]
vaesdec xmm18, xmm19, [r12+2048]
vaesdec xmm18, xmm19, [r12-2048]
vaesdec ymm1, ymm2, ymm3
vaesdec ymm8, ymm9, [r13]
{evex} vaesdec ymm1, ymm2, ymm3
vaesdec ymm17, ymm22, ymm30
vaesdec ymm31, ymm16, [r13]
{evex} vaesdec ymm4, ymm5, [rax+4064]
vaesdec ymm18, ymm19, [r12+4096]
vaesdec ymm18, ymm19, [r12-4096]
{evex} vaesdec zmm1, zmm2, zmm3
vaesdec zmm17, zmm22, zmm30
vaesdec zmm31, zmm16, [r13]
{evex} vaesdec zmm4, zmm5, [rax+8128]
vaesdec zmm18, zmm19, [r12+8192]
vaesdec zmm18, zmm19, [r12-8192]
vaesdeclast xmm1, xmm2, xmm3
vaesdeclast xmm8, xmm9, [r13]
{evex} vaesdeclast xmm1, xmm2, xmm3
vaesdeclast xmm17, xmm22, xmm30
vaesdeclast xmm31, xmm16, [r13]
{evex} vaesdeclast xmm4, xmm5, [rax+2032]
vaesdeclast xmm18, xmm19, [r12+2048]
vaesdeclast xmm18, xmm19, [r12-2048]
vaesdeclast ymm1, ymm2, ymm3
vaesdeclast ymm8, ymm9, [r13]
{evex} vaesdeclast ymm1, ymm2, ymm3
vaesdeclast ymm17, ymm22, ymm30
vaesdeclast ymm31, ymm16, [r13]
{evex} vaesdeclast ymm4, ymm5, [rax+4064]
vaesdeclast ymm18, ymm19, [r12+4096]
vaesdeclast ymm18, ymm19, [r12-4096]
{evex} vaesdeclast zmm1, zmm2, zmm3
vaesdeclast zmm17, zmm22, zmm30
vaesdeclast zmm31, zmm16, [r13]
{evex} vaesdeclast zmm4, zmm5, [rax+8128]
vaesdeclast zmm18, zmm19, [r12+8192]
vaesdeclast zmm18, zmm19, [r12-8192]
end
