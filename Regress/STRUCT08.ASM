
;--- test arrays inside structs

	.286

S1  struc
f1	db ?
f2	db ?
f3	db 8 dup (?)
S1  ends

TE1	equ <3,4,5>
TE2	equ <'abc'>

_DATA segment 'DATA'
	S1 <1,2,<3,4,5>>
	S1 <1,2,5 dup (3)>
	S1 <1,2,<TE1>>
;	S1 <1,2,<TE2>>  ;Masm complains
	S1 <1,2,'abc'>
	S1 <1,2,TE2>	;this didn't work prior to v2.04
_DATA ends

	end
