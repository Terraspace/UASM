
option flat:1

.code

	use32

	; 4 opnd form
	;------------------------------------------
	vblendvps xmm1,xmm2,xmm3,xmm4
	vblendvps xmm1,xmm2,myVector,xmm4
	vblendvps xmm1,xmm2,[edi],xmm4
	vblendvps xmm1,xmm2,[edi+eax*2],xmm4
	vblendvps xmm2,xmm1,xmm3,xmm4
	vblendvps xmm1,xmm2,myVector,xmm4
	vblendvps xmm3,xmm2,[edi],xmm4
	vblendvps xmm2,xmm3,[edi+eax*2],xmm1

	vblendvps ymm1,ymm2,ymm3,ymm4
	vblendvps ymm1,ymm2,myVector,ymm4
	vblendvps ymm1,ymm2,[edi],ymm4
	vblendvps ymm1,ymm2,[edi+eax*2],ymm4
	vblendvps ymm2,ymm1,ymm3,ymm4
	vblendvps ymm1,ymm2,myVector,ymm4
	vblendvps ymm3,ymm2,[edi],ymm4
	vblendvps ymm2,ymm3,[edi+eax*2],ymm1
	
	; 3 opnd with imm and implicit NDS
	;------------------------------------------
	vmpsadbw xmm0, xmm2, 1
	vmpsadbw xmm0, xmm2, 2
	vmpsadbw ymm0, ymm2, 1
	vmpsadbw ymm0, ymm2, 2
	
	; 3 opnd with imm
	;------------------------------------------
	vmpsadbw xmm0, xmm1, xmm2, 1
	vmpsadbw xmm0, xmm1, myVector, 1
	vmpsadbw xmm1, xmm2, [edi], 3
	vmpsadbw xmm0, xmm1, [edi+eax], 4
	vmpsadbw xmm1, xmm2, [ebp+eax*2], 5

	vmpsadbw ymm0, ymm1, ymm2, 1
	vmpsadbw ymm0, ymm1, myVector, 1
	vmpsadbw ymm1, ymm2, [edi], 3
	vmpsadbw ymm0, ymm1, [edi+eax], 4
	vmpsadbw ymm1, ymm2, [ebp+eax*2], 5
	
	; VSIB addressing
	;------------------------------------------
	vgatherdps xmm0, [xmm1], xmm2
	vgatherdps xmm0, [edi+xmm1], xmm2
	vgatherdps xmm0, [eax+xmm1*4], xmm2
	vgatherdps xmm0, [ebp+xmm1*4], xmm2

	vgatherdps ymm0, [ymm1], ymm2
	vgatherdps ymm0, [edi+ymm1], ymm2
	vgatherdps ymm0, [eax+ymm1*4], ymm2
	vgatherdps ymm0, [ebp+ymm1*4], ymm2
	
	; 2 opnd forms with imm
	;------------------------------------------
	vpshufd xmm0, xmm0, 1
	vpshufd xmm0, xmm3, 0
	vpshufd xmm0, xmm2, 0xff
	vpshufd xmm1, xmm3, 2
	vpshufd xmm1, xmm2, 10

	vpshufd ymm0, ymm0, 1
	vpshufd ymm0, ymm3, 0
	vpshufd ymm0, ymm2, 0xff
	vpshufd ymm2, ymm3, 2
	vpshufd ymm3, ymm3, 10
	
	vpshufd xmm0, [edi], 1
	vpshufd xmm2, [edi+eax*2], 3
	vpshufd xmm3, [esp], 4
	vpshufd xmm4, [ebp-4], 5

	vpshufd xmm0, myVector, 1
	
	; 3 opnd forms with implicit NDS
	; This is common for users who just add v to 
	; existing sse instructions
	;------------------------------------------
	;REG/REG
	vmulps xmm0,xmm2
	vmulps xmm0,xmm0
	vmulps xmm0,xmm2
	vmulps xmm2,xmm3

	vmulps ymm0,ymm2
	vmulps ymm0,ymm0
	vmulps ymm2,ymm3
	
	; 3 opnd forms
	;------------------------------------------
	;REG/MEM
	vmulps xmm0,xmm1,[edi+eax*2]
	vmulps xmm0,xmm1,myVector
	vmulps xmm0,xmm1,[edi]
	vmulps ymm0,ymm1,[edi+eax*2]
	vmulps ymm0,ymm1,myVector
	vmulps ymm0,ymm1,[edi]
	
	;REG/REG
	vmulps xmm0,xmm1,xmm2
	vmulps xmm0,xmm0,xmm0
	vmulps xmm2,xmm1,xmm3

	vmulps ymm0,ymm1,ymm2
	vmulps ymm0,ymm0,ymm0
	vmulps ymm3,ymm1,ymm2
	
.data

align 32
myVector __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>