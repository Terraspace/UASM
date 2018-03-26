
    .x64
    .model flat
    option evex:1
    .code

	vmovupd zmm0, [rsi+0*64-8]
	vmovupd zmm0{k1}, [rsi+0*64-8]
	vmovupd [rsi+0*64-8], zmm0
	vmovupd [rsi+0*64-8] {k1}, zmm0
	;assembles as; reported by gwoltmann 10th feb 2018

	;vmovupd zmm0, zmmword ptr [rsi-8H*40H] ; 0000 _ 62 F1 FD 48: 10. 46, F8
	;vmovupd zmm0 {k1}, zmmword ptr [rsi-8H] ; 0007 _ 62 F1 FD 49: 10. 86, FFFFFFF8
	;vmovupd zmmword ptr [rsi-8H*40H], zmm0 ; 0011 _ 62 F1 FD 48: 11. 46, F8
	;vmovupd zmmword ptr [rsi-8H] {k1}, zmm0 ; 0018 _ 62 F1 FD 49: 11. 86, FFFFFFF8


    end