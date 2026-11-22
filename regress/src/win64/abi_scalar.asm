; Scalar Win64 ABI: all modes on both bases; memory/stack and variadic args.
option casemap:none
option arch:sse
scalar_sink proto :qword,:qword,:qword,:qword,:qword,:qword
scalar_variadic proto :dword,:vararg
scalar_fixed proto :real8,:vararg
scalar_fixed4 proto :real4,:vararg
scalar_capture proto :real8,:real8,:real8,:real8,:vararg
.data
scalar_f real4 1.5
scalar_d real8 2.5
.code
option stackbase:rsp
option win64:1
scalar_rsp_1 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rsp_1 endp
scalar_call_rsp_1 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rsp_1 endp
option stackbase:rsp
option win64:2
scalar_rsp_2 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rsp_2 endp
scalar_call_rsp_2 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rsp_2 endp
option stackbase:rsp
option win64:3
scalar_rsp_3 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rsp_3 endp
scalar_call_rsp_3 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rsp_3 endp
option stackbase:rsp
option win64:4
scalar_rsp_4 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rsp_4 endp
scalar_call_rsp_4 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rsp_4 endp
option stackbase:rsp
option win64:5
scalar_rsp_5 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rsp_5 endp
scalar_call_rsp_5 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rsp_5 endp
option stackbase:rsp
option win64:6
scalar_rsp_6 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rsp_6 endp
scalar_call_rsp_6 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rsp_6 endp
option stackbase:rsp
option win64:7
scalar_rsp_7 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rsp_7 endp
scalar_call_rsp_7 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rsp_7 endp
option stackbase:rsp
option win64:8
scalar_rsp_8 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rsp_8 endp
scalar_call_rsp_8 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rsp_8 endp
option stackbase:rsp
option win64:9
scalar_rsp_9 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rsp_9 endp
scalar_call_rsp_9 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rsp_9 endp
option stackbase:rsp
option win64:10
scalar_rsp_10 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rsp_10 endp
scalar_call_rsp_10 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rsp_10 endp
option stackbase:rsp
option win64:11
scalar_rsp_11 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rsp_11 endp
scalar_call_rsp_11 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rsp_11 endp
option stackbase:rsp
option win64:12
scalar_rsp_12 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rsp_12 endp
scalar_call_rsp_12 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rsp_12 endp
option stackbase:rsp
option win64:13
scalar_rsp_13 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rsp_13 endp
scalar_call_rsp_13 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rsp_13 endp
option stackbase:rsp
option win64:14
scalar_rsp_14 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rsp_14 endp
scalar_call_rsp_14 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rsp_14 endp
option stackbase:rsp
option win64:15
scalar_rsp_15 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rsp_15 endp
scalar_call_rsp_15 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rsp_15 endp
option stackbase:rbp
option win64:1
scalar_rbp_1 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rbp_1 endp
scalar_call_rbp_1 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rbp_1 endp
option stackbase:rbp
option win64:2
scalar_rbp_2 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rbp_2 endp
scalar_call_rbp_2 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rbp_2 endp
option stackbase:rbp
option win64:3
scalar_rbp_3 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rbp_3 endp
scalar_call_rbp_3 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rbp_3 endp
option stackbase:rbp
option win64:4
scalar_rbp_4 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rbp_4 endp
scalar_call_rbp_4 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rbp_4 endp
option stackbase:rbp
option win64:5
scalar_rbp_5 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rbp_5 endp
scalar_call_rbp_5 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rbp_5 endp
option stackbase:rbp
option win64:6
scalar_rbp_6 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rbp_6 endp
scalar_call_rbp_6 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rbp_6 endp
option stackbase:rbp
option win64:7
scalar_rbp_7 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rbp_7 endp
scalar_call_rbp_7 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rbp_7 endp
option stackbase:rbp
option win64:8
scalar_rbp_8 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rbp_8 endp
scalar_call_rbp_8 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rbp_8 endp
option stackbase:rbp
option win64:9
scalar_rbp_9 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rbp_9 endp
scalar_call_rbp_9 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rbp_9 endp
option stackbase:rbp
option win64:10
scalar_rbp_10 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rbp_10 endp
scalar_call_rbp_10 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rbp_10 endp
option stackbase:rbp
option win64:11
scalar_rbp_11 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rbp_11 endp
scalar_call_rbp_11 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rbp_11 endp
option stackbase:rbp
option win64:12
scalar_rbp_12 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rbp_12 endp
scalar_call_rbp_12 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rbp_12 endp
option stackbase:rbp
option win64:13
scalar_rbp_13 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rbp_13 endp
scalar_call_rbp_13 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rbp_13 endp
option stackbase:rbp
option win64:14
scalar_rbp_14 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rbp_14 endp
scalar_call_rbp_14 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rbp_14 endp
option stackbase:rbp
option win64:15
scalar_rbp_15 proc frame uses rbx r12 xmm6, p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 local loc[32]:byte
 mov loc[0],77
 mov rax,rcx
 add rax,rdx
 add rax,r8
 add rax,r9
 add rax,p5
 add rax,p6
 ret
