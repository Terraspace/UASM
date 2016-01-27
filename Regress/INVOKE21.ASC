
;--- -Zg option

    .386
    .model flat, stdcall

    .code

proc2 proc p1:dword
	ret
proc2 endp

proc1 proc p1:dword

local lcl2:word
local lcl1:dword    ;"add esp, -xxx" instead of "sub esp,xxx"

	mov eax, p1
	.if eax == 0	;"or eax, eax" instead of "cmp eax,xxx"
		inc eax
	.endif
	invoke proc2, lcl2	;extend without destroying contents of eax
	ret				;"leave" instead of ???

proc1 endp

    end
