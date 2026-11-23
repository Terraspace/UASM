; M06: invalid widths, broadcasts, memory zeroing and immediates.
.x64
.model flat
option evex:1
.code
vpcompressb xmm1, ymm2
vpcompressb [rax]{k1}{z}, zmm2
vpcompressb xmm1, dword ptr [rax]{1to4}
vpcompressw xmm1, ymm2
vpcompressw [rax]{k1}{z}, zmm2
vpcompressw xmm1, dword ptr [rax]{1to4}
vpexpandb xmm1, ymm2
vpexpandb xmm1, dword ptr [rax]{1to4}
vpexpandw xmm1, ymm2
vpexpandw xmm1, dword ptr [rax]{1to4}
vpshldd xmm1, ymm2, xmm3, 255
vpshldd zmm1, zmm2, zmm3, 256
vpshldq xmm1, ymm2, xmm3, 255
vpshldq zmm1, zmm2, zmm3, 256
vpshldw xmm1, ymm2, xmm3, 255
vpshldw xmm1, xmm2, dword ptr [rax]{1to4}, 255
vpshldw zmm1, zmm2, zmm3, 256
vpshrdd xmm1, ymm2, xmm3, 255
vpshrdd zmm1, zmm2, zmm3, 256
vpshrdq xmm1, ymm2, xmm3, 255
vpshrdq zmm1, zmm2, zmm3, 256
vpshrdw xmm1, ymm2, xmm3, 255
vpshrdw xmm1, xmm2, dword ptr [rax]{1to4}, 255
vpshrdw zmm1, zmm2, zmm3, 256
vpshldvd xmm1, ymm2, xmm3
vpshldvq xmm1, ymm2, xmm3
vpshldvw xmm1, ymm2, xmm3
vpshldvw xmm1, xmm2, dword ptr [rax]{1to4}
vpshrdvd xmm1, ymm2, xmm3
vpshrdvq xmm1, ymm2, xmm3
vpshrdvw xmm1, ymm2, xmm3
vpshrdvw xmm1, xmm2, dword ptr [rax]{1to4}
end
