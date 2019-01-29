
option flat:1

.code

	use64

	; 4 opnd form
	;------------------------------------------
	vblendvps xmm1,xmm2,xmm3,xmm4
	vblendvps xmm1,xmm2,myVector,xmm4
	vblendvps xmm1,xmm2,[rdi],xmm4
	vblendvps xmm1,xmm2,[edi],xmm4
	vblendvps xmm1,xmm2,[edi+eax*2],xmm4
	vblendvps xmm1,xmm2,[rdi+rax*2],xmm4
	
	vblendvps xmm2,xmm8,xmm3,xmm4
	vblendvps xmm1,xmm2,xmm3,xmm8
	vblendvps xmm9,xmm2,xmm3,xmm4
	vblendvps xmm3,xmm2,xmm10,xmm8
	vblendvps xmm9,xmm2,myVector,xmm4
	vblendvps xmm9,xmm2,[rdi],xmm4
	vblendvps xmm9,xmm9,[rdi+rax*2],xmm11
	
	vblendvps ymm1,ymm2,ymm3,ymm4
	vblendvps ymm1,ymm2,myVector,ymm4
	vblendvps ymm1,ymm2,[rdi],ymm4
	vblendvps ymm1,ymm2,[edi],ymm4
	vblendvps ymm1,ymm2,[edi+eax*2],ymm4
	vblendvps ymm1,ymm2,[rdi+rax*2],ymm4
	
	; 3 opnd with imm and implicit NDS
	;------------------------------------------
	vmpsadbw xmm0, xmm2, 1
	vmpsadbw xmm0, xmm2, 2
	vmpsadbw xmm9, xmm2, 3
	vmpsadbw xmm0, xmm9, 4
	vmpsadbw xmm10, xmm11, 5

	vmpsadbw ymm0, ymm2, 1
	vmpsadbw ymm0, ymm2, 2
	vmpsadbw ymm9, ymm2, 3
	vmpsadbw ymm0, ymm9, 4
	vmpsadbw ymm10, ymm11, 5
	
	; 3 opnd with imm
	;------------------------------------------
	vmpsadbw xmm0, xmm1, xmm2, 1
	vmpsadbw xmm0, xmm8, xmm2, 2
	vmpsadbw xmm9, xmm8, xmm2, 3
	vmpsadbw xmm0, xmm8, xmm9, 4
	vmpsadbw xmm10, xmm8, xmm11, 5
	vmpsadbw xmm0, xmm1, myVector, 1
	vmpsadbw xmm0, xmm8, [rdi], 2
	vmpsadbw xmm9, xmm8, [edi], 3
	vmpsadbw xmm0, xmm8, [rdi+rax], 4
	vmpsadbw xmm10, xmm8, [r8+rax*2], 5

	vmpsadbw ymm0, ymm1, ymm2, 1
	vmpsadbw ymm0, ymm8, ymm2, 2
	vmpsadbw ymm9, ymm8, ymm2, 3
	vmpsadbw ymm0, ymm8, ymm9, 4
	vmpsadbw ymm10, ymm8, ymm11, 5
	vmpsadbw ymm0, ymm1, myVector, 1
	vmpsadbw ymm0, ymm8, [rdi], 2
	vmpsadbw ymm9, ymm8, [edi], 3
	vmpsadbw ymm0, ymm8, [rdi+rax], 4
	vmpsadbw ymm10, ymm8, [r8+rax*2], 5
	
	; VSIB addressing
	;------------------------------------------
	vgatherdps xmm0, [xmm1], xmm2
	vgatherdps xmm0, [rdi+xmm1], xmm2
	vgatherdps xmm0, [rax+xmm1*4], xmm2
	vgatherdps xmm0, [r8+xmm1*4], xmm2
	vgatherdps xmm0, [r8+xmm9*4], xmm2

	vgatherdps ymm0, [ymm1], ymm2
	vgatherdps ymm0, [rdi+ymm1], ymm2
	vgatherdps ymm0, [rax+ymm1*4], ymm2
	vgatherdps ymm0, [r8+ymm1*4], ymm2
	vgatherdps ymm0, [r8+ymm9*4], ymm2
	
	; 2 opnd forms with imm
	;------------------------------------------
	vpshufd xmm0, xmm0, 1
	vpshufd xmm0, xmm3, 0
	vpshufd xmm0, xmm8, 0xff
	vpshufd xmm8, xmm3, 2
	vpshufd xmm8, xmm9, 10

	vpshufd ymm0, ymm0, 1
	vpshufd ymm0, ymm3, 0
	vpshufd ymm0, ymm8, 0xff
	vpshufd ymm8, ymm3, 2
	vpshufd ymm8, ymm9, 10
	
	vpshufd xmm0, [rdi], 1
	vpshufd xmm2, [rdi+rax*2], 3
	vpshufd xmm3, [rsp], 4
	vpshufd xmm4, [rbp-4], 5
	vpshufd xmm8, [rdi], 1
	vpshufd xmm9, [rdi+rax*2], 2
	vpshufd xmm10, [rsp], 3
	vpshufd xmm11, [rbp-4], 4	
	
	vpshufd xmm0, myVector, 1
	vpshufd xmm9, myVector, 2
	
	; 3 opnd forms with implicit NDS
	; This is common for users who just add v to 
	; existing sse instructions
	;------------------------------------------
	;REG/REG
	vmulps xmm0,xmm2
	vmulps xmm0,xmm0
	vmulps xmm8,xmm2
	vmulps xmm0,xmm2
	vmulps xmm2,xmm10
	vmulps xmm8,xmm10

	vmulps ymm0,ymm2
	vmulps ymm0,ymm0
	vmulps ymm8,ymm2
	vmulps ymm0,ymm2
	vmulps ymm2,ymm10
	vmulps ymm8,ymm10
	
	; 3 opnd forms
	;------------------------------------------
	;REG/MEM
	vmulps xmm0,xmm1,[rdi+rax*2]
	vmulps xmm0,xmm8,[rdi+rax*2]
	vmulps xmm8,xmm9,[rdi+rax*2]
	
	vmulps xmm0,xmm1,myVector
	vmulps xmm0,xmm8,myVector
	vmulps xmm8,xmm9,myVector

	vmulps xmm0,xmm1,[rdi]
	vmulps xmm0,xmm8,[rdi]
	vmulps xmm8,xmm9,[rdi]

	vmulps ymm0,ymm1,[rdi+rax*2]
	vmulps ymm0,ymm8,[rdi+rax*2]
	vmulps ymm8,ymm9,[rdi+rax*2]
	
	vmulps ymm0,ymm1,myVector
	vmulps ymm0,ymm8,myVector
	vmulps ymm8,ymm9,myVector

	vmulps ymm0,ymm1,[rdi]
	vmulps ymm0,ymm8,[rdi]
	vmulps ymm8,ymm9,[rdi]
	
	;REG/REG
	vmulps xmm0,xmm1,xmm2
	vmulps xmm0,xmm0,xmm0
	vmulps xmm8,xmm1,xmm2
	vmulps xmm0,xmm8,xmm2
	vmulps xmm2,xmm4,xmm10
	vmulps xmm8,xmm9,xmm10

	vmulps ymm0,ymm1,ymm2
	vmulps ymm0,ymm0,ymm0
	vmulps ymm8,ymm1,ymm2
	vmulps ymm0,ymm8,ymm2
	vmulps ymm2,ymm4,ymm10
	vmulps ymm8,ymm9,ymm10
	
.data

align 32
myVector __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>