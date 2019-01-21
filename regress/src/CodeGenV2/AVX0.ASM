
option flat:1

.code

	use64
	
	vmovaps xmm0,xmm0
	vmovaps xmm0,xmm4
	vmovaps xmm4,xmm2
	vmovaps xmm0,xmm12
	vmovaps xmm12,xmm0
	vmovaps xmm12,xmm13
	
	vmovaps ymm0,ymm0
	vmovaps ymm0,ymm4
	vmovaps ymm4,ymm2
	vmovaps ymm0,ymm12
	vmovaps ymm12,ymm0
	vmovaps ymm12,ymm13	
	
.data

align 32
myVector __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>