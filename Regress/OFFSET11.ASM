
;--- JWasm allows parts of a relocatable label to be pushed.

	.x64
	.model flat

	.data
v1	dd -1
	.code
	db 3 dup (90h)
start:

	mov [v1], low32 start
	push low32 start		;should push a dword with 32-bit fixup

END
