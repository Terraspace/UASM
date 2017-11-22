
;--- v2.11: TYPE had a problem if type coercion was active and a
;--- unary operator was used.

	.x64
	.model flat

	.CODE
start:

	dw TYPE QWORD PTR offset start
	dw TYPE QWORD PTR low32 start
	dw TYPE QWORD PTR lowword start
	dw TYPE QWORD PTR low start

END
