option casemap:none
option elfpic:1
extern counter:dword,qvalue:qword,bvalue:byte,scalar:real8,other:dword
.code
{evex} vmovsd xmm0,GOT(scalar,r11)
end
