; Invalid widths/memory forms/decorators.
.x64
.model flat
option evex:1
.code
vcvtneps2bf16 zmm1, zmm2
vcvtneps2bf16 xmm1, zmm2
vcvtneps2bf16 ymm1, ymm2
vcvtneps2bf16 ymm1, ymmword ptr [rax]
vcvtneps2bf16 xmm1{k1}, dword ptr [rax]{1to16}
vdpbf16ps xmm1, ymm2, xmm3
vdpbf16ps zmm1, zmm2, qword ptr [rax]{1to8}
vcvtne2ps2bf16 xmm1, xmm2, ymm3
end
