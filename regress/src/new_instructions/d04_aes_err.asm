; D04: masks, zeroing and broadcasts are not supported.
.x64
.model flat
option evex:1
.code
vaesenc zmm1{k1}, zmm2, zmm3
vaesenc zmm1{k1}{z}, zmm2, zmm3
vaesenc zmm1, zmm2, dword ptr [rax]{1to16}
vaesenclast zmm1{k1}, zmm2, zmm3
vaesenclast zmm1{k1}{z}, zmm2, zmm3
vaesenclast zmm1, zmm2, dword ptr [rax]{1to16}
vaesdec zmm1{k1}, zmm2, zmm3
vaesdec zmm1{k1}{z}, zmm2, zmm3
vaesdec zmm1, zmm2, dword ptr [rax]{1to16}
vaesdeclast zmm1{k1}, zmm2, zmm3
vaesdeclast zmm1{k1}{z}, zmm2, zmm3
vaesdeclast zmm1, zmm2, dword ptr [rax]{1to16}
end
