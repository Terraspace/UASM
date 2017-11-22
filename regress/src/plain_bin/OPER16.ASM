
;--- operators SIZE, TYPE
;--- for 16-bit NEAR/FAR

	.286
	.model small

TN  typedef near
TF  typedef far

	.code

	dw near, size near, type near
	dw far,  size far,  type far

	dw TN, size TN, type TN
	dw TF, size TF, type TF

v1	label near
v2	label far

	dw size v1, type v1
	dw size v2, type v2

p1	proc

local l1[2]:TN
local l2[2]:TF

	dw sizeof   l1
	dw lengthof l1
	dw size     l1
	dw length   l1
	dw type     l1

	dw sizeof   l2
	dw lengthof l2
	dw size     l2
	dw length   l2
	dw type     l2

p1	endp

	END
