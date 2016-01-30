
;--- 64-bit invoke, test for "register value overwritten' error.
;--- cannot be assembled with ML64!

	.x64
	.model flat, fastcall

S1 struct
F1 dd ?
S1 ends

pr1 proto :qword, :dword, :dword, :qword, :qword, :dword

	.code

main proc

local v1:byte

	invoke pr1, qword ptr [rax].S1.F1, [rax].S1.F1, 3, 4, addr v1, [rax].S1.F1

main endp

	end
