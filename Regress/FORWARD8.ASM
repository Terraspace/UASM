
;--- regression in v2.09-2.10
;--- the "je" will be extended although final distance is just 127 bytes.
;--- it's caused by the forward reference (l2) in the "add" instruction.

	.model small
	.code
l1:
	and al,al
	je l3
	add dx,l2 - l1
l2:
	org $+124
l3:

end
