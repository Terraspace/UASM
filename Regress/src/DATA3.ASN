
;--- labels in "data expressions"
;--- jwasm doesn't handle this fully Masm compatible
;--- because it doesn't ignore a possible type coercion.
;--- the Masm-behavior is regarded a bug.

	.286
	.model small
	option casemap:none

	.stack 200h

	.code

start:
	mov ah,4ch
	int 21h

cl1 label near
	nop
cl2 label far
	nop
cl3 label proc

	.data

dl1 db 0
dl2 dw 0
dl4 dd 0

	dw dl1,dl2,dl4
	dw near ptr dl1,near ptr dl2,near ptr dl4
;	dw far ptr dl1	;didn't fail if < v2.06
	dd dl1,dl2,dl4
	dd near ptr dl1,near ptr dl2,near ptr dl4
	dd far ptr dl1,far ptr dl2,far ptr dl4	;fails for v2.00-2.05

	dw cl1,cl2,cl3
	dw near ptr cl1,near ptr cl2,near ptr cl3
;	dw far ptr cl1	;didn't fail if < v2.06
	dd cl1,cl2,cl3
	dd near ptr cl1,near ptr cl2,near ptr cl3
	dd far ptr cl1,far ptr cl2,far ptr cl3	;fails for v2.00-2.05

	end start
