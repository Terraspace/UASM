; LLVM-verified ISA forms, mixed widths, high registers and memory.
.x64
.model flat
option evex:1
.code
vsm4key4 xmm1, xmm2, xmm3
vsm4key4 xmm15, xmm8, xmm14
vsm4key4 xmm15, xmm8, xmm14
vsm4key4 xmm15, xmm8, xmm14
vsm4key4 xmm1, xmm2, xmmword ptr [r13]
vsm4key4 xmm15, xmm8, xmmword ptr [r12+r14*2+127]
vsm4key4 xmm15, xmm8, xmmword ptr [r12+r14*2+128]
vsm4key4 xmm15, xmm8, xmmword ptr [r12+r14*2+1]
vsm4key4 ymm1, ymm2, ymm3
vsm4key4 ymm15, ymm8, ymm14
vsm4key4 ymm15, ymm8, ymm14
vsm4key4 ymm15, ymm8, ymm14
vsm4key4 ymm1, ymm2, ymmword ptr [r13]
vsm4key4 ymm15, ymm8, ymmword ptr [r12+r14*2+127]
vsm4key4 ymm15, ymm8, ymmword ptr [r12+r14*2+128]
vsm4key4 ymm15, ymm8, ymmword ptr [r12+r14*2+1]
vsm4rnds4 xmm1, xmm2, xmm3
vsm4rnds4 xmm15, xmm8, xmm14
vsm4rnds4 xmm15, xmm8, xmm14
vsm4rnds4 xmm15, xmm8, xmm14
vsm4rnds4 xmm1, xmm2, xmmword ptr [r13]
vsm4rnds4 xmm15, xmm8, xmmword ptr [r12+r14*2+127]
vsm4rnds4 xmm15, xmm8, xmmword ptr [r12+r14*2+128]
vsm4rnds4 xmm15, xmm8, xmmword ptr [r12+r14*2+1]
vsm4rnds4 ymm1, ymm2, ymm3
vsm4rnds4 ymm15, ymm8, ymm14
vsm4rnds4 ymm15, ymm8, ymm14
vsm4rnds4 ymm15, ymm8, ymm14
vsm4rnds4 ymm1, ymm2, ymmword ptr [r13]
vsm4rnds4 ymm15, ymm8, ymmword ptr [r12+r14*2+127]
vsm4rnds4 ymm15, ymm8, ymmword ptr [r12+r14*2+128]
vsm4rnds4 ymm15, ymm8, ymmword ptr [r12+r14*2+1]
end
