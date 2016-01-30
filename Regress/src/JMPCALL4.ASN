
;--- regression test
;--- code generation
;--- JMP/CALL immediate operand

	.286
	.model small
	.dosseg
	.386

	.stack

_TEXT16 segment WORD use16 'CODE'
p3 proc far
	ret
p3 endp
_TEXT16 ends

_TEXT32 segment DWORD use32 'CODE'
p4 proc far
	ret
p4 endp
_TEXT32 ends

	.code

start:
	mov ah,4ch
	int 21h

p1 proc near
	ret
p1 endp

p2 proc far
	ret
p2 endp

	call p1
	call near ptr p1
	jmp p1
	jmp near ptr p1
	jmp short p1
	call p1f
	call near ptr p1f
	jmp p1f
	jmp near ptr p1f
	jmp short p1f

	call p2
	call far ptr p2
	jmp p2
	jmp far ptr p2
	call p2f
	call far ptr p2f
	jmp p2f
	jmp far ptr p2f

	call p3
	call far ptr p3
	call far16 ptr p3
	jmp p3
	jmp far ptr p3
	jmp far16 ptr p3

	call p4
	call far ptr p4
	call far32 ptr p4
	jmp p4
	jmp far ptr p4
	jmp far32 ptr p4

p1f proc near
	ret
p1f endp

p2f proc far
	ret
p2f endp

	end start
