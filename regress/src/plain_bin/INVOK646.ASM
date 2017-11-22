
;--- test 64-bit invoke with VARARG parameter
;--- also see vararg64.asm

ifdef __JWASM__
	.x64
	.model flat, fastcall
	option win64:2
endif

	.data
uvq	label qword
uvd	label dword
uvw	label word
uvb	label byte
svq	label sqword
svd	label sdword
svw	label sword
svb	label sbyte
	dq 0

	.code

p1 proc a1:VARARG
p1 endp

	invoke p1, 0

	invoke p1, 1, 2, 3, 4
	invoke p1, uvq, uvd, uvw, uvb
	invoke p1, svq, svd, svw, svb
	invoke p1, 1, 2, 3, 4, 5, 6
	invoke p1, 1, 2, 3, 4, uvb, uvw, uvd, uvq
	invoke p1, 1, 2, 3, 4, svb, svw, svd, svq
	invoke p1, 1, 2, 3, 4, addr uvb, addr uvw
	invoke p1, 1, 2, 3, 4, offset uvb, offset uvw
	ret

	end
