; Smart Win64 homing/unwind matrix. Runtime companion: validation/win64_unwind_driver.c
; Modes 11/15, flags on/off, 0-8 GPR saves, sparse/full named parameter use,
; mixed XMM saves, outgoing calls, small/inline-probed/helper-probed frames.
option casemap:none
option prologue:none
option epilogue:none
.code
RunUnwind proc frame
 sub rsp,56
 .allocstack 56
 .endprolog
 mov [rsp+32],rcx
 mov ecx,1
 mov edx,2
 mov r8d,3
 mov r9d,4
 pushfq
 or qword ptr [rsp],100h
 popfq
 call qword ptr [rsp+32]
 add rsp,56
 ret
RunUnwind endp
UnwindCallee proc p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,p6:qword
 mov rax,rsp
 and eax,15
 cmp eax,8
 je @F
 inc UnwindFailures
@@:
 ret
UnwindCallee endp
option prologue:prologuedef
option epilogue:epiloguedef
; The parameters independently vary frame size, named-parameter use and saves.
unwind_case macro pname:req, n:req, mask:req, bytes:req, outgoing:req, rlist:vararg
 ifb <rlist>
  pname proc frame, p1:qword,p2:qword,p3:qword,p4:qword
 else
  pname proc frame uses rlist, p1:qword,p2:qword,p3:qword,p4:qword
 endif
 if bytes
  local storage[bytes]:byte
 endif
 if mask and 1
  mov rax,p1
  cmp rax,1
  je @F
  inc UnwindFailures
@@:
 endif
 if mask and 2
  mov rax,p2
  cmp rax,2
  je @F
  inc UnwindFailures
@@:
 endif
 if mask and 4
  mov rax,p3
  cmp rax,3
  je @F
  inc UnwindFailures
@@:
 endif
 if mask and 8
  mov rax,p4
  cmp rax,4
  je @F
  inc UnwindFailures
@@:
 endif
 if n ge 1
  mov rbx,12345678h
 endif
 if n ge 2
  mov r12,12345678h
 endif
 if n ge 3
  mov r13,12345678h
 endif
 if n ge 4
  mov r14,12345678h
 endif
 if n ge 5
  mov r15,12345678h
 endif
 if n ge 6
  mov rsi,12345678h
 endif
 if n ge 7
  mov rdi,12345678h
 endif
 if n ge 8
  mov rbp,12345678h
 endif
 pxor xmm6,xmm6
 if bytes
  mov storage[0],1
  mov storage[bytes-1],2
  cmp storage[0],1
  je @F
  inc UnwindFailures
@@:
  cmp storage[bytes-1],2
  je @F
  inc UnwindFailures
@@:
 endif
 if outgoing
  invoke UnwindCallee,1,2,3,4,5,6
 endif
 ret
 pname endp
endm

