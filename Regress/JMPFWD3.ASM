
;--- short jump (without extension)
;--- the pattern is:
;--- first jump's destination is a forward reference
;--- second jump's destination is backward

;	option noljmp	;will make Masm emit error 'jump destination too far'

_TEXT segment WORD public 'CODE'

;--- the following pattern is a problem for Masm, it will extend the 
;--- (conditional) jumps.
;--- JWasm's "optimistic" approach has no problems, all jumps are short.

;--- conditional jumps for 8086
l0:
	db 124 dup (?)
	jz l1          ;distance is 7Fh
	jz l0          ;distance is 80h
	db 125 dup (?)
l1:

;--- unconditional jumps for 8086
l2:
	db 124 dup (?)
	jmp l3          ;distance is 7Fh
	jmp l2          ;distance is 80h
	db 125 dup (?)
l3:

	.386

;--- conditional jumps for 80386
l4:
	db 124 dup (?)
	jz l5          ;distance is 7Fh
	jz l4          ;distance is 80h
	db 125 dup (?)
l5:

_TEXT ends

	end
