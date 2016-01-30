
;--- quoted strings

	.386
	.model flat, stdcall

S1 struct
f1	db ?
f2	db ""	;accepted, but gives error if instanced
S1 ends

	.code

	mov al,""	;not accepted since v2.11

v1	S1 <>

	db ""

END
