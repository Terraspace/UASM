; System V regression: scalar_stack
; run_tests returns zero when its ABI assertions pass.
option casemap:none

option redzone:no
.code
large_immediate_callee proc SYSTEMV a1:qword,a2:qword,a3:qword,a4:qword,a5:qword,a6:qword,a7:qword
mov rax,a7
ret
large_immediate_callee endp
large_immediate_run_tests proc SYSTEMV
invoke large_immediate_callee,1,2,3,4,5,6,123456789abcdef0h
mov r10,123456789abcdef0h
sub rax,r10
ret
large_immediate_run_tests endp

option redzone:no
.code
recursive_callee proc SYSTEMV n:qword,a2:qword,a3:qword,a4:qword,a5:qword,a6:qword,a7:qword
cmp n,0
je recursive_done
dec n
invoke recursive_callee,n,2,3,4,5,6,7
ret
recursive_done:
mov rax,a7
sub rax,7
ret
recursive_callee endp
recursive_run_tests proc SYSTEMV
invoke recursive_callee,3,2,3,4,5,6,7
ret
recursive_run_tests endp

option redzone:no
.code
small_byte_callee proc SYSTEMV a0:qword,a1:qword,a2:qword,a3:qword,a4:qword,a5:qword,last:byte
movzx eax,last
ret
small_byte_callee endp
small_byte_run_tests proc SYSTEMV
mov r10b,123
invoke small_byte_callee,1,2,3,4,5,6,r10b
sub rax,123
ret
small_byte_run_tests endp

option redzone:no
.code
small_dword_callee proc SYSTEMV a0:qword,a1:qword,a2:qword,a3:qword,a4:qword,a5:qword,last:dword
mov eax,last
ret
small_dword_callee endp
small_dword_run_tests proc SYSTEMV
mov r10d,1234567
invoke small_dword_callee,1,2,3,4,5,6,r10d
sub rax,1234567
ret
small_dword_run_tests endp

option redzone:no
.code
small_qword_callee proc SYSTEMV a0:qword,a1:qword,a2:qword,a3:qword,a4:qword,a5:qword,last:qword
mov rax,last
ret
small_qword_callee endp
small_qword_run_tests proc SYSTEMV
mov r10,1234567890
invoke small_qword_callee,1,2,3,4,5,6,r10
sub rax,1234567890
ret
small_qword_run_tests endp

option redzone:no
.code
small_word_callee proc SYSTEMV a0:qword,a1:qword,a2:qword,a3:qword,a4:qword,a5:qword,last:word
movzx eax,last
ret
small_word_callee endp
small_word_run_tests proc SYSTEMV
mov r10w,12345
invoke small_word_callee,1,2,3,4,5,6,r10w
sub rax,12345
ret
small_word_run_tests endp

option redzone:no
.code
stack_rax_byte_callee proc SYSTEMV g0:qword,g1:qword,g2:qword,g3:qword,g4:qword,g5:qword,keep:qword,last:byte
mov rax,keep
sub rax,123
ret
stack_rax_byte_callee endp
stack_rax_byte_run_tests proc SYSTEMV
local v:byte
mov v,0
mov eax,123
invoke stack_rax_byte_callee,1,2,3,4,5,6,rax,v
ret
stack_rax_byte_run_tests endp

option redzone:no
.code
stack_rax_dword_callee proc SYSTEMV g0:qword,g1:qword,g2:qword,g3:qword,g4:qword,g5:qword,keep:qword,last:dword
mov rax,keep
sub rax,123
ret
stack_rax_dword_callee endp
stack_rax_dword_run_tests proc SYSTEMV
local v:dword
mov v,0
mov eax,123
invoke stack_rax_dword_callee,1,2,3,4,5,6,rax,v
ret
stack_rax_dword_run_tests endp

option redzone:no
.code
stack_rax_qword_callee proc SYSTEMV g0:qword,g1:qword,g2:qword,g3:qword,g4:qword,g5:qword,keep:qword,last:qword
mov rax,keep
sub rax,123
ret
stack_rax_qword_callee endp
stack_rax_qword_run_tests proc SYSTEMV
local v:qword
mov v,0
mov eax,123
invoke stack_rax_qword_callee,1,2,3,4,5,6,rax,v
ret
stack_rax_qword_run_tests endp

option redzone:no
.code
stack_rax_real4_callee proc SYSTEMV g0:qword,g1:qword,g2:qword,g3:qword,g4:qword,g5:qword,keep:qword,f0:real4,f1:real4,f2:real4,f3:real4,f4:real4,f5:real4,f6:real4,f7:real4,last:real4
mov rax,keep
sub rax,123
ret
stack_rax_real4_callee endp
stack_rax_real4_run_tests proc SYSTEMV
local v:real4
mov v,0
mov eax,123
invoke stack_rax_real4_callee,1,2,3,4,5,6,rax,xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,v
ret
stack_rax_real4_run_tests endp

option redzone:no
.code
stack_rax_real8_callee proc SYSTEMV g0:qword,g1:qword,g2:qword,g3:qword,g4:qword,g5:qword,keep:qword,f0:real8,f1:real8,f2:real8,f3:real8,f4:real8,f5:real8,f6:real8,f7:real8,last:real8
mov rax,keep
sub rax,123
ret
stack_rax_real8_callee endp
stack_rax_real8_run_tests proc SYSTEMV
local v:real8
mov v,0
mov eax,123
invoke stack_rax_real8_callee,1,2,3,4,5,6,rax,xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,v
ret
stack_rax_real8_run_tests endp

option redzone:no
.code
stack_rax_word_callee proc SYSTEMV g0:qword,g1:qword,g2:qword,g3:qword,g4:qword,g5:qword,keep:qword,last:word
mov rax,keep
sub rax,123
ret
stack_rax_word_callee endp
stack_rax_word_run_tests proc SYSTEMV
local v:word
mov v,0
mov eax,123
invoke stack_rax_word_callee,1,2,3,4,5,6,rax,v
ret
stack_rax_word_run_tests endp

option redzone:no
.code
run_tests proc SYSTEMV uses r12
xor r12d,r12d
invoke large_immediate_run_tests
or r12,rax
invoke recursive_run_tests
or r12,rax
invoke small_byte_run_tests
or r12,rax
invoke small_dword_run_tests
or r12,rax
invoke small_qword_run_tests
or r12,rax
invoke small_word_run_tests
or r12,rax
invoke stack_rax_byte_run_tests
or r12,rax
invoke stack_rax_dword_run_tests
or r12,rax
invoke stack_rax_qword_run_tests
or r12,rax
invoke stack_rax_real4_run_tests
or r12,rax
invoke stack_rax_real8_run_tests
or r12,rax
invoke stack_rax_word_run_tests
or r12,rax
mov rax,r12
ret
run_tests endp
end
