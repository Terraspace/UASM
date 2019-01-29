
option flat:1

.code

	use32
	mpsadbw xmm0, xmm2, 1
	mpsadbw xmm0, xmm2, 2
	mpsadbw xmm0, myVector, 1
	mpsadbw xmm3, [edi], 3
	mpsadbw xmm0, [edi+eax], 4
	mpsadbw xmm2, [ebp+eax*2], 5
	
	blendvps xmm1, xmm2
	blendvps xmm3, xmm5
	blendvps xmm3, myVector
	blendvps xmm2, [edi]
	blendvps xmm2, [edi+eax*2]
	
.data
	
align 16
myVector __m128f <1.0,2.0,3.0,4.0>