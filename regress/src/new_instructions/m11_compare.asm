; AVX-512 FP16: register/memory widths, masks, tuples and legal rounding/SAE.
.x64
.model flat
option evex:1
.code
vcmpph k5, xmm2, xmm3, 17
vcmpph k5{k3}, xmm16, xmm30, 17
vcmpph k5{k3}, xmm16, xmmword ptr [r13], 17
vcmpph k5{k3}, xmm16, xmmword ptr [r12+r14*2+2032], 17
vcmpph k5{k3}, xmm16, xmmword ptr [r12+r14*2+2048], 17
vcmpph k5{k3}, xmm16, xmmword ptr [r12+r14*2+1], 17
vcmpph k5{k3}, xmm16, word ptr [r12+r14*2+254]{1to8}, 17
vcmpph k5, ymm2, ymm3, 17
vcmpph k5{k3}, ymm16, ymm30, 17
vcmpph k5{k3}, ymm16, ymmword ptr [r13], 17
vcmpph k5{k3}, ymm16, ymmword ptr [r12+r14*2+4064], 17
vcmpph k5{k3}, ymm16, ymmword ptr [r12+r14*2+4096], 17
vcmpph k5{k3}, ymm16, ymmword ptr [r12+r14*2+1], 17
vcmpph k5{k3}, ymm16, word ptr [r12+r14*2+254]{1to16}, 17
vcmpph k5, zmm2, zmm3, 17
vcmpph k5{k3}, zmm16, zmm30, 17
vcmpph k5{k3}, zmm16, zmm30, {sae}, 17
vcmpph k5{k3}, zmm16, zmmword ptr [r13], 17
vcmpph k5{k3}, zmm16, zmmword ptr [r12+r14*2+8128], 17
vcmpph k5{k3}, zmm16, zmmword ptr [r12+r14*2+8192], 17
vcmpph k5{k3}, zmm16, zmmword ptr [r12+r14*2+1], 17
vcmpph k5{k3}, zmm16, word ptr [r12+r14*2+254]{1to32}, 17
vcmpsh k5, xmm2, xmm3, 17
vcmpsh k5{k3}, xmm16, xmm30, 17
vcmpsh k5{k3}, xmm16, xmm30, {sae}, 17
vcmpsh k5{k3}, xmm16, word ptr [r13], 17
vcmpsh k5{k3}, xmm16, word ptr [r12+r14*2+254], 17
vcmpsh k5{k3}, xmm16, word ptr [r12+r14*2+256], 17
vcmpsh k5{k3}, xmm16, word ptr [r12+r14*2+1], 17
vcomish xmm1, xmm2
vcomish xmm31, xmm16
vcomish xmm31, xmm16, {sae}
vcomish xmm31, word ptr [r13]
vcomish xmm31, word ptr [r12+r14*2+254]
vcomish xmm31, word ptr [r12+r14*2+256]
vcomish xmm31, word ptr [r12+r14*2+1]
vfpclassph k5, xmm2, 255
vfpclassph k5{k3}, xmm16, 255
vfpclassph k5{k3}, xmmword ptr [r13], 255
vfpclassph k5{k3}, xmmword ptr [r12+r14*2+2032], 255
vfpclassph k5{k3}, xmmword ptr [r12+r14*2+2048], 255
vfpclassph k5{k3}, xmmword ptr [r12+r14*2+1], 255
vfpclassph k5{k3}, word ptr [r12+r14*2+254]{1to8}, 255
vfpclassph k5, ymm2, 255
vfpclassph k5{k3}, ymm16, 255
vfpclassph k5{k3}, ymmword ptr [r13], 255
vfpclassph k5{k3}, ymmword ptr [r12+r14*2+4064], 255
vfpclassph k5{k3}, ymmword ptr [r12+r14*2+4096], 255
vfpclassph k5{k3}, ymmword ptr [r12+r14*2+1], 255
vfpclassph k5{k3}, word ptr [r12+r14*2+254]{1to16}, 255
vfpclassph k5, zmm2, 255
vfpclassph k5{k3}, zmm16, 255
vfpclassph k5{k3}, zmmword ptr [r13], 255
vfpclassph k5{k3}, zmmword ptr [r12+r14*2+8128], 255
vfpclassph k5{k3}, zmmword ptr [r12+r14*2+8192], 255
vfpclassph k5{k3}, zmmword ptr [r12+r14*2+1], 255
vfpclassph k5{k3}, word ptr [r12+r14*2+254]{1to32}, 255
vfpclasssh k5, xmm2, 255
vfpclasssh k5{k3}, xmm16, 255
vfpclasssh k5{k3}, word ptr [r13], 255
vfpclasssh k5{k3}, word ptr [r12+r14*2+254], 255
vfpclasssh k5{k3}, word ptr [r12+r14*2+256], 255
vfpclasssh k5{k3}, word ptr [r12+r14*2+1], 255
vucomish xmm1, xmm2
vucomish xmm31, xmm16
vucomish xmm31, xmm16, {sae}
vucomish xmm31, word ptr [r13]
vucomish xmm31, word ptr [r12+r14*2+254]
vucomish xmm31, word ptr [r12+r14*2+256]
vucomish xmm31, word ptr [r12+r14*2+1]
end
