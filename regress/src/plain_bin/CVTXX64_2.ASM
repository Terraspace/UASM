
ifdef __JWASM__
	.x64
	.model flat
endif

	.data

m128	OWORD 0
m64		dq 0
m32		dd 0
m16		dw 0

	.code

main proc
	cvtsi2ss xmm0,eax
	cvtsi2ss xmm10,eax

	cvtsi2ss xmm0,rax
	cvtsi2ss xmm10,rcx

	cvtsi2ss xmm0,r10d
	cvtsi2ss xmm1,r10d
	cvtsi2ss xmm10,r9d

	cvtsi2ss xmm0,r10
	cvtsi2ss xmm1,r9
	cvtsi2ss xmm10,r9

	ret
main endp

    END
