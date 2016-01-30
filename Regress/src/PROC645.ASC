
;--- v2.12: new flag 16-byte stack alignment (win64:4)
;--- should work with FRAME procs and also if option win64:2 is set

	.x64
	.model flat,fastcall

	option frame:auto
	option win64:7

ifndef ?DISPLAY
?DISPLAY equ 0
endif

if ?DISPLAY
printf proto :vararg

CStr macro text:vararg
local xxx
	.const
xxx db text,0
	.code
	exitm <offset xxx>
endm
endif

proccode macro
	movaps l2, xmm1
if ?DISPLAY
	mov eax, a1
	mov l1, eax
	mov l3, rax
	invoke printf, CStr("a1=%d l1=%d l3=%d",10), a1, l1, l3
endif
	ret
endm

allprocs macro num
p&num&0 PROC FRAME
LOCAL l2 : XMMWORD
	movaps l2, xmm2
	ret
p&num&0 endp

p&num&1 PROC FRAME a1:DWORD
LOCAL l1 : DWORD
LOCAL l2 : XMMWORD
LOCAL l3 : QWORD
	proccode
p&num&1 endp

p&num&2 PROC FRAME uses r12 a1:DWORD
LOCAL l1 : DWORD
LOCAL l2 : XMMWORD
LOCAL l3 : QWORD
	proccode
p&num&2 endp

p&num&3 PROC FRAME uses r12 r13 a1:DWORD
LOCAL l1 : DWORD
LOCAL l2 : XMMWORD
LOCAL l3 : QWORD
	proccode
p&num&3 endp

p&num&4 PROC FRAME uses xmm7 a1:DWORD
LOCAL l1 : DWORD
LOCAL l2 : XMMWORD
LOCAL l3 : QWORD
	proccode
p&num&4 endp

p&num&5 PROC FRAME uses r12 xmm7 a1:DWORD
LOCAL l1 : DWORD
LOCAL l2 : XMMWORD
LOCAL l3 : QWORD
	proccode
p&num&5 endp

p&num&6 PROC FRAME uses r12 xmm7 r13 a1:DWORD
LOCAL l1 : DWORD
LOCAL l2 : XMMWORD
LOCAL l3 : QWORD
	proccode
p&num&6 endp

p&num&7 PROC FRAME uses r12 xmm7 xmm8 a1:DWORD
LOCAL l1 : DWORD
LOCAL l2 : XMMWORD
LOCAL l3 : QWORD
	proccode
p&num&7 endp

p&num&8 PROC FRAME uses r12 xmm7 r13 xmm8 a1:DWORD
LOCAL l1 : DWORD
LOCAL l2 : XMMWORD
LOCAL l3 : QWORD
	proccode
p&num&8 endp

p&num&9 PROC FRAME uses r12 xmm7 r13 xmm8 a1:DWORD
LOCAL l1 : DWORD
LOCAL l2 : XMMWORD
LOCAL l3 : QWORD
LOCAL l4 : XMMWORD
	proccode
p&num&9 endp
endm

	.code

	allprocs 0

	option stackbase:rsp

	allprocs 1

start proc
if ?DISPLAY

	mov r12, 0123456789abcdefh
	mov r13, 0fedcba987654321h
	mov rax, 55aa55aa55aa55aah
	movd xmm7, rax
	invoke p00
	invoke p01, 5
	invoke p02, 5
	invoke p03, 5
	invoke p04, 5
	invoke p05, 5
	invoke p06, 5
	invoke p07, 5
	invoke p08, 5
	invoke p09, 5
	movd rax, xmm7
	invoke printf, CStr("result with frame pointer  r12=%I64X r13=%I64X xmm7=%I64X",10), r12, r13, rax

	mov r12, 0123456789abcdefh
	mov r13, 0fedcba987654321h
	mov rax, 55aa55aa55aa55aah
	movd xmm7, rax
	invoke p10
	invoke p11, 5
	invoke p12, 5
	invoke p13, 5
	invoke p14, 5
	invoke p15, 5
	invoke p16, 5
	invoke p17, 5
	invoke p18, 5
	invoke p19, 5
	movd rax, xmm7
	invoke printf, CStr("result without frame pointer  r12=%I64X r13=%I64X xmm7=%I64X",10), r12, r13, rax

endif
	ret
start endp

end start
