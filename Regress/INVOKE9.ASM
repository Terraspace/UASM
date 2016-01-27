
;--- test invoke with :VARARG prototype and ADDR operator

	.286
	.model small,c
	.386

	.data

v1	db 0

_TEXT32 segment use32 public 'CODE'

printf32 proc c a:ptr, b:VARARG
	ret
printf32 endp

	invoke printf32, 0, addr v1, addr printf32

_TEXT32 ends

	.code

printf16 proc c a:ptr, b:VARARG
	ret
printf16 endp

	invoke printf16, 0, addr v1, addr printf32

	end
