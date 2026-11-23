; Invalid widths/memory forms/decorators.
.x64
.model flat
option evex:1
.code
vsha512msg1 xmm1, xmm2
vsha512msg1 ymm1, ymm2
vsha512msg1 ymm1, [rax]
vsha512msg2 ymm1, xmm2
vsha512rnds2 ymm1, ymm2, ymm3
vsm3msg1 ymm1, ymm2, ymm3
vsm3msg2 xmm1, xmm2, qword ptr [rax]
vsm3rnds2 xmm1, xmm2, xmm3, 256
vsm4key4 zmm1, zmm2, zmm3
vsm4rnds4 xmm1{k1}, xmm2, xmm3
vsm4key4 xmm17, xmm2, xmm3
{evex} vsha512msg2 ymm1, ymm2
end
