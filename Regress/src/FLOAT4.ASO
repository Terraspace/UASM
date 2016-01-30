
;--- float instructions which accept multiple memory operand sizes
;--- for the first operand.


	.286
	.model small
	option casemap:none
	.686
	.xmm

	.data

m08	label byte
m16	label word
m32	label dword
m48	label fword
m64	label qword
m80	label tbyte

	.code

	fcom  [bx]
	fcomp [bx]

	fadd  [bx]
	fdiv  [bx]
	fdivr [bx]
	fmul  [bx]
	fsub  [bx]
	fsubr [bx]

	fiadd  [bx]
	ficom  [bx]
	ficomp [bx]
	fidiv  [bx]
	fidivr [bx]
	fimul  [bx]
	fisub  [bx]
	fisubr [bx]

	fild  [bx]
	fistp [bx]
	fist  [bx]

	fld  [bx]
	fstp [bx]
	fst  [bx]

	end
