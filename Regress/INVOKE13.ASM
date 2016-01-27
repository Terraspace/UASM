
;--- in v2.04, there was a problem with VARARG parameters
;--- in 16-bit code, if argument was a 32-bit register.

	.286
	.model small
	.386
	.dosseg
	.stack 400h

printf proto c :ptr BYTE, :VARARG

CStr macro y:VARARG
local sym
	.const
sym db y,0
	.code
	exitm <offset sym>
	endm

	.code

printf PROC c fmt:ptr byte, args:VARARG
    ret
printf ENDP

start:
	mov eax, 0
	invoke printf, CStr("%lX"), eax
	mov ah,4Ch
	int 21h

	END start
