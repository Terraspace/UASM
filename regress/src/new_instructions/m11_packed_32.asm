; AVX-512 FP16: register/memory widths, masks, tuples and legal rounding/SAE.
.686p
.xmm
.model flat
option evex:1
.code
vaddph xmm1, xmm2, xmm3
vaddph xmm1{k3}{z}, xmm2, xmm3
vaddph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vaddph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vaddph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vaddph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vaddph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vaddph ymm1, ymm2, ymm3
vaddph ymm1{k3}{z}, ymm2, ymm3
vaddph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vaddph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vaddph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vaddph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vaddph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vaddph zmm1, zmm2, zmm3
vaddph zmm1{k3}{z}, zmm2, zmm3
vaddph zmm1{k3}, zmm2, zmm3, {rn-sae}
vaddph zmm1{k3}, zmm2, zmm3, {rd-sae}
vaddph zmm1{k3}, zmm2, zmm3, {ru-sae}
vaddph zmm1{k3}, zmm2, zmm3, {rz-sae}
vaddph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vaddph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vaddph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vaddph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vaddph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vdivph xmm1, xmm2, xmm3
vdivph xmm1{k3}{z}, xmm2, xmm3
vdivph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vdivph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vdivph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vdivph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vdivph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vdivph ymm1, ymm2, ymm3
vdivph ymm1{k3}{z}, ymm2, ymm3
vdivph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vdivph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vdivph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vdivph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vdivph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vdivph zmm1, zmm2, zmm3
vdivph zmm1{k3}{z}, zmm2, zmm3
vdivph zmm1{k3}, zmm2, zmm3, {rn-sae}
vdivph zmm1{k3}, zmm2, zmm3, {rd-sae}
vdivph zmm1{k3}, zmm2, zmm3, {ru-sae}
vdivph zmm1{k3}, zmm2, zmm3, {rz-sae}
vdivph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vdivph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vdivph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vdivph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vdivph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vgetexpph xmm1, xmm2
vgetexpph xmm1{k3}{z}, xmm2
vgetexpph xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vgetexpph xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vgetexpph xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vgetexpph xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vgetexpph xmm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vgetexpph ymm1, ymm2
vgetexpph ymm1{k3}{z}, ymm2
vgetexpph ymm1{k3}, ymmword ptr [ebx+esi*2+0]
vgetexpph ymm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vgetexpph ymm1{k3}, ymmword ptr [ebx+esi*2+4096]
vgetexpph ymm1{k3}, ymmword ptr [ebx+esi*2+1]
vgetexpph ymm1{k3}, word ptr [ebx+esi*2+254]{1to16}
vgetexpph zmm1, zmm2
vgetexpph zmm1{k3}{z}, zmm2
vgetexpph zmm1{k3}, zmm2, {sae}
vgetexpph zmm1{k3}, zmmword ptr [ebx+esi*2+0]
vgetexpph zmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vgetexpph zmm1{k3}, zmmword ptr [ebx+esi*2+8192]
vgetexpph zmm1{k3}, zmmword ptr [ebx+esi*2+1]
vgetexpph zmm1{k3}, word ptr [ebx+esi*2+254]{1to32}
vgetmantph xmm1, xmm2, 255
vgetmantph xmm1{k3}{z}, xmm2, 255
vgetmantph xmm1{k3}, xmmword ptr [ebx+esi*2+0], 255
vgetmantph xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032], 255
vgetmantph xmm1{k3}, xmmword ptr [ebx+esi*2+2048], 255
vgetmantph xmm1{k3}, xmmword ptr [ebx+esi*2+1], 255
vgetmantph xmm1{k3}, word ptr [ebx+esi*2+254]{1to8}, 255
vgetmantph ymm1, ymm2, 255
vgetmantph ymm1{k3}{z}, ymm2, 255
vgetmantph ymm1{k3}, ymmword ptr [ebx+esi*2+0], 255
vgetmantph ymm1{k3}{z}, ymmword ptr [ebx+esi*2+4064], 255
vgetmantph ymm1{k3}, ymmword ptr [ebx+esi*2+4096], 255
vgetmantph ymm1{k3}, ymmword ptr [ebx+esi*2+1], 255
vgetmantph ymm1{k3}, word ptr [ebx+esi*2+254]{1to16}, 255
vgetmantph zmm1, zmm2, 255
vgetmantph zmm1{k3}{z}, zmm2, 255
vgetmantph zmm1{k3}, zmm2, {sae}, 255
vgetmantph zmm1{k3}, zmmword ptr [ebx+esi*2+0], 255
vgetmantph zmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128], 255
vgetmantph zmm1{k3}, zmmword ptr [ebx+esi*2+8192], 255
vgetmantph zmm1{k3}, zmmword ptr [ebx+esi*2+1], 255
vgetmantph zmm1{k3}, word ptr [ebx+esi*2+254]{1to32}, 255
vmaxph xmm1, xmm2, xmm3
vmaxph xmm1{k3}{z}, xmm2, xmm3
vmaxph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vmaxph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vmaxph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vmaxph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vmaxph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vmaxph ymm1, ymm2, ymm3
vmaxph ymm1{k3}{z}, ymm2, ymm3
vmaxph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vmaxph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vmaxph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vmaxph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vmaxph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vmaxph zmm1, zmm2, zmm3
vmaxph zmm1{k3}{z}, zmm2, zmm3
vmaxph zmm1{k3}, zmm2, zmm3, {sae}
vmaxph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vmaxph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vmaxph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vmaxph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vmaxph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vminph xmm1, xmm2, xmm3
vminph xmm1{k3}{z}, xmm2, xmm3
vminph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vminph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vminph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vminph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vminph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vminph ymm1, ymm2, ymm3
vminph ymm1{k3}{z}, ymm2, ymm3
vminph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vminph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vminph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vminph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vminph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vminph zmm1, zmm2, zmm3
vminph zmm1{k3}{z}, zmm2, zmm3
vminph zmm1{k3}, zmm2, zmm3, {sae}
vminph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vminph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vminph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vminph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vminph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vmulph xmm1, xmm2, xmm3
vmulph xmm1{k3}{z}, xmm2, xmm3
vmulph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vmulph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vmulph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vmulph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vmulph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vmulph ymm1, ymm2, ymm3
vmulph ymm1{k3}{z}, ymm2, ymm3
vmulph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vmulph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vmulph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vmulph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vmulph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vmulph zmm1, zmm2, zmm3
vmulph zmm1{k3}{z}, zmm2, zmm3
vmulph zmm1{k3}, zmm2, zmm3, {rn-sae}
vmulph zmm1{k3}, zmm2, zmm3, {rd-sae}
vmulph zmm1{k3}, zmm2, zmm3, {ru-sae}
vmulph zmm1{k3}, zmm2, zmm3, {rz-sae}
vmulph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vmulph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vmulph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vmulph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vmulph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vrcpph xmm1, xmm2
vrcpph xmm1{k3}{z}, xmm2
vrcpph xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vrcpph xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vrcpph xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vrcpph xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vrcpph xmm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vrcpph ymm1, ymm2
vrcpph ymm1{k3}{z}, ymm2
vrcpph ymm1{k3}, ymmword ptr [ebx+esi*2+0]
vrcpph ymm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vrcpph ymm1{k3}, ymmword ptr [ebx+esi*2+4096]
vrcpph ymm1{k3}, ymmword ptr [ebx+esi*2+1]
vrcpph ymm1{k3}, word ptr [ebx+esi*2+254]{1to16}
vrcpph zmm1, zmm2
vrcpph zmm1{k3}{z}, zmm2
vrcpph zmm1{k3}, zmmword ptr [ebx+esi*2+0]
vrcpph zmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vrcpph zmm1{k3}, zmmword ptr [ebx+esi*2+8192]
vrcpph zmm1{k3}, zmmword ptr [ebx+esi*2+1]
vrcpph zmm1{k3}, word ptr [ebx+esi*2+254]{1to32}
vreduceph xmm1, xmm2, 255
vreduceph xmm1{k3}{z}, xmm2, 255
vreduceph xmm1{k3}, xmmword ptr [ebx+esi*2+0], 255
vreduceph xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032], 255
vreduceph xmm1{k3}, xmmword ptr [ebx+esi*2+2048], 255
vreduceph xmm1{k3}, xmmword ptr [ebx+esi*2+1], 255
vreduceph xmm1{k3}, word ptr [ebx+esi*2+254]{1to8}, 255
vreduceph ymm1, ymm2, 255
vreduceph ymm1{k3}{z}, ymm2, 255
vreduceph ymm1{k3}, ymmword ptr [ebx+esi*2+0], 255
vreduceph ymm1{k3}{z}, ymmword ptr [ebx+esi*2+4064], 255
vreduceph ymm1{k3}, ymmword ptr [ebx+esi*2+4096], 255
vreduceph ymm1{k3}, ymmword ptr [ebx+esi*2+1], 255
vreduceph ymm1{k3}, word ptr [ebx+esi*2+254]{1to16}, 255
vreduceph zmm1, zmm2, 255
vreduceph zmm1{k3}{z}, zmm2, 255
vreduceph zmm1{k3}, zmm2, {sae}, 255
vreduceph zmm1{k3}, zmmword ptr [ebx+esi*2+0], 255
vreduceph zmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128], 255
vreduceph zmm1{k3}, zmmword ptr [ebx+esi*2+8192], 255
vreduceph zmm1{k3}, zmmword ptr [ebx+esi*2+1], 255
vreduceph zmm1{k3}, word ptr [ebx+esi*2+254]{1to32}, 255
vrndscaleph xmm1, xmm2, 255
vrndscaleph xmm1{k3}{z}, xmm2, 255
vrndscaleph xmm1{k3}, xmmword ptr [ebx+esi*2+0], 255
vrndscaleph xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032], 255
vrndscaleph xmm1{k3}, xmmword ptr [ebx+esi*2+2048], 255
vrndscaleph xmm1{k3}, xmmword ptr [ebx+esi*2+1], 255
vrndscaleph xmm1{k3}, word ptr [ebx+esi*2+254]{1to8}, 255
vrndscaleph ymm1, ymm2, 255
vrndscaleph ymm1{k3}{z}, ymm2, 255
vrndscaleph ymm1{k3}, ymmword ptr [ebx+esi*2+0], 255
vrndscaleph ymm1{k3}{z}, ymmword ptr [ebx+esi*2+4064], 255
vrndscaleph ymm1{k3}, ymmword ptr [ebx+esi*2+4096], 255
vrndscaleph ymm1{k3}, ymmword ptr [ebx+esi*2+1], 255
vrndscaleph ymm1{k3}, word ptr [ebx+esi*2+254]{1to16}, 255
vrndscaleph zmm1, zmm2, 255
vrndscaleph zmm1{k3}{z}, zmm2, 255
vrndscaleph zmm1{k3}, zmm2, {sae}, 255
vrndscaleph zmm1{k3}, zmmword ptr [ebx+esi*2+0], 255
vrndscaleph zmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128], 255
vrndscaleph zmm1{k3}, zmmword ptr [ebx+esi*2+8192], 255
vrndscaleph zmm1{k3}, zmmword ptr [ebx+esi*2+1], 255
vrndscaleph zmm1{k3}, word ptr [ebx+esi*2+254]{1to32}, 255
vrsqrtph xmm1, xmm2
vrsqrtph xmm1{k3}{z}, xmm2
vrsqrtph xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vrsqrtph xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vrsqrtph xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vrsqrtph xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vrsqrtph xmm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vrsqrtph ymm1, ymm2
vrsqrtph ymm1{k3}{z}, ymm2
vrsqrtph ymm1{k3}, ymmword ptr [ebx+esi*2+0]
vrsqrtph ymm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vrsqrtph ymm1{k3}, ymmword ptr [ebx+esi*2+4096]
vrsqrtph ymm1{k3}, ymmword ptr [ebx+esi*2+1]
vrsqrtph ymm1{k3}, word ptr [ebx+esi*2+254]{1to16}
vrsqrtph zmm1, zmm2
vrsqrtph zmm1{k3}{z}, zmm2
vrsqrtph zmm1{k3}, zmmword ptr [ebx+esi*2+0]
vrsqrtph zmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vrsqrtph zmm1{k3}, zmmword ptr [ebx+esi*2+8192]
vrsqrtph zmm1{k3}, zmmword ptr [ebx+esi*2+1]
vrsqrtph zmm1{k3}, word ptr [ebx+esi*2+254]{1to32}
vscalefph xmm1, xmm2, xmm3
vscalefph xmm1{k3}{z}, xmm2, xmm3
vscalefph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vscalefph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vscalefph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vscalefph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vscalefph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vscalefph ymm1, ymm2, ymm3
vscalefph ymm1{k3}{z}, ymm2, ymm3
vscalefph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vscalefph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vscalefph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vscalefph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vscalefph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vscalefph zmm1, zmm2, zmm3
vscalefph zmm1{k3}{z}, zmm2, zmm3
vscalefph zmm1{k3}, zmm2, zmm3, {rn-sae}
vscalefph zmm1{k3}, zmm2, zmm3, {rd-sae}
vscalefph zmm1{k3}, zmm2, zmm3, {ru-sae}
vscalefph zmm1{k3}, zmm2, zmm3, {rz-sae}
vscalefph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vscalefph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vscalefph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vscalefph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vscalefph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
vsqrtph xmm1, xmm2
vsqrtph xmm1{k3}{z}, xmm2
vsqrtph xmm1{k3}, xmmword ptr [ebx+esi*2+0]
vsqrtph xmm1{k3}{z}, xmmword ptr [ebx+esi*2+2032]
vsqrtph xmm1{k3}, xmmword ptr [ebx+esi*2+2048]
vsqrtph xmm1{k3}, xmmword ptr [ebx+esi*2+1]
vsqrtph xmm1{k3}, word ptr [ebx+esi*2+254]{1to8}
vsqrtph ymm1, ymm2
vsqrtph ymm1{k3}{z}, ymm2
vsqrtph ymm1{k3}, ymmword ptr [ebx+esi*2+0]
vsqrtph ymm1{k3}{z}, ymmword ptr [ebx+esi*2+4064]
vsqrtph ymm1{k3}, ymmword ptr [ebx+esi*2+4096]
vsqrtph ymm1{k3}, ymmword ptr [ebx+esi*2+1]
vsqrtph ymm1{k3}, word ptr [ebx+esi*2+254]{1to16}
vsqrtph zmm1, zmm2
vsqrtph zmm1{k3}{z}, zmm2
vsqrtph zmm1{k3}, zmm2, {rn-sae}
vsqrtph zmm1{k3}, zmm2, {rd-sae}
vsqrtph zmm1{k3}, zmm2, {ru-sae}
vsqrtph zmm1{k3}, zmm2, {rz-sae}
vsqrtph zmm1{k3}, zmmword ptr [ebx+esi*2+0]
vsqrtph zmm1{k3}{z}, zmmword ptr [ebx+esi*2+8128]
vsqrtph zmm1{k3}, zmmword ptr [ebx+esi*2+8192]
vsqrtph zmm1{k3}, zmmword ptr [ebx+esi*2+1]
vsqrtph zmm1{k3}, word ptr [ebx+esi*2+254]{1to32}
vsubph xmm1, xmm2, xmm3
vsubph xmm1{k3}{z}, xmm2, xmm3
vsubph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+0]
vsubph xmm1{k3}{z}, xmm2, xmmword ptr [ebx+esi*2+2032]
vsubph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+2048]
vsubph xmm1{k3}, xmm2, xmmword ptr [ebx+esi*2+1]
vsubph xmm1{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}
vsubph ymm1, ymm2, ymm3
vsubph ymm1{k3}{z}, ymm2, ymm3
vsubph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+0]
vsubph ymm1{k3}{z}, ymm2, ymmword ptr [ebx+esi*2+4064]
vsubph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+4096]
vsubph ymm1{k3}, ymm2, ymmword ptr [ebx+esi*2+1]
vsubph ymm1{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}
vsubph zmm1, zmm2, zmm3
vsubph zmm1{k3}{z}, zmm2, zmm3
vsubph zmm1{k3}, zmm2, zmm3, {rn-sae}
vsubph zmm1{k3}, zmm2, zmm3, {rd-sae}
vsubph zmm1{k3}, zmm2, zmm3, {ru-sae}
vsubph zmm1{k3}, zmm2, zmm3, {rz-sae}
vsubph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+0]
vsubph zmm1{k3}{z}, zmm2, zmmword ptr [ebx+esi*2+8128]
vsubph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+8192]
vsubph zmm1{k3}, zmm2, zmmword ptr [ebx+esi*2+1]
vsubph zmm1{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}
end
