
	.686p
	.mmx
	.xmm
    .model flat,stdcall
	
    option evex:1
    
	.code

	VPGATHERDD zmm1{k1}, [edx+zmm0]
	vmovdqu32 ZMMWORD PTR [edi+eax], zmm1

	;reported by AW 01-11-2018

    end