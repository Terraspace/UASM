.intel_syntax noprefix
.text
mov rax, qword ptr [rip+b@GOTPCREL]
movzx eax, byte ptr [rax]
mov rax, qword ptr [rip+b@GOTPCREL]
movsx rax, byte ptr [rax]
mov r8, qword ptr [rip+w@GOTPCREL]
movzx r8d, word ptr [r8]
mov r9, qword ptr [rip+w@GOTPCREL]
movsx r9, word ptr [r9]
mov r10, qword ptr [rip+d@GOTPCREL]
movsxd r10, dword ptr [r10]
mov rdi, qword ptr [rip+b@GOTPCREL]
mov al, byte ptr [rdi]
mov rsi, qword ptr [rip+w@GOTPCREL]
mov ax, word ptr [rsi]
mov rdi, qword ptr [rip+b@GOTPCREL]
mov ah, byte ptr [rdi]
mov r15, qword ptr [rip+q@GOTPCREL]
mov qword ptr [r15], rax
mov r11, qword ptr [rip+d@GOTPCREL]
add dword ptr [r11], 3
mov r11, qword ptr [rip+d@GOTPCREL]
adc dword ptr [r11], eax
mov r12, qword ptr [rip+q@GOTPCREL]
cmp qword ptr [r12], rax
mov r13, qword ptr [rip+d@GOTPCREL]
xchg dword ptr [r13], eax
mov r14, qword ptr [rip+v@GOTPCREL]
movdqu xmm1, xmmword ptr [r14]
mov r15, qword ptr [rip+wide@GOTPCREL]
vmovdqu ymm2, ymmword ptr [r15]
mov r11, qword ptr [rip+d@GOTPCREL]
mov eax, dword ptr [r11+4]
mov r11, qword ptr [rip+d@GOTPCREL]
mov eax, dword ptr [r11-4]
ret
