.intel_syntax noprefix
.text
mov rax, qword ptr [rip+counter@GOTPCREL]
mov eax, dword ptr [rax]
mov rbx, qword ptr [rip+value@GOTPCREL]
mov rbx, qword ptr [rbx]
mov rax, qword ptr [rip+counter@GOTPCREL]
mov rax, qword ptr [rip+counter@GOTPCREL]
lea rax, [rax+4]
mov r11, qword ptr [rip+counter@GOTPCREL]
mov eax, dword ptr [r11]
mov r11, qword ptr [rip+counter@GOTPCREL]
mov dword ptr [r11], eax
mov r11, qword ptr [rip+counter@GOTPCREL]
lock inc dword ptr [r11]
mov r10, qword ptr [rip+scalar@GOTPCREL]
movsd xmm0, qword ptr [r10]
mov rax, qword ptr [rip+imported@GOTPCREL]
mov rax, qword ptr [rip+imported@GOTPCREL]
ret
