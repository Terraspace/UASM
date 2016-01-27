
;--- problem: TYPE with proto pointer argument
;--- the argument's type was lost prior to v2.05.
;--- It's needed by INVOKE.

	.386
	.model flat, stdcall
	option dotname

	.code

TestProto typedef PROTO STDCALL :DWORD,:DWORD
TestProcPtr equ <(type TestProto) PTR edx>

p1 proc hInst:dword

local Arg1:dword

	invoke TestProcPtr, hInst, addr Arg1
	ret

p1 endp

end

