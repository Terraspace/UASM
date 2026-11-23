; LLVM-verified ISA forms, mixed widths, high registers and memory.
.686p
.xmm
.model flat
option evex:1
.code
vsha512msg1 ymm1, xmm2
vsha512msg1 ymm1, xmm2
vsha512msg1 ymm1, xmm2
vsha512msg1 ymm1, xmm2
vsha512msg2 ymm1, ymm2
vsha512msg2 ymm1, ymm2
vsha512msg2 ymm1, ymm2
vsha512msg2 ymm1, ymm2
vsha512rnds2 ymm1, ymm2, xmm3
vsha512rnds2 ymm1, ymm2, xmm3
vsha512rnds2 ymm1, ymm2, xmm3
vsha512rnds2 ymm1, ymm2, xmm3
end
