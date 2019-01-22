
option flat:1

.code

	use32
	
	mulps xmm0, xmm0
	mulps xmm0, xmm1
	mulps xmm2, xmm3
	mulps xmm0, myVector
	mulps xmm0, [edi]
	mulps xmm2, [edi+eax*2]
	mulps xmm2, [ebp-0x04]
	mulps xmm2, [esp]
	
.data

align 16
myVector __m128f <1.0,2.0,3.0,4.0>