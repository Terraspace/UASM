;
; AVX-2
;
    .x64
    .model flat
    .code

    vpmaskmovd xmm6,xmm4,OWORD PTR [rcx]
    vpmaskmovd OWORD PTR [rcx],xmm6,xmm4
    vpmaskmovq xmm6,xmm4,OWORD PTR [rcx]
    vpmaskmovq OWORD PTR [rcx],xmm6,xmm4

    vpsrlvq xmm2,xmm6,xmm4
    vpsrlvq xmm2,xmm6,OWORD PTR [rcx]

    vpmaskmovd ymm6,ymm4,YMMWORD PTR [rcx]
    vpmaskmovd YMMWORD PTR [rcx],ymm6,ymm4
    vpmaskmovq ymm6,ymm4,YMMWORD PTR [rcx]
    vpmaskmovq YMMWORD PTR [rcx],ymm6,ymm4

    vpermpd ymm2,ymm6,0x7
    vpermpd ymm6,YMMWORD PTR [rcx],0x7
    vpermq  ymm2,ymm6,0x7
    vpermq  ymm6,YMMWORD PTR [rcx],0x7
    vpermd  ymm2,ymm6,ymm4
    vpermd  ymm2,ymm6,YMMWORD PTR [rcx]
    vpermps ymm2,ymm6,ymm4
    vpermps ymm2,ymm6,YMMWORD PTR [rcx]
    vpsllvd ymm2,ymm6,ymm4
    vpsllvd ymm2,ymm6,YMMWORD PTR [rcx]
    vpsllvq ymm2,ymm6,ymm4
    vpsllvq ymm2,ymm6,YMMWORD PTR [rcx]
    vpsravd ymm2,ymm6,ymm4
    vpsravd ymm2,ymm6,YMMWORD PTR [rcx]
    vpsrlvd ymm2,ymm6,ymm4
    vpsrlvd ymm2,ymm6,YMMWORD PTR [rcx]
    vpsrlvq ymm2,ymm6,ymm4
    vpsrlvq ymm2,ymm6,YMMWORD PTR [rcx]

