
option flat:1
option evex:1

.code

	use64
	
	;REG/REG
	vmovaps zmm0, zmm1
	vmovaps zmm9, zmm1
	vmovaps zmm17, zmm1
	vmovaps zmm0, zmm9
	vmovaps zmm0, zmm17
	vmovaps zmm10, zmm11
	vmovaps zmm20, zmm30
	
	vmovaps zmm0{z}, zmm1
	vmovaps zmm1{k1}, zmm20
	vmovaps zmm2{k2}{z}, zmm3
	
	{evex} vmovaps xmm0,xmm0
	{evex} vmovaps xmm0,xmm4
	{evex} vmovaps xmm4,xmm2
	{evex} vmovaps xmm0,xmm12
	{evex} vmovaps xmm12,xmm0
	{evex} vmovaps xmm12,xmm13
	
	{evex} vmovaps ymm0,ymm0
	{evex} vmovaps ymm0,ymm4
	{evex} vmovaps ymm4,ymm2
	{evex} vmovaps ymm0,ymm12
	{evex} vmovaps ymm12,ymm0
	{evex} vmovaps ymm12,ymm13	
	
	comment $
	; REG/MEM
	vmovaps xmm0,[rdi]
	vmovaps xmm2,[rdi+rax]
	vmovaps xmm2,[rsi+rbx*2]
	vmovaps xmm4,[rbp-0x04]
	vmovaps xmm5,[rsp]
	vmovaps xmm3,[rdi+r12]
	vmovaps xmm6,myVector
	vmovaps xmm7,XMMWORD PTR myVector
	
	vmovaps xmm8,[rdi]
	vmovaps xmm9,[rdi+rax]
	vmovaps xmm9,[rsi+rbx*2]
	vmovaps xmm10,[rbp-0x04]
	vmovaps xmm15,[rsp]
	vmovaps xmm13,[rdi+r11]
	vmovaps xmm11,myVector
	vmovaps xmm12,XMMWORD PTR myVector

	vmovaps ymm0,[rdi]
	vmovaps ymm2,[rdi+rax]
	vmovaps ymm2,[rsi+rbx*2]
	vmovaps ymm4,[rbp-0x04]
	vmovaps ymm5,[rsp]
	vmovaps ymm6,myVector
	vmovaps ymm7,YMMWORD PTR myVector
	
	vmovaps ymm8,[rdi]
	vmovaps ymm9,[rdi+rax]
	vmovaps ymm9,[rsi+rbx*2]
	vmovaps ymm10,[rbp-0x04]
	vmovaps ymm15,[rsp]
	vmovaps ymm11,myVector
	vmovaps ymm12,YMMWORD PTR myVector	
	
	; MEM/REG
	vmovaps [rdi],xmm0
	vmovaps [rdi+rax],xmm2
	vmovaps [rsi+rbx*2],xmm2
	vmovaps [rbp-0x04],xmm4
	vmovaps [rdi+r12],xmm3
	vmovaps [rsp],xmm5
	vmovaps myVector,xmm6
	vmovaps XMMWORD PTR myVector,xmm7
	
	vmovaps [rdi],xmm8
	vmovaps [rdi+rax],xmm9
	vmovaps [rsi+rbx*2],xmm9
	vmovaps [rbp-0x04],xmm10
	vmovaps [rsi+r11],xmm13
	vmovaps [rsp],xmm15
	vmovaps myVector,xmm11
	vmovaps XMMWORD PTR myVector,xmm12

	vmovaps [rdi],ymm0
	vmovaps [rdi+rax],ymm2
	vmovaps [rsi+rbx*2],ymm2
	vmovaps [rbp-0x04],ymm4
	vmovaps [rsp],ymm5
	vmovaps myVector,ymm6
	vmovaps YMMWORD PTR myVector,ymm7
	
	vmovaps [rdi],ymm8
	vmovaps [rdi+rax],ymm9
	vmovaps [rsi+rbx*2],ymm9
	vmovaps [rbp-0x04],ymm10
	vmovaps [rsp],ymm15
	vmovaps myVector,ymm11
	vmovaps XMMWORD PTR myVector,ymm12
	$
.data

align 32
myVector __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>