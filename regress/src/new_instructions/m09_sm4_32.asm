; LLVM-verified ISA forms, mixed widths, high registers and memory.
.686p
.xmm
.model flat
option evex:1
.code
vsm4key4 xmm1, xmm2, xmm3
vsm4key4 xmm1, xmm2, xmm3
vsm4key4 xmm1, xmm2, xmm3
vsm4key4 xmm1, xmm2, xmm3
vsm4key4 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm4key4 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm4key4 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm4key4 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm4key4 ymm1, ymm2, ymm3
vsm4key4 ymm1, ymm2, ymm3
vsm4key4 ymm1, ymm2, ymm3
vsm4key4 ymm1, ymm2, ymm3
vsm4key4 ymm1, ymm2, ymmword ptr [ebx+esi*2+128]
vsm4key4 ymm1, ymm2, ymmword ptr [ebx+esi*2+128]
vsm4key4 ymm1, ymm2, ymmword ptr [ebx+esi*2+128]
vsm4key4 ymm1, ymm2, ymmword ptr [ebx+esi*2+128]
vsm4rnds4 xmm1, xmm2, xmm3
vsm4rnds4 xmm1, xmm2, xmm3
vsm4rnds4 xmm1, xmm2, xmm3
vsm4rnds4 xmm1, xmm2, xmm3
vsm4rnds4 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm4rnds4 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm4rnds4 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm4rnds4 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm4rnds4 ymm1, ymm2, ymm3
vsm4rnds4 ymm1, ymm2, ymm3
vsm4rnds4 ymm1, ymm2, ymm3
vsm4rnds4 ymm1, ymm2, ymm3
vsm4rnds4 ymm1, ymm2, ymmword ptr [ebx+esi*2+128]
vsm4rnds4 ymm1, ymm2, ymmword ptr [ebx+esi*2+128]
vsm4rnds4 ymm1, ymm2, ymmword ptr [ebx+esi*2+128]
vsm4rnds4 ymm1, ymm2, ymmword ptr [ebx+esi*2+128]
end
