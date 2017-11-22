
;--- PTR operator inside square brackets
;--- is supposed to be "dereferenced" if possible.

	.386
	.model flat, stdcall
	option casemap:none

PWORD typedef ptr WORD
PPWORD typedef ptr ptr WORD

S1 struct
x DD ?
y DW ?
S1 ends

PS1 typedef ptr S1

	.code

	mov [PWORD ptr eax],1234h	;target WORD
	mov [PPWORD ptr eax],1234h	;target DWORD

	assume eax:ptr BYTE	;
	mov [eax],12h				;target BYTE
	mov [PWORD ptr eax],1234h	;target WORD, PTR has higher precedence than ASSUME
	mov [PS1 ptr eax].y,1234h	;target S1, PTR has higher precedence than ASSUME

END
