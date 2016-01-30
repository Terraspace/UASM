
;--- check unmatching proc/endp
;--- didn't work in v2.05-2.09 if the
;--- ENDP label did fully comprise the PROC label

	.386
	.model flat, stdcall
	option casemap:none

	.code

p1	proc a1:dword
	ret
p1x	endp

END
