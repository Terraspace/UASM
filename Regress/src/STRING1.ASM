
;--- just the segment part of operands is checked.

_TEXT segment word public 'CODE'

;--- no prefix generated
	repe cmps word ptr [si],word ptr [di]
;--- no prefix generated
	repe cmps word ptr ds:[si],word ptr [di]
;--- CS prefix generated
	repe cmps word ptr cs:[si],word ptr es:[di]
;--- ES prefix generated
	repe cmps word ptr es:[si],word ptr [di]

_TEXT ends

	end


