
;--- % operator in TEXTEQU

_DATA segment
v1	db 0
v2	db 0

TM1	textequ %1+1	;ok
TM2	textequ %v1		;not a constant
TM3	textequ %v2-v1	;ok
TM4	textequ %fv2	;symbol not defined
E3	equ %1			;ok (will be a text)

fv1	db 0
fv2	db 0
_DATA ends


	end
