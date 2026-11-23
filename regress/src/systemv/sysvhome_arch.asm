; SYSVHOME honours ARCH for scalar/XMM homes; wide operands require AVX.
option casemap:none
option sysvhome:1
.code
option arch:sse
sse_homes proc uses xmm6 arg_f:real4,arg_d:real8,arg_v:oword
 lea rax,arg_f
 lea rax,arg_d
 lea rax,arg_v
 ret
sse_homes endp
option arch:avx
avx_homes proc uses xmm6 arg_f:real4,arg_d:real8,arg_v:oword
 lea rax,arg_f
 lea rax,arg_d
 lea rax,arg_v
 ret
avx_homes endp
option arch:sse
sse_again_homes proc uses xmm6 arg_f:real4,arg_d:real8,arg_v:oword
 lea rax,arg_f
 lea rax,arg_d
 lea rax,arg_v
 ret
sse_again_homes endp
end

