; M02: wrong operand classes/widths and unsupported decorators.
.x64
.model flat
option evex:1
.code
vpopcntd k1, k2
vpopcntq xmm1, ymm2
vpopcntb xmm1, dword ptr [rax]{1to4}
vpopcntw zmm1, qword ptr [rax]{1to8}
vpopcntd zmm1, dword ptr [rax]{1to8}
vpshufbitqmb zmm1, zmm2, zmm3
vpshufbitqmb k1{k2}{z}, zmm2, zmm3
vpshufbitqmb k1, zmm2, qword ptr [rax]{1to8}
vpshufbitqmb k1, xmm2, ymm3
end
