option casemap:none
option elfpic:1
extern counter:dword,qvalue:qword,bvalue:byte,scalar:real8,other:dword
.code
f proc SYSTEMV argument:dword
mov GOT(counter,rdi),argument
ret
f endp
end