option stackbase:rsp
option win64:11
option framepreserveflags:off
unwind_case uw_11_off_0_0, 0, 0, 0, 1, xmm6
unwind_case uw_11_off_0_1, 0, 1, 32, 0, xmm6
unwind_case uw_11_off_0_5, 0, 5, 32, 0, xmm6
unwind_case uw_11_off_0_15, 0, 15, 65536, 1, xmm6
unwind_case uw_11_off_1_0, 1, 0, 32, 0, rbx xmm6
unwind_case uw_11_off_1_1, 1, 1, 4096, 0, rbx xmm6
unwind_case uw_11_off_1_5, 1, 5, 4096, 1, rbx xmm6
unwind_case uw_11_off_1_15, 1, 15, 0, 0, rbx xmm6
unwind_case uw_11_off_2_0, 2, 0, 4096, 0, rbx r12 xmm6
unwind_case uw_11_off_2_1, 2, 1, 65536, 1, rbx r12 xmm6
unwind_case uw_11_off_2_5, 2, 5, 65536, 0, rbx r12 xmm6
unwind_case uw_11_off_2_15, 2, 15, 32, 0, rbx r12 xmm6
unwind_case uw_11_off_3_0, 3, 0, 65536, 1, rbx r12 r13 xmm6
unwind_case uw_11_off_3_1, 3, 1, 0, 0, rbx r12 r13 xmm6
unwind_case uw_11_off_3_5, 3, 5, 0, 0, rbx r12 r13 xmm6
unwind_case uw_11_off_3_15, 3, 15, 4096, 1, rbx r12 r13 xmm6
unwind_case uw_11_off_4_0, 4, 0, 0, 0, rbx r12 r13 r14 xmm6
unwind_case uw_11_off_4_1, 4, 1, 32, 0, rbx r12 r13 r14 xmm6
unwind_case uw_11_off_4_5, 4, 5, 32, 1, rbx r12 r13 r14 xmm6
unwind_case uw_11_off_4_15, 4, 15, 65536, 0, rbx r12 r13 r14 xmm6
unwind_case uw_11_off_5_0, 5, 0, 32, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_11_off_5_1, 5, 1, 4096, 1, rbx r12 r13 r14 r15 xmm6
unwind_case uw_11_off_5_5, 5, 5, 4096, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_11_off_5_15, 5, 15, 0, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_11_off_6_0, 6, 0, 4096, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_11_off_6_1, 6, 1, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_11_off_6_5, 6, 5, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_11_off_6_15, 6, 15, 32, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_11_off_7_0, 7, 0, 65536, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_11_off_7_1, 7, 1, 0, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_11_off_7_5, 7, 5, 0, 1, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_11_off_7_15, 7, 15, 4096, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_11_off_8_0, 8, 0, 0, 0, rbx r12 r13 r14 r15 rsi rdi rbp xmm6
unwind_case uw_11_off_8_1, 8, 1, 32, 1, rbx r12 r13 r14 r15 rsi rdi rbp xmm6
unwind_case uw_11_off_8_5, 8, 5, 32, 0, rbx r12 r13 r14 r15 rsi rdi rbp xmm6
unwind_case uw_11_off_8_15, 8, 15, 65536, 0, rbx r12 r13 r14 r15 rsi rdi rbp xmm6
option framepreserveflags:on
unwind_case uw_11_on_0_0, 0, 0, 0, 1, xmm6
unwind_case uw_11_on_0_1, 0, 1, 32, 0, xmm6
unwind_case uw_11_on_0_5, 0, 5, 32, 0, xmm6
unwind_case uw_11_on_0_15, 0, 15, 65536, 1, xmm6
unwind_case uw_11_on_1_0, 1, 0, 32, 0, rbx xmm6
unwind_case uw_11_on_1_1, 1, 1, 4096, 0, rbx xmm6
unwind_case uw_11_on_1_5, 1, 5, 4096, 1, rbx xmm6
unwind_case uw_11_on_1_15, 1, 15, 0, 0, rbx xmm6
unwind_case uw_11_on_2_0, 2, 0, 4096, 0, rbx r12 xmm6
unwind_case uw_11_on_2_1, 2, 1, 65536, 1, rbx r12 xmm6
unwind_case uw_11_on_2_5, 2, 5, 65536, 0, rbx r12 xmm6
unwind_case uw_11_on_2_15, 2, 15, 32, 0, rbx r12 xmm6
unwind_case uw_11_on_3_0, 3, 0, 65536, 1, rbx r12 r13 xmm6
unwind_case uw_11_on_3_1, 3, 1, 0, 0, rbx r12 r13 xmm6
unwind_case uw_11_on_3_5, 3, 5, 0, 0, rbx r12 r13 xmm6
unwind_case uw_11_on_3_15, 3, 15, 4096, 1, rbx r12 r13 xmm6
unwind_case uw_11_on_4_0, 4, 0, 0, 0, rbx r12 r13 r14 xmm6
unwind_case uw_11_on_4_1, 4, 1, 32, 0, rbx r12 r13 r14 xmm6
unwind_case uw_11_on_4_5, 4, 5, 32, 1, rbx r12 r13 r14 xmm6
unwind_case uw_11_on_4_15, 4, 15, 65536, 0, rbx r12 r13 r14 xmm6
unwind_case uw_11_on_5_0, 5, 0, 32, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_11_on_5_1, 5, 1, 4096, 1, rbx r12 r13 r14 r15 xmm6
unwind_case uw_11_on_5_5, 5, 5, 4096, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_11_on_5_15, 5, 15, 0, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_11_on_6_0, 6, 0, 4096, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_11_on_6_1, 6, 1, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_11_on_6_5, 6, 5, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_11_on_6_15, 6, 15, 32, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_11_on_7_0, 7, 0, 65536, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_11_on_7_1, 7, 1, 0, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_11_on_7_5, 7, 5, 0, 1, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_11_on_7_15, 7, 15, 4096, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_11_on_8_0, 8, 0, 0, 0, rbx r12 r13 r14 r15 rsi rdi rbp xmm6
unwind_case uw_11_on_8_1, 8, 1, 32, 1, rbx r12 r13 r14 r15 rsi rdi rbp xmm6
unwind_case uw_11_on_8_5, 8, 5, 32, 0, rbx r12 r13 r14 r15 rsi rdi rbp xmm6
unwind_case uw_11_on_8_15, 8, 15, 65536, 0, rbx r12 r13 r14 r15 rsi rdi rbp xmm6
option win64:15
option framepreserveflags:off
unwind_case uw_15_off_0_0, 0, 0, 0, 1, xmm6
unwind_case uw_15_off_0_1, 0, 1, 32, 0, xmm6
unwind_case uw_15_off_0_5, 0, 5, 32, 0, xmm6
unwind_case uw_15_off_0_15, 0, 15, 65536, 1, xmm6
unwind_case uw_15_off_1_0, 1, 0, 32, 0, rbx xmm6
unwind_case uw_15_off_1_1, 1, 1, 4096, 0, rbx xmm6
unwind_case uw_15_off_1_5, 1, 5, 4096, 1, rbx xmm6
unwind_case uw_15_off_1_15, 1, 15, 0, 0, rbx xmm6
unwind_case uw_15_off_2_0, 2, 0, 4096, 0, rbx r12 xmm6
unwind_case uw_15_off_2_1, 2, 1, 65536, 1, rbx r12 xmm6
unwind_case uw_15_off_2_5, 2, 5, 65536, 0, rbx r12 xmm6
unwind_case uw_15_off_2_15, 2, 15, 32, 0, rbx r12 xmm6
unwind_case uw_15_off_3_0, 3, 0, 65536, 1, rbx r12 r13 xmm6
unwind_case uw_15_off_3_1, 3, 1, 0, 0, rbx r12 r13 xmm6
unwind_case uw_15_off_3_5, 3, 5, 0, 0, rbx r12 r13 xmm6
unwind_case uw_15_off_3_15, 3, 15, 4096, 1, rbx r12 r13 xmm6
unwind_case uw_15_off_4_0, 4, 0, 0, 0, rbx r12 r13 r14 xmm6
unwind_case uw_15_off_4_1, 4, 1, 32, 0, rbx r12 r13 r14 xmm6
unwind_case uw_15_off_4_5, 4, 5, 32, 1, rbx r12 r13 r14 xmm6
unwind_case uw_15_off_4_15, 4, 15, 65536, 0, rbx r12 r13 r14 xmm6
unwind_case uw_15_off_5_0, 5, 0, 32, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_15_off_5_1, 5, 1, 4096, 1, rbx r12 r13 r14 r15 xmm6
unwind_case uw_15_off_5_5, 5, 5, 4096, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_15_off_5_15, 5, 15, 0, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_15_off_6_0, 6, 0, 4096, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_15_off_6_1, 6, 1, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_15_off_6_5, 6, 5, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_15_off_6_15, 6, 15, 32, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_15_off_7_0, 7, 0, 65536, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_15_off_7_1, 7, 1, 0, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_15_off_7_5, 7, 5, 0, 1, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_15_off_7_15, 7, 15, 4096, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_15_off_8_0, 8, 0, 0, 0, rbx r12 r13 r14 r15 rsi rdi rbp xmm6
unwind_case uw_15_off_8_1, 8, 1, 32, 1, rbx r12 r13 r14 r15 rsi rdi rbp xmm6
unwind_case uw_15_off_8_5, 8, 5, 32, 0, rbx r12 r13 r14 r15 rsi rdi rbp xmm6
unwind_case uw_15_off_8_15, 8, 15, 65536, 0, rbx r12 r13 r14 r15 rsi rdi rbp xmm6
option framepreserveflags:on
unwind_case uw_15_on_0_0, 0, 0, 0, 1, xmm6
unwind_case uw_15_on_0_1, 0, 1, 32, 0, xmm6
unwind_case uw_15_on_0_5, 0, 5, 32, 0, xmm6
unwind_case uw_15_on_0_15, 0, 15, 65536, 1, xmm6
unwind_case uw_15_on_1_0, 1, 0, 32, 0, rbx xmm6
unwind_case uw_15_on_1_1, 1, 1, 4096, 0, rbx xmm6
unwind_case uw_15_on_1_5, 1, 5, 4096, 1, rbx xmm6
unwind_case uw_15_on_1_15, 1, 15, 0, 0, rbx xmm6
unwind_case uw_15_on_2_0, 2, 0, 4096, 0, rbx r12 xmm6
unwind_case uw_15_on_2_1, 2, 1, 65536, 1, rbx r12 xmm6
unwind_case uw_15_on_2_5, 2, 5, 65536, 0, rbx r12 xmm6
unwind_case uw_15_on_2_15, 2, 15, 32, 0, rbx r12 xmm6
unwind_case uw_15_on_3_0, 3, 0, 65536, 1, rbx r12 r13 xmm6
unwind_case uw_15_on_3_1, 3, 1, 0, 0, rbx r12 r13 xmm6
unwind_case uw_15_on_3_5, 3, 5, 0, 0, rbx r12 r13 xmm6
unwind_case uw_15_on_3_15, 3, 15, 4096, 1, rbx r12 r13 xmm6
unwind_case uw_15_on_4_0, 4, 0, 0, 0, rbx r12 r13 r14 xmm6
unwind_case uw_15_on_4_1, 4, 1, 32, 0, rbx r12 r13 r14 xmm6
unwind_case uw_15_on_4_5, 4, 5, 32, 1, rbx r12 r13 r14 xmm6
unwind_case uw_15_on_4_15, 4, 15, 65536, 0, rbx r12 r13 r14 xmm6
unwind_case uw_15_on_5_0, 5, 0, 32, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_15_on_5_1, 5, 1, 4096, 1, rbx r12 r13 r14 r15 xmm6
unwind_case uw_15_on_5_5, 5, 5, 4096, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_15_on_5_15, 5, 15, 0, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_15_on_6_0, 6, 0, 4096, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_15_on_6_1, 6, 1, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_15_on_6_5, 6, 5, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_15_on_6_15, 6, 15, 32, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_15_on_7_0, 7, 0, 65536, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_15_on_7_1, 7, 1, 0, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_15_on_7_5, 7, 5, 0, 1, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_15_on_7_15, 7, 15, 4096, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_15_on_8_0, 8, 0, 0, 0, rbx r12 r13 r14 r15 rsi rdi rbp xmm6
unwind_case uw_15_on_8_1, 8, 1, 32, 1, rbx r12 r13 r14 r15 rsi rdi rbp xmm6
unwind_case uw_15_on_8_5, 8, 5, 32, 0, rbx r12 r13 r14 r15 rsi rdi rbp xmm6
unwind_case uw_15_on_8_15, 8, 15, 65536, 0, rbx r12 r13 r14 r15 rsi rdi rbp xmm6