;
; AVX2 testcases written for gas
;
; http://sourceware.org/ml/binutils/2011-06/msg00150.html
;
; b/gas/testsuite/gas/i386/avx2-intel.d

    vpmaskmovd ymm6,ymm4,ymmword ptr [rcx]
    vpmaskmovd ymmword ptr [rcx],ymm6,ymm4
    vpmaskmovq ymm6,ymm4,ymmword ptr [rcx]
    vpmaskmovq ymmword ptr [rcx],ymm6,ymm4
    vpermpd ymm2,ymm6,0x7
    vpermpd ymm6,ymmword ptr [rcx],0x7
    vpermq ymm2,ymm6,0x7
    vpermq ymm6,ymmword ptr [rcx],0x7
    vpermd ymm2,ymm6,ymm4
    vpermd ymm2,ymm6,ymmword ptr [rcx]
    vpermps ymm2,ymm6,ymm4
    vpermps ymm2,ymm6,ymmword ptr [rcx]
    vpsllvd ymm2,ymm6,ymm4
    vpsllvd ymm2,ymm6,ymmword ptr [rcx]
    vpsllvq ymm2,ymm6,ymm4
    vpsllvq ymm2,ymm6,ymmword ptr [rcx]
    vpsravd ymm2,ymm6,ymm4
    vpsravd ymm2,ymm6,ymmword ptr [rcx]
    vpsrlvd ymm2,ymm6,ymm4
    vpsrlvd ymm2,ymm6,ymmword ptr [rcx]
    vpsrlvq ymm2,ymm6,ymm4
    vpsrlvq ymm2,ymm6,ymmword ptr [rcx]
    vmovntdqa ymm4,ymmword ptr [rcx]
    vbroadcastsd ymm6,xmm4
    vbroadcastss ymm6,xmm4
    vpblendd ymm2,ymm6,ymm4,0x7
    vpblendd ymm2,ymm6,ymmword ptr [rcx],0x7
    vperm2i128 ymm2,ymm6,ymm4,0x7
    vperm2i128 ymm2,ymm6,ymmword ptr [rcx],0x7
    vinserti128 ymm6,ymm4,xmm4,0x7
    vinserti128 ymm6,ymm4,oword ptr [rcx],0x7
    vbroadcasti128 ymm4,oword ptr [rcx]
    vpsllvd xmm2,xmm6,xmm4
    vpsllvd xmm7,xmm6,oword ptr [rcx]
    vpsllvq xmm2,xmm6,xmm4
    vpsllvq xmm7,xmm6,oword ptr [rcx]
    vpsravd xmm2,xmm6,xmm4
    vpsravd xmm7,xmm6,oword ptr [rcx]
    vpsrlvd xmm2,xmm6,xmm4
    vpsrlvd xmm7,xmm6,oword ptr [rcx]
    vpsrlvq xmm2,xmm6,xmm4
    vpsrlvq xmm7,xmm6,oword ptr [rcx]
    vpmaskmovd xmm6,xmm4,oword ptr [rcx]
    vpmaskmovq xmm6,xmm4,oword ptr [rcx]
    vextracti128 xmm6,ymm4,0x7
    vextracti128 oword ptr [rcx],ymm4,0x7
    vpmaskmovd oword ptr [rcx],xmm6,xmm4
    vpmaskmovq oword ptr [rcx],xmm6,xmm4
    vpblendd xmm2,xmm6,xmm4,0x7
    vpblendd xmm2,xmm6,oword ptr [rcx],0x7
    vpbroadcastq xmm6,xmm4
    vpbroadcastq xmm4,qword ptr [rcx]
    vpbroadcastq ymm6,xmm4
    vpbroadcastq ymm4,qword ptr [rcx]
    vpbroadcastd ymm4,xmm4
    vpbroadcastd ymm4,dword ptr [rcx]
    vpbroadcastd xmm6,xmm4
    vpbroadcastd xmm4,dword ptr [rcx]
    vpbroadcastw xmm6,xmm4
    vpbroadcastw xmm4,word ptr [rcx]
    vpbroadcastw ymm6,xmm4
    vpbroadcastw ymm4,word ptr [rcx]
    vpbroadcastb xmm6,xmm4
    vpbroadcastb xmm4,byte ptr [rcx]
    vpbroadcastb ymm6,xmm4
    vpbroadcastb ymm4,byte ptr [rcx]
    vbroadcastss xmm6,xmm4
    vpmaskmovd ymm6,ymm4,ymmword ptr [rcx]
    vpmaskmovd ymmword ptr [rcx],ymm6,ymm4
    vpmaskmovd ymm6,ymm4,ymmword ptr [rcx]
    vpmaskmovd ymmword ptr [rcx],ymm6,ymm4
    vpmaskmovq ymm6,ymm4,ymmword ptr [rcx]
    vpmaskmovq ymmword ptr [rcx],ymm6,ymm4
    vpmaskmovq ymm6,ymm4,ymmword ptr [rcx]
    vpmaskmovq ymmword ptr [rcx],ymm6,ymm4
    vpermpd ymm2,ymm6,0x7
    vpermpd ymm6,ymmword ptr [rcx],0x7
    vpermpd ymm6,ymmword ptr [rcx],0x7
    vpermq ymm2,ymm6,0x7
    vpermq ymm6,ymmword ptr [rcx],0x7
    vpermq ymm6,ymmword ptr [rcx],0x7
    vpermd ymm2,ymm6,ymm4
    vpermd ymm2,ymm6,ymmword ptr [rcx]
    vpermd ymm2,ymm6,ymmword ptr [rcx]
    vpermps ymm2,ymm6,ymm4
    vpermps ymm2,ymm6,ymmword ptr [rcx]
    vpermps ymm2,ymm6,ymmword ptr [rcx]
    vpsllvd ymm2,ymm6,ymm4
    vpsllvd ymm2,ymm6,ymmword ptr [rcx]
    vpsllvd ymm2,ymm6,ymmword ptr [rcx]
    vpsllvq ymm2,ymm6,ymm4
    vpsllvq ymm2,ymm6,ymmword ptr [rcx]
    vpsllvq ymm2,ymm6,ymmword ptr [rcx]
    vpsravd ymm2,ymm6,ymm4
    vpsravd ymm2,ymm6,ymmword ptr [rcx]
    vpsravd ymm2,ymm6,ymmword ptr [rcx]
    vpsrlvd ymm2,ymm6,ymm4
    vpsrlvd ymm2,ymm6,ymmword ptr [rcx]
    vpsrlvd ymm2,ymm6,ymmword ptr [rcx]
    vpsrlvq ymm2,ymm6,ymm4
    vpsrlvq ymm2,ymm6,ymmword ptr [rcx]
    vpsrlvq ymm2,ymm6,ymmword ptr [rcx]
    vmovntdqa ymm4,ymmword ptr [rcx]
    vmovntdqa ymm4,ymmword ptr [rcx]
    vbroadcastsd ymm6,xmm4
    vbroadcastss ymm6,xmm4
    vpblendd ymm2,ymm6,ymm4,0x7
    vpblendd ymm2,ymm6,ymmword ptr [rcx],0x7
    vpblendd ymm2,ymm6,ymmword ptr [rcx],0x7
    vperm2i128 ymm2,ymm6,ymm4,0x7
    vperm2i128 ymm2,ymm6,ymmword ptr [rcx],0x7
    vperm2i128 ymm2,ymm6,ymmword ptr [rcx],0x7
    vinserti128 ymm6,ymm4,xmm4,0x7
    vinserti128 ymm6,ymm4,oword ptr [rcx],0x7
    vinserti128 ymm6,ymm4,oword ptr [rcx],0x7
    vbroadcasti128 ymm4,oword ptr [rcx]
    vbroadcasti128 ymm4,oword ptr [rcx]
    vpsllvd xmm2,xmm6,xmm4
    vpsllvd xmm7,xmm6,oword ptr [rcx]
    vpsllvd xmm7,xmm6,oword ptr [rcx]
    vpsllvq xmm2,xmm6,xmm4
    vpsllvq xmm7,xmm6,oword ptr [rcx]
    vpsllvq xmm7,xmm6,oword ptr [rcx]
    vpsravd xmm2,xmm6,xmm4
    vpsravd xmm7,xmm6,oword ptr [rcx]
    vpsravd xmm7,xmm6,oword ptr [rcx]
    vpsrlvd xmm2,xmm6,xmm4
    vpsrlvd xmm7,xmm6,oword ptr [rcx]
    vpsrlvd xmm7,xmm6,oword ptr [rcx]
    vpsrlvq xmm2,xmm6,xmm4
    vpsrlvq xmm7,xmm6,oword ptr [rcx]
    vpsrlvq xmm7,xmm6,oword ptr [rcx]
    vpmaskmovd xmm6,xmm4,oword ptr [rcx]
    vpmaskmovd xmm6,xmm4,oword ptr [rcx]
    vpmaskmovq xmm6,xmm4,oword ptr [rcx]
    vpmaskmovq xmm6,xmm4,oword ptr [rcx]
    vextracti128 xmm6,ymm4,0x7
    vextracti128 oword ptr [rcx],ymm4,0x7
    vextracti128 oword ptr [rcx],ymm4,0x7
    vpmaskmovd oword ptr [rcx],xmm6,xmm4
    vpmaskmovd oword ptr [rcx],xmm6,xmm4
    vpmaskmovq oword ptr [rcx],xmm6,xmm4
    vpmaskmovq oword ptr [rcx],xmm6,xmm4
    vpblendd xmm2,xmm6,xmm4,0x7
    vpblendd xmm2,xmm6,oword ptr [rcx],0x7
    vpblendd xmm2,xmm6,oword ptr [rcx],0x7
    vpbroadcastq xmm6,xmm4
    vpbroadcastq xmm4,qword ptr [rcx]
    vpbroadcastq xmm4,qword ptr [rcx]
    vpbroadcastq ymm6,xmm4
    vpbroadcastq ymm4,qword ptr [rcx]
    vpbroadcastq ymm4,qword ptr [rcx]
    vpbroadcastd ymm4,xmm4
    vpbroadcastd ymm4,dword ptr [rcx]
    vpbroadcastd ymm4,dword ptr [rcx]
    vpbroadcastd xmm6,xmm4
    vpbroadcastd xmm4,dword ptr [rcx]
    vpbroadcastd xmm4,dword ptr [rcx]
    vpbroadcastw xmm6,xmm4
    vpbroadcastw xmm4,word ptr [rcx]
    vpbroadcastw xmm4,word ptr [rcx]
    vpbroadcastw ymm6,xmm4
    vpbroadcastw ymm4,word ptr [rcx]
    vpbroadcastw ymm4,word ptr [rcx]
    vpbroadcastb xmm6,xmm4
    vpbroadcastb xmm4,byte ptr [rcx]
    vpbroadcastb xmm4,byte ptr [rcx]
    vpbroadcastb ymm6,xmm4
    vpbroadcastb ymm4,byte ptr [rcx]
    vpbroadcastb ymm4,byte ptr [rcx]
    vbroadcastss xmm6,xmm4

