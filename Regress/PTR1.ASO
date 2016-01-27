
;--- binary PTR operator

	.386
	.model flat, stdcall
	option casemap:none

	.code

;--- v2.10: it's a problem to detect that operator PTR and operand EAX are at
;--- the same bracket level. Currently a workaround is implemented in evalopnd.c

	mov [WORD ptr eax],1234h
	mov [DWORD ptr bx],1234h

END