; The same smart features with an explicit frame pointer.
option stackbase:rbp
option win64:11
option framepreserveflags:off
unwind_case uw_rbp_11_off_0_0, 0, 0, 0, 1, xmm6
unwind_case uw_rbp_11_off_0_1, 0, 1, 32, 0, xmm6
unwind_case uw_rbp_11_off_0_5, 0, 5, 32, 0, xmm6
unwind_case uw_rbp_11_off_0_15, 0, 15, 65536, 1, xmm6
unwind_case uw_rbp_11_off_1_0, 1, 0, 32, 0, rbx xmm6
unwind_case uw_rbp_11_off_1_1, 1, 1, 4096, 0, rbx xmm6
unwind_case uw_rbp_11_off_1_5, 1, 5, 4096, 1, rbx xmm6
unwind_case uw_rbp_11_off_1_15, 1, 15, 0, 0, rbx xmm6
unwind_case uw_rbp_11_off_2_0, 2, 0, 4096, 0, rbx r12 xmm6
unwind_case uw_rbp_11_off_2_1, 2, 1, 65536, 1, rbx r12 xmm6
unwind_case uw_rbp_11_off_2_5, 2, 5, 65536, 0, rbx r12 xmm6
unwind_case uw_rbp_11_off_2_15, 2, 15, 32, 0, rbx r12 xmm6
unwind_case uw_rbp_11_off_3_0, 3, 0, 65536, 1, rbx r12 r13 xmm6
unwind_case uw_rbp_11_off_3_1, 3, 1, 0, 0, rbx r12 r13 xmm6
unwind_case uw_rbp_11_off_3_5, 3, 5, 0, 0, rbx r12 r13 xmm6
unwind_case uw_rbp_11_off_3_15, 3, 15, 4096, 1, rbx r12 r13 xmm6
unwind_case uw_rbp_11_off_4_0, 4, 0, 0, 0, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_11_off_4_1, 4, 1, 32, 0, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_11_off_4_5, 4, 5, 32, 1, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_11_off_4_15, 4, 15, 65536, 0, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_11_off_5_0, 5, 0, 32, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_11_off_5_1, 5, 1, 4096, 1, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_11_off_5_5, 5, 5, 4096, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_11_off_5_15, 5, 15, 0, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_11_off_6_0, 6, 0, 4096, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_11_off_6_1, 6, 1, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_11_off_6_5, 6, 5, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_11_off_6_15, 6, 15, 32, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_11_off_7_0, 7, 0, 65536, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_rbp_11_off_7_1, 7, 1, 0, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_rbp_11_off_7_5, 7, 5, 0, 1, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_rbp_11_off_7_15, 7, 15, 4096, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
option framepreserveflags:on
unwind_case uw_rbp_11_on_0_0, 0, 0, 0, 1, xmm6
unwind_case uw_rbp_11_on_0_1, 0, 1, 32, 0, xmm6
unwind_case uw_rbp_11_on_0_5, 0, 5, 32, 0, xmm6
unwind_case uw_rbp_11_on_0_15, 0, 15, 65536, 1, xmm6
unwind_case uw_rbp_11_on_1_0, 1, 0, 32, 0, rbx xmm6
unwind_case uw_rbp_11_on_1_1, 1, 1, 4096, 0, rbx xmm6
unwind_case uw_rbp_11_on_1_5, 1, 5, 4096, 1, rbx xmm6
unwind_case uw_rbp_11_on_1_15, 1, 15, 0, 0, rbx xmm6
unwind_case uw_rbp_11_on_2_0, 2, 0, 4096, 0, rbx r12 xmm6
unwind_case uw_rbp_11_on_2_1, 2, 1, 65536, 1, rbx r12 xmm6
unwind_case uw_rbp_11_on_2_5, 2, 5, 65536, 0, rbx r12 xmm6
unwind_case uw_rbp_11_on_2_15, 2, 15, 32, 0, rbx r12 xmm6
unwind_case uw_rbp_11_on_3_0, 3, 0, 65536, 1, rbx r12 r13 xmm6
unwind_case uw_rbp_11_on_3_1, 3, 1, 0, 0, rbx r12 r13 xmm6
unwind_case uw_rbp_11_on_3_5, 3, 5, 0, 0, rbx r12 r13 xmm6
unwind_case uw_rbp_11_on_3_15, 3, 15, 4096, 1, rbx r12 r13 xmm6
unwind_case uw_rbp_11_on_4_0, 4, 0, 0, 0, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_11_on_4_1, 4, 1, 32, 0, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_11_on_4_5, 4, 5, 32, 1, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_11_on_4_15, 4, 15, 65536, 0, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_11_on_5_0, 5, 0, 32, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_11_on_5_1, 5, 1, 4096, 1, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_11_on_5_5, 5, 5, 4096, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_11_on_5_15, 5, 15, 0, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_11_on_6_0, 6, 0, 4096, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_11_on_6_1, 6, 1, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_11_on_6_5, 6, 5, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_11_on_6_15, 6, 15, 32, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_11_on_7_0, 7, 0, 65536, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_rbp_11_on_7_1, 7, 1, 0, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_rbp_11_on_7_5, 7, 5, 0, 1, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_rbp_11_on_7_15, 7, 15, 4096, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
option win64:15
option framepreserveflags:off
unwind_case uw_rbp_15_off_0_0, 0, 0, 0, 1, xmm6
unwind_case uw_rbp_15_off_0_1, 0, 1, 32, 0, xmm6
unwind_case uw_rbp_15_off_0_5, 0, 5, 32, 0, xmm6
unwind_case uw_rbp_15_off_0_15, 0, 15, 65536, 1, xmm6
unwind_case uw_rbp_15_off_1_0, 1, 0, 32, 0, rbx xmm6
unwind_case uw_rbp_15_off_1_1, 1, 1, 4096, 0, rbx xmm6
unwind_case uw_rbp_15_off_1_5, 1, 5, 4096, 1, rbx xmm6
unwind_case uw_rbp_15_off_1_15, 1, 15, 0, 0, rbx xmm6
unwind_case uw_rbp_15_off_2_0, 2, 0, 4096, 0, rbx r12 xmm6
unwind_case uw_rbp_15_off_2_1, 2, 1, 65536, 1, rbx r12 xmm6
unwind_case uw_rbp_15_off_2_5, 2, 5, 65536, 0, rbx r12 xmm6
unwind_case uw_rbp_15_off_2_15, 2, 15, 32, 0, rbx r12 xmm6
unwind_case uw_rbp_15_off_3_0, 3, 0, 65536, 1, rbx r12 r13 xmm6
unwind_case uw_rbp_15_off_3_1, 3, 1, 0, 0, rbx r12 r13 xmm6
unwind_case uw_rbp_15_off_3_5, 3, 5, 0, 0, rbx r12 r13 xmm6
unwind_case uw_rbp_15_off_3_15, 3, 15, 4096, 1, rbx r12 r13 xmm6
unwind_case uw_rbp_15_off_4_0, 4, 0, 0, 0, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_15_off_4_1, 4, 1, 32, 0, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_15_off_4_5, 4, 5, 32, 1, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_15_off_4_15, 4, 15, 65536, 0, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_15_off_5_0, 5, 0, 32, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_15_off_5_1, 5, 1, 4096, 1, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_15_off_5_5, 5, 5, 4096, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_15_off_5_15, 5, 15, 0, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_15_off_6_0, 6, 0, 4096, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_15_off_6_1, 6, 1, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_15_off_6_5, 6, 5, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_15_off_6_15, 6, 15, 32, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_15_off_7_0, 7, 0, 65536, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_rbp_15_off_7_1, 7, 1, 0, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_rbp_15_off_7_5, 7, 5, 0, 1, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_rbp_15_off_7_15, 7, 15, 4096, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
option framepreserveflags:on
unwind_case uw_rbp_15_on_0_0, 0, 0, 0, 1, xmm6
unwind_case uw_rbp_15_on_0_1, 0, 1, 32, 0, xmm6
unwind_case uw_rbp_15_on_0_5, 0, 5, 32, 0, xmm6
unwind_case uw_rbp_15_on_0_15, 0, 15, 65536, 1, xmm6
unwind_case uw_rbp_15_on_1_0, 1, 0, 32, 0, rbx xmm6
unwind_case uw_rbp_15_on_1_1, 1, 1, 4096, 0, rbx xmm6
unwind_case uw_rbp_15_on_1_5, 1, 5, 4096, 1, rbx xmm6
unwind_case uw_rbp_15_on_1_15, 1, 15, 0, 0, rbx xmm6
unwind_case uw_rbp_15_on_2_0, 2, 0, 4096, 0, rbx r12 xmm6
unwind_case uw_rbp_15_on_2_1, 2, 1, 65536, 1, rbx r12 xmm6
unwind_case uw_rbp_15_on_2_5, 2, 5, 65536, 0, rbx r12 xmm6
unwind_case uw_rbp_15_on_2_15, 2, 15, 32, 0, rbx r12 xmm6
unwind_case uw_rbp_15_on_3_0, 3, 0, 65536, 1, rbx r12 r13 xmm6
unwind_case uw_rbp_15_on_3_1, 3, 1, 0, 0, rbx r12 r13 xmm6
unwind_case uw_rbp_15_on_3_5, 3, 5, 0, 0, rbx r12 r13 xmm6
unwind_case uw_rbp_15_on_3_15, 3, 15, 4096, 1, rbx r12 r13 xmm6
unwind_case uw_rbp_15_on_4_0, 4, 0, 0, 0, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_15_on_4_1, 4, 1, 32, 0, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_15_on_4_5, 4, 5, 32, 1, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_15_on_4_15, 4, 15, 65536, 0, rbx r12 r13 r14 xmm6
unwind_case uw_rbp_15_on_5_0, 5, 0, 32, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_15_on_5_1, 5, 1, 4096, 1, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_15_on_5_5, 5, 5, 4096, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_15_on_5_15, 5, 15, 0, 0, rbx r12 r13 r14 r15 xmm6
unwind_case uw_rbp_15_on_6_0, 6, 0, 4096, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_15_on_6_1, 6, 1, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_15_on_6_5, 6, 5, 65536, 0, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_15_on_6_15, 6, 15, 32, 1, rbx r12 r13 r14 r15 rsi xmm6
unwind_case uw_rbp_15_on_7_0, 7, 0, 65536, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_rbp_15_on_7_1, 7, 1, 0, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_rbp_15_on_7_5, 7, 5, 0, 1, rbx r12 r13 r14 r15 rsi rdi xmm6
unwind_case uw_rbp_15_on_7_15, 7, 15, 4096, 0, rbx r12 r13 r14 r15 rsi rdi xmm6
option stackbase:rsp

