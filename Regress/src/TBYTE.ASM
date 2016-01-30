
;--- tbyte numbers
;--- JWasm since v2.06 will handle the unary + op,
;--- but for the huge rest bits 64-79 will be cleared.

_DATA segment para

	dt 112233445566778899AAh
	align 16
	dt +112233445566778899AAh	;JWasm ok, Masm no
	align 16
	dt -1		;Masm ok, JWasm ok since v2.06
	align 16
	dt 1-3		;Masm ok, JWasm no
	align 16
	dt -1+3		;both ok, since result is positive and fits in 64-bit

if 0
	align 16
;--- arithmetic is 64-bit only, no error msg
	dt 1111b shl 32
	align 16
	dt 1111b shl 62	;upper 2 bits get lost
	align 16

;--- wrong result
	dt 1-10000000000000000000h
	align 16
;--- wrong result
	dt 102030405060708090A0h + 0102030405060708090Ah
	align 16
endif

_DATA ends

	end
