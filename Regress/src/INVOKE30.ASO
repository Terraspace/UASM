
;--- extend to DWORD param in 16-bit

	.8086
	.model small,c

	.code

x proc c a1:dword
	ret
x endp

	invoke x, ax	;ax overwritten ( by generated "xor ax,ax" )

	end
