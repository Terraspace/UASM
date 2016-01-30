
;--- 64bit moves

ifdef __JWASM__
	.x64
	.model flat
endif

	.data

vq	dq 123456789ABCDEF0h
vd	dd 12345678h
vw	dw 1234h
vb	db 12h

	.code

l1:

;--- mov reg, imm

	mov al,1
	mov ax,1
	mov eax,1
	mov r9w,1
	mov r10,1
	mov rax,1
	mov rbx,123456789ABCDEF0h
	mov r9,1
	mov rbx,7FFFFFFFh	;short format ok
	mov rbx,80000000h	;needs long format
	mov rbx,0FFFFFFFFh
	mov rbx,qword ptr 0FFFFFFFFh

;--- mov reg, reg

	mov al,ah
	mov al,r8b
	mov r9b,al
	mov r10b,r11b
	mov al,sil
	mov bpl,r12b

	mov ax,cx
	mov ax,r10w
	mov r10w,cx
	mov r11w,r12w

	mov eax,edx
	mov eax,r11d
	mov r12d,ecx
	mov r13d,r14d

	mov rax,rdx
	mov rax,r11
	mov r12,rcx
	mov r13,r14

;--- mov mem, imm

	mov vb,1
	mov vw,1
	mov vd,1
	mov vd,-1
	mov vd,12345678h
	mov vq,1
	mov vd,offset l1
;	mov vq,offset l1
	mov vq,12345678h
	mov vq,80000000h
	mov vq,-1
;	mov vq,180000000h

;--- mov reg, mem

	mov  al,[vb]
	mov r8b,[vb]
	mov  ax,[vw]
	mov r8w,[vw]
	mov eax,[vd]
	mov edx,[vd]
	mov r8d,[vd]
	mov rax,[vq]
	mov  r8,[vq]

	mov  al,[ecx]
	mov r9b,[ecx]
	mov  ax,[ecx]
	mov r9w,[ecx]
	mov eax,[ecx]
	mov r9d,[ecx]
	mov rax,[ecx]
	mov r10,[ecx]

	mov  cl,[ecx+2*eax]
	mov r8b,[ecx+2*eax]
	mov  cx,[ecx+2*eax]
	mov r8w,[ecx+2*eax]
	mov ecx,[ecx+2*eax]
	mov r9d,[ecx+2*eax]
	mov rcx,[ecx+2*eax]
	mov r10,[ecx+2*eax]

	mov  al,[edx+2*r8d]
	mov r9b,[edx+2*r8d]
	mov  ax,[edx+2*r8d]
	mov r9w,[edx+2*r8d]
	mov eax,[edx+2*r8d]
	mov r9d,[edx+2*r8d]
	mov rax,[edx+2*r8d]
	mov r11,[edx+2*r8d]

	mov  al,[edx+4]
	mov r9b,[edx+4]
	mov  ax,[edx+4]
	mov r9w,[edx+4]
	mov eax,[edx+4]
	mov r9d,[edx+4]
	mov rax,[edx+4]
	mov r12,[edx+4]

	mov  al,[edx+2*ecx+4]
	mov r9b,[edx+2*ecx+4]
	mov  ax,[edx+2*ecx+4]
	mov r9w,[edx+2*ecx+4]
	mov eax,[edx+2*ecx+4]
	mov r9d,[edx+2*ecx+4]
	mov rax,[edx+2*ecx+4]
	mov r13,[edx+2*ecx+4]

	mov  al,[edx+2*r9d+4]
	mov r8b,[edx+2*r9d+4]
	mov  ax,[edx+2*r9d+4]
	mov r8w,[edx+2*r9d+4]
	mov eax,[edx+2*r9d+4]
	mov r8d,[edx+2*r9d+4]
	mov rax,[edx+2*r9d+4]
	mov r14,[edx+2*r9d+4]

	mov  bl,[r8d+2*r9d+4]
	mov r8b,[r8d+2*r9d+4]
	mov  bx,[r8d+2*r9d+4]
	mov r8w,[r8d+2*r9d+4]
	mov ebx,[r8d+2*r9d+4]
	mov r8d,[r8d+2*r9d+4]
	mov rbx,[r8d+2*r9d+4]
	mov r15,[r8d+2*r9d+4]

	mov  al,[rax]
	mov r8b,[rax]
	mov  ax,[rax]
	mov r9w,[rax]
	mov eax,[rax]
	mov r9d,[rax]
	mov rax,[rax]
	mov  r9,[rax]

	mov  al,[r8]
	mov r9b,[r8]
	mov  ax,[r8]
	mov r9w,[r8]
	mov eax,[r8]
	mov r9d,[r8]
	mov rax,[r8]
	mov  r9,[r8]

	mov  al,[r9+r10*4]
	mov r9b,[r9+r10*4]
	mov  ax,[r9+r10*4]
	mov r9w,[r9+r10*4]
	mov eax,[r9+r10*4]
	mov r9d,[r9+r10*4]
	mov rax,[r9+r10*4]
	mov  r9,[r9+r10*4]

	mov  al,[r9+r11*4+2]
	mov r9b,[r9+r11*4+2]
	mov  ax,[r9+r11*4+2]
	mov r9w,[r9+r11*4+2]
	mov eax,[r9+r11*4+2]
	mov r9d,[r9+r11*4+2]
	mov rax,[r9+r11*4+2]
	mov  r9,[r9+r11*4+2]

	mov  al,[rdx+vb]
	mov  ax,[rdx+vw]
	mov eax,[rdx+vd]
	mov rax,[rdx+vq]

;--- mov mem, reg

	mov [vb], al
	mov [vb], r8b
	mov [vw], ax
	mov [vw], r8w
	mov [vd], eax
	mov [vd], edx
	mov [vd], r8d
	mov [vq], rax
	mov [vq], r8

	mov [ecx], al
	mov [ecx], r9b
	mov [ecx], ax
	mov [ecx], r9w
	mov [ecx], eax
	mov [ecx], r9d
	mov [ecx], rax
	mov [ecx], r9

	mov [edx+2*r8d], al
	mov [edx+2*r8d], r9b
	mov [edx+2*r8d], ax
	mov [edx+2*r8d], r9w
	mov [edx+2*r8d], eax
	mov [edx+2*r8d], r9d
	mov [edx+2*r8d], rax
	mov [edx+2*r8d], r9

	mov [rax], al
	mov [rax], r8b
	mov [rax], ax
	mov [rax], r9w
	mov [rax], eax
	mov [rax], r9d
	mov [rax], rax
	mov [rax], r9

	mov [rax+rdx*2], al
	mov [rax+rdx*2], r8b
	mov [rax+rdx*2], ax
	mov [rax+rdx*2], r9w
	mov [rax+rdx*2], eax
	mov [rax+rdx*2], r9d
	mov [rax+rdx*2], rax
	mov [rax+rdx*2], r9

	mov [rax+rdi*2+4], cl
	mov [rax+rdi*2+4], r8b
	mov [rax+rdi*2+4], cx
	mov [rax+rdi*2+4], r9w
	mov [rax+rdi*2+4], ecx
	mov [rax+rdi*2+4], r9d
	mov [rax+rdi*2+4], rcx
	mov [rax+rdi*2+4], r9

	mov [rdx+vb], al
	mov [rdx+vw], ax
	mov [rdx+vd], eax
	mov [rdx+vq], rax
	mov [rdx+vq], r9

;--- mov segreg, reg - mov reg, segreg

	mov ds, rax
	mov ds, eax
	mov ds, ax
	mov rax, ds
	mov eax, ds
	mov ax, ds

	ret

	end
