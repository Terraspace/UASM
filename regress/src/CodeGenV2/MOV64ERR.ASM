
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
	
	mov r8b,[rsi+rsp*4+32]	; invalid encoding rsi+rsp 
	mov r8b,[rsp+rsp*4+32]	; invalid encoding rsp+rsp
	mov r8b,[rax+rsp*4]		; invalid encoding 
	
	mov ah,[r10+32000] 		; cannot use ah with REX
	mov r8b,DWORD PTR [rax+rax*4+0xc80]  ; error sizing
	
	mov al,[si]				; 16bit addressing not allowed in long mode
	
	lock mov rax,rax		; cant use lock
	rep mov eax,ecx			; cant use rep
	bnd mov eax,ecx         ; cant use bnd
	
	mov bl,[0x00000000]     ; moffset cant only use rax..
