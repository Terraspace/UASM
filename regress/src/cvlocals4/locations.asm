; Standalone Win64 CodeView manual check. Assemble with -win64 -Zi8.
; Each INT 3 stops after the prologue and local initialisation.
option casemap:none
option stackbase:rsp
option win64:15
ExitProcess proto :dword
DebugItem struct
 count qword ?
 weight real8 ?
 tag dword ?
DebugItem ends
HF2 struct
 x real4 ?
 y real4 ?
HF2 ends
.data
public SampleDebugItem
SampleDebugItem DebugItem <123,6.5,77>
InputDouble real8 3.25
InputFloat real4 1.5
LocalDouble real8 6.5
align 16
InputVector __m128f <1.0,2.0,3.0,4.0>
InputHFA HF2 <5.0,6.0>
.code
Sink proto :qword,:qword,:qword,:qword,:qword,:qword
option stackbase:rbp
option win64:1
Check_rbp_1 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rbp_1_point
Check_rbp_1_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rbp_1 endp
option stackbase:rbp
option win64:2
Check_rbp_2 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
public Check_rbp_2_point
Check_rbp_2_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rbp_2 endp
option stackbase:rbp
option win64:3
Check_rbp_3 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rbp_3_point
Check_rbp_3_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rbp_3 endp
option stackbase:rbp
option win64:4
Check_rbp_4 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
public Check_rbp_4_point
Check_rbp_4_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rbp_4 endp
option stackbase:rbp
option win64:5
Check_rbp_5 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rbp_5_point
Check_rbp_5_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rbp_5 endp
option stackbase:rbp
option win64:6
Check_rbp_6 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
public Check_rbp_6_point
Check_rbp_6_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rbp_6 endp
option stackbase:rbp
option win64:7
Check_rbp_7 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rbp_7_point
Check_rbp_7_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rbp_7 endp
option stackbase:rbp
option win64:8
Check_rbp_8 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rbp_8_point
Check_rbp_8_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rbp_8 endp
option stackbase:rbp
option win64:9
Check_rbp_9 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rbp_9_point
Check_rbp_9_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rbp_9 endp
option stackbase:rbp
option win64:10
Check_rbp_10 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rbp_10_point
Check_rbp_10_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rbp_10 endp
option stackbase:rbp
option win64:11
Check_rbp_11 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rbp_11_point
Check_rbp_11_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rbp_11 endp
option stackbase:rbp
option win64:12
Check_rbp_12 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rbp_12_point
Check_rbp_12_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rbp_12 endp
option stackbase:rbp
option win64:13
Check_rbp_13 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rbp_13_point
Check_rbp_13_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rbp_13 endp
option stackbase:rbp
option win64:14
Check_rbp_14 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rbp_14_point
Check_rbp_14_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rbp_14 endp
option stackbase:rbp
option win64:15
Check_rbp_15 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rbp_15_point
Check_rbp_15_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rbp_15 endp
option stackbase:rsp
option win64:1
Check_rsp_1 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rsp_1_point
Check_rsp_1_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rsp_1 endp
option stackbase:rsp
option win64:2
Check_rsp_2 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
public Check_rsp_2_point
Check_rsp_2_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rsp_2 endp
option stackbase:rsp
option win64:3
Check_rsp_3 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rsp_3_point
Check_rsp_3_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rsp_3 endp
option stackbase:rsp
option win64:4
Check_rsp_4 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
public Check_rsp_4_point
Check_rsp_4_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rsp_4 endp
option stackbase:rsp
option win64:5
Check_rsp_5 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rsp_5_point
Check_rsp_5_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rsp_5 endp
option stackbase:rsp
option win64:6
Check_rsp_6 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
public Check_rsp_6_point
Check_rsp_6_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rsp_6 endp
option stackbase:rsp
option win64:7
Check_rsp_7 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rsp_7_point
Check_rsp_7_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rsp_7 endp
option stackbase:rsp
option win64:8
Check_rsp_8 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rsp_8_point
Check_rsp_8_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rsp_8 endp
option stackbase:rsp
option win64:9
Check_rsp_9 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rsp_9_point
Check_rsp_9_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rsp_9 endp
option stackbase:rsp
option win64:10
Check_rsp_10 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rsp_10_point
Check_rsp_10_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rsp_10 endp
option stackbase:rsp
option win64:11
Check_rsp_11 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rsp_11_point
Check_rsp_11_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rsp_11 endp
option stackbase:rsp
option win64:12
Check_rsp_12 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rsp_12_point
Check_rsp_12_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rsp_12 endp
option stackbase:rsp
option win64:13
Check_rsp_13 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rsp_13_point
Check_rsp_13_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rsp_13 endp
option stackbase:rsp
option win64:14
Check_rsp_14 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rsp_14_point
Check_rsp_14_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rsp_14 endp
option stackbase:rsp
option win64:15
Check_rsp_15 proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
mov rax,arg_i
mov rax,arg_ptr
mov rax,arg_tail
movsd xmm4,arg_d
movss xmm4,arg_f
public Check_rsp_15_point
Check_rsp_15_point::
int 3 ; CHECK: arguments and locals now have known values.
invoke Sink,1,2,3,4,5,6
xor eax,eax
ret
Check_rsp_15 endp
option stackbase:rsp
option win64:15
Sink proc frame a:qword,b:qword,c1:qword,d:qword,e:qword,f:qword
ret
Sink endp
Main proc frame
invoke Check_rbp_1,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rbp_2,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rbp_3,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rbp_4,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rbp_5,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rbp_6,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rbp_7,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rbp_8,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rbp_9,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rbp_10,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rbp_11,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rbp_12,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rbp_13,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rbp_14,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rbp_15,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rsp_1,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rsp_2,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rsp_3,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rsp_4,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rsp_5,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rsp_6,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rsp_7,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rsp_8,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rsp_9,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rsp_10,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rsp_11,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rsp_12,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rsp_13,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rsp_14,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Check_rsp_15,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke ExitProcess,0
Main endp
end Main
