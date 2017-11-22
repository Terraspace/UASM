
;--- forward references with LxS

	.model small

	.code

	lds bx,var1
	les dx,var1
	.386
	lfs ax,var1
	lgs cx,var1
	lss sp,var1
	lds esi,var2
	les edi,var2
	lfs ebp,var2
	lss esp,var2

	.data
var1 dd 0
var2 df 0

	END
