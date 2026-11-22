; Independent ML64 oracle: compare both register classes for four fixed
; floating arguments to a variadic target, and check the fifth stack value.
option casemap:none
.code
scalar_capture proc
 movq rax,xmm0
 cmp rax,rcx
 jne bad
 movq rax,xmm1
 cmp rax,rdx
 jne bad
 movq rax,xmm2
 cmp rax,r8
 jne bad
 movq rax,xmm3
 cmp rax,r9
 jne bad
 cmp rax,[rsp+40]
 jne bad
 mov rdx,4004000000000000h
 cmp rax,rdx
 jne bad
 xor eax,eax
 ret
bad:
 mov eax,1
 ret
scalar_capture endp
end
