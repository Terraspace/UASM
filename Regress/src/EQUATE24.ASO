
;--- this was a regression in v2.08
;--- an valid numeric equate was stored as a text macro
;--- in certain cases.

	.386
	.model flat,stdcall

	.code

; the next line ensures that a) the equate is parsed in pass 2
; and b) that the token buffer is filled with more than 3 items.
	db 1,2,3,4,5
E1	equ 'what'
	db E1

	end
