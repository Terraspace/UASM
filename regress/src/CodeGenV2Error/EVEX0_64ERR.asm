option flat:1
option evex:1

.code

	use64

	vmovaps myVector{z},xmm21				; Unsupported masking operator.
	vmulps zmm20{k2}{z}, zmm0, [rdi]{1to8}	; Broadcast wrong size.
	vgatherdps zmm0, [zmm1]					; vgatherdps requires mask register.
	
	{evex} vblendvps xmm1,xmm2,xmm3,xmm4    ; no evex form possible, only exists as avx2.
	vblendvps xmm21,xmm2,xmm3,xmm4    		; no evex form possible, only exists as avx2.
	{evex} vmpsadbw xmm0, xmm2, 1			; no evex forms possible.
	vmpsadbw xmm21, xmm2, 2					; ""
