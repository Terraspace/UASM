
;--- parameter type check
;--- since v2.05, it should cause a lot of errors

	.386
	.model flat, stdcall

	.code

E1	equ 0

PTRX typedef ptr
PTRB typedef ptr BYTE
PTRW typedef ptr WORD
PTRSB typedef ptr SBYTE
GUID struct
	dd ?
	dw 2 dup (?)
	db 8 dup (?)
GUID ends
IID typedef GUID
REFIID typedef ptr IID

p1 proto :DWORD
p1 proto :ptr		;error

p2 proto :DWORD
p2 proto :PTRX		;error

p3 proto :DWORD
p3 proto :SDWORD	;error

p4 proto :PTRX
p4 proto :PTRX		;ok
p4 proc a1:PTRX		;ok
p4 endp

p5 proto :ptr
p5 proto :PTRX		;ok

p6 proto :PTRB
p6 proto :PTRW		;error

p7 proto :ptr
p7 proto :PTRB		;error

p8 proto :ptr near	;ok
p8 proto :ptr near32

p9 proto :ptr BYTE
p9 proto :ptr SBYTE	;error

p10 proto :XXX		;error 'undefined symbol'
p11 proto :E1		;error 'invalid qualified type'

p12 proto :ptr ptr
p12 proc a1:ptr ptr	;ok
	ret
p12 endp

p13 proto :ptr ABC
p13 proc a1:ptr ABC	;ok
	ret
p13 endp

p14 proto :REFIID
p14 proc a1:ptr IID	;ok
p14 endp

;ABC	equ 1

	end
