; Runtime companion: link with validation/stackprobe_driver.c on Windows.
option casemap:none
option prologue:none
option epilogue:none
.code
RunProbe proc frame
 sub rsp,56
 .allocstack 56
 .endprolog
 mov [rsp+32],rcx
 mov rcx,rdx
 mov rdx,11223344h
 mov r8,55667788h
 mov r9,12345678h
 mov r10,23456789h
 mov r11,3456789ah
 pcmpeqd xmm0,xmm0
 movdqa xmm1,xmm0
 movdqa xmm2,xmm0
 movdqa xmm3,xmm0
 movdqa xmm4,xmm0
 movdqa xmm5,xmm0
 xor eax,eax
 stc
 mov eax,456789abh
 call qword ptr [rsp+32]
 add rsp,56
 ret
RunProbe endp
option prologue:prologuedef
option epilogue:epiloguedef
option frame:auto
option framepreserveflags:on
option stackbase:rbp
option win64:1
probe_m1 proc frame uses rbx r12 r13 r14 r15
 local storage[1048576]:byte
 mov [rcx],rax
 mov [rcx+8],rdx
 mov [rcx+16],r8
 mov [rcx+24],r9
 mov [rcx+32],r10
 mov [rcx+40],r11
 pushfq
 pop rax
 mov [rcx+48],rax
 movdqu [rcx+56],xmm0
 movdqu [rcx+72],xmm1
 movdqu [rcx+88],xmm2
 movdqu [rcx+104],xmm3
 movdqu [rcx+120],xmm4
 movdqu [rcx+136],xmm5
 mov storage[0],1
 mov storage[1048575],2
 ret
probe_m1 endp
option stackbase:rbp
option win64:2
probe_m2 proc frame uses rbx r12 r13 r14 r15
 local storage[1048576]:byte
 mov [rcx],rax
 mov [rcx+8],rdx
 mov [rcx+16],r8
 mov [rcx+24],r9
 mov [rcx+32],r10
 mov [rcx+40],r11
 pushfq
 pop rax
 mov [rcx+48],rax
 movdqu [rcx+56],xmm0
 movdqu [rcx+72],xmm1
 movdqu [rcx+88],xmm2
 movdqu [rcx+104],xmm3
 movdqu [rcx+120],xmm4
 movdqu [rcx+136],xmm5
 mov storage[0],1
 mov storage[1048575],2
 ret
probe_m2 endp
option stackbase:rbp
option win64:3
probe_m3 proc frame uses rbx r12 r13 r14 r15
 local storage[1048576]:byte
 mov [rcx],rax
 mov [rcx+8],rdx
 mov [rcx+16],r8
 mov [rcx+24],r9
 mov [rcx+32],r10
 mov [rcx+40],r11
 pushfq
 pop rax
 mov [rcx+48],rax
 movdqu [rcx+56],xmm0
 movdqu [rcx+72],xmm1
 movdqu [rcx+88],xmm2
 movdqu [rcx+104],xmm3
 movdqu [rcx+120],xmm4
 movdqu [rcx+136],xmm5
 mov storage[0],1
 mov storage[1048575],2
 ret
probe_m3 endp
option stackbase:rbp
option win64:4
probe_m4 proc frame uses rbx r12 r13 r14 r15
 local storage[1048576]:byte
 mov [rcx],rax
 mov [rcx+8],rdx
 mov [rcx+16],r8
 mov [rcx+24],r9
 mov [rcx+32],r10
 mov [rcx+40],r11
 pushfq
 pop rax
 mov [rcx+48],rax
 movdqu [rcx+56],xmm0
 movdqu [rcx+72],xmm1
 movdqu [rcx+88],xmm2
 movdqu [rcx+104],xmm3
 movdqu [rcx+120],xmm4
 movdqu [rcx+136],xmm5
 mov storage[0],1
 mov storage[1048575],2
 ret
