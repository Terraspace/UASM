
;--- forward reference in critical expressions
;--- jwasm <  v2.11: error 'constant expected'
;--- jwasm >= v2.11: error 'symbol not defined'

	.model small
	.code

	mov ax,E1

X2	substr <abc>,E1

if E1
endif

	db E1 dup (?)

	repeat E1
	endm

	option fieldalign:E1
	option procalign:E1

E1 equ 1

end
