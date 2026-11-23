; M03: SSE GFNI; independently verified against LLVM.
.x64
.model flat
.code
gf2p8mulb xmm1, xmm2
gf2p8mulb xmm8, xmm15
gf2p8mulb xmm15, xmm8
gf2p8mulb xmm1, [rbp]
gf2p8mulb xmm15, [r13]
gf2p8mulb xmm8, [r12+r14*4+127]
gf2p8mulb xmm9, [rax+128]
gf2p8mulb xmm10, [rbx-128]
gf2p8mulb xmm11, [rbx-129]
gf2p8affineqb xmm1, xmm2, 0
gf2p8affineqb xmm8, xmm15, 0
gf2p8affineqb xmm15, xmm8, 0
gf2p8affineqb xmm1, [rbp], 0
gf2p8affineqb xmm15, [r13], 0
gf2p8affineqb xmm8, [r12+r14*4+127], 0
gf2p8affineqb xmm9, [rax+128], 0
gf2p8affineqb xmm10, [rbx-128], 0
gf2p8affineqb xmm11, [rbx-129], 0
gf2p8affineqb xmm1, xmm2, 1
gf2p8affineqb xmm8, xmm15, 1
gf2p8affineqb xmm15, xmm8, 1
gf2p8affineqb xmm1, [rbp], 1
gf2p8affineqb xmm15, [r13], 1
gf2p8affineqb xmm8, [r12+r14*4+127], 1
gf2p8affineqb xmm9, [rax+128], 1
gf2p8affineqb xmm10, [rbx-128], 1
gf2p8affineqb xmm11, [rbx-129], 1
gf2p8affineqb xmm1, xmm2, 127
gf2p8affineqb xmm8, xmm15, 127
gf2p8affineqb xmm15, xmm8, 127
gf2p8affineqb xmm1, [rbp], 127
gf2p8affineqb xmm15, [r13], 127
gf2p8affineqb xmm8, [r12+r14*4+127], 127
gf2p8affineqb xmm9, [rax+128], 127
gf2p8affineqb xmm10, [rbx-128], 127
gf2p8affineqb xmm11, [rbx-129], 127
gf2p8affineqb xmm1, xmm2, 128
gf2p8affineqb xmm8, xmm15, 128
gf2p8affineqb xmm15, xmm8, 128
gf2p8affineqb xmm1, [rbp], 128
gf2p8affineqb xmm15, [r13], 128
gf2p8affineqb xmm8, [r12+r14*4+127], 128
gf2p8affineqb xmm9, [rax+128], 128
gf2p8affineqb xmm10, [rbx-128], 128
gf2p8affineqb xmm11, [rbx-129], 128
gf2p8affineqb xmm1, xmm2, 255
gf2p8affineqb xmm8, xmm15, 255
gf2p8affineqb xmm15, xmm8, 255
gf2p8affineqb xmm1, [rbp], 255
gf2p8affineqb xmm15, [r13], 255
gf2p8affineqb xmm8, [r12+r14*4+127], 255
gf2p8affineqb xmm9, [rax+128], 255
gf2p8affineqb xmm10, [rbx-128], 255
gf2p8affineqb xmm11, [rbx-129], 255
gf2p8affineqb xmm1, xmm2, -128
gf2p8affineqb xmm8, xmm15, -128
gf2p8affineqb xmm15, xmm8, -128
gf2p8affineqb xmm1, [rbp], -128
gf2p8affineqb xmm15, [r13], -128
gf2p8affineqb xmm8, [r12+r14*4+127], -128
gf2p8affineqb xmm9, [rax+128], -128
gf2p8affineqb xmm10, [rbx-128], -128
gf2p8affineqb xmm11, [rbx-129], -128
gf2p8affineqb xmm1, xmm2, -1
gf2p8affineqb xmm8, xmm15, -1
gf2p8affineqb xmm15, xmm8, -1
gf2p8affineqb xmm1, [rbp], -1
gf2p8affineqb xmm15, [r13], -1
gf2p8affineqb xmm8, [r12+r14*4+127], -1
gf2p8affineqb xmm9, [rax+128], -1
gf2p8affineqb xmm10, [rbx-128], -1
gf2p8affineqb xmm11, [rbx-129], -1
gf2p8affineinvqb xmm1, xmm2, 0
gf2p8affineinvqb xmm8, xmm15, 0
gf2p8affineinvqb xmm15, xmm8, 0
gf2p8affineinvqb xmm1, [rbp], 0
gf2p8affineinvqb xmm15, [r13], 0
gf2p8affineinvqb xmm8, [r12+r14*4+127], 0
gf2p8affineinvqb xmm9, [rax+128], 0
gf2p8affineinvqb xmm10, [rbx-128], 0
gf2p8affineinvqb xmm11, [rbx-129], 0
gf2p8affineinvqb xmm1, xmm2, 1
gf2p8affineinvqb xmm8, xmm15, 1
gf2p8affineinvqb xmm15, xmm8, 1
gf2p8affineinvqb xmm1, [rbp], 1
gf2p8affineinvqb xmm15, [r13], 1
gf2p8affineinvqb xmm8, [r12+r14*4+127], 1
gf2p8affineinvqb xmm9, [rax+128], 1
gf2p8affineinvqb xmm10, [rbx-128], 1
gf2p8affineinvqb xmm11, [rbx-129], 1
gf2p8affineinvqb xmm1, xmm2, 127
gf2p8affineinvqb xmm8, xmm15, 127
gf2p8affineinvqb xmm15, xmm8, 127
gf2p8affineinvqb xmm1, [rbp], 127
gf2p8affineinvqb xmm15, [r13], 127
gf2p8affineinvqb xmm8, [r12+r14*4+127], 127
gf2p8affineinvqb xmm9, [rax+128], 127
gf2p8affineinvqb xmm10, [rbx-128], 127
gf2p8affineinvqb xmm11, [rbx-129], 127
gf2p8affineinvqb xmm1, xmm2, 128
gf2p8affineinvqb xmm8, xmm15, 128
gf2p8affineinvqb xmm15, xmm8, 128
gf2p8affineinvqb xmm1, [rbp], 128
gf2p8affineinvqb xmm15, [r13], 128
gf2p8affineinvqb xmm8, [r12+r14*4+127], 128
gf2p8affineinvqb xmm9, [rax+128], 128
gf2p8affineinvqb xmm10, [rbx-128], 128
gf2p8affineinvqb xmm11, [rbx-129], 128
gf2p8affineinvqb xmm1, xmm2, 255
gf2p8affineinvqb xmm8, xmm15, 255
gf2p8affineinvqb xmm15, xmm8, 255
gf2p8affineinvqb xmm1, [rbp], 255
gf2p8affineinvqb xmm15, [r13], 255
gf2p8affineinvqb xmm8, [r12+r14*4+127], 255
gf2p8affineinvqb xmm9, [rax+128], 255
gf2p8affineinvqb xmm10, [rbx-128], 255
gf2p8affineinvqb xmm11, [rbx-129], 255
gf2p8affineinvqb xmm1, xmm2, -128
gf2p8affineinvqb xmm8, xmm15, -128
gf2p8affineinvqb xmm15, xmm8, -128
gf2p8affineinvqb xmm1, [rbp], -128
gf2p8affineinvqb xmm15, [r13], -128
gf2p8affineinvqb xmm8, [r12+r14*4+127], -128
gf2p8affineinvqb xmm9, [rax+128], -128
gf2p8affineinvqb xmm10, [rbx-128], -128
gf2p8affineinvqb xmm11, [rbx-129], -128
gf2p8affineinvqb xmm1, xmm2, -1
gf2p8affineinvqb xmm8, xmm15, -1
gf2p8affineinvqb xmm15, xmm8, -1
gf2p8affineinvqb xmm1, [rbp], -1
gf2p8affineinvqb xmm15, [r13], -1
gf2p8affineinvqb xmm8, [r12+r14*4+127], -1
gf2p8affineinvqb xmm9, [rax+128], -1
gf2p8affineinvqb xmm10, [rbx-128], -1
gf2p8affineinvqb xmm11, [rbx-129], -1
end
