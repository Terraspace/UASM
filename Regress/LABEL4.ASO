
;--- JWasm versions < 2.05 assembled this without errors.
;--- it must give errors, since the offset is 32-bit
;--- and won't fit in 8- or 16-bit registers.

	.386

_TEXT segment dword public 'CODE'

	assume cs:_TEXT

	mov al,1

xxx:
	mov al,xxx
	mov ax,xxx

	call xxx

_TEXT ends

	end
