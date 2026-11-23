; M02: expected bytes checked against LLVM; masks/high registers/displacement boundaries.
.x64
.model flat
option evex:1
.code
vpopcntd xmm1, xmm2
vpopcntd xmm17{k3}, xmm30
vpopcntd xmm31{k7}{z}, [r13]
vpopcntd xmm18{k2}{z}, [r12+r14*2+2032]
vpopcntd xmm18{k2}{z}, [r12+r14*2+2048]
vpopcntd xmm18{k2}{z}, [r12+r14*2-2048]
vpopcntd xmm18{k2}{z}, [r12+r14*2-2064]
vpopcntd xmm18{k2}{z}, [r12+r14*2+1]
vpopcntd xmm17{k3}{z}, dword ptr [r13+508]{1to4}
vpopcntd ymm1, ymm2
vpopcntd ymm17{k3}, ymm30
vpopcntd ymm31{k7}{z}, [r13]
vpopcntd ymm18{k2}{z}, [r12+r14*2+4064]
vpopcntd ymm18{k2}{z}, [r12+r14*2+4096]
vpopcntd ymm18{k2}{z}, [r12+r14*2-4096]
vpopcntd ymm18{k2}{z}, [r12+r14*2-4128]
vpopcntd ymm18{k2}{z}, [r12+r14*2+1]
vpopcntd ymm17{k3}{z}, dword ptr [r13+508]{1to8}
vpopcntd zmm1, zmm2
vpopcntd zmm17{k3}, zmm30
vpopcntd zmm31{k7}{z}, [r13]
vpopcntd zmm18{k2}{z}, [r12+r14*2+8128]
vpopcntd zmm18{k2}{z}, [r12+r14*2+8192]
vpopcntd zmm18{k2}{z}, [r12+r14*2-8192]
vpopcntd zmm18{k2}{z}, [r12+r14*2-8256]
vpopcntd zmm18{k2}{z}, [r12+r14*2+1]
vpopcntd zmm17{k3}{z}, dword ptr [r13+508]{1to16}
vpopcntq xmm1, xmm2
vpopcntq xmm17{k3}, xmm30
vpopcntq xmm31{k7}{z}, [r13]
vpopcntq xmm18{k2}{z}, [r12+r14*2+2032]
vpopcntq xmm18{k2}{z}, [r12+r14*2+2048]
vpopcntq xmm18{k2}{z}, [r12+r14*2-2048]
vpopcntq xmm18{k2}{z}, [r12+r14*2-2064]
vpopcntq xmm18{k2}{z}, [r12+r14*2+1]
vpopcntq xmm17{k3}{z}, qword ptr [r13+1016]{1to2}
vpopcntq ymm1, ymm2
vpopcntq ymm17{k3}, ymm30
vpopcntq ymm31{k7}{z}, [r13]
vpopcntq ymm18{k2}{z}, [r12+r14*2+4064]
vpopcntq ymm18{k2}{z}, [r12+r14*2+4096]
vpopcntq ymm18{k2}{z}, [r12+r14*2-4096]
vpopcntq ymm18{k2}{z}, [r12+r14*2-4128]
vpopcntq ymm18{k2}{z}, [r12+r14*2+1]
vpopcntq ymm17{k3}{z}, qword ptr [r13+1016]{1to4}
vpopcntq zmm1, zmm2
vpopcntq zmm17{k3}, zmm30
vpopcntq zmm31{k7}{z}, [r13]
vpopcntq zmm18{k2}{z}, [r12+r14*2+8128]
vpopcntq zmm18{k2}{z}, [r12+r14*2+8192]
vpopcntq zmm18{k2}{z}, [r12+r14*2-8192]
vpopcntq zmm18{k2}{z}, [r12+r14*2-8256]
vpopcntq zmm18{k2}{z}, [r12+r14*2+1]
vpopcntq zmm17{k3}{z}, qword ptr [r13+1016]{1to8}
end
