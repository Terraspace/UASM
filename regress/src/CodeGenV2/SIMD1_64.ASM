
option flat:1

.code

	use64
	
	mulps xmm0, xmm0
	mulps xmm0, xmm1
	mulps xmm2, xmm3

	mulps xmm0, xmm8
	mulps xmm0, xmm9
	mulps xmm2, xmm10

	mulps xmm8, xmm0
	mulps xmm9, xmm1
	mulps xmm10, xmm3

	mulps xmm8, xmm8
	mulps xmm9, xmm9
	mulps xmm10, xmm10
	
	mulps xmm0, myVector
	mulps xmm0, [rdi]
	mulps xmm2, [rdi+rax*2]
	mulps xmm2, [rbp-0x04]
	mulps xmm2, [rsp]

	mulps xmm12, myVector
	mulps xmm11, [rdi]
	mulps xmm10, [rdi+rax*2]
	mulps xmm9, [rbp-0x04]
	mulps xmm8, [rsp]	
	
.data

align 16
myVector __m128f <1.0,2.0,3.0,4.0>