option casemap:none
option elfpic:1
option frame:auto
extern counter:dword,values:dword,real_value:real8,callback:qword
imported_fn proto SYSTEMV
consume proto SYSTEMV :ptr dword
public call_pointer,tail_pointer,check_regs,get_counter,set_counter,bump_counter,get_second,get_real,get_pointer,get_offset,get_function,check_flags,adc_counter,call_consume,local_counter,get_local
.data
local_counter dd 31
.code
get_counter:
 mov eax,counter
 ret
set_counter:
 mov GOT(counter,r11),edi
 ret
bump_counter:
 lock inc GOT(counter,r11)
 ret
get_second:
 mov eax,GOT(values+4,r11)
 ret
get_real:
 movsd xmm0,GOT(real_value,r10)
 ret
get_pointer:
 lea rax,counter
 ret
get_offset:
 mov rax,offset values+4
 ret
get_function:
 mov rax,imported_fn
 ret
check_flags:
 stc
 mov eax,counter
 setc al
 movzx eax,al
 ret
adc_counter:
 mov eax,0
 stc
 adc GOT(counter,r11),eax
 ret
get_local:
 mov eax,local_counter
 ret
check_regs:
 mov r11,12345
 mov eax,counter
 cmp r11,12345
 sete al
 movzx eax,al
 ret
call_pointer proc SYSTEMV
 call GOT(callback,r11)
 ret
call_pointer endp
tail_pointer:
 jmp GOT(callback,r11)
call_consume proc SYSTEMV
 invoke consume,addr counter
 ret
call_consume endp
end
