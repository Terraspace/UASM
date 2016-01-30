
;--- regression in v2.06
;--- negative result of subtraction of 2 labels for 16-bit

	.model small
	.code

pr1	proc
	ret
pr1	endp

	dw pr1-$-2

	end
