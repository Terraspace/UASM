
;--- test ARPL. This is a somewhat special case
;--- because although it has 16-bit operands the
;--- size prefix (066h) should NOT be set in 32-bit code.
;--- There are a few similiar opcodes (LLDT, SMSW, ... ), but those
;--- are 2 byte opcodes that can be marked with F_0FNO66 to achieve
;--- the same effect.

	.286p
	.model small
	.386p

	.data

vw	label word

	.code

	arpl ax,bx
	lldt ax
	lmsw ax
	ltr  ax
	sldt ax
	smsw ax
	str  ax
	verr ax
	verw ax

	arpl vw,ax
	lldt vw
	lmsw vw
	ltr  vw
	sldt vw
	smsw vw
	str  vw
	verr vw
	verw vw

	ret

_TEXT32 segment use32
	arpl vw,ax
	lldt vw
_TEXT32 ends

	end
