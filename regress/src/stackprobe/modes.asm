; Issue #104: dependency-free Win64 probes.
option casemap:none
option frame:auto
.code
option stackbase:rbp
option win64:1
mode_1 proc frame uses rbx r12 xmm6, arg1:qword, arg2:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
mode_1 endp
option stackbase:rbp
option win64:2
mode_2 proc frame uses rbx r12 xmm6, arg1:qword, arg2:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
mode_2 endp
option stackbase:rbp
option win64:3
mode_3 proc frame uses rbx r12 xmm6, arg1:qword, arg2:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
mode_3 endp
option stackbase:rbp
option win64:4
mode_4 proc frame uses rbx r12 xmm6, arg1:qword, arg2:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
mode_4 endp
option stackbase:rbp
option win64:5
mode_5 proc frame uses rbx r12 xmm6, arg1:qword, arg2:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
mode_5 endp
option stackbase:rbp
option win64:6
mode_6 proc frame uses rbx r12 xmm6, arg1:qword, arg2:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
mode_6 endp
option stackbase:rbp
option win64:7
mode_7 proc frame uses rbx r12 xmm6, arg1:qword, arg2:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
mode_7 endp
option stackbase:rsp
option win64:8
mode_8 proc frame uses rbx r12 xmm6, arg1:qword, arg2:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
mode_8 endp
option stackbase:rsp
option win64:9
mode_9 proc frame uses rbx r12 xmm6, arg1:qword, arg2:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
mode_9 endp
option stackbase:rsp
option win64:10
mode_10 proc frame uses rbx r12 xmm6, arg1:qword, arg2:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
mode_10 endp
option stackbase:rsp
option win64:11
mode_11 proc frame uses rbx r12 xmm6, arg1:qword, arg2:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
mode_11 endp
option stackbase:rsp
option win64:12
mode_12 proc frame uses rbx r12 xmm6, arg1:qword, arg2:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
mode_12 endp
option stackbase:rsp
option win64:13
mode_13 proc frame uses rbx r12 xmm6, arg1:qword, arg2:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
mode_13 endp
option stackbase:rsp
option win64:14
mode_14 proc frame uses rbx r12 xmm6, arg1:qword, arg2:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
mode_14 endp
option stackbase:rsp
option win64:15
mode_15 proc frame uses rbx r12 xmm6, arg1:qword, arg2:real8
 local storage[65536]:byte
 mov storage[0],1
 ret
mode_15 endp
end
