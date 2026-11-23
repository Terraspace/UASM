; AVX-512 FP16: register/memory widths, masks, tuples and legal rounding/SAE.
.x64
.model flat
option evex:1
.code
vmovsh xmm31{k3}, word ptr [r13]
vmovsh xmm31{k3}{z}, word ptr [r12+r14*2+254]
vmovsh xmm31{k3}, word ptr [r12+r14*2+256]
vmovsh xmm31{k3}, word ptr [r12+r14*2+1]
vmovsh word ptr [r13]{k3}, xmm16
vmovsh word ptr [r12+r14*2+254]{k3}, xmm16
vmovsh word ptr [r12+r14*2+256]{k3}, xmm16
vmovsh word ptr [r12+r14*2+1]{k3}, xmm16
vmovsh xmm1, xmm2, xmm3
vmovsh xmm31{k3}{z}, xmm16, xmm30
vmovw xmm1, ecx
vmovw xmm31, r9d
vmovw xmm31, word ptr [r13]
vmovw xmm31, word ptr [r12+r14*2+254]
vmovw xmm31, word ptr [r12+r14*2+256]
vmovw xmm31, word ptr [r12+r14*2+1]
vmovw ecx, xmm2
vmovw r9d, xmm16
vmovw word ptr [r13], xmm16
vmovw word ptr [r12+r14*2+254], xmm16
vmovw word ptr [r12+r14*2+256], xmm16
vmovw word ptr [r12+r14*2+1], xmm16
end
