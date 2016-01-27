
;--- pointer type arguments
;--- also see invoke37.asm

	.286
	.MODEL small, c
	.386
	option casemap:none

;--- push 2, 4, 4, 6, 4, 8 bytes

p1 typedef proto :near ptr
p2 typedef proto :far ptr
p3 typedef proto :near32 ptr
p4 typedef proto :far32 ptr
p5 typedef proto far32 :near32 ptr
p6 typedef proto far32 :far32 ptr

	.data

dlbl label byte

	.CODE

	invoke p1 ptr [bx], al	;size must be 2
	invoke p1 ptr [bx], eax	;size must be 2
	invoke p2 ptr [bx], ax	;size must be 4
	invoke p3 ptr [bx], ax	;size must be 4
	invoke p4 ptr [bx], ax	;size must be 6
	invoke p4 ptr [bx], eax	;size must be 6
	invoke p5 ptr [bx], ax	;size must be 4
	invoke p6 ptr [bx], eax	;size must be 8

	END
