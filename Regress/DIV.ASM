
;--- test div [, idiv, mul, neg, not ] - 16-bit

	.286
	.model small
	.386

	.data

vb	db 0
vw	dw 0
vd	dd 0
vq	dq 0

	.code

	div cl
	div cx
	div ecx
	div vb
	div vw
	div vd
;	div vq

	end
