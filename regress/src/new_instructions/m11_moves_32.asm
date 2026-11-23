; AVX-512 FP16: register/memory widths, masks, tuples and legal rounding/SAE.
.686p
.xmm
.model flat
option evex:1
.code
vmovsh xmm1{k3}, word ptr [ebx+esi*2+0]
vmovsh xmm1{k3}{z}, word ptr [ebx+esi*2+254]
vmovsh xmm1{k3}, word ptr [ebx+esi*2+256]
vmovsh xmm1{k3}, word ptr [ebx+esi*2+1]
vmovsh word ptr [ebx+esi*2+0]{k3}, xmm2
vmovsh word ptr [ebx+esi*2+254]{k3}, xmm2
vmovsh word ptr [ebx+esi*2+256]{k3}, xmm2
vmovsh word ptr [ebx+esi*2+1]{k3}, xmm2
vmovsh xmm1, xmm2, xmm3
vmovsh xmm1{k3}{z}, xmm2, xmm3
vmovw xmm1, ecx
vmovw xmm1, ecx
vmovw xmm1, word ptr [ebx+esi*2+0]
vmovw xmm1, word ptr [ebx+esi*2+254]
vmovw xmm1, word ptr [ebx+esi*2+256]
vmovw xmm1, word ptr [ebx+esi*2+1]
vmovw ecx, xmm2
vmovw ecx, xmm2
vmovw word ptr [ebx+esi*2+0], xmm2
vmovw word ptr [ebx+esi*2+254], xmm2
vmovw word ptr [ebx+esi*2+256], xmm2
vmovw word ptr [ebx+esi*2+1], xmm2
end
