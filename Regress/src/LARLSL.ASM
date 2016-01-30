
;--- LAR/LSL:
;--- according to intel docs, mem ref must always be a WORD
;--- Masm (32-bit) won't accept <lsl r32, m16>, however.

	.386
	.model flat

	.data


	.code

	assume ds:_TEXT
	lsl ax,vw
	lsl ax,bx
	lsl eax,vd
	lsl eax,edx

	lar ax,vw
	lar ax,bx
	lar eax,vd
	lar eax,edx
	ret
vw	dw 0h
vd	dd 0h

_TEXT16 segment use16 public 'CODE'
	assume ds:_TEXT16
	lsl ax,vwx
	lsl ax,bx
	lsl eax,vdx
	lsl eax,edx

	lar ax,vwx
	lar ax,bx
	lar eax,vdx
	lar eax,edx
	ret
vwx dw 0h
vdx dd 0h
_TEXT16 ends

	end
