; LLVM-verified ISA forms, mixed widths, high registers and memory.
.x64
.model flat
option evex:1
.code
{evex} vcvtne2ps2bf16 xmm1, xmm2, xmm3
{evex} vcvtne2ps2bf16 xmm31{k3}, xmm16, xmm30
{evex} vcvtne2ps2bf16 xmm31{k3}{z}, xmm16, xmm30
{evex} vcvtne2ps2bf16 xmm31{k3}, xmm16, xmm30
{evex} vcvtne2ps2bf16 xmm1, xmm2, xmmword ptr [r13]
{evex} vcvtne2ps2bf16 xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+2032]
{evex} vcvtne2ps2bf16 xmm31{k3}{z}, xmm16, xmmword ptr [r12+r14*2+2048]
{evex} vcvtne2ps2bf16 xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+1]
{evex} vcvtne2ps2bf16 xmm1{k2}, xmm2, dword ptr [r13+508]{1to4}
{evex} vcvtne2ps2bf16 ymm1, ymm2, ymm3
{evex} vcvtne2ps2bf16 ymm31{k3}, ymm16, ymm30
{evex} vcvtne2ps2bf16 ymm31{k3}{z}, ymm16, ymm30
{evex} vcvtne2ps2bf16 ymm31{k3}, ymm16, ymm30
{evex} vcvtne2ps2bf16 ymm1, ymm2, ymmword ptr [r13]
{evex} vcvtne2ps2bf16 ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+4064]
{evex} vcvtne2ps2bf16 ymm31{k3}{z}, ymm16, ymmword ptr [r12+r14*2+4096]
{evex} vcvtne2ps2bf16 ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+1]
{evex} vcvtne2ps2bf16 ymm1{k2}, ymm2, dword ptr [r13+508]{1to8}
{evex} vcvtne2ps2bf16 zmm1, zmm2, zmm3
{evex} vcvtne2ps2bf16 zmm31{k3}, zmm16, zmm30
{evex} vcvtne2ps2bf16 zmm31{k3}{z}, zmm16, zmm30
{evex} vcvtne2ps2bf16 zmm31{k3}, zmm16, zmm30
{evex} vcvtne2ps2bf16 zmm1, zmm2, zmmword ptr [r13]
{evex} vcvtne2ps2bf16 zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+8128]
{evex} vcvtne2ps2bf16 zmm31{k3}{z}, zmm16, zmmword ptr [r12+r14*2+8192]
{evex} vcvtne2ps2bf16 zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+1]
{evex} vcvtne2ps2bf16 zmm1{k2}, zmm2, dword ptr [r13+508]{1to16}
{evex} vcvtneps2bf16 xmm1, xmm2
{evex} vcvtneps2bf16 xmm31{k3}, xmm16
{evex} vcvtneps2bf16 xmm31{k3}{z}, xmm16
{evex} vcvtneps2bf16 xmm31{k3}, xmm16
{evex} vcvtneps2bf16 xmm1, xmmword ptr [r13]
{evex} vcvtneps2bf16 xmm31{k3}, xmmword ptr [r12+r14*2+2032]
{evex} vcvtneps2bf16 xmm31{k3}{z}, xmmword ptr [r12+r14*2+2048]
{evex} vcvtneps2bf16 xmm31{k3}, xmmword ptr [r12+r14*2+1]
{evex} vcvtneps2bf16 xmm1{k2}, dword ptr [r13+508]{1to4}
{evex} vcvtneps2bf16 xmm1, ymm2
{evex} vcvtneps2bf16 xmm31{k3}, ymm16
{evex} vcvtneps2bf16 xmm31{k3}{z}, ymm16
{evex} vcvtneps2bf16 xmm31{k3}, ymm16
{evex} vcvtneps2bf16 xmm1, ymmword ptr [r13]
{evex} vcvtneps2bf16 xmm31{k3}, ymmword ptr [r12+r14*2+4064]
{evex} vcvtneps2bf16 xmm31{k3}{z}, ymmword ptr [r12+r14*2+4096]
{evex} vcvtneps2bf16 xmm31{k3}, ymmword ptr [r12+r14*2+1]
{evex} vcvtneps2bf16 xmm1{k2}, dword ptr [r13+508]{1to8}
{evex} vcvtneps2bf16 ymm1, zmm2
{evex} vcvtneps2bf16 ymm31{k3}, zmm16
{evex} vcvtneps2bf16 ymm31{k3}{z}, zmm16
{evex} vcvtneps2bf16 ymm31{k3}, zmm16
{evex} vcvtneps2bf16 ymm1, zmmword ptr [r13]
{evex} vcvtneps2bf16 ymm31{k3}, zmmword ptr [r12+r14*2+8128]
{evex} vcvtneps2bf16 ymm31{k3}{z}, zmmword ptr [r12+r14*2+8192]
{evex} vcvtneps2bf16 ymm31{k3}, zmmword ptr [r12+r14*2+1]
{evex} vcvtneps2bf16 ymm1{k2}, dword ptr [r13+508]{1to16}
{evex} vdpbf16ps xmm1, xmm2, xmm3
{evex} vdpbf16ps xmm31{k3}, xmm16, xmm30
{evex} vdpbf16ps xmm31{k3}{z}, xmm16, xmm30
{evex} vdpbf16ps xmm31{k3}, xmm16, xmm30
{evex} vdpbf16ps xmm1, xmm2, xmmword ptr [r13]
{evex} vdpbf16ps xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+2032]
{evex} vdpbf16ps xmm31{k3}{z}, xmm16, xmmword ptr [r12+r14*2+2048]
{evex} vdpbf16ps xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+1]
{evex} vdpbf16ps xmm1{k2}, xmm2, dword ptr [r13+508]{1to4}
{evex} vdpbf16ps ymm1, ymm2, ymm3
{evex} vdpbf16ps ymm31{k3}, ymm16, ymm30
{evex} vdpbf16ps ymm31{k3}{z}, ymm16, ymm30
{evex} vdpbf16ps ymm31{k3}, ymm16, ymm30
{evex} vdpbf16ps ymm1, ymm2, ymmword ptr [r13]
{evex} vdpbf16ps ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+4064]
{evex} vdpbf16ps ymm31{k3}{z}, ymm16, ymmword ptr [r12+r14*2+4096]
{evex} vdpbf16ps ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+1]
{evex} vdpbf16ps ymm1{k2}, ymm2, dword ptr [r13+508]{1to8}
{evex} vdpbf16ps zmm1, zmm2, zmm3
{evex} vdpbf16ps zmm31{k3}, zmm16, zmm30
{evex} vdpbf16ps zmm31{k3}{z}, zmm16, zmm30
{evex} vdpbf16ps zmm31{k3}, zmm16, zmm30
{evex} vdpbf16ps zmm1, zmm2, zmmword ptr [r13]
{evex} vdpbf16ps zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+8128]
{evex} vdpbf16ps zmm31{k3}{z}, zmm16, zmmword ptr [r12+r14*2+8192]
{evex} vdpbf16ps zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+1]
{evex} vdpbf16ps zmm1{k2}, zmm2, dword ptr [r13+508]{1to16}
end
