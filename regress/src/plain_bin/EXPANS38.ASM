
;--- handle '\' as last char AFTER expansion
;--- works since v2.11

	.386
	.model flat

	.code

XXX	textequ <\>

	if XXX
	1
	db 0
	endif

;--- use a hll directive, to ensure it also
;--- works if the line will cause generated code.

	.if eax == XXX
	1
	db 0
	.endif

end
