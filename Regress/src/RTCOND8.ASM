
;--- constants coupled with && or ||
;--- see RTCOND7.ASM for the more simple cases

	.386
	.model flat

	.code

	.if 1 && 2 || 3 && 4	;true
		inc eax
	.endif

	.if 1 && 2 || 0 && 1	;true
		inc eax
	.endif

	.if 0 && 1 || 1 && 0	;false
		inc eax
	.endif

	.if 0 && 0 || 0 && 0	;false
		inc eax
	.endif

	.if 1 && 0 || 1 && 0	;false
		inc eax
	.endif

	.if (1 || 2) && (1 || 2)	;true
		inc eax
	.endif

	.if (1 || 0) && (1 || 0)	;true
		inc eax
	.endif

	.if (1 || 2) && (1 || 0)	;true
		inc eax
	.endif

	.if (1 || 0) && (1 || 2)	;true
		inc eax
	.endif

	.if (0 || 0) && (1 || 0)	;false
		inc eax
	.endif

	.if (1 || 0) && (0 || 0)	;false
		inc eax
	.endif

end
