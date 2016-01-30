
;--- VARARG with signed arguments

	.386
	.model flat, stdcall
	option proc:private

	includelib <kernel32.lib>
	includelib <msvcrt.lib>

CStr macro text:vararg
local xxx
	.const
xxx  db text,0
	.code
	exitm <offset xxx>
endm

	.code

printf proc c args:VARARG
	ret
printf endp

p1 proc uses ebx a1:dword, a2:sword, a3:sbyte

local l1:dword
local l2:sword
local l3:sbyte

	mov l1, 11
	mov l2, -12
	mov l3, -13
	invoke printf, CStr( "a1=%u a2=%d a3=%d  l1=%u l2=%d l3=%d",10 ), a1, a2, a3, l1, l2, l3
	ret

p1 endp

start:
	invoke p1, 1, -2, -3
	ret

end start
