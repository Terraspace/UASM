;
; CLMUL (including pseudo-op forms)
;
    .x64
    .model flat
    .code

    option evex:1
	
pclmulqdq xmm1, xmmword ptr [rax], 0x5  
pclmulqdq xmm1, xmm2, 0x5  
vpclmulqdq xmm1, xmm2, xmm3, 0x5  
vpclmulqdq xmm1, xmm2, xmmword ptr [rax], 0x5 

; PSEUDO-OP FORMS
PCLMULLQLQDQ xmm1, xmm2
PCLMULHQLQDQ xmm1, xmm2
PCLMULLQHQDQ xmm1, xmm2
PCLMULHQHQDQ xmm1, xmm2
VPCLMULLQLQDQ xmm1, xmm2,xmm3
VPCLMULHQLQDQ xmm1, xmm2,xmm3
VPCLMULLQHQDQ xmm1, xmm2,xmm3
VPCLMULHQHQDQ xmm1, xmm2,xmm3

end
