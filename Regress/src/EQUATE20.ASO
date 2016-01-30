
;--- redefinition of E1
;--- worked until v2.08, because expanded value == previous value
;--- now rejected

MF1	macro
	exitm <1>
	endm

E1	equ 1
E1	equ MF1()

TM1	textequ <1>

E1	equ TM1	;this is ok

	end
