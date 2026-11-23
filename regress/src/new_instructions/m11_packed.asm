; AVX-512 FP16: register/memory widths, masks, tuples and legal rounding/SAE.
.x64
.model flat
option evex:1
.code
vaddph xmm1, xmm2, xmm3
vaddph xmm31{k3}{z}, xmm16, xmm30
vaddph xmm31{k3}, xmm16, xmmword ptr [r13]
vaddph xmm31{k3}{z}, xmm16, xmmword ptr [r12+r14*2+2032]
vaddph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+2048]
vaddph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+1]
vaddph xmm31{k3}, xmm16, word ptr [r12+r14*2+254]{1to8}
vaddph ymm1, ymm2, ymm3
vaddph ymm31{k3}{z}, ymm16, ymm30
vaddph ymm31{k3}, ymm16, ymmword ptr [r13]
vaddph ymm31{k3}{z}, ymm16, ymmword ptr [r12+r14*2+4064]
vaddph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+4096]
vaddph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+1]
vaddph ymm31{k3}, ymm16, word ptr [r12+r14*2+254]{1to16}
vaddph zmm1, zmm2, zmm3
vaddph zmm31{k3}{z}, zmm16, zmm30
vaddph zmm31{k3}, zmm16, zmm30, {rn-sae}
vaddph zmm31{k3}, zmm16, zmm30, {rd-sae}
vaddph zmm31{k3}, zmm16, zmm30, {ru-sae}
vaddph zmm31{k3}, zmm16, zmm30, {rz-sae}
vaddph zmm31{k3}, zmm16, zmmword ptr [r13]
vaddph zmm31{k3}{z}, zmm16, zmmword ptr [r12+r14*2+8128]
vaddph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+8192]
vaddph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+1]
vaddph zmm31{k3}, zmm16, word ptr [r12+r14*2+254]{1to32}
vdivph xmm1, xmm2, xmm3
vdivph xmm31{k3}{z}, xmm16, xmm30
vdivph xmm31{k3}, xmm16, xmmword ptr [r13]
vdivph xmm31{k3}{z}, xmm16, xmmword ptr [r12+r14*2+2032]
vdivph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+2048]
vdivph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+1]
vdivph xmm31{k3}, xmm16, word ptr [r12+r14*2+254]{1to8}
vdivph ymm1, ymm2, ymm3
vdivph ymm31{k3}{z}, ymm16, ymm30
vdivph ymm31{k3}, ymm16, ymmword ptr [r13]
vdivph ymm31{k3}{z}, ymm16, ymmword ptr [r12+r14*2+4064]
vdivph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+4096]
vdivph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+1]
vdivph ymm31{k3}, ymm16, word ptr [r12+r14*2+254]{1to16}
vdivph zmm1, zmm2, zmm3
vdivph zmm31{k3}{z}, zmm16, zmm30
vdivph zmm31{k3}, zmm16, zmm30, {rn-sae}
vdivph zmm31{k3}, zmm16, zmm30, {rd-sae}
vdivph zmm31{k3}, zmm16, zmm30, {ru-sae}
vdivph zmm31{k3}, zmm16, zmm30, {rz-sae}
vdivph zmm31{k3}, zmm16, zmmword ptr [r13]
vdivph zmm31{k3}{z}, zmm16, zmmword ptr [r12+r14*2+8128]
vdivph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+8192]
vdivph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+1]
vdivph zmm31{k3}, zmm16, word ptr [r12+r14*2+254]{1to32}
vgetexpph xmm1, xmm2
vgetexpph xmm31{k3}{z}, xmm16
vgetexpph xmm31{k3}, xmmword ptr [r13]
vgetexpph xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vgetexpph xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vgetexpph xmm31{k3}, xmmword ptr [r12+r14*2+1]
vgetexpph xmm31{k3}, word ptr [r12+r14*2+254]{1to8}
vgetexpph ymm1, ymm2
vgetexpph ymm31{k3}{z}, ymm16
vgetexpph ymm31{k3}, ymmword ptr [r13]
vgetexpph ymm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vgetexpph ymm31{k3}, ymmword ptr [r12+r14*2+4096]
vgetexpph ymm31{k3}, ymmword ptr [r12+r14*2+1]
vgetexpph ymm31{k3}, word ptr [r12+r14*2+254]{1to16}
vgetexpph zmm1, zmm2
vgetexpph zmm31{k3}{z}, zmm16
vgetexpph zmm31{k3}, zmm16, {sae}
vgetexpph zmm31{k3}, zmmword ptr [r13]
vgetexpph zmm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vgetexpph zmm31{k3}, zmmword ptr [r12+r14*2+8192]
vgetexpph zmm31{k3}, zmmword ptr [r12+r14*2+1]
vgetexpph zmm31{k3}, word ptr [r12+r14*2+254]{1to32}
vgetmantph xmm1, xmm2, 255
vgetmantph xmm31{k3}{z}, xmm16, 255
vgetmantph xmm31{k3}, xmmword ptr [r13], 255
vgetmantph xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032], 255
vgetmantph xmm31{k3}, xmmword ptr [r12+r14*2+2048], 255
vgetmantph xmm31{k3}, xmmword ptr [r12+r14*2+1], 255
vgetmantph xmm31{k3}, word ptr [r12+r14*2+254]{1to8}, 255
vgetmantph ymm1, ymm2, 255
vgetmantph ymm31{k3}{z}, ymm16, 255
vgetmantph ymm31{k3}, ymmword ptr [r13], 255
vgetmantph ymm31{k3}{z}, ymmword ptr [r12+r14*2+4064], 255
vgetmantph ymm31{k3}, ymmword ptr [r12+r14*2+4096], 255
vgetmantph ymm31{k3}, ymmword ptr [r12+r14*2+1], 255
vgetmantph ymm31{k3}, word ptr [r12+r14*2+254]{1to16}, 255
vgetmantph zmm1, zmm2, 255
vgetmantph zmm31{k3}{z}, zmm16, 255
vgetmantph zmm31{k3}, zmm16, {sae}, 255
vgetmantph zmm31{k3}, zmmword ptr [r13], 255
vgetmantph zmm31{k3}{z}, zmmword ptr [r12+r14*2+8128], 255
vgetmantph zmm31{k3}, zmmword ptr [r12+r14*2+8192], 255
vgetmantph zmm31{k3}, zmmword ptr [r12+r14*2+1], 255
vgetmantph zmm31{k3}, word ptr [r12+r14*2+254]{1to32}, 255
vmaxph xmm1, xmm2, xmm3
vmaxph xmm31{k3}{z}, xmm16, xmm30
vmaxph xmm31{k3}, xmm16, xmmword ptr [r13]
vmaxph xmm31{k3}{z}, xmm16, xmmword ptr [r12+r14*2+2032]
vmaxph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+2048]
vmaxph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+1]
vmaxph xmm31{k3}, xmm16, word ptr [r12+r14*2+254]{1to8}
vmaxph ymm1, ymm2, ymm3
vmaxph ymm31{k3}{z}, ymm16, ymm30
vmaxph ymm31{k3}, ymm16, ymmword ptr [r13]
vmaxph ymm31{k3}{z}, ymm16, ymmword ptr [r12+r14*2+4064]
vmaxph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+4096]
vmaxph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+1]
vmaxph ymm31{k3}, ymm16, word ptr [r12+r14*2+254]{1to16}
vmaxph zmm1, zmm2, zmm3
vmaxph zmm31{k3}{z}, zmm16, zmm30
vmaxph zmm31{k3}, zmm16, zmm30, {sae}
vmaxph zmm31{k3}, zmm16, zmmword ptr [r13]
vmaxph zmm31{k3}{z}, zmm16, zmmword ptr [r12+r14*2+8128]
vmaxph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+8192]
vmaxph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+1]
vmaxph zmm31{k3}, zmm16, word ptr [r12+r14*2+254]{1to32}
vminph xmm1, xmm2, xmm3
vminph xmm31{k3}{z}, xmm16, xmm30
vminph xmm31{k3}, xmm16, xmmword ptr [r13]
vminph xmm31{k3}{z}, xmm16, xmmword ptr [r12+r14*2+2032]
vminph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+2048]
vminph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+1]
vminph xmm31{k3}, xmm16, word ptr [r12+r14*2+254]{1to8}
vminph ymm1, ymm2, ymm3
vminph ymm31{k3}{z}, ymm16, ymm30
vminph ymm31{k3}, ymm16, ymmword ptr [r13]
vminph ymm31{k3}{z}, ymm16, ymmword ptr [r12+r14*2+4064]
vminph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+4096]
vminph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+1]
vminph ymm31{k3}, ymm16, word ptr [r12+r14*2+254]{1to16}
vminph zmm1, zmm2, zmm3
vminph zmm31{k3}{z}, zmm16, zmm30
vminph zmm31{k3}, zmm16, zmm30, {sae}
vminph zmm31{k3}, zmm16, zmmword ptr [r13]
vminph zmm31{k3}{z}, zmm16, zmmword ptr [r12+r14*2+8128]
vminph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+8192]
vminph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+1]
vminph zmm31{k3}, zmm16, word ptr [r12+r14*2+254]{1to32}
vmulph xmm1, xmm2, xmm3
vmulph xmm31{k3}{z}, xmm16, xmm30
vmulph xmm31{k3}, xmm16, xmmword ptr [r13]
vmulph xmm31{k3}{z}, xmm16, xmmword ptr [r12+r14*2+2032]
vmulph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+2048]
vmulph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+1]
vmulph xmm31{k3}, xmm16, word ptr [r12+r14*2+254]{1to8}
vmulph ymm1, ymm2, ymm3
vmulph ymm31{k3}{z}, ymm16, ymm30
vmulph ymm31{k3}, ymm16, ymmword ptr [r13]
vmulph ymm31{k3}{z}, ymm16, ymmword ptr [r12+r14*2+4064]
vmulph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+4096]
vmulph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+1]
vmulph ymm31{k3}, ymm16, word ptr [r12+r14*2+254]{1to16}
vmulph zmm1, zmm2, zmm3
vmulph zmm31{k3}{z}, zmm16, zmm30
vmulph zmm31{k3}, zmm16, zmm30, {rn-sae}
vmulph zmm31{k3}, zmm16, zmm30, {rd-sae}
vmulph zmm31{k3}, zmm16, zmm30, {ru-sae}
vmulph zmm31{k3}, zmm16, zmm30, {rz-sae}
vmulph zmm31{k3}, zmm16, zmmword ptr [r13]
vmulph zmm31{k3}{z}, zmm16, zmmword ptr [r12+r14*2+8128]
vmulph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+8192]
vmulph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+1]
vmulph zmm31{k3}, zmm16, word ptr [r12+r14*2+254]{1to32}
vrcpph xmm1, xmm2
vrcpph xmm31{k3}{z}, xmm16
vrcpph xmm31{k3}, xmmword ptr [r13]
vrcpph xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vrcpph xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vrcpph xmm31{k3}, xmmword ptr [r12+r14*2+1]
vrcpph xmm31{k3}, word ptr [r12+r14*2+254]{1to8}
vrcpph ymm1, ymm2
vrcpph ymm31{k3}{z}, ymm16
vrcpph ymm31{k3}, ymmword ptr [r13]
vrcpph ymm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vrcpph ymm31{k3}, ymmword ptr [r12+r14*2+4096]
vrcpph ymm31{k3}, ymmword ptr [r12+r14*2+1]
vrcpph ymm31{k3}, word ptr [r12+r14*2+254]{1to16}
vrcpph zmm1, zmm2
vrcpph zmm31{k3}{z}, zmm16
vrcpph zmm31{k3}, zmmword ptr [r13]
vrcpph zmm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vrcpph zmm31{k3}, zmmword ptr [r12+r14*2+8192]
vrcpph zmm31{k3}, zmmword ptr [r12+r14*2+1]
vrcpph zmm31{k3}, word ptr [r12+r14*2+254]{1to32}
vreduceph xmm1, xmm2, 255
vreduceph xmm31{k3}{z}, xmm16, 255
vreduceph xmm31{k3}, xmmword ptr [r13], 255
vreduceph xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032], 255
vreduceph xmm31{k3}, xmmword ptr [r12+r14*2+2048], 255
vreduceph xmm31{k3}, xmmword ptr [r12+r14*2+1], 255
vreduceph xmm31{k3}, word ptr [r12+r14*2+254]{1to8}, 255
vreduceph ymm1, ymm2, 255
vreduceph ymm31{k3}{z}, ymm16, 255
vreduceph ymm31{k3}, ymmword ptr [r13], 255
vreduceph ymm31{k3}{z}, ymmword ptr [r12+r14*2+4064], 255
vreduceph ymm31{k3}, ymmword ptr [r12+r14*2+4096], 255
vreduceph ymm31{k3}, ymmword ptr [r12+r14*2+1], 255
vreduceph ymm31{k3}, word ptr [r12+r14*2+254]{1to16}, 255
vreduceph zmm1, zmm2, 255
vreduceph zmm31{k3}{z}, zmm16, 255
vreduceph zmm31{k3}, zmm16, {sae}, 255
vreduceph zmm31{k3}, zmmword ptr [r13], 255
vreduceph zmm31{k3}{z}, zmmword ptr [r12+r14*2+8128], 255
vreduceph zmm31{k3}, zmmword ptr [r12+r14*2+8192], 255
vreduceph zmm31{k3}, zmmword ptr [r12+r14*2+1], 255
vreduceph zmm31{k3}, word ptr [r12+r14*2+254]{1to32}, 255
vrndscaleph xmm1, xmm2, 255
vrndscaleph xmm31{k3}{z}, xmm16, 255
vrndscaleph xmm31{k3}, xmmword ptr [r13], 255
vrndscaleph xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032], 255
vrndscaleph xmm31{k3}, xmmword ptr [r12+r14*2+2048], 255
vrndscaleph xmm31{k3}, xmmword ptr [r12+r14*2+1], 255
vrndscaleph xmm31{k3}, word ptr [r12+r14*2+254]{1to8}, 255
vrndscaleph ymm1, ymm2, 255
vrndscaleph ymm31{k3}{z}, ymm16, 255
vrndscaleph ymm31{k3}, ymmword ptr [r13], 255
vrndscaleph ymm31{k3}{z}, ymmword ptr [r12+r14*2+4064], 255
vrndscaleph ymm31{k3}, ymmword ptr [r12+r14*2+4096], 255
vrndscaleph ymm31{k3}, ymmword ptr [r12+r14*2+1], 255
vrndscaleph ymm31{k3}, word ptr [r12+r14*2+254]{1to16}, 255
vrndscaleph zmm1, zmm2, 255
vrndscaleph zmm31{k3}{z}, zmm16, 255
vrndscaleph zmm31{k3}, zmm16, {sae}, 255
vrndscaleph zmm31{k3}, zmmword ptr [r13], 255
vrndscaleph zmm31{k3}{z}, zmmword ptr [r12+r14*2+8128], 255
vrndscaleph zmm31{k3}, zmmword ptr [r12+r14*2+8192], 255
vrndscaleph zmm31{k3}, zmmword ptr [r12+r14*2+1], 255
vrndscaleph zmm31{k3}, word ptr [r12+r14*2+254]{1to32}, 255
vrsqrtph xmm1, xmm2
vrsqrtph xmm31{k3}{z}, xmm16
vrsqrtph xmm31{k3}, xmmword ptr [r13]
vrsqrtph xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vrsqrtph xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vrsqrtph xmm31{k3}, xmmword ptr [r12+r14*2+1]
vrsqrtph xmm31{k3}, word ptr [r12+r14*2+254]{1to8}
vrsqrtph ymm1, ymm2
vrsqrtph ymm31{k3}{z}, ymm16
vrsqrtph ymm31{k3}, ymmword ptr [r13]
vrsqrtph ymm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vrsqrtph ymm31{k3}, ymmword ptr [r12+r14*2+4096]
vrsqrtph ymm31{k3}, ymmword ptr [r12+r14*2+1]
vrsqrtph ymm31{k3}, word ptr [r12+r14*2+254]{1to16}
vrsqrtph zmm1, zmm2
vrsqrtph zmm31{k3}{z}, zmm16
vrsqrtph zmm31{k3}, zmmword ptr [r13]
vrsqrtph zmm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vrsqrtph zmm31{k3}, zmmword ptr [r12+r14*2+8192]
vrsqrtph zmm31{k3}, zmmword ptr [r12+r14*2+1]
vrsqrtph zmm31{k3}, word ptr [r12+r14*2+254]{1to32}
vscalefph xmm1, xmm2, xmm3
vscalefph xmm31{k3}{z}, xmm16, xmm30
vscalefph xmm31{k3}, xmm16, xmmword ptr [r13]
vscalefph xmm31{k3}{z}, xmm16, xmmword ptr [r12+r14*2+2032]
vscalefph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+2048]
vscalefph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+1]
vscalefph xmm31{k3}, xmm16, word ptr [r12+r14*2+254]{1to8}
vscalefph ymm1, ymm2, ymm3
vscalefph ymm31{k3}{z}, ymm16, ymm30
vscalefph ymm31{k3}, ymm16, ymmword ptr [r13]
vscalefph ymm31{k3}{z}, ymm16, ymmword ptr [r12+r14*2+4064]
vscalefph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+4096]
vscalefph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+1]
vscalefph ymm31{k3}, ymm16, word ptr [r12+r14*2+254]{1to16}
vscalefph zmm1, zmm2, zmm3
vscalefph zmm31{k3}{z}, zmm16, zmm30
vscalefph zmm31{k3}, zmm16, zmm30, {rn-sae}
vscalefph zmm31{k3}, zmm16, zmm30, {rd-sae}
vscalefph zmm31{k3}, zmm16, zmm30, {ru-sae}
vscalefph zmm31{k3}, zmm16, zmm30, {rz-sae}
vscalefph zmm31{k3}, zmm16, zmmword ptr [r13]
vscalefph zmm31{k3}{z}, zmm16, zmmword ptr [r12+r14*2+8128]
vscalefph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+8192]
vscalefph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+1]
vscalefph zmm31{k3}, zmm16, word ptr [r12+r14*2+254]{1to32}
vsqrtph xmm1, xmm2
vsqrtph xmm31{k3}{z}, xmm16
vsqrtph xmm31{k3}, xmmword ptr [r13]
vsqrtph xmm31{k3}{z}, xmmword ptr [r12+r14*2+2032]
vsqrtph xmm31{k3}, xmmword ptr [r12+r14*2+2048]
vsqrtph xmm31{k3}, xmmword ptr [r12+r14*2+1]
vsqrtph xmm31{k3}, word ptr [r12+r14*2+254]{1to8}
vsqrtph ymm1, ymm2
vsqrtph ymm31{k3}{z}, ymm16
vsqrtph ymm31{k3}, ymmword ptr [r13]
vsqrtph ymm31{k3}{z}, ymmword ptr [r12+r14*2+4064]
vsqrtph ymm31{k3}, ymmword ptr [r12+r14*2+4096]
vsqrtph ymm31{k3}, ymmword ptr [r12+r14*2+1]
vsqrtph ymm31{k3}, word ptr [r12+r14*2+254]{1to16}
vsqrtph zmm1, zmm2
vsqrtph zmm31{k3}{z}, zmm16
vsqrtph zmm31{k3}, zmm16, {rn-sae}
vsqrtph zmm31{k3}, zmm16, {rd-sae}
vsqrtph zmm31{k3}, zmm16, {ru-sae}
vsqrtph zmm31{k3}, zmm16, {rz-sae}
vsqrtph zmm31{k3}, zmmword ptr [r13]
vsqrtph zmm31{k3}{z}, zmmword ptr [r12+r14*2+8128]
vsqrtph zmm31{k3}, zmmword ptr [r12+r14*2+8192]
vsqrtph zmm31{k3}, zmmword ptr [r12+r14*2+1]
vsqrtph zmm31{k3}, word ptr [r12+r14*2+254]{1to32}
vsubph xmm1, xmm2, xmm3
vsubph xmm31{k3}{z}, xmm16, xmm30
vsubph xmm31{k3}, xmm16, xmmword ptr [r13]
vsubph xmm31{k3}{z}, xmm16, xmmword ptr [r12+r14*2+2032]
vsubph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+2048]
vsubph xmm31{k3}, xmm16, xmmword ptr [r12+r14*2+1]
vsubph xmm31{k3}, xmm16, word ptr [r12+r14*2+254]{1to8}
vsubph ymm1, ymm2, ymm3
vsubph ymm31{k3}{z}, ymm16, ymm30
vsubph ymm31{k3}, ymm16, ymmword ptr [r13]
vsubph ymm31{k3}{z}, ymm16, ymmword ptr [r12+r14*2+4064]
vsubph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+4096]
vsubph ymm31{k3}, ymm16, ymmword ptr [r12+r14*2+1]
vsubph ymm31{k3}, ymm16, word ptr [r12+r14*2+254]{1to16}
vsubph zmm1, zmm2, zmm3
vsubph zmm31{k3}{z}, zmm16, zmm30
vsubph zmm31{k3}, zmm16, zmm30, {rn-sae}
vsubph zmm31{k3}, zmm16, zmm30, {rd-sae}
vsubph zmm31{k3}, zmm16, zmm30, {ru-sae}
vsubph zmm31{k3}, zmm16, zmm30, {rz-sae}
vsubph zmm31{k3}, zmm16, zmmword ptr [r13]
vsubph zmm31{k3}{z}, zmm16, zmmword ptr [r12+r14*2+8128]
vsubph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+8192]
vsubph zmm31{k3}, zmm16, zmmword ptr [r12+r14*2+1]
vsubph zmm31{k3}, zmm16, word ptr [r12+r14*2+254]{1to32}
end
