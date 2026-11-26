; Legacy codegen precedence regression; EXP independently assembled with LLVM.
.x64
.model flat
option evex:1
.code
vpmovmskb eax, xmm0
vpmovmskb eax, xmm7
vpmovmskb eax, xmm8
vpmovmskb eax, xmm15
vpmovmskb eax, ymm0
vpmovmskb eax, ymm7
vpmovmskb eax, ymm8
vpmovmskb eax, ymm15
vpmovmskb r8d, xmm0
vpmovmskb r8d, xmm7
vpmovmskb r8d, xmm8
vpmovmskb r8d, xmm15
vpmovmskb r8d, ymm0
vpmovmskb r8d, ymm7
vpmovmskb r8d, ymm8
vpmovmskb r8d, ymm15
vpmovmskb r15d, xmm0
vpmovmskb r15d, xmm7
vpmovmskb r15d, xmm8
vpmovmskb r15d, xmm15
vpmovmskb r15d, ymm0
vpmovmskb r15d, ymm7
vpmovmskb r15d, ymm8
vpmovmskb r15d, ymm15
vpmovmskb rax, xmm0
vpmovmskb rax, xmm7
vpmovmskb rax, xmm8
vpmovmskb rax, xmm15
vpmovmskb rax, ymm0
vpmovmskb rax, ymm7
vpmovmskb rax, ymm8
vpmovmskb rax, ymm15
vpmovmskb r8, xmm0
vpmovmskb r8, xmm7
vpmovmskb r8, xmm8
vpmovmskb r8, xmm15
vpmovmskb r8, ymm0
vpmovmskb r8, ymm7
vpmovmskb r8, ymm8
vpmovmskb r8, ymm15
vpmovmskb r15, xmm0
vpmovmskb r15, xmm7
vpmovmskb r15, xmm8
vpmovmskb r15, xmm15
vpmovmskb r15, ymm0
vpmovmskb r15, ymm7
vpmovmskb r15, ymm8
vpmovmskb r15, ymm15
end
