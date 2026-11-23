option casemap:none
option elfpic:1
extern counter:dword,qvalue:qword,bvalue:byte,scalar:real8,other:dword
.code
option elfpic:0
mov eax,GOT(counter,r11)
end
