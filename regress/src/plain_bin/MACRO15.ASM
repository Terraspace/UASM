
;--- there was a temporary problem in v2.07 with macro redefinitions,
;--- if the macro's type changed ( macro proc - macro function )

	.386
	.model flat

HRESULT_CODE macro hr
	exitm <( ( hr )  and  0FFFFh ) >
	endm

HRESULT_CODE macro
	movsx eax, ax
	endm

	.code
	HRESULT_CODE
	ret

	END

