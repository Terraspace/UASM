
	.386
	.model flat

	.code

TE1	equ <another forced error>
TE2	equ <>
TE3	equ <abc>
TE4	equ <undefined symbol>

tm1 macro
	exitm <_undefined symbol_>
	endm

	.err <this is a forced error>
	.err TE1

	.erre E2,<E2 is 0>
	.erre E2
	.errndef E1,<undefined symbol>
	.errndef E1,TE4
	.errndef E1,tm1()
	.errdef TE1,<text equate TE1 is defined>
	.errnb <b>,<argument isn't blank>
	.erridn <abc>,TE3
	.erridn <abc>,<abc>,<arguments are equal>

;E1	equ 1
E2	equ 0

	end
