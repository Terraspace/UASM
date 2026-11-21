; System V regression: floating_args
; run_tests returns zero when its ABI assertions pass.
option casemap:none

option redzone:no
.code
float_real4_1_callee proc SYSTEMV a0:real4
xorps xmm15,xmm15
addss xmm15,a0
cvttss2si rax,xmm15
ret
float_real4_1_callee endp
float_real4_1_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke float_real4_1_callee,1.0
sub rax,1
mov rsp,r12
ret
float_real4_1_run_tests endp

option redzone:no
.code
float_real4_10_callee proc SYSTEMV a0:real4,a1:real4,a2:real4,a3:real4,a4:real4,a5:real4,a6:real4,a7:real4,a8:real4,a9:real4
xorps xmm15,xmm15
addss xmm15,a0
addss xmm15,a1
addss xmm15,a2
addss xmm15,a3
addss xmm15,a4
addss xmm15,a5
addss xmm15,a6
addss xmm15,a7
addss xmm15,a8
addss xmm15,a9
cvttss2si rax,xmm15
ret
float_real4_10_callee endp
float_real4_10_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke float_real4_10_callee,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0
sub rax,55
mov rsp,r12
ret
float_real4_10_run_tests endp

option redzone:no
.code
float_real4_8_callee proc SYSTEMV a0:real4,a1:real4,a2:real4,a3:real4,a4:real4,a5:real4,a6:real4,a7:real4
xorps xmm15,xmm15
addss xmm15,a0
addss xmm15,a1
addss xmm15,a2
addss xmm15,a3
addss xmm15,a4
addss xmm15,a5
addss xmm15,a6
addss xmm15,a7
cvttss2si rax,xmm15
ret
float_real4_8_callee endp
float_real4_8_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke float_real4_8_callee,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0
sub rax,36
mov rsp,r12
ret
float_real4_8_run_tests endp

option redzone:no
.code
float_real4_9_callee proc SYSTEMV a0:real4,a1:real4,a2:real4,a3:real4,a4:real4,a5:real4,a6:real4,a7:real4,a8:real4
xorps xmm15,xmm15
addss xmm15,a0
addss xmm15,a1
addss xmm15,a2
addss xmm15,a3
addss xmm15,a4
addss xmm15,a5
addss xmm15,a6
addss xmm15,a7
addss xmm15,a8
cvttss2si rax,xmm15
ret
float_real4_9_callee endp
float_real4_9_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke float_real4_9_callee,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0
sub rax,45
mov rsp,r12
ret
float_real4_9_run_tests endp

option redzone:no
.code
float_real8_1_callee proc SYSTEMV a0:real8
xorps xmm15,xmm15
addsd xmm15,a0
cvttsd2si rax,xmm15
ret
float_real8_1_callee endp
float_real8_1_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke float_real8_1_callee,1.0
sub rax,1
mov rsp,r12
ret
float_real8_1_run_tests endp

option redzone:no
.code
float_real8_10_callee proc SYSTEMV a0:real8,a1:real8,a2:real8,a3:real8,a4:real8,a5:real8,a6:real8,a7:real8,a8:real8,a9:real8
xorps xmm15,xmm15
addsd xmm15,a0
addsd xmm15,a1
addsd xmm15,a2
addsd xmm15,a3
addsd xmm15,a4
addsd xmm15,a5
addsd xmm15,a6
addsd xmm15,a7
addsd xmm15,a8
addsd xmm15,a9
cvttsd2si rax,xmm15
ret
float_real8_10_callee endp
float_real8_10_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke float_real8_10_callee,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0
sub rax,55
mov rsp,r12
ret
float_real8_10_run_tests endp

option redzone:no
.code
float_real8_8_callee proc SYSTEMV a0:real8,a1:real8,a2:real8,a3:real8,a4:real8,a5:real8,a6:real8,a7:real8
xorps xmm15,xmm15
addsd xmm15,a0
addsd xmm15,a1
addsd xmm15,a2
addsd xmm15,a3
addsd xmm15,a4
addsd xmm15,a5
addsd xmm15,a6
addsd xmm15,a7
cvttsd2si rax,xmm15
ret
float_real8_8_callee endp
float_real8_8_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke float_real8_8_callee,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0
sub rax,36
mov rsp,r12
ret
float_real8_8_run_tests endp

option redzone:no
.code
float_real8_9_callee proc SYSTEMV a0:real8,a1:real8,a2:real8,a3:real8,a4:real8,a5:real8,a6:real8,a7:real8,a8:real8
xorps xmm15,xmm15
addsd xmm15,a0
addsd xmm15,a1
addsd xmm15,a2
addsd xmm15,a3
addsd xmm15,a4
addsd xmm15,a5
addsd xmm15,a6
addsd xmm15,a7
addsd xmm15,a8
cvttsd2si rax,xmm15
ret
float_real8_9_callee endp
float_real8_9_run_tests proc SYSTEMV uses r12
mov r12,rsp
invoke float_real8_9_callee,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0
sub rax,45
mov rsp,r12
ret
float_real8_9_run_tests endp

option redzone:no
.code
run_tests proc SYSTEMV uses r12
xor r12d,r12d
invoke float_real4_1_run_tests
or r12,rax
invoke float_real4_10_run_tests
or r12,rax
invoke float_real4_8_run_tests
or r12,rax
invoke float_real4_9_run_tests
or r12,rax
invoke float_real8_1_run_tests
or r12,rax
invoke float_real8_10_run_tests
or r12,rax
invoke float_real8_8_run_tests
or r12,rax
invoke float_real8_9_run_tests
or r12,rax
mov rax,r12
ret
run_tests endp
end
