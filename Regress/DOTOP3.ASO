
;--- dot operator errors
;--- most will work with OPTION OLDSTRUCTS

	.386
	.model flat

S1 struct
f1	dd ?
S1 ends

	.code

xxx S1 <>

	mov eax, [eax].f1		;undefined symbol f1
	mov eax, [eax].[ebx] 	;structure field expected
	mov eax, ds:[0].S1		;operand must be a memory expression
	mov eax, [eax].4		;structure field expected
	mov eax, [eax].DWORD	;structure field expected
	mov eax, eax.S1			;invalid use of register
	mov eax, [eax].xxx		;structure field expected

;--- prior to v2.07, it was accepted if a struct type
;--- was followed by another struct type

S21 struct
f1	db ?
S21 ends

S2 struct
f2	S11 <>                   ;Masm ok???, jwasm error
S2 ends

	mov al,[ebx.S2.S21.f1]   ;undefined symbol
	mov al,[ebx],S2.S21.f1   ;Masm ok???, jwasm error

END
