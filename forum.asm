Hi everyone

I have here my version of JWasm212pre
what is the difference?
  1. built in .for - .endfor hll
  2. sophisticated RSP stack base for 64 bit   
  3. more compact stack usage
  4. first variable is always aligned to 16 byte
  5. if there is no invoke it will not allocate shadow space
  6. if there are no locals and no invoke there is no need to alocate the stack
  

to use 64 bit with this version you need to use 'option win64 : 11'  (eleven)

option casemap : none
option win64 : 11
option frame : auto
option stackbase : rsp

here are examples to speak for itself:


test1 PROC FRAME param : QWORD        ;this function has no locals but uses param
000000013FCE1060 48 89 4C 24 08       mov         qword ptr [param],rcx  ;param is saved  
  .if (param && rax == rcx)                            ;but no need to alocate the stack
000000013FCE1065 48 83 7C 24 08 00    cmp         qword ptr [param],0  
000000013FCE106B 74 0E                je          test1+1Bh (013FCE107Bh)  
000000013FCE106D 48 3B C1             cmp         rax,rcx  
000000013FCE1070 75 09                jne         test1+1Bh (013FCE107Bh)  
    mov rdx,1
000000013FCE1072 48 C7 C2 01 00 00 00 mov         rdx,1  
  .else 
000000013FCE1079 EB 05                jmp         test1+20h (013FCE1080h)  
    mov rax,param
000000013FCE107B 48 8B 44 24 08       mov         rax,qword ptr [param]  
  .endif
ret
000000013FCE1080 C3                   ret  
test1 ENDP
;---------------------------------------------------------------------------------
test1 PROC FRAME param : QWORD       ;this function has no locals but uses rcx instead of param
.if (rcx && rax == rcx)              ;no need to save rcx in the shadow space
000000013FBC1060 48 23 C9             and         rcx,rcx  
000000013FBC1063 74 0E                je          test1+13h (013FBC1073h)  
000000013FBC1065 48 3B C1             cmp         rax,rcx  
000000013FBC1068 75 09                jne         test1+13h (013FBC1073h)  
    mov rdx,1
000000013FBC106A 48 C7 C2 01 00 00 00 mov         rdx,1  
.else 
000000013FBC1071 EB 03                jmp         test1+16h (013FBC1076h)  
    mov rax,rcx
000000013FBC1073 48 8B C1             mov         rax,rcx  
.endif
ret
000000013FBC1076 C3                   ret  
test1 ENDP

this version has invoke in it:

test PROC  FRAME USES rbx rbp rdi   a : QWORD   
000000013FD81128 48 89 4C 24 08       mov         qword ptr [rsp+8],rcx   ;a param is used so it's saved
000000013FD8112D 48 89 5C 24 10       mov         qword ptr [rsp+10h],rbx ;store rbx in unused space 
000000013FD81132 48 89 6C 24 18       mov         qword ptr [rsp+18h],rbp ;store rbp in unused space 
000000013FD81137 57                   push        rdi ;even there is still free space push it for alignment
000000013FD81138 48 83 EC 60          sub         rsp,60h  ;40h for vars + 20h for shadows
LOCAL var    : XMMWORD                            ;16 byte vars at the beginning off locals 
LOCAL var1   : XMMWORD                            ;are aligned to 16 byte
LOCAL other  : DWORD  
LOCAL other1 : QWORD     
LOCAL other2 : QWORD
LOCAL var2   : WORD   
LOCAL var3   : BYTE
    mov rax,-1
000000013FD8113C 48 C7 C0 FF FF FF FF mov         rax,0FFFFFFFFFFFFFFFFh  
    mov a,rax
000000013FD81143 48 89 44 24 70       mov         qword ptr [a],rax  
    invoke function,5                 
000000013FD81148 48 C7 C1 05 00 00 00 mov         rcx,5  
000000013FD8114F E8 0C FF FF FF       call        function (013FD81060h)  
    movaps var, xmm1             
000000013FD81154 0F 29 4C 24 20       movaps      xmmword ptr [var],xmm1  
    movaps var1, xmm2        
000000013FD81159 0F 29 54 24 30       movaps      xmmword ptr [var1],xmm2  
    mov other1, -1   
000000013FD8115E 48 C7 44 24 44 FF FF FF FF mov         qword ptr [other1],0FFFFFFFFFFFFFFFFh  
    mov other2, -2   
000000013FD81167 48 C7 44 24 50 FE FF FF FF mov         qword ptr [other2],0FFFFFFFFFFFFFFFEh  
    inc rax
000000013FD81170 48 FF C0             inc         rax  
    mov other2, rax
000000013FD81173 48 89 44 24 50       mov         qword ptr [other2],rax  
    inc rax  
000000013FD81178 48 FF C0             inc         rax  
    mov other2, rax
000000013FD8117B 48 89 44 24 50       mov         qword ptr [other2],rax  
    mov rax, 1111111h
