
;--- test equates and assembly time variables with externals
;--- assembles with errors

	.286
	.model small, stdcall
	.386

pr1 proto :dword
externdef ex1:abs
externdef ex2:dword

	.code

p1 proc a1:dword
	ret
p1 endp

E1	equ p1		;becomes a Number
E2	equ pr1		;becomes a text
E3	equ ex1		;becomes a text
E4	equ ex2		;becomes a text

	invoke E1, 0	;ok
	invoke E2, 0	;ok

A1	= p1	;Masm + JWasm ok
A2	= pr1   ;Masm + JWasm rejects
A3	= ex1   ;Masm + JWasm rejects
A4	= ex2   ;Masm + JWasm rejects

	invoke A1, 0	;ok
;	invoke A2, 0	;wont work

	End
