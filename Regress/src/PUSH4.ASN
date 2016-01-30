
;--- push with type coercion

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

E1	equ 2
lbl label near

	push -1
	push E1
	push byte ptr 1
	push byte ptr -1
	push byte ptr E1
	push word ptr 1
	push word ptr -1
	push word ptr E1
	push dword ptr 1
	push dword ptr -1
	push dword ptr E1
	push word ptr [m08]
	push dword ptr [m08]
	push lbl
	push near ptr lbl
	push near16 ptr lbl
	push near32 ptr lbl
	push far16 ptr lbl
	push word ptr lbl	;this will push CONTENT of lbl
	push dword ptr lbl	;this will push CONTENT of lbl

start:
	mov ah,4ch
	int 21h
	end start
