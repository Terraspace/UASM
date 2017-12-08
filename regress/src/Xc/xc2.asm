;
; asmc /Xc - v2.22 -- use loop[z|nz] if asmc_syntax == OFF
;
	.486
	.model flat
	.code

	.REPEAT
	.UNTILCXZ
	.REPEAT
	.UNTILCXZ eax == 1

	END
