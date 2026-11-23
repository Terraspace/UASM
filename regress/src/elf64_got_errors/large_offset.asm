option casemap:none
option elfpic:1
extern counter:dword,qvalue:qword,bvalue:byte,scalar:real8,other:dword
.code
mov eax,GOT(counter+80000000h,r11)
end