probe_m4 endp
option stackbase:rbp
option win64:5
probe_m5 proc frame uses rbx r12 r13 r14 r15
 local storage[1048576]:byte
 mov [rcx],rax
 mov [rcx+8],rdx
 mov [rcx+16],r8
 mov [rcx+24],r9
 mov [rcx+32],r10
 mov [rcx+40],r11
 pushfq
 pop rax
 mov [rcx+48],rax
 movdqu [rcx+56],xmm0
 movdqu [rcx+72],xmm1
 movdqu [rcx+88],xmm2
 movdqu [rcx+104],xmm3
 movdqu [rcx+120],xmm4
 movdqu [rcx+136],xmm5
 mov storage[0],1
 mov storage[1048575],2
 ret
probe_m5 endp
option stackbase:rbp
option win64:6
probe_m6 proc frame uses rbx r12 r13 r14 r15
 local storage[1048576]:byte
 mov [rcx],rax
 mov [rcx+8],rdx
 mov [rcx+16],r8
 mov [rcx+24],r9
 mov [rcx+32],r10
 mov [rcx+40],r11
 pushfq
 pop rax
 mov [rcx+48],rax
 movdqu [rcx+56],xmm0
 movdqu [rcx+72],xmm1
 movdqu [rcx+88],xmm2
 movdqu [rcx+104],xmm3
 movdqu [rcx+120],xmm4
 movdqu [rcx+136],xmm5
 mov storage[0],1
 mov storage[1048575],2
 ret
probe_m6 endp
option stackbase:rbp
option win64:7
probe_m7 proc frame uses rbx r12 r13 r14 r15
 local storage[1048576]:byte
 mov [rcx],rax
 mov [rcx+8],rdx
 mov [rcx+16],r8
 mov [rcx+24],r9
 mov [rcx+32],r10
 mov [rcx+40],r11
 pushfq
 pop rax
 mov [rcx+48],rax
 movdqu [rcx+56],xmm0
 movdqu [rcx+72],xmm1
 movdqu [rcx+88],xmm2
 movdqu [rcx+104],xmm3
 movdqu [rcx+120],xmm4
 movdqu [rcx+136],xmm5
 mov storage[0],1
 mov storage[1048575],2
 ret
probe_m7 endp
option stackbase:rsp
option win64:8
probe_m8 proc frame uses rbx r12 r13 r14 r15
 local storage[1048576]:byte
 mov [rcx],rax
 mov [rcx+8],rdx
 mov [rcx+16],r8
 mov [rcx+24],r9
 mov [rcx+32],r10
 mov [rcx+40],r11
 pushfq
 pop rax
 mov [rcx+48],rax
 movdqu [rcx+56],xmm0
 movdqu [rcx+72],xmm1
 movdqu [rcx+88],xmm2
 movdqu [rcx+104],xmm3
 movdqu [rcx+120],xmm4
 movdqu [rcx+136],xmm5
 mov storage[0],1
 mov storage[1048575],2
 ret
probe_m8 endp
option stackbase:rsp
option win64:9
probe_m9 proc frame uses rbx r12 r13 r14 r15
 local storage[1048576]:byte
 mov [rcx],rax
 mov [rcx+8],rdx
 mov [rcx+16],r8
 mov [rcx+24],r9
 mov [rcx+32],r10
 mov [rcx+40],r11
 pushfq
 pop rax
 mov [rcx+48],rax
 movdqu [rcx+56],xmm0
 movdqu [rcx+72],xmm1
 movdqu [rcx+88],xmm2
 movdqu [rcx+104],xmm3
 movdqu [rcx+120],xmm4
 movdqu [rcx+136],xmm5
 mov storage[0],1
 mov storage[1048575],2
 ret
probe_m9 endp
option stackbase:rsp
option win64:10
probe_m10 proc frame uses rbx r12 r13 r14 r15
 local storage[1048576]:byte
 mov [rcx],rax
 mov [rcx+8],rdx
 mov [rcx+16],r8
 mov [rcx+24],r9
 mov [rcx+32],r10
 mov [rcx+40],r11
 pushfq
 pop rax
 mov [rcx+48],rax
 movdqu [rcx+56],xmm0
 movdqu [rcx+72],xmm1
 movdqu [rcx+88],xmm2
 movdqu [rcx+104],xmm3
 movdqu [rcx+120],xmm4
 movdqu [rcx+136],xmm5
 mov storage[0],1
 mov storage[1048575],2
 ret
