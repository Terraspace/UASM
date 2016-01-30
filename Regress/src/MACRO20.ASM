
;--- macro function call in front of a loop directive
;--- didn't work prior to v2.08

	.386
	.MODEL small

	.code

m1 macro arg:vararg
%&TM1&&TM2&:repeat 3
;	echo 1
	db 1
	endm
MF1():repeat 3
;	echo 2
	db 2
	endm
endm

TM1	textequ <ab>
TM2	textequ <cd>

MF1 macro
;	echo inside MF1
	exitm <abc>
endm

	m1 1,2,3

	end
