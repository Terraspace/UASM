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
align 32
InputWide __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>
.code
option stackbase:rbp
option win64:15
Big_rbp proc frame arg_big:DebugItem
mov rax,arg_big
int 3
ret
Big_rbp endp
Wide_rbp proc vectorcall frame arg_vec256:__m256f
local local_vec256:__m256f
mov rax,arg_vec256
vmovups ymm4,[rax]
vmovups local_vec256,ymm4
int 3
vzeroupper
ret
Wide_rbp endp
option stackbase:rsp
option win64:15
Big_rsp proc frame arg_big:DebugItem
mov rax,arg_big
int 3
ret
Big_rsp endp
Wide_rsp proc vectorcall frame arg_vec256:__m256f
local local_vec256:__m256f
mov rax,arg_vec256
vmovups ymm4,[rax]
vmovups local_vec256,ymm4
int 3
vzeroupper
ret
Wide_rsp endp
option stackbase:rsp
option win64:15
Main proc frame
invoke Big_rbp,SampleDebugItem
invoke Big_rsp,SampleDebugItem
invoke Wide_rbp,InputWide
invoke Wide_rsp,InputWide
invoke ExitProcess,0
Main endp
end Main
