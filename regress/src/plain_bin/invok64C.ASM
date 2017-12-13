
;--- test invoke with ZERO valued EQUATE optimisation and 0 valued immediated (both use xor now).
;--- implemented in UASM 2.46.5

ifdef __UASM__
	.x64
	.model flat, fastcall
	option win64:2
endif

ZERO_EQUATE    equ 0
NONZERO_EQUATE equ 1

	.code

proc0 proc a1:dword
	mov eax,a1
	ret
proc0 endp

main proc
	invoke proc0, 0
	invoke proc0, ZERO_EQUATE
	invoke proc0, NONZERO_EQUATE
main endp

    END
