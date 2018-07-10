
    .x64
    .model flat
    option evex:1
    .code

	vgatherdps zmm2 {k1}, [zmm1]   ;62 F2 7D 49 92 14 0D 00 00 00 00'  UASM assembles wrong B2 instead F2
	;62 B2 7D 49 92 94 0D 00 00 00 00 

	;vgatherdps            zmm2, k1, zmmword ptr [rbp+zmm9]

    end