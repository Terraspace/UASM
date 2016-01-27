
;--- test OPTION directive
;--- no error expected

	.286
	.model small

	option casemap:none

TE2	textequ <dotname>
	option TE2

	option prologue:none
	option epilogue:none

	option nokeyword:<title>
	option nokeyword:<esi, add>

	option offset:segment
	option offset:group
	option oldstructs
	option m510

TE1	textequ <stdcall>
	option language:TE1
TE1	textequ <c>
	option language:TE1

S1 struct
F1	db ?
F2	db ?
S1 ends

	.data

var1 dw 0

	.code

add proc
	ret
add endp

esi proc
	ret
esi endp

title proc
	ret
title endp

main proc c

	mov ax,var1
;	mov cx,VAR1
	mov ax,offset esi
	mov ax,offset title
	mov ax,F2
	ret

main endp

	END


