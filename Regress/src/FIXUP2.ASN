
;--- memory operands with near/far immediates

	.286
	.model small
	.386

	.stack 200h
	.data

m08	label byte
m16	label word
m32	label dword
m48	label fword
m64	label qword
m80	label tbyte

	.code

xxx proc far
	ret
xxx endp

	mov m16, xxx
	mov m16, far ptr xxx
	mov m16, far16 ptr xxx
	mov m16, seg far16 ptr xxx
	mov m16, offset far16 ptr xxx

	mov m32, xxx
	mov m32, far ptr xxx
	mov m32, far16 ptr xxx
	mov m32, seg far16 ptr xxx
	mov m32, offset far16 ptr xxx

start:
	mov ah,4ch
	int 21h
	end start
