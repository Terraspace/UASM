
;--- this was accepted up to v2.08

	.386
	.model flat

	.code

size_ = offset lbl2 - offset lbl1

	db size_ dup (?)	;error 'symbol not defined'

if size_ 	;warning 'symbol not defined'
	db 0
endif

lbl1:
	db size_
	db 15 dup (0)
lbl2:

end