scalar_rbp_15 endp
scalar_call_rbp_15 proc frame uses rbx r12 xmm6
 local loc:qword
 mov loc,100
 invoke scalar_sink,loc,2,3,4,5,6
 add rax,loc
 ret
scalar_call_rbp_15 endp
option stackbase:rsp
option win64:1
scalar_var_rsp_1 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rsp_1 endp
option stackbase:rsp
option win64:2
scalar_var_rsp_2 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rsp_2 endp
option stackbase:rsp
option win64:3
scalar_var_rsp_3 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rsp_3 endp
option stackbase:rsp
option win64:4
scalar_var_rsp_4 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rsp_4 endp
option stackbase:rsp
option win64:5
scalar_var_rsp_5 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rsp_5 endp
option stackbase:rsp
option win64:6
scalar_var_rsp_6 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rsp_6 endp
option stackbase:rsp
option win64:7
scalar_var_rsp_7 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rsp_7 endp
option stackbase:rsp
option win64:8
scalar_var_rsp_8 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rsp_8 endp
option stackbase:rsp
option win64:9
scalar_var_rsp_9 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rsp_9 endp
option stackbase:rsp
option win64:10
scalar_var_rsp_10 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rsp_10 endp
option stackbase:rsp
option win64:11
scalar_var_rsp_11 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rsp_11 endp
option stackbase:rsp
option win64:12
scalar_var_rsp_12 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rsp_12 endp
option stackbase:rsp
option win64:13
scalar_var_rsp_13 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rsp_13 endp
option stackbase:rsp
option win64:14
scalar_var_rsp_14 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rsp_14 endp
option stackbase:rsp
option win64:15
scalar_var_rsp_15 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rsp_15 endp
option stackbase:rbp
option win64:1
scalar_var_rbp_1 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rbp_1 endp
option stackbase:rbp
option win64:2
scalar_var_rbp_2 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rbp_2 endp
option stackbase:rbp
option win64:3
scalar_var_rbp_3 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rbp_3 endp
option stackbase:rbp
option win64:4
scalar_var_rbp_4 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rbp_4 endp
option stackbase:rbp
option win64:5
scalar_var_rbp_5 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rbp_5 endp
option stackbase:rbp
option win64:6
scalar_var_rbp_6 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rbp_6 endp
option stackbase:rbp
option win64:7
scalar_var_rbp_7 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rbp_7 endp
option stackbase:rbp
option win64:8
scalar_var_rbp_8 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rbp_8 endp
option stackbase:rbp
option win64:9
scalar_var_rbp_9 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rbp_9 endp
option stackbase:rbp
option win64:10
scalar_var_rbp_10 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rbp_10 endp
option stackbase:rbp
option win64:11
scalar_var_rbp_11 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rbp_11 endp
option stackbase:rbp
option win64:12
scalar_var_rbp_12 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rbp_12 endp
option stackbase:rbp
option win64:13
scalar_var_rbp_13 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rbp_13 endp
option stackbase:rbp
option win64:14
scalar_var_rbp_14 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rbp_14 endp
option stackbase:rbp
option win64:15
scalar_var_rbp_15 proc frame uses rbx
 local failed:qword
 mov failed,0
 invoke scalar_variadic,5,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed,scalar_d,scalar_f,3.5,scalar_f,4.5
 add failed,rax
 invoke scalar_fixed4,scalar_f,scalar_d,3.5,scalar_f,4.5
 add failed,rax
 movsd xmm4,scalar_d
 invoke scalar_capture,scalar_d,xmm4,scalar_d,scalar_d,scalar_d
 add failed,rax
 mov r10,scalar_d
 mov r11,scalar_d
 invoke scalar_capture,r10,r11,r10,r11,scalar_d
 add failed,rax
 mov r10d,scalar_f
 invoke scalar_fixed4,r10d,scalar_d,3.5,scalar_f,4.5
 add rax,failed
 ret
