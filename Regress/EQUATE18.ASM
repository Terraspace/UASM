
;--- quoted strings as EQU operand
;--- in 64-bits, they're treated as numbers as long
;--- as size is <= 8.

ifdef __JWASM__
	.x64
	.model flat
endif

E1	equ "A"
E2	equ "AB"
E3	equ "ABC"
E4	equ "ABCD"
E5	equ "ABCDE"
E6	equ "ABCDEF"
E7	equ "ABCDEFG"
E8	equ "ABCDEFGH"
E9	equ "ABCDEFGHI"

V1	= "A"
V2	= "AB"
V3	= "ABC"
V4	= "ABCD"
V5	= "ABCDE"
V6	= "ABCDEF"
V7	= "ABCDEFG"
V8	= "ABCDEFGH"
if 0 ; const value too large in 32- and 64-bit
V9	= "ABCDEFGHI"
endif

_DATA segment
	dq E8
	db E9
_DATA ends

	end
