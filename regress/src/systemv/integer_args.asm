; System V regression: integer_args
; run_tests returns zero when its ABI assertions pass.
option casemap:none

option redzone:no
.code
int0_callee proc SYSTEMV 
xor eax,eax
ret
int0_callee endp
int0_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke int0_callee
cmp rax,0
jne int0_bad
cmp rsp,r12
jne int0_bad
xor eax,eax
ret
int0_bad:
mov rsp,r12
mov eax,1
ret
int0_run_tests endp

option redzone:no
.code
int1_callee proc SYSTEMV a0:qword
xor eax,eax
add rax,a0
ret
int1_callee endp
int1_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke int1_callee,1
cmp rax,1
jne int1_bad
cmp rsp,r12
jne int1_bad
xor eax,eax
ret
int1_bad:
mov rsp,r12
mov eax,1
ret
int1_run_tests endp

option redzone:no
.code
int10_callee proc SYSTEMV a0:qword,a1:qword,a2:qword,a3:qword,a4:qword,a5:qword,a6:qword,a7:qword,a8:qword,a9:qword
xor eax,eax
add rax,a0
add rax,a1
add rax,a2
add rax,a3
add rax,a4
add rax,a5
add rax,a6
add rax,a7
add rax,a8
add rax,a9
ret
int10_callee endp
int10_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke int10_callee,1,2,3,4,5,6,7,8,9,10
cmp rax,55
jne int10_bad
cmp rsp,r12
jne int10_bad
xor eax,eax
ret
int10_bad:
mov rsp,r12
mov eax,1
ret
int10_run_tests endp

option redzone:no
.code
int11_callee proc SYSTEMV a0:qword,a1:qword,a2:qword,a3:qword,a4:qword,a5:qword,a6:qword,a7:qword,a8:qword,a9:qword,a10:qword
xor eax,eax
add rax,a0
add rax,a1
add rax,a2
add rax,a3
add rax,a4
add rax,a5
add rax,a6
add rax,a7
add rax,a8
add rax,a9
add rax,a10
ret
int11_callee endp
int11_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke int11_callee,1,2,3,4,5,6,7,8,9,10,11
cmp rax,66
jne int11_bad
cmp rsp,r12
jne int11_bad
xor eax,eax
ret
int11_bad:
mov rsp,r12
mov eax,1
ret
int11_run_tests endp

option redzone:no
.code
int12_callee proc SYSTEMV a0:qword,a1:qword,a2:qword,a3:qword,a4:qword,a5:qword,a6:qword,a7:qword,a8:qword,a9:qword,a10:qword,a11:qword
xor eax,eax
add rax,a0
add rax,a1
add rax,a2
add rax,a3
add rax,a4
add rax,a5
add rax,a6
add rax,a7
add rax,a8
add rax,a9
add rax,a10
add rax,a11
ret
int12_callee endp
int12_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke int12_callee,1,2,3,4,5,6,7,8,9,10,11,12
cmp rax,78
jne int12_bad
cmp rsp,r12
jne int12_bad
xor eax,eax
ret
int12_bad:
mov rsp,r12
mov eax,1
ret
int12_run_tests endp

option redzone:no
.code
int2_callee proc SYSTEMV a0:qword,a1:qword
xor eax,eax
add rax,a0
add rax,a1
ret
int2_callee endp
int2_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke int2_callee,1,2
cmp rax,3
jne int2_bad
cmp rsp,r12
jne int2_bad
xor eax,eax
ret
int2_bad:
mov rsp,r12
mov eax,1
ret
int2_run_tests endp

option redzone:no
.code
int3_callee proc SYSTEMV a0:qword,a1:qword,a2:qword
xor eax,eax
add rax,a0
add rax,a1
add rax,a2
ret
int3_callee endp
int3_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke int3_callee,1,2,3
cmp rax,6
jne int3_bad
cmp rsp,r12
jne int3_bad
xor eax,eax
ret
int3_bad:
mov rsp,r12
mov eax,1
ret
int3_run_tests endp

