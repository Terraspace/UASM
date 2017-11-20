
.code

	displacement EQU 200h

	mov ah,[rip]
	mov rax,[rip+3]
	mov rax,[rip+400h]
	mov cx,[rip+128]
	mov [rip+127],cx
	mov [rip+displacement],rbx
	mov rbx,[rip+displacement]
	mov rax,[rip]
	mov [rip+1],sil
	cmp byte ptr [rip], 90h
	lea rbx,[rip]
	lea rax,[rip+2]
	call qword ptr [rip+400]
	push [rip]
	push [rip+80h]
	pop [rip]

    end