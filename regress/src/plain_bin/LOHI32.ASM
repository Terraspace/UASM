
;--- LOW32, HIGH32 operators
;--- supported (activated) since v2.06
;--- also used by INVOKE if a 64-bit integer or float
;--- is to be pushed.

	.386
	.model flat, stdcall

	.code

yyy proc a1:qword, a2:dword
yyy endp

zzz proc a1:real8, a2:real4
zzz endp

	push 1.0
	pushd 1.0
	push low32 1122334455667788h
	push high32 1122334455667788h
	push low32 3.01
	push high32 3.01

	invoke yyy, 1, 2
	invoke yyy, 123456789ABCDEFh, 0
	invoke zzz, 1.0, 2.0

	end
