; System V regression: vector_args
; run_tests returns zero when its ABI assertions pass.
option casemap:none

option redzone:no
.code
mixed16_callee proc SYSTEMV g0:qword,g1:qword,g2:qword,g3:qword,g4:qword,g5:qword,g6:qword,v0:xmmword,v1:xmmword,v2:xmmword,v3:xmmword,v4:xmmword,v5:xmmword,v6:xmmword,v7:xmmword,v8:xmmword,last:qword
mov rax,g6
sub rax,7
mov r10,qword ptr v8
sub r10,42
or rax,r10
mov r10,last
sub r10,19
or rax,r10
lea r10,v8
and r10,15
or rax,r10
ret
mixed16_callee endp
mixed16_run_tests proc SYSTEMV
local buf:xmmword
mov qword ptr buf,42
invoke mixed16_callee,1,2,3,4,5,6,7,xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,buf,19
ret
mixed16_run_tests endp

option redzone:no
.code
mixed32_callee proc SYSTEMV g0:qword,g1:qword,g2:qword,g3:qword,g4:qword,g5:qword,g6:qword,v0:ymmword,v1:ymmword,v2:ymmword,v3:ymmword,v4:ymmword,v5:ymmword,v6:ymmword,v7:ymmword,v8:ymmword,last:qword
mov rax,g6
sub rax,7
mov r10,qword ptr v8
sub r10,42
or rax,r10
mov r10,last
sub r10,19
or rax,r10
lea r10,v8
and r10,31
or rax,r10
ret
mixed32_callee endp
mixed32_run_tests proc SYSTEMV
local buf:ymmword
mov qword ptr buf,42
invoke mixed32_callee,1,2,3,4,5,6,7,ymm0,ymm1,ymm2,ymm3,ymm4,ymm5,ymm6,ymm7,buf,19
ret
mixed32_run_tests endp

option redzone:no
.code
mixed64_callee proc SYSTEMV g0:qword,g1:qword,g2:qword,g3:qword,g4:qword,g5:qword,g6:qword,v0:zmmword,v1:zmmword,v2:zmmword,v3:zmmword,v4:zmmword,v5:zmmword,v6:zmmword,v7:zmmword,v8:zmmword,last:qword
mov rax,g6
sub rax,7
mov r10,qword ptr v8
sub r10,42
or rax,r10
mov r10,last
sub r10,19
or rax,r10
lea r10,v8
and r10,63
or rax,r10
ret
mixed64_callee endp
mixed64_run_tests proc SYSTEMV
local buf:zmmword
mov qword ptr buf,42
invoke mixed64_callee,1,2,3,4,5,6,7,zmm0,zmm1,zmm2,zmm3,zmm4,zmm5,zmm6,zmm7,buf,19
ret
mixed64_run_tests endp

option redzone:no
.code
preserve_xmm0_callee proc SYSTEMV uses xmm8
local v:qword
mov v,42
pxor xmm8,xmm8
ret
preserve_xmm0_callee endp
preserve_xmm0_run_tests proc SYSTEMV
mov eax,42
movq xmm8,rax
invoke preserve_xmm0_callee
movq rax,xmm8
sub rax,42
ret
preserve_xmm0_run_tests endp

option redzone:no
.code
preserve_xmm1_callee proc SYSTEMV uses rbx xmm8
local v:qword
mov v,42
pxor xmm8,xmm8
ret
preserve_xmm1_callee endp
preserve_xmm1_run_tests proc SYSTEMV
mov eax,42
movq xmm8,rax
invoke preserve_xmm1_callee
movq rax,xmm8
sub rax,42
ret
preserve_xmm1_run_tests endp

option redzone:no
.code
preserve_xmm2_callee proc SYSTEMV uses rbx r12 xmm8
local v:qword
mov v,42
pxor xmm8,xmm8
ret
preserve_xmm2_callee endp
preserve_xmm2_run_tests proc SYSTEMV
mov eax,42
movq xmm8,rax
invoke preserve_xmm2_callee
movq rax,xmm8
sub rax,42
ret
preserve_xmm2_run_tests endp

