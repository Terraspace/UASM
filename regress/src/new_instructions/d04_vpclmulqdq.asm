; D04: VEX/EVEX widths, high registers and full-vector displacement boundaries.
; Bytes independently checked against LLVM.
.x64
.model flat
option evex:1
.code
vpclmulqdq xmm1, xmm2, xmm3, 0
vpclmulqdq xmm8, xmm9, [r13], 0
{evex} vpclmulqdq xmm1, xmm2, xmm3, 0
vpclmulqdq xmm17, xmm22, xmm30, 0
vpclmulqdq xmm31, xmm16, [r13], 0
{evex} vpclmulqdq xmm4, xmm5, [rax+2032], 0
vpclmulqdq xmm18, xmm19, [r12+2048], 0
vpclmulqdq xmm18, xmm19, [r12-2048], 0
vpclmulqdq xmm1, xmm2, xmm3, 1
vpclmulqdq xmm8, xmm9, [r13], 1
{evex} vpclmulqdq xmm1, xmm2, xmm3, 1
vpclmulqdq xmm17, xmm22, xmm30, 1
vpclmulqdq xmm31, xmm16, [r13], 1
{evex} vpclmulqdq xmm4, xmm5, [rax+2032], 1
vpclmulqdq xmm18, xmm19, [r12+2048], 1
vpclmulqdq xmm18, xmm19, [r12-2048], 1
vpclmulqdq xmm1, xmm2, xmm3, 16
vpclmulqdq xmm8, xmm9, [r13], 16
{evex} vpclmulqdq xmm1, xmm2, xmm3, 16
vpclmulqdq xmm17, xmm22, xmm30, 16
vpclmulqdq xmm31, xmm16, [r13], 16
{evex} vpclmulqdq xmm4, xmm5, [rax+2032], 16
vpclmulqdq xmm18, xmm19, [r12+2048], 16
vpclmulqdq xmm18, xmm19, [r12-2048], 16
vpclmulqdq xmm1, xmm2, xmm3, 17
vpclmulqdq xmm8, xmm9, [r13], 17
{evex} vpclmulqdq xmm1, xmm2, xmm3, 17
vpclmulqdq xmm17, xmm22, xmm30, 17
vpclmulqdq xmm31, xmm16, [r13], 17
{evex} vpclmulqdq xmm4, xmm5, [rax+2032], 17
vpclmulqdq xmm18, xmm19, [r12+2048], 17
vpclmulqdq xmm18, xmm19, [r12-2048], 17
vpclmulqdq xmm1, xmm2, xmm3, 255
vpclmulqdq xmm8, xmm9, [r13], 255
{evex} vpclmulqdq xmm1, xmm2, xmm3, 255
vpclmulqdq xmm17, xmm22, xmm30, 255
vpclmulqdq xmm31, xmm16, [r13], 255
{evex} vpclmulqdq xmm4, xmm5, [rax+2032], 255
vpclmulqdq xmm18, xmm19, [r12+2048], 255
vpclmulqdq xmm18, xmm19, [r12-2048], 255
vpclmulqdq ymm1, ymm2, ymm3, 0
vpclmulqdq ymm8, ymm9, [r13], 0
{evex} vpclmulqdq ymm1, ymm2, ymm3, 0
vpclmulqdq ymm17, ymm22, ymm30, 0
vpclmulqdq ymm31, ymm16, [r13], 0
{evex} vpclmulqdq ymm4, ymm5, [rax+4064], 0
vpclmulqdq ymm18, ymm19, [r12+4096], 0
vpclmulqdq ymm18, ymm19, [r12-4096], 0
vpclmulqdq ymm1, ymm2, ymm3, 1
vpclmulqdq ymm8, ymm9, [r13], 1
{evex} vpclmulqdq ymm1, ymm2, ymm3, 1
vpclmulqdq ymm17, ymm22, ymm30, 1
vpclmulqdq ymm31, ymm16, [r13], 1
{evex} vpclmulqdq ymm4, ymm5, [rax+4064], 1
vpclmulqdq ymm18, ymm19, [r12+4096], 1
vpclmulqdq ymm18, ymm19, [r12-4096], 1
vpclmulqdq ymm1, ymm2, ymm3, 16
vpclmulqdq ymm8, ymm9, [r13], 16
{evex} vpclmulqdq ymm1, ymm2, ymm3, 16
vpclmulqdq ymm17, ymm22, ymm30, 16
vpclmulqdq ymm31, ymm16, [r13], 16
{evex} vpclmulqdq ymm4, ymm5, [rax+4064], 16
vpclmulqdq ymm18, ymm19, [r12+4096], 16
vpclmulqdq ymm18, ymm19, [r12-4096], 16
vpclmulqdq ymm1, ymm2, ymm3, 17
vpclmulqdq ymm8, ymm9, [r13], 17
{evex} vpclmulqdq ymm1, ymm2, ymm3, 17
vpclmulqdq ymm17, ymm22, ymm30, 17
vpclmulqdq ymm31, ymm16, [r13], 17
{evex} vpclmulqdq ymm4, ymm5, [rax+4064], 17
vpclmulqdq ymm18, ymm19, [r12+4096], 17
vpclmulqdq ymm18, ymm19, [r12-4096], 17
vpclmulqdq ymm1, ymm2, ymm3, 255
vpclmulqdq ymm8, ymm9, [r13], 255
{evex} vpclmulqdq ymm1, ymm2, ymm3, 255
vpclmulqdq ymm17, ymm22, ymm30, 255
vpclmulqdq ymm31, ymm16, [r13], 255
{evex} vpclmulqdq ymm4, ymm5, [rax+4064], 255
vpclmulqdq ymm18, ymm19, [r12+4096], 255
vpclmulqdq ymm18, ymm19, [r12-4096], 255
{evex} vpclmulqdq zmm1, zmm2, zmm3, 0
vpclmulqdq zmm17, zmm22, zmm30, 0
vpclmulqdq zmm31, zmm16, [r13], 0
{evex} vpclmulqdq zmm4, zmm5, [rax+8128], 0
vpclmulqdq zmm18, zmm19, [r12+8192], 0
vpclmulqdq zmm18, zmm19, [r12-8192], 0
{evex} vpclmulqdq zmm1, zmm2, zmm3, 1
vpclmulqdq zmm17, zmm22, zmm30, 1
vpclmulqdq zmm31, zmm16, [r13], 1
{evex} vpclmulqdq zmm4, zmm5, [rax+8128], 1
vpclmulqdq zmm18, zmm19, [r12+8192], 1
vpclmulqdq zmm18, zmm19, [r12-8192], 1
{evex} vpclmulqdq zmm1, zmm2, zmm3, 16
vpclmulqdq zmm17, zmm22, zmm30, 16
vpclmulqdq zmm31, zmm16, [r13], 16
{evex} vpclmulqdq zmm4, zmm5, [rax+8128], 16
vpclmulqdq zmm18, zmm19, [r12+8192], 16
vpclmulqdq zmm18, zmm19, [r12-8192], 16
{evex} vpclmulqdq zmm1, zmm2, zmm3, 17
vpclmulqdq zmm17, zmm22, zmm30, 17
vpclmulqdq zmm31, zmm16, [r13], 17
{evex} vpclmulqdq zmm4, zmm5, [rax+8128], 17
vpclmulqdq zmm18, zmm19, [r12+8192], 17
vpclmulqdq zmm18, zmm19, [r12-8192], 17
{evex} vpclmulqdq zmm1, zmm2, zmm3, 255
vpclmulqdq zmm17, zmm22, zmm30, 255
vpclmulqdq zmm31, zmm16, [r13], 255
{evex} vpclmulqdq zmm4, zmm5, [rax+8128], 255
vpclmulqdq zmm18, zmm19, [r12+8192], 255
vpclmulqdq zmm18, zmm19, [r12-8192], 255
end
