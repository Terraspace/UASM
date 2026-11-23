; LLVM-verified ISA forms, mixed widths, high registers and memory.
.x64
.model flat
option evex:1
.code
vsm3msg1 xmm1, xmm2, xmm3
vsm3msg1 xmm15, xmm8, xmm14
vsm3msg1 xmm15, xmm8, xmm14
vsm3msg1 xmm15, xmm8, xmm14
vsm3msg1 xmm1, xmm2, xmmword ptr [r13]
vsm3msg1 xmm15, xmm8, xmmword ptr [r12+r14*2+127]
vsm3msg1 xmm15, xmm8, xmmword ptr [r12+r14*2+128]
vsm3msg1 xmm15, xmm8, xmmword ptr [r12+r14*2+1]
vsm3msg2 xmm1, xmm2, xmm3
vsm3msg2 xmm15, xmm8, xmm14
vsm3msg2 xmm15, xmm8, xmm14
vsm3msg2 xmm15, xmm8, xmm14
vsm3msg2 xmm1, xmm2, xmmword ptr [r13]
vsm3msg2 xmm15, xmm8, xmmword ptr [r12+r14*2+127]
vsm3msg2 xmm15, xmm8, xmmword ptr [r12+r14*2+128]
vsm3msg2 xmm15, xmm8, xmmword ptr [r12+r14*2+1]
vsm3rnds2 xmm1, xmm2, xmm3, 0
vsm3rnds2 xmm15, xmm8, xmm14, 1
vsm3rnds2 xmm15, xmm8, xmm14, 128
vsm3rnds2 xmm15, xmm8, xmm14, 255
vsm3rnds2 xmm1, xmm2, xmmword ptr [r13], 0
vsm3rnds2 xmm15, xmm8, xmmword ptr [r12+r14*2+127], 1
vsm3rnds2 xmm15, xmm8, xmmword ptr [r12+r14*2+128], 128
vsm3rnds2 xmm15, xmm8, xmmword ptr [r12+r14*2+1], 255
end
