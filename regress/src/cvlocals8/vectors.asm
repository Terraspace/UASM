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
option stackbase:rbp
option win64:3
Homed_RBP proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
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
public Homed_RBP_point
Homed_RBP_point::
int 3 ; CHECK: arguments and locals now have known values.
xor eax,eax
ret
Homed_RBP endp
option stackbase:rsp
option win64:3
Homed_RSP proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
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
public Homed_RSP_point
Homed_RSP_point::
int 3 ; CHECK: arguments and locals now have known values.
xor eax,eax
ret
Homed_RSP endp
option stackbase:rbp
option win64:15
Smart_RBP proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
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
public Smart_RBP_point
Smart_RBP_point::
int 3 ; CHECK: arguments and locals now have known values.
xor eax,eax
ret
Smart_RBP endp
option stackbase:rsp
option win64:15
Smart_RSP proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
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
public Smart_RSP_point
Smart_RSP_point::
int 3 ; CHECK: arguments and locals now have known values.
xor eax,eax
ret
Smart_RSP endp
option stackbase:rbp
option win64:2
Registers_RBP proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
public Registers_RBP_point
Registers_RBP_point::
int 3 ; CHECK: arguments and locals now have known values.
xor eax,eax
ret
Registers_RBP endp
option stackbase:rsp
option win64:2
Registers_RSP proc frame uses rbx r12 xmm6, arg_i:qword,arg_d:real8,arg_f:real4,arg_ptr:ptr DebugItem,arg_tail:qword,arg_last:qword
local local_i:qword,local_d:real8,local_ptr:ptr DebugItem,local_vec:__m128f
mov local_i,42
movsd xmm4,LocalDouble
movsd local_d,xmm4
lea rax,SampleDebugItem
mov local_ptr,rax
movups xmm4,InputVector
movups local_vec,xmm4
public Registers_RSP_point
Registers_RSP_point::
int 3 ; CHECK: arguments and locals now have known values.
xor eax,eax
ret
Registers_RSP endp
option stackbase:rbp
option win64:15
Vectors_RBP proc vectorcall frame uses rbx xmm6, arg_vec:__m128f,arg_d:real8,arg_hfa:HF2,arg_ptr:ptr DebugItem,arg_tail:qword
local local_i:qword,local_vec:__m128f
mov local_i,42
mov rax,arg_vec
movups xmm4,[rax]
movups local_vec,xmm4
mov rax,arg_hfa
mov rax,arg_ptr
movsd xmm4,arg_d
mov rax,arg_tail
public Vectors_RBP_point
Vectors_RBP_point::
int 3 ; CHECK arg_vec={1,2,3,4}, arg_hfa={5,6}, local_vec={1,2,3,4}.
xor eax,eax
ret
Vectors_RBP endp
option stackbase:rsp
option win64:15
Vectors_RSP proc vectorcall frame uses rbx xmm6, arg_vec:__m128f,arg_d:real8,arg_hfa:HF2,arg_ptr:ptr DebugItem,arg_tail:qword
local local_i:qword,local_vec:__m128f
mov local_i,42
mov rax,arg_vec
movups xmm4,[rax]
movups local_vec,xmm4
mov rax,arg_hfa
mov rax,arg_ptr
movsd xmm4,arg_d
mov rax,arg_tail
public Vectors_RSP_point
Vectors_RSP_point::
int 3 ; CHECK arg_vec={1,2,3,4}, arg_hfa={5,6}, local_vec={1,2,3,4}.
xor eax,eax
ret
Vectors_RSP endp
option stackbase:rsp
option win64:2
RegisterHFA proc vectorcall frame arg_hfa:HF2
public RegisterHFA_point
RegisterHFA_point::
int 3 ; CHECK arg_hfa={5,6}, split across XMM0 and XMM1.
ret
RegisterHFA endp
option stackbase:rsp
option win64:15
Main proc frame
invoke Homed_RBP,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Homed_RSP,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Smart_RBP,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Smart_RSP,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Registers_RBP,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Registers_RSP,1122334455667788h,InputDouble,InputFloat,addr SampleDebugItem,55667788h,99
invoke Vectors_RBP,InputVector,InputDouble,InputHFA,addr SampleDebugItem,55667788h
invoke Vectors_RSP,InputVector,InputDouble,InputHFA,addr SampleDebugItem,55667788h
invoke RegisterHFA,InputHFA
invoke ExitProcess,0
Main endp
end Main
