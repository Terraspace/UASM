
;--- more expansion

	.model small

	.data

TE1	equ <string1>
TE2	equ <4>

M1	macro p1, p2, p3:vararg
local tmp
tmp CatStr <p1>,<p2>,<p3>
	db @CatStr(!", tmp, !")
	db @CatStr(!", %tmp, !")
	endm

	M1 <abc>.<def>,<ghi>,<jkl>,<mno>
	M1 <% TE1>,< % 1+2>,< 5 %TE2 + 3>
	M1 < %1>,< %2>,< % >

END