option redzone:no
.code
preserve_xmm3_callee proc SYSTEMV uses rbx r12 r13 xmm8
local v:qword
mov v,42
pxor xmm8,xmm8
ret
preserve_xmm3_callee endp
preserve_xmm3_run_tests proc SYSTEMV
mov eax,42
movq xmm8,rax
invoke preserve_xmm3_callee
movq rax,xmm8
sub rax,42
ret
preserve_xmm3_run_tests endp

option redzone:no
.code
preserve_ymm_callee proc SYSTEMV uses rbx ymm8
local v:qword
vpxor ymm8,ymm8,ymm8
ret
preserve_ymm_callee endp
preserve_ymm_run_tests proc SYSTEMV
vpcmpeqd ymm8,ymm8,ymm8
invoke preserve_ymm_callee
vpmovmskb eax,ymm8
inc eax
ret
preserve_ymm_run_tests endp

option redzone:no
.code
save_ymm8_run_tests proc SYSTEMV uses rbx ymm8
local v:qword
mov v,42
mov rax,v
sub rax,42
ret
save_ymm8_run_tests endp

option redzone:no
.code
vector16_0_callee proc SYSTEMV a0:xmmword,a1:xmmword,a2:xmmword,a3:xmmword,a4:xmmword,a5:xmmword,a6:xmmword,a7:xmmword,a8:xmmword
mov rax,qword ptr a8
sub rax,42
lea r10,a8
and r10,15
or rax,r10
ret
vector16_0_callee endp
vector16_0_run_tests proc SYSTEMV
mov eax,42
movq xmm8,rax
invoke vector16_0_callee,xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,xmm8
ret
vector16_0_run_tests endp

option redzone:no
.code
vector16_1_callee proc SYSTEMV a0:xmmword,a1:xmmword,a2:xmmword,a3:xmmword,a4:xmmword,a5:xmmword,a6:xmmword,a7:xmmword,a8:xmmword
mov rax,qword ptr a8
sub rax,42
lea r10,a8
and r10,15
or rax,r10
ret
vector16_1_callee endp
vector16_1_run_tests proc SYSTEMV
local buf:xmmword
mov qword ptr buf,42
invoke vector16_1_callee,xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,buf
ret
vector16_1_run_tests endp

option redzone:no
.code
vector32_0_callee proc SYSTEMV a0:ymmword,a1:ymmword,a2:ymmword,a3:ymmword,a4:ymmword,a5:ymmword,a6:ymmword,a7:ymmword,a8:ymmword
mov rax,qword ptr a8
sub rax,42
lea r10,a8
and r10,31
or rax,r10
ret
vector32_0_callee endp
vector32_0_run_tests proc SYSTEMV
mov eax,42
movq xmm8,rax
invoke vector32_0_callee,ymm0,ymm1,ymm2,ymm3,ymm4,ymm5,ymm6,ymm7,ymm8
ret
vector32_0_run_tests endp

option redzone:no
.code
vector32_1_callee proc SYSTEMV a0:ymmword,a1:ymmword,a2:ymmword,a3:ymmword,a4:ymmword,a5:ymmword,a6:ymmword,a7:ymmword,a8:ymmword
mov rax,qword ptr a8
sub rax,42
lea r10,a8
and r10,31
or rax,r10
ret
vector32_1_callee endp
vector32_1_run_tests proc SYSTEMV
local buf:ymmword
mov qword ptr buf,42
invoke vector32_1_callee,ymm0,ymm1,ymm2,ymm3,ymm4,ymm5,ymm6,ymm7,buf
ret
vector32_1_run_tests endp

