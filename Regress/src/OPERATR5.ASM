
;--- operators SIZEOF, LENGTHOF, SIZE, LENGTH, TYPE
;--- for LOCAL and LABEL

	.model small
	option casemap:none

S1 struct
	db ?,?
S1 ends

	.code

v0	label dword

v1	label S1
	S1 <>

v2	label S1
	S1 <>
	S1 <>

v3	label near

	dw sizeof v0, lengthof v0, size v0, length v0
	dw sizeof v1, lengthof v1, size v1, length v1
	dw sizeof v2, lengthof v2, size v2, length v2

p1	proc

local lcl1:S1
local lcl2[3]:S1

	dw sizeof lcl1, lengthof lcl1, size lcl1, length lcl1
	dw sizeof lcl2, lengthof lcl2, size lcl2, length lcl2

p1	endp

	END