; b/gas/testsuite/gas/i386/avx256int-intel.d

    vpmovmskb ecx,ymm4
    vpmovmskb ecx,ymm4
    vpslld ymm2,ymm6,0x7
    vpslldq ymm2,ymm6,0x7
    vpsllq ymm2,ymm6,0x7
    vpsllw ymm2,ymm6,0x7
    vpsrad ymm2,ymm6,0x7
    vpsraw ymm2,ymm6,0x7
    vpsrld ymm2,ymm6,0x7
    vpsrldq ymm2,ymm6,0x7
    vpsrlq ymm2,ymm6,0x7
    vpsrlw ymm2,ymm6,0x7
    vpshufd ymm2,ymm6,0x7
    vpshufd ymm6,ymmword ptr [rcx],0x7
    vpshufhw ymm2,ymm6,0x7
    vpshufhw ymm6,ymmword ptr [rcx],0x7
    vpshuflw ymm2,ymm6,0x7
    vpshuflw ymm6,ymmword ptr [rcx],0x7
    vpackssdw ymm2,ymm6,ymm4
    vpackssdw ymm2,ymm6,ymmword ptr [rcx]
    vpacksswb ymm2,ymm6,ymm4
    vpacksswb ymm2,ymm6,ymmword ptr [rcx]
    vpackusdw ymm2,ymm6,ymm4
    vpackusdw ymm2,ymm6,ymmword ptr [rcx]
    vpackuswb ymm2,ymm6,ymm4
    vpackuswb ymm2,ymm6,ymmword ptr [rcx]
    vpaddb ymm2,ymm6,ymm4
    vpaddb ymm2,ymm6,ymmword ptr [rcx]
    vpaddw ymm2,ymm6,ymm4
    vpaddw ymm2,ymm6,ymmword ptr [rcx]
    vpaddd ymm2,ymm6,ymm4
    vpaddd ymm2,ymm6,ymmword ptr [rcx]
    vpaddq ymm2,ymm6,ymm4
    vpaddq ymm2,ymm6,ymmword ptr [rcx]
    vpaddsb ymm2,ymm6,ymm4
    vpaddsb ymm2,ymm6,ymmword ptr [rcx]
    vpaddsw ymm2,ymm6,ymm4
    vpaddsw ymm2,ymm6,ymmword ptr [rcx]
    vpaddusb ymm2,ymm6,ymm4
    vpaddusb ymm2,ymm6,ymmword ptr [rcx]
    vpaddusw ymm2,ymm6,ymm4
    vpaddusw ymm2,ymm6,ymmword ptr [rcx]
    vpand ymm2,ymm6,ymm4
    vpand ymm2,ymm6,ymmword ptr [rcx]
    vpandn ymm2,ymm6,ymm4
    vpandn ymm2,ymm6,ymmword ptr [rcx]
    vpavgb ymm2,ymm6,ymm4
    vpavgb ymm2,ymm6,ymmword ptr [rcx]
    vpavgw ymm2,ymm6,ymm4
    vpavgw ymm2,ymm6,ymmword ptr [rcx]
    vpcmpeqb ymm2,ymm6,ymm4
    vpcmpeqb ymm2,ymm6,ymmword ptr [rcx]
    vpcmpeqw ymm2,ymm6,ymm4
    vpcmpeqw ymm2,ymm6,ymmword ptr [rcx]
    vpcmpeqd ymm2,ymm6,ymm4
    vpcmpeqd ymm2,ymm6,ymmword ptr [rcx]
    vpcmpeqq ymm2,ymm6,ymm4
    vpcmpeqq ymm2,ymm6,ymmword ptr [rcx]
    vpcmpgtb ymm2,ymm6,ymm4
    vpcmpgtb ymm2,ymm6,ymmword ptr [rcx]
    vpcmpgtw ymm2,ymm6,ymm4
    vpcmpgtw ymm2,ymm6,ymmword ptr [rcx]
    vpcmpgtd ymm2,ymm6,ymm4
    vpcmpgtd ymm2,ymm6,ymmword ptr [rcx]
    vpcmpgtq ymm2,ymm6,ymm4
    vpcmpgtq ymm2,ymm6,ymmword ptr [rcx]
    vphaddw ymm2,ymm6,ymm4
    vphaddw ymm2,ymm6,ymmword ptr [rcx]
    vphaddd ymm2,ymm6,ymm4
    vphaddd ymm2,ymm6,ymmword ptr [rcx]
    vphaddsw ymm2,ymm6,ymm4
    vphaddsw ymm2,ymm6,ymmword ptr [rcx]
    vphsubw ymm2,ymm6,ymm4
    vphsubw ymm2,ymm6,ymmword ptr [rcx]
    vphsubd ymm2,ymm6,ymm4
    vphsubd ymm2,ymm6,ymmword ptr [rcx]
    vphsubsw ymm2,ymm6,ymm4
    vphsubsw ymm2,ymm6,ymmword ptr [rcx]
    vpmaddwd ymm2,ymm6,ymm4
    vpmaddwd ymm2,ymm6,ymmword ptr [rcx]
    vpmaddubsw ymm2,ymm6,ymm4
    vpmaddubsw ymm2,ymm6,ymmword ptr [rcx]
    vpmaxsb ymm2,ymm6,ymm4
    vpmaxsb ymm2,ymm6,ymmword ptr [rcx]
    vpmaxsw ymm2,ymm6,ymm4
    vpmaxsw ymm2,ymm6,ymmword ptr [rcx]
    vpmaxsd ymm2,ymm6,ymm4
    vpmaxsd ymm2,ymm6,ymmword ptr [rcx]
    vpmaxub ymm2,ymm6,ymm4
    vpmaxub ymm2,ymm6,ymmword ptr [rcx]
    vpmaxuw ymm2,ymm6,ymm4
    vpmaxuw ymm2,ymm6,ymmword ptr [rcx]
    vpmaxud ymm2,ymm6,ymm4
    vpmaxud ymm2,ymm6,ymmword ptr [rcx]
    vpminsb ymm2,ymm6,ymm4
    vpminsb ymm2,ymm6,ymmword ptr [rcx]
    vpminsw ymm2,ymm6,ymm4
    vpminsw ymm2,ymm6,ymmword ptr [rcx]
    vpminsd ymm2,ymm6,ymm4
    vpminsd ymm2,ymm6,ymmword ptr [rcx]
    vpminub ymm2,ymm6,ymm4
    vpminub ymm2,ymm6,ymmword ptr [rcx]
    vpminuw ymm2,ymm6,ymm4
    vpminuw ymm2,ymm6,ymmword ptr [rcx]
    vpminud ymm2,ymm6,ymm4
    vpminud ymm2,ymm6,ymmword ptr [rcx]
    vpmulhuw ymm2,ymm6,ymm4
    vpmulhuw ymm2,ymm6,ymmword ptr [rcx]
    vpmulhrsw ymm2,ymm6,ymm4
    vpmulhrsw ymm2,ymm6,ymmword ptr [rcx]
    vpmulhw ymm2,ymm6,ymm4
    vpmulhw ymm2,ymm6,ymmword ptr [rcx]
    vpmullw ymm2,ymm6,ymm4
    vpmullw ymm2,ymm6,ymmword ptr [rcx]
    vpmulld ymm2,ymm6,ymm4
    vpmulld ymm2,ymm6,ymmword ptr [rcx]
    vpmuludq ymm2,ymm6,ymm4
    vpmuludq ymm2,ymm6,ymmword ptr [rcx]
    vpmuldq ymm2,ymm6,ymm4
    vpmuldq ymm2,ymm6,ymmword ptr [rcx]
    vpor ymm2,ymm6,ymm4
    vpor ymm2,ymm6,ymmword ptr [rcx]
    vpsadbw ymm2,ymm6,ymm4
    vpsadbw ymm2,ymm6,ymmword ptr [rcx]
    vpshufb ymm2,ymm6,ymm4
    vpshufb ymm2,ymm6,ymmword ptr [rcx]
    vpsignb ymm2,ymm6,ymm4
    vpsignb ymm2,ymm6,ymmword ptr [rcx]
    vpsignw ymm2,ymm6,ymm4
    vpsignw ymm2,ymm6,ymmword ptr [rcx]
    vpsignd ymm2,ymm6,ymm4
    vpsignd ymm2,ymm6,ymmword ptr [rcx]
    vpsubb ymm2,ymm6,ymm4
    vpsubb ymm2,ymm6,ymmword ptr [rcx]
    vpsubw ymm2,ymm6,ymm4
    vpsubw ymm2,ymm6,ymmword ptr [rcx]
    vpsubd ymm2,ymm6,ymm4
    vpsubd ymm2,ymm6,ymmword ptr [rcx]
    vpsubq ymm2,ymm6,ymm4
    vpsubq ymm2,ymm6,ymmword ptr [rcx]
    vpsubsb ymm2,ymm6,ymm4
    vpsubsb ymm2,ymm6,ymmword ptr [rcx]
    vpsubsw ymm2,ymm6,ymm4
    vpsubsw ymm2,ymm6,ymmword ptr [rcx]
    vpsubusb ymm2,ymm6,ymm4
    vpsubusb ymm2,ymm6,ymmword ptr [rcx]
    vpsubusw ymm2,ymm6,ymm4
    vpsubusw ymm2,ymm6,ymmword ptr [rcx]
    vpunpckhbw ymm2,ymm6,ymm4
    vpunpckhbw ymm2,ymm6,ymmword ptr [rcx]
    vpunpckhwd ymm2,ymm6,ymm4
    vpunpckhwd ymm2,ymm6,ymmword ptr [rcx]
    vpunpckhdq ymm2,ymm6,ymm4
    vpunpckhdq ymm2,ymm6,ymmword ptr [rcx]
    vpunpckhqdq ymm2,ymm6,ymm4
    vpunpckhqdq ymm2,ymm6,ymmword ptr [rcx]
    vpunpcklbw ymm2,ymm6,ymm4
    vpunpcklbw ymm2,ymm6,ymmword ptr [rcx]
    vpunpcklwd ymm2,ymm6,ymm4
    vpunpcklwd ymm2,ymm6,ymmword ptr [rcx]
    vpunpckldq ymm2,ymm6,ymm4
    vpunpckldq ymm2,ymm6,ymmword ptr [rcx]
    vpunpcklqdq ymm2,ymm6,ymm4
    vpunpcklqdq ymm2,ymm6,ymmword ptr [rcx]
    vpxor ymm2,ymm6,ymm4
    vpxor ymm2,ymm6,ymmword ptr [rcx]
    vpabsb ymm6,ymm4
    vpabsb ymm4,ymmword ptr [rcx]
    vpabsw ymm6,ymm4
    vpabsw ymm4,ymmword ptr [rcx]
    vpabsd ymm6,ymm4
    vpabsd ymm4,ymmword ptr [rcx]
    vmpsadbw ymm2,ymm6,ymm4,0x7
    vmpsadbw ymm2,ymm6,ymmword ptr [rcx],0x7
    vpalignr ymm2,ymm6,ymm4,0x7
    vpalignr ymm2,ymm6,ymmword ptr [rcx],0x7
    vpblendw ymm2,ymm6,ymm4,0x7
    vpblendw ymm2,ymm6,ymmword ptr [rcx],0x7
    vpblendvb ymm7,ymm2,ymm6,ymm4
    vpblendvb ymm7,ymm2,ymmword ptr [rcx],ymm4
    vpsllw ymm2,ymm6,xmm4
    vpsllw ymm2,ymm6,oword ptr [rcx]
    vpslld ymm2,ymm6,xmm4
    vpslld ymm2,ymm6,oword ptr [rcx]
    vpsllq ymm2,ymm6,xmm4
    vpsllq ymm2,ymm6,oword ptr [rcx]
    vpsraw ymm2,ymm6,xmm4
    vpsraw ymm2,ymm6,oword ptr [rcx]
    vpsrad ymm2,ymm6,xmm4
    vpsrad ymm2,ymm6,oword ptr [rcx]
    vpsrlw ymm2,ymm6,xmm4
    vpsrlw ymm2,ymm6,oword ptr [rcx]
    vpsrld ymm2,ymm6,xmm4
    vpsrld ymm2,ymm6,oword ptr [rcx]
    vpsrlq ymm2,ymm6,xmm4
    vpsrlq ymm2,ymm6,oword ptr [rcx]
    vpmovsxbw ymm4,xmm4
    vpmovsxbw ymm4,oword ptr [rcx]
    vpmovsxwd ymm4,xmm4
    vpmovsxwd ymm4,oword ptr [rcx]
    vpmovsxdq ymm4,xmm4
    vpmovsxdq ymm4,oword ptr [rcx]
    vpmovzxbw ymm4,xmm4
    vpmovzxbw ymm4,oword ptr [rcx]
    vpmovzxwd ymm4,xmm4
    vpmovzxwd ymm4,oword ptr [rcx]
    vpmovzxdq ymm4,xmm4
    vpmovzxdq ymm4,oword ptr [rcx]
    vpmovsxbd ymm6,xmm4
    vpmovsxbd ymm4,qword ptr [rcx]
    vpmovsxwq ymm6,xmm4
    vpmovsxwq ymm4,qword ptr [rcx]
    vpmovzxbd ymm6,xmm4
    vpmovzxbd ymm4,qword ptr [rcx]
    vpmovzxwq ymm6,xmm4
    vpmovzxwq ymm4,qword ptr [rcx]
    vpmovsxbq ymm4,xmm4
    vpmovsxbq ymm4,dword ptr [rcx]
    vpmovzxbq ymm4,xmm4
    vpmovzxbq ymm4,dword ptr [rcx]
    vpmovmskb ecx,ymm4
    vpmovmskb ecx,ymm4
    vpslld ymm2,ymm6,0x7
    vpslldq ymm2,ymm6,0x7
    vpsllq ymm2,ymm6,0x7
    vpsllw ymm2,ymm6,0x7
    vpsrad ymm2,ymm6,0x7
    vpsraw ymm2,ymm6,0x7
    vpsrld ymm2,ymm6,0x7
    vpsrldq ymm2,ymm6,0x7
    vpsrlq ymm2,ymm6,0x7
    vpsrlw ymm2,ymm6,0x7
    vpshufd ymm2,ymm6,0x7
    vpshufd ymm6,ymmword ptr [rcx],0x7
    vpshufd ymm6,ymmword ptr [rcx],0x7
    vpshufhw ymm2,ymm6,0x7
    vpshufhw ymm6,ymmword ptr [rcx],0x7
    vpshufhw ymm6,ymmword ptr [rcx],0x7
    vpshuflw ymm2,ymm6,0x7
    vpshuflw ymm6,ymmword ptr [rcx],0x7
    vpshuflw ymm6,ymmword ptr [rcx],0x7
    vpackssdw ymm2,ymm6,ymm4
    vpackssdw ymm2,ymm6,ymmword ptr [rcx]
    vpackssdw ymm2,ymm6,ymmword ptr [rcx]
    vpacksswb ymm2,ymm6,ymm4
    vpacksswb ymm2,ymm6,ymmword ptr [rcx]
    vpacksswb ymm2,ymm6,ymmword ptr [rcx]
    vpackusdw ymm2,ymm6,ymm4
    vpackusdw ymm2,ymm6,ymmword ptr [rcx]
    vpackusdw ymm2,ymm6,ymmword ptr [rcx]
    vpackuswb ymm2,ymm6,ymm4
    vpackuswb ymm2,ymm6,ymmword ptr [rcx]
    vpackuswb ymm2,ymm6,ymmword ptr [rcx]
    vpaddb ymm2,ymm6,ymm4
    vpaddb ymm2,ymm6,ymmword ptr [rcx]
    vpaddb ymm2,ymm6,ymmword ptr [rcx]
    vpaddw ymm2,ymm6,ymm4
    vpaddw ymm2,ymm6,ymmword ptr [rcx]
    vpaddw ymm2,ymm6,ymmword ptr [rcx]
    vpaddd ymm2,ymm6,ymm4
    vpaddd ymm2,ymm6,ymmword ptr [rcx]
    vpaddd ymm2,ymm6,ymmword ptr [rcx]
    vpaddq ymm2,ymm6,ymm4
    vpaddq ymm2,ymm6,ymmword ptr [rcx]
    vpaddq ymm2,ymm6,ymmword ptr [rcx]
    vpaddsb ymm2,ymm6,ymm4
    vpaddsb ymm2,ymm6,ymmword ptr [rcx]
    vpaddsb ymm2,ymm6,ymmword ptr [rcx]
    vpaddsw ymm2,ymm6,ymm4
    vpaddsw ymm2,ymm6,ymmword ptr [rcx]
    vpaddsw ymm2,ymm6,ymmword ptr [rcx]
    vpaddusb ymm2,ymm6,ymm4
    vpaddusb ymm2,ymm6,ymmword ptr [rcx]
    vpaddusb ymm2,ymm6,ymmword ptr [rcx]
    vpaddusw ymm2,ymm6,ymm4
    vpaddusw ymm2,ymm6,ymmword ptr [rcx]
    vpaddusw ymm2,ymm6,ymmword ptr [rcx]
    vpand ymm2,ymm6,ymm4
    vpand ymm2,ymm6,ymmword ptr [rcx]
    vpand ymm2,ymm6,ymmword ptr [rcx]
    vpandn ymm2,ymm6,ymm4
    vpandn ymm2,ymm6,ymmword ptr [rcx]
    vpandn ymm2,ymm6,ymmword ptr [rcx]
    vpavgb ymm2,ymm6,ymm4
    vpavgb ymm2,ymm6,ymmword ptr [rcx]
    vpavgb ymm2,ymm6,ymmword ptr [rcx]
    vpavgw ymm2,ymm6,ymm4
    vpavgw ymm2,ymm6,ymmword ptr [rcx]
    vpavgw ymm2,ymm6,ymmword ptr [rcx]
    vpcmpeqb ymm2,ymm6,ymm4
    vpcmpeqb ymm2,ymm6,ymmword ptr [rcx]
    vpcmpeqb ymm2,ymm6,ymmword ptr [rcx]
    vpcmpeqw ymm2,ymm6,ymm4
    vpcmpeqw ymm2,ymm6,ymmword ptr [rcx]
    vpcmpeqw ymm2,ymm6,ymmword ptr [rcx]
    vpcmpeqd ymm2,ymm6,ymm4
    vpcmpeqd ymm2,ymm6,ymmword ptr [rcx]
    vpcmpeqd ymm2,ymm6,ymmword ptr [rcx]
    vpcmpeqq ymm2,ymm6,ymm4
    vpcmpeqq ymm2,ymm6,ymmword ptr [rcx]
    vpcmpeqq ymm2,ymm6,ymmword ptr [rcx]
    vpcmpgtb ymm2,ymm6,ymm4
    vpcmpgtb ymm2,ymm6,ymmword ptr [rcx]
    vpcmpgtb ymm2,ymm6,ymmword ptr [rcx]
    vpcmpgtw ymm2,ymm6,ymm4
    vpcmpgtw ymm2,ymm6,ymmword ptr [rcx]
    vpcmpgtw ymm2,ymm6,ymmword ptr [rcx]
    vpcmpgtd ymm2,ymm6,ymm4
    vpcmpgtd ymm2,ymm6,ymmword ptr [rcx]
    vpcmpgtd ymm2,ymm6,ymmword ptr [rcx]
    vpcmpgtq ymm2,ymm6,ymm4
    vpcmpgtq ymm2,ymm6,ymmword ptr [rcx]
    vpcmpgtq ymm2,ymm6,ymmword ptr [rcx]
    vphaddw ymm2,ymm6,ymm4
    vphaddw ymm2,ymm6,ymmword ptr [rcx]
    vphaddw ymm2,ymm6,ymmword ptr [rcx]
    vphaddd ymm2,ymm6,ymm4
    vphaddd ymm2,ymm6,ymmword ptr [rcx]
    vphaddd ymm2,ymm6,ymmword ptr [rcx]
    vphaddsw ymm2,ymm6,ymm4
    vphaddsw ymm2,ymm6,ymmword ptr [rcx]
    vphaddsw ymm2,ymm6,ymmword ptr [rcx]
    vphsubw ymm2,ymm6,ymm4
    vphsubw ymm2,ymm6,ymmword ptr [rcx]
    vphsubw ymm2,ymm6,ymmword ptr [rcx]
    vphsubd ymm2,ymm6,ymm4
    vphsubd ymm2,ymm6,ymmword ptr [rcx]
    vphsubd ymm2,ymm6,ymmword ptr [rcx]
    vphsubsw ymm2,ymm6,ymm4
    vphsubsw ymm2,ymm6,ymmword ptr [rcx]
    vphsubsw ymm2,ymm6,ymmword ptr [rcx]
    vpmaddwd ymm2,ymm6,ymm4
    vpmaddwd ymm2,ymm6,ymmword ptr [rcx]
    vpmaddwd ymm2,ymm6,ymmword ptr [rcx]
    vpmaddubsw ymm2,ymm6,ymm4
    vpmaddubsw ymm2,ymm6,ymmword ptr [rcx]
    vpmaddubsw ymm2,ymm6,ymmword ptr [rcx]
    vpmaxsb ymm2,ymm6,ymm4
    vpmaxsb ymm2,ymm6,ymmword ptr [rcx]
    vpmaxsb ymm2,ymm6,ymmword ptr [rcx]
    vpmaxsw ymm2,ymm6,ymm4
    vpmaxsw ymm2,ymm6,ymmword ptr [rcx]
    vpmaxsw ymm2,ymm6,ymmword ptr [rcx]
    vpmaxsd ymm2,ymm6,ymm4
    vpmaxsd ymm2,ymm6,ymmword ptr [rcx]
    vpmaxsd ymm2,ymm6,ymmword ptr [rcx]
    vpmaxub ymm2,ymm6,ymm4
    vpmaxub ymm2,ymm6,ymmword ptr [rcx]
    vpmaxub ymm2,ymm6,ymmword ptr [rcx]
    vpmaxuw ymm2,ymm6,ymm4
    vpmaxuw ymm2,ymm6,ymmword ptr [rcx]
    vpmaxuw ymm2,ymm6,ymmword ptr [rcx]
    vpmaxud ymm2,ymm6,ymm4
    vpmaxud ymm2,ymm6,ymmword ptr [rcx]
    vpmaxud ymm2,ymm6,ymmword ptr [rcx]
    vpminsb ymm2,ymm6,ymm4
    vpminsb ymm2,ymm6,ymmword ptr [rcx]
    vpminsb ymm2,ymm6,ymmword ptr [rcx]
    vpminsw ymm2,ymm6,ymm4
    vpminsw ymm2,ymm6,ymmword ptr [rcx]
    vpminsw ymm2,ymm6,ymmword ptr [rcx]
    vpminsd ymm2,ymm6,ymm4
    vpminsd ymm2,ymm6,ymmword ptr [rcx]
    vpminsd ymm2,ymm6,ymmword ptr [rcx]
    vpminub ymm2,ymm6,ymm4
    vpminub ymm2,ymm6,ymmword ptr [rcx]
    vpminub ymm2,ymm6,ymmword ptr [rcx]
    vpminuw ymm2,ymm6,ymm4
    vpminuw ymm2,ymm6,ymmword ptr [rcx]
    vpminuw ymm2,ymm6,ymmword ptr [rcx]
    vpminud ymm2,ymm6,ymm4
    vpminud ymm2,ymm6,ymmword ptr [rcx]
    vpminud ymm2,ymm6,ymmword ptr [rcx]
    vpmulhuw ymm2,ymm6,ymm4
    vpmulhuw ymm2,ymm6,ymmword ptr [rcx]
    vpmulhuw ymm2,ymm6,ymmword ptr [rcx]
    vpmulhrsw ymm2,ymm6,ymm4
    vpmulhrsw ymm2,ymm6,ymmword ptr [rcx]
    vpmulhrsw ymm2,ymm6,ymmword ptr [rcx]
    vpmulhw ymm2,ymm6,ymm4
    vpmulhw ymm2,ymm6,ymmword ptr [rcx]
    vpmulhw ymm2,ymm6,ymmword ptr [rcx]
    vpmullw ymm2,ymm6,ymm4
    vpmullw ymm2,ymm6,ymmword ptr [rcx]
    vpmullw ymm2,ymm6,ymmword ptr [rcx]
    vpmulld ymm2,ymm6,ymm4
    vpmulld ymm2,ymm6,ymmword ptr [rcx]
    vpmulld ymm2,ymm6,ymmword ptr [rcx]
    vpmuludq ymm2,ymm6,ymm4
    vpmuludq ymm2,ymm6,ymmword ptr [rcx]
    vpmuludq ymm2,ymm6,ymmword ptr [rcx]
    vpmuldq ymm2,ymm6,ymm4
    vpmuldq ymm2,ymm6,ymmword ptr [rcx]
    vpmuldq ymm2,ymm6,ymmword ptr [rcx]
    vpor ymm2,ymm6,ymm4
    vpor ymm2,ymm6,ymmword ptr [rcx]
    vpor ymm2,ymm6,ymmword ptr [rcx]
    vpsadbw ymm2,ymm6,ymm4
    vpsadbw ymm2,ymm6,ymmword ptr [rcx]
    vpsadbw ymm2,ymm6,ymmword ptr [rcx]
    vpshufb ymm2,ymm6,ymm4
    vpshufb ymm2,ymm6,ymmword ptr [rcx]
    vpshufb ymm2,ymm6,ymmword ptr [rcx]
    vpsignb ymm2,ymm6,ymm4
    vpsignb ymm2,ymm6,ymmword ptr [rcx]
    vpsignb ymm2,ymm6,ymmword ptr [rcx]
    vpsignw ymm2,ymm6,ymm4
    vpsignw ymm2,ymm6,ymmword ptr [rcx]
    vpsignw ymm2,ymm6,ymmword ptr [rcx]
    vpsignd ymm2,ymm6,ymm4
    vpsignd ymm2,ymm6,ymmword ptr [rcx]
    vpsignd ymm2,ymm6,ymmword ptr [rcx]
    vpsubb ymm2,ymm6,ymm4
    vpsubb ymm2,ymm6,ymmword ptr [rcx]
    vpsubb ymm2,ymm6,ymmword ptr [rcx]
    vpsubw ymm2,ymm6,ymm4
    vpsubw ymm2,ymm6,ymmword ptr [rcx]
    vpsubw ymm2,ymm6,ymmword ptr [rcx]
    vpsubd ymm2,ymm6,ymm4
    vpsubd ymm2,ymm6,ymmword ptr [rcx]
    vpsubd ymm2,ymm6,ymmword ptr [rcx]
    vpsubq ymm2,ymm6,ymm4
    vpsubq ymm2,ymm6,ymmword ptr [rcx]
    vpsubq ymm2,ymm6,ymmword ptr [rcx]
    vpsubsb ymm2,ymm6,ymm4
    vpsubsb ymm2,ymm6,ymmword ptr [rcx]
    vpsubsb ymm2,ymm6,ymmword ptr [rcx]
    vpsubsw ymm2,ymm6,ymm4
    vpsubsw ymm2,ymm6,ymmword ptr [rcx]
    vpsubsw ymm2,ymm6,ymmword ptr [rcx]
    vpsubusb ymm2,ymm6,ymm4
    vpsubusb ymm2,ymm6,ymmword ptr [rcx]
    vpsubusb ymm2,ymm6,ymmword ptr [rcx]
    vpsubusw ymm2,ymm6,ymm4
    vpsubusw ymm2,ymm6,ymmword ptr [rcx]
    vpsubusw ymm2,ymm6,ymmword ptr [rcx]
    vpunpckhbw ymm2,ymm6,ymm4
    vpunpckhbw ymm2,ymm6,ymmword ptr [rcx]
    vpunpckhbw ymm2,ymm6,ymmword ptr [rcx]
    vpunpckhwd ymm2,ymm6,ymm4
    vpunpckhwd ymm2,ymm6,ymmword ptr [rcx]
    vpunpckhwd ymm2,ymm6,ymmword ptr [rcx]
    vpunpckhdq ymm2,ymm6,ymm4
    vpunpckhdq ymm2,ymm6,ymmword ptr [rcx]
    vpunpckhdq ymm2,ymm6,ymmword ptr [rcx]
    vpunpckhqdq ymm2,ymm6,ymm4
    vpunpckhqdq ymm2,ymm6,ymmword ptr [rcx]
    vpunpckhqdq ymm2,ymm6,ymmword ptr [rcx]
    vpunpcklbw ymm2,ymm6,ymm4
    vpunpcklbw ymm2,ymm6,ymmword ptr [rcx]
    vpunpcklbw ymm2,ymm6,ymmword ptr [rcx]
    vpunpcklwd ymm2,ymm6,ymm4
    vpunpcklwd ymm2,ymm6,ymmword ptr [rcx]
    vpunpcklwd ymm2,ymm6,ymmword ptr [rcx]
    vpunpckldq ymm2,ymm6,ymm4
    vpunpckldq ymm2,ymm6,ymmword ptr [rcx]
    vpunpckldq ymm2,ymm6,ymmword ptr [rcx]
    vpunpcklqdq ymm2,ymm6,ymm4
    vpunpcklqdq ymm2,ymm6,ymmword ptr [rcx]
    vpunpcklqdq ymm2,ymm6,ymmword ptr [rcx]
    vpxor ymm2,ymm6,ymm4
    vpxor ymm2,ymm6,ymmword ptr [rcx]
    vpxor ymm2,ymm6,ymmword ptr [rcx]
    vpabsb ymm6,ymm4
    vpabsb ymm4,ymmword ptr [rcx]
    vpabsb ymm4,ymmword ptr [rcx]
    vpabsw ymm6,ymm4
    vpabsw ymm4,ymmword ptr [rcx]
    vpabsw ymm4,ymmword ptr [rcx]
    vpabsd ymm6,ymm4
    vpabsd ymm4,ymmword ptr [rcx]
    vpabsd ymm4,ymmword ptr [rcx]
    vmpsadbw ymm2,ymm6,ymm4,0x7
    vmpsadbw ymm2,ymm6,ymmword ptr [rcx],0x7
    vmpsadbw ymm2,ymm6,ymmword ptr [rcx],0x7
    vpalignr ymm2,ymm6,ymm4,0x7
    vpalignr ymm2,ymm6,ymmword ptr [rcx],0x7
    vpalignr ymm2,ymm6,ymmword ptr [rcx],0x7
    vpblendw ymm2,ymm6,ymm4,0x7
    vpblendw ymm2,ymm6,ymmword ptr [rcx],0x7
    vpblendw ymm2,ymm6,ymmword ptr [rcx],0x7
    vpblendvb ymm7,ymm2,ymm6,ymm4
    vpblendvb ymm7,ymm2,ymmword ptr [rcx],ymm4
    vpblendvb ymm7,ymm2,ymmword ptr [rcx],ymm4
    vpsllw ymm2,ymm6,xmm4
    vpsllw ymm2,ymm6,oword ptr [rcx]
    vpsllw ymm2,ymm6,oword ptr [rcx]
    vpslld ymm2,ymm6,xmm4
    vpslld ymm2,ymm6,oword ptr [rcx]
    vpslld ymm2,ymm6,oword ptr [rcx]
    vpsllq ymm2,ymm6,xmm4
    vpsllq ymm2,ymm6,oword ptr [rcx]
    vpsllq ymm2,ymm6,oword ptr [rcx]
    vpsraw ymm2,ymm6,xmm4
    vpsraw ymm2,ymm6,oword ptr [rcx]
    vpsraw ymm2,ymm6,oword ptr [rcx]
    vpsrad ymm2,ymm6,xmm4
    vpsrad ymm2,ymm6,oword ptr [rcx]
    vpsrad ymm2,ymm6,oword ptr [rcx]
    vpsrlw ymm2,ymm6,xmm4
    vpsrlw ymm2,ymm6,oword ptr [rcx]
    vpsrlw ymm2,ymm6,oword ptr [rcx]
    vpsrld ymm2,ymm6,xmm4
    vpsrld ymm2,ymm6,oword ptr [rcx]
    vpsrld ymm2,ymm6,oword ptr [rcx]
    vpsrlq ymm2,ymm6,xmm4
    vpsrlq ymm2,ymm6,oword ptr [rcx]
    vpsrlq ymm2,ymm6,oword ptr [rcx]
    vpmovsxbw ymm4,xmm4
    vpmovsxbw ymm4,oword ptr [rcx]
    vpmovsxbw ymm4,oword ptr [rcx]
    vpmovsxwd ymm4,xmm4
    vpmovsxwd ymm4,oword ptr [rcx]
    vpmovsxwd ymm4,oword ptr [rcx]
    vpmovsxdq ymm4,xmm4
    vpmovsxdq ymm4,oword ptr [rcx]
    vpmovsxdq ymm4,oword ptr [rcx]
    vpmovzxbw ymm4,xmm4
    vpmovzxbw ymm4,oword ptr [rcx]
    vpmovzxbw ymm4,oword ptr [rcx]
    vpmovzxwd ymm4,xmm4
    vpmovzxwd ymm4,oword ptr [rcx]
    vpmovzxwd ymm4,oword ptr [rcx]
    vpmovzxdq ymm4,xmm4
    vpmovzxdq ymm4,oword ptr [rcx]
    vpmovzxdq ymm4,oword ptr [rcx]
    vpmovsxbd ymm6,xmm4
    vpmovsxbd ymm4,qword ptr [rcx]
    vpmovsxbd ymm4,qword ptr [rcx]
    vpmovsxwq ymm6,xmm4
    vpmovsxwq ymm4,qword ptr [rcx]
    vpmovsxwq ymm4,qword ptr [rcx]
    vpmovzxbd ymm6,xmm4
    vpmovzxbd ymm4,qword ptr [rcx]
    vpmovzxbd ymm4,qword ptr [rcx]
    vpmovzxwq ymm6,xmm4
    vpmovzxwq ymm4,qword ptr [rcx]
    vpmovzxwq ymm4,qword ptr [rcx]
    vpmovsxbq ymm4,xmm4
    vpmovsxbq ymm4,dword ptr [rcx]
    vpmovsxbq ymm4,dword ptr [rcx]
    vpmovzxbq ymm4,xmm4
    vpmovzxbq ymm4,dword ptr [rcx]
    vpmovzxbq ymm4,dword ptr [rcx]

    end
