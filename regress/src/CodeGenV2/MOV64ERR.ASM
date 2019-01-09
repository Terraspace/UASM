
option flat:1
.code

	use64

	mov r8b,ah				; Cannot mix R8U with R8E
	mov sil,ch				; ""
	
	mov rax,fs:rcx			; Cant use segment override.
	mov ecx,es:[rax]		; Can't use segment override in 64bit except for fs/gs
	mov eax,[rax*16]		; Scale max is 8.
	mov eax,[rax+rcx+rdx]	; Can't use 3 addressing registers.
	mov fs:r8,rax 			; No segment prefix allowed.