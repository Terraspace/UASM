
option flat:1

.code

	use64
	
	;REG/REG
	vmulps xmm0,xmm1,xmm2
	vmulps xmm0,xmm0,xmm0
	vmulps xmm0,xmm8,xmm2
	vmulps xmm2,xmm4,xmm10
	vmulps xmm8,xmm9,xmm10
	
	;REG/MEM
	vmulps xmm0,xmm1,myVector
	vmulps xmm0,xmm8,myVector
	vmulps xmm8,xmm9,myVector
	
.data

align 32
myVector __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>