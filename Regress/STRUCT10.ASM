
;--- struct access.
;--- this emitted a warning ( and produced wrong code )
;--- prior to v2.04

	.386
	.model flat,stdcall

	.code

	mov ax,sizeof OPRND

;--- struct (includes anonymous structs) located AFTER code lines
;--- so it's ensured that it will be parsed in pass 2

OPRND struc
flags	db ?
union
reg1	db ?
numadd	db ?
ends
union
struct
reg2	db ?
index	db ?
ends
num2	dw ?
ends
orednum	db ?
num		dd ?
OPRND ends

	mov ax,sizeof OPRND

	end
