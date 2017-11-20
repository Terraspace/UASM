
; ASMC 2.20
; CreateVariable() - qword

	.386
	.model	flat
	.code

foostr TEXTEQU <xyz>
foo SIZESTR foostr

%	mov	eax,@CatStr(%foo)

IF foo GT 1
	mov	eax,1
ELSE
	.err <should be dead code>
ENDIF

foo = foo - 100		; <--- does set asym.value3264 to -1
foo SIZESTR foostr	; <-- CreateVariable() does not zero asym.value3264, if equate already exist.

%	mov	eax,@CatStr(%foo)
IF foo GT 1
	mov	eax,1
ELSE
	.err <should be dead code>
ENDIF

	END
