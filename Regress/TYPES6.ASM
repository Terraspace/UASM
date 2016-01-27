
;--- TYPE and type comparisons

	.286
	.model small

S1 struct
	dd ?
S1 ends

S2 struct	;this struct has no equivalent simple type
	dd ?
	dd ?
	dd ?
S2 ends

S2x struct	;alias of S2
	dd ?
	dd ?
	dd ?
S2x ends

	.code

v1 S1 <>
v2 S2 <>

	db TYPE(v1) eq S1	;is -1
	db TYPE(v2) eq S2	;is -1
	db TYPE(v2) eq S2x	;is 0

	end
