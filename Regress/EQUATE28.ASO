
;--- using $ in an expression outside of segment or struct block
;--- is an error - even in an EQU operand!

	.386
	.model flat, stdcall
	option casemap :none

S1 struct
E0 equ $	;ok
S1 ends

E1 equ $
E2 equ $+1
E3 = $
E4 = $+1

end
