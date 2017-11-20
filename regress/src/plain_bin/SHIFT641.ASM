
ifdef __JWASM__
	.x64
	.model flat
endif

	.code

vb	db 0
vw	dw 0
vd	dd 0
vq	dq 0

	shr al,cl
	shr ax,cl
	shr eax,cl
	shr rax,cl
	shr vb,cl
	shr vw,cl
	shr vd,cl
	shr vq,cl
	shr al,1
	shr ax,1
	shr eax,1
	shr rax,1
	shr vb,1
	shr vw,1
	shr vd,1
	shr vq,1
	shr al,5
	shr ax,5
	shr eax,5
	shr rax,5
	shr vb,5
	shr vw,5
	shr vd,5
	shr vq,5

	end
