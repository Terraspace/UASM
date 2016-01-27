
;--- privileged opcodes

	.686p
	.model flat

	.data

m8	db	0
m16	dw	0
m32	dd	0
m48	df	0
m64	dq	0
m80	dt	0

	.code

	sysenter
	sysexit

	lgdt m48
	lidt m48
	sgdt m48
	sidt m48
;--- with Masm, SGDT/SIDT accept any sizes.
;--- JWasm will reject size M64
	sgdt m32
	sidt m32

;--- LLDT, SLDT, LTR,STR, LMSW, LMSW accept 16-bit operand only

	lldt ax
;	lldt ebx
	lldt m16

	lmsw ax
;	lmsw eax
	lmsw m16

	ltr ax
;	ltr ebx
	ltr m16

	sldt dx
;	sldt ecx
	sldt m16

	smsw dx
;	smsw ebx
	smsw m16

	str ax
;	str ebx
	str m16

	end