000000013FD81180 48 C7 C0 11 11 11 01 mov         rax,1111111h  
    movd xmm1, rax
000000013FD81187 66 48 0F 6E C8       movd        xmm1,rax  
    shl rax, 1  
000000013FD8118C 48 D1 E0             shl         rax,1  
    .for (rax=rcx¦r8¦rcx++, r8--)
000000013FD8118F 48 8B C1             mov         rax,rcx  
000000013FD81192 4D 23 C0             and         r8,r8  
000000013FD81195 74 0A                je          test+79h (013FD811A1h)  
      mov[rcx], dl
000000013FD81197 88 11                mov         byte ptr [rcx],dl  
    .endfor
000000013FD81199 48 FF C1             inc         rcx  ;note how it uses INC here instead of ADD RCX,1
    .endfor
000000013FD8119C 49 FF C8             dec         r8  ;note how it uses DEC here instead of SUB r8,1
000000013FD8119F EB F1                jmp         test+6Ah (013FD81192h)  
    ret    
000000013FD811A1 48 83 C4 60          add         rsp,60h  
000000013FD811A5 5F                   pop         rdi  
000000013FD811A6 48 8B 5C 24 10       mov         rbx,qword ptr [rsp+10h]  
000000013FD811AB 48 8B 6C 24 18       mov         rbp,qword ptr [rsp+18h]  
000000013FD811B0 C3                   ret  
test ENDP
;---------------------------------------------------------------------------------
and the version without invoke 

test PROC  FRAME USES rbx rbp rdi   a : QWORD
000000013F4C1128 48 89 4C 24 08       mov         qword ptr [rsp+8],rcx  
000000013F4C112D 48 89 5C 24 10       mov         qword ptr [var1],rbx  
000000013F4C1132 48 89 6C 24 18       mov         qword ptr [rsp+18h],rbp  
000000013F4C1137 57                   push        rdi  
000000013F4C1138 48 83 EC 40          sub         rsp,40h  ;only space for locals alocated
LOCAL var    : XMMWORD                                     ;because no invoke calls
LOCAL var1   : XMMWORD
LOCAL other  : DWORD
LOCAL other1 : QWORD
LOCAL other2 : QWORD
LOCAL var2   : WORD
LOCAL var3   : BYTE
mov rax, -1
000000013F4C113C 48 C7 C0 FF FF FF FF mov         rax,0FFFFFFFFFFFFFFFFh  
mov a, rax
000000013F4C1143 48 89 44 24 50       mov         qword ptr [a],rax  
   ; invoke test1, 5
    movaps var, xmm1             
000000013F4C1148 0F 29 0C 24          movaps      xmmword ptr [rsp],xmm1  
    movaps var1, xmm2        
000000013F4C114C 0F 29 54 24 10       movaps      xmmword ptr [var1],xmm2  
    mov other1, -1   
000000013F4C1151 48 C7 44 24 24 FF FF FF FF mov         qword ptr [other1],0FFFFFFFFFFFFFFFFh  
    mov other2, -2   
000000013F4C115A 48 C7 44 24 30 FE FF FF FF mov         qword ptr [other2],0FFFFFFFFFFFFFFFEh  
    inc rax
000000013F4C1163 48 FF C0             inc         rax  
    mov other2, rax
000000013F4C1166 48 89 44 24 30       mov         qword ptr [other2],rax  
    inc rax  
000000013F4C116B 48 FF C0             inc         rax  
    mov other2, rax
000000013F4C116E 48 89 44 24 30       mov         qword ptr [other2],rax  
    mov rax, 1111111h
000000013F4C1173 48 C7 C0 11 11 11 01 mov         rax,1111111h  
    movd xmm1, rax
000000013F4C117A 66 48 0F 6E C8       movd        xmm1,rax  
    shl rax, 1  
000000013F4C117F 48 D1 E0             shl         rax,1  
    .for (rax=rcx¦r8¦rcx++, r8--)
000000013F4C1182 48 8B C1             mov         rax,rcx  
000000013F4C1185 4D 23 C0             and         r8,r8  
000000013F4C1188 74 0A                je          test+6Ch (013F4C1194h)  
      mov[rcx], dl
000000013F4C118A 88 11                mov         byte ptr [rcx],dl  
    .endfor
000000013F4C118C 48 FF C1             inc         rcx  
000000013F4C118F 49 FF C8             dec         r8  
    .endfor
000000013F4C1192 EB F1                jmp         test+5Dh (013F4C1185h)  
    ret    
000000013F4C1194 48 83 C4 40          add         rsp,40h  
000000013F4C1198 5F                   pop         rdi  
000000013F4C1199 48 8B 5C 24 10       mov         rbx,qword ptr [var1]  
000000013F4C119E 48 8B 6C 24 18       mov         rbp,qword ptr [rsp+18h]  
000000013F4C11A3 C3                   ret  
test ENDP
;---------------------------------------------------------------------------------
