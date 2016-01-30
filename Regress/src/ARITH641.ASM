
ifdef __JWASM__
	.x64
	.model flat
endif

	.code

vb	db 0
vw	dw 0
vd	dd 0
vq	dq 0

op macro instr
;;
	instr al,cl
	instr al,1
	instr al,vb
	instr vb,1
	instr vb,al
;;
	instr ax,cx
	instr ax,1
	instr ax,vw
	instr ax,1234h
	instr bx,1234h
	instr vw,1
	instr vw,1234h
	instr vw,ax
;;
	instr eax,ecx
	instr eax,1
	instr eax,vd
	instr eax,1234h
	instr ebx,1234h
	instr vd,1
	instr vd,1234h
	instr vd,eax
;;
	instr rax,rcx
	instr rax,1
	instr rax,vq
	instr rax,1234h
	instr rbx,1234h
	instr vq,1
	instr vq,1234h
	instr vq,rax
	endm

	for x,<add,or,adc,sbb,and,sub,xor,cmp>
	op x
	endm

	end
