
;--- proc arguments and locals without type specifier
;--- ML64 assumes DWORD, jwasm up to v2.07 assumed QWORD

;--- locations:
;--- p1 : EBP+10h
;--- p2 : EBP+18h
;--- p3 : EBP+20h
;--- l1 : EBP-04h
;--- l2 : EBP-08h
;--- l3 : EBP-0Ch

ifdef __JWASM__
	.x64
	.model flat, fastcall
endif

	.code

proc1 proc p1, p2, p3

local l1, l2, l3
;local l1:DWORD, l2:DWORD, l3:DWORD

	mov eax, p1
	mov ecx, l1
	ret
proc1 endp

    END
