
;--- \; inside a literal causes line concatenation, rest of line is ignored

	.286
	.model small

S1	struct
	db ?
	db ?
	db ?
	db ?
	db ?
	db ?
S1	ends

	.data

xx	textequ <abc\;def>
	qqq>
%	db "&xx"	;must be "abcqqq"

v1	S1 {1,2,3\;}
	,4,5,6}

	end
