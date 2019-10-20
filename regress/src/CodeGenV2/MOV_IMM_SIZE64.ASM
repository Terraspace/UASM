
; Allow move to take MASM style sized immediates (CodeGen V2 regression)

option flat:1

.code

	use64

	mov word ptr [rsi],0x20
	mov byte ptr [rsi+10],0x10
	mov dword ptr [rsi+20],0x100
	
	mov [rsi],word ptr 0x20
	mov [rsi+10],byte ptr 0x10
	mov [rsi+20],dword ptr 0x100

	end
