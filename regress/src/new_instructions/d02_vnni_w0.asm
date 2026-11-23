; D02/D03: EVEX W=0; VEX controls, masks, high registers and displacement boundaries.
; Expected bytes independently checked with LLVM 22.1.3.
.x64
.model flat
option evex:1
.code
vpdpbusd xmm1, xmm2, xmm3
vpdpbusd xmm4, xmm5, [rax]
{evex} vpdpbusd xmm1, xmm2, xmm3
vpdpbusd xmm17{k3}, xmm22, xmm30
vpdpbusd xmm31{k7}{z}, xmm16, [r13]
{evex} vpdpbusd xmm4, xmm5, [rax+2032]
vpdpbusd xmm18{k2}, xmm19, [r12+2048]
vpdpbusd xmm17{k1}{z}, xmm20, dword ptr [r13+508]{1to4}
vpdpbusd ymm1, ymm2, ymm3
vpdpbusd ymm4, ymm5, [rax]
{evex} vpdpbusd ymm1, ymm2, ymm3
vpdpbusd ymm17{k3}, ymm22, ymm30
vpdpbusd ymm31{k7}{z}, ymm16, [r13]
{evex} vpdpbusd ymm4, ymm5, [rax+4064]
vpdpbusd ymm18{k2}, ymm19, [r12+4096]
vpdpbusd ymm17{k1}{z}, ymm20, dword ptr [r13+508]{1to8}
{evex} vpdpbusd zmm1, zmm2, zmm3
vpdpbusd zmm17{k3}, zmm22, zmm30
vpdpbusd zmm31{k7}{z}, zmm16, [r13]
{evex} vpdpbusd zmm4, zmm5, [rax+8128]
vpdpbusd zmm18{k2}, zmm19, [r12+8192]
vpdpbusd zmm17{k1}{z}, zmm20, dword ptr [r13+508]{1to16}
vpdpbusds xmm1, xmm2, xmm3
vpdpbusds xmm4, xmm5, [rax]
{evex} vpdpbusds xmm1, xmm2, xmm3
vpdpbusds xmm17{k3}, xmm22, xmm30
vpdpbusds xmm31{k7}{z}, xmm16, [r13]
{evex} vpdpbusds xmm4, xmm5, [rax+2032]
vpdpbusds xmm18{k2}, xmm19, [r12+2048]
vpdpbusds xmm17{k1}{z}, xmm20, dword ptr [r13+508]{1to4}
vpdpbusds ymm1, ymm2, ymm3
vpdpbusds ymm4, ymm5, [rax]
{evex} vpdpbusds ymm1, ymm2, ymm3
vpdpbusds ymm17{k3}, ymm22, ymm30
vpdpbusds ymm31{k7}{z}, ymm16, [r13]
{evex} vpdpbusds ymm4, ymm5, [rax+4064]
vpdpbusds ymm18{k2}, ymm19, [r12+4096]
vpdpbusds ymm17{k1}{z}, ymm20, dword ptr [r13+508]{1to8}
{evex} vpdpbusds zmm1, zmm2, zmm3
vpdpbusds zmm17{k3}, zmm22, zmm30
vpdpbusds zmm31{k7}{z}, zmm16, [r13]
{evex} vpdpbusds zmm4, zmm5, [rax+8128]
vpdpbusds zmm18{k2}, zmm19, [r12+8192]
vpdpbusds zmm17{k1}{z}, zmm20, dword ptr [r13+508]{1to16}
vpdpwssd xmm1, xmm2, xmm3
vpdpwssd xmm4, xmm5, [rax]
{evex} vpdpwssd xmm1, xmm2, xmm3
vpdpwssd xmm17{k3}, xmm22, xmm30
vpdpwssd xmm31{k7}{z}, xmm16, [r13]
{evex} vpdpwssd xmm4, xmm5, [rax+2032]
vpdpwssd xmm18{k2}, xmm19, [r12+2048]
vpdpwssd xmm17{k1}{z}, xmm20, dword ptr [r13+508]{1to4}
vpdpwssd ymm1, ymm2, ymm3
vpdpwssd ymm4, ymm5, [rax]
{evex} vpdpwssd ymm1, ymm2, ymm3
vpdpwssd ymm17{k3}, ymm22, ymm30
vpdpwssd ymm31{k7}{z}, ymm16, [r13]
{evex} vpdpwssd ymm4, ymm5, [rax+4064]
vpdpwssd ymm18{k2}, ymm19, [r12+4096]
vpdpwssd ymm17{k1}{z}, ymm20, dword ptr [r13+508]{1to8}
{evex} vpdpwssd zmm1, zmm2, zmm3
vpdpwssd zmm17{k3}, zmm22, zmm30
vpdpwssd zmm31{k7}{z}, zmm16, [r13]
{evex} vpdpwssd zmm4, zmm5, [rax+8128]
vpdpwssd zmm18{k2}, zmm19, [r12+8192]
vpdpwssd zmm17{k1}{z}, zmm20, dword ptr [r13+508]{1to16}
vpdpwssds xmm1, xmm2, xmm3
vpdpwssds xmm4, xmm5, [rax]
{evex} vpdpwssds xmm1, xmm2, xmm3
vpdpwssds xmm17{k3}, xmm22, xmm30
vpdpwssds xmm31{k7}{z}, xmm16, [r13]
{evex} vpdpwssds xmm4, xmm5, [rax+2032]
vpdpwssds xmm18{k2}, xmm19, [r12+2048]
vpdpwssds xmm17{k1}{z}, xmm20, dword ptr [r13+508]{1to4}
vpdpwssds ymm1, ymm2, ymm3
vpdpwssds ymm4, ymm5, [rax]
{evex} vpdpwssds ymm1, ymm2, ymm3
vpdpwssds ymm17{k3}, ymm22, ymm30
vpdpwssds ymm31{k7}{z}, ymm16, [r13]
{evex} vpdpwssds ymm4, ymm5, [rax+4064]
vpdpwssds ymm18{k2}, ymm19, [r12+4096]
vpdpwssds ymm17{k1}{z}, ymm20, dword ptr [r13+508]{1to8}
{evex} vpdpwssds zmm1, zmm2, zmm3
vpdpwssds zmm17{k3}, zmm22, zmm30
vpdpwssds zmm31{k7}{z}, zmm16, [r13]
{evex} vpdpwssds zmm4, zmm5, [rax+8128]
vpdpwssds zmm18{k2}, zmm19, [r12+8192]
vpdpwssds zmm17{k1}{z}, zmm20, dword ptr [r13+508]{1to16}
end
