
;--- 32-bit: extending size if target is :VARARG

	.386
	.model flat, stdcall
	option proc:private

?PRINT equ 0

if ?PRINT
printf proto c :vararg
vprintf proto c :ptr byte, :ptr
endif

CStr macro text:vararg
local xxx
	.const
xxx  db text,0
	.code
	exitm <offset xxx>
endm

	.code

px proc c args:VARARG
if ?PRINT
	invoke vprintf, CStr( "px: a1=%d a2=%d  l1=%d l2=%d l3=%d",10 ), addr args
endif
	ret
px endp

p1 proc a1:dword, a2:word
local l1:dword
local l2:word
local l3:byte
	mov word ptr l1+0, LOWWORD -11
	mov word ptr l1+2, HIGHWORD -11
	mov l2, -12
	mov l3, -13
if ?PRINT
	invoke printf, CStr( "p1: a1=%d a2=%d  l1=%d l2=%d l3=%d",10 ), a1, a2, l1, l2, l3
endif
	invoke px, a1, a2, l1, l2, l3
	ret
p1 endp

p2 proc a1:sdword, a2:sword
local l1:sdword
local l2:sword
local l3:sbyte
	mov word ptr l1+0, LOWWORD -11
	mov word ptr l1+2, HIGHWORD -11
	mov l2, -12
	mov l3, -13
if ?PRINT
	invoke printf, CStr( "p2: a1=%d a2=%d  l1=%d l2=%d l3=%d",10 ), a1, a2, l1, l2, l3
endif
	invoke px, a1, a2, l1, l2, l3
	ret
p2 endp

if ?PRINT
main proc c public
	invoke p1, -1, -2
	invoke p2, -1, -2
	ret
main endp
endif

end
