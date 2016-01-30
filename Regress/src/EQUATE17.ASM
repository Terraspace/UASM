
;--- quoted strings as EQU operand
;--- in 32-bits, they're treated as numbers as long
;--- as size is <= 4.
;--- in 64-bits, they're treated as numbers as long
;--- as size is <= 8.

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
if 0 ; const value too large in 32-bit
V5	= "ABCDE"
V6	= "ABCDEF"
V7	= "ABCDEFG"
V8	= "ABCDEFGH"
endif
if 0 ; const value too large in 32- and 64-bit
V9	= "ABCDEFGHI"
endif

_DATA segment
	dd E4
	db E5
_DATA ends

	end
