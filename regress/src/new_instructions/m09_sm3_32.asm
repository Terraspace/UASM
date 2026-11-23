; LLVM-verified ISA forms, mixed widths, high registers and memory.
.686p
.xmm
.model flat
option evex:1
.code
vsm3msg1 xmm1, xmm2, xmm3
vsm3msg1 xmm1, xmm2, xmm3
vsm3msg1 xmm1, xmm2, xmm3
vsm3msg1 xmm1, xmm2, xmm3
vsm3msg1 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm3msg1 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm3msg1 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm3msg1 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm3msg2 xmm1, xmm2, xmm3
vsm3msg2 xmm1, xmm2, xmm3
vsm3msg2 xmm1, xmm2, xmm3
vsm3msg2 xmm1, xmm2, xmm3
vsm3msg2 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm3msg2 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm3msg2 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm3msg2 xmm1, xmm2, xmmword ptr [ebx+esi*2+128]
vsm3rnds2 xmm1, xmm2, xmm3, 0
vsm3rnds2 xmm1, xmm2, xmm3, 1
vsm3rnds2 xmm1, xmm2, xmm3, 128
vsm3rnds2 xmm1, xmm2, xmm3, 255
vsm3rnds2 xmm1, xmm2, xmmword ptr [ebx+esi*2+128], 0
vsm3rnds2 xmm1, xmm2, xmmword ptr [ebx+esi*2+128], 1
vsm3rnds2 xmm1, xmm2, xmmword ptr [ebx+esi*2+128], 128
vsm3rnds2 xmm1, xmm2, xmmword ptr [ebx+esi*2+128], 255
end
