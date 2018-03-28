
    .x64
    .model flat
    option evex:1
    .code

	vxorpd zmm1, [rsi]
	;it should raise an error ... reported by gwoltman 28-3-2018

    end