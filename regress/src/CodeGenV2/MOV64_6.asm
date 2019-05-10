
option flat:1

.code

	use64
	
	; http://masm32.com/board/index.php?topic=7829.0
	; Correct unsigned types
	mov byte ptr [rax],10
	mov byte ptr [rax],0e8h
	mov byte ptr [rax],2ah
	
	mov [rax],10    ; assume byte not word
	mov [rax],0xe8  ; assume byte not word
	mov [rax],0x1000 ; assume word not dword ?
	
	and BYTE PTR[rax], 128
	and [rax], 128
	and [rax], 127
	mov [rax], 128
	mov[rax], 127
	mov BYTE PTR[rax], 128
	mov BYTE PTR[rax], 127
	mov BYTE PTR[rax],128
	and al, 128
	mov al, 128
	mov bl, 128
	mov ax, 128
	mov ax, 300