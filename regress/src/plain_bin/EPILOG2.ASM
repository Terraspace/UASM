
;--- test PROC epilogue creation with RET
;--- inside the macro, a RET has still to be translated to
;--- RETF if the proc is FAR.

myepilogue macro a,b,c,d,e,f
ret
endm

option epilogue:myepilogue

_TEXT segment word public 'CODE'
tproc proc far
xor ax, ax
ret
tproc endp
_TEXT ends

	END
