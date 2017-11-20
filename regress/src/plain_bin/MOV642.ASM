
;--- some special cases

ifdef __JWASM__
	.x64
	.model flat
	assume gs:nothing
endif

	.data
vq	dq 0

	.code

if 1
	mov rdx,[vq]
	mov rdx,gs:[30h]
endif
	mov rax,[r11]

	mov rax,[rsp]
	mov rax,[esp]
	mov rax,[r12]
	mov rax,[r12d]

	mov [rsp], rcx
	mov [esp], rdx
	mov [r12], r8
	mov [r12d], r9

	mov rax,[rsp+1]
	mov rax,[esp+1]
	mov rax,[r12+1]
	mov rax,[r12d+1]

	mov [rsp+1], rcx
	mov [esp+1], rdx
	mov [r12+1], r8
	mov [r12d+1], r9

	mov rax,[rbp]
	mov rax,[ebp]
	mov rax,[r13]
	mov rax,[r13d]

	mov [rbp], rcx
	mov [ebp], rdx
	mov [r13], r8
	mov [r13d], r9

	mov rax,[rbp+1]
	mov rax,[ebp+1]
	mov rax,[r13+1]
	mov rax,[r13d+1]

	mov [rbp+1], rcx
	mov [ebp+1], rdx
	mov [r13+1], r8
	mov [r13d+1], r9

	mov rax,[rbp+rdx*2]
	mov rax,[ebp+edx*2]
	mov rax,[r13+rdx*2]
	mov rax,[r13d+edx*2]

	mov [rbp+rdx*2], rcx
	mov [ebp+edx*2], rdx
	mov [r13+rdx*2], r8
	mov [r13d+edx*2], r9

	ret

	end
