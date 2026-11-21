; MOV m64 accepts signed values and MASM unsigned imm32 bit patterns.
.x64
_TEXT SEGMENT USE64
mov qword ptr [rax],0
mov qword ptr [rax],7fffffffh
mov qword ptr [rax],-80000000h
mov qword ptr [rax],0ffffffff80000000h
mov qword ptr [rax],-1
mov rax,1122334455667788h
mov rbx,1122334455667788h
mov r15,1122334455667788h
mov dword ptr [rax],0ffffffffh
mov qword ptr [rax],80000000h
mov qword ptr [rax],0ffff1223h
mov qword ptr [rax],0ffffffffh
mov qword ptr [rax],-80000001h
mov qword ptr [rax],-0ffffffffh
_TEXT ENDS
END
