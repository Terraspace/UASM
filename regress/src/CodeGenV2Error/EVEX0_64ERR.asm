option flat:1
option evex:1

.code

	use64

	vmovaps myVector{z},xmm21				; Unsupported masking operator.
	vmulps zmm20{k2}{z}, zmm0, [rdi]{1to8}	; Broadcast wrong size.
	