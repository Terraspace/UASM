
;--- syntax error in .break/.continue shouldn't affect .endw/.until

	.model small

	.code

	.while ax==1
		inc cx
		.break .if cx==%2
		inc ax
	.endw

end
