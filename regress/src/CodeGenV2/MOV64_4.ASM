
option flat:1

.data

.code

	use64
	
	; Test REX.X extension of SIB
	mov rax,[rax+r8]
	
	; Index only form
	mov eax,[rdi*2]
	