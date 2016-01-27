
;--- SEH in 64-bit code
;--- needs coff output format

ifdef __JWASM__
	.x64
	.model flat,fastcall
endif

	.code

p1 proc frame

	.allocstack 8			;min value for UWOP_ALLOC_SMALL
	.allocstack 8*16		;max value for UWOP_ALLOC_SMALL
	.allocstack 8*16+8		;min value for UWOP_ALLOC_LARGE, op info 0
	.allocstack 8*10000h-8	;max value for UWOP_ALLOC_LARGE, op info 0
	.allocstack 8*10000h	;min value for UWOP_ALLOC_LARGE, op info 1
	.allocstack 100000000h-8;max value for UWOP_ALLOC_LARGE, op info 1
	.endprolog
	ret

p1 endp

	END
