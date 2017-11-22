
;--- LAR/LSL:
;--- according to intel docs, mem ref must always be a WORD
;--- However, this is true for 64-bit only (JWasm and ML64).

ifdef __JWASM__
	.x64
	.model flat
endif

	.data

vw	dw 0h

	.code

	lsl ax,vw
	lsl ax,bx
	lsl eax,vw
	lsl eax,edx
	lsl rax,vw
	lsl rax,rdx

	lar ax,vw
	lar ax,bx
	lar eax,vw
	lar eax,edx
	lar rax,vw
	lar rax,rdx
	ret

	end
