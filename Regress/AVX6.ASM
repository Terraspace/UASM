
;--- AVX, 32-bit
;--- test of some instructions that were missing in avx1.asm

	.686
	.model flat
	.xmm

	.data

m32 label dword
m64 label qword
	dq 0

	.code

	vmovss xmm0, xmm1, xmm2
	vmovss xmm0, m32
	vmovss m32, xmm0
	vmovss xmm0, dword ptr [ebx]
	vmovss dword ptr [ebx], xmm0

	vmovsd xmm0, xmm1, xmm2
	vmovsd xmm0, m64
	vmovsd m64, xmm0
	vmovsd xmm0, qword ptr [ebx]
	vmovsd qword ptr [ebx], xmm0

end
