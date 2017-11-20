
.286p

code segment para public use16 'code16'
assume cs:code, ds:code, es:code

start:

	in al,20h

mov al,1
mov bl,10
mov cl,200
mov ah,20
mov ch,10
mov si,10
mov di,20
mov dl,10
mov dh,30

int 10h
mov es:[si],al
mov ds:[di],bl
mov byte ptr es:[si],10
mov word ptr ds:[si],20
mov word ptr ds:[di],10

cld
clc
stosb
lodsb
rep movsb
rep movsw
rep stosb
rep stosw

mov al,bl
mov dl,ch
mov si,ax
mov bx,cx
mov dx,bx
mov di,si

push ax
pop bx

ret
iret

pusha
popa

in al,dx
in ax,dx
out dx,al
out dx,ax

and al,bl
or dx,ax

code ends

end start
