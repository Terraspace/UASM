
ifdef __JWASM__
	.x64
	.model flat, fastcall
endif

	.data

m64	dq 0

	.code

lbl1:
	mov m64, offset lbl1 ;ok for 2.05-2.06c, rejected < 2.04
	push offset lbl1     ;ok for 2.05-2.06c, rejected < 2.04
	ret

	end
