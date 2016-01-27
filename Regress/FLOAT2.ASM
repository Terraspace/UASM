
;--- test improved float support of v2.05

	.386
	.model flat

	.code

	dw .type 25.1
	dw .type (25.1)
	mov eax, 1.0
	real4 1.0, +1.0, -1.0
	dt real4 ptr 1.0, real4 ptr -1.0

	END
