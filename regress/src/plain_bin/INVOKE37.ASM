
;--- pointer type arguments
;--- see invoke38.asm for 32-bit variant
;--- see invoke39.aso for errors

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

	invoke p1 ptr [bx], 0
	invoke p2 ptr [bx], 0
	invoke p3 ptr [bx], 0
	invoke p4 ptr [bx], 0
	invoke p5 ptr [bx], 0
	invoke p6 ptr [bx], 0

	invoke p1 ptr [bx], addr dlbl
	invoke p2 ptr [bx], addr dlbl
	invoke p3 ptr [bx], addr dlbl	;prior to v2.11: address was pushed in far16 format
	invoke p4 ptr [bx], addr dlbl	;prior to v2.11: error 'INVOKE argument type mismatch'
	invoke p5 ptr [bx], addr dlbl	;prior to v2.11: address was pushed in far16 format
	invoke p6 ptr [bx], addr dlbl	;prior to v2.11: error 'INVOKE argument type mismatch'

	invoke p1 ptr [bx], ax			;regs pushed as word
	invoke p2 ptr [bx], ds::ax		;regs pushed as dword
	invoke p3 ptr [bx], eax			;regs pushed as dword
	invoke p4 ptr [bx], ds::eax		;regs pushed as fword
	invoke p5 ptr [bx], eax			;regs pushed as dword
	invoke p6 ptr [bx], ds::eax		;regs pushed as qword!

	END
