; M02: expected bytes checked against LLVM; masks/high registers/displacement boundaries.
.x64
.model flat
option evex:1
.code
vpshufbitqmb k0, xmm1, xmm2
vpshufbitqmb k7{k3}, xmm22, xmm30
vpshufbitqmb k1, xmm16, [r13]
vpshufbitqmb k2{k1}, xmm19, [r12+r14*2+2032]
vpshufbitqmb k2{k1}, xmm19, [r12+r14*2+2048]
vpshufbitqmb k2{k1}, xmm19, [r12+r14*2-2048]
vpshufbitqmb k2{k1}, xmm19, [r12+r14*2-2064]
vpshufbitqmb k2{k1}, xmm19, [r12+r14*2+1]
vpshufbitqmb k0, ymm1, ymm2
vpshufbitqmb k7{k3}, ymm22, ymm30
vpshufbitqmb k1, ymm16, [r13]
vpshufbitqmb k2{k1}, ymm19, [r12+r14*2+4064]
vpshufbitqmb k2{k1}, ymm19, [r12+r14*2+4096]
vpshufbitqmb k2{k1}, ymm19, [r12+r14*2-4096]
vpshufbitqmb k2{k1}, ymm19, [r12+r14*2-4128]
vpshufbitqmb k2{k1}, ymm19, [r12+r14*2+1]
vpshufbitqmb k0, zmm1, zmm2
vpshufbitqmb k7{k3}, zmm22, zmm30
vpshufbitqmb k1, zmm16, [r13]
vpshufbitqmb k2{k1}, zmm19, [r12+r14*2+8128]
vpshufbitqmb k2{k1}, zmm19, [r12+r14*2+8192]
vpshufbitqmb k2{k1}, zmm19, [r12+r14*2-8192]
vpshufbitqmb k2{k1}, zmm19, [r12+r14*2-8256]
vpshufbitqmb k2{k1}, zmm19, [r12+r14*2+1]
end
