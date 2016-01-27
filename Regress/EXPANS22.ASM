
;--- expansion of text macros and macro functions
;--- inside quoted strings (expansion operator at pos 0)

	.286
	.MODEL small
	.data

TM1	equ <___>
MF1 macro
	exitm <###>
	endm

%	db "&TM1'&TM1"  ;both equates are expanded
%	db '&TM1"TM1&'
%	db "TM1&'TM1&"
%	db '&TM1"TM1'   ;the second is NOT expanded
	
%	db "&MF1()'&MF1()"
%	db '&MF1()"MF1()&'
%	db "MF1()&'MF1()&"
%	db '&MF1()"MF1()'   ;the second is NOT expanded

end
