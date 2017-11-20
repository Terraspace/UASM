
;--- shift operations 
;--- with forward references

	.model small

	.data

vb	db 0
vw	dw 0
vd	dd 0

	.code

main proc
	shl al,cl
	shl ax,cl
	shl bx,cl
	shl [vb],cl
	shl [vw],cl
	shl [vb2],cl
	shl [vw2],cl
	shl al,1
	shl ax,1
	shl bx,1
	shl [vb],1
	shl [vw],1
	shl [vb2],1
	shl [vw2],1
	.186
	shl al,2
	shl ax,2
	shl bx,2
	shl [vb],2
	shl [vw],2
	shl [vb2],2
	shl [vw2],2
	.386
	shl eax,cl
	shl ebx,cl
	shl [vd],cl
	shl [vd2],cl
	shl eax,1
	shl ebx,1
	shl [vd],1
	shl [vd2],1
	shl eax,2
	shl ebx,2
	shl [vd],2
	shl [vd2],2
	.8086
	ret
main endp

	.data

vb2	db 0
vw2	dw 0
vd2	dd 0

    END
