; Two pushed GPRs, all home slots occupied, and an aligned XMM save.
option casemap:none
option stackbase:rsp
option win64:15
.code
xmm_frame_alignment proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword
 local storage[32]:byte
 mov rax,p1
 mov rax,p2
 mov rax,p3
 mov rax,p4
 mov storage[0],1
 ret
xmm_frame_alignment endp
end
