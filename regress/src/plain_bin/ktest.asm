;
; EVEX KTEST
;
    .x64
    .model flat
    .code

	ktestb k1,k1
	ktestw k1,k2
	ktestd k1,k3
	ktestq k1,k4
	
    end
