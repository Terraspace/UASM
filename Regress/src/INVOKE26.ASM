
;--- 16-bit: extending size of signed arguments to DWORD or WORD
;--- Masm uses CBW and CWD if cpu is < 80386,
;--- else it uses MOVSX eax, arg

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
	invoke printf, CStr( "px: a1=%ld a2=%ld a3=%ld a4=%ld a5=%ld",10 ), a1, a2, a3, a4, a5
endif
	ret
px endp

py proc a1:word, a2:word, a3:word, a4:word
if ?PRINT
	invoke printf, CStr( "py: a1=%d a2=%d a3=%d a4=%d",10 ), a1, a2, a3, a4
endif
	ret
py endp

p1 proc a1:sdword, a2:sword
local l1:sdword
local l2:sword
local l3:sbyte
	mov word ptr l1+0, LOWWORD -11
	mov word ptr l1+2, HIGHWORD -11
	mov l2, -12
	mov l3, -13
if ?PRINT
	invoke printf, CStr( "p1: a1=%ld a2=%d  l1=%ld l2=%d l3=%d",10 ), a1, a2, l1, l2, l3
endif
	invoke px, a1, a2, l1, l2, l3
	ret
p1 endp

p2 proc a1:sword, a2:sbyte
local l1:sword
local l2:sbyte
	mov l1, -11
	mov l2, -12
if ?PRINT
	invoke printf, CStr( "p2: a1=%d a2=%d  l1=%d l2=%d",10 ), a1, a2, l1, l2
endif
	invoke py, a1, a2, l1, l2
	ret
p2 endp

	.386

p3 proc a1:sdword, a2:sword

local l1:sdword
local l2:sword
local l3:sbyte

	mov l1, -11
	mov l2, -12
	mov l3, -13
if ?PRINT
	invoke printf, CStr( "p3: a1=%ld a2=%d  l1=%ld l2=%d l3=%d",10 ), a1, a2, l1, l2, l3
endif
	invoke px, a1, a2, l1, l2, l3
	ret

p3 endp

p4 proc a1:sword, a2:sbyte

local l1:sword
local l2:sbyte

	mov l1, -11
	mov l2, -12
if ?PRINT
	invoke printf, CStr( "p4: a1=%d a2=%d  l1=%d l2=%d",10 ), a1, a2, l1, l2
endif
	invoke py, a1, a2, l1, l2
	ret

p4 endp

if ?PRINT
main proc c public
	invoke p1, -1, -2
	invoke p2, -1, -2
	invoke p3, -1, -2
	invoke p4, -1, -2
	ret
main endp
endif

end
