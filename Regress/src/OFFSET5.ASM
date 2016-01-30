
;--- test that OFFSET removes var type

_TEXT segment word 'CODE'

vd dd ?
vw dw ?
vb db ?

	mov ax,[bx+offset vd]
	mov ax,[bx+offset vw]
	mov ax,[bx+offset vb]
	.386
	mov eax,[bx+vd]
	.8086
	mov ax,[bx+vw]
	mov al,[bx+vb]

_TEXT ends

	END
