
;--- arithmetic instructions
;--- see arith2.asm for immediate as second operand
;--- note that jwasm's code generation is to match Masm v8. 
;--- Masm v6 encodes the cmp instruction differently if 
;--- operands are byte registers.

	.386
	.model flat

	.code

vb	label byte
vw	label word
vd	label dword

op macro instr
;;
	instr al,cl
	instr al,vb
	instr bl,cl
	instr bl,vb
	instr vb,al
	instr vb,bl
;;
	instr ax,cx
	instr ax,vw
	instr bx,cx
	instr bx,vw
	instr vw,ax
	instr vw,bx
;;
	instr eax,ecx
	instr eax,vd
	instr ebx,ecx
	instr ebx,vd
	instr vd,eax
	instr vd,ebx
	endm

	for x,<add,or,adc,sbb,and,sub,xor,cmp>
	op x
	endm

	end
