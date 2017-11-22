
;--- constants coupled with && or ||, then negated
;--- see RTCOND7.ASM & RTCOND8.ASM for other cases.

	.386
	.model flat

	.code

	.if !(1 && 1)	;false
		inc eax
	.endif

	.if !(0 && 1)	;true
		inc eax
	.endif

	.if !(1 && 0)	;true
		inc eax
	.endif

	.if !(0 && 0)	;true
		inc eax
	.endif


	.if !(1 || 1)	;false
		inc eax
	.endif

	.if !(0 || 1)	;false
		inc eax
	.endif

	.if !(1 || 0)	;false
		inc eax
	.endif

	.if !(0 || 0)	;true
		inc eax
	.endif

end
