
;--- absolute segments

	.286

ABSSEG segment 'CODE' at 50h
label1 label far
	dd ?
label2 label far
ABSSEG ends

_TEXT segment word public 'CODE'

start:
	mov ah,4ch
	int 21h

	mov ax, ABSSEG
	jmp label1
	jmp label2
	dw ABSSEG
	dd label1
	dd label2

_TEXT ends

STACK segment stack 'STACK'
	db 100h dup (?)
STACK ends

	End start
