
;--- macro labels

	.286
	.model small

E1 = 0

m1 macro x

E1	= x
	:  lbl1
	E1 = E1+1
	if E1 lt 5
	  goto lbl1
	endif
	db E1
	endm

m2 macro x
local lab
E1	= x
	:  lab
	E1 = E1+1
	if E1 lt 5
	  goto lab
	endif
	db E1
	endm

	.code

	m1 0
	m2 0

end
