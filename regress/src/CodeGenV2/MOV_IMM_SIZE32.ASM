
; Allow move to take MASM style sized immediates (CodeGen V2 regression)

option flat:1

.code

	use32

	mov word ptr [esi],0x20
	mov byte ptr [esi+10],0x10
	mov dword ptr [esi+20],0x100
	
	mov [esi],word ptr 0x20
	mov [esi+10],byte ptr 0x10
	mov [esi+20],dword ptr 0x100

	end
