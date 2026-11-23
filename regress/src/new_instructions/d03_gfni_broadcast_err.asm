.x64
.model flat
option evex:1
.code
; GFNI byte multiplication has no broadcast form.
vgf2p8mulb xmm1{k1}, xmm2, qword ptr [rax]{1to2}
vgf2p8mulb ymm1{k1}, ymm2, qword ptr [rax]{1to4}
vgf2p8mulb zmm1{k1}, zmm2, qword ptr [rax]{1to8}
end
