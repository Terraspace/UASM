
; AVX-512BW instructions: VPBROADCASTW with GPR source and
; VPMOVZXBW / VPMOVSXBW with ZMM destination.
; These require option evex:1 but no opmask decoration.

    .x64
    .model flat
    option evex:1
    .code

; vpbroadcastw zmm, r32 (EVEX.512.66.0F38.W0 7B /r)
    vpbroadcastw zmm0, eax
    vpbroadcastw zmm13, esi
    vpbroadcastw zmm29, eax
    vpbroadcastw ymm5, edx
    vpbroadcastw xmm3, ecx

; vpmovzxbw zmm, ymm (EVEX.512.66.0F38.WIG 30 /r)
    vpmovzxbw zmm0, ymm1
    vpmovzxbw zmm30, ymm29
    vpmovzxbw zmm0, ymmword ptr [rax]
    vpmovzxbw zmm15, ymmword ptr [rcx+rdx*4]
    vpmovzxbw zmm0{k1}, ymm1
    vpmovzxbw zmm0{k1}{z}, ymm1

; vpmovsxbw zmm, ymm (EVEX.512.66.0F38.WIG 20 /r)
    vpmovsxbw zmm0, ymm1
    vpmovsxbw zmm30, ymm29
    vpmovsxbw zmm0, ymmword ptr [rax]

    end
