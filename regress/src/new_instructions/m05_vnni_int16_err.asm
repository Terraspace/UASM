; VEX-only scope: no ZMM, high registers, masking or EVEX promotion.
.x64
.model flat
option evex:1
.code
vpdpwsud zmm1, zmm2, zmm3
vpdpwsud xmm1, ymm2, xmm3
vpdpwsud xmm17, xmm2, xmm3
{evex} vpdpwsud xmm1, xmm2, xmm3
vpdpwsud xmm1{k1}, xmm2, xmm3
vpdpwsuds zmm1, zmm2, zmm3
vpdpwsuds xmm1, ymm2, xmm3
vpdpwsuds xmm17, xmm2, xmm3
{evex} vpdpwsuds xmm1, xmm2, xmm3
vpdpwsuds xmm1{k1}, xmm2, xmm3
vpdpwusd zmm1, zmm2, zmm3
vpdpwusd xmm1, ymm2, xmm3
vpdpwusd xmm17, xmm2, xmm3
{evex} vpdpwusd xmm1, xmm2, xmm3
vpdpwusd xmm1{k1}, xmm2, xmm3
vpdpwusds zmm1, zmm2, zmm3
vpdpwusds xmm1, ymm2, xmm3
vpdpwusds xmm17, xmm2, xmm3
{evex} vpdpwusds xmm1, xmm2, xmm3
vpdpwusds xmm1{k1}, xmm2, xmm3
vpdpwuud zmm1, zmm2, zmm3
vpdpwuud xmm1, ymm2, xmm3
vpdpwuud xmm17, xmm2, xmm3
{evex} vpdpwuud xmm1, xmm2, xmm3
vpdpwuud xmm1{k1}, xmm2, xmm3
vpdpwuuds zmm1, zmm2, zmm3
vpdpwuuds xmm1, ymm2, xmm3
vpdpwuuds xmm17, xmm2, xmm3
{evex} vpdpwuuds xmm1, xmm2, xmm3
vpdpwuuds xmm1{k1}, xmm2, xmm3
end
