
;--- SSSE3 instructions

	.686
	.model flat
	.xmm

	.data

var1	oword 0
var2	qword 0

	.code

	pabsb xmm1, var1
	pabsd xmm1, var1
	pabsw xmm1, var1
	pabsb mm1, var2
	pabsd mm1, var2
	pabsw mm1, var2

	pabsb xmm1, [ebx]
	pabsd xmm1, [ebx+10]
	pabsw xmm1, [ebx+1000]
	pabsb mm1, [ebx]
	pabsd mm1, [ebx+10]
	pabsw mm1, [ebx+1000]

	pabsb xmm1, [esp]
	pabsd xmm1, [esp+10]
	pabsw xmm1, [esp+1000]
	pabsb mm1, [esp]
	pabsd mm1, [esp+10]
	pabsw mm1, [esp+1000]

	palignr mm0, mm1, 1
	palignr mm0, var2, 2
	palignr xmm0, xmm1, 3
	palignr xmm0, var1, 4

	ret

end
