
; --- ASMC 1.04 - JWASM hll.c v2.11/12 -- missing label

	.386
	.model flat

	.code

	.while !(eax || edx) && ecx
	    nop
	.endw

	end
