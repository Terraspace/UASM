; AVX-512 FP16: register/memory widths, masks, tuples and legal rounding/SAE.
.686p
.xmm
.model flat
option evex:1
.code
vaddsh xmm1, xmm2, xmm3
vaddsh xmm1{k3}{z}, xmm2, xmm3
vaddsh xmm1{k3}, xmm2, xmm3, {rn-sae}
vaddsh xmm1{k3}, xmm2, xmm3, {rd-sae}
vaddsh xmm1{k3}, xmm2, xmm3, {ru-sae}
vaddsh xmm1{k3}, xmm2, xmm3, {rz-sae}
vaddsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vaddsh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vaddsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vaddsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vdivsh xmm1, xmm2, xmm3
vdivsh xmm1{k3}{z}, xmm2, xmm3
vdivsh xmm1{k3}, xmm2, xmm3, {rn-sae}
vdivsh xmm1{k3}, xmm2, xmm3, {rd-sae}
vdivsh xmm1{k3}, xmm2, xmm3, {ru-sae}
vdivsh xmm1{k3}, xmm2, xmm3, {rz-sae}
vdivsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vdivsh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vdivsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vdivsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vgetexpsh xmm1, xmm2, xmm3
vgetexpsh xmm1{k3}{z}, xmm2, xmm3
vgetexpsh xmm1{k3}, xmm2, xmm3, {sae}
vgetexpsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vgetexpsh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vgetexpsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vgetexpsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vgetmantsh xmm1, xmm2, xmm3, 255
vgetmantsh xmm1{k3}{z}, xmm2, xmm3, 255
vgetmantsh xmm1{k3}, xmm2, xmm3, {sae}, 255
vgetmantsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0], 255
vgetmantsh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254], 255
vgetmantsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256], 255
vgetmantsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1], 255
vmaxsh xmm1, xmm2, xmm3
vmaxsh xmm1{k3}{z}, xmm2, xmm3
vmaxsh xmm1{k3}, xmm2, xmm3, {sae}
vmaxsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vmaxsh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vmaxsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vmaxsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vminsh xmm1, xmm2, xmm3
vminsh xmm1{k3}{z}, xmm2, xmm3
vminsh xmm1{k3}, xmm2, xmm3, {sae}
vminsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vminsh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vminsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vminsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vmulsh xmm1, xmm2, xmm3
vmulsh xmm1{k3}{z}, xmm2, xmm3
vmulsh xmm1{k3}, xmm2, xmm3, {rn-sae}
vmulsh xmm1{k3}, xmm2, xmm3, {rd-sae}
vmulsh xmm1{k3}, xmm2, xmm3, {ru-sae}
vmulsh xmm1{k3}, xmm2, xmm3, {rz-sae}
vmulsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vmulsh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vmulsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vmulsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vrcpsh xmm1, xmm2, xmm3
vrcpsh xmm1{k3}{z}, xmm2, xmm3
vrcpsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vrcpsh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vrcpsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vrcpsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vreducesh xmm1, xmm2, xmm3, 255
vreducesh xmm1{k3}{z}, xmm2, xmm3, 255
vreducesh xmm1{k3}, xmm2, xmm3, {sae}, 255
vreducesh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0], 255
vreducesh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254], 255
vreducesh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256], 255
vreducesh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1], 255
vrndscalesh xmm1, xmm2, xmm3, 255
vrndscalesh xmm1{k3}{z}, xmm2, xmm3, 255
vrndscalesh xmm1{k3}, xmm2, xmm3, {sae}, 255
vrndscalesh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0], 255
vrndscalesh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254], 255
vrndscalesh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256], 255
vrndscalesh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1], 255
vrsqrtsh xmm1, xmm2, xmm3
vrsqrtsh xmm1{k3}{z}, xmm2, xmm3
vrsqrtsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vrsqrtsh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vrsqrtsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vrsqrtsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vscalefsh xmm1, xmm2, xmm3
vscalefsh xmm1{k3}{z}, xmm2, xmm3
vscalefsh xmm1{k3}, xmm2, xmm3, {rn-sae}
vscalefsh xmm1{k3}, xmm2, xmm3, {rd-sae}
vscalefsh xmm1{k3}, xmm2, xmm3, {ru-sae}
vscalefsh xmm1{k3}, xmm2, xmm3, {rz-sae}
vscalefsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vscalefsh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vscalefsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vscalefsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vsqrtsh xmm1, xmm2, xmm3
vsqrtsh xmm1{k3}{z}, xmm2, xmm3
vsqrtsh xmm1{k3}, xmm2, xmm3, {rn-sae}
vsqrtsh xmm1{k3}, xmm2, xmm3, {rd-sae}
vsqrtsh xmm1{k3}, xmm2, xmm3, {ru-sae}
vsqrtsh xmm1{k3}, xmm2, xmm3, {rz-sae}
vsqrtsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vsqrtsh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vsqrtsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vsqrtsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
vsubsh xmm1, xmm2, xmm3
vsubsh xmm1{k3}{z}, xmm2, xmm3
vsubsh xmm1{k3}, xmm2, xmm3, {rn-sae}
vsubsh xmm1{k3}, xmm2, xmm3, {rd-sae}
vsubsh xmm1{k3}, xmm2, xmm3, {ru-sae}
vsubsh xmm1{k3}, xmm2, xmm3, {rz-sae}
vsubsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+0]
vsubsh xmm1{k3}{z}, xmm2, word ptr [ebx+esi*2+254]
vsubsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+256]
vsubsh xmm1{k3}, xmm2, word ptr [ebx+esi*2+1]
end
