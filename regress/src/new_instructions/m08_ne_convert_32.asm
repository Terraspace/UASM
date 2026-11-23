; LLVM-verified ISA forms, mixed widths, high registers and memory.
.686p
.xmm
.model flat
option evex:1
.code
vbcstnebf162ps xmm1, word ptr [ebx+esi*2+128]
vbcstnebf162ps xmm1, word ptr [ebx+esi*2+128]
vbcstnebf162ps xmm1, word ptr [ebx+esi*2+128]
vbcstnebf162ps xmm1, word ptr [ebx+esi*2+128]
vbcstnebf162ps ymm1, word ptr [ebx+esi*2+128]
vbcstnebf162ps ymm1, word ptr [ebx+esi*2+128]
vbcstnebf162ps ymm1, word ptr [ebx+esi*2+128]
vbcstnebf162ps ymm1, word ptr [ebx+esi*2+128]
vbcstnesh2ps xmm1, word ptr [ebx+esi*2+128]
vbcstnesh2ps xmm1, word ptr [ebx+esi*2+128]
vbcstnesh2ps xmm1, word ptr [ebx+esi*2+128]
vbcstnesh2ps xmm1, word ptr [ebx+esi*2+128]
vbcstnesh2ps ymm1, word ptr [ebx+esi*2+128]
vbcstnesh2ps ymm1, word ptr [ebx+esi*2+128]
vbcstnesh2ps ymm1, word ptr [ebx+esi*2+128]
vbcstnesh2ps ymm1, word ptr [ebx+esi*2+128]
vcvtneebf162ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneebf162ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneebf162ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneebf162ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneebf162ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneebf162ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneebf162ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneebf162ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneeph2ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneeph2ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneeph2ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneeph2ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneeph2ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneeph2ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneeph2ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneeph2ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneobf162ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneobf162ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneobf162ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneobf162ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneobf162ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneobf162ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneobf162ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneobf162ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneoph2ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneoph2ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneoph2ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneoph2ps xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneoph2ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneoph2ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneoph2ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneoph2ps ymm1, ymmword ptr [ebx+esi*2+128]
vcvtneps2bf16 xmm1, xmm2
vcvtneps2bf16 xmm1, xmm2
vcvtneps2bf16 xmm1, xmm2
vcvtneps2bf16 xmm1, xmm2
vcvtneps2bf16 xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneps2bf16 xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneps2bf16 xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneps2bf16 xmm1, xmmword ptr [ebx+esi*2+128]
vcvtneps2bf16 xmm1, ymm2
vcvtneps2bf16 xmm1, ymm2
vcvtneps2bf16 xmm1, ymm2
vcvtneps2bf16 xmm1, ymm2
vcvtneps2bf16 xmm1, ymmword ptr [ebx+esi*2+128]
vcvtneps2bf16 xmm1, ymmword ptr [ebx+esi*2+128]
vcvtneps2bf16 xmm1, ymmword ptr [ebx+esi*2+128]
vcvtneps2bf16 xmm1, ymmword ptr [ebx+esi*2+128]
end
