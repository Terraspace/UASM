; M06 VBMI2: LLVM-verified encoding, masks, tuple/displacement boundaries.
.x64
.model flat
option evex:1
.code
vpshldvd xmm1, xmm2, xmm3
vpshldvd xmm31{k7}{z}, xmm16, xmm30
vpshldvd xmm17{k3}{z}, xmm22, [r12+r14*2+0]
vpshldvd xmm17{k3}{z}, xmm22, [r12+r14*2+2032]
vpshldvd xmm17{k3}{z}, xmm22, [r12+r14*2+2048]
vpshldvd xmm17{k3}{z}, xmm22, [r12+r14*2-2048]
vpshldvd xmm17{k3}{z}, xmm22, [r12+r14*2-2064]
vpshldvd xmm17{k3}{z}, xmm22, [r12+r14*2+1]
vpshldvd xmm17{k1}, xmm30, dword ptr [r13+508]{1to4}
vpshldvd ymm1, ymm2, ymm3
vpshldvd ymm31{k7}{z}, ymm16, ymm30
vpshldvd ymm17{k3}{z}, ymm22, [r12+r14*2+0]
vpshldvd ymm17{k3}{z}, ymm22, [r12+r14*2+4064]
vpshldvd ymm17{k3}{z}, ymm22, [r12+r14*2+4096]
vpshldvd ymm17{k3}{z}, ymm22, [r12+r14*2-4096]
vpshldvd ymm17{k3}{z}, ymm22, [r12+r14*2-4128]
vpshldvd ymm17{k3}{z}, ymm22, [r12+r14*2+1]
vpshldvd ymm17{k1}, ymm30, dword ptr [r13+508]{1to8}
vpshldvd zmm1, zmm2, zmm3
vpshldvd zmm31{k7}{z}, zmm16, zmm30
vpshldvd zmm17{k3}{z}, zmm22, [r12+r14*2+0]
vpshldvd zmm17{k3}{z}, zmm22, [r12+r14*2+8128]
vpshldvd zmm17{k3}{z}, zmm22, [r12+r14*2+8192]
vpshldvd zmm17{k3}{z}, zmm22, [r12+r14*2-8192]
vpshldvd zmm17{k3}{z}, zmm22, [r12+r14*2-8256]
vpshldvd zmm17{k3}{z}, zmm22, [r12+r14*2+1]
vpshldvd zmm17{k1}, zmm30, dword ptr [r13+508]{1to16}
vpshldvq xmm1, xmm2, xmm3
vpshldvq xmm31{k7}{z}, xmm16, xmm30
vpshldvq xmm17{k3}{z}, xmm22, [r12+r14*2+0]
vpshldvq xmm17{k3}{z}, xmm22, [r12+r14*2+2032]
vpshldvq xmm17{k3}{z}, xmm22, [r12+r14*2+2048]
vpshldvq xmm17{k3}{z}, xmm22, [r12+r14*2-2048]
vpshldvq xmm17{k3}{z}, xmm22, [r12+r14*2-2064]
vpshldvq xmm17{k3}{z}, xmm22, [r12+r14*2+1]
vpshldvq xmm17{k1}, xmm30, qword ptr [r13+1016]{1to2}
vpshldvq ymm1, ymm2, ymm3
vpshldvq ymm31{k7}{z}, ymm16, ymm30
vpshldvq ymm17{k3}{z}, ymm22, [r12+r14*2+0]
vpshldvq ymm17{k3}{z}, ymm22, [r12+r14*2+4064]
vpshldvq ymm17{k3}{z}, ymm22, [r12+r14*2+4096]
vpshldvq ymm17{k3}{z}, ymm22, [r12+r14*2-4096]
vpshldvq ymm17{k3}{z}, ymm22, [r12+r14*2-4128]
vpshldvq ymm17{k3}{z}, ymm22, [r12+r14*2+1]
vpshldvq ymm17{k1}, ymm30, qword ptr [r13+1016]{1to4}
vpshldvq zmm1, zmm2, zmm3
vpshldvq zmm31{k7}{z}, zmm16, zmm30
vpshldvq zmm17{k3}{z}, zmm22, [r12+r14*2+0]
vpshldvq zmm17{k3}{z}, zmm22, [r12+r14*2+8128]
vpshldvq zmm17{k3}{z}, zmm22, [r12+r14*2+8192]
vpshldvq zmm17{k3}{z}, zmm22, [r12+r14*2-8192]
vpshldvq zmm17{k3}{z}, zmm22, [r12+r14*2-8256]
vpshldvq zmm17{k3}{z}, zmm22, [r12+r14*2+1]
vpshldvq zmm17{k1}, zmm30, qword ptr [r13+1016]{1to8}
vpshldvw xmm1, xmm2, xmm3
vpshldvw xmm31{k7}{z}, xmm16, xmm30
vpshldvw xmm17{k3}{z}, xmm22, [r12+r14*2+0]
vpshldvw xmm17{k3}{z}, xmm22, [r12+r14*2+2032]
vpshldvw xmm17{k3}{z}, xmm22, [r12+r14*2+2048]
vpshldvw xmm17{k3}{z}, xmm22, [r12+r14*2-2048]
vpshldvw xmm17{k3}{z}, xmm22, [r12+r14*2-2064]
vpshldvw xmm17{k3}{z}, xmm22, [r12+r14*2+1]
vpshldvw ymm1, ymm2, ymm3
vpshldvw ymm31{k7}{z}, ymm16, ymm30
vpshldvw ymm17{k3}{z}, ymm22, [r12+r14*2+0]
vpshldvw ymm17{k3}{z}, ymm22, [r12+r14*2+4064]
vpshldvw ymm17{k3}{z}, ymm22, [r12+r14*2+4096]
vpshldvw ymm17{k3}{z}, ymm22, [r12+r14*2-4096]
vpshldvw ymm17{k3}{z}, ymm22, [r12+r14*2-4128]
vpshldvw ymm17{k3}{z}, ymm22, [r12+r14*2+1]
vpshldvw zmm1, zmm2, zmm3
vpshldvw zmm31{k7}{z}, zmm16, zmm30
vpshldvw zmm17{k3}{z}, zmm22, [r12+r14*2+0]
vpshldvw zmm17{k3}{z}, zmm22, [r12+r14*2+8128]
vpshldvw zmm17{k3}{z}, zmm22, [r12+r14*2+8192]
vpshldvw zmm17{k3}{z}, zmm22, [r12+r14*2-8192]
vpshldvw zmm17{k3}{z}, zmm22, [r12+r14*2-8256]
vpshldvw zmm17{k3}{z}, zmm22, [r12+r14*2+1]
vpshrdvd xmm1, xmm2, xmm3
vpshrdvd xmm31{k7}{z}, xmm16, xmm30
vpshrdvd xmm17{k3}{z}, xmm22, [r12+r14*2+0]
vpshrdvd xmm17{k3}{z}, xmm22, [r12+r14*2+2032]
vpshrdvd xmm17{k3}{z}, xmm22, [r12+r14*2+2048]
vpshrdvd xmm17{k3}{z}, xmm22, [r12+r14*2-2048]
vpshrdvd xmm17{k3}{z}, xmm22, [r12+r14*2-2064]
vpshrdvd xmm17{k3}{z}, xmm22, [r12+r14*2+1]
vpshrdvd xmm17{k1}, xmm30, dword ptr [r13+508]{1to4}
vpshrdvd ymm1, ymm2, ymm3
vpshrdvd ymm31{k7}{z}, ymm16, ymm30
vpshrdvd ymm17{k3}{z}, ymm22, [r12+r14*2+0]
vpshrdvd ymm17{k3}{z}, ymm22, [r12+r14*2+4064]
vpshrdvd ymm17{k3}{z}, ymm22, [r12+r14*2+4096]
vpshrdvd ymm17{k3}{z}, ymm22, [r12+r14*2-4096]
vpshrdvd ymm17{k3}{z}, ymm22, [r12+r14*2-4128]
vpshrdvd ymm17{k3}{z}, ymm22, [r12+r14*2+1]
vpshrdvd ymm17{k1}, ymm30, dword ptr [r13+508]{1to8}
vpshrdvd zmm1, zmm2, zmm3
vpshrdvd zmm31{k7}{z}, zmm16, zmm30
vpshrdvd zmm17{k3}{z}, zmm22, [r12+r14*2+0]
vpshrdvd zmm17{k3}{z}, zmm22, [r12+r14*2+8128]
vpshrdvd zmm17{k3}{z}, zmm22, [r12+r14*2+8192]
vpshrdvd zmm17{k3}{z}, zmm22, [r12+r14*2-8192]
vpshrdvd zmm17{k3}{z}, zmm22, [r12+r14*2-8256]
vpshrdvd zmm17{k3}{z}, zmm22, [r12+r14*2+1]
vpshrdvd zmm17{k1}, zmm30, dword ptr [r13+508]{1to16}
vpshrdvq xmm1, xmm2, xmm3
vpshrdvq xmm31{k7}{z}, xmm16, xmm30
vpshrdvq xmm17{k3}{z}, xmm22, [r12+r14*2+0]
vpshrdvq xmm17{k3}{z}, xmm22, [r12+r14*2+2032]
vpshrdvq xmm17{k3}{z}, xmm22, [r12+r14*2+2048]
vpshrdvq xmm17{k3}{z}, xmm22, [r12+r14*2-2048]
vpshrdvq xmm17{k3}{z}, xmm22, [r12+r14*2-2064]
vpshrdvq xmm17{k3}{z}, xmm22, [r12+r14*2+1]
vpshrdvq xmm17{k1}, xmm30, qword ptr [r13+1016]{1to2}
vpshrdvq ymm1, ymm2, ymm3
vpshrdvq ymm31{k7}{z}, ymm16, ymm30
vpshrdvq ymm17{k3}{z}, ymm22, [r12+r14*2+0]
vpshrdvq ymm17{k3}{z}, ymm22, [r12+r14*2+4064]
vpshrdvq ymm17{k3}{z}, ymm22, [r12+r14*2+4096]
vpshrdvq ymm17{k3}{z}, ymm22, [r12+r14*2-4096]
vpshrdvq ymm17{k3}{z}, ymm22, [r12+r14*2-4128]
vpshrdvq ymm17{k3}{z}, ymm22, [r12+r14*2+1]
vpshrdvq ymm17{k1}, ymm30, qword ptr [r13+1016]{1to4}
vpshrdvq zmm1, zmm2, zmm3
vpshrdvq zmm31{k7}{z}, zmm16, zmm30
vpshrdvq zmm17{k3}{z}, zmm22, [r12+r14*2+0]
vpshrdvq zmm17{k3}{z}, zmm22, [r12+r14*2+8128]
vpshrdvq zmm17{k3}{z}, zmm22, [r12+r14*2+8192]
vpshrdvq zmm17{k3}{z}, zmm22, [r12+r14*2-8192]
vpshrdvq zmm17{k3}{z}, zmm22, [r12+r14*2-8256]
vpshrdvq zmm17{k3}{z}, zmm22, [r12+r14*2+1]
vpshrdvq zmm17{k1}, zmm30, qword ptr [r13+1016]{1to8}
vpshrdvw xmm1, xmm2, xmm3
vpshrdvw xmm31{k7}{z}, xmm16, xmm30
vpshrdvw xmm17{k3}{z}, xmm22, [r12+r14*2+0]
vpshrdvw xmm17{k3}{z}, xmm22, [r12+r14*2+2032]
vpshrdvw xmm17{k3}{z}, xmm22, [r12+r14*2+2048]
vpshrdvw xmm17{k3}{z}, xmm22, [r12+r14*2-2048]
vpshrdvw xmm17{k3}{z}, xmm22, [r12+r14*2-2064]
vpshrdvw xmm17{k3}{z}, xmm22, [r12+r14*2+1]
vpshrdvw ymm1, ymm2, ymm3
vpshrdvw ymm31{k7}{z}, ymm16, ymm30
vpshrdvw ymm17{k3}{z}, ymm22, [r12+r14*2+0]
vpshrdvw ymm17{k3}{z}, ymm22, [r12+r14*2+4064]
vpshrdvw ymm17{k3}{z}, ymm22, [r12+r14*2+4096]
vpshrdvw ymm17{k3}{z}, ymm22, [r12+r14*2-4096]
vpshrdvw ymm17{k3}{z}, ymm22, [r12+r14*2-4128]
vpshrdvw ymm17{k3}{z}, ymm22, [r12+r14*2+1]
vpshrdvw zmm1, zmm2, zmm3
vpshrdvw zmm31{k7}{z}, zmm16, zmm30
vpshrdvw zmm17{k3}{z}, zmm22, [r12+r14*2+0]
vpshrdvw zmm17{k3}{z}, zmm22, [r12+r14*2+8128]
vpshrdvw zmm17{k3}{z}, zmm22, [r12+r14*2+8192]
vpshrdvw zmm17{k3}{z}, zmm22, [r12+r14*2-8192]
vpshrdvw zmm17{k3}{z}, zmm22, [r12+r14*2-8256]
vpshrdvw zmm17{k3}{z}, zmm22, [r12+r14*2+1]
end
