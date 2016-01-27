
;--- invoke argument is a struct
;--- problem: some struct type sizes have an associated memtype, and 
;--- INVOKE did use this erroneously. Fixed in v2.10.

	.386
	.MODEL FLAT, stdcall
	option casemap:none

p1 proto :dword

S1 STRUCT	;memtype DWORD
F1 DD ?
S1 ENDS

S2 STRUCT	;memtype QWORD
F1 DD ?
F2 DD ?
S2 ENDS

	.CODE

p1 proc arg1:dword
	ret
p1 endp

	invoke p1,S1	;push 4
	invoke p1,S2	;push 8
	ret

END
