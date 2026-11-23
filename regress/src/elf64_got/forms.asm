option casemap:none
option elfpic:1
extern counter:dword, value:qword, scalar:real8
extern imported:proc
.code
 mov eax,counter
 mov rbx,value
 lea rax,counter
 mov rax,offset counter+4
 mov eax,GOT(counter,r11)
 mov GOT(counter,r11),eax
 lock inc GOT(counter,r11)
 movsd xmm0,GOT(scalar,r10)
 mov rax,imported
 lea rax,imported
 ret
end
