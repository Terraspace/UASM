
    .x64
    .model flat
    option evex:1
    .code

    vmovupd [rsi-88]{k7}, zmm0
    ; assembles as: vmovupd zmmword ptr [rsi-58H*40H] {k7}, zmm0 ; 00A4 _ 62 F1 FD 4F: 11. 46, A8
    ; Reported by Gwoltman 5th December 2017

    vmovapd [rsi-88]{k7}, zmm0
    vmovupd [rsi-88]{k7}, zmm0
    vmovups [rsi-88]{k7}, zmm0
    vmovaps [rsi-88]{k7}, zmm0

    vmovapd [rsi]{k7}, zmm0
    vmovupd [rsi]{k7}, zmm0
    vmovups [rsi]{k7}, zmm0
    vmovaps [rsi]{k7}, zmm0

    vmovapd zmm2{k7}, zmm0
    vmovupd zmm2{k7}, zmm0
    vmovups zmm2{k7}, zmm0
    vmovaps zmm2{k7}, zmm0

    vmovapd zmm10,zmm17
    ;assembles as vmovapd zmm10, zmm1 ; 0000 _ 62 71 FD 48: 28. D1
    ; Reported by Gwoltman, 13th December 2017

    end