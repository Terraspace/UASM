
;--- don't extend integers to pointers

	.286
	.model small

	.data

uvb byte 0
uvw word 0
uvd dword 0

svb sbyte 0
svw sword 0
svd sdword 0

	.code

x proc c a1:near ptr, a2:far ptr, a3:far ptr
	ret
x endp

	.286
	invoke x, uvb, uvb, uvw
	.386
	invoke x, uvb, uvb, uvw

	.286
	invoke x, svb, svb, svw
	.386
	invoke x, svb, svb, svw

	end
