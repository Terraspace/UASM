
;--- prologue generation 
;--- first instruction after PROC contains a macro function!

	.386
	.model flat, stdcall
	option casemap :none

@prologue macro procname,flag,parmbyte,localbyte,reglist,userparms

	if flag
	  if parmbyte + localbyte
		push ebp
		movzx ebp,sp
	  endif
	  if localbyte
		add esp,-localbyte
	  endif
	endif
	for r,reglist
	   push r
	endm
		exitm %localbyte
endm

CStr macro text
local x
	.const
x	db text,0
	.code
	exitm <offset x>
	endm

	.code

x1 proc a1:dword
	ret
x1 endp

	option prologue:@prologue

p1 proc uses ebx esi x:dword
	ret
p1 endp

p2 proc uses ebx esi x:dword
	invoke x1, CStr("abc")
	ret
p2 endp

p3 proc uses ebx esi x:dword
	.if ( eax == 1 )
	.endif
	ret
p3 endp

	end
