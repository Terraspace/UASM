; D02/D03: EVEX W=0; VEX controls, masks, high registers and displacement boundaries.
; Expected bytes independently checked with LLVM 22.1.3.
.x64
.model flat
option evex:1
.code
vgf2p8mulb xmm1, xmm2, xmm3
vgf2p8mulb xmm4, xmm5, [rax]
{evex} vgf2p8mulb xmm1, xmm2, xmm3
vgf2p8mulb xmm17{k3}, xmm22, xmm30
vgf2p8mulb xmm31{k7}{z}, xmm16, [r13]
{evex} vgf2p8mulb xmm4, xmm5, [rax+2032]
vgf2p8mulb xmm18{k2}, xmm19, [r12+2048]
vgf2p8mulb ymm1, ymm2, ymm3
vgf2p8mulb ymm4, ymm5, [rax]
{evex} vgf2p8mulb ymm1, ymm2, ymm3
vgf2p8mulb ymm17{k3}, ymm22, ymm30
vgf2p8mulb ymm31{k7}{z}, ymm16, [r13]
{evex} vgf2p8mulb ymm4, ymm5, [rax+4064]
vgf2p8mulb ymm18{k2}, ymm19, [r12+4096]
{evex} vgf2p8mulb zmm1, zmm2, zmm3
vgf2p8mulb zmm17{k3}, zmm22, zmm30
vgf2p8mulb zmm31{k7}{z}, zmm16, [r13]
{evex} vgf2p8mulb zmm4, zmm5, [rax+8128]
vgf2p8mulb zmm18{k2}, zmm19, [r12+8192]
{evex} vgf2p8affineqb xmm1{k2}{z}, xmm2, xmm3, 17
{evex} vgf2p8affineqb ymm1{k2}{z}, ymm2, ymm3, 17
{evex} vgf2p8affineqb zmm1{k2}{z}, zmm2, zmm3, 17
{evex} vgf2p8affineinvqb xmm1{k2}{z}, xmm2, xmm3, 17
{evex} vgf2p8affineinvqb ymm1{k2}{z}, ymm2, ymm3, 17
{evex} vgf2p8affineinvqb zmm1{k2}{z}, zmm2, zmm3, 17
end
