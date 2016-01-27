
;--- initialization of multiple structured variables

	.386
	.model flat
	option casemap:none

S1 struct
	db ?
S1 ends

	.data

v1 S1 2 dup (<1>), <2>
v2 S1 2 dup (<1>), 2 dup (<2>)

	dw size v1		;must be 2
    dw length v1	;must be 2
    dw sizeof v1	;must be 3
    dw lengthof v1	;must be 3
	dw size v2		;must be 2
    dw length v2	;must be 2
    dw sizeof v2	;must be 4
    dw lengthof v2	;must be 4

	END
