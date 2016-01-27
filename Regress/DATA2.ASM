
;--- problem: at pos 0 is a userdef. type,
;--- at pos 1 a predefined type. JWasm versions 2.01-2.04
;--- will reject this syntax.

	.286

UINT typedef WORD

_DATA segment dword public 'DATA'

	UINT byte, word


_DATA ends

	end
