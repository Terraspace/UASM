
;--- access to a struct with incompatible size must be flagged

	.386
	.model flat
	option casemap:none

S1 STRUCT
x  dd ?
S1 ENDS

S2 STRUCT
y  dw ?
S2 ENDS

S3 STRUCT
x  dd ?
y  dw ?
S3 ENDS

S4 struct
   dd ?
a  S3 <>
S4 ends

S5 struct
   dd ?
   S4 <>
S5 ends

	.code

	assume ebx:ptr S2
	mov al, S3
	mov ax, [ebx].y
	mov eax, [ebx.S1]
	mov eax, [ebx.S1.x]
	mov ax, [ebx.S3.y]

	assume ebx:nothing
	mov ax, [ebx].S3.y
	mov ax, [ebx].S4.a.y
	mov ax, [ebx].S5.a.y
	mov ax, S3.y[ebx]
	mov ax, S4.a.y[ebx]
	mov ax, S5.a.y[ebx]

	end
