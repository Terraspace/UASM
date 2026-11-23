; LLVM-verified ISA forms, mixed widths, high registers and memory.
.x64
.model flat
option evex:1
.code
vbcstnebf162ps xmm1, word ptr [r13]
vbcstnebf162ps xmm15, word ptr [r12+r14*2+127]
vbcstnebf162ps xmm15, word ptr [r12+r14*2+128]
vbcstnebf162ps xmm15, word ptr [r12+r14*2+1]
vbcstnebf162ps ymm1, word ptr [r13]
vbcstnebf162ps ymm15, word ptr [r12+r14*2+127]
vbcstnebf162ps ymm15, word ptr [r12+r14*2+128]
vbcstnebf162ps ymm15, word ptr [r12+r14*2+1]
vbcstnesh2ps xmm1, word ptr [r13]
vbcstnesh2ps xmm15, word ptr [r12+r14*2+127]
vbcstnesh2ps xmm15, word ptr [r12+r14*2+128]
vbcstnesh2ps xmm15, word ptr [r12+r14*2+1]
vbcstnesh2ps ymm1, word ptr [r13]
vbcstnesh2ps ymm15, word ptr [r12+r14*2+127]
vbcstnesh2ps ymm15, word ptr [r12+r14*2+128]
vbcstnesh2ps ymm15, word ptr [r12+r14*2+1]
vcvtneebf162ps xmm1, xmmword ptr [r13]
vcvtneebf162ps xmm15, xmmword ptr [r12+r14*2+127]
vcvtneebf162ps xmm15, xmmword ptr [r12+r14*2+128]
vcvtneebf162ps xmm15, xmmword ptr [r12+r14*2+1]
vcvtneebf162ps ymm1, ymmword ptr [r13]
vcvtneebf162ps ymm15, ymmword ptr [r12+r14*2+127]
vcvtneebf162ps ymm15, ymmword ptr [r12+r14*2+128]
vcvtneebf162ps ymm15, ymmword ptr [r12+r14*2+1]
vcvtneeph2ps xmm1, xmmword ptr [r13]
vcvtneeph2ps xmm15, xmmword ptr [r12+r14*2+127]
vcvtneeph2ps xmm15, xmmword ptr [r12+r14*2+128]
vcvtneeph2ps xmm15, xmmword ptr [r12+r14*2+1]
vcvtneeph2ps ymm1, ymmword ptr [r13]
vcvtneeph2ps ymm15, ymmword ptr [r12+r14*2+127]
vcvtneeph2ps ymm15, ymmword ptr [r12+r14*2+128]
vcvtneeph2ps ymm15, ymmword ptr [r12+r14*2+1]
vcvtneobf162ps xmm1, xmmword ptr [r13]
vcvtneobf162ps xmm15, xmmword ptr [r12+r14*2+127]
vcvtneobf162ps xmm15, xmmword ptr [r12+r14*2+128]
vcvtneobf162ps xmm15, xmmword ptr [r12+r14*2+1]
vcvtneobf162ps ymm1, ymmword ptr [r13]
vcvtneobf162ps ymm15, ymmword ptr [r12+r14*2+127]
vcvtneobf162ps ymm15, ymmword ptr [r12+r14*2+128]
vcvtneobf162ps ymm15, ymmword ptr [r12+r14*2+1]
vcvtneoph2ps xmm1, xmmword ptr [r13]
vcvtneoph2ps xmm15, xmmword ptr [r12+r14*2+127]
vcvtneoph2ps xmm15, xmmword ptr [r12+r14*2+128]
vcvtneoph2ps xmm15, xmmword ptr [r12+r14*2+1]
vcvtneoph2ps ymm1, ymmword ptr [r13]
vcvtneoph2ps ymm15, ymmword ptr [r12+r14*2+127]
vcvtneoph2ps ymm15, ymmword ptr [r12+r14*2+128]
vcvtneoph2ps ymm15, ymmword ptr [r12+r14*2+1]
vcvtneps2bf16 xmm1, xmm2
vcvtneps2bf16 xmm15, xmm8
vcvtneps2bf16 xmm15, xmm8
vcvtneps2bf16 xmm15, xmm8
vcvtneps2bf16 xmm1, xmmword ptr [r13]
vcvtneps2bf16 xmm15, xmmword ptr [r12+r14*2+127]
vcvtneps2bf16 xmm15, xmmword ptr [r12+r14*2+128]
vcvtneps2bf16 xmm15, xmmword ptr [r12+r14*2+1]
vcvtneps2bf16 xmm1, ymm2
vcvtneps2bf16 xmm15, ymm8
vcvtneps2bf16 xmm15, ymm8
vcvtneps2bf16 xmm15, ymm8
vcvtneps2bf16 xmm1, ymmword ptr [r13]
vcvtneps2bf16 xmm15, ymmword ptr [r12+r14*2+127]
vcvtneps2bf16 xmm15, ymmword ptr [r12+r14*2+128]
vcvtneps2bf16 xmm15, ymmword ptr [r12+r14*2+1]
end
