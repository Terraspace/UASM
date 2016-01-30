
;--- invalid alignment argument

	.386
	.model flat, stdcall

S1 struct <abc>	;literal
S1 ends

S2 struct E2	;forward ref
S2 ends

E2 equ 2

S3 struct 64	;constant > 32
S3 ends

S4 struct 3		;not a power of 2
S4 ends

S5 struct ,NONUNIQUE
S5 ends

S6 struct 4, ABC
S6 ends

end
