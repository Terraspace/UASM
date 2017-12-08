option flat:1

.code

USE16

start:

push cs
push ds
push es
push ss
push fs
push gs

push bp
push ax
push bx
push cx
push dx
push si
push di

pusha
popa

pop ds
pop es
pop fs
pop gs
pop ss

pop bp
pop ax
pop bx
pop cx
pop dx
pop si
pop di

push eax
push ebx
push ecx
push edx
push edi
push esi
pop eax
pop ebx
pop ecx
pop edx
pop edi
pop esi

mov al,ds:[si]
mov al,es:[si]
mov es:[di],al
mov ds:[si],al
mov ax,ds:[si]
mov eax,ds:[esi]
mov es:[edi],eax

cli
sti
