
;--- macro redefinition within the macro.
;--- didn't work with GOTO prior to v2.06.

	.286
	.model small

E1 = 0

m1 macro x
	purge m1
:lbl1
	mov al,E1+x
	E1 = E1+1
	if E1 lt 5
	  goto lbl1
	endif
	endm

	.code

	m1 0

end
