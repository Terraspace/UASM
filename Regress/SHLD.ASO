
	.386
	.model small, stdcall

	.data
vw	dw 0
vb	db 0
	.code

;--- prior to v2.05, error was "invalid SHLD/SHRD format"
	shld eax,ecx,bx
;--- prior to v2.05, more than 3 operands was accepted
	shld eax,ecx,1,2
;--- prior to v2.05, 2 operands only was accepted!
	shld eax,ecx
;--- prior to v2.05, different size of (register) operands was accepted!
	shld eax,bx,1
	shld vb,cx,1
	shld vw,ecx,1
;--- last operand must be cl or byte constant
	shld vw,bx,256

	end
