
;--- a simple struct member requires a valid expression as init string.
;--- Note: Masm accepts this, jwasm is intentionally more rigid here.

	.386
	.model flat, stdcall
	option casemap:none

FOO STRUCT
f1	dword ?
FOO ENDS

	.data

foo1 FOO <<>>

end
