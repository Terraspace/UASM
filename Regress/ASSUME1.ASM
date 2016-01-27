
;--- valid assumes

	.286
	.model small

S1 struct
   db ?
f1 db ?
S1 ends

	assume ds:_TEXT
	assume cs:ds
	assume bx:ptr
	assume es:DGROUP
	assume bx:ptr WORD
	assume bx:ptr S1

	.code

	mov al,[bx].f1

	end
