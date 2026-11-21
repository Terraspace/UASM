; System V regression: vector512
; run_tests returns zero when its ABI assertions pass.
option casemap:none

option redzone:no
option evex:1
.code
save_zmm8_run_tests proc SYSTEMV uses rbx zmm8
local v:qword
mov v,42
mov rax,v
sub rax,42
ret
save_zmm8_run_tests endp

option redzone:no
option evex:1
.code
vector64_0_callee proc SYSTEMV a0:zmmword,a1:zmmword,a2:zmmword,a3:zmmword,a4:zmmword,a5:zmmword,a6:zmmword,a7:zmmword,a8:zmmword
mov rax,qword ptr a8
sub rax,42
lea r10,a8
and r10,63
or rax,r10
ret
vector64_0_callee endp
vector64_0_run_tests proc SYSTEMV
mov eax,42
movq xmm8,rax
invoke vector64_0_callee,zmm0,zmm1,zmm2,zmm3,zmm4,zmm5,zmm6,zmm7,zmm8
ret
vector64_0_run_tests endp

option redzone:no
.code
run_tests proc SYSTEMV uses r12
xor r12d,r12d
invoke save_zmm8_run_tests
or r12,rax
invoke vector64_0_run_tests
or r12,rax
mov rax,r12
ret
run_tests endp
end
