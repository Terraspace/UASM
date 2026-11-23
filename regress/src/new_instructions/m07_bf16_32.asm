; LLVM-verified ISA forms, mixed widths, high registers and memory.
.686p
.xmm
.model flat
option evex:1
.code
{evex} vcvtne2ps2bf16 xmm1, xmm2, xmm3
{evex} vcvtne2ps2bf16 xmm1{k3}, xmm2, xmm3
{evex} vcvtne2ps2bf16 xmm1{k3}{z}, xmm2, xmm3
{evex} vcvtne2ps2bf16 xmm1{k3}, xmm2, xmm3
{evex} vcvtne2ps2bf16 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
{evex} vcvtne2ps2bf16 xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+128]
{evex} vcvtne2ps2bf16 xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+128]
{evex} vcvtne2ps2bf16 xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+128]
{evex} vcvtne2ps2bf16 xmm1{k2}, xmm2, dword ptr [ebx+508]{1to4}
{evex} vcvtne2ps2bf16 ymm1, ymm2, ymm3
{evex} vcvtne2ps2bf16 ymm1{k3}, ymm2, ymm3
{evex} vcvtne2ps2bf16 ymm1{k3}{z}, ymm2, ymm3
{evex} vcvtne2ps2bf16 ymm1{k3}, ymm2, ymm3
{evex} vcvtne2ps2bf16 ymm1, ymm2, ymmword ptr [ebx+esi*2+128]
{evex} vcvtne2ps2bf16 ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+128]
{evex} vcvtne2ps2bf16 ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+128]
{evex} vcvtne2ps2bf16 ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+128]
{evex} vcvtne2ps2bf16 ymm1{k2}, ymm2, dword ptr [ebx+508]{1to8}
{evex} vcvtne2ps2bf16 zmm1, zmm2, zmm3
{evex} vcvtne2ps2bf16 zmm1{k3}, zmm2, zmm3
{evex} vcvtne2ps2bf16 zmm1{k3}{z}, zmm2, zmm3
{evex} vcvtne2ps2bf16 zmm1{k3}, zmm2, zmm3
{evex} vcvtne2ps2bf16 zmm1, zmm2, zmmword ptr [ebx+esi*2+128]
{evex} vcvtne2ps2bf16 zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+128]
{evex} vcvtne2ps2bf16 zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+128]
{evex} vcvtne2ps2bf16 zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+128]
{evex} vcvtne2ps2bf16 zmm1{k2}, zmm2, dword ptr [ebx+508]{1to16}
{evex} vcvtneps2bf16 xmm1, xmm2
{evex} vcvtneps2bf16 xmm1{k3}, xmm2
{evex} vcvtneps2bf16 xmm1{k3}{z}, xmm2
{evex} vcvtneps2bf16 xmm1{k3}, xmm2
{evex} vcvtneps2bf16 xmm1, xmmword ptr [ebx+esi*2+128]
{evex} vcvtneps2bf16 xmm1{k3}, xmmword ptr [ebx+esi*2+128]
{evex} vcvtneps2bf16 xmm1{k3}{z}, xmmword ptr [ebx+esi*2+128]
{evex} vcvtneps2bf16 xmm1{k3}, xmmword ptr [ebx+esi*2+128]
{evex} vcvtneps2bf16 xmm1{k2}, dword ptr [ebx+508]{1to4}
{evex} vcvtneps2bf16 xmm1, ymm2
{evex} vcvtneps2bf16 xmm1{k3}, ymm2
{evex} vcvtneps2bf16 xmm1{k3}{z}, ymm2
{evex} vcvtneps2bf16 xmm1{k3}, ymm2
{evex} vcvtneps2bf16 xmm1, ymmword ptr [ebx+esi*2+128]
{evex} vcvtneps2bf16 xmm1{k3}, ymmword ptr [ebx+esi*2+128]
{evex} vcvtneps2bf16 xmm1{k3}{z}, ymmword ptr [ebx+esi*2+128]
{evex} vcvtneps2bf16 xmm1{k3}, ymmword ptr [ebx+esi*2+128]
{evex} vcvtneps2bf16 xmm1{k2}, dword ptr [ebx+508]{1to8}
{evex} vcvtneps2bf16 ymm1, zmm2
{evex} vcvtneps2bf16 ymm1{k3}, zmm2
{evex} vcvtneps2bf16 ymm1{k3}{z}, zmm2
{evex} vcvtneps2bf16 ymm1{k3}, zmm2
{evex} vcvtneps2bf16 ymm1, zmmword ptr [ebx+esi*2+128]
{evex} vcvtneps2bf16 ymm1{k3}, zmmword ptr [ebx+esi*2+128]
{evex} vcvtneps2bf16 ymm1{k3}{z}, zmmword ptr [ebx+esi*2+128]
{evex} vcvtneps2bf16 ymm1{k3}, zmmword ptr [ebx+esi*2+128]
{evex} vcvtneps2bf16 ymm1{k2}, dword ptr [ebx+508]{1to16}
{evex} vdpbf16ps xmm1, xmm2, xmm3
{evex} vdpbf16ps xmm1{k3}, xmm2, xmm3
{evex} vdpbf16ps xmm1{k3}{z}, xmm2, xmm3
{evex} vdpbf16ps xmm1{k3}, xmm2, xmm3
{evex} vdpbf16ps xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
{evex} vdpbf16ps xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+128]
{evex} vdpbf16ps xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+128]
{evex} vdpbf16ps xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+128]
{evex} vdpbf16ps xmm1{k2}, xmm2, dword ptr [ebx+508]{1to4}
{evex} vdpbf16ps ymm1, ymm2, ymm3
{evex} vdpbf16ps ymm1{k3}, ymm2, ymm3
{evex} vdpbf16ps ymm1{k3}{z}, ymm2, ymm3
{evex} vdpbf16ps ymm1{k3}, ymm2, ymm3
{evex} vdpbf16ps ymm1, ymm2, ymmword ptr [ebx+esi*2+128]
{evex} vdpbf16ps ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+128]
{evex} vdpbf16ps ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+128]
{evex} vdpbf16ps ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+128]
{evex} vdpbf16ps ymm1{k2}, ymm2, dword ptr [ebx+508]{1to8}
{evex} vdpbf16ps zmm1, zmm2, zmm3
{evex} vdpbf16ps zmm1{k3}, zmm2, zmm3
{evex} vdpbf16ps zmm1{k3}{z}, zmm2, zmm3
{evex} vdpbf16ps zmm1{k3}, zmm2, zmm3
{evex} vdpbf16ps zmm1, zmm2, zmmword ptr [ebx+esi*2+128]
{evex} vdpbf16ps zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+128]
{evex} vdpbf16ps zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+128]
{evex} vdpbf16ps zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+128]
{evex} vdpbf16ps zmm1{k2}, zmm2, dword ptr [ebx+508]{1to16}
end
