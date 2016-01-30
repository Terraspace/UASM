
;--- 64-bit: register arguments with VARARG

	.x64
	.model flat, fastcall

	option frame:auto
	option win64:2

?DISPLAY equ 0	;set to1 if you want a real application

CStr macro text:vararg
if ?DISPLAY
local xxx
	.const
xxx db text,0
	.code
	exitm <addr xxx>
else
	exitm <addr $>
endif
endm

	includelib <msvcrt.lib>

	.code

uvq	dq 1122334455667788h
uvd dd 12345678h
uvw dw 1234h
uvb db 12h
	align 8
svq	sqword -1
svd sdword -2
svw sword -3
svb sbyte -4

if ?DISPLAY eq 0
?PATTR equ <>
printf proc ?PATTR fmt:ptr byte, args:vararg
	ret
printf endp
else
?PATTR equ <FRAME>
printf proto :ptr BYTE, :VARARG
exit proto :dword
endif

main proc ?PATTR
if ?DISPLAY
	mov rdi, 1122334455667788h
	mov edx, 12345678h
	mov cl, 12h
	mov si, 1234h
	mov bh, 12h
	mov r11, 1122334455667788h
endif
	invoke printf, CStr("unsigned rdi=%I64X, edx=%X, cl=%X. si=%X, bh=%X, r11=%I64X",10), rdi, edx, cl, si, bh, r11
if ?DISPLAY
	mov rdi, -1
	mov edx, -2
	mov cl, -3
	mov si, -4
	mov bh, -5
	mov r11, -6
endif
	invoke printf, CStr("signed rdi=%I64d, edx=%d, cl=%d. si=%d, bh=%d, r11=%I64d",10), 
		sqword ptr rdi, sdword ptr edx, sbyte ptr cl, sword ptr si, sbyte ptr bh, sqword ptr r11

	invoke printf, CStr("unsigned dq=%I64X, dd=%X, dw=%X. db=%X, dw=%X, dd=%X",10), uvq, uvd, uvw, uvb, uvw, uvd
	invoke printf, CStr("signed dq=%I64d, dd=%d, dw=%d. db=%d, dw=%d, dd=%d",10), svq, svd, svw, svb, svw, svd

	ret
main endp

start proc ?PATTR
if ?DISPLAY
	invoke main
	invoke exit, 0
endif
	ret
start endp

	END start
