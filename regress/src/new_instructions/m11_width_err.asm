; FP16 invalid operands/decorators/immediate ranges.
.x64
.model flat
option evex:1
.code
vaddph xmm1, ymm2, xmm3
vaddsh ymm1, ymm2, ymm3
vcvtph2pd xmm1, ymm2
vcvtpd2ph ymm1, ymm2
vcomish xmm1, dword ptr [rax]
vmovw xmm1, rax
vmovw xmm1, dword ptr [rax]
vaddph zmm1, zmm2, dword ptr [rax]{1to32}
vcvtph2pd zmm1, word ptr [rax]{1to32}
vfpclassph xmm1, xmm2, 1
vcmpph zmm1, zmm2, zmm3, 1
end
