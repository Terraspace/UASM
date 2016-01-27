
;--- store result of addr - addr in a byte

	.386
	.model flat

	.code

	db offset l1 - $
	dw 0
l1	db offset l2 - $
	dw 0
l2	db -1

	end
