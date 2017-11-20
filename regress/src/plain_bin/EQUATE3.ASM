
;--- equates which are a difference of 2 labels
;--- this code was rejected by JWasm v1.94-2.00

	.286

_TEXT segment public 'CODE'

@	equ $
	jmp init	;a near forward jump which causes a phase error
L1	dw 0
	dd 0
L2	dw 0

E1 equ L1-@
E2 equ (L1-@) XOR (L2-@)

	db 128 dup (0)

init:
	ret

_TEXT ends

	End
