option casemap:none
option elfpic:1
extern counter:dword,qvalue:qword,bvalue:byte,scalar:real8,other:dword
.code
lock lea rax,counter
end
