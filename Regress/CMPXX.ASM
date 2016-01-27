
	.686
	.model small
	.xmm

	.data

vo	OWORD 0
vq	dq 0
vd	dd 0

	.code

cmpxx macro suffix, var
	cmp&suffix xmm0, xmm1, 0
	cmp&suffix xmm0, var, 0
	cmpeq&suffix xmm0, xmm1
	cmpeq&suffix xmm0, var
	cmplt&suffix xmm0, xmm1
	cmplt&suffix xmm0, var
	cmple&suffix xmm0, xmm1
	cmple&suffix xmm0, var
	cmpunord&suffix xmm0, xmm1
	cmpunord&suffix xmm0, var
	cmpneq&suffix xmm0, xmm1
	cmpneq&suffix xmm0, var
	cmpnlt&suffix xmm0, xmm1
	cmpnlt&suffix xmm0, var
	cmpnle&suffix xmm0, xmm1
	cmpnle&suffix xmm0, var
	cmpord&suffix xmm0, xmm1
	cmpord&suffix xmm0, var
	endm

main proc
	CMPXX pd, vo
	CMPXX ps, vo
	CMPXX sd, vq
	CMPXX ss, vd
	ret
main endp

    END