probe_m10 endp
option stackbase:rsp
option win64:11
probe_m11 proc frame uses rbx r12 r13 r14 r15
 local storage[1048576]:byte
 mov [rcx],rax
 mov [rcx+8],rdx
 mov [rcx+16],r8
 mov [rcx+24],r9
 mov [rcx+32],r10
 mov [rcx+40],r11
 pushfq
 pop rax
 mov [rcx+48],rax
 movdqu [rcx+56],xmm0
 movdqu [rcx+72],xmm1
 movdqu [rcx+88],xmm2
 movdqu [rcx+104],xmm3
 movdqu [rcx+120],xmm4
 movdqu [rcx+136],xmm5
 mov storage[0],1
 mov storage[1048575],2
 ret
probe_m11 endp
option stackbase:rsp
option win64:12
probe_m12 proc frame uses rbx r12 r13 r14 r15
 local storage[1048576]:byte
 mov [rcx],rax
 mov [rcx+8],rdx
 mov [rcx+16],r8
 mov [rcx+24],r9
 mov [rcx+32],r10
 mov [rcx+40],r11
 pushfq
 pop rax
 mov [rcx+48],rax
 movdqu [rcx+56],xmm0
 movdqu [rcx+72],xmm1
 movdqu [rcx+88],xmm2
 movdqu [rcx+104],xmm3
 movdqu [rcx+120],xmm4
 movdqu [rcx+136],xmm5
 mov storage[0],1
 mov storage[1048575],2
 ret
probe_m12 endp
option stackbase:rsp
option win64:13
probe_m13 proc frame uses rbx r12 r13 r14 r15
 local storage[1048576]:byte
 mov [rcx],rax
 mov [rcx+8],rdx
 mov [rcx+16],r8
 mov [rcx+24],r9
 mov [rcx+32],r10
 mov [rcx+40],r11
 pushfq
 pop rax
 mov [rcx+48],rax
 movdqu [rcx+56],xmm0
 movdqu [rcx+72],xmm1
 movdqu [rcx+88],xmm2
 movdqu [rcx+104],xmm3
 movdqu [rcx+120],xmm4
 movdqu [rcx+136],xmm5
 mov storage[0],1
 mov storage[1048575],2
 ret
probe_m13 endp
option stackbase:rsp
option win64:14
probe_m14 proc frame uses rbx r12 r13 r14 r15
 local storage[1048576]:byte
 mov [rcx],rax
 mov [rcx+8],rdx
 mov [rcx+16],r8
 mov [rcx+24],r9
 mov [rcx+32],r10
 mov [rcx+40],r11
 pushfq
 pop rax
 mov [rcx+48],rax
 movdqu [rcx+56],xmm0
 movdqu [rcx+72],xmm1
 movdqu [rcx+88],xmm2
 movdqu [rcx+104],xmm3
 movdqu [rcx+120],xmm4
 movdqu [rcx+136],xmm5
 mov storage[0],1
 mov storage[1048575],2
 ret
probe_m14 endp
option stackbase:rsp
option win64:15
probe_m15 proc frame uses rbx r12 r13 r14 r15
 local storage[1048576]:byte
 mov [rcx],rax
 mov [rcx+8],rdx
 mov [rcx+16],r8
 mov [rcx+24],r9
 mov [rcx+32],r10
 mov [rcx+40],r11
 pushfq
 pop rax
 mov [rcx+48],rax
 movdqu [rcx+56],xmm0
 movdqu [rcx+72],xmm1
 movdqu [rcx+88],xmm2
 movdqu [rcx+104],xmm3
 movdqu [rcx+120],xmm4
 movdqu [rcx+136],xmm5
 mov storage[0],1
 mov storage[1048575],2
 ret
probe_m15 endp
end
