
;--- regression test
;--- code generation
;--- IN/OUT

	.286
	.model small
	.386

	.data

vd	dd 0
vw	dw 0
vb	db 0

	.code

	in al,20h
	in ax,20h
	in eax,20h
	in al,dx
	in ax,dx
	in eax,dx
	insb
	insw
	insd
	ins [vb],dx
	ins [vw],dx
	ins [vd],dx
	ins es:[vb],dx
	out 20h,al
	out 20h,ax
	out 20h,eax
	out dx,al
	out dx,ax
	out dx,eax
	outsb
	outsw
	outsd
	outs dx,[vb]
	outs dx,[vw]
	outs dx,[vd]
	outs dx,ds:[vb]
	outs dx,es:[vb]
	outs dx,cs:[vb]
	ret

	end
