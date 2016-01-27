
;--- THIS operator

	.286
	.model small
	option casemap:none

S1 struct
	dw ?
f1  equ this byte	;is accepted, but creates a text macro only
f2  equ this word
	db ?
S1 ends

if 0
;--- using THIS outside of a segment block is invalid!
wb	equ this byte
ww	equ this word
wd	equ this dword
wn	equ this near
endif

	.data

S2 struct
	dw ?
f3  equ this byte	;is accepted, but creates a text macro only
f4  equ this word
	db ?
S2 ends

xb	equ this byte
	db 1,2,3
xw	equ this word
	db 1,2,3
xd	equ this dword
	db 1,2,3
xn	equ this near

	.code

vb	equ this byte
	db 5,6,7
vw	equ this word
	db 5,6,7
vd	equ this dword
	db 5,6,7
vn	equ this near

	mov al,xb
	mov ax,xw
	mov ax,xn
	mov ax,this word
	mov bx,this word
	mov bx,this near

	end
