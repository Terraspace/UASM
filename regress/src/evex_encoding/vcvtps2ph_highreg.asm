; Legacy EVEX store regression: first instruction used to encode zmm22.
; Register-bank boundaries and address extension bits are independent.
.x64
option evex:1
_TEXT SEGMENT USE64
vcvtps2ph ymmword ptr [rcx],zmm30,0abh
vcvtps2ph ymmword ptr [rcx],zmm0,7bh
vcvtps2ph ymmword ptr [rcx],zmm7,7bh
vcvtps2ph ymmword ptr [rcx],zmm8,7bh
vcvtps2ph ymmword ptr [rcx],zmm15,7bh
vcvtps2ph ymmword ptr [rcx],zmm16,7bh
vcvtps2ph ymmword ptr [rcx],zmm23,7bh
vcvtps2ph ymmword ptr [rcx],zmm24,7bh
vcvtps2ph ymmword ptr [rcx],zmm31,7bh
vcvtps2ph ymmword ptr [rcx]{k7},zmm30,7bh
vcvtps2ph ymmword ptr [rax+r14*8+123h],zmm30,7bh
vcvtps2ph ymmword ptr [r13+r14*8+1000h]{k7},zmm31,7bh
_TEXT ENDS
END
