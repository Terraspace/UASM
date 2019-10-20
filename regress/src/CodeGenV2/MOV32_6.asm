
option flat:1

.code

	use32
	
	; http://masm32.com/board/index.php?topic=7829.0
	; Correct unsigned types
	mov byte ptr [eax],10
	mov byte ptr [edi],0e8h
	mov byte ptr [esi],2ah
	
	mov [edi],10    ; assume byte 
	mov [eax],0xe8  ; assume byte 
	mov [eax],0x1000 ; assume word 
	
	and BYTE PTR[eax], 128
	and [ebx], 128
	and [ecx], 127
	mov [edi], 128
	mov[eax], 127
	mov BYTE PTR[edi], 128
	mov BYTE PTR[edi], 127
	mov BYTE PTR[edi],128
	and al, 128
	mov al, 128
	mov bl, 128
	mov ax, 128
	mov ax, 300