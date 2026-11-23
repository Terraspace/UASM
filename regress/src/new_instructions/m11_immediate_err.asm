; FP16 invalid operands/decorators/immediate ranges.
.x64
.model flat
option evex:1
.code
vgetmantph xmm1, xmm2, 256
vrndscaleph zmm1, zmm2, -129
vfpclassph k1, zmm2, 256
vcmpsh k1, xmm2, xmm3, 256
vreducesh xmm1, xmm2, xmm3, 256
end
