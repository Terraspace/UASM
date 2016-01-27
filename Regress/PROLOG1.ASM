
	.386
	.model flat,stdcall
	option casemap:none

S1 struct
	db 50h dup (?)
S1 ends

	.code

OPTION PROLOGUE:NONE
OPTION EPILOGUE:NONE

pr1 proc p1:DWORD,p2:DWORD
	ret
pr1 endp

myprologue macro name,flags,parmsize,localsize,regslist,userparm

;%	echo prolog: name, flags, parmsize, localsize, regslist, userparm
	push ebp
	mov ebp, esp
	for r,regslist
		push r
	endm
	sub esp, localsize
	exitm %localsize
	endm

myepilogue macro name,flags,parmsize,localsize,regslist,userparm

;%	echo epilog: name, flags, parmsize, localsize, regslist, userparm
	for r,regslist
		pop r
	endm
	mov esp, ebp
	pop ebp
	ret parmsize
	endm

OPTION PROLOGUE:myprologue
OPTION EPILOGUE:myepilogue

pr2 proc uses ds ebx esi p1:DWORD, p2:DWORD
local l1:dword
local l2:dword
	ret
pr2 endp

pr3 proc uses esi p1:S1, p2:S1
local l1:S1
local l2:S1
	ret
pr3 endp

OPTION PROLOGUE:PROLOGUEDEF
OPTION EPILOGUE:EPILOGUEDEF

pr4 proc p1:DWORD, p2:DWORD
	ret
pr4 endp

	end
