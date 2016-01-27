
	.386
	.model flat

	.code

	ins byte  ptr es:[edi],dx
	ins word  ptr es:[edi],dx
	ins dword ptr es:[edi],dx
	ins es:vb,dx
	ins es:vw,dx
	ins es:vd,dx

	insb
	insw
	insd
	insb es:[edi],dx
	insw es:[edi],dx
	insd es:[edi],dx

	outs dx, byte  ptr [esi]
	outs dx, word  ptr [esi]
	outs dx, dword ptr [esi]
	outs dx,vb
	outs dx,vw
	outs dx,vd

	outsb
	outsw
	outsd
	outsb dx,ds:[esi]
	outsw dx,ds:[esi]
	outsd dx,ds:[esi]

	outsb dx,es:[esi]
	outsw dx,es:[esi]
	outsd dx,es:[esi]

vb	db 0
vw	dw 0
vd	dd 0
vq	dq 0

	end
