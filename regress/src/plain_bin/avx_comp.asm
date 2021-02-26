
    .x64
    .model flat
    .code

    option evex:1

	vcvtsi2ss xmm10,xmm1,DWORD PTR [rbx+rax*4]
	
	;0: c5 72 2a 14 83 vcvtsi2ss xmm10,xmm1,DWORD PTR [rbx+rax*4]
	;incorrectly encodes with a SIB byte of 0xf0
	
    end
