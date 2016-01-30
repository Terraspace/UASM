
;--- test TYPE with type coercions

	.286
	.model tiny
	.dosseg

UINT typedef DWORD

S1 struct
	dd ?
S1 ends

U1 union
	db ?
	dw ?
	dd ?
U1 ends

R1 record reserved:31,bit0:1

	.data
vd1	dd ?
vd2	UINT ?
vd3 S1 <>
vd4 U1 <>
vd5 R1 <>
	.code

	mov ax,type vd1
	mov ax,type (WORD ptr vd1)
	mov ax,type vd2
	mov ax,type (WORD ptr vd2)
	mov ax,type vd3
	mov ax,type (WORD ptr vd3)
	mov ax,type vd4
	mov ax,type (WORD ptr vd4)
	mov ax,type vd5
	mov ax,type (WORD ptr vd5)
	mov ax,type DWORD
	mov ax,type (WORD ptr DWORD)
	mov ax,type UINT
	mov ax,type (WORD ptr UINT)
	mov ax,type S1
	mov ax,type (WORD ptr S1)
	mov ax,type U1
	mov ax,type (WORD ptr U1)
	mov ax,type R1
	mov ax,type (WORD ptr R1)

	assume bx:ptr WORD
	mov ax,type [bx]
	assume bx:ptr UINT
	mov ax,type [bx]
	assume bx:ptr S1
	mov ax,type [bx]

	end
