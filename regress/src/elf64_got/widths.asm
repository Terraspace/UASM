option casemap:none
option elfpic:1
extern b:byte,w:word,d:dword,q:qword,v:xmmword,wide:ymmword
.code
 movzx eax,b
 movsx rax,b
 movzx r8d,w
 movsx r9,w
 movsxd r10,d
 mov al,GOT(b,rdi)
 mov ax,GOT(w,rsi)
 mov ah,GOT(b,rdi)
 mov GOT(q,r15),rax
 add GOT(d,r11),3
 adc GOT(d,r11),eax
 cmp GOT(q,r12),rax
 xchg GOT(d,r13),eax
 movdqu xmm1,GOT(v,r14)
 vmovdqu ymm2,GOT(wide,r15)
 mov eax,GOT(d+4,r11)
 mov eax,GOT(d-4,r11)
 ret
end
