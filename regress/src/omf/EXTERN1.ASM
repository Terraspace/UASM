
;--- test absolute externals

	.model small
	.stack

extern value1:abs

	includelib <extern1.lib>

	.code

start:
	or al,value1
	mov al,value1
	mov ah,4ch
	int 21h

	end start
