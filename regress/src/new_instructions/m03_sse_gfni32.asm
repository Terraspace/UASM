; M03: 32-bit addressing and SSE registers.
.686p
.xmm
.model flat
.code
gf2p8mulb xmm1, xmm7
gf2p8mulb xmm2, [ebp]
gf2p8mulb xmm3, [eax+esi*4+127]
gf2p8mulb xmm4, [ebx+128]
gf2p8affineqb xmm1, xmm7, 255
gf2p8affineqb xmm2, [ebp], 255
gf2p8affineqb xmm3, [eax+esi*4+127], 255
gf2p8affineqb xmm4, [ebx+128], 255
gf2p8affineinvqb xmm1, xmm7, 255
gf2p8affineinvqb xmm2, [ebp], 255
gf2p8affineinvqb xmm3, [eax+esi*4+127], 255
gf2p8affineinvqb xmm4, [ebx+128], 255
end
