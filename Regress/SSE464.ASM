
;--- SSE 4, 64-bit specific instructions
;--- was encoded incorrectly prior to v2.06

ifdef __JWASM__
if type near eq 0ff02h
	.x64
	.model flat
endif
endif

	.data

m64 label qword

	.code

	pextrq rax, xmm1, 1
	pextrq m64, xmm1, 2
	pinsrq xmm0, rax, 3
	pinsrq xmm0, m64, 4
	ret

	End
