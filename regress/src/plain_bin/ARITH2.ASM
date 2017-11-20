
;--- arithmetic instructions
;--- second operand is immediate

	.386
	.model flat

	.code

vb	label byte
vw	label word
vd	label dword

op macro instr
;;
	instr al,80h
	instr cl,80h
	instr vb,80h
;;
	instr ax,7fh
	instr cx,7fh
	instr vw,7fh
	instr ax,80h
	instr cx,80h
	instr vw,80h
;;
	instr eax,7fh
	instr ecx,7fh
	instr vd,7fh
	instr eax,80h
	instr ecx,80h
	instr vd,80h
	endm

	for x,<add,or,adc,sbb,and,sub,xor,cmp>
	op x
	endm

	end