UnwindHVA struct
 v0 __m128f <>
 v1 __m128f <>
UnwindHVA ends
option framepreserveflags:off
uw_unused_vector proc vectorcall frame uses rbx r12, arg:UnwindHVA
 mov rbx,12345678h
 mov r12,12345678h
 ret
uw_unused_vector endp
; Assembly-only caller establishes the unused HVA signature; not executed.
uw_vector_caller proc frame
 local val:UnwindHVA
 invoke uw_unused_vector,val
 ret
uw_vector_caller endp
; Used vector backing storage, SIMD USES and both frame bases.
option framepreserveflags:off
option stackbase:rsp
option win64:1
uw_vector_rsp_1 proc vectorcall frame uses rbx r12 xmm6, arg:UnwindHVA
local scratch[4]:qword
mov rax,arg
movaps xmm0,[rax]
xor ebx,ebx
xor r12d,r12d
pxor xmm6,xmm6
mov scratch[0],rax
ret
uw_vector_rsp_1 endp
option stackbase:rsp
option win64:3
uw_vector_rsp_3 proc vectorcall frame uses rbx r12 xmm6, arg:UnwindHVA
local scratch[4]:qword
mov rax,arg
movaps xmm0,[rax]
xor ebx,ebx
xor r12d,r12d
pxor xmm6,xmm6
mov scratch[0],rax
ret
uw_vector_rsp_3 endp
option stackbase:rsp
option win64:5
uw_vector_rsp_5 proc vectorcall frame uses rbx r12 xmm6, arg:UnwindHVA
local scratch[4]:qword
mov rax,arg
movaps xmm0,[rax]
xor ebx,ebx
xor r12d,r12d
pxor xmm6,xmm6
mov scratch[0],rax
ret
uw_vector_rsp_5 endp
option stackbase:rsp
option win64:7
uw_vector_rsp_7 proc vectorcall frame uses rbx r12 xmm6, arg:UnwindHVA
local scratch[4]:qword
mov rax,arg
movaps xmm0,[rax]
xor ebx,ebx
xor r12d,r12d
pxor xmm6,xmm6
mov scratch[0],rax
ret
uw_vector_rsp_7 endp
option stackbase:rsp
option win64:11
uw_vector_rsp_11 proc vectorcall frame uses rbx r12 xmm6, arg:UnwindHVA
local scratch[4]:qword
mov rax,arg
movaps xmm0,[rax]
xor ebx,ebx
xor r12d,r12d
pxor xmm6,xmm6
mov scratch[0],rax
ret
uw_vector_rsp_11 endp
option stackbase:rsp
option win64:15
uw_vector_rsp_15 proc vectorcall frame uses rbx r12 xmm6, arg:UnwindHVA
local scratch[4]:qword
mov rax,arg
movaps xmm0,[rax]
xor ebx,ebx
xor r12d,r12d
pxor xmm6,xmm6
mov scratch[0],rax
ret
uw_vector_rsp_15 endp
option stackbase:rbp
option win64:1
uw_vector_rbp_1 proc vectorcall frame uses rbx r12 xmm6, arg:UnwindHVA
local scratch[4]:qword
mov rax,arg
movaps xmm0,[rax]
xor ebx,ebx
xor r12d,r12d
pxor xmm6,xmm6
mov scratch[0],rax
ret
uw_vector_rbp_1 endp
option stackbase:rbp
option win64:3
uw_vector_rbp_3 proc vectorcall frame uses rbx r12 xmm6, arg:UnwindHVA
local scratch[4]:qword
mov rax,arg
movaps xmm0,[rax]
xor ebx,ebx
xor r12d,r12d
pxor xmm6,xmm6
mov scratch[0],rax
ret
uw_vector_rbp_3 endp
option stackbase:rbp
option win64:5
uw_vector_rbp_5 proc vectorcall frame uses rbx r12 xmm6, arg:UnwindHVA
local scratch[4]:qword
mov rax,arg
movaps xmm0,[rax]
xor ebx,ebx
xor r12d,r12d
pxor xmm6,xmm6
mov scratch[0],rax
ret
uw_vector_rbp_5 endp
option stackbase:rbp
option win64:7
uw_vector_rbp_7 proc vectorcall frame uses rbx r12 xmm6, arg:UnwindHVA
local scratch[4]:qword
mov rax,arg
movaps xmm0,[rax]
xor ebx,ebx
xor r12d,r12d
pxor xmm6,xmm6
mov scratch[0],rax
ret
uw_vector_rbp_7 endp
option stackbase:rbp
option win64:11
uw_vector_rbp_11 proc vectorcall frame uses rbx r12 xmm6, arg:UnwindHVA
local scratch[4]:qword
mov rax,arg
movaps xmm0,[rax]
xor ebx,ebx
xor r12d,r12d
pxor xmm6,xmm6
mov scratch[0],rax
ret
uw_vector_rbp_11 endp
option stackbase:rbp
option win64:15
uw_vector_rbp_15 proc vectorcall frame uses rbx r12 xmm6, arg:UnwindHVA
local scratch[4]:qword
mov rax,arg
movaps xmm0,[rax]
xor ebx,ebx
xor r12d,r12d
pxor xmm6,xmm6
mov scratch[0],rax
ret
uw_vector_rbp_15 endp
.data
public UnwindCases,UnwindCaseCount,UnwindFailures
align 8
UnwindFailures dq 0
UnwindCases label qword
 dq uw_11_off_0_0
 dq uw_11_off_0_1
 dq uw_11_off_0_5
 dq uw_11_off_0_15
 dq uw_11_off_1_0
 dq uw_11_off_1_1
 dq uw_11_off_1_5
 dq uw_11_off_1_15
 dq uw_11_off_2_0
 dq uw_11_off_2_1
 dq uw_11_off_2_5
 dq uw_11_off_2_15
 dq uw_11_off_3_0
 dq uw_11_off_3_1
 dq uw_11_off_3_5
 dq uw_11_off_3_15
 dq uw_11_off_4_0
 dq uw_11_off_4_1
 dq uw_11_off_4_5
 dq uw_11_off_4_15
 dq uw_11_off_5_0
 dq uw_11_off_5_1
 dq uw_11_off_5_5
 dq uw_11_off_5_15
 dq uw_11_off_6_0
 dq uw_11_off_6_1
 dq uw_11_off_6_5
 dq uw_11_off_6_15
 dq uw_11_off_7_0
 dq uw_11_off_7_1
 dq uw_11_off_7_5
 dq uw_11_off_7_15
 dq uw_11_off_8_0
 dq uw_11_off_8_1
 dq uw_11_off_8_5
 dq uw_11_off_8_15
 dq uw_11_on_0_0
 dq uw_11_on_0_1
 dq uw_11_on_0_5
 dq uw_11_on_0_15
 dq uw_11_on_1_0
 dq uw_11_on_1_1
 dq uw_11_on_1_5
 dq uw_11_on_1_15
 dq uw_11_on_2_0
 dq uw_11_on_2_1
 dq uw_11_on_2_5
 dq uw_11_on_2_15
 dq uw_11_on_3_0
 dq uw_11_on_3_1
 dq uw_11_on_3_5
 dq uw_11_on_3_15
 dq uw_11_on_4_0
 dq uw_11_on_4_1
 dq uw_11_on_4_5
 dq uw_11_on_4_15
 dq uw_11_on_5_0
 dq uw_11_on_5_1
 dq uw_11_on_5_5
 dq uw_11_on_5_15
 dq uw_11_on_6_0
 dq uw_11_on_6_1
 dq uw_11_on_6_5
 dq uw_11_on_6_15
 dq uw_11_on_7_0
 dq uw_11_on_7_1
 dq uw_11_on_7_5
 dq uw_11_on_7_15
 dq uw_11_on_8_0
 dq uw_11_on_8_1
 dq uw_11_on_8_5
 dq uw_11_on_8_15
 dq uw_15_off_0_0
 dq uw_15_off_0_1
 dq uw_15_off_0_5
 dq uw_15_off_0_15
 dq uw_15_off_1_0
 dq uw_15_off_1_1
 dq uw_15_off_1_5
 dq uw_15_off_1_15
 dq uw_15_off_2_0
 dq uw_15_off_2_1
 dq uw_15_off_2_5
 dq uw_15_off_2_15
 dq uw_15_off_3_0
 dq uw_15_off_3_1
 dq uw_15_off_3_5
 dq uw_15_off_3_15
 dq uw_15_off_4_0
 dq uw_15_off_4_1
 dq uw_15_off_4_5
 dq uw_15_off_4_15
 dq uw_15_off_5_0
 dq uw_15_off_5_1
 dq uw_15_off_5_5
 dq uw_15_off_5_15
 dq uw_15_off_6_0
 dq uw_15_off_6_1
 dq uw_15_off_6_5
 dq uw_15_off_6_15
 dq uw_15_off_7_0
 dq uw_15_off_7_1
 dq uw_15_off_7_5
 dq uw_15_off_7_15
 dq uw_15_off_8_0
 dq uw_15_off_8_1
 dq uw_15_off_8_5
 dq uw_15_off_8_15
 dq uw_15_on_0_0
 dq uw_15_on_0_1
 dq uw_15_on_0_5
 dq uw_15_on_0_15
 dq uw_15_on_1_0
 dq uw_15_on_1_1
 dq uw_15_on_1_5
 dq uw_15_on_1_15
 dq uw_15_on_2_0
 dq uw_15_on_2_1
 dq uw_15_on_2_5
 dq uw_15_on_2_15
 dq uw_15_on_3_0
 dq uw_15_on_3_1
 dq uw_15_on_3_5
 dq uw_15_on_3_15
 dq uw_15_on_4_0
 dq uw_15_on_4_1
 dq uw_15_on_4_5
 dq uw_15_on_4_15
 dq uw_15_on_5_0
 dq uw_15_on_5_1
 dq uw_15_on_5_5
 dq uw_15_on_5_15
 dq uw_15_on_6_0
 dq uw_15_on_6_1
 dq uw_15_on_6_5
 dq uw_15_on_6_15
 dq uw_15_on_7_0
 dq uw_15_on_7_1
 dq uw_15_on_7_5
 dq uw_15_on_7_15
 dq uw_15_on_8_0
 dq uw_15_on_8_1
 dq uw_15_on_8_5
 dq uw_15_on_8_15
 dq uw_unused_vector
 dq uw_rbp_11_off_0_0
 dq uw_rbp_11_off_0_1
 dq uw_rbp_11_off_0_5
 dq uw_rbp_11_off_0_15
 dq uw_rbp_11_off_1_0
 dq uw_rbp_11_off_1_1
 dq uw_rbp_11_off_1_5
 dq uw_rbp_11_off_1_15
 dq uw_rbp_11_off_2_0
 dq uw_rbp_11_off_2_1
 dq uw_rbp_11_off_2_5
 dq uw_rbp_11_off_2_15
 dq uw_rbp_11_off_3_0
 dq uw_rbp_11_off_3_1
 dq uw_rbp_11_off_3_5
 dq uw_rbp_11_off_3_15
 dq uw_rbp_11_off_4_0
 dq uw_rbp_11_off_4_1
 dq uw_rbp_11_off_4_5
 dq uw_rbp_11_off_4_15
 dq uw_rbp_11_off_5_0
 dq uw_rbp_11_off_5_1
 dq uw_rbp_11_off_5_5
 dq uw_rbp_11_off_5_15
 dq uw_rbp_11_off_6_0
 dq uw_rbp_11_off_6_1
 dq uw_rbp_11_off_6_5
 dq uw_rbp_11_off_6_15
 dq uw_rbp_11_off_7_0
 dq uw_rbp_11_off_7_1
 dq uw_rbp_11_off_7_5
 dq uw_rbp_11_off_7_15
 dq uw_rbp_11_on_0_0
 dq uw_rbp_11_on_0_1
 dq uw_rbp_11_on_0_5
 dq uw_rbp_11_on_0_15
 dq uw_rbp_11_on_1_0
 dq uw_rbp_11_on_1_1
 dq uw_rbp_11_on_1_5
 dq uw_rbp_11_on_1_15
 dq uw_rbp_11_on_2_0
 dq uw_rbp_11_on_2_1
 dq uw_rbp_11_on_2_5
 dq uw_rbp_11_on_2_15
 dq uw_rbp_11_on_3_0
 dq uw_rbp_11_on_3_1
 dq uw_rbp_11_on_3_5
 dq uw_rbp_11_on_3_15
 dq uw_rbp_11_on_4_0
 dq uw_rbp_11_on_4_1
 dq uw_rbp_11_on_4_5
 dq uw_rbp_11_on_4_15
 dq uw_rbp_11_on_5_0
 dq uw_rbp_11_on_5_1
 dq uw_rbp_11_on_5_5
 dq uw_rbp_11_on_5_15
 dq uw_rbp_11_on_6_0
 dq uw_rbp_11_on_6_1
 dq uw_rbp_11_on_6_5
 dq uw_rbp_11_on_6_15
 dq uw_rbp_11_on_7_0
 dq uw_rbp_11_on_7_1
 dq uw_rbp_11_on_7_5
 dq uw_rbp_11_on_7_15
 dq uw_rbp_15_off_0_0
 dq uw_rbp_15_off_0_1
 dq uw_rbp_15_off_0_5
 dq uw_rbp_15_off_0_15
 dq uw_rbp_15_off_1_0
 dq uw_rbp_15_off_1_1
 dq uw_rbp_15_off_1_5
 dq uw_rbp_15_off_1_15
 dq uw_rbp_15_off_2_0
 dq uw_rbp_15_off_2_1
 dq uw_rbp_15_off_2_5
 dq uw_rbp_15_off_2_15
 dq uw_rbp_15_off_3_0
 dq uw_rbp_15_off_3_1
 dq uw_rbp_15_off_3_5
 dq uw_rbp_15_off_3_15
 dq uw_rbp_15_off_4_0
 dq uw_rbp_15_off_4_1
 dq uw_rbp_15_off_4_5
 dq uw_rbp_15_off_4_15
 dq uw_rbp_15_off_5_0
 dq uw_rbp_15_off_5_1
 dq uw_rbp_15_off_5_5
 dq uw_rbp_15_off_5_15
 dq uw_rbp_15_off_6_0
 dq uw_rbp_15_off_6_1
 dq uw_rbp_15_off_6_5
 dq uw_rbp_15_off_6_15
 dq uw_rbp_15_off_7_0
 dq uw_rbp_15_off_7_1
 dq uw_rbp_15_off_7_5
 dq uw_rbp_15_off_7_15
 dq uw_rbp_15_on_0_0
 dq uw_rbp_15_on_0_1
 dq uw_rbp_15_on_0_5
 dq uw_rbp_15_on_0_15
 dq uw_rbp_15_on_1_0
 dq uw_rbp_15_on_1_1
 dq uw_rbp_15_on_1_5
 dq uw_rbp_15_on_1_15
 dq uw_rbp_15_on_2_0
 dq uw_rbp_15_on_2_1
 dq uw_rbp_15_on_2_5
 dq uw_rbp_15_on_2_15
 dq uw_rbp_15_on_3_0
 dq uw_rbp_15_on_3_1
 dq uw_rbp_15_on_3_5
 dq uw_rbp_15_on_3_15
 dq uw_rbp_15_on_4_0
 dq uw_rbp_15_on_4_1
 dq uw_rbp_15_on_4_5
 dq uw_rbp_15_on_4_15
 dq uw_rbp_15_on_5_0
 dq uw_rbp_15_on_5_1
 dq uw_rbp_15_on_5_5
 dq uw_rbp_15_on_5_15
 dq uw_rbp_15_on_6_0
 dq uw_rbp_15_on_6_1
 dq uw_rbp_15_on_6_5
 dq uw_rbp_15_on_6_15
 dq uw_rbp_15_on_7_0
 dq uw_rbp_15_on_7_1
 dq uw_rbp_15_on_7_5
 dq uw_rbp_15_on_7_15
 dq uw_vector_rsp_1
 dq uw_vector_rsp_3
 dq uw_vector_rsp_5
 dq uw_vector_rsp_7
 dq uw_vector_rsp_11
 dq uw_vector_rsp_15
 dq uw_vector_rbp_1
 dq uw_vector_rbp_3
 dq uw_vector_rbp_5
 dq uw_vector_rbp_7
 dq uw_vector_rbp_11
 dq uw_vector_rbp_15
UnwindCaseCount dq 285
end
