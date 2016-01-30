
;--- test usage of assembly time variables within structures

	.286

S1  struc
	dw 1
	dw 2
	dw 3
	dw 4
	dw 5
filler db (16-$) dup(0)	;this didn't work before v2.03
S1  ends

S2  struc
	dw $
	dw $
	dw $
S2  ends

S3  struc
	db ?
	S2 <>
S3  ends

E1 = 2

S4  struc
	db E1
	db E1*2
S4  ends

E1 = 3

E2  = 5

S5  struc
	db E2 dup ( 1, 2 )
	db -1
S5  ends

E2  = 10	;change of variable should have no effect for S5!

_DATA segment 'DATA'
	S1 <>
	S2 <>
	S3 <>
	S4 <>	;must contain 2,4
	S5 <>	;must contain 5 * 1,2, then -1
_DATA ends

	end
