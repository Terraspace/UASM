
;--- instructions which accept multiple memory operand sizes
;--- for the first operand.

	.286
	.model small
	.686

	.code

;--- PUSH/POP is accepted by Masm without size
	push [bx]
	pop  [bx]

	call [bx]	;error - in pass 2
	jmp  [bx]	;error - in pass 2

	div  [bx]
	idiv [bx]
	mul  [bx]
	neg  [bx]
	not  [bx]
	imul [bx]

	mov  [bx],1	;Masm rejects, jwasm warns only

	end
