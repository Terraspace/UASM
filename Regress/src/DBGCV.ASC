
;--- test codeview debugging info for COFF

	.386
	.model flat

HWND typedef ptr

S1 struct
f1	dd ?
f2	dd ?
S1 ends

	.data

	public g1
g1	db 0	;public global
st1	db 0	;static global

	.code

;--- private proc
proc1 proc fastcall private a1:dword, a2:qword
local l1[5]:byte
local l2[2]:HWND
	ret
proc1 endp

;--- public proc
main proc c argc:dword, argv:ptr ptr
local l1[2]:S1
	invoke proc1, 1, 2
	ret
main endp

;--- label
_start:
	invoke main, 0, 0
	ret

	end _start
