
;--- local macros

	.386
	.model flat

m1 macro arg
local lbl1, lbl2

m1x macro argx
	mov ax, argx
	endm
	m1x cx
lbl1:m1x dx
lbl2:for p,<bx,cx>
	m1x p
	endm
	endm

	.code

	m1 0

	end
