
;--- VARARG macro functions (+@CatStr,which is also VARARG since v2.08).
;--- "blank" items in VARARG argument

	.286
	.model small

	.data

TM0	textequ @CatStr()
TM1	textequ @CatStr(,<abc>)

;%echo 0 TM0
;%echo 1 TM1
%   db "&TM0&TM1&"

	db 0CCh

MF1 macro arg:vararg
;	echo MF1 full argument: >arg<
	for x,<arg>
;	echo argument: >x<
ifnb <x>
	db x
else
	db -1
endif
	endm
	exitm <>
	endm

;--- for macro functions, trailing commas are "swallowed"

	MF1()
	MF1(1,2,3)
	MF1(,2)
	MF1(,,3)
	MF1(1,,3)
	MF1(1,,,4)
	MF1(1,)
	MF1(,)
;--- jwasm swallows the last comma only
;	MF1(1,,)

M1 macro arg:vararg
;	echo M1 full argument: >arg<
	for x,<arg>
;	echo argument: >x<
ifnb <x>
	db x
else
	db -1
endif
	endm
	endm

;--- with macro procedures, nothing is swallowed
;--- (but still not quite compatible!)
;--- v2.09: the last three cases should work now.

	M1
	M1 1,2,3
	M1 ,2
	M1 ,,3
	M1 1,,3
	M1 1,,,4
;	M1 1,
;	M1 ,
;	M1 1,,

end

