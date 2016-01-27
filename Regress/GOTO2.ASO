
;--- GOTO directive peculiarities
;--- a GOTO will reset the if-nesting-level 
;--- hence if a goto-label is inside an if-block,
;--- an error will occur at the next ENDIF.
;--- the only way to circumvent this is to use EXITM
;--- works since v2.10

	.386
	.model flat, stdcall

AU MACRO a1
	if 1
		goto ms1
		:ms1
		goto ms2
		:ms2
	endif
ENDM

	.data

	AU(1)

end
