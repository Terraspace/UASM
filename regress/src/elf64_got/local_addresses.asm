option casemap:none
option elfpic:1
public local_data,hidden_data
option elfvisibility:hidden_data:hidden
.data
padding dq 99
local_data dq 101
hidden_data dq 102
private_data dq 103
.code
 lea rax,local_data+8
 mov rax,offset hidden_data+8
 mov rax,offset private_data-8
 mov rax,hidden_data
 mov rax,private_data
 mov rax,GOT(private_data,r12)
 mov GOT(hidden_data,r13),rax
 mov rax,private_func
 ret
private_func:
 ret
end
