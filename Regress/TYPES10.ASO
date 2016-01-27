
;--- a qualified type in a PROC's parameter list
;--- may define a "forward" reference to a type (typekind=TYPE_NONE)
;--- This symbol cannot be redefined

	.386
	.model flat, stdcall
	option casemap:none

	.code

p1	proc a1:ptr IMAGELIST	;defines forward ref to type IMAGELIST
	ret
p1	endp

IMAGELIST	equ 1			;must be an error in pass 1

END
