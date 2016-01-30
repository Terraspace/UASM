
;--- 2 forward references in 1 line

	.286
	.model small

	.code

	jmp l2	;jump will be short if size of E1 is assumed BYTE
	mov v1,E1
	db 122 dup (?)
l2:

	.data

E1	equ 2
v1	db 0

	end
