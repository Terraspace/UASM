
;--- 16-bit: extending size of unsigned arguments to DWORD

	.286
	.model small, c
	option proc:private

?PRINT equ 0

if ?PRINT
printf proto c :vararg
endif

CStr macro text:vararg
local xxx
	.const
xxx  db text,0
	.code
	exitm <offset xxx>
endm

	.code

px proc a1:dword, a2:dword, a3:dword, a4:dword, a5:dword
if ?PRINT
	invoke printf, CStr( "a1=%ld a2=%ld a3=%ld a4=%ld a5=%ld",10 ), a1, a2, a3, a4, a5
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
	invoke printf, CStr( "a1=%ld a2=%d  l1=%ld l2=%d l3=%d",10 ), a1, a2, l1, l2, l3
endif
	invoke px, a1, a2, l1, l2, l3
	ret

p1 endp

	.386

p2 proc a1:dword, a2:word

local l1:dword
local l2:word
local l3:byte

	mov l1, -11
	mov l2, -12
	mov l3, -13
if ?PRINT
	invoke printf, CStr( "a1=%ld a2=%d  l1=%ld l2=%d l3=%d",10 ), a1, a2, l1, l2, l3
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
