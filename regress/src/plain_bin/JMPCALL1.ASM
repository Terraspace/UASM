
;--- regression test
;--- code generation
;--- JMP/CALL indirect

	.386
	.model flat

PN16 typedef ptr near16
PN32 typedef ptr near32
PF16 typedef ptr far16
PF32 typedef ptr far32

	.data

v2	dw 0
v22	PN16 0
v4	dd 0
v41	PN32 0
v42	PF16 0
v6	df 0
v62	PF32 0
v8	dq 0

	.code
	jmp [v2]
	jmp [v22]
	jmp PN16 ptr [ebx]

	jmp [v4]
	jmp [v41]
	jmp [v42]
	jmp PN32 ptr [ebx]
	jmp PF16 ptr [ebx]

	jmp [v6]
	jmp [v62]
	jmp PF32 ptr [ebx]

;	 jmp [v8]
	end
