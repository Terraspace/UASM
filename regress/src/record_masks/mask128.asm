; UASM XMM MASK extension: full, crossing, upper/lower and reused masks.
.x64
.model flat
option casemap:none
R128 RECORD upper:60, crossing:8, lower:60
.code
entry PROC
    vmovups xmm1, MASK R128
    movups xmm2, MASK crossing
    vmovups xmm15, MASK upper
    por xmm2, MASK lower
    vmovups xmm3, MASK crossing
    ret
entry ENDP
END
