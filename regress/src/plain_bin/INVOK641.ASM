
;--- invoke in 64-bit - ML64 will reject!

ifdef __JWASM__
	.x64
	.model flat, fastcall
endif

	.data

rd	real4 1.0
rq	real8 1.0

	.code

proc0 proc
	ret
proc0 endp

proc1 proc p1:dword
	ret
proc1 endp

proc2 proc p1:dword, p2:qword
	ret
proc2 endp

proc3 proc p1:word, p2:qword, p3:qword
	ret
proc3 endp

proc4 proc p1:byte, p2:word, p3:dword, p4:qword
	ret
proc4 endp

proc5 proc p1:word, p2:word, p3:word, p4:word, p5:qword
	ret
proc5 endp

proc6 proc p1:word, p2:word, p3:word, p4:word, p5:dword, p6:qword
	ret
proc6 endp

proc7 proc p1:dword, p2:qword, p3:dword, p4:qword, p5:qword, p6:dword, p7:word
	ret
proc7 endp

proc8 proc p1:dword, p2:real4, p3:real8, p4:byte
	ret
proc8 endp


main proc
	invoke proc0
	invoke proc1, 1
	invoke proc2, 1, 2
	invoke proc3, 1, 2, 3
	invoke proc4, 1, 2, 3, 4
	invoke proc5, 1, 2, 3, 4, 5
	invoke proc6, 1, 2, 3, 4, 5, 6
	invoke proc7, 1, 2, 3, 4, 5, 6, 7
	invoke proc8, 1, rd, rq, 4
	invoke proc1, eax
;--- ecx is overwritten. This is checked since v2.04
;	invoke proc2, 1, ecx
main endp

    END
