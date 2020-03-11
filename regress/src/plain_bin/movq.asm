
    .x64
    .model flat
    .code

    option evex:1

	; this should err
	;MOVQ XMM0, EAX
	
	;0: 48 0f 6e c0 
	movq mm0,rax
	
	;4: 49 0f 6e c1 
	movq mm0,r9

	movd mm0,eax
	movd eax,mm0
	movq rax,mm0
	;----
	movd xmm0,eax
	movq xmm0,rax
	movd eax,xmm0
	movd r9d,xmm0
	movq rax,xmm0
	movq r9,xmm0
	
	vmovd xmm0,eax
	vmovd xmm0,r9d
	vmovq xmm0,rax
	vmovd eax,xmm0
	vmovd r9d,xmm0
	vmovq rax,xmm0
	vmovq r9,xmm0
	
	
    end
