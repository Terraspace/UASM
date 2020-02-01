
    .x64
    .model flat
    .code

    option evex:1

	; this should err
	MOVQ XMM0, EAX
	
	;0: 48 0f 6e c0 
	movq mm0,rax
	
	;4: 49 0f 6e c1 
	movq mm0,r9

    end
