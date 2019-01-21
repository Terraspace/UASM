
option flat:1

.code

	use64
	
	movaps XMMWORD PTR [rsp],xmm2

	movaps xmm0,xmm0
	movaps xmm0,xmm4
	movaps xmm4,xmm2
	movaps xmm8,xmm0
	movaps xmm10,xmm2
	movaps xmm0,xmm9
	movaps xmm2,xmm12
	movaps xmm0,xmm15
	movaps xmm10,xmm12
	
	movaps xmm0,myVector
	movaps xmm12,myVector
	movaps myVector,xmm0
	movaps myVector,xmm12
	
	movaps xmm0,[rdi]
	movaps [rdi],xmm0
	
	movaps xmm0,[rdi+rax*2]
	movaps [rdi+rax*2],xmm0

	movaps xmm12,[rdi]
	movaps [rdi],xmm12
	
	movaps xmm12,[rdi+rax*2]
	movaps [rdi+rax*2],xmm12
	
.data

align 16
myVector __m128f <1.0,2.0,3.0,4.0>