
;--- test max constant values

	.286
	.model tiny

	.code

	and ax,not 0C000h
	mov ax, 0FFFF3FFFh	;ok (everything's ok as long as hi32 is 0 or -1)
;	mov ax, 12345h		;accepted by Masm, rejected by JWasm
;	and ax,not 1C000h	;accepted by Masm, rejected by JWasm
;	and ax, 0FFFE3FFFh	;accepted by Masm, rejected by JWasm

	end
