
;--- JWasm allows parts of a relocatable label to be pushed.

	.386
	.model small
	.stack 400h

	.code

_start:
	mov ah,4Ch
	int 21h

;--- currently LOW generates a 6A opcode - this is NOT a good idea
;--- because the byte is sign-extended, and the assembler can't know if the least-
;--- significant byte of the offset will be < 80h or not.

	push low _start			;should push a dword with 8-bit fixup
	push lowword _start		;should push a dword with 16-bit fixup
	push low32 _start		;should push a dword with 32-bit fixup

;--- actually, the SEG operator causes a 16-bit push in Masm/JWasm.
;--- IMO it would have been better if the operator DOES not
;--- force a specific size of the push operand, but just the fixup type.

	push seg _start

END _start
