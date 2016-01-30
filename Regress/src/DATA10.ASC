
;--- regression in v2.09 if /coff

	.386
	.model flat

	.data

	db offset nextl - $   ;error 'invalid fixup type for coff' was displayed
	db 10 dup (0)
nextl label byte

	end
