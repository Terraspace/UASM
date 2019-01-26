
option flat:1

.code

	use64
	
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

	;REG/REG
	vmulps xmm0,xmm1,xmm2
	vmulps xmm0,xmm0,xmm0
	vmulps xmm8,xmm1,xmm2
	vmulps xmm0,xmm8,xmm2
	vmulps xmm2,xmm4,xmm10
	vmulps xmm8,xmm9,xmm10

	; 3 opnd forms with implicit NDS
	;------------------------------------------
	;REG/REG
	vmulps xmm0,xmm2
	vmulps xmm0,xmm0
	vmulps xmm8,xmm2
	vmulps xmm0,xmm2
	vmulps xmm2,xmm10
	vmulps xmm8,xmm10

	; 2 opnd forms with imm
	;------------------------------------------
	vpshufd xmm0, xmm0, 1
	
	; 3 opnd with imm
	;------------------------------------------
	vmpsadbw xmm0, xmm1, xmm2, 1
		
	; 3 opnd with imm and implicit NDS
	;------------------------------------------
	vmpsadbw xmm0, xmm2, 1
	
	; VSIB addressing
	;------------------------------------------
	vgatherdps xmm0, [rdi+xmm1], xmm2
	vgatherdps xmm0, [xmm1], xmm2
	vgatherdps xmm0, [rax+xmm1*4], xmm2
	vgatherdps xmm0, [r8+xmm1*4], xmm2
	
	; 4 opnd form
	vblendvps
	
.data

align 32
myVector __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>