scalar_var_rbp_15 endp
.data
public ScalarSums,ScalarCalls,ScalarVariadics
ScalarSums label qword
 dq scalar_rsp_1
 dq scalar_rsp_2
 dq scalar_rsp_3
 dq scalar_rsp_4
 dq scalar_rsp_5
 dq scalar_rsp_6
 dq scalar_rsp_7
 dq scalar_rsp_8
 dq scalar_rsp_9
 dq scalar_rsp_10
 dq scalar_rsp_11
 dq scalar_rsp_12
 dq scalar_rsp_13
 dq scalar_rsp_14
 dq scalar_rsp_15
 dq scalar_rbp_1
 dq scalar_rbp_2
 dq scalar_rbp_3
 dq scalar_rbp_4
 dq scalar_rbp_5
 dq scalar_rbp_6
 dq scalar_rbp_7
 dq scalar_rbp_8
 dq scalar_rbp_9
 dq scalar_rbp_10
 dq scalar_rbp_11
 dq scalar_rbp_12
 dq scalar_rbp_13
 dq scalar_rbp_14
 dq scalar_rbp_15
ScalarCalls label qword
 dq scalar_call_rsp_1
 dq scalar_call_rsp_2
 dq scalar_call_rsp_3
 dq scalar_call_rsp_4
 dq scalar_call_rsp_5
 dq scalar_call_rsp_6
 dq scalar_call_rsp_7
 dq scalar_call_rsp_8
 dq scalar_call_rsp_9
 dq scalar_call_rsp_10
 dq scalar_call_rsp_11
 dq scalar_call_rsp_12
 dq scalar_call_rsp_13
 dq scalar_call_rsp_14
 dq scalar_call_rsp_15
 dq scalar_call_rbp_1
 dq scalar_call_rbp_2
 dq scalar_call_rbp_3
 dq scalar_call_rbp_4
 dq scalar_call_rbp_5
 dq scalar_call_rbp_6
 dq scalar_call_rbp_7
 dq scalar_call_rbp_8
 dq scalar_call_rbp_9
 dq scalar_call_rbp_10
 dq scalar_call_rbp_11
 dq scalar_call_rbp_12
 dq scalar_call_rbp_13
 dq scalar_call_rbp_14
 dq scalar_call_rbp_15
ScalarVariadics label qword
 dq scalar_var_rsp_1
 dq scalar_var_rsp_2
 dq scalar_var_rsp_3
 dq scalar_var_rsp_4
 dq scalar_var_rsp_5
 dq scalar_var_rsp_6
 dq scalar_var_rsp_7
 dq scalar_var_rsp_8
 dq scalar_var_rsp_9
 dq scalar_var_rsp_10
 dq scalar_var_rsp_11
 dq scalar_var_rsp_12
 dq scalar_var_rsp_13
 dq scalar_var_rsp_14
 dq scalar_var_rsp_15
 dq scalar_var_rbp_1
 dq scalar_var_rbp_2
 dq scalar_var_rbp_3
 dq scalar_var_rbp_4
 dq scalar_var_rbp_5
 dq scalar_var_rbp_6
 dq scalar_var_rbp_7
 dq scalar_var_rbp_8
 dq scalar_var_rbp_9
 dq scalar_var_rbp_10
 dq scalar_var_rbp_11
 dq scalar_var_rbp_12
 dq scalar_var_rbp_13
 dq scalar_var_rbp_14
 dq scalar_var_rbp_15
end
