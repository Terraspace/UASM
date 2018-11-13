
	.686p
	.mmx
	.xmm
    .model flat,stdcall
	
    option evex:1
    
	.code
	
	;32bit AVX512
	
	VPGATHERDD zmm1{k1}, [edx+zmm0]
	vmovdqu32 ZMMWORD PTR [edi+eax], zmm1
	vgatherpf0dpd [edi+ymm1*8+0x7b] {k1}
	
	;reported by AW 01-11-2018

    end