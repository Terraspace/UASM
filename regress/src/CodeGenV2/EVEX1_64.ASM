
option flat:1
option evex:1

.code

	use64

	vmulps zmm20{k2}{z}, zmm0, [rdi]{1to16}
	vmulps zmm10{k2}{z}, zmm2, [rbp+4]{1to16}
	vmulps zmm10{k2}{z}, zmm2, [rbp+16]{1to16}
	vmulps zmm10{k2}{z}, zmm2, [rbp+25]{1to16}
	vmulps zmm2{k3}, zmm20, [rdi+rax*4]{1to16}
	
	vmulps zmm0, zmm1, zmm2
	vmulps zmm8{z}, zmm0, zmm20
	vmulps zmm9{k1}, zmm10, zmm21
	vmulps zmm20{k2}{z}, zmm0, zmm7
	vmulps zmm20{k2}{z}, zmm0, zmm7, {rd-sae}
	vmulps zmm20{k3}{z}, zmm20, zmm7, {rn-sae}
	vmulps zmm10{k4}, zmm20, zmm7, {ru-sae}
	vmulps zmm10{k5}{z}, zmm20, zmm7, {rz-sae}

	vmulps zmm20{k2}{z}, zmm0, [rdi]{1to16}
	vmulps zmm10{k2}{z}, zmm2, [rbp+4]{1to16}
	vmulps zmm10{k2}{z}, zmm2, [rbp+16]{1to16}
	vmulps zmm10{k2}{z}, zmm2, [rbp+25]{1to16}
	vmulps zmm2{k3}, zmm20, [rdi+rax*4]{1to16}

	;------------------------------------------
	;REG/MEM
	{evex} vmulps xmm0,xmm1,[rdi+rax*2]
	{evex} vmulps xmm0,xmm8,[rdi+rax*2]
	{evex} vmulps xmm8,xmm9,[rdi+rax*2]
	
	{evex} vmulps xmm0,xmm1,myVector
	{evex} vmulps xmm0,xmm8,myVector
	{evex} vmulps xmm8,xmm9,myVector

	{evex} vmulps xmm0,xmm1,[rdi]
	{evex} vmulps xmm0,xmm8,[rdi]
	{evex} vmulps xmm8,xmm9,[rdi]

	{evex} vmulps ymm0,ymm1,[rdi+rax*2]
	{evex} vmulps ymm0,ymm8,[rdi+rax*2]
	{evex} vmulps ymm8,ymm9,[rdi+rax*2]
	
	{evex} vmulps ymm0,ymm1,myVector
	{evex} vmulps ymm0,ymm8,myVector
	{evex} vmulps ymm8,ymm9,myVector

	{evex} vmulps ymm0,ymm1,[rdi]
	{evex} vmulps ymm0,ymm8,[rdi]
	{evex} vmulps ymm8,ymm9,[rdi]
	
	;REG/REG
	{evex} vmulps xmm0,xmm1,xmm2
	{evex} vmulps xmm0,xmm0,xmm0
	{evex} vmulps xmm8,xmm1,xmm2
	{evex} vmulps xmm0,xmm8,xmm2
	{evex} vmulps xmm2,xmm4,xmm10
	{evex} vmulps xmm8,xmm9,xmm10

	{evex} vmulps ymm0,ymm1,ymm2
	{evex} vmulps ymm0,ymm0,ymm0
	{evex} vmulps ymm8,ymm1,ymm2
	{evex} vmulps ymm0,ymm8,ymm2
	{evex} vmulps ymm2,ymm4,ymm10
	{evex} vmulps ymm8,ymm9,ymm10

	; 2 opnd forms with imm
	;------------------------------------------
	vpshufd zmm0, zmm0, 1
	vpshufd zmm0{k1}, zmm3, 0
	vpshufd zmm0{z}, zmm8, 0xff
	vpshufd zmm8, zmm3, 2
	vpshufd zmm8{k3}{z}, zmm9, 10
	vpshufd zmm9, zmm19, 10
	vpshufd zmm18, zmm23, 11
	vpshufd zmm0{k3}{z}, [rdi]{1to16}, 1
	vpshufd zmm2, [rdi+rax*2], 3
	vpshufd zmm9{z}, [rsp], 4
	vpshufd zmm15, [rbp-4], 5
	vpshufd zmm18, [rdi]{1to16}, 1
	vpshufd zmm29{k2}, [rdi+rax*2], 2
	vpshufd zmm10, [rsp], 3
	vpshufd zmm11, [rbp-4], 4	
	
	{evex} vpshufd xmm0, xmm0, 1
	{evex} vpshufd xmm0, xmm3, 0
	{evex} vpshufd xmm0, xmm8, 0xff
	{evex} vpshufd xmm8, xmm3, 2
	{evex} vpshufd xmm8, xmm9, 10

	{evex} vpshufd ymm0, ymm0, 1
	{evex} vpshufd ymm0, ymm3, 0
	{evex} vpshufd ymm0, ymm8, 0xff
	{evex} vpshufd ymm8, ymm3, 2
	{evex} vpshufd ymm8, ymm9, 10
	
	{evex} vpshufd xmm0, [rdi], 1
	{evex} vpshufd xmm2, [rdi+rax*2], 3
	{evex} vpshufd xmm3, [rsp], 4
	{evex} vpshufd xmm4, [rbp-4], 5
	{evex} vpshufd xmm8, [rdi], 1
	{evex} vpshufd xmm9, [rdi+rax*2], 2
	{evex} vpshufd xmm10, [rsp], 3
	{evex} vpshufd xmm11, [rbp-4], 4	
	
	{evex} vpshufd xmm0, myVector, 1
	{evex} vpshufd xmm9, myVector, 2

	
	; VSIB addressing
	;------------------------------------------
	vgatherdps zmm30{k1}, [r9+zmm31*1+0x100]
	vgatherdps zmm30{k1},ZMMWORD PTR [r14+zmm31*8+0x7b]
	vgatherdps zmm0{k1}, [zmm1]
	vgatherdps zmm9{k2}, [rax+zmm21*4]

	vgatherdps zmm0{k1}, [zmm1]
	vgatherdps zmm2{k3}, [rdi+zmm1]
	vgatherdps zmm9{k2}, [rax+zmm21*4]
	vgatherdps zmm17{k1}, [r8+zmm11*4]
	vgatherdps zmm22{k4}, [r8+zmm9*4]

	vgatherdps xmm0{k1}, [xmm1]
	vgatherdps xmm2{k3}, [rdi+xmm1]
	vgatherdps xmm9{k2}, [rax+xmm21*4]
	vgatherdps xmm17{k1}, [r8+xmm11*4]
	vgatherdps xmm22{k4}, [r8+xmm9*4]

	vgatherdps ymm0{k1}, [ymm1]
	vgatherdps ymm2{k3}, [rdi+ymm1]
	vgatherdps ymm9{k2}, [rax+ymm21*4]
	vgatherdps ymm17{k1}, [r8+ymm11*4]
	vgatherdps ymm22{k4}, [r8+ymm9*4]
	
.data

align 32
myVector __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>