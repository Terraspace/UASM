
option flat:1
.code

	use64

	mov al,[rax+32]
	mov al,[rbx]
	mov al,[rcx]
	mov al,[rdx]
	mov al,[rsi]
	mov al,[rdi]
	mov al,[rsp]
	mov al,[rbp]
	mov al,[rip]
	mov al,[r8]
	mov al,[r9]
	mov al,[r10]
	mov al,[r11]
	mov al,[r12]
	mov al,[r13]
	mov al,[r14]
	mov al,[r15]
	
	; Mixed immediates
	mov al,10
	mov al,130
	mov cl,-25
	mov dh,120
	mov bl,0xff
	mov r10b,22
	mov ah,32
	mov ax,10
	mov ax,0x20
	mov cx,25
	mov r10w,22
	mov r8w,0x0f0f
	mov eax,10
	mov eax,0x20
	mov ecx,25
	mov r10d,22
	mov r8d,16
	mov eax,10
	mov rax,10
	mov rax,0x20
	mov rcx,25
	mov r10,22
	mov r8,16
	mov rax,10
	mov rax,0x1234123412341234
	mov rbx,0x1234123412341234
	mov r10,0x1234123412341234
	
;0:  b0 0a                   mov    al,0xa
;2:  b0 20                   mov    al,0x20
;4:  b1 19                   mov    cl,0x19
;6:  b6 78                   mov    dh,0x78
;8:  b3 ff                   mov    bl,0xff
;a:  41 b2 16                mov    r10b,0x16
;d:  b4 20                   mov    ah,0x20
;f:  66 b8 0a 00             mov    ax,0xa
;13: 66 b8 20 00             mov    ax,0x20
;17: 66 b9 19 00             mov    cx,0x19
;1b: 66 41 ba 16 00          mov    r10w,0x16
;20: 66 41 b8 0f 0f          mov    r8w,0xf0f
;25: b8 0a 00 00 00          mov    eax,0xa
;2a: b8 20 00 00 00          mov    eax,0x20
;2f: b9 19 00 00 00          mov    ecx,0x19
;34: 41 ba 16 00 00 00       mov    r10d,0x16
;3a: 41 b8 10 00 00 00       mov    r8d,0x10
;40: b8 0a 00 00 00          mov    eax,0xa
;45: 48 c7 c0 0a 00 00 00    mov    rax,0xa
;4c: 48 c7 c0 20 00 00 00    mov    rax,0x20
;53: 48 c7 c1 19 00 00 00    mov    rcx,0x19
;5a: 49 c7 c2 16 00 00 00    mov    r10,0x16
;61: 49 c7 c0 10 00 00 00    mov    r8,0x10
;68: 48 c7 c0 0a 00 00 00    mov    rax,0xa
;6f: 48 b8 34 12 34 12 34    movabs rax,0x1234123412341234
;76: 12 34 12
;79: 48 bb 34 12 34 12 34    movabs rbx,0x1234123412341234
;80: 12 34 12
;83: 49 ba 34 12 34 12 34    movabs r10,0x1234123412341234
;8a: 12 34 12

	; (8bit immediates)
	mov al,10
	mov al,0x20
	mov cl,25
	mov dh,120
	mov bl,01010101b
	mov r10b,22
	mov ah,32
	
	; (16bit immediates)
	mov ax,10
	mov ax,0x20
	mov cx,25
	mov r10w,22
	mov r8w,1111000011110000b
	
	; (32bit immediates)
	mov eax,10
	mov eax,0x20
	mov ecx,25
	mov r10d,22
	mov r8d,(1 SHL 4)
	mov eax,1.0
	
	; (64bit immediates)
	mov rax,10
	mov rax,0x20
	mov rcx,25
	mov r10,22
	mov r8,(1 SHL 4)
	mov rax,1.0
	mov rax,1234123412341234h
	mov rbx,1234123412341234h
	mov r10,1234123412341234h
	
	; Segment Register Moves (64bit allowed)
	mov ax,cs		; 0x66 0x8c 0xc8
	mov ax,fs		; 0x66 0x8c 0xe0
	mov r8w,cs		;
	mov r12w,ds		;
	mov eax,gs		;
	mov eax,fs		;
	mov r10d,ds		;
	mov rax,cs		;
	mov rax,es
	mov rdi,cs
	mov r9,cs
	mov cs,ax		;
	mov fs,ax		;
	mov es,r8w		;
	mov gs,eax		;
	mov fs,eax		;
	mov fs,r10d		;
	mov cs,rax		;
	mov es,rax
	mov cs,rdi
	mov ds,r9		;

	; Special Moves (CR/DR)
	mov rax,cr0		; 0x0f 0x20 0xc0
	mov rcx,cr2		; 0x0f 0x20 0xd1
	mov r8,cr4		; 0x0f 0x20 0xe0
	mov r12,cr8		; 0x45 0x0f 0x20 0xc4 (CR8 is 64bit only == TPR).
	mov cr8,r8		; 0x45 0x0f 0x22 0xc0
	mov cr0,rax		; 0x0f 0x22 0xc0
	mov rax,dr0		; 0x0f 0x21 0xc0
	mov rcx,dr1
	mov r8,dr7		; 0x41 0x0f 0x21 0xf8
	mov dr7,r12
	mov dr0,rax
	
	; 64 bit R/R moves
	mov rax,rax		; 0x48 0x89 0xc0
	mov rax,rbx
	mov r10,rdx		; 0x49 0x89 0xd2
	mov rsi,rdi
	mov r9,rax
	mov rbx,rcx
	mov rax,rbp
	mov rbx,r12		; 0x4c 0x89 0xe3
	mov r13,r9		; 0x4d 0x89 0xcd
	
	; 32 bit R/R moves
	mov eax,eax		; 0x89 0xc0
	mov ebx,eax		; 0x89 0xc3
	mov ecx,edx		;
	mov edx,eax		;
	mov eax,r9d		; 0x44 0x89 0xc8
	mov ecx,r12d	; 0x44 0x89 0xe1
	mov r8d,eax		; 0x41 0x89 0xc0
	mov r9d,edx
	mov r10d,esi
	mov r12d,edi
	mov r13d,ebp	
	mov eax,esp
	mov r8d,esp
	
	; 16 bit R/R moves
	mov ax,bx		; 0x66 0x89 0xd8
	mov si,dx		; 0x66 0x89 0xd6
	mov dx,di		; 0x66 0x89 0xfa
	mov bp,ax		; 0x66 0x89 0xc5
	mov ax,r9w		; 0x66 0x44 0x89 0xc8
	mov cx,r12w		; 0x66 0x44 0x89 0xe1
	mov r8w,ax		; 0x66 0x41 0x89 0xc0
	mov r9w,dx
	mov r10w,si
	mov r12w,di
	mov r13w,bp
	mov bx,sp
	mov ax,ax
	
	; 8 bit R/R moves
	mov al,al 		; 0x88 0xc0	
	mov al,bl 		; 0x88 0xd8
	mov cl,dl 		; 0x88 0xd1
	mov al,ah 		; 0x88 0xe0
	mov ch,bl 		; 0x88 0xdd
	mov bh,dh 		; 0x88 0xf7
	mov r10b,al
	mov ch,al
	mov al,r8b		; 0x44 0x88 0xc0
	mov r9b,r12b	; 0x45 0x88 0xe1
	mov sil,al		; 0x40 0x88 0xc6
	mov dil,dl		; 0x40 0x88 0xd7
	mov bpl,al		;
	mov spl,al		;
	mov sil,dil		;
	mov bpl,spl		;
	mov r14b,r15b	;
