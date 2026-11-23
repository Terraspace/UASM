; AVX-512 FP16: register/memory widths, masks, tuples and legal rounding/SAE.
.x64
.model flat
option evex:1
.code
vaddsh xmm1, xmm2, xmm3
vaddsh xmm31{k3}{z}, xmm16, xmm30
vaddsh xmm31{k3}, xmm16, xmm30, {rn-sae}
vaddsh xmm31{k3}, xmm16, xmm30, {rd-sae}
vaddsh xmm31{k3}, xmm16, xmm30, {ru-sae}
vaddsh xmm31{k3}, xmm16, xmm30, {rz-sae}
vaddsh xmm31{k3}, xmm16, word ptr [r13]
vaddsh xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254]
vaddsh xmm31{k3}, xmm16, word ptr [r12+r14*2+256]
vaddsh xmm31{k3}, xmm16, word ptr [r12+r14*2+1]
vdivsh xmm1, xmm2, xmm3
vdivsh xmm31{k3}{z}, xmm16, xmm30
vdivsh xmm31{k3}, xmm16, xmm30, {rn-sae}
vdivsh xmm31{k3}, xmm16, xmm30, {rd-sae}
vdivsh xmm31{k3}, xmm16, xmm30, {ru-sae}
vdivsh xmm31{k3}, xmm16, xmm30, {rz-sae}
vdivsh xmm31{k3}, xmm16, word ptr [r13]
vdivsh xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254]
vdivsh xmm31{k3}, xmm16, word ptr [r12+r14*2+256]
vdivsh xmm31{k3}, xmm16, word ptr [r12+r14*2+1]
vgetexpsh xmm1, xmm2, xmm3
vgetexpsh xmm31{k3}{z}, xmm16, xmm30
vgetexpsh xmm31{k3}, xmm16, xmm30, {sae}
vgetexpsh xmm31{k3}, xmm16, word ptr [r13]
vgetexpsh xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254]
vgetexpsh xmm31{k3}, xmm16, word ptr [r12+r14*2+256]
vgetexpsh xmm31{k3}, xmm16, word ptr [r12+r14*2+1]
vgetmantsh xmm1, xmm2, xmm3, 255
vgetmantsh xmm31{k3}{z}, xmm16, xmm30, 255
vgetmantsh xmm31{k3}, xmm16, xmm30, {sae}, 255
vgetmantsh xmm31{k3}, xmm16, word ptr [r13], 255
vgetmantsh xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254], 255
vgetmantsh xmm31{k3}, xmm16, word ptr [r12+r14*2+256], 255
vgetmantsh xmm31{k3}, xmm16, word ptr [r12+r14*2+1], 255
vmaxsh xmm1, xmm2, xmm3
vmaxsh xmm31{k3}{z}, xmm16, xmm30
vmaxsh xmm31{k3}, xmm16, xmm30, {sae}
vmaxsh xmm31{k3}, xmm16, word ptr [r13]
vmaxsh xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254]
vmaxsh xmm31{k3}, xmm16, word ptr [r12+r14*2+256]
vmaxsh xmm31{k3}, xmm16, word ptr [r12+r14*2+1]
vminsh xmm1, xmm2, xmm3
vminsh xmm31{k3}{z}, xmm16, xmm30
vminsh xmm31{k3}, xmm16, xmm30, {sae}
vminsh xmm31{k3}, xmm16, word ptr [r13]
vminsh xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254]
vminsh xmm31{k3}, xmm16, word ptr [r12+r14*2+256]
vminsh xmm31{k3}, xmm16, word ptr [r12+r14*2+1]
vmulsh xmm1, xmm2, xmm3
vmulsh xmm31{k3}{z}, xmm16, xmm30
vmulsh xmm31{k3}, xmm16, xmm30, {rn-sae}
vmulsh xmm31{k3}, xmm16, xmm30, {rd-sae}
vmulsh xmm31{k3}, xmm16, xmm30, {ru-sae}
vmulsh xmm31{k3}, xmm16, xmm30, {rz-sae}
vmulsh xmm31{k3}, xmm16, word ptr [r13]
vmulsh xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254]
vmulsh xmm31{k3}, xmm16, word ptr [r12+r14*2+256]
vmulsh xmm31{k3}, xmm16, word ptr [r12+r14*2+1]
vrcpsh xmm1, xmm2, xmm3
vrcpsh xmm31{k3}{z}, xmm16, xmm30
vrcpsh xmm31{k3}, xmm16, word ptr [r13]
vrcpsh xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254]
vrcpsh xmm31{k3}, xmm16, word ptr [r12+r14*2+256]
vrcpsh xmm31{k3}, xmm16, word ptr [r12+r14*2+1]
vreducesh xmm1, xmm2, xmm3, 255
vreducesh xmm31{k3}{z}, xmm16, xmm30, 255
vreducesh xmm31{k3}, xmm16, xmm30, {sae}, 255
vreducesh xmm31{k3}, xmm16, word ptr [r13], 255
vreducesh xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254], 255
vreducesh xmm31{k3}, xmm16, word ptr [r12+r14*2+256], 255
vreducesh xmm31{k3}, xmm16, word ptr [r12+r14*2+1], 255
vrndscalesh xmm1, xmm2, xmm3, 255
vrndscalesh xmm31{k3}{z}, xmm16, xmm30, 255
vrndscalesh xmm31{k3}, xmm16, xmm30, {sae}, 255
vrndscalesh xmm31{k3}, xmm16, word ptr [r13], 255
vrndscalesh xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254], 255
vrndscalesh xmm31{k3}, xmm16, word ptr [r12+r14*2+256], 255
vrndscalesh xmm31{k3}, xmm16, word ptr [r12+r14*2+1], 255
vrsqrtsh xmm1, xmm2, xmm3
vrsqrtsh xmm31{k3}{z}, xmm16, xmm30
vrsqrtsh xmm31{k3}, xmm16, word ptr [r13]
vrsqrtsh xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254]
vrsqrtsh xmm31{k3}, xmm16, word ptr [r12+r14*2+256]
vrsqrtsh xmm31{k3}, xmm16, word ptr [r12+r14*2+1]
vscalefsh xmm1, xmm2, xmm3
vscalefsh xmm31{k3}{z}, xmm16, xmm30
vscalefsh xmm31{k3}, xmm16, xmm30, {rn-sae}
vscalefsh xmm31{k3}, xmm16, xmm30, {rd-sae}
vscalefsh xmm31{k3}, xmm16, xmm30, {ru-sae}
vscalefsh xmm31{k3}, xmm16, xmm30, {rz-sae}
vscalefsh xmm31{k3}, xmm16, word ptr [r13]
vscalefsh xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254]
vscalefsh xmm31{k3}, xmm16, word ptr [r12+r14*2+256]
vscalefsh xmm31{k3}, xmm16, word ptr [r12+r14*2+1]
vsqrtsh xmm1, xmm2, xmm3
vsqrtsh xmm31{k3}{z}, xmm16, xmm30
vsqrtsh xmm31{k3}, xmm16, xmm30, {rn-sae}
vsqrtsh xmm31{k3}, xmm16, xmm30, {rd-sae}
vsqrtsh xmm31{k3}, xmm16, xmm30, {ru-sae}
vsqrtsh xmm31{k3}, xmm16, xmm30, {rz-sae}
vsqrtsh xmm31{k3}, xmm16, word ptr [r13]
vsqrtsh xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254]
vsqrtsh xmm31{k3}, xmm16, word ptr [r12+r14*2+256]
vsqrtsh xmm31{k3}, xmm16, word ptr [r12+r14*2+1]
vsubsh xmm1, xmm2, xmm3
vsubsh xmm31{k3}{z}, xmm16, xmm30
vsubsh xmm31{k3}, xmm16, xmm30, {rn-sae}
vsubsh xmm31{k3}, xmm16, xmm30, {rd-sae}
vsubsh xmm31{k3}, xmm16, xmm30, {ru-sae}
vsubsh xmm31{k3}, xmm16, xmm30, {rz-sae}
vsubsh xmm31{k3}, xmm16, word ptr [r13]
vsubsh xmm31{k3}{z}, xmm16, word ptr [r12+r14*2+254]
vsubsh xmm31{k3}, xmm16, word ptr [r12+r14*2+256]
vsubsh xmm31{k3}, xmm16, word ptr [r12+r14*2+1]
end
