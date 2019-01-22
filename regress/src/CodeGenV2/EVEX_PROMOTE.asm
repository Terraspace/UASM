; test promotion of vex to evex 

    .x64
    .model flat
    option evex:1
    .code


    {evex} vmovntdq  xmmword ptr [rax],xmm0
    {evex} vmovntdqa xmm0,xmmword ptr [rax]
    {evex} vmovntpd  xmmword ptr [rax],xmm0
    {evex} vmovntps  xmmword ptr [rax],xmm0
    {evex} vmovntdq  ymmword ptr [rax],ymm0
    {evex} vmovntdqa ymm0,ymmword ptr [rax]
    {evex} vmovntpd  ymmword ptr [rax],ymm0
    {evex} vmovntps  ymmword ptr [rax],ymm0
    {evex} vbroadcastss xmm0,dword ptr [rax]
    {evex} vbroadcastss ymm0,dword ptr [rax]
    {evex} vbroadcastsd ymm0,qword ptr [rax]
    {evex} vpermilpd xmm0,xmm1,xmm2
    {evex} vpermilpd xmm0,xmm1,xmmword ptr [rax]
    {evex} vpermilpd xmm0,xmm1,1
    {evex} vpermilpd ymm0,ymm1,ymm2
    {evex} vpermilpd ymm0,ymm1,ymmword ptr [rax]
    {evex} vpermilpd ymm0,ymm1,1
    {evex} vpermilps xmm0,xmm1,xmm2
    {evex} vpermilps xmm0,xmm1,xmmword ptr [rax]
    {evex} vpermilps xmm0,xmm1,1
    {evex} vpermilps ymm0,ymm1,ymm2
    {evex} vpermilps ymm0,ymm1,ymmword ptr [rax]
    {evex} vpermilps ymm0,ymm1,1
    {evex} vcomisd xmm1,xmm0
    {evex} vcomisd xmm0,xmm0
    {evex} vcomisd xmm0,[rax]
    {evex} vcomisd xmm0,xmm1
    {evex} vcomisd xmm0,xmm0
    {evex} vcomisd xmm1,xmm1
    {evex} vcomisd xmm0,xmm0
    {evex} vaddpd xmm0,xmm1,xmm2
    {evex} vaddpd xmm0,xmm31,xmm2
    {evex} vxorpd xmm1,xmm0,xmm0
    {evex} vxorpd xmm1,xmm0,[rax]
    {evex} vaddps xmm0,xmm1,xmm2
    {evex} vaddps xmm0,xmm1,[rax]
    {evex} vaddps ymm0,ymm1,ymm2
    {evex} vaddps ymm0,ymm1,[rax]
    {evex} vaddsd xmm0,xmm1,xmm2
    {evex} vaddsd xmm0,xmm1,[rax]
    {evex} vaddss xmm0,xmm1,xmm2
    {evex} vaddss xmm0,xmm1,[rax]
    {evex} vdivpd xmm0,xmm1,xmm2
    {evex} vdivpd xmm0,xmm1,[rax]
    {evex} vdivpd ymm0,ymm1,ymm2
    {evex} vdivpd ymm0,ymm1,[rax]
    {evex} vdivps xmm0,xmm1,xmm2
    {evex} vdivps xmm0,xmm1,[rax]
    {evex} vdivps ymm0,ymm1,ymm2
    {evex} vdivps ymm0,ymm1,[rax]
    {evex} vdivsd xmm0,xmm1,xmm2
    {evex} vdivsd xmm0,xmm1,[rax]
    {evex} vdivss xmm0,xmm1,xmm2
    {evex} vdivss xmm0,xmm1,[rax]
    {evex} vandpd xmm0,xmm1,xmm2
    {evex} vandpd ymm0,ymm1,ymm2
    {evex} vandps xmm0,xmm1,xmm2
    {evex} vandps ymm0,ymm1,ymm2
    {evex} vandnpd xmm0,xmm1,xmm2
    {evex} vandnpd ymm0,ymm1,ymm2
    {evex} vandnps xmm0,xmm1,xmm2
    {evex} vandnps ymm0,ymm1,ymm2
    {evex} vpsrlw xmm0,xmm1,xmm2
    {evex} vpsrlw xmm0,xmm1,[rax]
    {evex} vpsrld xmm0,xmm1,xmm2
    {evex} vpsrld xmm0,xmm1,[rax]
    {evex} vpsrlq xmm0,xmm1,xmm2
    {evex} vpsrlq xmm0,xmm1,[rax]
    {evex} vpsraw xmm0,xmm1,xmm2
    {evex} vpsraw xmm0,xmm1,[rax]
    {evex} vpsrad xmm0,xmm1,xmm2
    {evex} vpsrad xmm0,xmm1,[rax]
    {evex} vpsllw xmm0,xmm1,xmm2
    {evex} vpsllw xmm0,xmm1,[rax]
    {evex} vpslld xmm0,xmm1,xmm2
    {evex} vpslld xmm0,xmm1,[rax]
    {evex} vpsllq xmm0,xmm1,xmm2
    {evex} vpsllq xmm0,xmm1,[rax]
    {evex} vpslldq xmm0,xmm1,1
    {evex} vpsrldq xmm0,xmm1,2
    {evex} vpsrlw  xmm0,xmm1,3
    {evex} vpsrld  xmm0,xmm1,4
    {evex} vpsrlq  xmm0,xmm1,5
    {evex} vpsraw  xmm0,xmm1,6
    {evex} vpsrad  xmm0,xmm1,7
    {evex} vpsllw  xmm0,xmm1,8
    {evex} vpslld  xmm0,xmm1,9
    {evex} vpsllq  xmm0,xmm1,10
    {evex} vpsrlw  xmm0,xmm1,xmm2
    {evex} vpsrlw  xmm0,xmm1,[rax]
    {evex} vpsrld  xmm0,xmm1,xmm2
    {evex} vpsrld  xmm0,xmm1,[rax]
    {evex} vpsrlq  xmm0,xmm1,xmm2
    {evex} vpsrlq  xmm0,xmm1,[rax]
    {evex} vpsraw  xmm0,xmm1,xmm2
    {evex} vpsraw  xmm0,xmm1,[rax]
    {evex} vpsrad  xmm0,xmm1,xmm2
    {evex} vpsrad  xmm0,xmm1,[rax]
    {evex} vpsllw  xmm0,xmm1,xmm2
    {evex} vpsllw  xmm0,xmm1,[rax]
    {evex} vpslld  xmm0,xmm1,xmm2
    {evex} vpslld  xmm0,xmm1,[rax]
    {evex} vpsllq  xmm0,xmm1,xmm2
    {evex} vpsllq  xmm0,xmm1,[rax]
    {evex} vpabsb xmm0,xmm1
    {evex} vpabsb xmm0,[rax]
    {evex} vpabsw xmm0,xmm1
    {evex} vpabsw xmm0,[rax]
    {evex} vpabsd xmm0,xmm1
    {evex} vpabsd xmm0,[rax]
    {evex} vcomisd xmm0,xmm1
    {evex} vcomisd xmm0,[rax]
    {evex} vcomiss xmm0,xmm1
    {evex} vcomiss xmm0,[rax]
    {evex} vucomisd xmm0,xmm1
    {evex} vucomisd xmm0,[rax]
    {evex} vucomiss xmm0,xmm1
    {evex} vucomiss xmm0,[rax]
    {evex} vpmovsxbw xmm0,xmm1
    {evex} vpmovsxbw xmm0,[rax]
    {evex} vpmovsxbd xmm0,xmm1
    {evex} vpmovsxbd xmm0,[rax]
    {evex} vpmovsxbq xmm0,xmm1
    {evex} vpmovsxbq xmm0,[rax]
    {evex} vpmovsxwd xmm0,xmm1
    {evex} vpmovsxwd xmm0,[rax]
    {evex} vpmovsxwq xmm0,xmm1
    {evex} vpmovsxwq xmm0,[rax]
    {evex} vpmovsxdq xmm0,xmm1
    {evex} vpmovsxdq xmm0,[rax]
    {evex} vextractps eax,xmm1,1
    {evex} vextractps [rax],xmm1,1
    {evex} vinsertps xmm0,xmm1,xmm3,0
    {evex} vinsertps xmm0,xmm1,[rax],1
    {evex} vcvtdq2pd xmm0,xmm1
    {evex} vcvtdq2pd xmm0,[rax]
    {evex} vcvtdq2pd ymm0,xmm1	  ;!
    {evex} vcvtdq2pd ymm0,[rax]	  ;!
    {evex} vcvtdq2ps xmm0,xmm1
    {evex} vcvtdq2ps xmm0,[rax]
    {evex} vcvtdq2ps ymm0,ymm1
    {evex} vcvtdq2ps ymm0,[rax]
    {evex} vcvtpd2dq xmm0,xmm1
    {evex} vcvtpd2dq xmm0,xmmword ptr [rax]
    {evex} vcvtpd2dq xmm0,ymm1
    {evex} vcvtpd2dq xmm0,ymmword ptr [rax]
    {evex} vcvttpd2dq xmm0,xmm1
    {evex} vcvttpd2dq xmm0,xmmword ptr [rax]
    {evex} vcvttpd2dq xmm0,ymm1
    {evex} vcvttpd2dq xmm0,ymmword ptr [rax]
    {evex} vcvtpd2ps xmm0,xmm1
    {evex} vcvtpd2ps xmm0,xmmword ptr [rax]
    {evex} vcvtpd2ps xmm0,ymm1
    {evex} vcvtpd2ps xmm0,ymmword ptr [rax]
    {evex} vcvtps2dq xmm0,xmm1
    {evex} vcvtps2dq xmm0,xmmword ptr [rax]
    {evex} vcvtps2dq ymm0,ymm1
    {evex} vcvtps2dq ymm0,ymmword ptr [rax]
    {evex} vcvttps2dq xmm0,xmm1
    {evex} vcvttps2dq xmm0,xmmword ptr [rax]
    {evex} vcvttps2dq ymm0,ymm1
    {evex} vcvttps2dq ymm0,ymmword ptr [rax]
    {evex} vcvtps2pd xmm0,xmm1
    {evex} vcvtps2pd ymm0,xmm1
    {evex} vcvtsd2si eax,xmm1
    {evex} vcvtsd2si eax,[rax]
    {evex} vcvttsd2si eax,xmm1
    {evex} vcvttsd2si eax,[rax]
    {evex} vcvtsd2ss xmm0,xmm1,xmm2
    {evex} vcvtsd2ss xmm0,xmm1,[rax]
    {evex} vcvtsi2sd xmm0,xmm1,eax
    {evex} vcvtsi2sd xmm0,xmm1,dword ptr [rax]
    {evex} vcvtsi2ss xmm0,xmm1,eax
    {evex} vcvtsi2ss xmm0,xmm1,dword ptr [rax]
    {evex} vcvtss2sd xmm0,xmm1,xmm2
    {evex} vcvtss2sd xmm0,xmm1,dword ptr [rax]
    {evex} vcvtss2si eax,xmm1
    {evex} vcvtss2si eax,[rax]
    {evex} vcvttss2si eax,xmm1
    {evex} vcvttss2si eax,[rax]
    {evex} vmovapd xmm0,xmm1
    {evex} vmovapd xmm0,xmmword ptr [rax]
    {evex} vmovapd xmmword ptr [rax],xmm1
    {evex} vmovapd ymm0,ymm1
    {evex} vmovapd ymm0,ymmword ptr [rax]
    {evex} vmovapd ymmword ptr [rax],ymm1
    {evex} vmovaps xmm0,xmm1
    {evex} vmovaps xmm0,xmmword ptr [rax]
    {evex} vmovaps xmmword ptr [rax],xmm1
    {evex} vmovaps ymm0,ymm1
    {evex} vmovaps ymm0,ymmword ptr [rax]
    {evex} vmovaps ymmword ptr [rax],ymm1
    {evex} vmovupd xmm0,xmm1
    {evex} vmovupd xmm0,xmmword ptr [rax]
    {evex} vmovupd xmmword ptr [rax],xmm1
    {evex} vmovupd ymm0,ymm1
    {evex} vmovupd ymm0,ymmword ptr [rax]
    {evex} vmovupd ymmword ptr [rax],ymm1
    {evex} vmovups xmm0,xmm1
    {evex} vmovups xmm0,xmmword ptr [rax]
    {evex} vmovups xmmword ptr [rax],xmm1
    {evex} vmovups ymm0,ymm1
    {evex} vmovups ymm0,ymmword ptr [rax]
    {evex} vmovups ymmword ptr [rax],ymm1
    {evex} vmovhlps xmm0,xmm1,xmm2
    {evex} vmovlhps xmm0,xmm1,xmm2
    {evex} vmovhpd xmm0,xmm1,qword ptr [rax]
    {evex} vmovhpd qword ptr [rax],xmm1
    {evex} vmovhps xmm0,xmm1,qword ptr [rax]
    {evex} vmovhps qword ptr [rax],xmm1
    {evex} vmovlpd xmm0,xmm1,qword ptr [rax]
    {evex} vmovlpd qword ptr [rax],xmm1
    {evex} vmovlps xmm0,xmm1,qword ptr [rax]
    {evex} vmovlps qword ptr [rax],xmm1
    {evex} vpextrb eax,xmm1,1
    {evex} vpextrb byte ptr [rax],xmm1,1
    ;{evex} vpextrw eax,xmm1,2
    ;{evex} vpextrw word ptr [rax],xmm1,2
    {evex} vpextrd eax,xmm1,3
    {evex} vpextrd dword ptr [rax],xmm1,3
    {evex} vpextrq rax,xmm1,4
    {evex} vpextrq qword ptr [rax],xmm1,4
    {evex} vpinsrb xmm0,xmm1,eax,1
    {evex} vpinsrb xmm0,xmm1,byte ptr [rax],1
    {evex} vpinsrw xmm0,xmm1,eax,2
    {evex} vpinsrw xmm0,xmm1,word ptr [rax],2
    {evex} vpinsrd xmm0,xmm1,eax,3
    {evex} vpinsrd xmm0,xmm1,dword ptr [rax],3
    {evex} vpinsrq xmm0,xmm1,rax,4
    {evex} vpinsrq xmm0,xmm1,qword ptr [rax],4
    {evex} vmovddup xmm0,xmm1
    {evex} vmovddup xmm0,qword ptr [rax]
    {evex} vmovddup ymm0,ymm1
    {evex} vmovddup ymm0,ymmword ptr [rax]
    {evex} vpaddb   xmm0,xmm0,xmm1
    {evex} vpaddw   xmm0,xmm0,xmm1
    {evex} vpaddd   xmm0,xmm0,xmm1
    {evex} vpaddq   xmm0,xmm0,xmm1
    {evex} vpaddsb  xmm0,xmm0,xmm1
    {evex} vpaddsw  xmm0,xmm0,xmm1
    {evex} vpaddusb xmm0,xmm0,xmm1
    {evex} vpaddusw xmm0,xmm0,xmm1
    {evex} vpavgb   xmm0,xmm0,xmm1
    {evex} vpavgw   xmm0,xmm0,xmm1
    {evex} vpaddb   ymm0,ymm0,ymm1
    {evex} vpaddw   ymm0,ymm0,ymm1
    {evex} vpaddd   ymm0,ymm0,ymm1
    {evex} vpaddq   ymm0,ymm0,ymm1
    {evex} vpaddsb  ymm0,ymm0,ymm1
    {evex} vpaddsw  ymm0,ymm0,ymm1
    {evex} vpaddusb ymm0,ymm0,ymm1
    {evex} vpaddusw ymm0,ymm0,ymm1
    {evex} vpavgb   ymm0,ymm0,ymm1
    {evex} vpavgw   ymm0,ymm0,ymm1

    {evex} vpsrlvq xmm2,xmm6,xmm4
    {evex} vpsrlvq xmm2,xmm6,xmmword ptr [rcx]
    {evex} vpermpd ymm2,ymm6,0x7
    {evex} vpermpd ymm6,YMMWORD PTR [rcx],0x7
    {evex} vpermq  ymm2,ymm6,0x7
    {evex} vpermq  ymm6,YMMWORD PTR [rcx],0x7
    {evex} vpermd  ymm2,ymm6,ymm4
    {evex} vpermd  ymm2,ymm6,YMMWORD PTR [rcx]
    {evex} vpermps ymm2,ymm6,ymm4
    {evex} vpermps ymm2,ymm6,YMMWORD PTR [rcx]
    {evex} vpsllvd ymm2,ymm6,ymm4
    {evex} vpsllvd ymm2,ymm6,YMMWORD PTR [rcx]
    {evex} vpsllvq ymm2,ymm6,ymm4
    {evex} vpsllvq ymm2,ymm6,YMMWORD PTR [rcx]
    {evex} vpsravd ymm2,ymm6,ymm4
    {evex} vpsravd ymm2,ymm6,YMMWORD PTR [rcx]
    {evex} vpsrlvd ymm2,ymm6,ymm4
    {evex} vpsrlvd ymm2,ymm6,YMMWORD PTR [rcx]
    {evex} vpsrlvq ymm2,ymm6,ymm4
    {evex} vpsrlvq ymm2,ymm6,YMMWORD PTR [rcx]

end