
;--- regression test
;--- JMP/CALL indirect with displacement

	.286
	.model small
	.386

	.code

	xor ebx,ebx
	jmp [bx+offset jmptable]
	jmp [ebx*2+offset jmptable]
	call [bx+offset jmptable]
	call [ebx*2+offset jmptable]

jmptable label word
	dw label1, label2, label3, label4

label1:
	ret
label2:
	ret
label3:
	ret
label4:
	ret

	end
