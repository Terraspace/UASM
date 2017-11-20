
	.x64
	.model flat

	.code

	db 3 dup (90h)
start:
	mov rax, offset start			;creates 8-byte ADDR64 fixup, 8 byte immediate
	mov rax, LOW32 start			;creates 4-byte ADDR32 fixup, 8 byte immediate
	mov rax, dword ptr LOW32 start	;creates 4-byte ADDR32 fixup, 4 byte (signed) immediate

END