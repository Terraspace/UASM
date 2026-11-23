; M03: SSE-only operand limits.
.x64
.model flat
option evex:1
.code
gf2p8mulb ymm1, ymm2
gf2p8mulb xmm16, xmm1
gf2p8mulb xmm1, xmm31
gf2p8affineqb xmm1, xmm2, 256
gf2p8affineinvqb xmm1, xmm2, -129
gf2p8mulb xmm1{k1}, xmm2
gf2p8affineqb xmm1{k1}{z}, xmm2, 1
gf2p8mulb xmm1, dword ptr [rax]{1to4}
{evex} gf2p8mulb xmm1, xmm2
end
