
;--- constants coupled with && or ||
;--- also see rtcond8.asm.

	.386
	.model flat

	.code

	.if 1 && 2
		inc eax
	.endif

	.if 1 && 0
		inc eax
	.endif

	.if 0 && 0
		inc eax
	.endif

	.if 1 || 2
		inc eax
	.endif

	.if 1 || 0
		inc eax
	.endif

	.if 0 || 0
		inc eax
	.endif

end
