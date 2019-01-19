
option flat:1

.code

	use64
	
	vmovaps xmm0,xmm0
	
.data

align 32
myVector __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>