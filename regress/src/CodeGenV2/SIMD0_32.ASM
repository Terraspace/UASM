
option flat:1

.code

	use32
	
	movaps XMMWORD PTR [esp],xmm2

	movaps xmm0,xmm0
	movaps xmm0,xmm4
	movaps xmm4,xmm2
	movaps xmm0,xmm5
	
	movaps xmm0,myVector
	movaps myVector,xmm0
	
	movaps xmm0,[edi]
	movaps [edi],xmm0
	
	movaps xmm0,[edi+eax*2]
	movaps [edi+eax*2],xmm0

.data

align 16
myVector __m128f <1.0,2.0,3.0,4.0>