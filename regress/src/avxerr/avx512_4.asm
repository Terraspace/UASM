
    .x64
    .model flat
    option evex:1
    .code

	vmulpd zmm1, [rax]

	;vmulpd zmm1, [rax]
	;assembles as
	;vmulpd zmm1, zmm0, [rax]
	;it should raise an error instead

	vaddpd zmm12, [rsi+64], zmm30
	;should raise error
	
    end