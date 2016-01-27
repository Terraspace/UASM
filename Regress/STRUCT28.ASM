
	.model tiny

SW struc
b1 db ?
b2 db ?
SW ends

SD struc
w1 dw ?
w2 dw ?
SD ends

	.code

v1 SD <>

	mov al, v1.w2.SW.b2
	mov al, (SW ptr v1.w2).b2
	mov al, [bx].SD.w2.SW.b2
	mov al, (SD ptr [bx]).w2.SW.b2
	mov al, (SW ptr [bx].SD.w2).b2

end
