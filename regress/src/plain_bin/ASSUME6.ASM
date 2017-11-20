
;--- register assume overwritten by type coercion

	.386
	.model flat

VFT struct
mt1 dd ?
mt2 dd ?
VFT ends

DMY struct
DMY ends

	.code

	assume edx:ptr DMY
	call (VFT ptr [edx - 4]).mt1

end
