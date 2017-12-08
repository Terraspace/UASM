;
; v2.24 - /elf64 syscall
;
    .code

p1  proc a1:byte, a2:byte, a3:byte, a4:byte, a5:byte, a6:byte
    mov al,a1
    mov al,a2
    mov al,a3
    mov al,a4
    mov al,a5
    mov al,a6
    ret
p1  endp

p2  proc a1:word, a2:word, a3:word, a4:word, a5:word, a6:word
    mov ax,a1
    mov ax,a2
    mov ax,a3
    mov ax,a4
    mov ax,a5
    mov ax,a6
    ret
p2  endp

p4  proc a1:dword, a2:dword, a3:dword, a4:dword, a5:dword, a6:dword
    mov eax,a1
    mov eax,a2
    mov eax,a3
    mov eax,a4
    mov eax,a5
    mov eax,a6
    ret
p4  endp

p8  proc a1:qword, a2:qword, a3:qword, a4:qword, a5:qword, a6:qword
    mov rax,a1
    mov rax,a2
    mov rax,a3
    mov rax,a4
    mov rax,a5
    mov rax,a6
    ret
p8  endp

pf  proc a1:REAL8, a2:REAL8, a3:REAL8, a4:REAL8, a5:REAL8, a6:REAL8
    movups xmm0,a1
    movups xmm1,a2
    movups xmm2,a3
    movups xmm3,a4
    movups xmm4,a5
    movups xmm5,a6
    ret
pf  endp

pp  proc a1:ptr
    local b:dword
    mov b,eax
    mov rax,a1
    ret
pp  endp

pv  proc a1:ptr, a2:vararg
    mov rax,a1
    mov rax,a2
    ret
pv  endp

    ; reduced to call px
    invoke p1,dil,sil,dl,cl,r8b,r9b
    invoke p2,di,si,dx,cx,r8w,r9w
    invoke p4,edi,esi,edx,ecx,r8d,r9d
    invoke p8,rdi,rsi,rdx,rcx,r8,r9
    invoke pf,xmm0,xmm1,xmm2,xmm3,xmm4,xmm5
ifdef __ASMC__
    ; no "reg overwritten" error
    invoke p1,cl,cl,cl,cl,cl,al
    invoke p2,cx,cx,cx,cx,cx,ax
    invoke p4,ecx,ecx,ecx,ecx,ecx,ecx
    invoke p8,rcx,rcx,rcx,rcx,rcx,rcx
    invoke pf,xmm0,xmm0,xmm0,xmm0,xmm0,xmm0
endif
    invoke pp,addr pp
    invoke pv,rax,rax

    end

