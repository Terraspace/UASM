; M02: expected bytes checked against LLVM; masks/high registers/displacement boundaries.
.x64
.model flat
option evex:1
.code
vpopcntb xmm1, xmm2
vpopcntb xmm17{k3}, xmm30
vpopcntb xmm31{k7}{z}, [r13]
vpopcntb xmm18{k2}{z}, [r12+r14*2+2032]
vpopcntb xmm18{k2}{z}, [r12+r14*2+2048]
vpopcntb xmm18{k2}{z}, [r12+r14*2-2048]
vpopcntb xmm18{k2}{z}, [r12+r14*2-2064]
vpopcntb xmm18{k2}{z}, [r12+r14*2+1]
vpopcntb ymm1, ymm2
vpopcntb ymm17{k3}, ymm30
vpopcntb ymm31{k7}{z}, [r13]
vpopcntb ymm18{k2}{z}, [r12+r14*2+4064]
vpopcntb ymm18{k2}{z}, [r12+r14*2+4096]
vpopcntb ymm18{k2}{z}, [r12+r14*2-4096]
vpopcntb ymm18{k2}{z}, [r12+r14*2-4128]
vpopcntb ymm18{k2}{z}, [r12+r14*2+1]
vpopcntb zmm1, zmm2
vpopcntb zmm17{k3}, zmm30
vpopcntb zmm31{k7}{z}, [r13]
vpopcntb zmm18{k2}{z}, [r12+r14*2+8128]
vpopcntb zmm18{k2}{z}, [r12+r14*2+8192]
vpopcntb zmm18{k2}{z}, [r12+r14*2-8192]
vpopcntb zmm18{k2}{z}, [r12+r14*2-8256]
vpopcntb zmm18{k2}{z}, [r12+r14*2+1]
vpopcntw xmm1, xmm2
vpopcntw xmm17{k3}, xmm30
vpopcntw xmm31{k7}{z}, [r13]
vpopcntw xmm18{k2}{z}, [r12+r14*2+2032]
vpopcntw xmm18{k2}{z}, [r12+r14*2+2048]
vpopcntw xmm18{k2}{z}, [r12+r14*2-2048]
vpopcntw xmm18{k2}{z}, [r12+r14*2-2064]
vpopcntw xmm18{k2}{z}, [r12+r14*2+1]
vpopcntw ymm1, ymm2
vpopcntw ymm17{k3}, ymm30
vpopcntw ymm31{k7}{z}, [r13]
vpopcntw ymm18{k2}{z}, [r12+r14*2+4064]
vpopcntw ymm18{k2}{z}, [r12+r14*2+4096]
vpopcntw ymm18{k2}{z}, [r12+r14*2-4096]
vpopcntw ymm18{k2}{z}, [r12+r14*2-4128]
vpopcntw ymm18{k2}{z}, [r12+r14*2+1]
vpopcntw zmm1, zmm2
vpopcntw zmm17{k3}, zmm30
vpopcntw zmm31{k7}{z}, [r13]
vpopcntw zmm18{k2}{z}, [r12+r14*2+8128]
vpopcntw zmm18{k2}{z}, [r12+r14*2+8192]
vpopcntw zmm18{k2}{z}, [r12+r14*2-8192]
vpopcntw zmm18{k2}{z}, [r12+r14*2-8256]
vpopcntw zmm18{k2}{z}, [r12+r14*2+1]
end
