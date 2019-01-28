
option flat:1

.code

	use64
	
	pshufd xmm0, xmm0, 1
	pshufd xmm0, xmm3, 0
	pshufd xmm0, xmm8, 0xff
	pshufd xmm8, xmm3, 2
	pshufd xmm8, xmm9, 10

	pshufd xmm0, [rdi], 1
	pshufd xmm2, [rdi+rax*2], 1
	pshufd xmm3, [rsp], 2
	pshufd xmm4, [rbp-4], 3
	pshufd xmm8, [rdi], 1
	pshufd xmm9, [rdi+rax*2], 2
	pshufd xmm10, [rsp], 3
	pshufd xmm11, [rbp-4], 4	
	
	pshufd xmm0, myVector, 1
	pshufd xmm9, myVector, 2
	
.data
	
align 16
myVector __m128f <1.0,2.0,3.0,4.0>