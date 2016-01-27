
;--- Jcc with option LJMP/NOLJMP and NEAR/FAR destinations

	.286
	.model small

	.code

externdef x1:near
externdef x2:near
externdef y1:far
externdef y2:far

	option ljmp

	.286
	jz x1
	jz x2
	jz y1
	jz y2
	.386
	jz x1
	jz x2
	jz y1
	jz y2

	option noljmp

	.286
	jz x1
	jz x2	;fails
	jz y1
	jz y2	;fails
	.386
	jz x1
	jz x2
	jz y1
	jz y2	;fails

x1 label near
y1 label far
	nop

end
