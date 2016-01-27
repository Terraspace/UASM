
	.286

_TEXT segment word public 'CODE'
	db ?          ;0
	even          ;1   should NOT emit data (works with v2.04+)
	mov ax,1      ;2-4
	dw ?          ;5-6
	even          ;7   should NOT emit data (works with v2.04+)
	mov ax,2      ;8-10
	db ?
_TEXT ends

	end
