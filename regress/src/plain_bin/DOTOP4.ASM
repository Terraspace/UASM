
;--- regression in v2.07-2.08a
;--- with option oldstructs

	.model small

	option oldstructs

S1 struc
w1 dw ?
w2 dw ?
S1 ends

S2 struc
b1 db ?
b2 db ?
S2 ends

	.code
	assume bx:ptr S1
	mov ax,[bx].w1
	mov al,[bx].S2.b2
	mov al,[bx].w2.S2.b2
	end
