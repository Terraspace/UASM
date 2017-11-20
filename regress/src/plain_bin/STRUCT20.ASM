
;--- struct member forward reference

	.286
	.model small

	.code

	mov  [bx].S1.f1,2	;in v2.06, error 'Size not specified, assuming BYTE'
	mul  [bx].S1.f1		;in v2.06, error 'Instruction operand must have size'
	push [bx].S1.f2		;ok
	call [bx].S1.f2		;ok

S1 struct
f1 db ?
f2 dw ?
S1 ends

	end
