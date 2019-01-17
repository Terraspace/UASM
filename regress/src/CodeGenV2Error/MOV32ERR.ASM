
option flat:1
.code

	use32
	
	mov r8b,ah				; Registers not available in 32bit.
	mov sil,ch				; ""
	
	mov eax,FLAT:[0]	; This legacy mode should fall back to old codegen.

	bnd mov eax,ecx         ; cant use bnd	
	lock mov eax,eax		; cant use lock
	rep mov eax,ecx			; cant use rep
	repe mov eax,ecx		; cant use rep
	repz mov eax,ecx		; cant use rep
	repne mov eax,ecx		; cant use rep
	repnz mov eax,ecx		; cant use rep
	
	mov eax,fs:ecx			; Cant use segment override.
	
	mov eax,[eax*16]		; Scale max is 8.
	mov eax,[eax+ecx+edx]	; Can't use 3 addressing registers.
	
	mov eax,[esi+esp*4+32]	; invalid encoding rsi+rsp 
	mov eax,[esp+esp*4+32]	; invalid encoding rsp+rsp
	mov eax,[eax+esp*4]		; invalid encoding 
	
	mov al,DWORD PTR [eax+eax*4+0xc80]  ; error sizing
	
	movabs bl,[0x00000000]  ; moffset cant only use eax..
	
	mov al,300				; immediate data too large, opnds must be the same size.

.data

ddVar dd 0
