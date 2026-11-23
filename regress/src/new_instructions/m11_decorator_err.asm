; FP16 invalid operands/decorators/immediate ranges.
.x64
.model flat
option evex:1
.code
vaddph xmm1, xmm2, xmm3, {rn-sae}
vaddph ymm1, ymm2, ymm3, {sae}
vaddph zmm1, zmm2, zmmword ptr [rax], {rn-sae}
vaddsh xmm1, xmm2, word ptr [rax], {rn-sae}
vrcpph zmm1, zmm2, {sae}
vmovw xmm1{k1}, eax
vmovsh word ptr [rax]{k1}{z}, xmm2
vcomish xmm1{k1}, xmm2
vcmpph k1{k2}{z}, zmm2, zmm3, 1
vaddph zmm1{z}, zmm2, zmm3
vmulsh xmm1, xmm2, word ptr [rax]{1to8}
vaddps zmm1, zmm2, dword ptr [rax]{1to32}
end
