
;--- OPATTR with undefined struct member

	.386

S1 struct
f1 db ?
S1 ends

_DATA segment 

	dw opattr S1.f1
	dw opattr S1.f2

_DATA ends

	end
