
	.686
	.model small
	.xmm

	.data

m128	OWORD 0
m64		dq 0
m32		dd 0
m16		dw 0

	.code

	assume ds:DGROUP

main proc
	cvtpd2pi mm0, xmm1
	cvtpd2pi mm0, m128
;	cvtpd2pi mm0, m64	;accepted by Masm?!
	cvtps2pi mm1, xmm2
	cvtps2pi mm0, m64
	cvtsd2si eax, xmm1
	cvtsd2si ebx, m64
	cvtss2si ecx, xmm1
	cvtss2si edx, m32

	cvtpi2pd xmm0, mm1
	cvtpi2pd xmm0, m64
	cvtpi2ps xmm0, mm1
	cvtpi2ps xmm0, m64
	cvtsi2sd xmm0, eax
	cvtsi2sd xmm0, m32
;	cvtsi2sd xmm0, m64	;64-bit only
	cvtsi2ss xmm0, eax
	cvtsi2ss xmm0, m32
;	cvtsi2ss xmm0, m64	;64-bit only

	ret
main endp

    END
