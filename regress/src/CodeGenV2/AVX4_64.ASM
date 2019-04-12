
option flat:1

.code

	use64
	
	;REG/REG
	
	vmovapd xmm0,xmm0
	vmovapd xmm0,xmm4
	vmovapd xmm4,xmm2
	vmovapd xmm0,xmm12
	vmovapd xmm12,xmm0
	vmovapd xmm12,xmm13
	
	vmovapd ymm0,ymm0
	vmovapd ymm0,ymm4
	vmovapd ymm4,ymm2
	vmovapd ymm0,ymm12
	vmovapd ymm12,ymm0
	vmovapd ymm12,ymm13	
	
	; REG/MEM
	vmovapd xmm0,[rdi]
	vmovapd xmm2,[rdi+rax]
	vmovapd xmm2,[rsi+rbx*2]
	vmovapd xmm4,[rbp-0x04]
	vmovapd xmm5,[rsp]
	vmovapd xmm3,[rdi+r12]
	vmovapd xmm6,myVector
	vmovapd xmm7,XMMWORD PTR myVector
	
	vmovapd xmm8,[rdi]
	vmovapd xmm9,[rdi+rax]
	vmovapd xmm9,[rsi+rbx*2]
	vmovapd xmm10,[rbp-0x04]
	vmovapd xmm15,[rsp]
	vmovapd xmm13,[rdi+r11]
	vmovapd xmm11,myVector
	vmovapd xmm12,XMMWORD PTR myVector

	vmovapd ymm0,[rdi]
	vmovapd ymm2,[rdi+rax]
	vmovapd ymm2,[rsi+rbx*2]
	vmovapd ymm4,[rbp-0x04]
	vmovapd ymm5,[rsp]
	vmovapd ymm6,myVector
	vmovapd ymm7,YMMWORD PTR myVector
	
	vmovapd ymm8,[rdi]
	vmovapd ymm9,[rdi+rax]
	vmovapd ymm9,[rsi+rbx*2]
	vmovapd ymm10,[rbp-0x04]
	vmovapd ymm15,[rsp]
	vmovapd ymm11,myVector
	vmovapd ymm12,YMMWORD PTR myVector	
	
	; MEM/REG
	vmovapd [rdi],xmm0
	vmovapd [rdi+rax],xmm2
	vmovapd [rsi+rbx*2],xmm2
	vmovapd [rbp-0x04],xmm4
	vmovapd [rdi+r12],xmm3
	vmovapd [rsp],xmm5
	vmovapd myVector,xmm6
	vmovapd XMMWORD PTR myVector,xmm7
	
	vmovapd [rdi],xmm8
	vmovapd [rdi+rax],xmm9
	vmovapd [rsi+rbx*2],xmm9
	vmovapd [rbp-0x04],xmm10
	vmovapd [rsi+r11],xmm13
	vmovapd [rsp],xmm15
	vmovapd myVector,xmm11
	vmovapd XMMWORD PTR myVector,xmm12

	vmovapd [rdi],ymm0
	vmovapd [rdi+rax],ymm2
	vmovapd [rsi+rbx*2],ymm2
	vmovapd [rbp-0x04],ymm4
	vmovapd [rsp],ymm5
	vmovapd myVector,ymm6
	vmovapd YMMWORD PTR myVector,ymm7
	
	vmovapd [rdi],ymm8
	vmovapd [rdi+rax],ymm9
	vmovapd [rsi+rbx*2],ymm9
	vmovapd [rbp-0x04],ymm10
	vmovapd [rsp],ymm15
	vmovapd myVector,ymm11
	vmovapd XMMWORD PTR myVector,ymm12
.data

align 32
myVector __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>