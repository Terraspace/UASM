;
; F16C
;
    .x64
    .model flat
    .code

    vcvtph2ps xmm0,xmm1
    vcvtph2ps xmm7,xmm11
    vcvtph2ps xmm0,[rax]
    vcvtph2ps xmm0,qword ptr [rsi+rax*8+1024]

    vcvtph2ps ymm0,xmm1
    vcvtph2ps ymm7,xmm11
    vcvtph2ps ymm0,[rax]
    vcvtph2ps ymm0,oword ptr [rsi+rax*8+1024]

    vcvtps2ph xmm0,xmm1,0
    vcvtps2ph [rax],xmm1,0
    vcvtps2ph qword ptr [rsi+rax*8+1024],xmm7,0

    vcvtps2ph xmm0,ymm1,0
    vcvtps2ph [rax],ymm1,0
    vcvtps2ph oword ptr [rsi+rax*8+1024],ymm3,0

    end
