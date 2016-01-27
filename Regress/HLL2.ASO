
;--- hll errors

	.386
	.MODEL FLAT, stdcall
	option casemap:none

	.code

	.while eax == 0 || eax == 1
		nop
	.endif 	;nesting error

	.repeat
		.break .until eax == 0	;just .if after .break allowed
		inc eax
	.until eax == 2

	.repeat
		inc eax
	.untilcxz eax > 100		;must be EQ or NE

	end
