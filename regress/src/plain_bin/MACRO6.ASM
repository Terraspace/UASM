
;--- FOR/FORC MACRO parameter test

	.286
	.MODEL small

	.CODE

FORC arg, <ABC>
    BYTE  '&arg&'
ENDM

FOR arg:=<X>, <1,,2,,3,,4>
    BYTE  '&arg'
ENDM

	END
