
;--- privileged opcodes

ifdef __JWASM__
	.x64p
	.model flat
endif

	.data

m8	db	0
m16	dw	0
m32	dd	0
m48	df	0
m64	dq	0
m80	dt	0

	.code

if 0
	cli

	clts

	hlt

	invd

	invlpg byte ptr m8

	iret
	iretd
	iretq

	lar dx,word ptr m16
	lar eax,esp
	lar r10,rax

	lsl ebx,r9d


	mov cr0,r9
	mov cr8,rdx
	mov rcx,cr4
	mov r11,cr2

	mov dr0,r15
	mov rdx,dr7

	rdmsr

	rdpmc

	rdtsc

	rsm
endif

if 0	;according to Intel only r/m64 is supported in 64bit
	jmp m16		;accepted by ML64
	jmp ax		;accepted by ML64
;	jmp m32		;not accepted by ML64 and JWasm
;	jmp eax		;not accepted by ML64 and JWasm
endif

;--- intel docs state that operand's size for LGDT|SGDT|LIDT|SIDT
;--- is fix 80-bit! ML64 accepts 48-bit operands.
;	lgdt m48	;not accepted by JWasm
;	lidt m48	;not accepted by JWasm
	sgdt m48
	sidt m48

;--- ML64 won't accept 48-bit operands!
ifdef __JWASM__
	lgdt m80	;not accepted by ML64
	lidt m80	;not accepted by ML64
endif
	sgdt m80
	sidt m80

	lldt ax
;	lldt ebx	;not accepted by ML64 and JWasm
;	lldt rcx	;not accepted by ML64 and JWasm
	lldt m16

	lmsw r9w
;	lmsw eax	;not accepted by ML64 and JWasm
;	lmsw rax	;not accepted by ML64 and JWasm
	lmsw m16

	ltr ax
;	ltr ebx		;not accepted by ML64 and JWasm
;	ltr rcx		;not accepted by ML64 and JWasm
	ltr m16

	sldt dx
	sldt ecx
	sldt r13
	sldt m16

	smsw dx
	smsw ebx
	smsw rcx
	smsw m16

	str ax
	str ebx
	str r12
	str m16

	end
