
;--- expansion details
;--- prior to v2.08, result of expansion was 4 in 1,2,4 and xxx&_yyy in 3

	.386
	.model flat,stdcall

TM1 equ <xxx>
TM2 equ <yyy>
MF1 macro
	exitm <xxx>
	endm
MF2 macro
	exitm <yyy>
	endm

xxx_yyy equ <4>

	.code

m1	macro
if 0
%echo TM1&_yyy		;% expands to xxx_yyy
%echo xxx_&TM2		;% expands to xxx_yyy
%echo MF1()&_yyy	;% expands to xxx_yyy
%echo xxx_&MF2()	;% expands to xxx_yyy
endif
%	db TM1&_yyy		;% expands to xxx_yyy, xxx_yyy to 4 by ExpandLine()
%	db xxx_&TM2		;% expands to xxx_yyy, xxx_yyy to 4 by ExpandLine()
%	db MF1()&_yyy	;% expands to xxx_yyy, xxx_yyy to 4 by ExpandLine()
%	db xxx_&MF2()	;% expands to xxx_yyy, xxx_yyy to 4 by ExpandLine()
	endm

	m1

	end
