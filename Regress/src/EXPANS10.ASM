
;--- there was a bug in v2.04 
;--- which made macro expansion not to work
;--- after a double-colon

	.386
	.model flat, stdcall
	option casemap :none

m1 MACRO
ENDM

	.code

p1 proc
	nop
l1::m1
	ret
p1 endp

	end
