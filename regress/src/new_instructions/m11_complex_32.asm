; AVX-512 FP16: register/memory widths, masks, tuples and legal rounding/SAE.
.686p
.xmm
.model flat
option evex:1
.code
vfcmaddcph xmm1, xmm2, xmm3
vfcmaddcph xmm1{k3}{z}, xmm2, xmm3
vfcmaddcph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfcmaddcph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfcmaddcph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfcmaddcph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfcmaddcph xmm1{k3}, xmm2, dword ptr [ebx+esi*2+508]{1to4}
vfcmaddcph ymm1, ymm2, ymm3
vfcmaddcph ymm1{k3}{z}, ymm2, ymm3
vfcmaddcph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfcmaddcph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfcmaddcph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfcmaddcph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfcmaddcph ymm1{k3}, ymm2, dword ptr [ebx+esi*2+508]{1to8}
vfcmaddcph zmm1, zmm2, zmm3
vfcmaddcph zmm1{k3}{z}, zmm2, zmm3
vfcmaddcph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfcmaddcph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfcmaddcph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfcmaddcph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfcmaddcph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfcmaddcph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfcmaddcph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfcmaddcph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfcmaddcph zmm1{k3}, zmm2, dword ptr [ebx+esi*2+508]{1to16}
vfcmaddcsh xmm1, xmm2, xmm3
vfcmaddcsh xmm1{k3}{z}, xmm2, xmm3
vfcmaddcsh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfcmaddcsh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfcmaddcsh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfcmaddcsh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfcmaddcsh xmm1{k3}, xmm2, dword ptr [ebx+esi*2+0]
vfcmaddcsh xmm1{k3}{z}, xmm2, dword ptr [ebx+esi*2+508]
vfcmaddcsh xmm1{k3}, xmm2, dword ptr [ebx+esi*2+512]
vfcmaddcsh xmm1{k3}, xmm2, dword ptr [ebx+esi*2+1]
vfcmulcph xmm1, xmm2, xmm3
vfcmulcph xmm1{k3}{z}, xmm2, xmm3
vfcmulcph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfcmulcph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfcmulcph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfcmulcph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfcmulcph xmm1{k3}, xmm2, dword ptr [ebx+esi*2+508]{1to4}
vfcmulcph ymm1, ymm2, ymm3
vfcmulcph ymm1{k3}{z}, ymm2, ymm3
vfcmulcph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfcmulcph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfcmulcph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfcmulcph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfcmulcph ymm1{k3}, ymm2, dword ptr [ebx+esi*2+508]{1to8}
vfcmulcph zmm1, zmm2, zmm3
vfcmulcph zmm1{k3}{z}, zmm2, zmm3
vfcmulcph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfcmulcph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfcmulcph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfcmulcph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfcmulcph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfcmulcph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfcmulcph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfcmulcph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfcmulcph zmm1{k3}, zmm2, dword ptr [ebx+esi*2+508]{1to16}
vfcmulcsh xmm1, xmm2, xmm3
vfcmulcsh xmm1{k3}{z}, xmm2, xmm3
vfcmulcsh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfcmulcsh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfcmulcsh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfcmulcsh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfcmulcsh xmm1{k3}, xmm2, dword ptr [ebx+esi*2+0]
vfcmulcsh xmm1{k3}{z}, xmm2, dword ptr [ebx+esi*2+508]
vfcmulcsh xmm1{k3}, xmm2, dword ptr [ebx+esi*2+512]
vfcmulcsh xmm1{k3}, xmm2, dword ptr [ebx+esi*2+1]
vfmaddcph xmm1, xmm2, xmm3
vfmaddcph xmm1{k3}{z}, xmm2, xmm3
vfmaddcph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfmaddcph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfmaddcph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfmaddcph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfmaddcph xmm1{k3}, xmm2, dword ptr [ebx+esi*2+508]{1to4}
vfmaddcph ymm1, ymm2, ymm3
vfmaddcph ymm1{k3}{z}, ymm2, ymm3
vfmaddcph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfmaddcph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfmaddcph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfmaddcph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfmaddcph ymm1{k3}, ymm2, dword ptr [ebx+esi*2+508]{1to8}
vfmaddcph zmm1, zmm2, zmm3
vfmaddcph zmm1{k3}{z}, zmm2, zmm3
vfmaddcph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfmaddcph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfmaddcph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfmaddcph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfmaddcph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfmaddcph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfmaddcph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfmaddcph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfmaddcph zmm1{k3}, zmm2, dword ptr [ebx+esi*2+508]{1to16}
vfmaddcsh xmm1, xmm2, xmm3
vfmaddcsh xmm1{k3}{z}, xmm2, xmm3
vfmaddcsh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfmaddcsh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfmaddcsh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfmaddcsh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfmaddcsh xmm1{k3}, xmm2, dword ptr [ebx+esi*2+0]
vfmaddcsh xmm1{k3}{z}, xmm2, dword ptr [ebx+esi*2+508]
vfmaddcsh xmm1{k3}, xmm2, dword ptr [ebx+esi*2+512]
vfmaddcsh xmm1{k3}, xmm2, dword ptr [ebx+esi*2+1]
vfmulcph xmm1, xmm2, xmm3
vfmulcph xmm1{k3}{z}, xmm2, xmm3
vfmulcph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vfmulcph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vfmulcph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vfmulcph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vfmulcph xmm1{k3}, xmm2, dword ptr [ebx+esi*2+508]{1to4}
vfmulcph ymm1, ymm2, ymm3
vfmulcph ymm1{k3}{z}, ymm2, ymm3
vfmulcph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vfmulcph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vfmulcph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vfmulcph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vfmulcph ymm1{k3}, ymm2, dword ptr [ebx+esi*2+508]{1to8}
vfmulcph zmm1, zmm2, zmm3
vfmulcph zmm1{k3}{z}, zmm2, zmm3
vfmulcph zmm1{k3}, zmm2, zmm3, {rn-sae}
vfmulcph zmm1{k3}, zmm2, zmm3, {rd-sae}
vfmulcph zmm1{k3}, zmm2, zmm3, {ru-sae}
vfmulcph zmm1{k3}, zmm2, zmm3, {rz-sae}
vfmulcph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vfmulcph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vfmulcph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vfmulcph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vfmulcph zmm1{k3}, zmm2, dword ptr [ebx+esi*2+508]{1to16}
vfmulcsh xmm1, xmm2, xmm3
vfmulcsh xmm1{k3}{z}, xmm2, xmm3
vfmulcsh xmm1{k3}, xmm2, xmm3, {rn-sae}
vfmulcsh xmm1{k3}, xmm2, xmm3, {rd-sae}
vfmulcsh xmm1{k3}, xmm2, xmm3, {ru-sae}
vfmulcsh xmm1{k3}, xmm2, xmm3, {rz-sae}
vfmulcsh xmm1{k3}, xmm2, dword ptr [ebx+esi*2+0]
vfmulcsh xmm1{k3}{z}, xmm2, dword ptr [ebx+esi*2+508]
vfmulcsh xmm1{k3}, xmm2, dword ptr [ebx+esi*2+512]
vfmulcsh xmm1{k3}, xmm2, dword ptr [ebx+esi*2+1]
end
