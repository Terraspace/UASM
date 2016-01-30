
;--- a qualified type in a PROC's parameter list
;--- may define a "forward" reference to a type (typekind=TYPE_NONE)
;--- However, in pass two this type must be defined
;--- works in v2.10, didn't work in v2.04-2.09

	.386
	.model flat, stdcall
	option casemap:none

	.code

p1	proc a1:ptr IMAGELIST	;defines forward ref to type IMAGELIST
	ret
p1	endp

	mov eax, sizeof IMAGELIST	;must be an error in pass 2
	ret

END
