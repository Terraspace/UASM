; M06: 32-bit mode/addressing.
.686p
.xmm
.model flat
option evex:1
.code
vpcompressb [ebp]{k2}, xmm7
vpcompressb [ebp]{k2}, ymm7
vpcompressb [ebp]{k2}, zmm7
vpcompressw [ebp]{k2}, xmm7
vpcompressw [ebp]{k2}, ymm7
vpcompressw [ebp]{k2}, zmm7
vpexpandb xmm1{k3}{z}, [ebx+esi*4+128]
vpexpandb ymm1{k3}{z}, [ebx+esi*4+128]
vpexpandb zmm1{k3}{z}, [ebx+esi*4+128]
vpexpandw xmm1{k3}{z}, [ebx+esi*4+128]
vpexpandw ymm1{k3}{z}, [ebx+esi*4+128]
vpexpandw zmm1{k3}{z}, [ebx+esi*4+128]
vpshldd xmm1{k3}{z}, xmm2, [ebx+esi*4+128], 255
vpshldd ymm1{k3}{z}, ymm2, [ebx+esi*4+128], 255
vpshldd zmm1{k3}{z}, zmm2, [ebx+esi*4+128], 255
vpshldq xmm1{k3}{z}, xmm2, [ebx+esi*4+128], 255
vpshldq ymm1{k3}{z}, ymm2, [ebx+esi*4+128], 255
vpshldq zmm1{k3}{z}, zmm2, [ebx+esi*4+128], 255
vpshldw xmm1{k3}{z}, xmm2, [ebx+esi*4+128], 255
vpshldw ymm1{k3}{z}, ymm2, [ebx+esi*4+128], 255
vpshldw zmm1{k3}{z}, zmm2, [ebx+esi*4+128], 255
vpshrdd xmm1{k3}{z}, xmm2, [ebx+esi*4+128], 255
vpshrdd ymm1{k3}{z}, ymm2, [ebx+esi*4+128], 255
vpshrdd zmm1{k3}{z}, zmm2, [ebx+esi*4+128], 255
vpshrdq xmm1{k3}{z}, xmm2, [ebx+esi*4+128], 255
vpshrdq ymm1{k3}{z}, ymm2, [ebx+esi*4+128], 255
vpshrdq zmm1{k3}{z}, zmm2, [ebx+esi*4+128], 255
vpshrdw xmm1{k3}{z}, xmm2, [ebx+esi*4+128], 255
vpshrdw ymm1{k3}{z}, ymm2, [ebx+esi*4+128], 255
vpshrdw zmm1{k3}{z}, zmm2, [ebx+esi*4+128], 255
vpshldvd xmm1{k3}{z}, xmm2, [ebx+esi*4+128]
vpshldvd ymm1{k3}{z}, ymm2, [ebx+esi*4+128]
vpshldvd zmm1{k3}{z}, zmm2, [ebx+esi*4+128]
vpshldvq xmm1{k3}{z}, xmm2, [ebx+esi*4+128]
vpshldvq ymm1{k3}{z}, ymm2, [ebx+esi*4+128]
vpshldvq zmm1{k3}{z}, zmm2, [ebx+esi*4+128]
vpshldvw xmm1{k3}{z}, xmm2, [ebx+esi*4+128]
vpshldvw ymm1{k3}{z}, ymm2, [ebx+esi*4+128]
vpshldvw zmm1{k3}{z}, zmm2, [ebx+esi*4+128]
vpshrdvd xmm1{k3}{z}, xmm2, [ebx+esi*4+128]
vpshrdvd ymm1{k3}{z}, ymm2, [ebx+esi*4+128]
vpshrdvd zmm1{k3}{z}, zmm2, [ebx+esi*4+128]
vpshrdvq xmm1{k3}{z}, xmm2, [ebx+esi*4+128]
vpshrdvq ymm1{k3}{z}, ymm2, [ebx+esi*4+128]
vpshrdvq zmm1{k3}{z}, zmm2, [ebx+esi*4+128]
vpshrdvw xmm1{k3}{z}, xmm2, [ebx+esi*4+128]
vpshrdvw ymm1{k3}{z}, ymm2, [ebx+esi*4+128]
vpshrdvw zmm1{k3}{z}, zmm2, [ebx+esi*4+128]
end