option redzone:no
.code
int4_callee proc SYSTEMV a0:qword,a1:qword,a2:qword,a3:qword
xor eax,eax
add rax,a0
add rax,a1
add rax,a2
add rax,a3
ret
int4_callee endp
int4_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke int4_callee,1,2,3,4
cmp rax,10
jne int4_bad
cmp rsp,r12
jne int4_bad
xor eax,eax
ret
int4_bad:
mov rsp,r12
mov eax,1
ret
int4_run_tests endp

option redzone:no
.code
int5_callee proc SYSTEMV a0:qword,a1:qword,a2:qword,a3:qword,a4:qword
xor eax,eax
add rax,a0
add rax,a1
add rax,a2
add rax,a3
add rax,a4
ret
int5_callee endp
int5_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke int5_callee,1,2,3,4,5
cmp rax,15
jne int5_bad
cmp rsp,r12
jne int5_bad
xor eax,eax
ret
int5_bad:
mov rsp,r12
mov eax,1
ret
int5_run_tests endp

option redzone:no
.code
int6_callee proc SYSTEMV a0:qword,a1:qword,a2:qword,a3:qword,a4:qword,a5:qword
xor eax,eax
add rax,a0
add rax,a1
add rax,a2
add rax,a3
add rax,a4
add rax,a5
ret
int6_callee endp
int6_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke int6_callee,1,2,3,4,5,6
cmp rax,21
jne int6_bad
cmp rsp,r12
jne int6_bad
xor eax,eax
ret
int6_bad:
mov rsp,r12
mov eax,1
ret
int6_run_tests endp

option redzone:no
.code
int7_callee proc SYSTEMV a0:qword,a1:qword,a2:qword,a3:qword,a4:qword,a5:qword,a6:qword
xor eax,eax
add rax,a0
add rax,a1
add rax,a2
add rax,a3
add rax,a4
add rax,a5
add rax,a6
ret
int7_callee endp
int7_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke int7_callee,1,2,3,4,5,6,7
cmp rax,28
jne int7_bad
cmp rsp,r12
jne int7_bad
xor eax,eax
ret
int7_bad:
mov rsp,r12
mov eax,1
ret
int7_run_tests endp

option redzone:no
.code
int8_callee proc SYSTEMV a0:qword,a1:qword,a2:qword,a3:qword,a4:qword,a5:qword,a6:qword,a7:qword
xor eax,eax
add rax,a0
add rax,a1
add rax,a2
add rax,a3
add rax,a4
add rax,a5
add rax,a6
add rax,a7
ret
int8_callee endp
int8_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke int8_callee,1,2,3,4,5,6,7,8
cmp rax,36
jne int8_bad
cmp rsp,r12
jne int8_bad
xor eax,eax
ret
int8_bad:
mov rsp,r12
mov eax,1
ret
int8_run_tests endp

option redzone:no
.code
int9_callee proc SYSTEMV a0:qword,a1:qword,a2:qword,a3:qword,a4:qword,a5:qword,a6:qword,a7:qword,a8:qword
xor eax,eax
add rax,a0
add rax,a1
add rax,a2
add rax,a3
add rax,a4
add rax,a5
add rax,a6
add rax,a7
add rax,a8
ret
int9_callee endp
int9_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke int9_callee,1,2,3,4,5,6,7,8,9
cmp rax,45
jne int9_bad
cmp rsp,r12
jne int9_bad
xor eax,eax
ret
int9_bad:
mov rsp,r12
mov eax,1
ret
int9_run_tests endp

option redzone:no
.code
run_tests proc SYSTEMV uses r12
xor r12d,r12d
invoke int0_run_tests
or r12,rax
invoke int1_run_tests
or r12,rax
invoke int10_run_tests
or r12,rax
invoke int11_run_tests
or r12,rax
invoke int12_run_tests
or r12,rax
invoke int2_run_tests
or r12,rax
invoke int3_run_tests
or r12,rax
invoke int4_run_tests
or r12,rax
invoke int5_run_tests
or r12,rax
invoke int6_run_tests
or r12,rax
invoke int7_run_tests
or r12,rax
invoke int8_run_tests
or r12,rax
invoke int9_run_tests
or r12,rax
mov rax,r12
ret
run_tests endp
end
