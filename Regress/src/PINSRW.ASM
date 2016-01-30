
	.686
	.model small
	.xmm

	.data

m16		dw 0

	.code

main proc
	pinsrw mm0, eax, 0
	pinsrw mm1, eax, 1
	pinsrw mm2, m16, 0
	pinsrw mm3, m16, 1
	pinsrw xmm0, eax, 0
	pinsrw xmm1, eax, 1
	pinsrw xmm2, m16, 0
	pinsrw xmm3, m16, 1
	ret
main endp

    END