option redzone:no
.code
vector64_1_callee proc SYSTEMV a0:zmmword,a1:zmmword,a2:zmmword,a3:zmmword,a4:zmmword,a5:zmmword,a6:zmmword,a7:zmmword,a8:zmmword
mov rax,qword ptr a8
sub rax,42
lea r10,a8
and r10,63
or rax,r10
ret
vector64_1_callee endp
vector64_1_run_tests proc SYSTEMV
local buf:zmmword
mov qword ptr buf,42
invoke vector64_1_callee,zmm0,zmm1,zmm2,zmm3,zmm4,zmm5,zmm6,zmm7,buf
ret
vector64_1_run_tests endp

option redzone:no
.code
vector_indirect16_callee proc SYSTEMV a0:xmmword,a1:xmmword,a2:xmmword,a3:xmmword,a4:xmmword,a5:xmmword,a6:xmmword,a7:xmmword,a8:xmmword
mov rax,qword ptr a8
sub rax,42
mov r10,qword ptr a8[8]
sub r10,43
or rax,r10
ret
vector_indirect16_callee endp
vector_indirect16_run_tests proc SYSTEMV
local buf:xmmword
mov qword ptr buf,42
mov qword ptr buf[8],43
lea rax,buf
invoke vector_indirect16_callee,xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,xmmword ptr [rax]
ret
vector_indirect16_run_tests endp

option redzone:no
.code
vector_indirect32_callee proc SYSTEMV a0:ymmword,a1:ymmword,a2:ymmword,a3:ymmword,a4:ymmword,a5:ymmword,a6:ymmword,a7:ymmword,a8:ymmword
mov rax,qword ptr a8
sub rax,42
mov r10,qword ptr a8[8]
sub r10,43
or rax,r10
ret
vector_indirect32_callee endp
vector_indirect32_run_tests proc SYSTEMV
local buf:ymmword
mov qword ptr buf,42
mov qword ptr buf[8],43
lea rax,buf
invoke vector_indirect32_callee,ymm0,ymm1,ymm2,ymm3,ymm4,ymm5,ymm6,ymm7,ymmword ptr [rax]
ret
vector_indirect32_run_tests endp

option redzone:no
.code
vector_save0_run_tests proc SYSTEMV uses xmm8
local v:qword
mov v,42
mov rax,v
sub rax,42
ret
vector_save0_run_tests endp

option redzone:no
.code
vector_save1_run_tests proc SYSTEMV uses rbx xmm8
local v:qword
mov v,42
mov rax,v
sub rax,42
ret
vector_save1_run_tests endp

option redzone:no
.code
vector_save2_run_tests proc SYSTEMV uses rbx r12 xmm8
local v:qword
mov v,42
mov rax,v
sub rax,42
ret
vector_save2_run_tests endp

option redzone:no
.code
run_tests proc SYSTEMV uses r12
xor r12d,r12d
invoke mixed16_run_tests
or r12,rax
invoke mixed32_run_tests
or r12,rax
invoke mixed64_run_tests
or r12,rax
invoke preserve_xmm0_run_tests
or r12,rax
invoke preserve_xmm1_run_tests
or r12,rax
invoke preserve_xmm2_run_tests
or r12,rax
invoke preserve_xmm3_run_tests
or r12,rax
invoke preserve_ymm_run_tests
or r12,rax
invoke save_ymm8_run_tests
or r12,rax
invoke vector16_0_run_tests
or r12,rax
invoke vector16_1_run_tests
or r12,rax
invoke vector32_0_run_tests
or r12,rax
invoke vector32_1_run_tests
or r12,rax
invoke vector64_1_run_tests
or r12,rax
invoke vector_indirect16_run_tests
or r12,rax
invoke vector_indirect32_run_tests
or r12,rax
invoke vector_save0_run_tests
or r12,rax
invoke vector_save1_run_tests
or r12,rax
invoke vector_save2_run_tests
or r12,rax
mov rax,r12
ret
run_tests endp
end
