
option flat:1

.code

	use32
	
	;REG/REG
	vmovaps xmm0,xmm0
	vmovaps xmm0,xmm4
	vmovaps xmm4,xmm2
	
	vmovaps ymm0,ymm0
	vmovaps ymm0,ymm4
	vmovaps ymm4,ymm2
	
	; REG/MEM
	vmovaps xmm0,[edi]
	vmovaps xmm2,[edi+eax]
	vmovaps xmm2,[esi+ebx*2]
	vmovaps xmm4,[ebp-0x04]
	vmovaps xmm5,[esp]
	vmovaps xmm3,[edi+eax]
	vmovaps xmm6,myVector
	vmovaps xmm7,XMMWORD PTR myVector
	
	vmovaps ymm0,[edi]
	vmovaps ymm2,[edi+eax]
	vmovaps ymm2,[esi+ebx*2]
	vmovaps ymm4,[ebp-0x04]
	vmovaps ymm5,[esp]
	vmovaps ymm6,myVector
	vmovaps ymm7,YMMWORD PTR myVector
	
	; MEM/REG
	vmovaps [edi],xmm0
	vmovaps [edi+eax],xmm2
	vmovaps [esi+ebx*2],xmm2
	vmovaps [ebp-0x04],xmm4
	vmovaps [edi+ebx],xmm3
	vmovaps [esp],xmm5
	vmovaps myVector,xmm6
	vmovaps XMMWORD PTR myVector,xmm7
	
	vmovaps [edi],ymm0
	vmovaps [edi+eax],ymm2
	vmovaps [esi+ebx*2],ymm2
	vmovaps [ebp-0x04],ymm4
	vmovaps [esp],ymm5
	vmovaps myVector,ymm6
	vmovaps YMMWORD PTR myVector,ymm7
	
.data

align 32
myVector __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>