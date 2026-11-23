; M01: byte permutation has no broadcast form; vector widths must match.
.x64
.model flat
option evex:1
.code
vpermt2b xmm1, xmm2, dword ptr [rax]{1to4}
vpermt2b ymm1, ymm2, dword ptr [rax]{1to8}
vpermt2b zmm1, zmm2, dword ptr [rax]{1to16}
vpermt2b xmm1, ymm2, xmm3
vpermt2b ymm1, ymm2, zmm3
end
