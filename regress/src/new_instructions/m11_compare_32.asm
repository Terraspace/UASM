; AVX-512 FP16: register/memory widths, masks, tuples and legal rounding/SAE.
.686p
.xmm
.model flat
option evex:1
.code
vcmpph k5, xmm2, xmm3, 17
vcmpph k5{k3}, xmm2, xmm3, 17
vcmpph k5{k3}, xmm2, xmmword ptr [ebx+esi*2+0], 17
vcmpph k5{k3}, xmm2, xmmword ptr [ebx+esi*2+2032], 17
vcmpph k5{k3}, xmm2, xmmword ptr [ebx+esi*2+2048], 17
vcmpph k5{k3}, xmm2, xmmword ptr [ebx+esi*2+1], 17
vcmpph k5{k3}, xmm2, word ptr [ebx+esi*2+254]{1to8}, 17
vcmpph k5, ymm2, ymm3, 17
vcmpph k5{k3}, ymm2, ymm3, 17
vcmpph k5{k3}, ymm2, ymmword ptr [ebx+esi*2+0], 17
vcmpph k5{k3}, ymm2, ymmword ptr [ebx+esi*2+4064], 17
vcmpph k5{k3}, ymm2, ymmword ptr [ebx+esi*2+4096], 17
vcmpph k5{k3}, ymm2, ymmword ptr [ebx+esi*2+1], 17
vcmpph k5{k3}, ymm2, word ptr [ebx+esi*2+254]{1to16}, 17
vcmpph k5, zmm2, zmm3, 17
vcmpph k5{k3}, zmm2, zmm3, 17
vcmpph k5{k3}, zmm2, zmm3, {sae}, 17
vcmpph k5{k3}, zmm2, zmmword ptr [ebx+esi*2+0], 17
vcmpph k5{k3}, zmm2, zmmword ptr [ebx+esi*2+8128], 17
vcmpph k5{k3}, zmm2, zmmword ptr [ebx+esi*2+8192], 17
vcmpph k5{k3}, zmm2, zmmword ptr [ebx+esi*2+1], 17
vcmpph k5{k3}, zmm2, word ptr [ebx+esi*2+254]{1to32}, 17
vcmpsh k5, xmm2, xmm3, 17
vcmpsh k5{k3}, xmm2, xmm3, 17
vcmpsh k5{k3}, xmm2, xmm3, {sae}, 17
vcmpsh k5{k3}, xmm2, word ptr [ebx+esi*2+0], 17
vcmpsh k5{k3}, xmm2, word ptr [ebx+esi*2+254], 17
vcmpsh k5{k3}, xmm2, word ptr [ebx+esi*2+256], 17
vcmpsh k5{k3}, xmm2, word ptr [ebx+esi*2+1], 17
vcomish xmm1, xmm2
vcomish xmm1, xmm2
vcomish xmm1, xmm2, {sae}
vcomish xmm1, word ptr [ebx+esi*2+0]
vcomish xmm1, word ptr [ebx+esi*2+254]
vcomish xmm1, word ptr [ebx+esi*2+256]
vcomish xmm1, word ptr [ebx+esi*2+1]
vfpclassph k5, xmm2, 255
vfpclassph k5{k3}, xmm2, 255
vfpclassph k5{k3}, xmmword ptr [ebx+esi*2+0], 255
vfpclassph k5{k3}, xmmword ptr [ebx+esi*2+2032], 255
vfpclassph k5{k3}, xmmword ptr [ebx+esi*2+2048], 255
vfpclassph k5{k3}, xmmword ptr [ebx+esi*2+1], 255
vfpclassph k5{k3}, word ptr [ebx+esi*2+254]{1to8}, 255
vfpclassph k5, ymm2, 255
vfpclassph k5{k3}, ymm2, 255
vfpclassph k5{k3}, ymmword ptr [ebx+esi*2+0], 255
vfpclassph k5{k3}, ymmword ptr [ebx+esi*2+4064], 255
vfpclassph k5{k3}, ymmword ptr [ebx+esi*2+4096], 255
vfpclassph k5{k3}, ymmword ptr [ebx+esi*2+1], 255
vfpclassph k5{k3}, word ptr [ebx+esi*2+254]{1to16}, 255
vfpclassph k5, zmm2, 255
vfpclassph k5{k3}, zmm2, 255
vfpclassph k5{k3}, zmmword ptr [ebx+esi*2+0], 255
vfpclassph k5{k3}, zmmword ptr [ebx+esi*2+8128], 255
vfpclassph k5{k3}, zmmword ptr [ebx+esi*2+8192], 255
vfpclassph k5{k3}, zmmword ptr [ebx+esi*2+1], 255
vfpclassph k5{k3}, word ptr [ebx+esi*2+254]{1to32}, 255
vfpclasssh k5, xmm2, 255
vfpclasssh k5{k3}, xmm2, 255
vfpclasssh k5{k3}, word ptr [ebx+esi*2+0], 255
vfpclasssh k5{k3}, word ptr [ebx+esi*2+254], 255
vfpclasssh k5{k3}, word ptr [ebx+esi*2+256], 255
vfpclasssh k5{k3}, word ptr [ebx+esi*2+1], 255
vucomish xmm1, xmm2
vucomish xmm1, xmm2
vucomish xmm1, xmm2, {sae}
vucomish xmm1, word ptr [ebx+esi*2+0]
vucomish xmm1, word ptr [ebx+esi*2+254]
vucomish xmm1, word ptr [ebx+esi*2+256]
vucomish xmm1, word ptr [ebx+esi*2+1]
end
