
;--- fixups for FAR assembly-time variables
;--- didn't work prior to v2.07

Cseg SEGMENT public byte 'CODE'

start:
	mov ah,4ch
	int 21h

	DD RtS	;far pointer behind 11s
	DD Lab	;far pointer behind FFs (label)
	DD Lab_p1	;far pointer behind FFs (assembly-time var)

	db 14 dup(0ffh)

	Lab_1:
	Lab_p1 = Lab_1

	db 0AAh

CSEG ENDS

RCSEG SEGMENT public byte 'CODE'

	db 15 dup(011h)
Lab:
	db 1 dup(022h)

RCSEG ENDS

RtS = Lab

STACK segment stack 'STACK'
	db 100h dup (?)
STACK ends

end start
