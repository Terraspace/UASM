
;--- forward references define symbols with state SYM_UNDEFINED.
;--- such symbols are NOT supposed to prevent the creation of symbols
;--- with the very same name, but local scope!
;---
;--- error msg should be "undefined symbol" at the line where the undefined
;--- symbol is first referenced.
;--- fixed in v2.10 ( see also: local2.aso ).

	.286
	.model small, c

	.code

	mov ax,a1	;defines forward ref a1

proc1 proc a1:word
	ret
proc1 endp

;--- the case where the PROC is preceded by a PROTO is
;--- handled by a different branch in proc.c and needs its
;--- own test case.

	mov ax,a2	;defines forward ref a2

proc2 proto :word

proc2 proc a2:word
	ret
proc2 endp

end

