
	.386
	.model flat

	.code

	.if 100000000h	;must fit in 32-bits
		nop
	.endif

	.if eax CARRY? ecx	;was accepted up to v2.11
	.endif

	.if eax ! ecx	;was accepted up to v2.11
	.endif

	.if && eax		;was accepted up to v2.11
	.endif

	.repeat
		inc eax
	.until 0 + CARRY?	;was accepted - in pass 1 - up to v2.11

	.if CARRY? > eax	;did emit simple "syntax error" up to v2.11, now "syntax error in control-flow directive" 
	.endif

	.if 1
		inc eax
	.endif eax			;nothing allowed behind .endif

	.while 1
		inc eax
	.endw eax			;nothing allowed behind .endw

	.repeat 1+2			;nothing allowed behind .repeat
		inc eax
	.until 0

end
