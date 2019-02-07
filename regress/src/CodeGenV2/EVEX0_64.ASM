
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
	
	; REG/MEM
	vmovaps xmm20{z},[rdi]
	vmovaps xmm22,[rdi+rax]
	vmovaps xmm22{k2},[rsi+rbx*2]
	vmovaps xmm24,[rbp-0x04]
	vmovaps xmm25,[rsp]
	vmovaps xmm23{k5}{z},[rdi+r12]
	vmovaps xmm26,myVector
	vmovaps xmm27,XMMWORD PTR myVector

	vmovaps ymm20,[rdi]
	vmovaps ymm22{z},[rdi+rax]
	vmovaps ymm22,[rsi+rbx*2]
	vmovaps ymm24,[rbp-0x04]
	vmovaps ymm25{k3}{z},[rsp]
	vmovaps ymm23,[rdi+r12]
	vmovaps ymm26,myVector
	vmovaps ymm27,YMMWORD PTR myVector

	vmovaps zmm20{z}{k1},[rdi]
	vmovaps zmm22,[rdi+rax]
	vmovaps zmm22,[rsi+rbx*2]
	vmovaps zmm24,[rbp-0x04]
	vmovaps zmm25,[rsp]
	vmovaps zmm23{k2},[rdi+r12]
	vmovaps zmm26,myVector
	vmovaps zmm27,ZMMWORD PTR myVector

	{evex} vmovaps xmm0,[rdi]
	{evex} vmovaps xmm2,[rdi+rax]
	{evex} vmovaps xmm2,[rsi+rbx*2]
	{evex} vmovaps xmm4,[rbp-0x04]
	{evex} vmovaps xmm5,[rsp]
	{evex} vmovaps xmm3,[rdi+r12]
	{evex} vmovaps xmm6,myVector
	{evex} vmovaps xmm7,XMMWORD PTR myVector
	
	{evex} vmovaps xmm8,[rdi]
	{evex} vmovaps xmm9{k2}{z},[rdi+rax]
	{evex} vmovaps xmm9,[rsi+rbx*2]
	{evex} vmovaps xmm10,[rbp-0x04]
	{evex} vmovaps xmm15,[rsp]
	{evex} vmovaps xmm13,[rdi+r11]
	{evex} vmovaps xmm11,myVector
	{evex} vmovaps xmm12,XMMWORD PTR myVector

	{evex} vmovaps ymm0,[rdi]
	{evex} vmovaps ymm2,[rdi+rax]
	{evex} vmovaps ymm2,[rsi+rbx*2]
	{evex} vmovaps ymm4{k3},[rbp-0x04]
	{evex} vmovaps ymm5,[rsp]
	{evex} vmovaps ymm6,myVector
	{evex} vmovaps ymm7,YMMWORD PTR myVector
	
	{evex} vmovaps ymm8,[rdi]
	{evex} vmovaps ymm9,[rdi+rax]
	{evex} vmovaps ymm9,[rsi+rbx*2]
	{evex} vmovaps ymm10,[rbp-0x04]
	{evex} vmovaps ymm15,[rsp]
	{evex} vmovaps ymm11,myVector
	{evex} vmovaps ymm12,YMMWORD PTR myVector	
	
	; MEM/REG

	{evex} vmovaps [rdi],xmm0
	{evex} vmovaps [rdi+rax],xmm2
	{evex} vmovaps [rsi+rbx*2],xmm2
	{evex} vmovaps [rbp-0x04],xmm4
	{evex} vmovaps [rdi+r12],xmm3
	{evex} vmovaps [rsp],xmm5
	{evex} vmovaps myVector,xmm6
	{evex} vmovaps XMMWORD PTR myVector,xmm7
	
	{evex} vmovaps [rdi]{k2},xmm8
	{evex} vmovaps [rdi+rax],xmm9
	{evex} vmovaps [rsi+rbx*2],xmm9
	{evex} vmovaps [rbp-0x04],xmm10
	{evex} vmovaps [rsi+r11],xmm13
	{evex} vmovaps [rsp],xmm15
	{evex} vmovaps myVector,xmm11
	{evex} vmovaps XMMWORD PTR myVector,xmm12

	{evex} vmovaps [rdi],ymm0
	{evex} vmovaps [rdi+rax],ymm2
	{evex} vmovaps [rsi+rbx*2],ymm2
	{evex} vmovaps [rbp-0x04],ymm4
	{evex} vmovaps [rsp],ymm5
	{evex} vmovaps myVector,ymm6
	{evex} vmovaps YMMWORD PTR myVector,ymm7
	
	{evex} vmovaps [rdi],ymm8
	{evex} vmovaps [rdi+rax],ymm9
	{evex} vmovaps [rsi+rbx*2],ymm9
	{evex} vmovaps [rbp-0x04],ymm10
	{evex} vmovaps [rsp],ymm15
	{evex} vmovaps myVector,ymm11
	{evex} vmovaps XMMWORD PTR myVector,ymm12
	
	vmovaps [rdi]{k1},xmm18
	vmovaps [rdi+rax],xmm19
	vmovaps [rsi+rbx*2],xmm19
	vmovaps [rbp-0x04],xmm20
	vmovaps [rsi+r11],xmm23
	vmovaps [rsp],xmm25
	vmovaps myVector{k1},xmm21
	vmovaps XMMWORD PTR myVector,xmm22

	vmovaps [rdi],ymm20
	vmovaps [rdi+rax],ymm22
	vmovaps [rsi+rbx*2],ymm22
	vmovaps [rbp-0x04],ymm24
	vmovaps [rsp],ymm25
	vmovaps myVector,ymm26
	vmovaps YMMWORD PTR myVector,ymm27
	
	vmovaps [rdi]{k1},zmm28
	vmovaps [rdi+rax],zmm29
	vmovaps [rsi+rbx*2]{k2},zmm29
	vmovaps [rbp-0x04],zmm20
	vmovaps [rsp],zmm25
	vmovaps myVector,zmm21
	vmovaps XMMWORD PTR myVector,zmm22	

.data

align 32
myVector __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>