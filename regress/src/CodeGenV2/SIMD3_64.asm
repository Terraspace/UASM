
option flat:1

.code

	use64

	mpsadbw xmm0, xmm2, 1
	mpsadbw xmm0, xmm2, 2
	mpsadbw xmm9, xmm2, 3
	mpsadbw xmm0, xmm9, 4
	mpsadbw xmm10, xmm11, 5
	mpsadbw xmm0, myVector, 1
	mpsadbw xmm0, [rdi], 2
	mpsadbw xmm9, [edi], 3
	mpsadbw xmm0, [rdi+rax], 4
	mpsadbw xmm10, [r8+rax*2], 5
	
	blendvps xmm1, xmm2
	blendvps xmm3, xmm5
	blendvps xmm3, myVector
	blendvps xmm2, [rdi]
	blendvps xmm2, [rdi+rax*2]

	blendvps xmm9, xmm2
	blendvps xmm9, xmm10
	blendvps xmm3, xmm9
	blendvps xmm9, myVector
	blendvps xmm9, [rdi]
	blendvps xmm8, [rdi+rax*2]	
	
.data
	
align 16
myVector __m128f <1.0,2.0,3.0,4.0>