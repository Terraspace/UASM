; AVX-512 FP16: register/memory widths, masks, tuples and legal rounding/SAE.
.x64
.model flat
option evex:1
.code
vfcmaddcph xmm1, xmm2, xmm3
vfcmaddcph xmm31{k3}{z}, xmm16, xmm30
vfcmaddcph xmm31{k3}, xmm16, xmmword ptr [r13]
vfcmaddcph xmm31{k3}{z}, xmm16, xmmword ptr [r12+r14*2+2032]
vfcmaddcph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+2048]
vfcmaddcph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+1]
vfcmaddcph xmm31{k3}, xmm16, dword ptr [r12+r14*2+508]{1to4}
vfcmaddcph ymm1, ymm2, ymm3
vfcmaddcph ymm31{k3}{z}, ymm16, ymm30
vfcmaddcph ymm31{k3}, ymm16, ymmword ptr [r13]
vfcmaddcph ymm31{k3}{z}, ymm16, ymmword ptr [r12+r14*2+4064]
vfcmaddcph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+4096]
vfcmaddcph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+1]
vfcmaddcph ymm31{k3}, ymm16, dword ptr [r12+r14*2+508]{1to8}
vfcmaddcph zmm1, zmm2, zmm3
vfcmaddcph zmm31{k3}{z}, zmm16, zmm30
vfcmaddcph zmm31{k3}, zmm16, zmm30, {rn-sae}
vfcmaddcph zmm31{k3}, zmm16, zmm30, {rd-sae}
vfcmaddcph zmm31{k3}, zmm16, zmm30, {ru-sae}
vfcmaddcph zmm31{k3}, zmm16, zmm30, {rz-sae}
vfcmaddcph zmm31{k3}, zmm16, zmmword ptr [r13]
vfcmaddcph zmm31{k3}{z}, zmm16, zmmword ptr [r12+r14*2+8128]
vfcmaddcph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+8192]
vfcmaddcph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+1]
vfcmaddcph zmm31{k3}, zmm16, dword ptr [r12+r14*2+508]{1to16}
vfcmaddcsh xmm1, xmm2, xmm3
vfcmaddcsh xmm31{k3}{z}, xmm16, xmm30
vfcmaddcsh xmm31{k3}, xmm16, xmm30, {rn-sae}
vfcmaddcsh xmm31{k3}, xmm16, xmm30, {rd-sae}
vfcmaddcsh xmm31{k3}, xmm16, xmm30, {ru-sae}
vfcmaddcsh xmm31{k3}, xmm16, xmm30, {rz-sae}
vfcmaddcsh xmm31{k3}, xmm16, dword ptr [r13]
vfcmaddcsh xmm31{k3}{z}, xmm16, dword ptr [r12+r14*2+508]
vfcmaddcsh xmm31{k3}, xmm16, dword ptr [r12+r14*2+512]
vfcmaddcsh xmm31{k3}, xmm16, dword ptr [r12+r14*2+1]
vfcmulcph xmm1, xmm2, xmm3
vfcmulcph xmm31{k3}{z}, xmm16, xmm30
vfcmulcph xmm31{k3}, xmm16, xmmword ptr [r13]
vfcmulcph xmm31{k3}{z}, xmm16, xmmword ptr [r12+r14*2+2032]
vfcmulcph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+2048]
vfcmulcph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+1]
vfcmulcph xmm31{k3}, xmm16, dword ptr [r12+r14*2+508]{1to4}
vfcmulcph ymm1, ymm2, ymm3
vfcmulcph ymm31{k3}{z}, ymm16, ymm30
vfcmulcph ymm31{k3}, ymm16, ymmword ptr [r13]
vfcmulcph ymm31{k3}{z}, ymm16, ymmword ptr [r12+r14*2+4064]
vfcmulcph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+4096]
vfcmulcph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+1]
vfcmulcph ymm31{k3}, ymm16, dword ptr [r12+r14*2+508]{1to8}
vfcmulcph zmm1, zmm2, zmm3
vfcmulcph zmm31{k3}{z}, zmm16, zmm30
vfcmulcph zmm31{k3}, zmm16, zmm30, {rn-sae}
vfcmulcph zmm31{k3}, zmm16, zmm30, {rd-sae}
vfcmulcph zmm31{k3}, zmm16, zmm30, {ru-sae}
vfcmulcph zmm31{k3}, zmm16, zmm30, {rz-sae}
vfcmulcph zmm31{k3}, zmm16, zmmword ptr [r13]
vfcmulcph zmm31{k3}{z}, zmm16, zmmword ptr [r12+r14*2+8128]
vfcmulcph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+8192]
vfcmulcph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+1]
vfcmulcph zmm31{k3}, zmm16, dword ptr [r12+r14*2+508]{1to16}
vfcmulcsh xmm1, xmm2, xmm3
vfcmulcsh xmm31{k3}{z}, xmm16, xmm30
vfcmulcsh xmm31{k3}, xmm16, xmm30, {rn-sae}
vfcmulcsh xmm31{k3}, xmm16, xmm30, {rd-sae}
vfcmulcsh xmm31{k3}, xmm16, xmm30, {ru-sae}
vfcmulcsh xmm31{k3}, xmm16, xmm30, {rz-sae}
vfcmulcsh xmm31{k3}, xmm16, dword ptr [r13]
vfcmulcsh xmm31{k3}{z}, xmm16, dword ptr [r12+r14*2+508]
vfcmulcsh xmm31{k3}, xmm16, dword ptr [r12+r14*2+512]
vfcmulcsh xmm31{k3}, xmm16, dword ptr [r12+r14*2+1]
vfmaddcph xmm1, xmm2, xmm3
vfmaddcph xmm31{k3}{z}, xmm16, xmm30
vfmaddcph xmm31{k3}, xmm16, xmmword ptr [r13]
vfmaddcph xmm31{k3}{z}, xmm16, xmmword ptr [r12+r14*2+2032]
vfmaddcph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+2048]
vfmaddcph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+1]
vfmaddcph xmm31{k3}, xmm16, dword ptr [r12+r14*2+508]{1to4}
vfmaddcph ymm1, ymm2, ymm3
vfmaddcph ymm31{k3}{z}, ymm16, ymm30
vfmaddcph ymm31{k3}, ymm16, ymmword ptr [r13]
vfmaddcph ymm31{k3}{z}, ymm16, ymmword ptr [r12+r14*2+4064]
vfmaddcph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+4096]
vfmaddcph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+1]
vfmaddcph ymm31{k3}, ymm16, dword ptr [r12+r14*2+508]{1to8}
vfmaddcph zmm1, zmm2, zmm3
vfmaddcph zmm31{k3}{z}, zmm16, zmm30
vfmaddcph zmm31{k3}, zmm16, zmm30, {rn-sae}
vfmaddcph zmm31{k3}, zmm16, zmm30, {rd-sae}
vfmaddcph zmm31{k3}, zmm16, zmm30, {ru-sae}
vfmaddcph zmm31{k3}, zmm16, zmm30, {rz-sae}
vfmaddcph zmm31{k3}, zmm16, zmmword ptr [r13]
vfmaddcph zmm31{k3}{z}, zmm16, zmmword ptr [r12+r14*2+8128]
vfmaddcph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+8192]
vfmaddcph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+1]
vfmaddcph zmm31{k3}, zmm16, dword ptr [r12+r14*2+508]{1to16}
vfmaddcsh xmm1, xmm2, xmm3
vfmaddcsh xmm31{k3}{z}, xmm16, xmm30
vfmaddcsh xmm31{k3}, xmm16, xmm30, {rn-sae}
vfmaddcsh xmm31{k3}, xmm16, xmm30, {rd-sae}
vfmaddcsh xmm31{k3}, xmm16, xmm30, {ru-sae}
vfmaddcsh xmm31{k3}, xmm16, xmm30, {rz-sae}
vfmaddcsh xmm31{k3}, xmm16, dword ptr [r13]
vfmaddcsh xmm31{k3}{z}, xmm16, dword ptr [r12+r14*2+508]
vfmaddcsh xmm31{k3}, xmm16, dword ptr [r12+r14*2+512]
vfmaddcsh xmm31{k3}, xmm16, dword ptr [r12+r14*2+1]
vfmulcph xmm1, xmm2, xmm3
vfmulcph xmm31{k3}{z}, xmm16, xmm30
vfmulcph xmm31{k3}, xmm16, xmmword ptr [r13]
vfmulcph xmm31{k3}{z}, xmm16, xmmword ptr [r12+r14*2+2032]
vfmulcph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+2048]
vfmulcph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+1]
vfmulcph xmm31{k3}, xmm16, dword ptr [r12+r14*2+508]{1to4}
vfmulcph ymm1, ymm2, ymm3
vfmulcph ymm31{k3}{z}, ymm16, ymm30
vfmulcph ymm31{k3}, ymm16, ymmword ptr [r13]
vfmulcph ymm31{k3}{z}, ymm16, ymmword ptr [r12+r14*2+4064]
vfmulcph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+4096]
vfmulcph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+1]
vfmulcph ymm31{k3}, ymm16, dword ptr [r12+r14*2+508]{1to8}
vfmulcph zmm1, zmm2, zmm3
vfmulcph zmm31{k3}{z}, zmm16, zmm30
vfmulcph zmm31{k3}, zmm16, zmm30, {rn-sae}
vfmulcph zmm31{k3}, zmm16, zmm30, {rd-sae}
vfmulcph zmm31{k3}, zmm16, zmm30, {ru-sae}
vfmulcph zmm31{k3}, zmm16, zmm30, {rz-sae}
vfmulcph zmm31{k3}, zmm16, zmmword ptr [r13]
vfmulcph zmm31{k3}{z}, zmm16, zmmword ptr [r12+r14*2+8128]
vfmulcph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+8192]
vfmulcph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+1]
vfmulcph zmm31{k3}, zmm16, dword ptr [r12+r14*2+508]{1to16}
vfmulcsh xmm1, xmm2, xmm3
vfmulcsh xmm31{k3}{z}, xmm16, xmm30
vfmulcsh xmm31{k3}, xmm16, xmm30, {rn-sae}
vfmulcsh xmm31{k3}, xmm16, xmm30, {rd-sae}
vfmulcsh xmm31{k3}, xmm16, xmm30, {ru-sae}
vfmulcsh xmm31{k3}, xmm16, xmm30, {rz-sae}
vfmulcsh xmm31{k3}, xmm16, dword ptr [r13]
vfmulcsh xmm31{k3}{z}, xmm16, dword ptr [r12+r14*2+508]
vfmulcsh xmm31{k3}, xmm16, dword ptr [r12+r14*2+512]
vfmulcsh xmm31{k3}, xmm16, dword ptr [r12+r14*2+1]
end
