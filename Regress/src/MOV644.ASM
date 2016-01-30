
;--- direct addressing with constant addresses
;--- works since v2.11
;--- Note that ML64 has a different syntax!

ifdef __JWASM__
	.x64
	.model flat
	assume gs:nothing
endif

	.code

start proc

ifdef __JWASM__
	mov al,flat:[0]
	mov al,flat:[10h]
	mov al,flat:[7FFFFFFFh]
	mov al,flat:[80000000h]
	mov al,flat:[100000000h]
	mov al,flat:[123456789ABCDEF0h]
	mov ax,flat:[123456789ABCDEF0h]
	mov eax,flat:[123456789ABCDEF0h]
	mov rax,flat:[123456789ABCDEF0h]
	mov al,flat:[0ffffffff80000000h]
	mov flat:[0],al
	mov flat:[10h],al
	mov flat:[7FFFFFFFh],al
	mov flat:[80000000h],al
	mov flat:[100000000h],al
	mov flat:[123456789ABCDEF0h],al
	mov flat:[123456789ABCDEF0h],ax
	mov flat:[123456789ABCDEF0h],eax
	mov flat:[123456789ABCDEF0h],rax
	mov flat:[0ffffffff80000000h],al
	mov cl,flat:[7fffffffh]
	mov cl,flat:[-1]
	mov cl,flat:[0ffffffff80000000h]
else
	mov al,[0]
	mov al,[10h]
	mov al,[7FFFFFFFh]
	mov al,[80000000h]
	mov al,[100000000h]
	mov al,[123456789ABCDEF0h]
	mov ax,[123456789ABCDEF0h]
	mov eax,[123456789ABCDEF0h]
	mov rax,[123456789ABCDEF0h]
	mov al,[0ffffffff80000000h]
	mov [0],al
	mov [10h],al
	mov [7FFFFFFFh],al
	mov [80000000h],al
	mov [100000000h],al
	mov [123456789ABCDEF0h],al
	mov [123456789ABCDEF0h],ax
	mov [123456789ABCDEF0h],eax
	mov [123456789ABCDEF0h],rax
	mov [0ffffffff80000000h],al
	mov cl,[7fffffffh]
	mov cl,[-1]
	mov cl,[0ffffffff80000000h]
endif
	mov al,gs:[10h]
	mov al,gs:[7fffffffh]
	mov al,gs:[80000000h]
	mov al,gs:[123456789ABCDEF0h]

start endp

end 
