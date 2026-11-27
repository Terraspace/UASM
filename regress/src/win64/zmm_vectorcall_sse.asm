.x64
option casemap:none
option evex:1
option arch:sse
option frame:auto
TwoVectors struct
 first __m512 <>
 second __m512 <>
TwoVectors ends
.data
vec __m512 <>
pair TwoVectors <>
.code
option stackbase:rbp
option win64:15
One_rbp proto vectorcall (zmmword) :zmmword
One_rbp proc vectorcall frame uses zmm8, arg:zmmword
 mov rax,arg
 vmovdqu64 zmm0,[rax]
 ret
One_rbp endp
Seven_rbp proc vectorcall frame a0:zmmword,a1:zmmword,a2:zmmword,a3:zmmword,a4:zmmword,a5:zmmword,a6:zmmword
 mov rax,a0
 vmovdqu64 zmm0,[rax]
 mov rax,a6
 vmovdqu64 zmm5,[rax]
 ret
Seven_rbp endp
HVA_rbp proc vectorcall frame arg:TwoVectors
 mov rax,arg
 vmovdqu64 zmm0,[rax]
 vmovdqu64 zmm1,[rax+64]
 ret
HVA_rbp endp
Caller_rbp proc frame
 invoke One_rbp,vec
 invoke One_rbp,zmm16
 invoke Seven_rbp,vec,vec,vec,vec,vec,vec,vec
 invoke HVA_rbp,pair
 ret
Caller_rbp endp
option stackbase:rsp
option win64:15
One_rsp proto vectorcall (zmmword) :zmmword
One_rsp proc vectorcall frame uses zmm8, arg:zmmword
 mov rax,arg
 vmovdqu64 zmm0,[rax]
 ret
One_rsp endp
Seven_rsp proc vectorcall frame a0:zmmword,a1:zmmword,a2:zmmword,a3:zmmword,a4:zmmword,a5:zmmword,a6:zmmword
 mov rax,a0
 vmovdqu64 zmm0,[rax]
 mov rax,a6
 vmovdqu64 zmm5,[rax]
 ret
Seven_rsp endp
HVA_rsp proc vectorcall frame arg:TwoVectors
 mov rax,arg
 vmovdqu64 zmm0,[rax]
 vmovdqu64 zmm1,[rax+64]
 ret
HVA_rsp endp
Caller_rsp proc frame
 invoke One_rsp,vec
 invoke One_rsp,zmm16
 invoke Seven_rsp,vec,vec,vec,vec,vec,vec,vec
 invoke HVA_rsp,pair
 ret
Caller_rsp endp
end
