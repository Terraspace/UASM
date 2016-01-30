
;--- extend unsigned and signed data labels to DWORD in 16-bit

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

x proc c a1:dword, a2:dword, a3:dword
	ret
x endp

	.8086
	invoke x, uvb, uvw, uvd
	.186
	invoke x, uvb, uvw, uvd
	.386
	invoke x, uvb, uvw, uvd

	.8086
	invoke x, svb, svw, svd
	.186
	invoke x, svb, svw, svd
	.386
	invoke x, svb, svw, svd

	end
