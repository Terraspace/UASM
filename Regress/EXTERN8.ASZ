
;--- abs external:

		.386

		includelib <extern8.lib>

externdef value1:abs

_DATA	segment word public 'DATA'
		db value1      ;was rejected prior to v2.08
		dw value1      ;regression in v2.07, fixed in v2.07a
		dd value1
_DATA	ends

_TEXT	segment word public 'CODE'
		mov al, value1
		mov ax, value1
		mov eax, value1

start:
		mov ah,4ch
		int 21h
_TEXT	ends

STACK segment stack 'STACK'
		db 100 dup (?)
STACK ends

		END start

