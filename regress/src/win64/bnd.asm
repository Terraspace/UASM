; Intel MPX Test-Piece

option casemap:none
option stackbase:rbp
option win64:7

option bnd:on	; Enable automatic generation of BND on invokes.

testProc PROTO aPointer:PTR

.data

bndStore0 dq 0,0

.code

testProc PROC aPointer:PTR

	bnd ret
testProc ENDP

main PROC
	LOCAL myBuffer[100]:BYTE
	
	; Create two bounds.
	; lower bound is stored as is in the BND0 register, the upper value RCX is size-1 and stored in 1s complement.
	lea rax,myBuffer
	mov rcx,99
	bndmk bnd0,[rax+rcx]
	
	lea rax,myBuffer
	bndmk bnd1,[rax+99]
	
	; Verify the bound move operations between registers and oword sized memory.
	bndmov bnd2,bnd0
	bndmov bndStore0,bnd1
	bndmov bnd1,bndStore0
	
	; Verify the bounds of the pointer in RAX pre-write for a dword sized write.
	; CL (check lower bound uses the pointer value itself).
	; CU (check upper uses the pointer + size - 1).
	lea rax,myBuffer
	bndcl bnd0,[rax]
	bndcu bnd0,[rax+3]
	mov dword ptr [rax],ecx
	
	; Test OPTION BND via invoke
	invoke testProc, rax

	; Test BND call.
	mov rcx, rax
	bnd call testProc
	
	; Test BND jmp/jcc
	mov rcx,10
	bnd jmp firstLabel
	
firstLabel:
	dec rcx
	bnd jnz short firstLabel
	
	; Test invalid prefix on opcodes that don't allow BND
	;bnd mov rax,[rax]
	;bnd iretq
	;bnd cmp rax,rbx
	
	xsave [rdi]
	xsave64 [rdi]
	
	ret
main ENDP
	
end main
