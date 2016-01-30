
;--- % operator errors

	.386
	.model flat

m1 macro value
	dd value
	endm
m2 macro value
	exitm %value
	endm

	.data

;--- ok
	m1 %1
	m1 %1+2
	dd m2(1+2)
	dd m2(%1+2)
	dd m2(1+%2)
tm1 textequ %1
tm1 textequ %1+2
tm1 equ %1
tm1 equ %1+2
tm2 equ %1
tm2 equ %1+2
tm3 textequ tm1

;--- errors
	dd %1
	dd 1+%2
	dd tm2
tm3 textequ %tm1

end

