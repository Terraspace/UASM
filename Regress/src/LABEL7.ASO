
;--- since v2.10, label accepts an additional argument,
;--- but for data only ( not for NEAR, FAR or PROC! )

	.386
	.model flat, stdcall

TP1	typedef near
TP2	typedef proto :dword

	.code

;--- this is ok
x1 label near
x2 label far
x3 label proc
x4 label TP1
x5 label TP2

;--- this is still supposed to be an error
x1x label near :dword
x2x label far  :dword
x3x label proc :dword
x4x label TP1  :dword
x5x label TP2  :dword

end