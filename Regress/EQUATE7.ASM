
;--- test EQU aliases
;--- in Masm, support for aliases is still implemented,
;--- although docs for v6 state that it has been removed.
;--- However, there are some quirks.

    .386
    .model flat

	.code

P1 proc
	ret
P1 endp

E1	equ P1

	dd P1, TYPE P1, SIZE P1, LENGTH P1
	dd E1, TYPE E1, SIZE E1, LENGTH E1

vb	db 0,1,2

E2	equ vb

	dd vb, TYPE vb, SIZEOF vb, LENGTHOF vb, SIZE vb, LENGTH vb

;--- Masm accepts the operators, but ignores them (except TYPE)!)

	mov al, E2
	mov al, TYPE     E2
	mov al, SIZEOF   E2
	mov al, LENGTHOF E2
	mov al, SIZE     E2
	mov al, LENGTH   E2

externdef E3:abs
E3	equ 5          ;E3 will become public

if 0 ;JWasm won't accept number arguments for SIZEOF, LENGTHOF, ...
	dd E3, TYPE E3, SIZEOF E3, LENGTHOF E3, SIZE E3, LENGTH E3
endif

    RET

    END
