
; Demonstrates a FASM style flat-mode source, ideal for creating boot-sectors and OS pre-kernel 
; code with UASM.

option flat:1
.code

	org 0h

	use16

var0 dd 10
	
	xor ax,ax
	xor eax,eax
	mov eax,var1

	org 100h

var1 dd 20
	
	use32

	xor ax,ax
	xor eax,eax
	mov eax,var2
		
	org 1000h

var2 dd 30
	
	use64
	
	xor ax,ax
	xor eax,eax
	xor rax,rax
	mov eax,var2 ; -18   rip
	mov eax,var1 ; -3864 rip
	mov eax,var0 ; -4126 rip

	