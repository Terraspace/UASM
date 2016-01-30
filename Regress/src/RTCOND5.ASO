
;--- run-time conditionals
;--- check for multiple .ELSE clauses
;--- .ENDIF without .IF

	.386
	.model flat

	.code
	.if ebx
		xor eax,eax
	.else
		dec eax
	.else
		dec eax
	.endif

	.if ebx > 1
		xor eax,eax
	.else
		dec eax
	.elseif ebx > 2
		dec eax
	.endif

	.if				;jwasm NEEDS an expression, Masm accepts void
	.endif

	.if 1
	.endw			;endw instead of .endif

	.repeat
	.endif

	.while 1
	.endif

	end
