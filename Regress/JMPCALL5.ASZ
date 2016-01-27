
	.286
	.model small
	.stack 200h

	includelib <jmpcall5.lib>

_TEXT segment
extern e1:far
e2 proto far
_TEXT ends

	.data

v1	dq 0

	.code
start:
	mov ah,4CH
	int 21h

;--- external far label

	call e1
	call e2
	jmp e1
	jmp short e1
	jz short e1
	jz e1

;--- internal far label

	call p1
	call far ptr p1
	jmp p1
	jmp short p1
	jz p1
	jz short p1

p1 proc far
	ret
p1 endp

	end start
