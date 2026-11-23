; VEX-only scope: no ZMM, high registers, masking or EVEX promotion.
.x64
.model flat
option evex:1
.code
vpdpbssd zmm1, zmm2, zmm3
vpdpbssd xmm1, ymm2, xmm3
vpdpbssd xmm17, xmm2, xmm3
{evex} vpdpbssd xmm1, xmm2, xmm3
vpdpbssd xmm1{k1}, xmm2, xmm3
vpdpbssds zmm1, zmm2, zmm3
vpdpbssds xmm1, ymm2, xmm3
vpdpbssds xmm17, xmm2, xmm3
{evex} vpdpbssds xmm1, xmm2, xmm3
vpdpbssds xmm1{k1}, xmm2, xmm3
vpdpbsud zmm1, zmm2, zmm3
vpdpbsud xmm1, ymm2, xmm3
vpdpbsud xmm17, xmm2, xmm3
{evex} vpdpbsud xmm1, xmm2, xmm3
vpdpbsud xmm1{k1}, xmm2, xmm3
vpdpbsuds zmm1, zmm2, zmm3
vpdpbsuds xmm1, ymm2, xmm3
vpdpbsuds xmm17, xmm2, xmm3
{evex} vpdpbsuds xmm1, xmm2, xmm3
vpdpbsuds xmm1{k1}, xmm2, xmm3
vpdpbuud zmm1, zmm2, zmm3
vpdpbuud xmm1, ymm2, xmm3
vpdpbuud xmm17, xmm2, xmm3
{evex} vpdpbuud xmm1, xmm2, xmm3
vpdpbuud xmm1{k1}, xmm2, xmm3
vpdpbuuds zmm1, zmm2, zmm3
vpdpbuuds xmm1, ymm2, xmm3
vpdpbuuds xmm17, xmm2, xmm3
{evex} vpdpbuuds xmm1, xmm2, xmm3
vpdpbuuds xmm1{k1}, xmm2, xmm3
end
