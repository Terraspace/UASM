option flat:1

.code

SOME_ADDR equ 0C2100Dh

USE64

add eax,[0x0c888880]
imul rax,[1234]
sub eax,[0x12535]
sub rax,[0x14242054]
mov rax,[0C2100Dh]
	
mov rax,[SOME_ADDR]
mov rax,[10+(100*256)]

	mov [0C2100Dh],rax
	mov [0000788880888880h],al
	mov rax,[0000788880888880h]                ;48 A1 60 F6 7F 80 F8 7F 00 00
	mov rax,7FF8807FF660h
	mov eax,[00007FF6601D1010h]
	mov ax,[00007FF6601D1010h]
	mov al,[00007FF6601D1010h]
mov rax,[0C2100Dh]
mov eax,[0C2100Dh]
mov ax ,[0C2100Dh]
mov al ,[0C2100Dh]
mov [0C2100Dh],rax
mov [0C2100Dh],ax
mov [0C2100Dh],al
mov [0C2100Dh],rax
mov [0C2100Dh],ax
mov [0C2100Dh],al
	mov [0000788880888880h],rax
	mov [00007FF6601D1010h],al
	mov [00007FF6601D1010h],ax
	mov al ,[00007FF6601D1010h]
	mov ax ,[00007FF6601D1010h]
	mov eax,[00007FF6601D1010h]
	mov rax,[00007FF8807FF660h]                ;48 A1 60 F6 7F 80 F8 7F 00 00
	mov rax,7FF8807FF660h

mov qword ptr [0C2100Dh],rax
mov [0C2100Dh],eax
mov [0C2100Dh],eax
mov [00007FF6601D1010h],eax
mov QWORD PTR [00007FF8807FF660h],rax                ;48 A3 60 F6 7F 80 F8 7F 00 00

db 20 DUP (90h)

USE32

imul eax,[12345]
add eax,[0x8c888880]

; NEW Style for 2.37, implicit DS and size from register.
mov [0C2100Dh],eax
mov [0C2100Dh],ax
mov [0C2100Dh],al
add [0x1234],ax
add [0x12341f25],eax
mov eax,[0C2100Dh]
mov ax ,[0C2100Dh]
mov al ,[0C2100Dh]

; OLD Style that did work with 2.36.
mov ds:[0C2100Dh],eax
mov ds:[0C2100Dh],ax
mov ds:[0C2100Dh],al
add ds:[0x1234],ax
add ds:[0x12341f25],eax
mov eax,ds:[0C2100Dh]
mov ax ,ds:[0C2100Dh]
mov al ,ds:[0C2100Dh]

