; D04: masks, zeroing and broadcasts are not supported.
.x64
.model flat
option evex:1
.code
vpclmulqdq zmm1{k1}, zmm2, zmm3, 17
vpclmulqdq zmm1{k1}{z}, zmm2, zmm3, 17
vpclmulqdq zmm1, zmm2, dword ptr [rax]{1to16}, 17
vpclmulqdq zmm1, zmm2, zmm3, 256
vpclmulqdq zmm1, zmm2, zmm3, -129
end
