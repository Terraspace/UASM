
option flat:1

.code

	use32
	
	pshufd xmm0, xmm0, 1
	pshufd xmm0, xmm3, 0
	
	pshufd xmm0, [edi], 1
	pshufd xmm2, [edi+eax*2], 2
	pshufd xmm3, [esp], 3
	pshufd xmm4, [ebp-4], 4
	
	pshufd xmm0, myVector, 1
	
.data
	
align 16
myVector __m128f <1.0,2.0,3.0,4.0>