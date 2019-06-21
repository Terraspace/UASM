
option flat:1

.data

vq	dq 123456789ABCDEF0h
vd	dd 12345678h
vw	dw 1234h
vb	db 12h

vbe EQU 20h

.code

	use64

	mov [rax + vb], al
	mov [rdx + vb], ah
	mov al, [rdx + vb] 
	mov [rdx + vb], al
	mov al, [rdx + vb]
	mov al, [rdx + vb]
	mov [vb], al
	
	mov [rax + vbe], al
	mov [rdx + vbe], ah
	mov al, [rdx + vbe] 
	mov [rdx + vbe], al
	mov al, [rdx + vbe]
	mov al, [rdx + vbe]