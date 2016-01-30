
;--- assembly time variables restauration
;--- prior to v2.05 there was a bug in equate.c
;--- which didn't restore assembly time variables correctly
;--- if their value was negative. Error msg "constant
;--- value too large" was displayed then.

	.386
	.model flat

X1	= -1

	.code

	db 0	;initiate line storage

X1	= X1 + 1

X1	= X1 + 1

	mov eax, X1

	end
