; System V regression: variadic_args
; run_tests returns zero when its ABI assertions pass.
option casemap:none

option redzone:no
.code
vararg_count_callee proc SYSTEMV fixed:real8,args:vararg
movzx eax,al
sub eax,2
movq r10,xmm1
mov r11,4004000000000000h
sub r10,r11
or rax,r10
ret
vararg_count_callee endp
vararg_count_run_tests proc SYSTEMV
invoke vararg_count_callee,1.0,2.5
ret
vararg_count_run_tests endp

option redzone:no
.code
vararg_mem_real4_callee proc SYSTEMV fixed:qword,args:vararg
movq rax,xmm0
mov r10,4004000000000000h
sub rax,r10
ret
vararg_mem_real4_callee endp
vararg_mem_real4_run_tests proc SYSTEMV
local v:real4
mov v,2.5
invoke vararg_mem_real4_callee,0,v
ret
vararg_mem_real4_run_tests endp

option redzone:no
.code
vararg_mem_real8_callee proc SYSTEMV fixed:qword,args:vararg
movq rax,xmm0
mov r10,4004000000000000h
sub rax,r10
ret
vararg_mem_real8_callee endp
vararg_mem_real8_run_tests proc SYSTEMV
local v:real8
mov rax,4004000000000000h
mov v,rax
invoke vararg_mem_real8_callee,0,v
ret
vararg_mem_real8_run_tests endp

option redzone:no
.code
vararg_memspill_real4_callee proc SYSTEMV tag:qword,args:vararg
mov rax,[rbp+16]
mov r10,4004000000000000h
sub rax,r10
ret
vararg_memspill_real4_callee endp
vararg_memspill_real4_run_tests proc SYSTEMV
local v:real4
mov v,2.5
invoke vararg_memspill_real4_callee,0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,v
ret
vararg_memspill_real4_run_tests endp

option redzone:no
.code
vararg_memspill_real8_callee proc SYSTEMV tag:qword,args:vararg
mov rax,[rbp+16]
mov r10,4004000000000000h
sub rax,r10
ret
vararg_memspill_real8_callee endp
vararg_memspill_real8_run_tests proc SYSTEMV
local v:real8
mov rax,4004000000000000h
mov v,rax
invoke vararg_memspill_real8_callee,0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,v
ret
vararg_memspill_real8_run_tests endp

option redzone:no
.code
vararg_small_byte_callee proc SYSTEMV tag:qword,args:vararg
mov eax,esi
sub eax,255
ret
vararg_small_byte_callee endp
vararg_small_byte_run_tests proc SYSTEMV
mov r10,-1
invoke vararg_small_byte_callee,0,byte ptr r10b
ret
vararg_small_byte_run_tests endp

option redzone:no
.code
vararg_small_sbyte_callee proc SYSTEMV tag:qword,args:vararg
mov eax,esi
sub eax,-1
ret
vararg_small_sbyte_callee endp
vararg_small_sbyte_run_tests proc SYSTEMV
mov r10,-1
invoke vararg_small_sbyte_callee,0,sbyte ptr r10b
ret
vararg_small_sbyte_run_tests endp

option redzone:no
.code
vararg_small_sword_callee proc SYSTEMV tag:qword,args:vararg
mov eax,esi
sub eax,-1
ret
vararg_small_sword_callee endp
vararg_small_sword_run_tests proc SYSTEMV
mov r10,-1
invoke vararg_small_sword_callee,0,sword ptr r10w
ret
vararg_small_sword_run_tests endp

option redzone:no
.code
vararg_small_word_callee proc SYSTEMV tag:qword,args:vararg
mov eax,esi
sub eax,65535
ret
vararg_small_word_callee endp
vararg_small_word_run_tests proc SYSTEMV
mov r10,-1
invoke vararg_small_word_callee,0,word ptr r10w
ret
vararg_small_word_run_tests endp

option redzone:no
.code
vararg_spill_callee proc SYSTEMV tag:qword,args:vararg
movzx eax,al
sub eax,8
mov r10,[rbp+16]
mov r11,4022000000000000h
sub r10,r11
or rax,r10
ret
vararg_spill_callee endp
vararg_spill_run_tests proc SYSTEMV
invoke vararg_spill_callee,0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0
ret
vararg_spill_run_tests endp

option redzone:no
.code
vararg_wide32_callee proc SYSTEMV tag:qword,args:vararg
movzx eax,al
mov r10,[rbp+16]
sub r10,42
or rax,r10
lea r10,[rbp+16]
and r10,31
or rax,r10
ret
vararg_wide32_callee endp
vararg_wide32_run_tests proc SYSTEMV
local v:__m256
mov qword ptr v,42
invoke vararg_wide32_callee,0,v
ret
vararg_wide32_run_tests endp

option redzone:no
.code
vararg_wide64_callee proc SYSTEMV tag:qword,args:vararg
movzx eax,al
mov r10,[rbp+16]
sub r10,42
or rax,r10
lea r10,[rbp+16]
and r10,63
or rax,r10
ret
vararg_wide64_callee endp
vararg_wide64_run_tests proc SYSTEMV
local v:__m512
mov qword ptr v,42
invoke vararg_wide64_callee,0,v
ret
vararg_wide64_run_tests endp

option redzone:no
.code
run_tests proc SYSTEMV uses r12
xor r12d,r12d
invoke vararg_count_run_tests
or r12,rax
invoke vararg_mem_real4_run_tests
or r12,rax
invoke vararg_mem_real8_run_tests
or r12,rax
invoke vararg_memspill_real4_run_tests
or r12,rax
invoke vararg_memspill_real8_run_tests
or r12,rax
invoke vararg_small_byte_run_tests
or r12,rax
invoke vararg_small_sbyte_run_tests
or r12,rax
invoke vararg_small_sword_run_tests
or r12,rax
invoke vararg_small_word_run_tests
or r12,rax
invoke vararg_spill_run_tests
or r12,rax
invoke vararg_wide32_run_tests
or r12,rax
invoke vararg_wide64_run_tests
or r12,rax
mov rax,r12
ret
run_tests endp
end
