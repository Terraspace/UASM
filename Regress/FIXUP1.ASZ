
;--- test 'data' fixups in OMF format.
;--- created object module was invalid in v2.00-v2.01
;--- (LEDATA and fixups out of sync)

	.model small
	.stack
	.code
	db 90h
start:
	mov bx,offset table
exit:
	mov ax,4c00h
	int 21h

	even
table dw 256 dup(start,exit)

	end start
