
;--- test PROC epilogue creation with RET

;--- there is some wrong information about when epilogue code is created.
;--- it isn't created for RETN and RETF, but it is ALWAYS created if a 
;--  RET <x> is found, regardless what <x> is.

	.386
	.model flat
	option casemap:none

myepilogue macro name,flags,parmsize,localsize,regslist,userparm

	for r,regslist
		pop r
	endm
	mov esp, ebp
	pop ebp
	ret parmsize
	endm

	option epilogue:myepilogue

	.code

p1 proc stdcall uses ebx esi edi a1:dword, a2:dword

local	l1:dword

	mov eax,l1
	ret
	mov eax,l1
	retn		;no epilogue with RETN

p1 endp

	option epilogue:none

p2 proc stdcall uses ebx esi edi a1:dword, a2:dword

local	l1:dword

	mov eax,l1
	ret
	mov eax,l1
	retn

p2 endp

	END
