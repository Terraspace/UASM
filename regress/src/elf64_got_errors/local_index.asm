option casemap:none
option elfpic:1
extern counter:dword,qvalue:qword,bvalue:byte,scalar:real8,other:dword
.code
jmp next
private_var dd 1
next:
mov eax,private_var[rbx]
end
