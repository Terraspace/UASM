
;--- regression test
;--- code generation
;--- JMP/CALL indirect with -Zm

	.286
	.model small

	option m510

	.data

v2	dw 0,1
v4	dd 0,1

	.code

;--- with -Zm, no size is needed for indirect jumps

	jmp [bx]
	jmp [bx+si]
	jmp [bx+2]
	jmp [bx+v2]  ;the size is determined by v2
	jmp [bx+v4]  ;the size is determined by v4
	call [bx]
	call [bx+si]
	call [bx+2]
	call [bx+v2]
	call [bx+v4]
	end
