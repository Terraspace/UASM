
;--- test "invalid" constant values
;--- However, Masm v6 accepts those values!
;--- Masm v8 won't accept first and last line.

	.386
	.model flat

	.code

	mov ax, 12345h       ;masm v8: no
	and ax,not 1C000h
	and ax, 0FFFEFFFFh
	mov ax, -65535       ;ok, this is hex 0FFFF0001h
	mov ax, -65536       ;masm v8: no

	end
