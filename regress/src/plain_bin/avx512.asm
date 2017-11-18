
    .x64
    .model flat
    option evex:1
    .code

    vmovd eax,xmm1
    vmovd eax,xmm20
    vmovd xmm20,eax
    vmovd xmm30,eax
    vmovd xmm30,ebp
    vmovd xmm30,r13d
    vmovd xmm20,dword ptr [rax]
    vmovd xmm30,dword ptr [rcx]
    vmovd xmm30,dword ptr [rax+r14*8+0x123]
    vmovd xmm30,dword ptr [rdx+0x1fc]
    vmovd xmm30,dword ptr [rdx+0x200]
    vmovd xmm30,dword ptr [rdx-0x200]
    vmovd xmm30,dword ptr [rdx-0x204]
    vmovd dword ptr [rax],xmm20
    vmovd dword ptr [rcx],xmm30
    vmovd dword ptr [rax+r14*8+0x123],xmm30
    vmovd dword ptr [rdx+0x1fc],xmm30
    vmovd dword ptr [rdx+0x200],xmm30
    vmovd dword ptr [rdx-0x200],xmm30
    vmovd dword ptr [rdx-0x204],xmm30

    vmovq xmm0,rax
    vmovq xmm3,r8
    vmovq xmm30,rax
    vmovq xmm30,r8
    vmovq xmm20,qword ptr [rax]
    vmovq xmm30,qword ptr [rcx]
    vmovq xmm30,qword ptr [rax+r14*8+0x123]
    vmovq xmm30,qword ptr [rdx+0x3f8]
    vmovq xmm30,qword ptr [rdx+0x400]
    vmovq xmm30,qword ptr [rdx-0x400]
    vmovq xmm30,qword ptr [rdx-0x408]
    vmovq qword ptr [rax],xmm20
    vmovq qword ptr [rcx],xmm30
    vmovq qword ptr [rax+r14*8+0x123],xmm30
    vmovq qword ptr [rdx+0x3f8],xmm30
    vmovq qword ptr [rdx+0x400],xmm30
    vmovq qword ptr [rdx-0x400],xmm30
    vmovq qword ptr [rdx-0x408],xmm30
    vmovq xmm30,xmm29
    vmovq xmm30,qword ptr [rcx]
    vmovq xmm30,qword ptr [rax+r14*8+0x123]
    vmovq xmm30,qword ptr [rdx+0x3f8]
    vmovq xmm30,qword ptr [rdx+0x400]
    vmovq xmm30,qword ptr [rdx-0x400]
    vmovq xmm30,qword ptr [rdx-0x408]
    vmovq qword ptr [rcx],xmm29
    vmovq qword ptr [rax+r14*8+0x123],xmm29
    vmovq qword ptr [rdx+0x3f8],xmm29
    vmovq qword ptr [rdx+0x400],xmm29
    vmovq qword ptr [rdx-0x400],xmm29
    vmovq qword ptr [rdx-0x408],xmm29

    vaddpd xmm1,xmm2,xmm3
    vaddps xmm1,xmm2,xmm3
    vaddsd xmm1,xmm2,xmm3
    vaddss xmm1,xmm2,xmm3
    vaddpd xmm1{k1}{z},xmm2,xmm3
    vaddps xmm1{k1}{z},xmm2,xmm3
    vaddsd xmm1{k1}{z},xmm2,xmm3
    vaddss xmm1{k1}{z},xmm2,xmm3
    vaddpd ymm1,ymm2,ymm3
    vaddps ymm1,ymm2,ymm3
    vaddpd ymm1{k1}{z},ymm2,ymm3
    vaddps ymm1{k1}{z},ymm2,ymm3
    vaddpd zmm1,zmm2,zmm3
    vaddps zmm1,zmm2,zmm3
    vaddpd zmm1{k1}{z},zmm2,zmm3
    vaddps zmm1{k1}{z},zmm2,zmm3
    vaddpd xmm1,xmm2,[rax]
    vaddps xmm1,xmm2,[rax]
    vaddsd xmm1,xmm2,[rax]
    vaddss xmm1,xmm2,[rax]
    vaddpd xmm1{k1}{z},xmm2,[rax]
    vaddps xmm1{k1}{z},xmm2,[rax]
    vaddsd xmm1{k1}{z},xmm2,[rax]
    vaddss xmm1{k1}{z},xmm2,[rax]
    vaddpd ymm1,ymm2,[rax]
    vaddps ymm1,ymm2,[rax]
    vaddpd ymm1{k1}{z},ymm2,[rax]
    vaddps ymm1{k1}{z},ymm2,[rax]
    vaddpd zmm1,zmm2,[rax]
    vaddps zmm1,zmm2,[rax]
    vaddpd zmm1{k1}{z},zmm2,[rax]
    vaddps zmm1{k1}{z},zmm2,[rax]

    vaddpd xmm16,xmm1,xmm2
    vaddpd xmm16,xmm31,xmm2
    vxorpd xmm17,xmm16,xmm16
    vxorpd xmm17,xmm16,[rax]
    vaddps xmm16,xmm1,xmm2
    vaddps xmm16,xmm1,[rax]
    vaddps ymm16,ymm1,ymm2
    vaddps ymm16,ymm1,[rax]
    vaddsd xmm16,xmm1,xmm2
    vaddsd xmm16,xmm1,[rax]
    vaddss xmm16,xmm1,xmm2
    vaddss xmm16,xmm1,[rax]

    vaddpd xmm16,xmm2,xmm3
    vaddps xmm16,xmm2,xmm3
    vaddsd xmm16,xmm2,xmm3
    vaddss xmm16,xmm2,xmm3
    vaddpd xmm16{k1}{z},xmm2,xmm3
    vaddps xmm16{k1}{z},xmm2,xmm3
    vaddsd xmm16{k1}{z},xmm2,xmm3
    vaddss xmm16{k1}{z},xmm2,xmm3
    vaddpd ymm16,ymm2,ymm3
    vaddps ymm16,ymm2,ymm3
    vaddpd ymm16{k1}{z},ymm2,ymm3
    vaddps ymm16{k1}{z},ymm2,ymm3
    vaddpd xmm16,xmm2,[rax]
    vaddps xmm16,xmm2,[rax]
    vaddsd xmm16,xmm2,[rax]
    vaddss xmm16,xmm2,[rax]
    vaddpd xmm16{k1}{z},xmm2,[rax]
    vaddps xmm16{k1}{z},xmm2,[rax]
    vaddsd xmm16{k1}{z},xmm2,[rax]
    vaddss xmm16{k1}{z},xmm2,[rax]
    vaddpd ymm16,ymm2,[rax]
    vaddps ymm16,ymm2,[rax]
    vaddpd ymm16{k1}{z},ymm2,[rax]
    vaddps ymm16{k1}{z},ymm2,[rax]

    vaddpd zmm30,zmm29,zmm28
    vaddpd zmm30{k7},zmm29,zmm28
    vaddpd zmm30{k7}{z},zmm29,zmm28
    vaddpd zmm30,zmm29,zmm28,{rn-sae}
    vaddpd zmm30,zmm29,zmm28,{ru-sae}
    vaddpd zmm30,zmm29,zmm28,{rd-sae}
    vaddpd zmm30,zmm29,zmm28,{rz-sae}
    vaddpd zmm30,zmm29,zmmword ptr [rcx]
    vaddpd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vaddpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vaddpd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vaddpd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vaddpd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vaddpd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vaddpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vaddpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vaddpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vaddpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vaddps zmm30,zmm29,zmm28
    vaddps zmm30{k7},zmm29,zmm28
    vaddps zmm30{k7}{z},zmm29,zmm28
    vaddps zmm30,zmm29,zmm28,{rn-sae}
    vaddps zmm30,zmm29,zmm28,{ru-sae}
    vaddps zmm30,zmm29,zmm28,{rd-sae}
    vaddps zmm30,zmm29,zmm28,{rz-sae}
    vaddps zmm30,zmm29,zmmword ptr [rcx]
    vaddps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vaddps zmm30,zmm29,dword ptr [rcx]{1to16}
    vaddps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vaddps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vaddps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vaddps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vaddps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vaddps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vaddps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vaddps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vaddsd xmm30{k7},xmm29,xmm28
    vaddsd xmm30{k7}{z},xmm29,xmm28
    vaddsd xmm30{k7},xmm29,xmm28,{rn-sae}
    vaddsd xmm30{k7},xmm29,xmm28,{ru-sae}
    vaddsd xmm30{k7},xmm29,xmm28,{rd-sae}
    vaddsd xmm30{k7},xmm29,xmm28,{rz-sae}
    vaddsd xmm30{k7},xmm29,qword ptr [rcx]
    vaddsd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vaddsd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vaddsd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vaddsd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vaddsd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vaddss xmm30{k7},xmm29,xmm28
    vaddss xmm30{k7}{z},xmm29,xmm28
    vaddss xmm30{k7},xmm29,xmm28,{rn-sae}
    vaddss xmm30{k7},xmm29,xmm28,{ru-sae}
    vaddss xmm30{k7},xmm29,xmm28,{rd-sae}
    vaddss xmm30{k7},xmm29,xmm28,{rz-sae}
    vaddss xmm30{k7},xmm29,dword ptr [rcx]
    vaddss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vaddss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vaddss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vaddss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vaddss xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vdivpd xmm1,xmm2,xmm3
    vdivps xmm1,xmm2,xmm3
    vdivsd xmm1,xmm2,xmm3
    vdivss xmm1,xmm2,xmm3
    vdivpd xmm1{k1}{z},xmm2,xmm3
    vdivps xmm1{k1}{z},xmm2,xmm3
    vdivsd xmm1{k1}{z},xmm2,xmm3
    vdivss xmm1{k1}{z},xmm2,xmm3
    vdivpd ymm1,ymm2,ymm3
    vdivps ymm1,ymm2,ymm3
    vdivpd ymm1{k1}{z},ymm2,ymm3
    vdivps ymm1{k1}{z},ymm2,ymm3
    vdivpd zmm1,zmm2,zmm3
    vdivps zmm1,zmm2,zmm3
    vdivpd zmm1{k1}{z},zmm2,zmm3
    vdivps zmm1{k1}{z},zmm2,zmm3
    vdivpd xmm1,xmm2,[rax]
    vdivps xmm1,xmm2,[rax]
    vdivsd xmm1,xmm2,[rax]
    vdivss xmm1,xmm2,[rax]
    vdivpd xmm1{k1}{z},xmm2,[rax]
    vdivps xmm1{k1}{z},xmm2,[rax]
    vdivsd xmm1{k1}{z},xmm2,[rax]
    vdivss xmm1{k1}{z},xmm2,[rax]
    vdivpd ymm1,ymm2,[rax]
    vdivps ymm1,ymm2,[rax]
    vdivpd ymm1{k1}{z},ymm2,[rax]
    vdivps ymm1{k1}{z},ymm2,[rax]
    vdivpd zmm1,zmm2,[rax]
    vdivps zmm1,zmm2,[rax]
    vdivpd zmm1{k1}{z},zmm2,[rax]
    vdivps zmm1{k1}{z},zmm2,[rax]

    vdivpd xmm16,xmm1,xmm2
    vdivpd xmm16,xmm1,[rax]
    vdivpd ymm16,ymm1,ymm2
    vdivpd ymm16,ymm1,[rax]
    vdivps xmm16,xmm1,xmm2
    vdivps xmm16,xmm1,[rax]
    vdivps ymm16,ymm1,ymm2
    vdivps ymm16,ymm1,[rax]
    vdivsd xmm20,xmm1,xmm2
    vdivsd xmm20,xmm1,[rax]
    vdivss xmm20,xmm1,xmm2
    vdivss xmm20,xmm1,[rax]

    vdivpd zmm30,zmm29,zmm28
    vdivpd zmm30{k7},zmm29,zmm28
    vdivpd zmm30{k7}{z},zmm29,zmm28
    vdivpd zmm30,zmm29,zmm28,{rn-sae}
    vdivpd zmm30,zmm29,zmm28,{ru-sae}
    vdivpd zmm30,zmm29,zmm28,{rd-sae}
    vdivpd zmm30,zmm29,zmm28,{rz-sae}
    vdivpd zmm30,zmm29,zmmword ptr [rcx]
    vdivpd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vdivpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vdivpd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vdivpd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vdivpd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vdivpd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vdivpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vdivpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vdivpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vdivpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vdivps zmm30,zmm29,zmm28
    vdivps zmm30{k7},zmm29,zmm28
    vdivps zmm30{k7}{z},zmm29,zmm28
    vdivps zmm30,zmm29,zmm28,{rn-sae}
    vdivps zmm30,zmm29,zmm28,{ru-sae}
    vdivps zmm30,zmm29,zmm28,{rd-sae}
    vdivps zmm30,zmm29,zmm28,{rz-sae}
    vdivps zmm30,zmm29,zmmword ptr [rcx]
    vdivps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vdivps zmm30,zmm29,dword ptr [rcx]{1to16}
    vdivps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vdivps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vdivps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vdivps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vdivps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vdivps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vdivps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vdivps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vdivsd xmm30{k7},xmm29,xmm28
    vdivsd xmm30{k7}{z},xmm29,xmm28
    vdivsd xmm30{k7},xmm29,xmm28,{rn-sae}
    vdivsd xmm30{k7},xmm29,xmm28,{ru-sae}
    vdivsd xmm30{k7},xmm29,xmm28,{rd-sae}
    vdivsd xmm30{k7},xmm29,xmm28,{rz-sae}
    vdivsd xmm30{k7},xmm29,qword ptr [rcx]
    vdivsd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vdivsd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vdivsd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vdivsd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vdivsd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vdivss xmm30{k7},xmm29,xmm28
    vdivss xmm30{k7}{z},xmm29,xmm28
    vdivss xmm30{k7},xmm29,xmm28,{rn-sae}
    vdivss xmm30{k7},xmm29,xmm28,{ru-sae}
    vdivss xmm30{k7},xmm29,xmm28,{rd-sae}
    vdivss xmm30{k7},xmm29,xmm28,{rz-sae}
    vdivss xmm30{k7},xmm29,dword ptr [rcx]
    vdivss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vdivss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vdivss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vdivss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vdivss xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vmaxpd xmm1,xmm2,xmm3
    vmaxps xmm1,xmm2,xmm3
    vmaxsd xmm1,xmm2,xmm3
    vmaxss xmm1,xmm2,xmm3
    vmaxpd xmm1{k1}{z},xmm2,xmm3
    vmaxps xmm1{k1}{z},xmm2,xmm3
    vmaxsd xmm1{k1}{z},xmm2,xmm3
    vmaxss xmm1{k1}{z},xmm2,xmm3
    vmaxpd ymm1,ymm2,ymm3
    vmaxps ymm1,ymm2,ymm3
    vmaxpd ymm1{k1}{z},ymm2,ymm3
    vmaxps ymm1{k1}{z},ymm2,ymm3
    vmaxpd zmm1,zmm2,zmm3
    vmaxps zmm1,zmm2,zmm3
    vmaxpd zmm1{k1}{z},zmm2,zmm3
    vmaxps zmm1{k1}{z},zmm2,zmm3
    vmaxpd xmm1,xmm2,[rax]
    vmaxps xmm1,xmm2,[rax]
    vmaxsd xmm1,xmm2,[rax]
    vmaxss xmm1,xmm2,[rax]
    vmaxpd xmm1{k1}{z},xmm2,[rax]
    vmaxps xmm1{k1}{z},xmm2,[rax]
    vmaxsd xmm1{k1}{z},xmm2,[rax]
    vmaxss xmm1{k1}{z},xmm2,[rax]
    vmaxpd ymm1,ymm2,[rax]
    vmaxps ymm1,ymm2,[rax]
    vmaxpd ymm1{k1}{z},ymm2,[rax]
    vmaxps ymm1{k1}{z},ymm2,[rax]
    vmaxpd zmm1,zmm2,[rax]
    vmaxps zmm1,zmm2,[rax]
    vmaxpd zmm1{k1}{z},zmm2,[rax]
    vmaxps zmm1{k1}{z},zmm2,[rax]

    vmaxpd zmm30,zmm29,zmm28
    vmaxpd zmm30{k7},zmm29,zmm28
    vmaxpd zmm30{k7}{z},zmm29,zmm28
    vmaxpd zmm30,zmm29,zmm28,{sae}
    vmaxpd zmm30,zmm29,zmmword ptr [rcx]
    vmaxpd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vmaxpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vmaxpd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vmaxpd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vmaxpd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vmaxpd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vmaxpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vmaxpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vmaxpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vmaxpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vmaxps zmm30,zmm29,zmm28
    vmaxps zmm30{k7},zmm29,zmm28
    vmaxps zmm30{k7}{z},zmm29,zmm28
    vmaxps zmm30,zmm29,zmm28,{sae}
    vmaxps zmm30,zmm29,zmmword ptr [rcx]
    vmaxps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vmaxps zmm30,zmm29,dword ptr [rcx]{1to16}
    vmaxps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vmaxps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vmaxps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vmaxps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vmaxps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vmaxps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vmaxps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vmaxps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vmaxsd xmm30{k7},xmm29,xmm28
    vmaxsd xmm30{k7}{z},xmm29,xmm28
    vmaxsd xmm30{k7},xmm29,xmm28,{sae}
    vmaxsd xmm30{k7},xmm29,qword ptr [rcx]
    vmaxsd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vmaxsd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vmaxsd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vmaxsd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vmaxsd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vmaxss xmm30{k7},xmm29,xmm28
    vmaxss xmm30{k7}{z},xmm29,xmm28
    vmaxss xmm30{k7},xmm29,xmm28,{sae}
    vmaxss xmm30{k7},xmm29,dword ptr [rcx]
    vmaxss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vmaxss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vmaxss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vmaxss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vmaxss xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vminpd xmm1,xmm2,xmm3
    vminps xmm1,xmm2,xmm3
    vminsd xmm1,xmm2,xmm3
    vminss xmm1,xmm2,xmm3
    vminpd xmm1{k1}{z},xmm2,xmm3
    vminps xmm1{k1}{z},xmm2,xmm3
    vminsd xmm1{k1}{z},xmm2,xmm3
    vminss xmm1{k1}{z},xmm2,xmm3
    vminpd ymm1,ymm2,ymm3
    vminps ymm1,ymm2,ymm3
    vminpd ymm1{k1}{z},ymm2,ymm3
    vminps ymm1{k1}{z},ymm2,ymm3
    vminpd zmm1,zmm2,zmm3
    vminps zmm1,zmm2,zmm3
    vminpd zmm1{k1}{z},zmm2,zmm3
    vminps zmm1{k1}{z},zmm2,zmm3
    vminpd xmm1,xmm2,[rax]
    vminps xmm1,xmm2,[rax]
    vminsd xmm1,xmm2,[rax]
    vminss xmm1,xmm2,[rax]
    vminpd xmm1{k1}{z},xmm2,[rax]
    vminps xmm1{k1}{z},xmm2,[rax]
    vminsd xmm1{k1}{z},xmm2,[rax]
    vminss xmm1{k1}{z},xmm2,[rax]
    vminpd ymm1,ymm2,[rax]
    vminps ymm1,ymm2,[rax]
    vminpd ymm1{k1}{z},ymm2,[rax]
    vminps ymm1{k1}{z},ymm2,[rax]
    vminpd zmm1,zmm2,[rax]
    vminps zmm1,zmm2,[rax]
    vminpd zmm1{k1}{z},zmm2,[rax]
    vminps zmm1{k1}{z},zmm2,[rax]

    vminpd zmm30,zmm29,zmm28
    vminpd zmm30{k7},zmm29,zmm28
    vminpd zmm30{k7}{z},zmm29,zmm28
    vminpd zmm30,zmm29,zmm28,{sae}
    vminpd zmm30,zmm29,zmmword ptr [rcx]
    vminpd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vminpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vminpd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vminpd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vminpd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vminpd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vminpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vminpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vminpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vminpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vminps zmm30,zmm29,zmm28
    vminps zmm30{k7},zmm29,zmm28
    vminps zmm30{k7}{z},zmm29,zmm28
    vminps zmm30,zmm29,zmm28,{sae}
    vminps zmm30,zmm29,zmmword ptr [rcx]
    vminps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vminps zmm30,zmm29,dword ptr [rcx]{1to16}
    vminps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vminps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vminps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vminps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vminps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vminps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vminps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vminps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vminsd xmm30{k7},xmm29,xmm28
    vminsd xmm30{k7}{z},xmm29,xmm28
    vminsd xmm30{k7},xmm29,xmm28,{sae}
    vminsd xmm30{k7},xmm29,qword ptr [rcx]
    vminsd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vminsd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vminsd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vminsd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vminsd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vminss xmm30{k7},xmm29,xmm28
    vminss xmm30{k7}{z},xmm29,xmm28
    vminss xmm30{k7},xmm29,xmm28,{sae}
    vminss xmm30{k7},xmm29,dword ptr [rcx]
    vminss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vminss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vminss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vminss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vminss xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vmulpd xmm1,xmm2,xmm3
    vmulps xmm1,xmm2,xmm3
    vmulsd xmm1,xmm2,xmm3
    vmulss xmm1,xmm2,xmm3
    vmulpd xmm1{k1}{z},xmm2,xmm3
    vmulps xmm1{k1}{z},xmm2,xmm3
    vmulsd xmm1{k1}{z},xmm2,xmm3
    vmulss xmm1{k1}{z},xmm2,xmm3
    vmulpd ymm1,ymm2,ymm3
    vmulps ymm1,ymm2,ymm3
    vmulpd ymm1{k1}{z},ymm2,ymm3
    vmulps ymm1{k1}{z},ymm2,ymm3
    vmulpd zmm1,zmm2,zmm3
    vmulps zmm1,zmm2,zmm3
    vmulpd zmm1{k1}{z},zmm2,zmm3
    vmulps zmm1{k1}{z},zmm2,zmm3
    vmulpd xmm1,xmm2,[rax]
    vmulps xmm1,xmm2,[rax]
    vmulsd xmm1,xmm2,[rax]
    vmulss xmm1,xmm2,[rax]
    vmulpd xmm1{k1}{z},xmm2,[rax]
    vmulps xmm1{k1}{z},xmm2,[rax]
    vmulsd xmm1{k1}{z},xmm2,[rax]
    vmulss xmm1{k1}{z},xmm2,[rax]
    vmulpd ymm1,ymm2,[rax]
    vmulps ymm1,ymm2,[rax]
    vmulpd ymm1{k1}{z},ymm2,[rax]
    vmulps ymm1{k1}{z},ymm2,[rax]
    vmulpd zmm1,zmm2,[rax]
    vmulps zmm1,zmm2,[rax]
    vmulpd zmm1{k1}{z},zmm2,[rax]
    vmulps zmm1{k1}{z},zmm2,[rax]

    vmulpd zmm30,zmm29,zmm28
    vmulpd zmm30{k7},zmm29,zmm28
    vmulpd zmm30{k7}{z},zmm29,zmm28
    vmulpd zmm30,zmm29,zmm28,{rn-sae}
    vmulpd zmm30,zmm29,zmm28,{ru-sae}
    vmulpd zmm30,zmm29,zmm28,{rd-sae}
    vmulpd zmm30,zmm29,zmm28,{rz-sae}
    vmulpd zmm30,zmm29,zmmword ptr [rcx]
    vmulpd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vmulpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vmulpd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vmulpd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vmulpd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vmulpd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vmulpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vmulpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vmulpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vmulpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vmulps zmm30,zmm29,zmm28
    vmulps zmm30{k7},zmm29,zmm28
    vmulps zmm30{k7}{z},zmm29,zmm28
    vmulps zmm30,zmm29,zmm28,{rn-sae}
    vmulps zmm30,zmm29,zmm28,{ru-sae}
    vmulps zmm30,zmm29,zmm28,{rd-sae}
    vmulps zmm30,zmm29,zmm28,{rz-sae}
    vmulps zmm30,zmm29,zmmword ptr [rcx]
    vmulps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vmulps zmm30,zmm29,dword ptr [rcx]{1to16}
    vmulps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vmulps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vmulps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vmulps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vmulps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vmulps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vmulps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vmulps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vmulsd xmm30{k7},xmm29,xmm28
    vmulsd xmm30{k7}{z},xmm29,xmm28
    vmulsd xmm30{k7},xmm29,xmm28,{rn-sae}
    vmulsd xmm30{k7},xmm29,xmm28,{ru-sae}
    vmulsd xmm30{k7},xmm29,xmm28,{rd-sae}
    vmulsd xmm30{k7},xmm29,xmm28,{rz-sae}
    vmulsd xmm30{k7},xmm29,qword ptr [rcx]
    vmulsd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vmulsd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vmulsd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vmulsd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vmulsd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vmulss xmm30{k7},xmm29,xmm28
    vmulss xmm30{k7}{z},xmm29,xmm28
    vmulss xmm30{k7},xmm29,xmm28,{rn-sae}
    vmulss xmm30{k7},xmm29,xmm28,{ru-sae}
    vmulss xmm30{k7},xmm29,xmm28,{rd-sae}
    vmulss xmm30{k7},xmm29,xmm28,{rz-sae}
    vmulss xmm30{k7},xmm29,dword ptr [rcx]
    vmulss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vmulss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vmulss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vmulss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vmulss xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vsubpd xmm1,xmm2,xmm3
    vsubps xmm1,xmm2,xmm3
    vsubsd xmm1,xmm2,xmm3
    vsubss xmm1,xmm2,xmm3
    vsubpd xmm1{k1}{z},xmm2,xmm3
    vsubps xmm1{k1}{z},xmm2,xmm3
    vsubsd xmm1{k1}{z},xmm2,xmm3
    vsubss xmm1{k1}{z},xmm2,xmm3
    vsubpd ymm1,ymm2,ymm3
    vsubps ymm1,ymm2,ymm3
    vsubpd ymm1{k1}{z},ymm2,ymm3
    vsubps ymm1{k1}{z},ymm2,ymm3
    vsubpd zmm1,zmm2,zmm3
    vsubps zmm1,zmm2,zmm3
    vsubpd zmm1{k1}{z},zmm2,zmm3
    vsubps zmm1{k1}{z},zmm2,zmm3
    vsubpd xmm1,xmm2,[rax]
    vsubps xmm1,xmm2,[rax]
    vsubsd xmm1,xmm2,[rax]
    vsubss xmm1,xmm2,[rax]
    vsubpd xmm1{k1}{z},xmm2,[rax]
    vsubps xmm1{k1}{z},xmm2,[rax]
    vsubsd xmm1{k1}{z},xmm2,[rax]
    vsubss xmm1{k1}{z},xmm2,[rax]
    vsubpd ymm1,ymm2,[rax]
    vsubps ymm1,ymm2,[rax]
    vsubpd ymm1{k1}{z},ymm2,[rax]
    vsubps ymm1{k1}{z},ymm2,[rax]
    vsubpd zmm1,zmm2,[rax]
    vsubps zmm1,zmm2,[rax]
    vsubpd zmm1{k1}{z},zmm2,[rax]
    vsubps zmm1{k1}{z},zmm2,[rax]

    vsubpd zmm30,zmm29,zmm28
    vsubpd zmm30{k7},zmm29,zmm28
    vsubpd zmm30{k7}{z},zmm29,zmm28
    vsubpd zmm30,zmm29,zmm28,{rn-sae}
    vsubpd zmm30,zmm29,zmm28,{ru-sae}
    vsubpd zmm30,zmm29,zmm28,{rd-sae}
    vsubpd zmm30,zmm29,zmm28,{rz-sae}
    vsubpd zmm30,zmm29,zmmword ptr [rcx]
    vsubpd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vsubpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vsubpd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vsubpd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vsubpd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vsubpd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vsubpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vsubpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vsubpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vsubpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vsubps zmm30,zmm29,zmm28
    vsubps zmm30{k7},zmm29,zmm28
    vsubps zmm30{k7}{z},zmm29,zmm28
    vsubps zmm30,zmm29,zmm28,{rn-sae}
    vsubps zmm30,zmm29,zmm28,{ru-sae}
    vsubps zmm30,zmm29,zmm28,{rd-sae}
    vsubps zmm30,zmm29,zmm28,{rz-sae}
    vsubps zmm30,zmm29,zmmword ptr [rcx]
    vsubps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vsubps zmm30,zmm29,dword ptr [rcx]{1to16}
    vsubps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vsubps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vsubps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vsubps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vsubps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vsubps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vsubps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vsubps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vsubsd xmm30{k7},xmm29,xmm28
    vsubsd xmm30{k7}{z},xmm29,xmm28
    vsubsd xmm30{k7},xmm29,xmm28,{rn-sae}
    vsubsd xmm30{k7},xmm29,xmm28,{ru-sae}
    vsubsd xmm30{k7},xmm29,xmm28,{rd-sae}
    vsubsd xmm30{k7},xmm29,xmm28,{rz-sae}
    vsubsd xmm30{k7},xmm29,qword ptr [rcx]
    vsubsd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vsubsd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vsubsd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vsubsd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vsubsd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vsubss xmm30{k7},xmm29,xmm28
    vsubss xmm30{k7}{z},xmm29,xmm28
    vsubss xmm30{k7},xmm29,xmm28,{rn-sae}
    vsubss xmm30{k7},xmm29,xmm28,{ru-sae}
    vsubss xmm30{k7},xmm29,xmm28,{rd-sae}
    vsubss xmm30{k7},xmm29,xmm28,{rz-sae}
    vsubss xmm30{k7},xmm29,dword ptr [rcx]
    vsubss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vsubss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vsubss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vsubss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vsubss xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vsqrtpd xmm1,xmm2
    vsqrtps xmm1,xmm2
    vsqrtsd xmm1,xmm2,xmm3
    vsqrtss xmm1,xmm2,xmm3
    vsqrtpd xmm1{k1}{z},xmm2
    vsqrtps xmm1{k1}{z},xmm2
    vsqrtsd xmm1{k1}{z},xmm2,xmm3
    vsqrtss xmm1{k1}{z},xmm2,xmm3
    vsqrtpd ymm1,ymm2
    vsqrtps ymm1,ymm2
    vsqrtpd ymm1{k1}{z},ymm2
    vsqrtps ymm1{k1}{z},ymm2
    vsqrtpd zmm1,zmm2
    vsqrtps zmm1,zmm2
    vsqrtpd zmm1{k1}{z},zmm2
    vsqrtps zmm1{k1}{z},zmm2
    vsqrtpd xmm1,[rax]
    vsqrtps xmm1,[rax]
    vsqrtsd xmm1,xmm3,[rax]
    vsqrtss xmm1,xmm3,[rax]
    vsqrtpd xmm1{k1}{z},[rax]
    vsqrtps xmm1{k1}{z},[rax]
    vsqrtsd xmm1{k1}{z},xmm2,[rax]
    vsqrtss xmm1{k1}{z},xmm2,[rax]
    vsqrtpd ymm1,[rax]
    vsqrtps ymm1,[rax]
    vsqrtpd ymm1{k1}{z},[rax]
    vsqrtps ymm1{k1}{z},[rax]
    vsqrtpd zmm1,[rax]
    vsqrtps zmm1,[rax]
    vsqrtpd zmm1{k1}{z},[rax]
    vsqrtps zmm1{k1}{z},[rax]

    vsqrtpd zmm30,zmm29
    vsqrtpd zmm30{k7},zmm29
    vsqrtpd zmm30{k7}{z},zmm29
    vsqrtpd zmm30,zmm29,{rn-sae}
    vsqrtpd zmm30,zmm29,{ru-sae}
    vsqrtpd zmm30,zmm29,{rd-sae}
    vsqrtpd zmm30,zmm29,{rz-sae}
    vsqrtpd zmm30,zmmword ptr [rcx]
    vsqrtpd zmm30,zmmword ptr [rax+r14*8+0x123]
    vsqrtpd zmm30,qword ptr [rcx]{1to8}
    vsqrtpd zmm30,zmmword ptr [rdx+0x1fc0]
    vsqrtpd zmm30,zmmword ptr [rdx+0x2000]
    vsqrtpd zmm30,zmmword ptr [rdx-0x2000]
    vsqrtpd zmm30,zmmword ptr [rdx-0x2040]
    vsqrtpd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vsqrtpd zmm30,qword ptr [rdx+0x400]{1to8}
    vsqrtpd zmm30,qword ptr [rdx-0x400]{1to8}
    vsqrtpd zmm30,qword ptr [rdx-0x408]{1to8}
    vsqrtps zmm30,zmm29
    vsqrtps zmm30{k7},zmm29
    vsqrtps zmm30{k7}{z},zmm29
    vsqrtps zmm30,zmm29,{rn-sae}
    vsqrtps zmm30,zmm29,{ru-sae}
    vsqrtps zmm30,zmm29,{rd-sae}
    vsqrtps zmm30,zmm29,{rz-sae}
    vsqrtps zmm30,zmmword ptr [rcx]
    vsqrtps zmm30,zmmword ptr [rax+r14*8+0x123]
    vsqrtps zmm30,dword ptr [rcx]{1to16}
    vsqrtps zmm30,zmmword ptr [rdx+0x1fc0]
    vsqrtps zmm30,zmmword ptr [rdx+0x2000]
    vsqrtps zmm30,zmmword ptr [rdx-0x2000]
    vsqrtps zmm30,zmmword ptr [rdx-0x2040]
    vsqrtps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vsqrtps zmm30,dword ptr [rdx+0x200]{1to16}
    vsqrtps zmm30,dword ptr [rdx-0x200]{1to16}
    vsqrtps zmm30,dword ptr [rdx-0x204]{1to16}
    vsqrtsd xmm30{k7},xmm29,xmm28
    vsqrtsd xmm30{k7}{z},xmm29,xmm28
    vsqrtsd xmm30{k7},xmm29,xmm28,{rn-sae}
    vsqrtsd xmm30{k7},xmm29,xmm28,{ru-sae}
    vsqrtsd xmm30{k7},xmm29,xmm28,{rd-sae}
    vsqrtsd xmm30{k7},xmm29,xmm28,{rz-sae}
    vsqrtsd xmm30{k7},xmm29,qword ptr [rcx]
    vsqrtsd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vsqrtsd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vsqrtsd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vsqrtsd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vsqrtsd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vsqrtss xmm30{k7},xmm29,xmm28
    vsqrtss xmm30{k7}{z},xmm29,xmm28
    vsqrtss xmm30{k7},xmm29,xmm28,{rn-sae}
    vsqrtss xmm30{k7},xmm29,xmm28,{ru-sae}
    vsqrtss xmm30{k7},xmm29,xmm28,{rd-sae}
    vsqrtss xmm30{k7},xmm29,xmm28,{rz-sae}
    vsqrtss xmm30{k7},xmm29,dword ptr [rcx]
    vsqrtss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vsqrtss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vsqrtss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vsqrtss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vsqrtss xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vcmppd xmm1,xmm2,xmm3,7
    vcmpps xmm1,xmm2,xmm3,7
    vcmpsd xmm1,xmm2,xmm3,7
    vcmpss xmm1,xmm2,xmm3,7
    vcmppd ymm1,ymm2,ymm3,7
    vcmpps ymm1,ymm2,ymm3,7
    vcmppd xmm1,xmm2,[rax],7
    vcmpps xmm1,xmm2,[rax],7
    vcmpsd xmm1,xmm2,[rax],7
    vcmpss xmm1,xmm2,[rax],7
    vcmppd ymm1,ymm2,[rax],7
    vcmpps ymm1,ymm2,[rax],7

    vcmppd k1{k2},xmm2,xmm3,7
    vcmpps k1{k2},xmm2,xmm3,7
    vcmpsd k1{k2},xmm2,xmm3,7
    vcmpss k1{k2},xmm2,xmm3,7
    vcmppd k1{k2},ymm2,ymm3,7
    vcmpps k1{k2},ymm2,ymm3,7

    vcmppd k1{k2},xmm2,[rax],7
    vcmpps k1{k2},xmm2,[rax],7
    vcmpsd k1{k2},xmm2,[rax],7
    vcmpss k1{k2},xmm2,[rax],7

    vcmppd k1{k2},zmm2,zmm3,7
    vcmpps k1{k2},zmm2,zmm3,7
    vcmppd k1{k2},ymm2,[rax],7
    vcmpps k1{k2},ymm2,[rax],7
    vcmppd k1{k2},zmm2,[rax],7
    vcmpps k1{k2},zmm2,[rax],7

    vcmppd k5,zmm30,zmm29,0xab
    vcmppd k5{k7},zmm30,zmm29,0xab
    vcmppd k5,zmm30,zmm29,{sae},0xab
    vcmppd k5,zmm30,zmm29,0x7b
    vcmppd k5,zmm30,zmm29,{sae},0x7b
    vcmppd k5,zmm30,zmmword ptr [rcx],0x7b
    vcmppd k5,zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vcmppd k5,zmm30,qword ptr [rcx]{1to8},0x7b
    vcmppd k5,zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vcmppd k5,zmm30,zmmword ptr [rdx+0x2000],0x7b
    vcmppd k5,zmm30,zmmword ptr [rdx-0x2000],0x7b
    vcmppd k5,zmm30,zmmword ptr [rdx-0x2040],0x7b
    vcmppd k5,zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vcmppd k5,zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vcmppd k5,zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vcmppd k5,zmm30,qword ptr [rdx-0x408]{1to8},0x7b
    vcmpps k5,zmm30,zmm29,0xab
    vcmpps k5{k7},zmm30,zmm29,0xab
    vcmpps k5,zmm30,zmm29,{sae},0xab
    vcmpps k5,zmm30,zmm29,0x7b
    vcmpps k5,zmm30,zmm29,{sae},0x7b
    vcmpps k5,zmm30,zmmword ptr [rcx],0x7b
    vcmpps k5,zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vcmpps k5,zmm30,dword ptr [rcx]{1to16},0x7b
    vcmpps k5,zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vcmpps k5,zmm30,zmmword ptr [rdx+0x2000],0x7b
    vcmpps k5,zmm30,zmmword ptr [rdx-0x2000],0x7b
    vcmpps k5,zmm30,zmmword ptr [rdx-0x2040],0x7b
    vcmpps k5,zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vcmpps k5,zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vcmpps k5,zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vcmpps k5,zmm30,dword ptr [rdx-0x204]{1to16},0x7b
    vcmpsd k5{k7},xmm29,xmm28,0xab
    vcmpsd k5{k7},xmm29,xmm28,{sae},0xab
    vcmpsd k5{k7},xmm29,xmm28,0x7b
    vcmpsd k5{k7},xmm29,xmm28,{sae},0x7b
    vcmpsd k5{k7},xmm29,qword ptr [rcx],0x7b
    vcmpsd k5{k7},xmm29,qword ptr [rax+r14*8+0x123],0x7b
    vcmpsd k5{k7},xmm29,qword ptr [rdx+0x3f8],0x7b
    vcmpsd k5{k7},xmm29,qword ptr [rdx+0x400],0x7b
    vcmpsd k5{k7},xmm29,qword ptr [rdx-0x400],0x7b
    vcmpsd k5{k7},xmm29,qword ptr [rdx-0x408],0x7b
    vcmpss k5{k7},xmm29,xmm28,0xab
    vcmpss k5{k7},xmm29,xmm28,{sae},0xab
    vcmpss k5{k7},xmm29,xmm28,0x7b
    vcmpss k5{k7},xmm29,xmm28,{sae},0x7b
    vcmpss k5{k7},xmm29,dword ptr [rcx],0x7b
    vcmpss k5{k7},xmm29,dword ptr [rax+r14*8+0x123],0x7b
    vcmpss k5{k7},xmm29,dword ptr [rdx+0x1fc],0x7b
    vcmpss k5{k7},xmm29,dword ptr [rdx+0x200],0x7b
    vcmpss k5{k7},xmm29,dword ptr [rdx-0x200],0x7b
    vcmpss k5{k7},xmm29,dword ptr [rdx-0x204],0x7b

    vandpd xmm1{k2}{z},xmm2,xmm3
    vandpd ymm1{k2}{z},ymm2,ymm3
    vandpd zmm1{k2}{z},zmm2,zmm3
    vandpd xmm1{k2}{z},xmm2,[rax]
    vandpd ymm1{k2}{z},ymm2,[rax]
    vandpd zmm1{k2}{z},zmm2,[rax]

    vandps xmm1{k2}{z},xmm2,xmm3
    vandps ymm1{k2}{z},ymm2,ymm3
    vandps zmm1{k2}{z},zmm2,zmm3
    vandps xmm1{k2}{z},xmm2,[rax]
    vandps ymm1{k2}{z},ymm2,[rax]
    vandps zmm1{k2}{z},zmm2,[rax]

    vandnpd xmm1{k2}{z},xmm2,xmm3
    vandnpd ymm1{k2}{z},ymm2,ymm3
    vandnpd zmm1{k2}{z},zmm2,zmm3
    vandnpd xmm1{k2}{z},xmm2,[rax]
    vandnpd ymm1{k2}{z},ymm2,[rax]
    vandnpd zmm1{k2}{z},zmm2,[rax]

    vandnps xmm1{k2}{z},xmm2,xmm3
    vandnps ymm1{k2}{z},ymm2,ymm3
    vandnps zmm1{k2}{z},zmm2,zmm3
    vandnps xmm1{k2}{z},xmm2,[rax]
    vandnps ymm1{k2}{z},ymm2,[rax]
    vandnps zmm1{k2}{z},zmm2,[rax]

    vandpd xmm20,xmm1,xmm2
    vandpd ymm20,ymm1,ymm2
    vandps xmm20,xmm1,xmm2
    vandps ymm20,ymm1,ymm2

    vandnpd xmm20,xmm1,xmm2
    vandnpd ymm20,ymm1,ymm2
    vandnps xmm20,xmm1,xmm2
    vandnps ymm20,ymm1,ymm2

    vorpd xmm1{k2}{z},xmm2,xmm3
    vorpd ymm1{k2}{z},ymm2,ymm3
    vorpd zmm1{k2}{z},zmm2,zmm3
    vorpd xmm1{k2}{z},xmm2,[rax]
    vorpd ymm1{k2}{z},ymm2,[rax]
    vorpd zmm1{k2}{z},zmm2,[rax]

    vorps xmm1{k2}{z},xmm2,xmm3
    vorps ymm1{k2}{z},ymm2,ymm3
    vorps zmm1{k2}{z},zmm2,zmm3
    vorps xmm1{k2}{z},xmm2,[rax]
    vorps ymm1{k2}{z},ymm2,[rax]
    vorps zmm1{k2}{z},zmm2,[rax]

    vxorpd xmm1{k2}{z},xmm2,xmm3
    vxorpd ymm1{k2}{z},ymm2,ymm3
    vxorpd zmm1{k2}{z},zmm2,zmm3
    vxorpd xmm1{k2}{z},xmm2,[rax]
    vxorpd ymm1{k2}{z},ymm2,[rax]
    vxorpd zmm1{k2}{z},zmm2,[rax]

    vxorps xmm1{k2}{z},xmm2,xmm3
    vxorps ymm1{k2}{z},ymm2,ymm3
    vxorps zmm1{k2}{z},zmm2,zmm3
    vxorps xmm1{k2}{z},xmm2,[rax]
    vxorps ymm1{k2}{z},ymm2,[rax]
    vxorps zmm1{k2}{z},zmm2,[rax]

    vcvtdq2pd zmm1{k1}{z},ymm2
    vcvtdq2ps zmm1{k1}{z},zmm2

    vcvtdq2pd xmm20,xmm1
    vcvtdq2pd xmm20,[rax]
    vcvtdq2pd ymm20,xmm1
    vcvtdq2pd ymm20,[rax]
    vcvtdq2pd zmm30{k7},ymm29
    vcvtdq2pd zmm30{k7}{z},ymm29
    vcvtdq2pd zmm30{k7},ymmword ptr [rcx]
    vcvtdq2pd zmm30{k7},ymmword ptr [rax+r14*8+0x123]
    vcvtdq2pd zmm30{k7},dword ptr [rcx]{1to8}
    vcvtdq2pd zmm30{k7},ymmword ptr [rdx+0xfe0]
    vcvtdq2pd zmm30{k7},ymmword ptr [rdx+0x1000]
    vcvtdq2pd zmm30{k7},ymmword ptr [rdx-0x1000]
    vcvtdq2pd zmm30{k7},ymmword ptr [rdx-0x1020]
    vcvtdq2pd zmm30{k7},dword ptr [rdx+0x1fc]{1to8}
    vcvtdq2pd zmm30{k7},dword ptr [rdx+0x200]{1to8}
    vcvtdq2pd zmm30{k7},dword ptr [rdx-0x200]{1to8}
    vcvtdq2pd zmm30{k7},dword ptr [rdx-0x204]{1to8}

    vcvtdq2ps xmm20,xmm1
    vcvtdq2ps xmm20,[rax]
    vcvtdq2ps ymm20,ymm1
    vcvtdq2ps ymm20,[rax]
    vcvtdq2ps zmm30,zmm29
    vcvtdq2ps zmm30{k7},zmm29
    vcvtdq2ps zmm30{k7}{z},zmm29
    vcvtdq2ps zmm30,zmm29,{rn-sae}
    vcvtdq2ps zmm30,zmm29,{ru-sae}
    vcvtdq2ps zmm30,zmm29,{rd-sae}
    vcvtdq2ps zmm30,zmm29,{rz-sae}
    vcvtdq2ps zmm30,zmmword ptr [rcx]
    vcvtdq2ps zmm30,zmmword ptr [rax+r14*8+0x123]
    vcvtdq2ps zmm30,dword ptr [rcx]{1to16}
    vcvtdq2ps zmm30,zmmword ptr [rdx+0x1fc0]
    vcvtdq2ps zmm30,zmmword ptr [rdx+0x2000]
    vcvtdq2ps zmm30,zmmword ptr [rdx-0x2000]
    vcvtdq2ps zmm30,zmmword ptr [rdx-0x2040]
    vcvtdq2ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vcvtdq2ps zmm30,dword ptr [rdx+0x200]{1to16}
    vcvtdq2ps zmm30,dword ptr [rdx-0x200]{1to16}
    vcvtdq2ps zmm30,dword ptr [rdx-0x204]{1to16}

    vcvtpd2dq xmm20,xmm1
    vcvtpd2dq xmm20,oword ptr [rax]
    vcvtpd2dq xmm20,ymm1
    vcvtpd2dq xmm20,ymmword ptr [rax]
    vcvtpd2dq ymm30{k7},zmm29
    vcvtpd2dq ymm30{k7}{z},zmm29
    vcvtpd2dq ymm30{k7},zmm29,{rn-sae}
    vcvtpd2dq ymm30{k7},zmm29,{ru-sae}
    vcvtpd2dq ymm30{k7},zmm29,{rd-sae}
    vcvtpd2dq ymm30{k7},zmm29,{rz-sae}
    vcvtpd2dq ymm30{k7},zmmword ptr [rcx]
    vcvtpd2dq ymm30{k7},zmmword ptr [rax+r14*8+0x123]
    vcvtpd2dq ymm30{k7},qword ptr [rcx]{1to8}
    vcvtpd2dq ymm30{k7},zmmword ptr [rdx+0x1fc0]
    vcvtpd2dq ymm30{k7},zmmword ptr [rdx+0x2000]
    vcvtpd2dq ymm30{k7},zmmword ptr [rdx-0x2000]
    vcvtpd2dq ymm30{k7},zmmword ptr [rdx-0x2040]
    vcvtpd2dq ymm30{k7},qword ptr [rdx+0x3f8]{1to8}
    vcvtpd2dq ymm30{k7},qword ptr [rdx+0x400]{1to8}
    vcvtpd2dq ymm30{k7},qword ptr [rdx-0x400]{1to8}
    vcvtpd2dq ymm30{k7},qword ptr [rdx-0x408]{1to8}

    vcvtpd2ps xmm20,xmm1
    vcvtpd2ps xmm20,oword ptr [rax]
    vcvtpd2ps xmm20,ymm1
    vcvtpd2ps xmm20,ymmword ptr [rax]
    vcvtpd2ps ymm30{k7},zmm29
    vcvtpd2ps ymm30{k7}{z},zmm29
    vcvtpd2ps ymm30{k7},zmm29,{rn-sae}
    vcvtpd2ps ymm30{k7},zmm29,{ru-sae}
    vcvtpd2ps ymm30{k7},zmm29,{rd-sae}
    vcvtpd2ps ymm30{k7},zmm29,{rz-sae}
    vcvtpd2ps ymm30{k7},zmmword ptr [rcx]
    vcvtpd2ps ymm30{k7},zmmword ptr [rax+r14*8+0x123]
    vcvtpd2ps ymm30{k7},qword ptr [rcx]{1to8}
    vcvtpd2ps ymm30{k7},zmmword ptr [rdx+0x1fc0]
    vcvtpd2ps ymm30{k7},zmmword ptr [rdx+0x2000]
    vcvtpd2ps ymm30{k7},zmmword ptr [rdx-0x2000]
    vcvtpd2ps ymm30{k7},zmmword ptr [rdx-0x2040]
    vcvtpd2ps ymm30{k7},qword ptr [rdx+0x3f8]{1to8}
    vcvtpd2ps ymm30{k7},qword ptr [rdx+0x400]{1to8}
    vcvtpd2ps ymm30{k7},qword ptr [rdx-0x400]{1to8}
    vcvtpd2ps ymm30{k7},qword ptr [rdx-0x408]{1to8}

    vcvtsd2si rax,xmm1
    vcvtsd2si eax,xmm21
    vcvtsd2si eax,[rax]
    vcvtsd2si eax,xmm30,{rn-sae}
    vcvtsd2si eax,xmm30,{ru-sae}
    vcvtsd2si eax,xmm30,{rd-sae}
    vcvtsd2si eax,xmm30,{rz-sae}
    vcvtsd2si ebp,xmm30,{rn-sae}
    vcvtsd2si ebp,xmm30,{ru-sae}
    vcvtsd2si ebp,xmm30,{rd-sae}
    vcvtsd2si ebp,xmm30,{rz-sae}
    vcvtsd2si r13d,xmm30,{rn-sae}
    vcvtsd2si r13d,xmm30,{ru-sae}
    vcvtsd2si r13d,xmm30,{rd-sae}
    vcvtsd2si r13d,xmm30,{rz-sae}
    vcvtsd2si rax,xmm30,{rn-sae}
    vcvtsd2si rax,xmm30,{ru-sae}
    vcvtsd2si rax,xmm30,{rd-sae}
    vcvtsd2si rax,xmm30,{rz-sae}
    vcvtsd2si r8,xmm30,{rn-sae}
    vcvtsd2si r8,xmm30,{ru-sae}
    vcvtsd2si r8,xmm30,{rd-sae}
    vcvtsd2si r8,xmm30,{rz-sae}

    vcvttsd2si eax,xmm21
    vcvttsd2si eax,[rax]
    vcvttsd2si rax,xmm1
    vcvttsd2si eax,xmm30,{sae}
    vcvttsd2si ebp,xmm30,{sae}
    vcvttsd2si r13d,xmm30,{sae}
    vcvttsd2si rax,xmm30,{sae}
    vcvttsd2si r8,xmm30,{sae}
    vcvttss2si eax,xmm30,{sae}
    vcvttss2si ebp,xmm30,{sae}
    vcvttss2si r13d,xmm30,{sae}
    vcvttss2si rax,xmm30,{sae}
    vcvttss2si r8,xmm30,{sae}

    vcvtsd2ss xmm1{k1}{z},xmm2,xmm3
    vcvtsd2ss xmm20,xmm1,xmm2
    vcvtsd2ss xmm20,xmm1,[rax]
    vcvtsd2ss xmm30{k7},xmm29,xmm28
    vcvtsd2ss xmm30{k7}{z},xmm29,xmm28
    vcvtsd2ss xmm30{k7},xmm29,xmm28,{rn-sae}
    vcvtsd2ss xmm30{k7},xmm29,xmm28,{ru-sae}
    vcvtsd2ss xmm30{k7},xmm29,xmm28,{rd-sae}
    vcvtsd2ss xmm30{k7},xmm29,xmm28,{rz-sae}
    vcvtsd2ss xmm30{k7},xmm29,qword ptr [rcx]
    vcvtsd2ss xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vcvtsd2ss xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vcvtsd2ss xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vcvtsd2ss xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vcvtsd2ss xmm30{k7},xmm29,qword ptr [rdx-0x408]

    vcvtsi2sd xmm1,xmm2,rax
    vcvtsi2sd xmm20,xmm1,eax
    vcvtsi2sd xmm30,xmm29,eax
    vcvtsi2sd xmm30,xmm29,ebp
    vcvtsi2sd xmm30,xmm29,r13d
    vcvtsi2sd xmm20,xmm1,dword ptr [rax]
    vcvtsi2sd xmm30,xmm29,dword ptr [rcx]
    vcvtsi2sd xmm30,xmm29,dword ptr [rax+r14*8+0x123]
    vcvtsi2sd xmm30,xmm29,dword ptr [rdx+0x1fc]
    vcvtsi2sd xmm30,xmm29,dword ptr [rdx+0x200]
    vcvtsi2sd xmm30,xmm29,dword ptr [rdx-0x200]
    vcvtsi2sd xmm30,xmm29,dword ptr [rdx-0x204]
    vcvtsi2sd xmm30,xmm29,rax
    vcvtsi2sd xmm30,xmm29,{rn-sae},rax
    vcvtsi2sd xmm30,xmm29,{ru-sae},rax
    vcvtsi2sd xmm30,xmm29,{rd-sae},rax
    vcvtsi2sd xmm30,xmm29,{rz-sae},rax
    vcvtsi2sd xmm30,xmm29,r8
    vcvtsi2sd xmm30,xmm29,{rn-sae},r8
    vcvtsi2sd xmm30,xmm29,{ru-sae},r8
    vcvtsi2sd xmm30,xmm29,{rd-sae},r8
    vcvtsi2sd xmm30,xmm29,{rz-sae},r8
    vcvtsi2sd xmm30,xmm29,qword ptr [rcx]
    vcvtsi2sd xmm30,xmm29,qword ptr [rax+r14*8+0x123]
    vcvtsi2sd xmm30,xmm29,qword ptr [rdx+0x3f8]
    vcvtsi2sd xmm30,xmm29,qword ptr [rdx+0x400]
    vcvtsi2sd xmm30,xmm29,qword ptr [rdx-0x400]
    vcvtsi2sd xmm30,xmm29,qword ptr [rdx-0x408]

    vcvtsi2ss xmm1,xmm2,rax
    vcvtsi2ss xmm20,xmm1,eax
    vcvtsi2ss xmm30,xmm29,eax
    vcvtsi2ss xmm30,xmm29,{rn-sae},eax
    vcvtsi2ss xmm30,xmm29,{ru-sae},eax
    vcvtsi2ss xmm30,xmm29,{rd-sae},eax
    vcvtsi2ss xmm30,xmm29,{rz-sae},eax
    vcvtsi2ss xmm30,xmm29,ebp
    vcvtsi2ss xmm30,xmm29,{rn-sae},ebp
    vcvtsi2ss xmm30,xmm29,{ru-sae},ebp
    vcvtsi2ss xmm30,xmm29,{rd-sae},ebp
    vcvtsi2ss xmm30,xmm29,{rz-sae},ebp
    vcvtsi2ss xmm30,xmm29,r13d
    vcvtsi2ss xmm30,xmm29,{rn-sae},r13d
    vcvtsi2ss xmm30,xmm29,{ru-sae},r13d
    vcvtsi2ss xmm30,xmm29,{rd-sae},r13d
    vcvtsi2ss xmm30,xmm29,{rz-sae},r13d
    vcvtsi2ss xmm20,xmm1,dword ptr [rax]
    vcvtsi2ss xmm30,xmm29,dword ptr [rcx]
    vcvtsi2ss xmm30,xmm29,dword ptr [rax+r14*8+0x123]
    vcvtsi2ss xmm30,xmm29,dword ptr [rdx+0x1fc]
    vcvtsi2ss xmm30,xmm29,dword ptr [rdx+0x200]
    vcvtsi2ss xmm30,xmm29,dword ptr [rdx-0x200]
    vcvtsi2ss xmm30,xmm29,dword ptr [rdx-0x204]
    vcvtsi2ss xmm30,xmm29,rax
    vcvtsi2ss xmm30,xmm29,{rn-sae},rax
    vcvtsi2ss xmm30,xmm29,{ru-sae},rax
    vcvtsi2ss xmm30,xmm29,{rd-sae},rax
    vcvtsi2ss xmm30,xmm29,{rz-sae},rax
    vcvtsi2ss xmm30,xmm29,r8
    vcvtsi2ss xmm30,xmm29,{rn-sae},r8
    vcvtsi2ss xmm30,xmm29,{ru-sae},r8
    vcvtsi2ss xmm30,xmm29,{rd-sae},r8
    vcvtsi2ss xmm30,xmm29,{rz-sae},r8
    vcvtsi2ss xmm30,xmm29,qword ptr [rcx]
    vcvtsi2ss xmm30,xmm29,qword ptr [rax+r14*8+0x123]
    vcvtsi2ss xmm30,xmm29,qword ptr [rdx+0x3f8]
    vcvtsi2ss xmm30,xmm29,qword ptr [rdx+0x400]
    vcvtsi2ss xmm30,xmm29,qword ptr [rdx-0x400]
    vcvtsi2ss xmm30,xmm29,qword ptr [rdx-0x408]

    vcvtss2sd xmm1 {k1}{z},xmm2,xmm3
    vcvtss2sd xmm20,xmm1,xmm2
    vcvtss2sd xmm20,xmm1,dword ptr [rax]
    vcvtss2sd xmm30{k7},xmm29,xmm28
    vcvtss2sd xmm30{k7}{z},xmm29,xmm28
    vcvtss2sd xmm30{k7},xmm29,xmm28,{sae}
    vcvtss2sd xmm30{k7},xmm29,dword ptr [rcx]
    vcvtss2sd xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vcvtss2sd xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vcvtss2sd xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vcvtss2sd xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vcvtss2sd xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vcvtss2si rax,xmm1
    vcvtss2si eax,xmm21
    vcvtss2si eax,[rax]
    vcvtss2si eax,xmm30,{rn-sae}
    vcvtss2si eax,xmm30,{ru-sae}
    vcvtss2si eax,xmm30,{rd-sae}
    vcvtss2si eax,xmm30,{rz-sae}
    vcvtss2si ebp,xmm30,{rn-sae}
    vcvtss2si ebp,xmm30,{ru-sae}
    vcvtss2si ebp,xmm30,{rd-sae}
    vcvtss2si ebp,xmm30,{rz-sae}
    vcvtss2si r13d,xmm30,{rn-sae}
    vcvtss2si r13d,xmm30,{ru-sae}
    vcvtss2si r13d,xmm30,{rd-sae}
    vcvtss2si r13d,xmm30,{rz-sae}
    vcvtss2si rax,xmm30,{rn-sae}
    vcvtss2si rax,xmm30,{ru-sae}
    vcvtss2si rax,xmm30,{rd-sae}
    vcvtss2si rax,xmm30,{rz-sae}
    vcvtss2si r8,xmm30,{rn-sae}
    vcvtss2si r8,xmm30,{ru-sae}
    vcvtss2si r8,xmm30,{rd-sae}
    vcvtss2si r8,xmm30,{rz-sae}

    vcvttss2si rax,xmm1
    vcvttss2si eax,xmm21
    vcvttss2si eax,[rax]

    vextractps eax,xmm1,7
    vextractps eax,xmm21,1
    vextractps rax,xmm29,0xab
    vextractps rax,xmm29,0x7b
    vextractps r8,xmm29,0x7b
    vextractps [rax],xmm21,1
    vextractps dword ptr [rcx],xmm29,0x7b
    vextractps dword ptr [rax+r14*8+0x123],xmm29,0x7b
    vextractps dword ptr [rdx+0x1fc],xmm29,0x7b
    vextractps dword ptr [rdx+0x200],xmm29,0x7b
    vextractps dword ptr [rdx-0x200],xmm29,0x7b
    vextractps dword ptr [rdx-0x204],xmm29,0x7b

    vinsertps xmm1,xmm2,xmm3,7
    vinsertps xmm20,xmm1,xmm3,0
    vinsertps xmm30,xmm29,xmm28,0xab
    vinsertps xmm30,xmm29,xmm28,0x7b
    vinsertps xmm20,xmm1,[rax],1
    vinsertps xmm30,xmm29,dword ptr [rcx],0x7b
    vinsertps xmm30,xmm29,dword ptr [rax+r14*8+0x123],0x7b
    vinsertps xmm30,xmm29,dword ptr [rdx+0x1fc],0x7b
    vinsertps xmm30,xmm29,dword ptr [rdx+0x200],0x7b
    vinsertps xmm30,xmm29,dword ptr [rdx-0x200],0x7b
    vinsertps xmm30,xmm29,dword ptr [rdx-0x204],0x7b

    vmovapd xmm20,xmm1
    vmovapd xmm20,oword ptr [rax]
    vmovapd oword ptr [rax],xmm21
    vmovapd ymm20,ymm1
    vmovapd ymm20,ymmword ptr [rax]
    vmovapd ymmword ptr [rax],ymm21
    vmovapd zmm2{k1}{z},zmm1
    vmovapd zmm30,zmm29
    vmovapd zmm30{k7},zmm29
    vmovapd zmm30{k7}{z},zmm29
    vmovapd zmm30,zmmword ptr [rcx]
    vmovapd zmm30,zmmword ptr [rax+r14*8+0x123]
    vmovapd zmm30,zmmword ptr [rdx+0x1fc0]
    vmovapd zmm30,zmmword ptr [rdx+0x2000]
    vmovapd zmm30,zmmword ptr [rdx-0x2000]
    vmovapd zmm30,zmmword ptr [rdx-0x2040]

    vmovaps xmm20,xmm1
    vmovaps xmm20,oword ptr [rax]
    vmovaps oword ptr [rax],xmm21
    vmovaps ymm20,ymm1
    vmovaps ymm20,ymmword ptr [rax]
    vmovaps ymmword ptr [rax],ymm21
    vmovaps zmm2{k1}{z},zmm1
    vmovaps zmm30,zmm29
    vmovaps zmm30{k7},zmm29
    vmovaps zmm30{k7}{z},zmm29
    vmovaps zmm30,zmmword ptr [rcx]
    vmovaps zmm30,zmmword ptr [rax+r14*8+0x123]
    vmovaps zmm30,zmmword ptr [rdx+0x1fc0]
    vmovaps zmm30,zmmword ptr [rdx+0x2000]
    vmovaps zmm30,zmmword ptr [rdx-0x2000]
    vmovaps zmm30,zmmword ptr [rdx-0x2040]

    vmovapd zmmword ptr [rcx],zmm30
    vmovapd zmmword ptr [rcx]{k7},zmm30
    vmovapd zmmword ptr [rax+r14*8+0x123],zmm30
    vmovapd zmmword ptr [rdx+0x1fc0],zmm30
    vmovapd zmmword ptr [rdx+0x2000],zmm30
    vmovapd zmmword ptr [rdx-0x2000],zmm30
    vmovapd zmmword ptr [rdx-0x2040],zmm30
    vmovaps zmmword ptr [rcx],zmm30
    vmovaps zmmword ptr [rcx]{k7},zmm30
    vmovaps zmmword ptr [rax+r14*8+0x123],zmm30
    vmovaps zmmword ptr [rdx+0x1fc0],zmm30
    vmovaps zmmword ptr [rdx+0x2000],zmm30
    vmovaps zmmword ptr [rdx-0x2000],zmm30
    vmovaps zmmword ptr [rdx-0x2040],zmm30

    vmovhlps xmm1,xmm2,xmm3
    vmovhlps xmm20,xmm1,xmm2
    vmovhlps xmm30,xmm29,xmm28

    vmovlhps xmm1,xmm2,xmm3
    vmovlhps xmm20,xmm1,xmm2
    vmovlhps xmm30,xmm29,xmm28

    vmovsd xmm1{k1}{z},xmm2,xmm3
    vmovsd xmm30{k7},qword ptr [rcx]
    vmovsd xmm30{k7}{z},qword ptr [rcx]
    vmovsd xmm30{k7},qword ptr [rax+r14*8+0x123]
    vmovsd xmm30{k7},qword ptr [rdx+0x3f8]
    vmovsd xmm30{k7},qword ptr [rdx+0x400]
    vmovsd xmm30{k7},qword ptr [rdx-0x400]
    vmovsd xmm30{k7},qword ptr [rdx-0x408]
    vmovsd qword ptr [rcx]{k7},xmm30
    vmovsd qword ptr [rax+r14*8+0x123]{k7},xmm30
    vmovsd qword ptr [rdx+0x3f8]{k7},xmm30
    vmovsd qword ptr [rdx+0x400]{k7},xmm30
    vmovsd qword ptr [rdx-0x400]{k7},xmm30
    vmovsd qword ptr [rdx-0x408]{k7},xmm30
    vmovsd xmm30{k7},xmm29,xmm28
    vmovsd xmm30{k7}{z},xmm29,xmm28
    vmovsd xmm20,xmm1, xmm2
    vmovsd xmm20,qword ptr [rax]
    vmovsd qword ptr [rax],xmm20
    vmovsd xmm20,qword ptr [rbx]
    vmovsd qword ptr [rbx],xmm20

    vmovss xmm1{k1}{z},xmm2,xmm3
    vmovss xmm30{k7},dword ptr [rcx]
    vmovss xmm30{k7}{z},dword ptr [rcx]
    vmovss xmm30{k7},dword ptr [rax+r14*8+0x123]
    vmovss xmm30{k7},dword ptr [rdx+0x1fc]
    vmovss xmm30{k7},dword ptr [rdx+0x200]
    vmovss xmm30{k7},dword ptr [rdx-0x200]
    vmovss xmm30{k7},dword ptr [rdx-0x204]
    vmovss dword ptr [rcx]{k7},xmm30
    vmovss dword ptr [rax+r14*8+0x123]{k7},xmm30
    vmovss dword ptr [rdx+0x1fc]{k7},xmm30
    vmovss dword ptr [rdx+0x200]{k7},xmm30
    vmovss dword ptr [rdx-0x200]{k7},xmm30
    vmovss dword ptr [rdx-0x204]{k7},xmm30
    vmovss xmm30{k7},xmm29,xmm28
    vmovss xmm30{k7}{z},xmm29,xmm28
    vmovss xmm20,xmm1, xmm2
    vmovss xmm20,dword ptr [rax]
    vmovss dword ptr [rax],xmm20
    vmovss xmm20,dword ptr [rbx]
    vmovss dword ptr [rbx],xmm20

    vmovntdq [rax],zmm1
    vmovntdq ymmword ptr [rax],ymm20
    vmovntdq zmmword ptr [rcx],zmm30
    vmovntdq zmmword ptr [rax+r14*8+0x123],zmm30
    vmovntdq zmmword ptr [rdx+0x1fc0],zmm30
    vmovntdq zmmword ptr [rdx+0x2000],zmm30
    vmovntdq zmmword ptr [rdx-0x2000],zmm30
    vmovntdq zmmword ptr [rdx-0x2040],zmm30
    vmovntdq oword ptr [rax],xmm20

    vmovntdqa zmm1,[rax]
    vmovntdqa xmm20,oword ptr [rax]
    vmovntdqa ymm20,ymmword ptr [rax]
    vmovntdqa zmm30,zmmword ptr [rcx]
    vmovntdqa zmm30,zmmword ptr [rax+r14*8+0x123]
    vmovntdqa zmm30,zmmword ptr [rdx+0x1fc0]
    vmovntdqa zmm30,zmmword ptr [rdx+0x2000]
    vmovntdqa zmm30,zmmword ptr [rdx-0x2000]
    vmovntdqa zmm30,zmmword ptr [rdx-0x2040]

    vmovntpd [rax],zmm1
    vmovntpd oword ptr [rax],xmm20
    vmovntpd ymmword ptr [rax],ymm20
    vmovntpd zmmword ptr [rcx],zmm30
    vmovntpd zmmword ptr [rax+r14*8+0x123],zmm30
    vmovntpd zmmword ptr [rdx+0x1fc0],zmm30
    vmovntpd zmmword ptr [rdx+0x2000],zmm30
    vmovntpd zmmword ptr [rdx-0x2000],zmm30
    vmovntpd zmmword ptr [rdx-0x2040],zmm30

    vmovntps [rax],zmm1
    vmovntps oword ptr [rax],xmm20
    vmovntps ymmword ptr [rax],ymm20
    vmovntps zmmword ptr [rcx],zmm30
    vmovntps zmmword ptr [rax+r14*8+0x123],zmm30
    vmovntps zmmword ptr [rdx+0x1fc0],zmm30
    vmovntps zmmword ptr [rdx+0x2000],zmm30
    vmovntps zmmword ptr [rdx-0x2000],zmm30
    vmovntps zmmword ptr [rdx-0x2040],zmm30

    vmovshdup zmm1{k1}{z},zmm2
    vmovshdup zmm30,zmm29
    vmovshdup zmm30{k7},zmm29
    vmovshdup zmm30{k7}{z},zmm29
    vmovshdup zmm30,zmmword ptr [rcx]
    vmovshdup zmm30,zmmword ptr [rax+r14*8+0x123]
    vmovshdup zmm30,zmmword ptr [rdx+0x1fc0]
    vmovshdup zmm30,zmmword ptr [rdx+0x2000]
    vmovshdup zmm30,zmmword ptr [rdx-0x2000]
    vmovshdup zmm30,zmmword ptr [rdx-0x2040]

    vmovsldup zmm1{k1}{z},zmm2
    vmovsldup zmm30,zmm29
    vmovsldup zmm30{k7},zmm29
    vmovsldup zmm30{k7}{z},zmm29
    vmovsldup zmm30,zmmword ptr [rcx]
    vmovsldup zmm30,zmmword ptr [rax+r14*8+0x123]
    vmovsldup zmm30,zmmword ptr [rdx+0x1fc0]
    vmovsldup zmm30,zmmword ptr [rdx+0x2000]
    vmovsldup zmm30,zmmword ptr [rdx-0x2000]
    vmovsldup zmm30,zmmword ptr [rdx-0x2040]

    vmovupd xmm20,xmm1
    vmovupd xmm20,oword ptr [rax]
    vmovupd oword ptr [rax],xmm21
    vmovupd ymm20,ymm1
    vmovupd ymm20,ymmword ptr [rax]
    vmovupd ymmword ptr [rax],ymm21
    vmovupd zmm1{k1}{z},zmm2
    vmovupd zmm30,zmm29
    vmovupd zmm30{k7},zmm29
    vmovupd zmm30{k7}{z},zmm29
    vmovupd zmm30,zmmword ptr [rcx]
    vmovupd zmm30,zmmword ptr [rax+r14*8+0x123]
    vmovupd zmm30,zmmword ptr [rdx+0x1fc0]
    vmovupd zmm30,zmmword ptr [rdx+0x2000]
    vmovupd zmm30,zmmword ptr [rdx-0x2000]
    vmovupd zmm30,zmmword ptr [rdx-0x2040]

    vmovups xmm20,xmm1
    vmovups xmm20,oword ptr [rax]
    vmovups oword ptr [rax],xmm21
    vmovups ymm20,ymm1
    vmovups ymm20,ymmword ptr [rax]
    vmovups ymmword ptr [rax],ymm21
    vmovups zmm1{k1}{z},zmm2
    vmovups zmm30,zmm29
    vmovups zmm30{k7},zmm29
    vmovups zmm30{k7}{z},zmm29
    vmovups zmm30,zmmword ptr [rcx]
    vmovups zmm30,zmmword ptr [rax+r14*8+0x123]
    vmovups zmm30,zmmword ptr [rdx+0x1fc0]
    vmovups zmm30,zmmword ptr [rdx+0x2000]
    vmovups zmm30,zmmword ptr [rdx-0x2000]
    vmovups zmm30,zmmword ptr [rdx-0x2040]

    vmovupd zmmword ptr [rcx],zmm30
    vmovupd zmmword ptr [rcx]{k7},zmm30
    vmovupd zmmword ptr [rax+r14*8+0x123],zmm30
    vmovupd zmmword ptr [rdx+0x1fc0],zmm30
    vmovupd zmmword ptr [rdx+0x2000],zmm30
    vmovupd zmmword ptr [rdx-0x2000],zmm30
    vmovupd zmmword ptr [rdx-0x2040],zmm30

    vmovups zmmword ptr [rcx],zmm30
    vmovups zmmword ptr [rcx]{k7},zmm30
    vmovups zmmword ptr [rax+r14*8+0x123],zmm30
    vmovups zmmword ptr [rdx+0x1fc0],zmm30
    vmovups zmmword ptr [rdx+0x2000],zmm30
    vmovups zmmword ptr [rdx-0x2000],zmm30
    vmovups zmmword ptr [rdx-0x2040],zmm30

    vpabsb xmm20,xmm1
    vpabsb xmm20,[rax]
    vpabsw xmm20,xmm1
    vpabsw xmm20,[rax]
    vpabsd xmm20,xmm1
    vpabsd xmm20,[rax]
    vpabsb zmm1{k1}{z},zmm2
    vpabsw zmm1{k1}{z},zmm2

    vpabsd zmm1{k1}{z},zmm2
    vpabsd zmm30,zmm29
    vpabsd zmm30{k7},zmm29
    vpabsd zmm30{k7}{z},zmm29
    vpabsd zmm30,zmmword ptr [rcx]
    vpabsd zmm30,zmmword ptr [rax+r14*8+0x123]
    vpabsd zmm30,dword ptr [rcx]{1to16}
    vpabsd zmm30,zmmword ptr [rdx+0x1fc0]
    vpabsd zmm30,zmmword ptr [rdx+0x2000]
    vpabsd zmm30,zmmword ptr [rdx-0x2000]
    vpabsd zmm30,zmmword ptr [rdx-0x2040]
    vpabsd zmm30,dword ptr [rdx+0x1fc]{1to16}
    vpabsd zmm30,dword ptr [rdx+0x200]{1to16}
    vpabsd zmm30,dword ptr [rdx-0x200]{1to16}
    vpabsd zmm30,dword ptr [rdx-0x204]{1to16}

    vpacksswb	zmm1{k1}{z},zmm2,zmm3
    vpackssdw	zmm1{k1}{z},zmm2,zmm3
    vpackuswb	zmm1{k1}{z},zmm2,zmm3
    vpackusdw	zmm1{k1}{z},zmm2,zmm3
    vpaddb	ymm1{k1}{z},ymm2,ymm3
    vpaddw	zmm1{k1}{z},zmm2,zmm3

    vpaddb   xmm20,xmm0,xmm1
    vpaddw   xmm20,xmm0,xmm1
    vpaddd   xmm20,xmm0,xmm1
    vpaddq   xmm20,xmm0,xmm1
    vpaddsb  xmm20,xmm0,xmm1
    vpaddsw  xmm20,xmm0,xmm1
    vpaddusb xmm20,xmm0,xmm1
    vpaddusw xmm20,xmm0,xmm1
    vpavgb   xmm20,xmm0,xmm1
    vpavgw   xmm20,xmm0,xmm1

    vpaddb   ymm20,ymm0,ymm1
    vpaddw   ymm20,ymm0,ymm1
    vpaddd   ymm20,ymm0,ymm1
    vpaddq   ymm20,ymm0,ymm1
    vpaddsb  ymm20,ymm0,ymm1
    vpaddsw  ymm20,ymm0,ymm1
    vpaddusb ymm20,ymm0,ymm1
    vpaddusw ymm20,ymm0,ymm1
    vpavgb   ymm20,ymm0,ymm1
    vpavgw   ymm20,ymm0,ymm1

    vpaddd ymm1{k1}{z},ymm2,ymm3
    vpaddd zmm30,zmm29,zmm28
    vpaddd zmm30{k7},zmm29,zmm28
    vpaddd zmm30{k7}{z},zmm29,zmm28
    vpaddd zmm30,zmm29,zmmword ptr [rcx]
    vpaddd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpaddd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpaddd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpaddd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpaddd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpaddd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpaddd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpaddd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpaddd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpaddd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpaddq zmm1{k1}{z},zmm2,zmm3
    vpaddq zmm30,zmm29,zmm28
    vpaddq zmm30{k7},zmm29,zmm28
    vpaddq zmm30{k7}{z},zmm29,zmm28
    vpaddq zmm30,zmm29,zmmword ptr [rcx]
    vpaddq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpaddq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpaddq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpaddq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpaddq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpaddq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpaddq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpaddq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpaddq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpaddq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpaddsb	zmm1{k1}{z},zmm2,zmm3
    vpaddsw	zmm1{k1}{z},zmm2,zmm3
    vpaddusb	ymm1{k1}{z},ymm2,ymm3
    vpaddusw	zmm1{k1}{z},zmm2,zmm3
    vpavgb	zmm1{k1}{z},zmm2,zmm3
    vpavgw	zmm1{k1}{z},zmm2,zmm3
    vpcmpeqb	k1{k2},zmm2,zmm3
    vpcmpeqw	k1{k2},zmm2,zmm3

    vpcmpeqd k1{k2},zmm2,zmm3
    vpcmpeqq k1{k2},zmm2,zmm3
    vpcmpgtb k1{k2},zmm2,zmm3
    vpcmpgtw k1{k2},zmm2,zmm3
    vpcmpgtd k1{k2},zmm2,zmm3
    vpcmpgtq k1{k2},zmm2,zmm3

    vpcmpeqd k5,zmm30,zmm29
    vpcmpeqd k5{k7},zmm30,zmm29
    vpcmpeqd k5,zmm30,zmmword ptr [rcx]
    vpcmpeqd k5,zmm30,zmmword ptr [rax+r14*8+0x123]
    vpcmpeqd k5,zmm30,dword ptr [rcx]{1to16}
    vpcmpeqd k5,zmm30,zmmword ptr [rdx+0x1fc0]
    vpcmpeqd k5,zmm30,zmmword ptr [rdx+0x2000]
    vpcmpeqd k5,zmm30,zmmword ptr [rdx-0x2000]
    vpcmpeqd k5,zmm30,zmmword ptr [rdx-0x2040]
    vpcmpeqd k5,zmm30,dword ptr [rdx+0x1fc]{1to16}
    vpcmpeqd k5,zmm30,dword ptr [rdx+0x200]{1to16}
    vpcmpeqd k5,zmm30,dword ptr [rdx-0x200]{1to16}
    vpcmpeqd k5,zmm30,dword ptr [rdx-0x204]{1to16}
    vpcmpeqq k5,zmm30,zmm29
    vpcmpeqq k5{k7},zmm30,zmm29
    vpcmpeqq k5,zmm30,zmmword ptr [rcx]
    vpcmpeqq k5,zmm30,zmmword ptr [rax+r14*8+0x123]
    vpcmpeqq k5,zmm30,qword ptr [rcx]{1to8}
    vpcmpeqq k5,zmm30,zmmword ptr [rdx+0x1fc0]
    vpcmpeqq k5,zmm30,zmmword ptr [rdx+0x2000]
    vpcmpeqq k5,zmm30,zmmword ptr [rdx-0x2000]
    vpcmpeqq k5,zmm30,zmmword ptr [rdx-0x2040]
    vpcmpeqq k5,zmm30,qword ptr [rdx+0x3f8]{1to8}
    vpcmpeqq k5,zmm30,qword ptr [rdx+0x400]{1to8}
    vpcmpeqq k5,zmm30,qword ptr [rdx-0x400]{1to8}
    vpcmpeqq k5,zmm30,qword ptr [rdx-0x408]{1to8}
    vpcmpgtd k5,zmm30,zmm29
    vpcmpgtd k5{k7},zmm30,zmm29
    vpcmpgtd k5,zmm30,zmmword ptr [rcx]
    vpcmpgtd k5,zmm30,zmmword ptr [rax+r14*8+0x123]
    vpcmpgtd k5,zmm30,dword ptr [rcx]{1to16}
    vpcmpgtd k5,zmm30,zmmword ptr [rdx+0x1fc0]
    vpcmpgtd k5,zmm30,zmmword ptr [rdx+0x2000]
    vpcmpgtd k5,zmm30,zmmword ptr [rdx-0x2000]
    vpcmpgtd k5,zmm30,zmmword ptr [rdx-0x2040]
    vpcmpgtd k5,zmm30,dword ptr [rdx+0x1fc]{1to16}
    vpcmpgtd k5,zmm30,dword ptr [rdx+0x200]{1to16}
    vpcmpgtd k5,zmm30,dword ptr [rdx-0x200]{1to16}
    vpcmpgtd k5,zmm30,dword ptr [rdx-0x204]{1to16}
    vpcmpgtq k5,zmm30,zmm29
    vpcmpgtq k5{k7},zmm30,zmm29
    vpcmpgtq k5,zmm30,zmmword ptr [rcx]
    vpcmpgtq k5,zmm30,zmmword ptr [rax+r14*8+0x123]
    vpcmpgtq k5,zmm30,qword ptr [rcx]{1to8}
    vpcmpgtq k5,zmm30,zmmword ptr [rdx+0x1fc0]
    vpcmpgtq k5,zmm30,zmmword ptr [rdx+0x2000]
    vpcmpgtq k5,zmm30,zmmword ptr [rdx-0x2000]
    vpcmpgtq k5,zmm30,zmmword ptr [rdx-0x2040]
    vpcmpgtq k5,zmm30,qword ptr [rdx+0x3f8]{1to8}
    vpcmpgtq k5,zmm30,qword ptr [rdx+0x400]{1to8}
    vpcmpgtq k5,zmm30,qword ptr [rdx-0x400]{1to8}
    vpcmpgtq k5,zmm30,qword ptr [rdx-0x408]{1to8}

    vpextrb eax,xmm2,7
    vpextrb eax,xmm21,1
    vpextrb byte ptr [rax],xmm21,1
    vpextrd eax,xmm2,7
    vpextrd eax,xmm21,3
    vpextrd dword ptr [rax],xmm21,3
    vpextrw word ptr [rax],xmm21,2
    vpextrq rax,xmm2,7
    vpextrq rax,xmm1,4
    vpextrq qword ptr [rax],xmm21,4

    vpinsrb xmm1,xmm2,eax,7
    vpinsrw xmm1,xmm2,eax,7
    vpinsrd xmm1,xmm2,eax,7
    vpinsrq xmm1,xmm2,rax,7
    vpinsrb xmm20,xmm1,eax,1
    vpinsrb xmm20,xmm1,byte ptr [rax],1
    vpinsrw xmm20,xmm1,eax,2
    vpinsrw xmm20,xmm1,word ptr [rax],2
    vpinsrd xmm20,xmm1,eax,3
    vpinsrd xmm20,xmm1,dword ptr [rax],3
    vpinsrq xmm20,xmm1,rax,4
    vpinsrq xmm20,xmm1,qword ptr [rax],4

    vpmaddwd	zmm1{k1}{z},zmm2,zmm3
    vpmaddubsw	zmm1{k1}{z},zmm2,zmm3
    vpmaxsb	zmm1{k1}{z},zmm2,zmm3
    vpmaxsw	ymm1{k1}{z},ymm2,ymm3

    vpmaxsd zmm1{k1}{z},zmm2,zmm3
    vpmaxsd zmm30,zmm29,zmm28
    vpmaxsd zmm30{k7},zmm29,zmm28
    vpmaxsd zmm30{k7}{z},zmm29,zmm28
    vpmaxsd zmm30,zmm29,zmmword ptr [rcx]
    vpmaxsd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpmaxsd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpmaxsd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpmaxsd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpmaxsd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpmaxsd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpmaxsd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpmaxsd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpmaxsd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpmaxsd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpmaxub	zmm1{k1}{z},zmm2,zmm3
    vpmaxuw	zmm1{k1}{z},zmm2,zmm3

    vpmaxud zmm1{k1}{z},zmm2,zmm3
    vpmaxud zmm30,zmm29,zmm28
    vpmaxud zmm30{k7},zmm29,zmm28
    vpmaxud zmm30{k7}{z},zmm29,zmm28
    vpmaxud zmm30,zmm29,zmmword ptr [rcx]
    vpmaxud zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpmaxud zmm30,zmm29,dword ptr [rcx]{1to16}
    vpmaxud zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpmaxud zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpmaxud zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpmaxud zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpmaxud zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpmaxud zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpmaxud zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpmaxud zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpminsb	zmm1{k1}{z},zmm2,zmm3
    vpminsw	zmm1{k1}{z},zmm2,zmm3

    vpminsd zmm1{k1}{z},zmm2,zmm3
    vpminsd zmm30,zmm29,zmm28
    vpminsd zmm30{k7},zmm29,zmm28
    vpminsd zmm30{k7}{z},zmm29,zmm28
    vpminsd zmm30,zmm29,zmmword ptr [rcx]
    vpminsd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpminsd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpminsd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpminsd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpminsd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpminsd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpminsd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpminsd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpminsd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpminsd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpminub	zmm1{k1}{z},zmm2,zmm3
    vpminuw	zmm1{k1}{z},zmm2,zmm3

    vpminud zmm1{k1}{z},zmm2,zmm3
    vpminud zmm30,zmm29,zmm28
    vpminud zmm30{k7},zmm29,zmm28
    vpminud zmm30{k7}{z},zmm29,zmm28
    vpminud zmm30,zmm29,zmmword ptr [rcx]
    vpminud zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpminud zmm30,zmm29,dword ptr [rcx]{1to16}
    vpminud zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpminud zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpminud zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpminud zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpminud zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpminud zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpminud zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpminud zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpmovsxbw xmm20,xmm1
    vpmovsxbw xmm20,[rax]
    vpmovsxbd xmm20,xmm1
    vpmovsxbd xmm20,[rax]
    vpmovsxbq xmm20,xmm1
    vpmovsxbq xmm20,[rax]
    vpmovsxwd xmm20,xmm1
    vpmovsxwd xmm20,[rax]
    vpmovsxwq xmm20,xmm1
    vpmovsxwq xmm20,[rax]
    vpmovsxdq xmm20,xmm1
    vpmovsxdq xmm20,[rax]

    vpmovsxbw zmm1{k1}{z},ymm3
    vpmovsxbd zmm1{k1}{z},xmm3
    vpmovsxbq zmm1{k1}{z},xmm3
    vpmovsxdq zmm1{k1}{z},ymm3
    vpmovzxwq zmm1{k1}{z},xmm2
    vpmovzxdq zmm1{k1}{z},ymm2

    vpmovsxbd zmm30{k7},xmm29
    vpmovsxbd zmm30{k7}{z},xmm29
    vpmovsxbd zmm30{k7},oword ptr [rcx]
    vpmovsxbd zmm30{k7},oword ptr [rax+r14*8+0x123]
    vpmovsxbd zmm30{k7},oword ptr [rdx+0x7f0]
    vpmovsxbd zmm30{k7},oword ptr [rdx+0x800]
    vpmovsxbd zmm30{k7},oword ptr [rdx-0x800]
    vpmovsxbd zmm30{k7},oword ptr [rdx-0x810]
    vpmovsxbq zmm30{k7},xmm29
    vpmovsxbq zmm30{k7}{z},xmm29
    vpmovsxbq zmm30{k7},qword ptr [rcx]
    vpmovsxbq zmm30{k7},qword ptr [rax+r14*8+0x123]
    vpmovsxbq zmm30{k7},qword ptr [rdx+0x3f8]
    vpmovsxbq zmm30{k7},qword ptr [rdx+0x400]
    vpmovsxbq zmm30{k7},qword ptr [rdx-0x400]
    vpmovsxbq zmm30{k7},qword ptr [rdx-0x408]
    vpmovsxdq zmm30{k7},ymm29
    vpmovsxdq zmm30{k7}{z},ymm29
    vpmovsxdq zmm30{k7},ymmword ptr [rcx]
    vpmovsxdq zmm30{k7},ymmword ptr [rax+r14*8+0x123]
    vpmovsxdq zmm30{k7},ymmword ptr [rdx+0xfe0]
    vpmovsxdq zmm30{k7},ymmword ptr [rdx+0x1000]
    vpmovsxdq zmm30{k7},ymmword ptr [rdx-0x1000]
    vpmovsxdq zmm30{k7},ymmword ptr [rdx-0x1020]
    vpmovsxwd zmm30{k7},ymm29
    vpmovsxwd zmm30{k7}{z},ymm29
    vpmovsxwd zmm30{k7},ymmword ptr [rcx]
    vpmovsxwd zmm30{k7},ymmword ptr [rax+r14*8+0x123]
    vpmovsxwd zmm30{k7},ymmword ptr [rdx+0xfe0]
    vpmovsxwd zmm30{k7},ymmword ptr [rdx+0x1000]
    vpmovsxwd zmm30{k7},ymmword ptr [rdx-0x1000]
    vpmovsxwd zmm30{k7},ymmword ptr [rdx-0x1020]
    vpmovsxwq zmm30{k7},xmm29
    vpmovsxwq zmm30{k7}{z},xmm29
    vpmovsxwq zmm30{k7},oword ptr [rcx]
    vpmovsxwq zmm30{k7},oword ptr [rax+r14*8+0x123]
    vpmovsxwq zmm30{k7},oword ptr [rdx+0x7f0]
    vpmovsxwq zmm30{k7},oword ptr [rdx+0x800]
    vpmovsxwq zmm30{k7},oword ptr [rdx-0x800]
    vpmovsxwq zmm30{k7},oword ptr [rdx-0x810]
    vpmovzxbd zmm30{k7},xmm29
    vpmovzxbd zmm30{k7}{z},xmm29
    vpmovzxbd zmm30{k7},oword ptr [rcx]
    vpmovzxbd zmm30{k7},oword ptr [rax+r14*8+0x123]
    vpmovzxbd zmm30{k7},oword ptr [rdx+0x7f0]
    vpmovzxbd zmm30{k7},oword ptr [rdx+0x800]
    vpmovzxbd zmm30{k7},oword ptr [rdx-0x800]
    vpmovzxbd zmm30{k7},oword ptr [rdx-0x810]
    vpmovzxbq zmm30{k7},xmm29
    vpmovzxbq zmm30{k7}{z},xmm29
    vpmovzxbq zmm30{k7},qword ptr [rcx]
    vpmovzxbq zmm30{k7},qword ptr [rax+r14*8+0x123]
    vpmovzxbq zmm30{k7},qword ptr [rdx+0x3f8]
    vpmovzxbq zmm30{k7},qword ptr [rdx+0x400]
    vpmovzxbq zmm30{k7},qword ptr [rdx-0x400]
    vpmovzxbq zmm30{k7},qword ptr [rdx-0x408]
    vpmovzxdq zmm30{k7},ymm29
    vpmovzxdq zmm30{k7}{z},ymm29
    vpmovzxdq zmm30{k7},ymmword ptr [rcx]
    vpmovzxdq zmm30{k7},ymmword ptr [rax+r14*8+0x123]
    vpmovzxdq zmm30{k7},ymmword ptr [rdx+0xfe0]
    vpmovzxdq zmm30{k7},ymmword ptr [rdx+0x1000]
    vpmovzxdq zmm30{k7},ymmword ptr [rdx-0x1000]
    vpmovzxdq zmm30{k7},ymmword ptr [rdx-0x1020]
    vpmovzxwd zmm30{k7},ymm29
    vpmovzxwd zmm30{k7}{z},ymm29
    vpmovzxwd zmm30{k7},ymmword ptr [rcx]
    vpmovzxwd zmm30{k7},ymmword ptr [rax+r14*8+0x123]
    vpmovzxwd zmm30{k7},ymmword ptr [rdx+0xfe0]
    vpmovzxwd zmm30{k7},ymmword ptr [rdx+0x1000]
    vpmovzxwd zmm30{k7},ymmword ptr [rdx-0x1000]
    vpmovzxwd zmm30{k7},ymmword ptr [rdx-0x1020]
    vpmovzxwq zmm30{k7},xmm29
    vpmovzxwq zmm30{k7}{z},xmm29
    vpmovzxwq zmm30{k7},oword ptr [rcx]
    vpmovzxwq zmm30{k7},oword ptr [rax+r14*8+0x123]
    vpmovzxwq zmm30{k7},oword ptr [rdx+0x7f0]
    vpmovzxwq zmm30{k7},oword ptr [rdx+0x800]
    vpmovzxwq zmm30{k7},oword ptr [rdx-0x800]
    vpmovzxwq zmm30{k7},oword ptr [rdx-0x810]

    vpmovzxbw xmm20,xmm1
    vpmovzxbd xmm20,xmm1
    vpmovzxbq xmm20,xmm1
    vpmovzxwd xmm20,xmm1
    vpmovzxwq xmm20,xmm1
    vpmovzxdq xmm20,xmm1
    vpmuldq xmm20,xmm1,xmm2
    vpmulld xmm20,xmm0,xmm1

    vpmovzxbw xmm20,qword ptr [rax]
    vpmovzxbd xmm20,dword ptr [rax]
    vpmovzxbq xmm20,word  ptr [rax]
    vpmovzxwd xmm20,qword ptr [rax]
    vpmovzxwq xmm20,dword ptr [rax]
    vpmovzxdq xmm20,qword ptr [rax]
    vpmuldq xmm20,xmm1,oword ptr [rax]
    vpmulld xmm20,xmm1,oword ptr [rax]

    vpmulhrsw zmm1{k1}{z},zmm2,zmm3
    vpmulhw zmm1{k1}{z},zmm2,zmm3
    vpmullw zmm1{k1}{z},zmm2,zmm3
    vpmulld zmm1{k1}{z},zmm2,zmm3
    vpmuludq zmm1{k1}{z},zmm2,zmm3
    vpmuldq zmm1{k1}{z},zmm2,zmm3
    vpmuldq zmm30,zmm29,zmm28
    vpmuldq zmm30{k7},zmm29,zmm28
    vpmuldq zmm30{k7}{z},zmm29,zmm28
    vpmuldq zmm30,zmm29,zmmword ptr [rcx]
    vpmuldq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpmuldq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpmuldq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpmuldq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpmuldq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpmuldq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpmuldq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpmuldq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpmuldq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpmuldq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vpmulld zmm30,zmm29,zmm28
    vpmulld zmm30{k7},zmm29,zmm28
    vpmulld zmm30{k7}{z},zmm29,zmm28
    vpmulld zmm30,zmm29,zmmword ptr [rcx]
    vpmulld zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpmulld zmm30,zmm29,dword ptr [rcx]{1to16}
    vpmulld zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpmulld zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpmulld zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpmulld zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpmulld zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpmulld zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpmulld zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpmulld zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vpmuludq zmm30,zmm29,zmm28
    vpmuludq zmm30{k7},zmm29,zmm28
    vpmuludq zmm30{k7}{z},zmm29,zmm28
    vpmuludq zmm30,zmm29,zmmword ptr [rcx]
    vpmuludq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpmuludq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpmuludq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpmuludq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpmuludq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpmuludq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpmuludq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpmuludq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpmuludq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpmuludq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpsadbw zmm1,zmm2,zmm3
    vpshufb zmm1{k1}{z},zmm2,zmm3
    vpshufd zmm1{k1}{z},zmm2,3
    vpshufd zmm30,zmm29,0xab
    vpshufd zmm30{k7},zmm29,0xab
    vpshufd zmm30{k7}{z},zmm29,0xab
    vpshufd zmm30,zmm29,0x7b
    vpshufd zmm30,zmmword ptr [rcx],0x7b
    vpshufd zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vpshufd zmm30,dword ptr [rcx]{1to16},0x7b
    vpshufd zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vpshufd zmm30,zmmword ptr [rdx+0x2000],0x7b
    vpshufd zmm30,zmmword ptr [rdx-0x2000],0x7b
    vpshufd zmm30,zmmword ptr [rdx-0x2040],0x7b
    vpshufd zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpshufd zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vpshufd zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vpshufd zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vpshufhw	zmm1{k1}{z},zmm2,3
    vpshuflw	zmm1{k1}{z},zmm2,3
    vpslldq	zmm1,zmm2,3
    vpsrldq	zmm1,zmm2,3
    vpsllw	zmm1{k1}{z},zmm2,3

    vpslld zmm1{k1}{z},zmm2,xmm3
    vpslld zmm30{k7},zmm29,xmm28
    vpslld zmm30{k7}{z},zmm29,xmm28
    vpslld zmm30{k7},zmm29,oword ptr [rcx]
    vpslld zmm30{k7},zmm29,oword ptr [rax+r14*8+0x123]
    vpslld zmm30{k7},zmm29,oword ptr [rdx+0x7f0]
    vpslld zmm30{k7},zmm29,oword ptr [rdx+0x800]
    vpslld zmm30{k7},zmm29,oword ptr [rdx-0x800]
    vpslld zmm30{k7},zmm29,oword ptr [rdx-0x810]
    vpslld zmm30,zmm29,0xab
    vpslld zmm30{k7},zmm29,0xab
    vpslld zmm30{k7}{z},zmm29,0xab
    vpslld zmm30,zmm29,0x7b
    vpslld zmm30,zmmword ptr [rcx],0x7b
    vpslld zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vpslld zmm30,dword ptr [rcx]{1to16},0x7b
    vpslld zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vpslld zmm30,zmmword ptr [rdx+0x2000],0x7b
    vpslld zmm30,zmmword ptr [rdx-0x2000],0x7b
    vpslld zmm30,zmmword ptr [rdx-0x2040],0x7b
    vpslld zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpslld zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vpslld zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vpslld zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vpsllq zmm1{k1}{z},zmm2,xmm3
    vpsllq zmm30{k7},zmm29,xmm28
    vpsllq zmm30{k7}{z},zmm29,xmm28
    vpsllq zmm30{k7},zmm29,oword ptr [rcx]
    vpsllq zmm30{k7},zmm29,oword ptr [rax+r14*8+0x123]
    vpsllq zmm30{k7},zmm29,oword ptr [rdx+0x7f0]
    vpsllq zmm30{k7},zmm29,oword ptr [rdx+0x800]
    vpsllq zmm30{k7},zmm29,oword ptr [rdx-0x800]
    vpsllq zmm30{k7},zmm29,oword ptr [rdx-0x810]
    vpsllq zmm30,zmm29,0xab
    vpsllq zmm30{k7},zmm29,0xab
    vpsllq zmm30{k7}{z},zmm29,0xab
    vpsllq zmm30,zmm29,0x7b
    vpsllq zmm30,zmmword ptr [rcx],0x7b
    vpsllq zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vpsllq zmm30,qword ptr [rcx]{1to8},0x7b
    vpsllq zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vpsllq zmm30,zmmword ptr [rdx+0x2000],0x7b
    vpsllq zmm30,zmmword ptr [rdx-0x2000],0x7b
    vpsllq zmm30,zmmword ptr [rdx-0x2040],0x7b
    vpsllq zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpsllq zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpsllq zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpsllq zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vpsraw zmm1,zmm2,3
    vpsrlw zmm1{k1}{z},zmm2,xmm3

    vpsrlw xmm20,xmm1,xmm2
    vpsrlw xmm20,xmm1,[rax]
    vpsrld xmm20,xmm1,xmm2
    vpsrld xmm20,xmm1,[rax]
    vpsrlq xmm20,xmm1,xmm2
    vpsrlq xmm20,xmm1,[rax]
    vpsraw xmm20,xmm1,xmm2
    vpsraw xmm20,xmm1,[rax]
    vpsrad xmm20,xmm1,xmm2
    vpsrad xmm20,xmm1,[rax]
    vpsllw xmm20,xmm1,xmm2
    vpsllw xmm20,xmm1,[rax]
    vpslld xmm20,xmm1,xmm2
    vpslld xmm20,xmm1,[rax]
    vpsllq xmm20,xmm1,xmm2
    vpsllq xmm20,xmm1,[rax]

    vpslldq xmm20,xmm1,1
    vpsrldq xmm20,xmm1,2
    vpsrlw xmm20,xmm1,3
    vpsrld xmm20,xmm1,4
    vpsrlq xmm20,xmm1,5
    vpsraw xmm20,xmm1,6
    vpsrad xmm20,xmm1,7
    vpsllw xmm20,xmm1,8
    vpslld xmm20,xmm1,9
    vpsllq xmm20,xmm1,10

    vpsrlw xmm20,xmm1,xmm2
    vpsrlw xmm20,xmm1,[rax]
    vpsrld xmm20,xmm1,xmm2
    vpsrld xmm20,xmm1,[rax]
    vpsrlq xmm20,xmm1,xmm2
    vpsrlq xmm20,xmm1,[rax]
    vpsraw xmm20,xmm1,xmm2
    vpsraw xmm20,xmm1,[rax]
    vpsrad xmm20,xmm1,xmm2
    vpsrad xmm20,xmm1,[rax]
    vpsllw xmm20,xmm1,xmm2
    vpsllw xmm20,xmm1,[rax]
    vpslld xmm20,xmm1,xmm2
    vpslld xmm20,xmm1,[rax]
    vpsllq xmm20,xmm1,xmm2
    vpsllq xmm20,xmm1,[rax]

    vpsrad zmm1{k1}{z},zmm2,xmm3
    vpsrad zmm30{k7},zmm29,xmm28
    vpsrad zmm30{k7}{z},zmm29,xmm28
    vpsrad zmm30{k7},zmm29,oword ptr [rcx]
    vpsrad zmm30{k7},zmm29,oword ptr [rax+r14*8+0x123]
    vpsrad zmm30{k7},zmm29,oword ptr [rdx+0x7f0]
    vpsrad zmm30{k7},zmm29,oword ptr [rdx+0x800]
    vpsrad zmm30{k7},zmm29,oword ptr [rdx-0x800]
    vpsrad zmm30{k7},zmm29,oword ptr [rdx-0x810]
    vpsrad zmm30,zmm29,0xab
    vpsrad zmm30{k7},zmm29,0xab
    vpsrad zmm30{k7}{z},zmm29,0xab
    vpsrad zmm30,zmm29,0x7b
    vpsrad zmm30,zmmword ptr [rcx],0x7b
    vpsrad zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vpsrad zmm30,dword ptr [rcx]{1to16},0x7b
    vpsrad zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vpsrad zmm30,zmmword ptr [rdx+0x2000],0x7b
    vpsrad zmm30,zmmword ptr [rdx-0x2000],0x7b
    vpsrad zmm30,zmmword ptr [rdx-0x2040],0x7b
    vpsrad zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpsrad zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vpsrad zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vpsrad zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vpsrld zmm1{k1}{z},zmm2,3
    vpsrld zmm30{k7},zmm29,xmm28
    vpsrld zmm30{k7}{z},zmm29,xmm28
    vpsrld zmm30{k7},zmm29,oword ptr [rcx]
    vpsrld zmm30{k7},zmm29,oword ptr [rax+r14*8+0x123]
    vpsrld zmm30{k7},zmm29,oword ptr [rdx+0x7f0]
    vpsrld zmm30{k7},zmm29,oword ptr [rdx+0x800]
    vpsrld zmm30{k7},zmm29,oword ptr [rdx-0x800]
    vpsrld zmm30{k7},zmm29,oword ptr [rdx-0x810]
    vpsrld zmm30,zmm29,0xab
    vpsrld zmm30{k7},zmm29,0xab
    vpsrld zmm30{k7}{z},zmm29,0xab
    vpsrld zmm30,zmm29,0x7b

    vpsrlq zmm1{k1}{z},zmm2,xmm3
    vpsrlq zmm30{k7},zmm29,xmm28
    vpsrlq zmm30{k7}{z},zmm29,xmm28
    vpsrlq zmm30{k7},zmm29,oword ptr [rcx]
    vpsrlq zmm30{k7},zmm29,oword ptr [rax+r14*8+0x123]
    vpsrlq zmm30{k7},zmm29,oword ptr [rdx+0x7f0]
    vpsrlq zmm30{k7},zmm29,oword ptr [rdx+0x800]
    vpsrlq zmm30{k7},zmm29,oword ptr [rdx-0x800]
    vpsrlq zmm30{k7},zmm29,oword ptr [rdx-0x810]
    vpsrlq zmm30,zmm29,0xab
    vpsrlq zmm30{k7},zmm29,0xab
    vpsrlq zmm30{k7}{z},zmm29,0xab
    vpsrlq zmm30,zmm29,0x7b

    vpsrld zmm30,zmmword ptr [rcx],0x7b
    vpsrld zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vpsrld zmm30,dword ptr [rcx]{1to16},0x7b
    vpsrld zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vpsrld zmm30,zmmword ptr [rdx+0x2000],0x7b
    vpsrld zmm30,zmmword ptr [rdx-0x2000],0x7b
    vpsrld zmm30,zmmword ptr [rdx-0x2040],0x7b
    vpsrld zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpsrld zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vpsrld zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vpsrld zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vpsrlq zmm30,zmmword ptr [rcx],0x7b
    vpsrlq zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vpsrlq zmm30,qword ptr [rcx]{1to8},0x7b
    vpsrlq zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vpsrlq zmm30,zmmword ptr [rdx+0x2000],0x7b
    vpsrlq zmm30,zmmword ptr [rdx-0x2000],0x7b
    vpsrlq zmm30,zmmword ptr [rdx-0x2040],0x7b
    vpsrlq zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpsrlq zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpsrlq zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpsrlq zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    ;vpmovsxwd	 zmm1{k1}{z},xmm3
    ;vpmovsxwq	 zmm1{k1}{z},ymm3
    vpsubb	zmm1{k1}{z},zmm2,zmm3
    vpsubw	zmm1{k1}{z},zmm2,zmm3
    vpsubd	zmm1{k1}{z},zmm2,zmm3
    vpsubq	zmm1{k1}{z},zmm2,zmm3
    vpsubsb	zmm1{k1}{z},zmm2,zmm3
    vpsubsw	zmm1{k1}{z},zmm2,zmm3
    vpsubusb	zmm1{k1}{z},zmm2,zmm3
    vpsubusw	zmm1{k1}{z},zmm2,zmm3
    vpunpckhbw	zmm1{k1}{z},zmm2,zmm3
    vpunpckhwd	zmm1{k1}{z},zmm2,zmm3
    vpunpckhdq	zmm1{k1}{z},zmm2,zmm3
    vpunpckhqdq zmm1{k1}{z},zmm2,zmm3
    vpunpcklbw	zmm1{k1}{z},zmm2,zmm3
    vpunpcklwd	zmm1{k1}{z},zmm2,zmm3
    vpunpckldq	zmm1{k1}{z},zmm2,zmm3
    vpunpcklqdq zmm1{k1}{z},zmm2,zmm3

    vcvtps2dq xmm20,xmm1
    vcvtps2dq xmm20,oword ptr [rax]
    vcvtps2dq ymm20,ymm1
    vcvtps2dq ymm20,ymmword ptr [rax]
    ;vcvtps2dq ymm1{k1}{z},zmm2
    vcvtps2dq ymm1{k1}{z},[rax]
    vcvtps2dq zmm30,zmm29
    vcvtps2dq zmm30{k7},zmm29
    vcvtps2dq zmm30{k7}{z},zmm29
    vcvtps2dq zmm30,zmm29,{rn-sae}
    vcvtps2dq zmm30,zmm29,{ru-sae}
    vcvtps2dq zmm30,zmm29,{rd-sae}
    vcvtps2dq zmm30,zmm29,{rz-sae}
    vcvtps2dq zmm30,zmmword ptr [rcx]
    vcvtps2dq zmm30,zmmword ptr [rax+r14*8+0x123]
    vcvtps2dq zmm30,dword ptr [rcx]{1to16}
    vcvtps2dq zmm30,zmmword ptr [rdx+0x1fc0]
    vcvtps2dq zmm30,zmmword ptr [rdx+0x2000]
    vcvtps2dq zmm30,zmmword ptr [rdx-0x2000]
    vcvtps2dq zmm30,zmmword ptr [rdx-0x2040]
    vcvtps2dq zmm30,dword ptr [rdx+0x1fc]{1to16}
    vcvtps2dq zmm30,dword ptr [rdx+0x200]{1to16}
    vcvtps2dq zmm30,dword ptr [rdx-0x200]{1to16}
    vcvtps2dq zmm30,dword ptr [rdx-0x204]{1to16}

    vcvtps2pd xmm20,xmm1
    vcvtps2pd ymm20,xmm1
    vcvtps2pd zmm1{k1}{z},ymm2
    vcvtps2pd zmm30{k7},ymm29
    vcvtps2pd zmm30{k7}{z},ymm29
    vcvtps2pd zmm30{k7},ymm29,{sae}
    vcvtps2pd zmm30{k7},ymmword ptr [rcx]
    vcvtps2pd zmm30{k7},ymmword ptr [rax+r14*8+0x123]
    vcvtps2pd zmm30{k7},dword ptr [rcx]{1to8}
    vcvtps2pd zmm30{k7},ymmword ptr [rdx+0xfe0]
    vcvtps2pd zmm30{k7},ymmword ptr [rdx+0x1000]
    vcvtps2pd zmm30{k7},ymmword ptr [rdx-0x1000]
    vcvtps2pd zmm30{k7},ymmword ptr [rdx-0x1020]
    vcvtps2pd zmm30{k7},dword ptr [rdx+0x1fc]{1to8}
    vcvtps2pd zmm30{k7},dword ptr [rdx+0x200]{1to8}
    vcvtps2pd zmm30{k7},dword ptr [rdx-0x200]{1to8}
    vcvtps2pd zmm30{k7},dword ptr [rdx-0x204]{1to8}

    vpalignr	zmm1{k1}{z},zmm2,zmm3,7
    vpalignr	zmm1{k1}{z},zmm2,[rax],7
    vpmovsxwd	zmm1{k1}{z},[rax]
    vpmovsxwq	zmm1{k1}{z},[rax]
    vpsubb	zmm1{k1}{z},zmm2,[rax]
    vpsubw	zmm1{k1}{z},zmm2,[rax]

    vpsubd zmm1{k1}{z},zmm2,[rax]
    vpsubd zmm30,zmm29,zmm28
    vpsubd zmm30{k7},zmm29,zmm28
    vpsubd zmm30{k7}{z},zmm29,zmm28
    vpsubd zmm30,zmm29,zmmword ptr [rcx]
    vpsubd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpsubd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpsubd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpsubd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpsubd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpsubd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpsubd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpsubd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpsubd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpsubd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpsubq zmm1{k1}{z},zmm2,[rax]
    vpsubq zmm30,zmm29,zmm28
    vpsubq zmm30{k7},zmm29,zmm28
    vpsubq zmm30{k7}{z},zmm29,zmm28
    vpsubq zmm30,zmm29,zmmword ptr [rcx]
    vpsubq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpsubq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpsubq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpsubq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpsubq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpsubq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpsubq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpsubq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpsubq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpsubq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpsubsb	zmm1{k1}{z},zmm2,[rax]
    vpsubsw	zmm1{k1}{z},zmm2,[rax]
    vpsubusb	zmm1{k1}{z},zmm2,[rax]
    vpsubusw	zmm1{k1}{z},zmm2,[rax]
    vpunpckhbw	zmm1{k1}{z},zmm2,[rax]
    vpunpckhwd	zmm1{k1}{z},zmm2,[rax]

    vpunpckhdq zmm1{k1}{z},zmm2,[rax]
    vpunpckhdq zmm30,zmm29,zmm28
    vpunpckhdq zmm30{k7},zmm29,zmm28
    vpunpckhdq zmm30{k7}{z},zmm29,zmm28
    vpunpckhdq zmm30,zmm29,zmmword ptr [rcx]
    vpunpckhdq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpunpckhdq zmm30,zmm29,dword ptr [rcx]{1to16}
    vpunpckhdq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpunpckhdq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpunpckhdq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpunpckhdq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpunpckhdq zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpunpckhdq zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpunpckhdq zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpunpckhdq zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpunpckhqdq zmm1{k1}{z},zmm2,[rax]
    vpunpckhqdq zmm30,zmm29,zmm28
    vpunpckhqdq zmm30{k7},zmm29,zmm28
    vpunpckhqdq zmm30{k7}{z},zmm29,zmm28
    vpunpckhqdq zmm30,zmm29,zmmword ptr [rcx]
    vpunpckhqdq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpunpckhqdq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpunpckhqdq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpunpckhqdq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpunpckhqdq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpunpckhqdq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpunpckhqdq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpunpckhqdq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpunpckhqdq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpunpckhqdq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpunpcklbw zmm1{k1}{z},zmm2,[rax]
    vpunpcklwd zmm1{k1}{z},zmm2,[rax]

    vpunpckldq zmm1{k1}{z},zmm2,[rax]
    vpunpckldq zmm30,zmm29,zmm28
    vpunpckldq zmm30{k7},zmm29,zmm28
    vpunpckldq zmm30{k7}{z},zmm29,zmm28
    vpunpckldq zmm30,zmm29,zmmword ptr [rcx]
    vpunpckldq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpunpckldq zmm30,zmm29,dword ptr [rcx]{1to16}
    vpunpckldq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpunpckldq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpunpckldq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpunpckldq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpunpckldq zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpunpckldq zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpunpckldq zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpunpckldq zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpunpcklqdq zmm1{k1}{z},zmm2,[rax]
    vpunpcklqdq zmm30,zmm29,zmm28
    vpunpcklqdq zmm30{k7},zmm29,zmm28
    vpunpcklqdq zmm30{k7}{z},zmm29,zmm28
    vpunpcklqdq zmm30,zmm29,zmmword ptr [rcx]
    vpunpcklqdq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpunpcklqdq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpunpcklqdq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpunpcklqdq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpunpcklqdq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpunpcklqdq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpunpcklqdq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpunpcklqdq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpunpcklqdq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpunpcklqdq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vshufpd zmm1{k1}{z},zmm2,zmm3,7
    vshufpd zmm1{k1}{z},zmm2,[rax],7
    vshufpd zmm30,zmm29,zmm28,0xab
    vshufpd zmm30{k7},zmm29,zmm28,0xab
    vshufpd zmm30{k7}{z},zmm29,zmm28,0xab
    vshufpd zmm30,zmm29,zmm28,0x7b
    vshufpd zmm30,zmm29,zmmword ptr [rcx],0x7b
    vshufpd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123],0x7b
    vshufpd zmm30,zmm29,qword ptr [rcx]{1to8},0x7b
    vshufpd zmm30,zmm29,zmmword ptr [rdx+0x1fc0],0x7b
    vshufpd zmm30,zmm29,zmmword ptr [rdx+0x2000],0x7b
    vshufpd zmm30,zmm29,zmmword ptr [rdx-0x2000],0x7b
    vshufpd zmm30,zmm29,zmmword ptr [rdx-0x2040],0x7b
    vshufpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8},0x7b
    vshufpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8},0x7b
    vshufpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8},0x7b
    vshufpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8},0x7b

    vshufps zmm1{k1}{z},zmm2,zmm3,7
    vshufps zmm1{k1}{z},zmm2,[rax],7
    vshufps zmm30,zmm29,zmm28,0xab
    vshufps zmm30{k7},zmm29,zmm28,0xab
    vshufps zmm30{k7}{z},zmm29,zmm28,0xab
    vshufps zmm30,zmm29,zmm28,0x7b
    vshufps zmm30,zmm29,zmmword ptr [rcx],0x7b
    vshufps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123],0x7b
    vshufps zmm30,zmm29,dword ptr [rcx]{1to16},0x7b
    vshufps zmm30,zmm29,zmmword ptr [rdx+0x1fc0],0x7b
    vshufps zmm30,zmm29,zmmword ptr [rdx+0x2000],0x7b
    vshufps zmm30,zmm29,zmmword ptr [rdx-0x2000],0x7b
    vshufps zmm30,zmm29,zmmword ptr [rdx-0x2040],0x7b
    vshufps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16},0x7b
    vshufps zmm30,zmm29,dword ptr [rdx+0x200]{1to16},0x7b
    vshufps zmm30,zmm29,dword ptr [rdx-0x200]{1to16},0x7b
    vshufps zmm30,zmm29,dword ptr [rdx-0x204]{1to16},0x7b

    vunpckhpd zmm1{k1}{z},zmm2,zmm3
    vunpckhps zmm1{k1}{z},zmm2,zmm3
    vunpcklpd zmm1{k1}{z},zmm2,zmm3
    vunpcklps zmm1{k1}{z},zmm2,zmm3
    vunpckhpd zmm1{k1}{z},zmm2,[rax]
    vunpckhps zmm1{k1}{z},zmm2,[rax]
    vunpcklpd zmm1{k1}{z},zmm2,[rax]
    vunpcklps zmm1{k1}{z},zmm2,[rax]

    vunpckhpd zmm30,zmm29,zmm28
    vunpckhpd zmm30{k7},zmm29,zmm28
    vunpckhpd zmm30{k7}{z},zmm29,zmm28
    vunpckhpd zmm30,zmm29,zmmword ptr [rcx]
    vunpckhpd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vunpckhpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vunpckhpd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vunpckhpd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vunpckhpd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vunpckhpd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vunpckhpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vunpckhpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vunpckhpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vunpckhpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vunpckhps zmm30,zmm29,zmm28
    vunpckhps zmm30{k7},zmm29,zmm28
    vunpckhps zmm30{k7}{z},zmm29,zmm28
    vunpckhps zmm30,zmm29,zmmword ptr [rcx]
    vunpckhps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vunpckhps zmm30,zmm29,dword ptr [rcx]{1to16}
    vunpckhps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vunpckhps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vunpckhps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vunpckhps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vunpckhps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vunpckhps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vunpckhps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vunpckhps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vunpcklpd zmm30,zmm29,zmm28
    vunpcklpd zmm30{k7},zmm29,zmm28
    vunpcklpd zmm30{k7}{z},zmm29,zmm28
    vunpcklpd zmm30,zmm29,zmmword ptr [rcx]
    vunpcklpd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vunpcklpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vunpcklpd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vunpcklpd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vunpcklpd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vunpcklpd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vunpcklpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vunpcklpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vunpcklpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vunpcklpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vunpcklps zmm30,zmm29,zmm28
    vunpcklps zmm30{k7},zmm29,zmm28
    vunpcklps zmm30{k7}{z},zmm29,zmm28
    vunpcklps zmm30,zmm29,zmmword ptr [rcx]
    vunpcklps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vunpcklps zmm30,zmm29,dword ptr [rcx]{1to16}
    vunpcklps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vunpcklps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vunpcklps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vunpcklps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vunpcklps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vunpcklps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vunpcklps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vunpcklps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpsllw	xmm1{k1}{z},xmm2,xmm3
    vpsllw	ymm1{k1}{z},ymm2,xmm3
    vpsllw	zmm1{k1}{z},zmm2,xmm3
    vpsllw	xmm1{k1}{z},xmm2,[rax]
    vpsllw	ymm1{k1}{z},ymm2,[rax]
    vpsllw	zmm1{k1}{z},zmm2,[rax]

    vpsllw	xmm1{k1}{z},xmm2,7
    vpsllw	ymm1{k1}{z},ymm2,7
    vpsllw	zmm1{k1}{z},zmm2,7
    vpsllw	xmm1{k1}{z},[rax],7
    vpsllw	ymm1{k1}{z},[rax],7
    vpsllw	zmm1{k1}{z},[rax],7

    vpermw	xmm1, xmm2, xmm3
    vpermw	ymm1, ymm2, ymm3
    vpermw	zmm1, zmm2, zmm3
    vpermw	zmm3, zmm2, zmm1

    vpsravw	xmm1, xmm2, xmm3
    vpsravw	ymm1, ymm2, ymm3
    vpsravw	zmm1, zmm2, zmm3

    vpsravq	xmm1, xmm2, xmm3
    vpsravq	ymm1, ymm2, ymm3
    vpsravq	zmm1, zmm2, zmm3

    vpsrlvw	xmm1, xmm2, xmm3
    vpsrlvw	ymm1, ymm2, ymm3
    vpsrlvw	zmm1, zmm2, zmm3

    vpermw	zmm1{k1},zmm2,zmm3
    vpermw	zmm1{k1}{z},zmm2,zmm3
    vpermw	zmm1{k2}{z},zmm2,zmm3
    vpermw	zmm1{k3}{z},zmm2,zmm3
    vpermw	zmm1{k4}{z},zmm2,zmm3
    vpermw	zmm1{k5}{z},zmm2,zmm3
    vpermw	zmm1{k6}{z},zmm2,zmm3
    vpermw	zmm1{k7}{z},zmm2,zmm3

    vpermw	xmm1,xmm2,[rax]
    vpermw	xmm1{k1},xmm2,[rax]
    vpermw	xmm1{k1}{z},xmm2,[rax]
    vpermw	xmm1{k2}{z},xmm2,[rax]
    vpermw	xmm1{k3}{z},xmm2,[rax]
    vpermw	xmm1{k4}{z},xmm2,[rax]
    vpermw	xmm1{k5}{z},xmm2,[rax]
    vpermw	xmm1{k6}{z},xmm2,[rax]
    vpermw	xmm1{k7}{z},xmm2,[rax]

    vpermw	ymm1,ymm2,[rax]
    vpermw	ymm1{k1},ymm2,[rax]
    vpermw	ymm1{k1}{z},ymm2,[rax]
    vpermw	ymm1{k2}{z},ymm2,[rax]
    vpermw	ymm1{k3}{z},ymm2,[rax]
    vpermw	ymm1{k4}{z},ymm2,[rax]
    vpermw	ymm1{k5}{z},ymm2,[rax]
    vpermw	ymm1{k6}{z},ymm2,[rax]
    vpermw	ymm1{k7}{z},ymm2,[rax]

    vpermw	zmm1,zmm2,[rax]
    vpermw	zmm1{k1},zmm2,[rax]
    vpermw	zmm1{k1}{z},zmm2,[rax]
    vpermw	zmm1{k2}{z},zmm2,[rax]
    vpermw	zmm1{k3}{z},zmm2,[rax]
    vpermw	zmm1{k4}{z},zmm2,[rax]
    vpermw	zmm1{k5}{z},zmm2,[rax]
    vpermw	zmm1{k6}{z},zmm2,[rax]
    vpermw	zmm1{k7}{z},zmm2,[rax]

    vpermw	zmm21,zmm2, zmm3
    vpermw	zmm21,zmm21,zmm3
    vpermw	zmm21,zmm21,zmm31
    vpermw	zmm21,zmm2, zmm31
    vpermw	zmm1, zmm2, zmm31
    vpermw	zmm1, zmm20,zmm31
    vpermw	zmm1, zmm20,zmm3

    vpandd zmm1{k1}{z},zmm2,zmm3
    vpandd zmm30,zmm29,zmm28
    vpandd zmm30{k7},zmm29,zmm28
    vpandd zmm30{k7}{z},zmm29,zmm28
    vpandd zmm30,zmm29,zmmword ptr [rcx]
    vpandd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpandd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpandd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpandd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpandd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpandd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpandd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpandd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpandd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpandd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpandq zmm1{k1}{z},zmm2,zmm3
    vpandq zmm30,zmm29,zmm28
    vpandq zmm30{k7},zmm29,zmm28
    vpandq zmm30{k7}{z},zmm29,zmm28
    vpandq zmm30,zmm29,zmmword ptr [rcx]
    vpandq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpandq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpandq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpandq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpandq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpandq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpandq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpandq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpandq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpandq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpandnd zmm1{k1}{z},zmm2,zmm3
    vpandnd zmm30,zmm29,zmm28
    vpandnd zmm30{k7},zmm29,zmm28
    vpandnd zmm30{k7}{z},zmm29,zmm28
    vpandnd zmm30,zmm29,zmmword ptr [rcx]
    vpandnd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpandnd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpandnd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpandnd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpandnd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpandnd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpandnd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpandnd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpandnd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpandnd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpandnq zmm1{k1}{z},zmm2,zmm3
    vpandnq zmm30,zmm29,zmm28
    vpandnq zmm30{k7},zmm29,zmm28
    vpandnq zmm30{k7}{z},zmm29,zmm28
    vpandnq zmm30,zmm29,zmmword ptr [rcx]
    vpandnq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpandnq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpandnq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpandnq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpandnq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpandnq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpandnq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpandnq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpandnq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpandnq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpxord zmm1{k1}{z},zmm2,zmm3
    vpxord zmm30,zmm29,zmm28
    vpxord zmm30{k7},zmm29,zmm28
    vpxord zmm30{k7}{z},zmm29,zmm28
    vpxord zmm30,zmm29,zmmword ptr [rcx]
    vpxord zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpxord zmm30,zmm29,dword ptr [rcx]{1to16}
    vpxord zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpxord zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpxord zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpxord zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpxord zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpxord zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpxord zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpxord zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpxorq zmm1{k1}{z},zmm2,zmm3
    vpxorq zmm30,zmm29,zmm28
    vpxorq zmm30{k7},zmm29,zmm28
    vpxorq zmm30{k7}{z},zmm29,zmm28
    vpxorq zmm30,zmm29,zmmword ptr [rcx]
    vpxorq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpxorq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpxorq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpxorq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpxorq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpxorq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpxorq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpxorq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpxorq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpxorq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpsraq xmm1{k1}{z},xmm2,xmm3
    vpsraq ymm1{k1}{z},ymm2,xmm3
    vpsraq zmm1{k1}{z},zmm2,xmm3
    vpsraq xmm1{k1}{z},xmm2,[rax]
    vpsraq ymm1{k1}{z},ymm2,[rax]
    vpsraq zmm1{k1}{z},zmm2,[rax]
    vpsraq xmm1{k1}{z},xmm2,7
    vpsraq ymm1{k1}{z},ymm2,7
    vpsraq zmm1{k1}{z},zmm2,7
    vpsraq xmm1{k1}{z},[rax],7
    vpsraq ymm1{k1}{z},[rax],7
    vpsraq zmm1{k1}{z},[rax],7
    vpsraq zmm30{k7},zmm29,xmm28
    vpsraq zmm30{k7}{z},zmm29,xmm28
    vpsraq zmm30{k7},zmm29,oword ptr [rcx]
    vpsraq zmm30{k7},zmm29,oword ptr [rax+r14*8+0x123]
    vpsraq zmm30{k7},zmm29,oword ptr [rdx+0x7f0]
    vpsraq zmm30{k7},zmm29,oword ptr [rdx+0x800]
    vpsraq zmm30{k7},zmm29,oword ptr [rdx-0x800]
    vpsraq zmm30{k7},zmm29,oword ptr [rdx-0x810]

    vpsraq zmm30,zmm29,0xab
    vpsraq zmm30{k7},zmm29,0xab
    vpsraq zmm30{k7}{z},zmm29,0xab
    vpsraq zmm30,zmm29,0x7b
    vpsraq zmm30,zmmword ptr [rcx],0x7b
    vpsraq zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vpsraq zmm30,qword ptr [rcx]{1to8},0x7b
    vpsraq zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vpsraq zmm30,zmmword ptr [rdx+0x2000],0x7b
    vpsraq zmm30,zmmword ptr [rdx-0x2000],0x7b
    vpsraq zmm30,zmmword ptr [rdx-0x2040],0x7b
    vpsraq zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpsraq zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpsraq zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpsraq zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vpconflictd zmm30,zmm1
    vpconflictd zmm30,zmm31
    vpconflictd zmm1,zmm31
    vpconflictd zmm3,zmm1
    vpconflictd xmm27,xmm3
    vpconflictd ymm27,ymm3

    vpconflictd zmm30,zmm29
    vpconflictd zmm30{k7},zmm29
    vpconflictd zmm30{k7}{z},zmm29
    vpconflictd zmm30,zmmword ptr [rcx]
    vpconflictd zmm30,zmmword ptr [rax+r14*8+0x123]
    vpconflictd zmm30,dword ptr [rcx]{1to16}
    vpconflictd zmm30,zmmword ptr [rdx+0x1fc0]
    vpconflictd zmm30,zmmword ptr [rdx+0x2000]
    vpconflictd zmm30,zmmword ptr [rdx-0x2000]
    vpconflictd zmm30,zmmword ptr [rdx-0x2040]
    vpconflictd zmm30,dword ptr [rdx+0x1fc]{1to16}
    vpconflictd zmm30,dword ptr [rdx+0x200]{1to16}
    vpconflictd zmm30,dword ptr [rdx-0x200]{1to16}
    vpconflictd zmm30,dword ptr [rdx-0x204]{1to16}
    vpconflictq zmm30,zmm29
    vpconflictq zmm30{k7},zmm29
    vpconflictq zmm30{k7}{z},zmm29
    vpconflictq zmm30,zmmword ptr [rcx]
    vpconflictq zmm30,zmmword ptr [rax+r14*8+0x123]
    vpconflictq zmm30,qword ptr [rcx]{1to8}
    vpconflictq zmm30,zmmword ptr [rdx+0x1fc0]
    vpconflictq zmm30,zmmword ptr [rdx+0x2000]
    vpconflictq zmm30,zmmword ptr [rdx-0x2000]
    vpconflictq zmm30,zmmword ptr [rdx-0x2040]
    vpconflictq zmm30,qword ptr [rdx+0x3f8]{1to8}
    vpconflictq zmm30,qword ptr [rdx+0x400]{1to8}
    vpconflictq zmm30,qword ptr [rdx-0x400]{1to8}
    vpconflictq zmm30,qword ptr [rdx-0x408]{1to8}

    vplzcntd	zmm30,zmm29
    vplzcntd	zmm30{k7},zmm29
    vplzcntd	zmm30{k7}{z},zmm29
    vplzcntd	zmm30,zmmword ptr [rcx]
    vplzcntd	zmm30,zmmword ptr [rax+r14*8+0x123]
    vplzcntd	zmm30,dword ptr [rcx]{1to16}
    vplzcntd	zmm30,zmmword ptr [rdx+0x1fc0]
    vplzcntd	zmm30,zmmword ptr [rdx+0x2000]
    vplzcntd	zmm30,zmmword ptr [rdx-0x2000]
    vplzcntd	zmm30,zmmword ptr [rdx-0x2040]
    vplzcntd	zmm30,dword ptr [rdx+0x1fc]{1to16}
    vplzcntd	zmm30,dword ptr [rdx+0x200]{1to16}
    vplzcntd	zmm30,dword ptr [rdx-0x200]{1to16}
    vplzcntd	zmm30,dword ptr [rdx-0x204]{1to16}
    vplzcntq	zmm30,zmm29
    vplzcntq	zmm30{k7},zmm29
    vplzcntq	zmm30{k7}{z},zmm29
    vplzcntq	zmm30,zmmword ptr [rcx]
    vplzcntq	zmm30,zmmword ptr [rax+r14*8+0x123]
    vplzcntq	zmm30,qword ptr [rcx]{1to8}
    vplzcntq	zmm30,zmmword ptr [rdx+0x1fc0]
    vplzcntq	zmm30,zmmword ptr [rdx+0x2000]
    vplzcntq	zmm30,zmmword ptr [rdx-0x2000]
    vplzcntq	zmm30,zmmword ptr [rdx-0x2040]
    vplzcntq	zmm30,qword ptr [rdx+0x3f8]{1to8}
    vplzcntq	zmm30,qword ptr [rdx+0x400]{1to8}
    vplzcntq	zmm30,qword ptr [rdx-0x400]{1to8}
    vplzcntq	zmm30,qword ptr [rdx-0x408]{1to8}

    vptestnmd	k5,zmm29,zmm28
    vptestnmd	k5{k7},zmm29,zmm28
    vptestnmd	k5,zmm29,zmmword ptr [rcx]
    vptestnmd	k5,zmm29,zmmword ptr [rax+r14*8+0x123]
    vptestnmd	k5,zmm29,dword ptr [rcx]{1to16}
    vptestnmd	k5,zmm29,zmmword ptr [rdx+0x1fc0]
    vptestnmd	k5,zmm29,zmmword ptr [rdx+0x2000]
    vptestnmd	k5,zmm29,zmmword ptr [rdx-0x2000]
    vptestnmd	k5,zmm29,zmmword ptr [rdx-0x2040]
    vptestnmd	k5,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vptestnmd	k5,zmm29,dword ptr [rdx+0x200]{1to16}
    vptestnmd	k5,zmm29,dword ptr [rdx-0x200]{1to16}
    vptestnmd	k5,zmm29,dword ptr [rdx-0x204]{1to16}
    vptestnmq	k5,zmm29,zmm28
    vptestnmq	k5{k7},zmm29,zmm28
    vptestnmq	k5,zmm29,zmmword ptr [rcx]
    vptestnmq	k5,zmm29,zmmword ptr [rax+r14*8+0x123]
    vptestnmq	k5,zmm29,qword ptr [rcx]{1to8}
    vptestnmq	k5,zmm29,zmmword ptr [rdx+0x1fc0]
    vptestnmq	k5,zmm29,zmmword ptr [rdx+0x2000]
    vptestnmq	k5,zmm29,zmmword ptr [rdx-0x2000]
    vptestnmq	k5,zmm29,zmmword ptr [rdx-0x2040]
    vptestnmq	k5,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vptestnmq	k5,zmm29,qword ptr [rdx+0x400]{1to8}
    vptestnmq	k5,zmm29,qword ptr [rdx-0x400]{1to8}
    vptestnmq	k5,zmm29,qword ptr [rdx-0x408]{1to8}

    vpbroadcastmw2d zmm30,k6
    vpbroadcastmb2q zmm30,k6

    kaddb	k1,k2,k3
    kaddw	k1,k2,k3
    kandb	k1,k2,k3
    kandw	k1,k2,k3
    kandnb	k1,k2,k3
    kandnw	k1,k2,k3
    korb	k1,k2,k3
    korw	k1,k2,k3
    kxorb	k1,k2,k3
    kxorw	k1,k2,k3
    kxnorb	k1,k2,k3
    kxnorw	k1,k2,k3

    kunpckbw	k1,k2,k3
    kunpckwd	k1,k2,k3

    kaddd	k1,k2,k3
    kaddq	k1,k2,k3
    kandd	k1,k2,k3
    kandq	k1,k2,k3
    kandnd	k1,k2,k3
    kandnq	k1,k2,k3
    kord	k1,k2,k3
    korq	k1,k2,k3
    kxord	k1,k2,k3
    kxorq	k1,k2,k3
    kxnord	k1,k2,k3
    kxnorq	k1,k2,k3
    kunpckdq	k1,k2,k3

    knotb	k1,k2
    knotw	k1,k2
    knotd	k1,k2
    knotq	k1,k2

    kortestb	k1,k2
    kortestw	k1,k2
    kortestd	k1,k2
    kortestq	k1,k2
    kshiftlb	k1,k2,3
    kshiftlw	k1,k2,3
    kshiftld	k1,k2,3
    kshiftlq	k1,k2,3
    kshiftrb	k1,k2,3
    kshiftrw	k1,k2,3
    kshiftrd	k1,k2,3
    kshiftrq	k1,k2,3

    kmovb	k1,k2
    kmovd	k1,k2
    kmovq	k1,k2
    kmovw	k1,k2
    kmovb	k1,[rax]
    kmovd	k1,[rax]
    kmovq	k1,[rax]
    kmovw	k1,[rax]
    kmovb	[rax],k2
    kmovd	[rax],k2
    kmovq	[rax],k2
    kmovw	[rax],k2

    kandw  k5,k6,k7
    kandnw k5,k6,k7
    korw   k5,k6,k7
    kxnorw k5,k6,k7
    kxorw  k5,k6,k7
    knotw  k5,k6

    kortestw k5,k6
    kshiftrw k5,k6,0xab
    kshiftrw k5,k6,0x7b
    kshiftlw k5,k6,0xab
    kshiftlw k5,k6,0x7b

    kmovw  k5,k6
    kmovw  k5,word ptr [rcx]
    kmovw  k5,word ptr [rax+r14*8+0x123]
    kmovw  word ptr [rcx],k5
    kmovw  word ptr [rax+r14*8+0x123],k5
    kmovw  k5,eax
    kmovw  k5,ebp
    kmovw  k5,r13d
    kmovw  eax,k5
    kmovw  ebp,k5
    kmovw  r13d,k5
    kunpckbw k5,k6,k7

    vexp2ps zmm30,zmm29
    vexp2ps zmm30,zmmword ptr [rcx]
    vexp2ps zmm30,zmmword ptr [rax+r14*8+0x123]
    vexp2ps zmm30,dword ptr [rcx]{1to16}
    vexp2ps zmm30,zmmword ptr [rdx+0x1fc0]
    vexp2ps zmm30,zmmword ptr [rdx+0x2000]
    vexp2ps zmm30,zmmword ptr [rdx-0x2000]
    vexp2ps zmm30,zmmword ptr [rdx-0x2040]
    vexp2ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vexp2ps zmm30,dword ptr [rdx+0x200]{1to16}
    vexp2ps zmm30,dword ptr [rdx-0x200]{1to16}
    vexp2ps zmm30,dword ptr [rdx-0x204]{1to16}

    vexp2pd zmm30,zmm29
    vexp2pd zmm30,zmmword ptr [rcx]
    vexp2pd zmm30,zmmword ptr [rax+r14*8+0x123]
    vexp2pd zmm30,qword ptr [rcx]{1to8}
    vexp2pd zmm30,zmmword ptr [rdx+0x1fc0]
    vexp2pd zmm30,zmmword ptr [rdx+0x2000]
    vexp2pd zmm30,zmmword ptr [rdx-0x2000]
    vexp2pd zmm30,zmmword ptr [rdx-0x2040]
    vexp2pd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vexp2pd zmm30,qword ptr [rdx+0x400]{1to8}
    vexp2pd zmm30,qword ptr [rdx-0x400]{1to8}
    vexp2pd zmm30,qword ptr [rdx-0x408]{1to8}

    vrcp28ps zmm30,zmm29
    vrcp28ps zmm30{k7},zmm29
    vrcp28ps zmm30{k7}{z},zmm29
    vrcp28ps zmm30,zmmword ptr [rcx]
    vrcp28ps zmm30,zmmword ptr [rax+r14*8+0x123]
    vrcp28ps zmm30,dword ptr [rcx]{1to16}
    vrcp28ps zmm30,zmmword ptr [rdx+0x1fc0]
    vrcp28ps zmm30,zmmword ptr [rdx+0x2000]
    vrcp28ps zmm30,zmmword ptr [rdx-0x2000]
    vrcp28ps zmm30,zmmword ptr [rdx-0x2040]
    vrcp28ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vrcp28ps zmm30,dword ptr [rdx+0x200]{1to16}
    vrcp28ps zmm30,dword ptr [rdx-0x200]{1to16}
    vrcp28ps zmm30,dword ptr [rdx-0x204]{1to16}
    vrcp28pd zmm30,zmm29
    vrcp28pd zmm30{k7},zmm29
    vrcp28pd zmm30{k7}{z},zmm29
    vrcp28pd zmm30,zmmword ptr [rcx]
    vrcp28pd zmm30,zmmword ptr [rax+r14*8+0x123]
    vrcp28pd zmm30,qword ptr [rcx]{1to8}
    vrcp28pd zmm30,zmmword ptr [rdx+0x1fc0]
    vrcp28pd zmm30,zmmword ptr [rdx+0x2000]
    vrcp28pd zmm30,zmmword ptr [rdx-0x2000]
    vrcp28pd zmm30,zmmword ptr [rdx-0x2040]
    vrcp28pd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vrcp28pd zmm30,qword ptr [rdx+0x400]{1to8}
    vrcp28pd zmm30,qword ptr [rdx-0x400]{1to8}
    vrcp28pd zmm30,qword ptr [rdx-0x408]{1to8}

    vrcp28ss xmm30{k7},xmm29,xmm28
    vrcp28ss xmm30{k7}{z},xmm29,xmm28
    vrcp28ss xmm30{k7},xmm29,dword ptr [rcx]
    vrcp28ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vrcp28ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vrcp28ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vrcp28ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vrcp28ss xmm30{k7},xmm29,dword ptr [rdx-0x204]
    vrcp28sd xmm30{k7},xmm29,xmm28
    vrcp28sd xmm30{k7}{z},xmm29,xmm28
    vrcp28sd xmm30{k7},xmm29,qword ptr [rcx]
    vrcp28sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vrcp28sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vrcp28sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vrcp28sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vrcp28sd xmm30{k7},xmm29,qword ptr [rdx-0x408]

    vrsqrt28ps zmm30,zmm29
    vrsqrt28ps zmm30{k7},zmm29
    vrsqrt28ps zmm30{k7}{z},zmm29
    vrsqrt28ps zmm30,zmmword ptr [rcx]
    vrsqrt28ps zmm30,zmmword ptr [rax+r14*8+0x123]
    vrsqrt28ps zmm30,dword ptr [rcx]{1to16}
    vrsqrt28ps zmm30,zmmword ptr [rdx+0x1fc0]
    vrsqrt28ps zmm30,zmmword ptr [rdx+0x2000]
    vrsqrt28ps zmm30,zmmword ptr [rdx-0x2000]
    vrsqrt28ps zmm30,zmmword ptr [rdx-0x2040]
    vrsqrt28ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vrsqrt28ps zmm30,dword ptr [rdx+0x200]{1to16}
    vrsqrt28ps zmm30,dword ptr [rdx-0x200]{1to16}
    vrsqrt28ps zmm30,dword ptr [rdx-0x204]{1to16}
    vrsqrt28pd zmm30,zmm29
    vrsqrt28pd zmm30{k7},zmm29
    vrsqrt28pd zmm30{k7}{z},zmm29
    vrsqrt28pd zmm30,zmmword ptr [rcx]
    vrsqrt28pd zmm30,zmmword ptr [rax+r14*8+0x123]
    vrsqrt28pd zmm30,qword ptr [rcx]{1to8}
    vrsqrt28pd zmm30,zmmword ptr [rdx+0x1fc0]
    vrsqrt28pd zmm30,zmmword ptr [rdx+0x2000]
    vrsqrt28pd zmm30,zmmword ptr [rdx-0x2000]
    vrsqrt28pd zmm30,zmmword ptr [rdx-0x2040]
    vrsqrt28pd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vrsqrt28pd zmm30,qword ptr [rdx+0x400]{1to8}
    vrsqrt28pd zmm30,qword ptr [rdx-0x400]{1to8}
    vrsqrt28pd zmm30,qword ptr [rdx-0x408]{1to8}
    vrsqrt28ss xmm30{k7},xmm29,xmm28
    vrsqrt28ss xmm30{k7}{z},xmm29,xmm28
    vrsqrt28ss xmm30{k7},xmm29,dword ptr [rcx]
    vrsqrt28ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vrsqrt28ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vrsqrt28ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vrsqrt28ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vrsqrt28ss xmm30{k7},xmm29,dword ptr [rdx-0x204]
    vrsqrt28sd xmm30{k7},xmm29,xmm28
    vrsqrt28sd xmm30{k7}{z},xmm29,xmm28
    vrsqrt28sd xmm30{k7},xmm29,qword ptr [rcx]
    vrsqrt28sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vrsqrt28sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vrsqrt28sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vrsqrt28sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vrsqrt28sd xmm30{k7},xmm29,qword ptr [rdx-0x408]

    vrsqrt14ps zmm1,zmm2
    vrsqrt14ps zmm1,[rax]
    vrsqrt14ps zmm30,zmm29
    vrsqrt14ps zmm30{k7},zmm29
    vrsqrt14ps zmm30{k7}{z},zmm29
    vrsqrt14ps zmm30,zmmword ptr [rcx]
    vrsqrt14ps zmm30,zmmword ptr [rax+r14*8+0x123]
    vrsqrt14ps zmm30,dword ptr [rcx]{1to16}
    vrsqrt14ps zmm30,zmmword ptr [rdx+0x1fc0]
    vrsqrt14ps zmm30,zmmword ptr [rdx+0x2000]
    vrsqrt14ps zmm30,zmmword ptr [rdx-0x2000]
    vrsqrt14ps zmm30,zmmword ptr [rdx-0x2040]
    vrsqrt14ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx+0x200]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx-0x200]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx-0x204]{1to16}

    vrsqrt14pd zmm30,zmm29
    vrsqrt14pd zmm30{k7},zmm29
    vrsqrt14pd zmm30{k7}{z},zmm29
    vrsqrt14pd zmm30,zmmword ptr [rcx]
    vrsqrt14pd zmm30,zmmword ptr [rax+r14*8+0x123]
    vrsqrt14pd zmm30,qword ptr [rcx]{1to8}
    vrsqrt14pd zmm30,zmmword ptr [rdx+0x1fc0]
    vrsqrt14pd zmm30,zmmword ptr [rdx+0x2000]
    vrsqrt14pd zmm30,zmmword ptr [rdx-0x2000]
    vrsqrt14pd zmm30,zmmword ptr [rdx-0x2040]
    vrsqrt14pd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vrsqrt14pd zmm30,qword ptr [rdx+0x400]{1to8}
    vrsqrt14pd zmm30,qword ptr [rdx-0x400]{1to8}
    vrsqrt14pd zmm30,qword ptr [rdx-0x408]{1to8}

    vrsqrt14ps zmm30,zmm29
    vrsqrt14ps zmm30{k7},zmm29
    vrsqrt14ps zmm30{k7}{z},zmm29
    vrsqrt14ps zmm30,zmmword ptr [rcx]
    vrsqrt14ps zmm30,zmmword ptr [rax+r14*8+0x123]
    vrsqrt14ps zmm30,dword ptr [rcx]{1to16}
    vrsqrt14ps zmm30,zmmword ptr [rdx+0x1fc0]
    vrsqrt14ps zmm30,zmmword ptr [rdx+0x2000]
    vrsqrt14ps zmm30,zmmword ptr [rdx-0x2000]
    vrsqrt14ps zmm30,zmmword ptr [rdx-0x2040]
    vrsqrt14ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx+0x200]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx-0x200]{1to16}
    vrsqrt14ps zmm30,dword ptr [rdx-0x204]{1to16}

    vrsqrt14sd xmm30{k7},xmm29,xmm28
    vrsqrt14sd xmm30{k7}{z},xmm29,xmm28
    vrsqrt14sd xmm30{k7},xmm29,qword ptr [rcx]
    vrsqrt14sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vrsqrt14sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vrsqrt14sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vrsqrt14sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vrsqrt14sd xmm30{k7},xmm29,qword ptr [rdx-0x408]

    vrsqrt14ss xmm1,xmm2,xmm3
    vrsqrt14ss xmm1,xmm2,[rax]
    vrsqrt14ss xmm30,xmm29,xmm3
    vrsqrt14ss xmm30{k7},xmm29,xmm3
    vrsqrt14ss xmm30{k7}{z},xmm29,xmm3
    vrsqrt14ss xmm30,xmm3,dword ptr [rcx]
    vrsqrt14ss xmm30,xmm3,dword ptr [rax+r14*8+0x123]
    vrsqrt14ss xmm30,xmm3,dword ptr [rcx]
    vrsqrt14ss xmm30,xmm3,dword ptr [rdx+0x1fc0]
    vrsqrt14ss xmm30,xmm3,dword ptr [rdx+0x2000]
    vrsqrt14ss xmm30,xmm3,dword ptr [rdx-0x2000]
    ;vrsqrt14ss xmm30,xmm3,xmmword ptr [rdx-0x2040]
    vrsqrt14ss xmm30,xmm3,dword ptr [rdx+0x1fc]
    vrsqrt14ss xmm30,xmm3,dword ptr [rdx+0x200]
    vrsqrt14ss xmm30,xmm3,dword ptr [rdx-0x200]
    vrsqrt14ss xmm30,xmm3,dword ptr [rdx-0x204]
    vrsqrt14ss xmm30{k7},xmm29,xmm28
    vrsqrt14ss xmm30{k7}{z},xmm29,xmm28
    vrsqrt14ss xmm30{k7},xmm29,dword ptr [rcx]
    vrsqrt14ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vrsqrt14ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vrsqrt14ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vrsqrt14ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vrsqrt14ss xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vmovdqa32 xmm1{k1}{z},xmm2
    vmovdqa32 xmm2{k1}{z},xmm1
    vmovdqa32 ymm1{k1}{z},ymm2
    vmovdqa32 ymm2{k1}{z},ymm1
    vmovdqa32 zmm1{k1}{z},zmm2
    vmovdqa32 zmm2{k1}{z},zmm1

    vmovdqa32 xmm1{k1}{z},[rcx]
    vmovdqa32 [rcx], xmm1
    vmovdqa32 ymm1{k1}{z},[rcx]
    vmovdqa32 [rcx],ymm1
    vmovdqa32 zmm1{k1}{z},[rcx]
    vmovdqa32 [rcx], zmm1

    vmovdqa64 xmm1{k1}{z},xmm2
    vmovdqa64 xmm2{k1}{z},xmm1
    vmovdqa64 ymm1{k1}{z},ymm2
    vmovdqa64 ymm2{k1}{z},ymm1
    vmovdqa64 zmm1{k1}{z},zmm2
    vmovdqa64 zmm2{k1}{z},zmm1

    vmovdqa64 xmm1{k1}{z},[rcx]
    vmovdqa64 [rcx], xmm1
    vmovdqa64 ymm1{k1}{z},[rcx]
    vmovdqa64 [rcx],ymm1
    vmovdqa64 zmm1{k1}{z},[rcx]
    vmovdqa64 [rcx], zmm1

    vmovdqa32 zmm30,zmm29
    vmovdqa32 zmm30{k7},zmm29
    vmovdqa32 zmm30{k7}{z},zmm29
    vmovdqa32 zmm30,zmmword ptr [rcx]
    vmovdqa32 zmm30,zmmword ptr [rax+r14*8+0x123]
    vmovdqa32 zmm30,zmmword ptr [rdx+0x1fc0]
    vmovdqa32 zmm30,zmmword ptr [rdx+0x2000]
    vmovdqa32 zmm30,zmmword ptr [rdx-0x2000]
    vmovdqa32 zmm30,zmmword ptr [rdx-0x2040]
    vmovdqa64 zmm30,zmm29
    vmovdqa64 zmm30{k7},zmm29
    vmovdqa64 zmm30{k7}{z},zmm29
    vmovdqa64 zmm30,zmmword ptr [rcx]
    vmovdqa64 zmm30,zmmword ptr [rax+r14*8+0x123]
    vmovdqa64 zmm30,zmmword ptr [rdx+0x1fc0]
    vmovdqa64 zmm30,zmmword ptr [rdx+0x2000]
    vmovdqa64 zmm30,zmmword ptr [rdx-0x2000]
    vmovdqa64 zmm30,zmmword ptr [rdx-0x2040]
    vmovdqu32 zmm30,zmm29
    vmovdqu32 zmm30{k7},zmm29
    vmovdqu32 zmm30{k7}{z},zmm29
    vmovdqu32 zmm30,zmmword ptr [rcx]
    vmovdqu32 zmm30,zmmword ptr [rax+r14*8+0x123]
    vmovdqu32 zmm30,zmmword ptr [rdx+0x1fc0]
    vmovdqu32 zmm30,zmmword ptr [rdx+0x2000]
    vmovdqu32 zmm30,zmmword ptr [rdx-0x2000]
    vmovdqu32 zmm30,zmmword ptr [rdx-0x2040]
    vmovdqu64 zmm30,zmm29
    vmovdqu64 zmm30{k7},zmm29
    vmovdqu64 zmm30{k7}{z},zmm29
    vmovdqu64 zmm30,zmmword ptr [rcx]
    vmovdqu64 zmm30,zmmword ptr [rax+r14*8+0x123]
    vmovdqu64 zmm30,zmmword ptr [rdx+0x1fc0]
    vmovdqu64 zmm30,zmmword ptr [rdx+0x2000]
    vmovdqu64 zmm30,zmmword ptr [rdx-0x2000]
    vmovdqu64 zmm30,zmmword ptr [rdx-0x2040]

    vmovdqa32 zmmword ptr [rcx],zmm30
    vmovdqa32 zmmword ptr [rcx]{k7},zmm30
    vmovdqa32 zmmword ptr [rax+r14*8+0x123],zmm30
    vmovdqa32 zmmword ptr [rdx+0x1fc0],zmm30
    vmovdqa32 zmmword ptr [rdx+0x2000],zmm30
    vmovdqa32 zmmword ptr [rdx-0x2000],zmm30
    vmovdqa32 zmmword ptr [rdx-0x2040],zmm30
    vmovdqa64 zmmword ptr [rcx],zmm30
    vmovdqa64 zmmword ptr [rcx]{k7},zmm30
    vmovdqa64 zmmword ptr [rax+r14*8+0x123],zmm30
    vmovdqa64 zmmword ptr [rdx+0x1fc0],zmm30
    vmovdqa64 zmmword ptr [rdx+0x2000],zmm30
    vmovdqa64 zmmword ptr [rdx-0x2000],zmm30
    vmovdqa64 zmmword ptr [rdx-0x2040],zmm30
    vmovdqu32 zmmword ptr [rcx],zmm30
    vmovdqu32 zmmword ptr [rcx]{k7},zmm30
    vmovdqu32 zmmword ptr [rax+r14*8+0x123],zmm30
    vmovdqu32 zmmword ptr [rdx+0x1fc0],zmm30
    vmovdqu32 zmmword ptr [rdx+0x2000],zmm30
    vmovdqu32 zmmword ptr [rdx-0x2000],zmm30
    vmovdqu32 zmmword ptr [rdx-0x2040],zmm30
    vmovdqu64 zmmword ptr [rcx],zmm30
    vmovdqu64 zmmword ptr [rcx]{k7},zmm30
    vmovdqu64 zmmword ptr [rax+r14*8+0x123],zmm30
    vmovdqu64 zmmword ptr [rdx+0x1fc0],zmm30
    vmovdqu64 zmmword ptr [rdx+0x2000],zmm30
    vmovdqu64 zmmword ptr [rdx-0x2000],zmm30
    vmovdqu64 zmmword ptr [rdx-0x2040],zmm30

    vmovdqu8 xmm1{k1}{z},xmm2
    vmovdqu8 xmm2{k1}{z},xmm1
    vmovdqu8 ymm1{k1}{z},ymm2
    vmovdqu8 ymm2{k1}{z},ymm1
    vmovdqu8 zmm1{k1}{z},zmm2
    vmovdqu8 zmm2{k1}{z},zmm1

    vmovdqu8 xmm1{k1}{z},[rax]
    vmovdqu8 [rax],xmm1
    vmovdqu8 ymm1{k1}{z},[rax]
    vmovdqu8 [rax],ymm1
    vmovdqu8 zmm1{k1}{z},[rax]
    vmovdqu8 [rax],zmm1

    vmovdqu16 xmm1{k1}{z},xmm2
    vmovdqu16 xmm2{k1}{z},xmm1
    vmovdqu16 ymm1{k1}{z},ymm2
    vmovdqu16 ymm2{k1}{z},ymm1
    vmovdqu16 zmm1{k1}{z},zmm2
    vmovdqu16 zmm2{k1}{z},zmm1

    vmovdqu16 xmm1{k1}{z},[rax]
    vmovdqu16 [rax],xmm1
    vmovdqu16 ymm1{k1}{z},[rax]
    vmovdqu16 [rax],ymm1
    vmovdqu16 zmm1{k1}{z},[rax]
    vmovdqu16 [rax],zmm1

    vmovdqu32 xmm1{k1}{z},xmm2
    vmovdqu32 xmm2{k1}{z},xmm1
    vmovdqu32 ymm1{k1}{z},ymm2
    vmovdqu32 ymm2{k1}{z},ymm1
    vmovdqu32 zmm1{k1}{z},zmm2
    vmovdqu32 zmm2{k1}{z},zmm1

    vmovdqu32 xmm1{k1}{z},[rax]
    vmovdqu32 [rax],xmm1
    vmovdqu32 ymm1{k1}{z},[rax]
    vmovdqu32 [rax],ymm1
    vmovdqu32 zmm1{k1}{z},[rax]
    vmovdqu32 [rax],zmm1

    vmovdqu64 xmm1{k1}{z},xmm2
    vmovdqu64 xmm2{k1}{z},xmm1
    vmovdqu64 ymm1{k1}{z},ymm2
    vmovdqu64 ymm2{k1}{z},ymm1
    vmovdqu64 zmm1{k1}{z},zmm2
    vmovdqu64 zmm2{k1}{z},zmm1

    vmovdqu64 xmm1{k1}{z},[rax]
    vmovdqu64 [rax],xmm1
    vmovdqu64 ymm1{k1}{z},[rax]
    vmovdqu64 [rax],ymm1
    vmovdqu64 zmm1{k1}{z},[rax]
    vmovdqu64 [rax],zmm1

    vbroadcastf32x2 ymm1{k1}{z},xmm2
    vbroadcastf32x2 zmm1{k1}{z},xmm2
    vbroadcastf32x2 ymm1,[rax]
    vbroadcastf32x2 zmm1,[rax]
    vbroadcastf32x2 ymm1,qword ptr [rax]
    vbroadcastf32x2 zmm1,qword ptr [rax]

    vbroadcastf32x4 ymm1{k1}{z},[rax]
    vbroadcastf32x4 zmm1{k1}{z},[rax]
    vbroadcastf32x8 zmm1{k1}{z},[rax]
    vbroadcastf64x2 ymm1{k1}{z},[rax]
    vbroadcastf64x2 zmm1{k1}{z},[rax]
    vbroadcastf64x4 zmm1{k1}{z},[rax]

    vbroadcastf32x4 ymm1,oword ptr [rax]
    vbroadcastf32x4 zmm1,oword ptr [rax]
    vbroadcastf32x8 zmm1,ymmword ptr [rax]
    vbroadcastf64x2 ymm1,oword ptr [rax]
    vbroadcastf64x2 zmm1,oword ptr [rax]
    vbroadcastf64x4 zmm1,ymmword ptr [rax]

    vcompresspd xmm1,xmm2
    vcompresspd [rcx],xmm2
    vcompresspd ymm1,ymm2
    vcompresspd [rcx],ymm2
    vcompressps zmm1,zmm2
    vcompressps [rcx],zmm2

    vcompresspd zmm1,zmm2
    vcompresspd [rcx],zmm2
    vcompresspd zmmword ptr [rcx],zmm30
    vcompresspd zmmword ptr [rcx]{k7},zmm30
    vcompresspd zmmword ptr [rax+r14*8+0x123],zmm30
    vcompresspd zmmword ptr [rdx+0x3f8],zmm30
    vcompresspd zmmword ptr [rdx+0x400],zmm30
    vcompresspd zmmword ptr [rdx-0x400],zmm30
    vcompresspd zmmword ptr [rdx-0x408],zmm30
    vcompresspd zmm30,zmm29
    vcompresspd zmm30{k7},zmm29
    vcompresspd zmm30{k7}{z},zmm29

    vcompressps zmmword ptr [rcx],zmm30
    vcompressps zmmword ptr [rcx]{k7},zmm30
    vcompressps zmmword ptr [rax+r14*8+0x123],zmm30
    vcompressps zmmword ptr [rdx+0x1fc],zmm30
    vcompressps zmmword ptr [rdx+0x200],zmm30
    vcompressps zmmword ptr [rdx-0x200],zmm30
    vcompressps zmmword ptr [rdx-0x204],zmm30
    vcompressps zmm30,zmm29
    vcompressps zmm30{k7},zmm29
    vcompressps zmm30{k7}{z},zmm29

    vcvtpd2qq xmm1{k1}{z},xmm2
    vcvtpd2qq ymm1{k1}{z},ymm2
    vcvtpd2qq zmm1{k1}{z},zmm2
    vcvtpd2qq xmm1,[rax]
    vcvtpd2qq ymm1,[rax]
    vcvtpd2qq zmm1,[rax]
    vcvtpd2qq xmm1,oword ptr [rax]
    vcvtpd2qq ymm1,ymmword ptr [rax]
    vcvtpd2qq zmm1,zmmword ptr [rax]

    vcvtpd2qq xmm16,xmm20
    vcvtpd2qq ymm16,ymm20
    vcvtpd2qq zmm16,zmm20

    vcvtps2qq xmm1{k1}{z},xmm2
    vcvtps2qq ymm1{k1}{z},xmm2
    vcvtps2qq zmm1{k1}{z},ymm2
    vcvtps2qq xmm1,[rax]
    vcvtps2qq ymm1,[rax]
    vcvtps2qq zmm1,[rax]
    vcvtps2qq xmm1,qword ptr [rax]
    vcvtps2qq ymm1,oword ptr [rax]
    vcvtps2qq zmm1,ymmword ptr [rax]

    vcvtps2qq xmm16,[rax]
    vcvtps2qq ymm16,[rax]
    vcvtps2qq zmm16,[rax]

    vcvtpd2udq xmm1{k1}{z},xmm2
    vcvtpd2udq xmm1{k1}{z},ymm2
    vcvtpd2udq ymm1{k1}{z},zmm2
    vcvtpd2udq xmm1,oword ptr [rax]
    vcvtpd2udq xmm1,ymmword ptr [rax]
    vcvtpd2udq ymm1,zmmword ptr [rax]

    vcvtpd2udq ymm30{k7},zmm29
    vcvtpd2udq ymm30{k7}{z},zmm29
    vcvtpd2udq ymm30{k7},zmm29,{rn-sae}
    vcvtpd2udq ymm30{k7},zmm29,{ru-sae}
    vcvtpd2udq ymm30{k7},zmm29,{rd-sae}
    vcvtpd2udq ymm30{k7},zmm29,{rz-sae}
    vcvtpd2udq ymm30{k7},zmmword ptr [rcx]
    vcvtpd2udq ymm30{k7},zmmword ptr [rax+r14*8+0x123]
    vcvtpd2udq ymm30{k7},qword ptr [rcx]{1to8}
    vcvtpd2udq ymm30{k7},zmmword ptr [rdx+0x1fc0]
    vcvtpd2udq ymm30{k7},zmmword ptr [rdx+0x2000]
    vcvtpd2udq ymm30{k7},zmmword ptr [rdx-0x2000]
    vcvtpd2udq ymm30{k7},zmmword ptr [rdx-0x2040]
    vcvtpd2udq ymm30{k7},qword ptr [rdx+0x3f8]{1to8}
    vcvtpd2udq ymm30{k7},qword ptr [rdx+0x400]{1to8}
    vcvtpd2udq ymm30{k7},qword ptr [rdx-0x400]{1to8}
    vcvtpd2udq ymm30{k7},qword ptr [rdx-0x408]{1to8}

    vcvtps2udq xmm1{k1}{z},xmm2
    vcvtps2udq ymm1{k1}{z},ymm2
    vcvtps2udq zmm1{k1}{z},zmm2
    vcvtps2udq xmm1,[rax]
    vcvtps2udq ymm1,[rax]
    vcvtps2udq zmm1,[rax]
    vcvtps2udq zmm30,zmm29
    vcvtps2udq zmm30{k7},zmm29
    vcvtps2udq zmm30{k7}{z},zmm29
    vcvtps2udq zmm30,zmm29,{rn-sae}
    vcvtps2udq zmm30,zmm29,{ru-sae}
    vcvtps2udq zmm30,zmm29,{rd-sae}
    vcvtps2udq zmm30,zmm29,{rz-sae}
    vcvtps2udq zmm30,zmmword ptr [rcx]
    vcvtps2udq zmm30,zmmword ptr [rax+r14*8+0x123]
    vcvtps2udq zmm30,dword ptr [rcx]{1to16}
    vcvtps2udq zmm30,zmmword ptr [rdx+0x1fc0]
    vcvtps2udq zmm30,zmmword ptr [rdx+0x2000]
    vcvtps2udq zmm30,zmmword ptr [rdx-0x2000]
    vcvtps2udq zmm30,zmmword ptr [rdx-0x2040]
    vcvtps2udq zmm30,dword ptr [rdx+0x1fc]{1to16}
    vcvtps2udq zmm30,dword ptr [rdx+0x200]{1to16}
    vcvtps2udq zmm30,dword ptr [rdx-0x200]{1to16}
    vcvtps2udq zmm30,dword ptr [rdx-0x204]{1to16}

    vcvtpd2uqq xmm1 {k1}{z}, xmm2
    vcvtpd2uqq ymm1 {k1}{z}, ymm2
    vcvtpd2uqq zmm1 {k1}{z}, zmm2
    vcvtpd2uqq xmm1, oword ptr [rax]
    vcvtpd2uqq ymm1, ymmword ptr [rax]
    vcvtpd2uqq zmm1, zmmword ptr [rax]
    vcvtpd2uqq xmm1, [rax]
    vcvtpd2uqq ymm1, [rax]
    vcvtpd2uqq zmm1, [rax]

    vcvtps2uqq xmm1 {k1}{z}, xmm2
    vcvtps2uqq ymm1 {k1}{z}, xmm2
    vcvtps2uqq zmm1 {k1}{z}, ymm2
    vcvtps2uqq xmm1, qword ptr [rax]
    vcvtps2uqq ymm1, oword ptr [rax]
    vcvtps2uqq zmm1, ymmword ptr [rax]
    vcvtps2uqq xmm1, [rax]
    vcvtps2uqq ymm1, [rax]
    vcvtps2uqq zmm1, [rax]

    vcvtph2ps xmm1{k1}{z},xmm2 ; vex
    vcvtph2ps ymm1{k1}{z},xmm2
    vcvtph2ps zmm1{k1}{z},ymm2 ; evex
    vcvtph2ps xmm1,qword ptr [rax]
    vcvtph2ps ymm1,oword ptr [rax]
    vcvtph2ps zmm1,ymmword ptr [rax]
    vcvtph2ps xmm1,[rax]
    vcvtph2ps ymm1,[rax]
    vcvtph2ps zmm1,[rax]

    vcvtph2ps zmm30{k7},ymm29
    vcvtph2ps zmm30{k7}{z},ymm29
    vcvtph2ps zmm30{k7},ymm29,{sae}
    vcvtph2ps zmm30{k7},ymmword ptr [rcx]
    vcvtph2ps zmm30{k7},ymmword ptr [rax+r14*8+0x123]
    vcvtph2ps zmm30{k7},ymmword ptr [rdx+0xfe0]
    vcvtph2ps zmm30{k7},ymmword ptr [rdx+0x1000]
    vcvtph2ps zmm30{k7},ymmword ptr [rdx-0x1000]
    vcvtph2ps zmm30{k7},ymmword ptr [rdx-0x1020]

    vcvtps2ph xmm1{k1}{z},ymm2,3
    vcvtps2ph xmm1{k1}{z},xmm2,3
    vcvtps2ph ymm1{k1}{z},zmm2,3
    vcvtps2ph qword ptr [rax],xmm2,3
    vcvtps2ph oword ptr [rax],ymm2,3
    vcvtps2ph ymmword ptr [rax],zmm2,3
    vcvtps2ph [rax],ymm2,3
    vcvtps2ph [rax],xmm2,3
    vcvtps2ph [rax],zmm2,3
    vcvtps2ph ymm30{k7},zmm29,0xab
    vcvtps2ph ymm30{k7}{z},zmm29,0xab
    vcvtps2ph ymm30{k7},zmm29,{sae},0xab
    vcvtps2ph ymm30{k7},zmm29,0x7b
    vcvtps2ph ymm30{k7},zmm29,{sae},0x7b

    vcvtps2ph ymmword ptr [rcx],zmm30,0xab
    vcvtps2ph ymmword ptr [rcx]{k7},zmm30,0xab
    vcvtps2ph ymmword ptr [rcx],zmm30,0x7b
    vcvtps2ph ymmword ptr [rax+r14*8+0x123],zmm30,0x7b
    vcvtps2ph ymmword ptr [rdx+0xfe0],zmm30,0x7b
    vcvtps2ph ymmword ptr [rdx+0x1000],zmm30,0x7b
    vcvtps2ph ymmword ptr [rdx-0x1000],zmm30,0x7b
    vcvtps2ph ymmword ptr [rdx-0x1020],zmm30,0x7b

    vcvtqq2pd xmm1{k1}{z},xmm2
    vcvtqq2pd ymm1{k1}{z},ymm2
    vcvtqq2pd zmm1{k1}{z},zmm2
    vcvtqq2pd xmm1,oword ptr [rax]
    vcvtqq2pd ymm1,ymmword ptr [rax]
    vcvtqq2pd zmm1,zmmword ptr [rax]
    vcvtqq2pd xmm1,[rax]
    vcvtqq2pd ymm1,[rax]
    vcvtqq2pd zmm1,[rax]

    vcvtqq2ps xmm1{k1}{z},xmm2
    vcvtqq2ps xmm1{k1}{z},ymm2
    vcvtqq2ps ymm1{k1}{z},zmm2
    vcvtqq2ps xmm1,oword ptr [rax]
    vcvtqq2ps xmm1,ymmword ptr [rax]
    vcvtqq2ps ymm1,zmmword ptr [rax]

    vcvttpd2qq xmm1{k1}{z},xmm2
    vcvttpd2qq ymm1{k1}{z},ymm2
    vcvttpd2qq zmm1{k1}{z},zmm2
    vcvttpd2qq xmm1,[rax]
    vcvttpd2qq ymm1,[rax]
    vcvttpd2qq zmm1,[rax]

    vcvttps2qq xmm1{k1}{z},xmm2
    vcvttps2qq ymm1{k1}{z},xmm2
    vcvttps2qq zmm1{k1}{z},ymm2
    vcvttps2qq xmm1,qword ptr [rax]
    vcvttps2qq ymm1,oword ptr [rax]
    vcvttps2qq zmm1,ymmword ptr [rax]

    vcvttps2udq xmm1{k1}{z},xmm2
    vcvttps2udq ymm1{k1}{z},ymm2
    vcvttps2udq zmm1{k1}{z},zmm2
    vcvttps2udq xmm1,[rax]
    vcvttps2udq ymm1,[rax]
    vcvttps2udq zmm1,[rax]

    vcvttpd2udq xmm1{k1}{z},xmm2
    vcvttpd2udq xmm1{k1}{z},ymm2
    vcvttpd2udq ymm1{k1}{z},zmm2
    vcvttpd2udq xmm1,oword ptr [rax]
    vcvttpd2udq xmm1,ymmword ptr [rax]
    vcvttpd2udq ymm1,zmmword ptr [rax]

    vcvttpd2udq ymm30{k7},zmm29
    vcvttpd2udq ymm30{k7}{z},zmm29
    vcvttpd2udq ymm30{k7},zmm29,{sae}
    vcvttpd2udq ymm30{k7},zmmword ptr [rcx]
    vcvttpd2udq ymm30{k7},zmmword ptr [rax+r14*8+0x123]
    vcvttpd2udq ymm30{k7},qword ptr [rcx]{1to8}
    vcvttpd2udq ymm30{k7},zmmword ptr [rdx+0x1fc0]
    vcvttpd2udq ymm30{k7},zmmword ptr [rdx+0x2000]
    vcvttpd2udq ymm30{k7},zmmword ptr [rdx-0x2000]
    vcvttpd2udq ymm30{k7},zmmword ptr [rdx-0x2040]
    vcvttpd2udq ymm30{k7},qword ptr [rdx+0x3f8]{1to8}
    vcvttpd2udq ymm30{k7},qword ptr [rdx+0x400]{1to8}
    vcvttpd2udq ymm30{k7},qword ptr [rdx-0x400]{1to8}
    vcvttpd2udq ymm30{k7},qword ptr [rdx-0x408]{1to8}
    vcvttps2udq zmm30,zmm29
    vcvttps2udq zmm30{k7},zmm29
    vcvttps2udq zmm30{k7}{z},zmm29
    vcvttps2udq zmm30,zmm29,{sae}
    vcvttps2udq zmm30,zmmword ptr [rcx]
    vcvttps2udq zmm30,zmmword ptr [rax+r14*8+0x123]
    vcvttps2udq zmm30,dword ptr [rcx]{1to16}
    vcvttps2udq zmm30,zmmword ptr [rdx+0x1fc0]
    vcvttps2udq zmm30,zmmword ptr [rdx+0x2000]
    vcvttps2udq zmm30,zmmword ptr [rdx-0x2000]
    vcvttps2udq zmm30,zmmword ptr [rdx-0x2040]
    vcvttps2udq zmm30,dword ptr [rdx+0x1fc]{1to16}
    vcvttps2udq zmm30,dword ptr [rdx+0x200]{1to16}
    vcvttps2udq zmm30,dword ptr [rdx-0x200]{1to16}
    vcvttps2udq zmm30,dword ptr [rdx-0x204]{1to16}

    vcvttpd2uqq xmm1{k1}{z},xmm2
    vcvttpd2uqq ymm1{k1}{z},ymm2
    vcvttpd2uqq zmm1{k1}{z},zmm2
    vcvttpd2uqq xmm1,[rax]
    vcvttpd2uqq ymm1,[rax]
    vcvttpd2uqq zmm1,[rax]

    vcvttps2uqq xmm1{k1}{z},xmm2
    vcvttps2uqq ymm1{k1}{z},xmm2
    vcvttps2uqq zmm1{k1}{z},ymm2
    vcvttps2uqq xmm1,qword ptr [rax]
    vcvttps2uqq ymm1,oword ptr [rax]
    vcvttps2uqq zmm1,ymmword ptr [rax]

    vcvtudq2pd xmm1{k1}{z},xmm2
    vcvtudq2pd ymm1{k1}{z},xmm2
    vcvtudq2pd zmm1{k1}{z},ymm2
    ;vcvtudq2pd xmm1,dword ptr [rax]
    vcvtudq2pd ymm1,oword ptr [rax]
    vcvtudq2pd zmm1,ymmword ptr [rax]
    vcvtudq2pd zmm30{k7},ymm29
    vcvtudq2pd zmm30{k7}{z},ymm29
    vcvtudq2pd zmm30{k7},ymmword ptr [rcx]
    vcvtudq2pd zmm30{k7},ymmword ptr [rax+r14*8+0x123]
    vcvtudq2pd zmm30{k7},dword ptr [rcx]{1to8}
    vcvtudq2pd zmm30{k7},ymmword ptr [rdx+0xfe0]
    vcvtudq2pd zmm30{k7},ymmword ptr [rdx+0x1000]
    vcvtudq2pd zmm30{k7},ymmword ptr [rdx-0x1000]
    vcvtudq2pd zmm30{k7},ymmword ptr [rdx-0x1020]
    vcvtudq2pd zmm30{k7},dword ptr [rdx+0x1fc]{1to8}
    vcvtudq2pd zmm30{k7},dword ptr [rdx+0x200]{1to8}
    vcvtudq2pd zmm30{k7},dword ptr [rdx-0x200]{1to8}
    vcvtudq2pd zmm30{k7},dword ptr [rdx-0x204]{1to8}

    vcvtuqq2pd xmm1{k1}{z},xmm2
    vcvtuqq2pd ymm1{k1}{z},ymm2
    vcvtuqq2pd zmm1{k1}{z},zmm2
    vcvtuqq2pd xmm1,[rax]
    vcvtuqq2pd ymm1,[rax]
    vcvtuqq2pd zmm1,[rax]

    vcvtudq2ps xmm1{k1}{z},xmm2
    vcvtudq2ps ymm1{k1}{z},ymm2
    vcvtudq2ps zmm1{k1}{z},zmm2
    vcvtudq2ps xmm1,[rax]
    vcvtudq2ps ymm1,[rax]
    vcvtudq2ps zmm1,[rax]
    vcvtudq2ps zmm30,zmm29
    vcvtudq2ps zmm30{k7},zmm29
    vcvtudq2ps zmm30{k7}{z},zmm29
    vcvtudq2ps zmm30,zmm29,{rn-sae}
    vcvtudq2ps zmm30,zmm29,{ru-sae}
    vcvtudq2ps zmm30,zmm29,{rd-sae}
    vcvtudq2ps zmm30,zmm29,{rz-sae}
    vcvtudq2ps zmm30,zmmword ptr [rcx]
    vcvtudq2ps zmm30,zmmword ptr [rax+r14*8+0x123]
    vcvtudq2ps zmm30,dword ptr [rcx]{1to16}
    vcvtudq2ps zmm30,zmmword ptr [rdx+0x1fc0]
    vcvtudq2ps zmm30,zmmword ptr [rdx+0x2000]
    vcvtudq2ps zmm30,zmmword ptr [rdx-0x2000]
    vcvtudq2ps zmm30,zmmword ptr [rdx-0x2040]
    vcvtudq2ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vcvtudq2ps zmm30,dword ptr [rdx+0x200]{1to16}
    vcvtudq2ps zmm30,dword ptr [rdx-0x200]{1to16}
    vcvtudq2ps zmm30,dword ptr [rdx-0x204]{1to16}

    vcvtuqq2ps xmm1{k1}{z},xmm2
    vcvtuqq2ps xmm1{k1}{z},ymm2
    vcvtuqq2ps ymm1{k1}{z},zmm2
    vcvtuqq2ps xmm1,oword ptr [rax]
    vcvtuqq2ps xmm1,ymmword ptr [rax]
    vcvtuqq2ps ymm1,zmmword ptr [rax]

    vexpandpd xmm1{k1}{z},xmm2
    vexpandpd ymm1{k1}{z},ymm2
    vexpandpd zmm1{k1}{z},zmm2
    vexpandpd xmm1,[rax]
    vexpandpd ymm1,[rax]
    vexpandpd zmm1,[rax]
    vexpandpd zmm30,zmmword ptr [rcx]
    vexpandpd zmm30{k7},zmmword ptr [rcx]
    vexpandpd zmm30{k7}{z},zmmword ptr [rcx]
    vexpandpd zmm30,zmmword ptr [rax+r14*8+0x123]
    vexpandpd zmm30,zmmword ptr [rdx+0x3f8]
    vexpandpd zmm30,zmmword ptr [rdx+0x400]
    vexpandpd zmm30,zmmword ptr [rdx-0x400]
    vexpandpd zmm30,zmmword ptr [rdx-0x408]
    vexpandpd zmm30,zmm29
    vexpandpd zmm30{k7},zmm29
    vexpandpd zmm30{k7}{z},zmm29

    vexpandps xmm1{k1}{z},xmm2
    vexpandps ymm1{k1}{z},ymm2
    vexpandps zmm1{k1}{z},zmm2
    vexpandps xmm1,[rax]
    vexpandps ymm1,[rax]
    vexpandps zmm1,[rax]
    vexpandps zmm30,zmmword ptr [rcx]
    vexpandps zmm30{k7},zmmword ptr [rcx]
    vexpandps zmm30{k7}{z},zmmword ptr [rcx]
    vexpandps zmm30,zmmword ptr [rax+r14*8+0x123]
    vexpandps zmm30,zmmword ptr [rdx+0x1fc]
    vexpandps zmm30,zmmword ptr [rdx+0x200]
    vexpandps zmm30,zmmword ptr [rdx-0x200]
    vexpandps zmm30,zmmword ptr [rdx-0x204]
    vexpandps zmm30,zmm29
    vexpandps zmm30{k7},zmm29
    vexpandps zmm30{k7}{z},zmm29

    vextractf32x4 xmm1{k1}{z},ymm2,3
    vextractf32x4 xmm1{k1}{z},zmm2,3
    vextractf32x4 oword ptr [rax],ymm2,3
    vextractf32x4 oword ptr [rax],zmm2,3
    vextractf64x2 xmm1{k1}{z},ymm2,3
    vextractf64x2 xmm1{k1}{z},zmm2,3
    vextractf64x2 oword ptr [rax],ymm2,3
    vextractf64x2 oword ptr [rax],zmm2,3
    vextractf32x8 ymm1{k1}{z},zmm2,3
    vextractf32x8 ymmword ptr [rax],zmm2,3
    vextractf64x4 ymm1{k1}{z},zmm2,3
    vextractf64x4 ymmword ptr [rax],zmm2,3
    vextracti32x4 xmm1{k1}{z},ymm2,3
    vextracti32x4 xmm1{k1}{z},zmm2,3
    vextracti32x4 oword ptr [rax],ymm2,3
    vextracti32x4 oword ptr [rax],zmm2,3
    vextracti64x2 xmm1{k1}{z},ymm2,3
    vextracti64x2 xmm1{k1}{z},zmm2,3
    vextracti64x2 oword ptr [rax],ymm2,3
    vextracti64x2 oword ptr [rax],zmm2,3
    vextracti32x8 ymm1{k1}{z},zmm2,3
    vextracti32x8 ymmword ptr [rax],zmm2,3
    vextracti64x4 ymm1{k1}{z},zmm2,3
    vextracti64x4 ymmword ptr [rax],zmm2,3
    vextractf32x4 xmm30{k7},zmm29,0xab
    vextractf32x4 xmm30{k7}{z},zmm29,0xab
    vextractf32x4 xmm30{k7},zmm29,0x7b
    vextractf64x4 ymm30{k7},zmm29,0xab
    vextractf64x4 ymm30{k7}{z},zmm29,0xab
    vextractf64x4 ymm30{k7},zmm29,0x7b
    vextracti32x4 xmm30{k7},zmm29,0xab
    vextracti32x4 xmm30{k7}{z},zmm29,0xab
    vextracti32x4 xmm30{k7},zmm29,0x7b
    vextracti64x4 ymm30{k7},zmm29,0xab
    vextracti64x4 ymm30{k7}{z},zmm29,0xab
    vextracti64x4 ymm30{k7},zmm29,0x7b

    vextractf32x4 oword ptr [rcx],zmm30,0xab
    vextractf32x4 oword ptr [rcx]{k7},zmm30,0xab
    vextractf32x4 oword ptr [rcx],zmm30,0x7b
    vextractf32x4 oword ptr [rax+r14*8+0x123],zmm30,0x7b
    vextractf32x4 oword ptr [rdx+0x7f0],zmm30,0x7b
    vextractf32x4 oword ptr [rdx+0x800],zmm30,0x7b
    vextractf32x4 oword ptr [rdx-0x800],zmm30,0x7b
    vextractf32x4 oword ptr [rdx-0x810],zmm30,0x7b
    vextractf64x4 ymmword ptr [rcx],zmm30,0xab
    vextractf64x4 ymmword ptr [rcx]{k7},zmm30,0xab
    vextractf64x4 ymmword ptr [rcx],zmm30,0x7b
    vextractf64x4 ymmword ptr [rax+r14*8+0x123],zmm30,0x7b
    vextractf64x4 ymmword ptr [rdx+0xfe0],zmm30,0x7b
    vextractf64x4 ymmword ptr [rdx+0x1000],zmm30,0x7b
    vextractf64x4 ymmword ptr [rdx-0x1000],zmm30,0x7b
    vextractf64x4 ymmword ptr [rdx-0x1020],zmm30,0x7b
    vextracti32x4 oword ptr [rcx],zmm30,0xab
    vextracti32x4 oword ptr [rcx]{k7},zmm30,0xab
    vextracti32x4 oword ptr [rcx],zmm30,0x7b
    vextracti32x4 oword ptr [rax+r14*8+0x123],zmm30,0x7b
    vextracti32x4 oword ptr [rdx+0x7f0],zmm30,0x7b
    vextracti32x4 oword ptr [rdx+0x800],zmm30,0x7b
    vextracti32x4 oword ptr [rdx-0x800],zmm30,0x7b
    vextracti32x4 oword ptr [rdx-0x810],zmm30,0x7b
    vextracti64x4 ymmword ptr [rcx],zmm30,0xab
    vextracti64x4 ymmword ptr [rcx]{k7},zmm30,0xab
    vextracti64x4 ymmword ptr [rcx],zmm30,0x7b
    vextracti64x4 ymmword ptr [rax+r14*8+0x123],zmm30,0x7b
    vextracti64x4 ymmword ptr [rdx+0xfe0],zmm30,0x7b
    vextracti64x4 ymmword ptr [rdx+0x1000],zmm30,0x7b
    vextracti64x4 ymmword ptr [rdx-0x1000],zmm30,0x7b
    vextracti64x4 ymmword ptr [rdx-0x1020],zmm30,0x7b

    vfpclasspd k2{k1},xmm2,3
    vfpclasspd k2{k1},ymm2,3
    vfpclasspd k2{k1},zmm2,3
    vfpclasspd k2,oword ptr [rax],3
    vfpclasspd k2,ymmword ptr [rax],3
    vfpclasspd k2,zmmword ptr [rax],3

    vfpclassps k2{k1},xmm2,3
    vfpclassps k2{k1},ymm2,3
    vfpclassps k2{k1},zmm2,3
    vfpclassps k2,oword ptr [rax],3
    vfpclassps k2,ymmword ptr [rax],3
    vfpclassps k2,zmmword ptr [rax],3

    vgatherdpd xmm1,qword ptr [rbp+xmm7*2+0x0],xmm2
    vgatherqpd xmm1,qword ptr [rbp+xmm7*2+0x0],xmm2
    vgatherdpd ymm1,qword ptr [rbp+xmm7*2+0x0],ymm2
    vgatherqpd ymm1,qword ptr [rbp+ymm7*2+0x0],ymm2
    vgatherdpd ymm6,qword ptr [xmm4*1+0x8],ymm5
    vgatherdpd ymm6,qword ptr [xmm4*1-0x8],ymm5
    vgatherdpd ymm6,qword ptr [xmm4*1+0x0],ymm5
    vgatherdpd ymm6,qword ptr [xmm4*1+0x298],ymm5
    vgatherdpd ymm6,qword ptr [xmm4*8+0x8],ymm5
    vgatherdpd ymm6,qword ptr [xmm4*8-0x8],ymm5
    vgatherdpd ymm6,qword ptr [xmm4*8+0x0],ymm5
    vgatherdpd ymm6,qword ptr [xmm4*8+0x298],ymm5
    vgatherdpd zmm30{k1}, [r14+ymm31*8+0x7b]
    vgatherdpd zmm30{k1}, [r14+ymm31*8+0x7b]
    vgatherdpd zmm30{k1}, [r9+ymm31*1+0x100]
    vgatherdpd zmm30{k1}, [rcx+ymm31*4+0x400]
    vgatherqpd zmm30{k1}, [r14+zmm31*8+0x7b]
    vgatherqpd zmm30{k1}, [r14+zmm31*8+0x7b]
    vgatherqpd zmm30{k1}, [r9+zmm31*1+0x100]
    vgatherqpd zmm30{k1}, [rcx+zmm31*4+0x400]

    vgatherdps xmm1,dword ptr [rbp+xmm7*2+0x0],xmm2
    vgatherqps xmm1,dword ptr [rbp+xmm7*2+0x0],xmm2
    vgatherdps ymm1,dword ptr [rbp+ymm7*2+0x0],ymm2
    vgatherqps xmm1,dword ptr [rbp+ymm7*2+0x0],xmm2
    vgatherdps xmm6,dword ptr [xmm4*1+0x8],xmm5
    vgatherdps xmm6,dword ptr [xmm4*1-0x8],xmm5
    vgatherdps xmm6,dword ptr [xmm4*1+0x0],xmm5
    vgatherdps xmm6,dword ptr [xmm4*1+0x298],xmm5
    vgatherdps xmm6,dword ptr [xmm4*8+0x8],xmm5
    vgatherdps xmm6,dword ptr [xmm4*8-0x8],xmm5
    vgatherdps xmm6,dword ptr [xmm4*8+0x0],xmm5
    vgatherdps xmm6,dword ptr [xmm4*8+0x298],xmm5
    vgatherdps zmm30{k1}, [r14+zmm31*8+0x7b]
    vgatherdps zmm30{k1}, [r14+zmm31*8+0x7b]
    vgatherdps zmm30{k1}, [r9+zmm31*1+0x100]
    vgatherdps zmm30{k1}, [rcx+zmm31*4+0x400]

    vpgatherdd xmm1,dword ptr [rbp+xmm7*2+0x0],xmm2
    vpgatherqd xmm1,dword ptr [rbp+xmm7*2+0x0],xmm2
    vpgatherdd ymm1,dword ptr [rbp+ymm7*2+0x0],ymm2
    vpgatherqd xmm1,dword ptr [rbp+ymm7*2+0x0],xmm2
    vpgatherdd xmm6,dword ptr [xmm4*1+0x8],xmm5
    vpgatherdd xmm6,dword ptr [xmm4*1-0x8],xmm5
    vpgatherdd xmm6,dword ptr [xmm4*1+0x0],xmm5
    vpgatherdd xmm6,dword ptr [xmm4*1+0x298],xmm5
    vpgatherdd xmm6,dword ptr [xmm4*8+0x8],xmm5
    vpgatherdd xmm6,dword ptr [xmm4*8-0x8],xmm5
    vpgatherdd xmm6,dword ptr [xmm4*8+0x0],xmm5
    vpgatherdd xmm6,dword ptr [xmm4*8+0x298],xmm5
    vpgatherdq xmm1,qword ptr [rbp+xmm7*2+0x0],xmm2
    vpgatherqq xmm1,qword ptr [rbp+xmm7*2+0x0],xmm2
    vpgatherdq ymm1,qword ptr [rbp+xmm7*2+0x0],ymm2
    vpgatherqq ymm1,qword ptr [rbp+ymm7*2+0x0],ymm2
    vpgatherdq ymm6,qword ptr [xmm4*1+0x8],ymm5
    vpgatherdq ymm6,qword ptr [xmm4*1-0x8],ymm5
    vpgatherdq ymm6,qword ptr [xmm4*1+0x0],ymm5
    vpgatherdq ymm6,qword ptr [xmm4*1+0x298],ymm5
    vpgatherdq ymm6,qword ptr [xmm4*8+0x8],ymm5
    vpgatherdq ymm6,qword ptr [xmm4*8-0x8],ymm5
    vpgatherdq ymm6,qword ptr [xmm4*8+0x0],ymm5
    vpgatherdq ymm6,qword ptr [xmm4*8+0x298],ymm5

    vpgatherdd zmm30{k1}, [r14+zmm31*8+0x7b]
    vpgatherdd zmm30{k1}, [r14+zmm31*8+0x7b]
    vpgatherdd zmm30{k1}, [r9+zmm31*1+0x100]
    vpgatherdd zmm30{k1}, [rcx+zmm31*4+0x400]
    vpgatherdq zmm30{k1}, [r14+ymm31*8+0x7b]
    vpgatherdq zmm30{k1}, [r14+ymm31*8+0x7b]
    vpgatherdq zmm30{k1}, [r9+ymm31*1+0x100]
    vpgatherdq zmm30{k1}, [rcx+ymm31*4+0x400]
    vpgatherqq zmm30{k1}, [r14+zmm31*8+0x7b]
    vpgatherqq zmm30{k1}, [r14+zmm31*8+0x7b]
    vpgatherqq zmm30{k1}, [r9+zmm31*1+0x100]
    vpgatherqq zmm30{k1}, [rcx+zmm31*4+0x400]

    vgatherpf0dpd  [r14+ymm31*8+0x7b]{k1}
    vgatherpf0dpd  [r14+ymm31*8+0x7b]{k1}
    vgatherpf0dpd  [r9+ymm31*1+0x100]{k1}
    vgatherpf0dpd  [rcx+ymm31*4+0x400]{k1}
    vgatherpf0dps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf0dps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf0dps  [r9+zmm31*1+0x100]{k1}
    vgatherpf0dps  [rcx+zmm31*4+0x400]{k1}
    vgatherpf0qpd  [r14+zmm31*8+0x7b]{k1}
    vgatherpf0qpd  [r14+zmm31*8+0x7b]{k1}
    vgatherpf0qpd  [r9+zmm31*1+0x100]{k1}
    vgatherpf0qpd  [rcx+zmm31*4+0x400]{k1}
    vgatherpf0qps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf0qps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf0qps  [r9+zmm31*1+0x100]{k1}
    vgatherpf0qps  [rcx+zmm31*4+0x400]{k1}
    vgatherpf1dpd  [r14+ymm31*8+0x7b]{k1}
    vgatherpf1dpd  [r14+ymm31*8+0x7b]{k1}
    vgatherpf1dpd  [r9+ymm31*1+0x100]{k1}
    vgatherpf1dpd  [rcx+ymm31*4+0x400]{k1}
    vgatherpf1dps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf1dps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf1dps  [r9+zmm31*1+0x100]{k1}
    vgatherpf1dps  [rcx+zmm31*4+0x400]{k1}
    vgatherpf1qpd  [r14+zmm31*8+0x7b]{k1}
    vgatherpf1qpd  [r14+zmm31*8+0x7b]{k1}
    vgatherpf1qpd  [r9+zmm31*1+0x100]{k1}
    vgatherpf1qpd  [rcx+zmm31*4+0x400]{k1}
    vgatherpf1qps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf1qps  [r14+zmm31*8+0x7b]{k1}
    vgatherpf1qps  [r9+zmm31*1+0x100]{k1}
    vgatherpf1qps  [rcx+zmm31*4+0x400]{k1}

    vscatterpf0dpd  [r14+ymm31*8+0x7b]{k1}
    vscatterpf0dpd  [r14+ymm31*8+0x7b]{k1}
    vscatterpf0dpd  [r9+ymm31*1+0x100]{k1}
    vscatterpf0dpd  [rcx+ymm31*4+0x400]{k1}
    vscatterpf0dps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf0dps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf0dps  [r9+zmm31*1+0x100]{k1}
    vscatterpf0dps  [rcx+zmm31*4+0x400]{k1}
    vscatterpf0qpd  [r14+zmm31*8+0x7b]{k1}
    vscatterpf0qpd  [r14+zmm31*8+0x7b]{k1}
    vscatterpf0qpd  [r9+zmm31*1+0x100]{k1}
    vscatterpf0qpd  [rcx+zmm31*4+0x400]{k1}
    vscatterpf0qps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf0qps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf0qps  [r9+zmm31*1+0x100]{k1}
    vscatterpf0qps  [rcx+zmm31*4+0x400]{k1}

    vscatterpf1dpd  [r14+ymm31*8+0x7b]{k1}
    vscatterpf1dpd  [r14+ymm31*8+0x7b]{k1}
    vscatterpf1dpd  [r9+ymm31*1+0x100]{k1}
    vscatterpf1dpd  [rcx+ymm31*4+0x400]{k1}
    vscatterpf1dps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf1dps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf1dps  [r9+zmm31*1+0x100]{k1}
    vscatterpf1dps  [rcx+zmm31*4+0x400]{k1}
    vscatterpf1qpd  [r14+zmm31*8+0x7b]{k1}
    vscatterpf1qpd  [r14+zmm31*8+0x7b]{k1}
    vscatterpf1qpd  [r9+zmm31*1+0x100]{k1}
    vscatterpf1qpd  [rcx+zmm31*4+0x400]{k1}
    vscatterpf1qps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf1qps  [r14+zmm31*8+0x7b]{k1}
    vscatterpf1qps  [r9+zmm31*1+0x100]{k1}
    vscatterpf1qps  [rcx+zmm31*4+0x400]{k1}

    vscatterdpd	 [r14+ymm31*8+0x7b]{k1},zmm30
    vscatterdpd	 [r14+ymm31*8+0x7b]{k1},zmm30
    vscatterdpd	 [r9+ymm31*1+0x100]{k1},zmm30
    vscatterdpd	 [rcx+ymm31*4+0x400]{k1},zmm30
    vscatterdps	 [r14+zmm31*8+0x7b]{k1},zmm30
    vscatterdps	 [r14+zmm31*8+0x7b]{k1},zmm30
    vscatterdps	 [r9+zmm31*1+0x100]{k1},zmm30
    vscatterdps	 [rcx+zmm31*4+0x400]{k1},zmm30
    vscatterqpd	 [r14+zmm31*8+0x7b]{k1},zmm30
    vscatterqpd	 [r14+zmm31*8+0x7b]{k1},zmm30
    vscatterqpd	 [r9+zmm31*1+0x100]{k1},zmm30
    vscatterqpd	 [rcx+zmm31*4+0x400]{k1},zmm30

    vpscatterdd	 [r14+zmm31*8+0x7b]{k1},zmm30
    vpscatterdd	 [r14+zmm31*8+0x7b]{k1},zmm30
    vpscatterdd	 [r9+zmm31*1+0x100]{k1},zmm30
    vpscatterdd	 [rcx+zmm31*4+0x400]{k1},zmm30
    vpscatterdq	 [r14+ymm31*8+0x7b]{k1},zmm30
    vpscatterdq	 [r14+ymm31*8+0x7b]{k1},zmm30
    vpscatterdq	 [r9+ymm31*1+0x100]{k1},zmm30
    vpscatterdq	 [rcx+ymm31*4+0x400]{k1},zmm30
    vpscatterqq	 [r14+zmm31*8+0x7b]{k1},zmm30
    vpscatterqq	 [r14+zmm31*8+0x7b]{k1},zmm30
    vpscatterqq	 [r9+zmm31*1+0x100]{k1},zmm30
    vpscatterqq	 [rcx+zmm31*4+0x400]{k1},zmm30

    vgetexppd zmm30,zmm29
    vgetexppd zmm30{k7},zmm29
    vgetexppd zmm30{k7}{z},zmm29
    vgetexppd zmm30,zmmword ptr [rcx]
    vgetexppd zmm30,zmmword ptr [rax+r14*8+0x123]
    vgetexppd zmm30,qword ptr [rcx]{1to8}
    vgetexppd zmm30,zmmword ptr [rdx+0x1fc0]
    vgetexppd zmm30,zmmword ptr [rdx+0x2000]
    vgetexppd zmm30,zmmword ptr [rdx-0x2000]
    vgetexppd zmm30,zmmword ptr [rdx-0x2040]
    vgetexppd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vgetexppd zmm30,qword ptr [rdx+0x400]{1to8}
    vgetexppd zmm30,qword ptr [rdx-0x400]{1to8}
    vgetexppd zmm30,qword ptr [rdx-0x408]{1to8}

    vgetexpps zmm30,zmm29
    vgetexpps zmm30{k7},zmm29
    vgetexpps zmm30{k7}{z},zmm29
    vgetexpps zmm30,zmmword ptr [rcx]
    vgetexpps zmm30,zmmword ptr [rax+r14*8+0x123]
    vgetexpps zmm30,dword ptr [rcx]{1to16}
    vgetexpps zmm30,zmmword ptr [rdx+0x1fc0]
    vgetexpps zmm30,zmmword ptr [rdx+0x2000]
    vgetexpps zmm30,zmmword ptr [rdx-0x2000]
    vgetexpps zmm30,zmmword ptr [rdx-0x2040]
    vgetexpps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vgetexpps zmm30,dword ptr [rdx+0x200]{1to16}
    vgetexpps zmm30,dword ptr [rdx-0x200]{1to16}
    vgetexpps zmm30,dword ptr [rdx-0x204]{1to16}

    vgetexpsd xmm30{k7},xmm29,xmm28
    vgetexpsd xmm30{k7}{z},xmm29,xmm28
    vgetexpsd xmm30{k7},xmm29,qword ptr [rcx]
    vgetexpsd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vgetexpsd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vgetexpsd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vgetexpsd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vgetexpsd xmm30{k7},xmm29,qword ptr [rdx-0x408]

    vgetexpss xmm30{k7},xmm29,xmm28
    vgetexpss xmm30{k7}{z},xmm29,xmm28
    vgetexpss xmm30{k7},xmm29,dword ptr [rcx]
    vgetexpss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vgetexpss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vgetexpss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vgetexpss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vgetexpss xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vpcompressd zmmword ptr [rcx],zmm30
    vpcompressd zmmword ptr [rcx]{k7},zmm30
    vpcompressd zmmword ptr [rax+r14*8+0x123],zmm30
    vpcompressd zmmword ptr [rdx+0x1fc],zmm30
    vpcompressd zmmword ptr [rdx+0x200],zmm30
    vpcompressd zmmword ptr [rdx-0x200],zmm30
    vpcompressd zmmword ptr [rdx-0x204],zmm30
    vpcompressd zmm30,zmm29
    vpcompressd zmm30{k7},zmm29
    vpcompressd zmm30{k7}{z},zmm29

    vpcompressq zmmword ptr [rcx],zmm30
    vpcompressq zmmword ptr [rcx]{k7},zmm30
    vpcompressq zmmword ptr [rax+r14*8+0x123],zmm30
    vpcompressq zmmword ptr [rdx+0x3f8],zmm30
    vpcompressq zmmword ptr [rdx+0x400],zmm30
    vpcompressq zmmword ptr [rdx-0x400],zmm30
    vpcompressq zmmword ptr [rdx-0x408],zmm30
    vpcompressq zmm30,zmm29
    vpcompressq zmm30{k7},zmm29
    vpcompressq zmm30{k7}{z},zmm29

    vbroadcastf32x2  ymm1 {k1}{z}, xmm2
    vbroadcastf32x2  zmm1 {k1}{z}, xmm2
    vbroadcastf32x4  ymm1 {k1}{z}, oword ptr [rax]
    vbroadcastf32x4  zmm1 {k1}{z}, oword ptr [rax]
    vbroadcastf32x8  zmm1 {k1}{z}, ymmword ptr [rax]
    vbroadcastf64x2  ymm1 {k1}{z}, oword ptr [rax]
    vbroadcastf64x2  zmm1 {k1}{z}, oword ptr [rax]
    vbroadcastf64x4  zmm1 {k1}{z}, ymmword ptr [rax]
    vbroadcasti32x2  xmm1 {k1}{z}, xmm2
    vbroadcasti32x2  ymm1 {k1}{z}, xmm2
    vbroadcasti32x2  zmm1 {k1}{z}, xmm2
    vbroadcasti32x4  ymm1 {k1}{z}, oword ptr [rax]
    vbroadcasti32x4  zmm1 {k1}{z}, oword ptr [rax]
    vbroadcasti32x8  zmm1 {k1}{z}, ymmword ptr [rax]
    vbroadcasti64x2  ymm1 {k1}{z}, oword ptr [rax]
    vbroadcasti64x2  zmm1 {k1}{z}, oword ptr [rax]
    vbroadcasti64x4  zmm1 {k1}{z}, ymmword ptr [rax]

    vbroadcastf32x2  ymm1 {k1}{z}, qword ptr [rax]
    vbroadcastf32x2  zmm1 {k1}{z}, qword ptr [rax]
    vbroadcasti32x2  xmm1 {k1}{z}, qword ptr [rax]
    vbroadcasti32x2  ymm1 {k1}{z}, qword ptr [rax]
    vbroadcasti32x2  zmm1 {k1}{z}, qword ptr [rax]

    vbroadcastf32x2  ymm1 {k1}{z}, [rax]
    vbroadcastf32x2  zmm1 {k1}{z}, [rax]
    vbroadcastf32x4  ymm1 {k1}{z}, [rax]
    vbroadcastf32x4  zmm1 {k1}{z}, [rax]
    vbroadcastf32x8  zmm1 {k1}{z}, [rax]
    vbroadcastf64x2  ymm1 {k1}{z}, [rax]
    vbroadcastf64x2  zmm1 {k1}{z}, [rax]
    vbroadcastf64x4  zmm1 {k1}{z}, [rax]
    vbroadcasti32x2  xmm1 {k1}{z}, [rax]
    vbroadcasti32x2  ymm1 {k1}{z}, [rax]
    vbroadcasti32x2  zmm1 {k1}{z}, [rax]
    vbroadcasti32x4  ymm1 {k1}{z}, [rax]
    vbroadcasti32x4  zmm1 {k1}{z}, [rax]
    vbroadcasti32x8  zmm1 {k1}{z}, [rax]
    vbroadcasti64x2  ymm1 {k1}{z}, [rax]
    vbroadcasti64x2  zmm1 {k1}{z}, [rax]
    vbroadcasti64x4  zmm1 {k1}{z}, [rax]

    vbroadcastf32x4 zmm30,oword ptr [rcx]
    vbroadcastf32x4 zmm30{k7},oword ptr [rcx]
    vbroadcastf32x4 zmm30{k7}{z},oword ptr [rcx]
    vbroadcastf32x4 zmm30,oword ptr [rax+r14*8+0x123]
    vbroadcastf32x4 zmm30,oword ptr [rdx+0x7f0]
    vbroadcastf32x4 zmm30,oword ptr [rdx+0x800]
    vbroadcastf32x4 zmm30,oword ptr [rdx-0x800]
    vbroadcastf32x4 zmm30,oword ptr [rdx-0x810]
    vbroadcastf64x4 zmm30,ymmword ptr [rcx]
    vbroadcastf64x4 zmm30{k7},ymmword ptr [rcx]
    vbroadcastf64x4 zmm30{k7}{z},ymmword ptr [rcx]
    vbroadcastf64x4 zmm30,ymmword ptr [rax+r14*8+0x123]
    vbroadcastf64x4 zmm30,ymmword ptr [rdx+0xfe0]
    vbroadcastf64x4 zmm30,ymmword ptr [rdx+0x1000]
    vbroadcastf64x4 zmm30,ymmword ptr [rdx-0x1000]
    vbroadcastf64x4 zmm30,ymmword ptr [rdx-0x1020]
    vbroadcasti32x4 zmm30,oword ptr [rcx]
    vbroadcasti32x4 zmm30{k7},oword ptr [rcx]
    vbroadcasti32x4 zmm30{k7}{z},oword ptr [rcx]
    vbroadcasti32x4 zmm30,oword ptr [rax+r14*8+0x123]
    vbroadcasti32x4 zmm30,oword ptr [rdx+0x7f0]
    vbroadcasti32x4 zmm30,oword ptr [rdx+0x800]
    vbroadcasti32x4 zmm30,oword ptr [rdx-0x800]
    vbroadcasti32x4 zmm30,oword ptr [rdx-0x810]
    vbroadcasti64x4 zmm30,ymmword ptr [rcx]
    vbroadcasti64x4 zmm30{k7},ymmword ptr [rcx]
    vbroadcasti64x4 zmm30{k7}{z},ymmword ptr [rcx]
    vbroadcasti64x4 zmm30,ymmword ptr [rax+r14*8+0x123]
    vbroadcasti64x4 zmm30,ymmword ptr [rdx+0xfe0]
    vbroadcasti64x4 zmm30,ymmword ptr [rdx+0x1000]
    vbroadcasti64x4 zmm30,ymmword ptr [rdx-0x1000]
    vbroadcasti64x4 zmm30,ymmword ptr [rdx-0x1020]

    vpexpandd zmm30,zmmword ptr [rcx]
    vpexpandd zmm30{k7},zmmword ptr [rcx]
    vpexpandd zmm30{k7}{z},zmmword ptr [rcx]
    vpexpandd zmm30,zmmword ptr [rax+r14*8+0x123]
    vpexpandd zmm30,zmmword ptr [rdx+0x1fc]
    vpexpandd zmm30,zmmword ptr [rdx+0x200]
    vpexpandd zmm30,zmmword ptr [rdx-0x200]
    vpexpandd zmm30,zmmword ptr [rdx-0x204]
    vpexpandd zmm30,zmm29
    vpexpandd zmm30{k7},zmm29
    vpexpandd zmm30{k7}{z},zmm29
    vpexpandq zmm30,zmmword ptr [rcx]
    vpexpandq zmm30{k7},zmmword ptr [rcx]
    vpexpandq zmm30{k7}{z},zmmword ptr [rcx]
    vpexpandq zmm30,zmmword ptr [rax+r14*8+0x123]
    vpexpandq zmm30,zmmword ptr [rdx+0x3f8]
    vpexpandq zmm30,zmmword ptr [rdx+0x400]
    vpexpandq zmm30,zmmword ptr [rdx-0x400]
    vpexpandq zmm30,zmmword ptr [rdx-0x408]
    vpexpandq zmm30,zmm29
    vpexpandq zmm30{k7},zmm29
    vpexpandq zmm30{k7}{z},zmm29

    vrcp14pd zmm30,zmm29
    vrcp14pd zmm30{k7},zmm29
    vrcp14pd zmm30{k7}{z},zmm29
    vrcp14pd zmm30,zmmword ptr [rcx]
    vrcp14pd zmm30,zmmword ptr [rax+r14*8+0x123]
    vrcp14pd zmm30,qword ptr [rcx]{1to8}
    vrcp14pd zmm30,zmmword ptr [rdx+0x1fc0]
    vrcp14pd zmm30,zmmword ptr [rdx+0x2000]
    vrcp14pd zmm30,zmmword ptr [rdx-0x2000]
    vrcp14pd zmm30,zmmword ptr [rdx-0x2040]
    vrcp14pd zmm30,qword ptr [rdx+0x3f8]{1to8}
    vrcp14pd zmm30,qword ptr [rdx+0x400]{1to8}
    vrcp14pd zmm30,qword ptr [rdx-0x400]{1to8}
    vrcp14pd zmm30,qword ptr [rdx-0x408]{1to8}

    vrcp14ps zmm30,zmm29
    vrcp14ps zmm30{k7},zmm29
    vrcp14ps zmm30{k7}{z},zmm29
    vrcp14ps zmm30,zmmword ptr [rcx]
    vrcp14ps zmm30,zmmword ptr [rax+r14*8+0x123]
    vrcp14ps zmm30,dword ptr [rcx]{1to16}
    vrcp14ps zmm30,zmmword ptr [rdx+0x1fc0]
    vrcp14ps zmm30,zmmword ptr [rdx+0x2000]
    vrcp14ps zmm30,zmmword ptr [rdx-0x2000]
    vrcp14ps zmm30,zmmword ptr [rdx-0x2040]
    vrcp14ps zmm30,dword ptr [rdx+0x1fc]{1to16}
    vrcp14ps zmm30,dword ptr [rdx+0x200]{1to16}
    vrcp14ps zmm30,dword ptr [rdx-0x200]{1to16}
    vrcp14ps zmm30,dword ptr [rdx-0x204]{1to16}

    vrcp14sd xmm30{k7},xmm29,xmm28
    vrcp14sd xmm30{k7}{z},xmm29,xmm28
    vrcp14sd xmm30{k7},xmm29,qword ptr [rcx]
    vrcp14sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vrcp14sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vrcp14sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vrcp14sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vrcp14sd xmm30{k7},xmm29,qword ptr [rdx-0x408]

    vrcp14ss xmm30{k7},xmm29,xmm28
    vrcp14ss xmm30{k7}{z},xmm29,xmm28
    vrcp14ss xmm30{k7},xmm29,dword ptr [rcx]
    vrcp14ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vrcp14ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vrcp14ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vrcp14ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vrcp14ss xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vreducepd xmm1{k1}{z},xmm2,3
    vreducepd ymm1{k1}{z},ymm2,3
    vreducepd zmm1{k1}{z},zmm2,3
    vreduceps xmm1{k1}{z},xmm2,3
    vreduceps ymm1{k1}{z},ymm2,3
    vreduceps zmm1{k1}{z},zmm2,3
    vreducesd xmm1{k1}{z},xmm2,xmm3,3
    vreducess xmm1{k1}{z},xmm2,xmm3,3
    vreducepd xmm1,[rax],3
    vreducepd ymm1,[rax],3
    vreducepd zmm1,[rax],3
    vreduceps xmm1,[rax],3
    vreduceps ymm1,[rax],3
    vreduceps zmm1,[rax],3
    vreducesd xmm1,xmm2,[rax],3
    vreducess xmm1,xmm2,[rax],3
    ;vreducepd xmm1,qword ptr [rax],3
    ;vreducepd ymm1,qword ptr [rax],3
    ;vreducepd zmm1,qword ptr [rax],3
    ;vreduceps xmm1,dword ptr [rax],3
    ;vreduceps ymm1,dword ptr [rax],3
    ;vreduceps zmm1,dword ptr [rax],3
    vreducesd xmm1,xmm2,qword ptr [rax],3
    vreducess xmm1,xmm2,dword ptr [rax],3

    vrndscalepd xmm1{k1}{z},xmm2,7
    vrndscalepd ymm1{k1}{z},ymm2,7
    vrndscalepd zmm1{k1}{z},zmm2,7
    vrndscaleps xmm1{k1}{z},xmm2,7
    vrndscaleps ymm1{k1}{z},ymm2,7
    vrndscaleps zmm1{k1}{z},zmm2,7
    vrndscalesd xmm1{k1}{z},xmm2,xmm3,7
    vrndscaless xmm1{k1}{z},xmm2,xmm3,3
    vrndscalepd xmm1,[rax],7
    vrndscalepd ymm1,[rax],7
    vrndscalepd zmm1,[rax],7
    vrndscaleps xmm1,[rax],7
    vrndscaleps ymm1,[rax],7
    vrndscaleps zmm1,[rax],7
    vrndscalesd xmm1,xmm2,[rax],7
    vrndscaless xmm1,xmm2,[rax],3
    ;vrndscalepd xmm1,qword ptr [rax],7
    ;vrndscalepd ymm1,qword ptr [rax],7
    ;vrndscalepd zmm1,qword ptr [rax],7
    ;vrndscaleps xmm1,dword ptr [rax],7
    ;vrndscaleps ymm1,dword ptr [rax],7
    ;vrndscaleps zmm1,dword ptr [rax],7
    vrndscalesd xmm1,xmm2,qword ptr [rax],7
    vrndscaless xmm1,xmm2,dword ptr [rax],3

    vrndscalepd zmm30,zmm29,0xab
    vrndscalepd zmm30{k7},zmm29,0xab
    vrndscalepd zmm30{k7}{z},zmm29,0xab
    vrndscalepd zmm30,zmm29,{sae},0xab
    vrndscalepd zmm30,zmm29,0x7b
    vrndscalepd zmm30,zmm29,{sae},0x7b
    vrndscalepd zmm30,zmmword ptr [rcx],0x7b
    vrndscalepd zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vrndscalepd zmm30,qword ptr [rcx]{1to8},0x7b
    vrndscalepd zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vrndscalepd zmm30,zmmword ptr [rdx+0x2000],0x7b
    vrndscalepd zmm30,zmmword ptr [rdx-0x2000],0x7b
    vrndscalepd zmm30,zmmword ptr [rdx-0x2040],0x7b
    vrndscalepd zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vrndscalepd zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vrndscalepd zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vrndscalepd zmm30,qword ptr [rdx-0x408]{1to8},0x7b
    vrndscaleps zmm30,zmm29,0xab
    vrndscaleps zmm30{k7},zmm29,0xab
    vrndscaleps zmm30{k7}{z},zmm29,0xab
    vrndscaleps zmm30,zmm29,{sae},0xab
    vrndscaleps zmm30,zmm29,0x7b
    vrndscaleps zmm30,zmm29,{sae},0x7b
    vrndscaleps zmm30,zmmword ptr [rcx],0x7b
    vrndscaleps zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vrndscaleps zmm30,dword ptr [rcx]{1to16},0x7b
    vrndscaleps zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vrndscaleps zmm30,zmmword ptr [rdx+0x2000],0x7b
    vrndscaleps zmm30,zmmword ptr [rdx-0x2000],0x7b
    vrndscaleps zmm30,zmmword ptr [rdx-0x2040],0x7b
    vrndscaleps zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vrndscaleps zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vrndscaleps zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vrndscaleps zmm30,dword ptr [rdx-0x204]{1to16},0x7b
    vrndscalesd xmm30{k7},xmm29,xmm28,0xab
    vrndscalesd xmm30{k7}{z},xmm29,xmm28,0xab
    vrndscalesd xmm30{k7},xmm29,xmm28,{sae},0xab
    vrndscalesd xmm30{k7},xmm29,xmm28,0x7b
    vrndscalesd xmm30{k7},xmm29,xmm28,{sae},0x7b
    vrndscalesd xmm30{k7},xmm29,qword ptr [rcx],0x7b
    vrndscalesd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123],0x7b
    vrndscalesd xmm30{k7},xmm29,qword ptr [rdx+0x3f8],0x7b
    vrndscalesd xmm30{k7},xmm29,qword ptr [rdx+0x400],0x7b
    vrndscalesd xmm30{k7},xmm29,qword ptr [rdx-0x400],0x7b
    vrndscalesd xmm30{k7},xmm29,qword ptr [rdx-0x408],0x7b
    vrndscaless xmm30{k7},xmm29,xmm28,0xab
    vrndscaless xmm30{k7}{z},xmm29,xmm28,0xab
    vrndscaless xmm30{k7},xmm29,xmm28,{sae},0xab
    vrndscaless xmm30{k7},xmm29,xmm28,0x7b
    vrndscaless xmm30{k7},xmm29,xmm28,{sae},0x7b
    vrndscaless xmm30{k7},xmm29,dword ptr [rcx],0x7b
    vrndscaless xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123],0x7b
    vrndscaless xmm30{k7},xmm29,dword ptr [rdx+0x1fc],0x7b
    vrndscaless xmm30{k7},xmm29,dword ptr [rdx+0x200],0x7b
    vrndscaless xmm30{k7},xmm29,dword ptr [rdx-0x200],0x7b
    vrndscaless xmm30{k7},xmm29,dword ptr [rdx-0x204],0x7b

    vpmovb2m k1,xmm1
    vpmovb2m k1,ymm1
    vpmovb2m k1,zmm1
    vpmovd2m k1,xmm1
    vpmovd2m k1,ymm1
    vpmovd2m k1,zmm1
    vpmovw2m k1,xmm1
    vpmovw2m k1,ymm1
    vpmovw2m k1,zmm1
    vpmovq2m k1,xmm1
    vpmovq2m k1,ymm1
    vpmovq2m k1,zmm1

    vpmovm2b xmm1,k1
    vpmovm2b ymm1,k1
    vpmovm2b zmm1,k1
    vpmovm2d xmm1,k1
    vpmovm2d ymm1,k1
    vpmovm2d zmm1,k1
    vpmovm2q xmm1,k1
    vpmovm2q ymm1,k1
    vpmovm2q zmm1,k1
    vpmovm2w xmm1,k1
    vpmovm2w ymm1,k1
    vpmovm2w zmm1,k1

    vpmovdb xmm1{k1}{z},zmm2
    vpmovdb xmm1{k1}{z},xmm2
    vpmovdb xmm1{k1}{z},ymm2
    vpmovdw xmm1{k1}{z},ymm2
    vpmovdw xmm1{k1}{z},xmm2
    vpmovdw ymm1{k1}{z},zmm2
    vpmovqb xmm1{k1}{z},xmm2
    vpmovqb xmm1{k1}{z},ymm2
    vpmovqb xmm1{k1}{z},zmm2
    vpmovqd xmm1{k1}{z},xmm2
    vpmovqd xmm1{k1}{z},ymm2
    vpmovqd ymm1{k1}{z},zmm2
    vpmovqw xmm1{k1}{z},zmm2
    vpmovqw xmm1{k1}{z},xmm2
    vpmovqw xmm1{k1}{z},ymm2
    vpmovdb [rax],zmm2
    vpmovdb [rax],xmm2
    vpmovdb [rax],ymm2
    vpmovdw [rax],ymm2
    vpmovdw [rax],xmm2
    vpmovdw [rax],zmm2
    vpmovqb [rax],xmm2
    vpmovqb [rax],ymm2
    vpmovqb [rax],zmm2
    vpmovqd [rax],xmm2
    vpmovqd [rax],ymm2
    vpmovqd [rax],zmm2
    vpmovqw [rax],zmm2
    vpmovqw [rax],xmm2
    vpmovqw [rax],ymm2
    vpmovdb oword ptr [rax],zmm2
    vpmovdb dword ptr [rax],xmm2
    vpmovdb qword ptr [rax],ymm2
    vpmovdw oword ptr [rax],ymm2
    vpmovdw qword ptr [rax],xmm2
    vpmovdw ymmword ptr [rax],zmm2
    vpmovqb word ptr [rax],xmm2
    vpmovqb dword ptr [rax],ymm2
    vpmovqb qword ptr [rax],zmm2
    vpmovqd oword ptr [rax],ymm2
    vpmovqd ymmword ptr [rax],zmm2
    vpmovqw oword ptr [rax],zmm2
    vpmovqw dword ptr [rax],xmm2
    vpmovqw qword ptr [rax],ymm2

    vpmovqb xmm30{k7},zmm29
    vpmovqb xmm30{k7}{z},zmm29
    vpmovsqb xmm30{k7},zmm29
    vpmovsqb xmm30{k7}{z},zmm29
    vpmovusqb xmm30{k7},zmm29
    vpmovusqb xmm30{k7}{z},zmm29
    vpmovqw xmm30{k7},zmm29
    vpmovqw xmm30{k7}{z},zmm29
    vpmovsqw xmm30{k7},zmm29
    vpmovsqw xmm30{k7}{z},zmm29
    vpmovusqw xmm30{k7},zmm29
    vpmovusqw xmm30{k7}{z},zmm29
    vpmovqd ymm30{k7},zmm29
    vpmovqd ymm30{k7}{z},zmm29
    vpmovsqd ymm30{k7},zmm29
    vpmovsqd ymm30{k7}{z},zmm29
    vpmovusqd ymm30{k7},zmm29
    vpmovusqd ymm30{k7}{z},zmm29
    vpmovdb xmm30{k7},zmm29
    vpmovdb xmm30{k7}{z},zmm29
    vpmovsdb xmm30{k7},zmm29
    vpmovsdb xmm30{k7}{z},zmm29
    vpmovusdb xmm30{k7},zmm29
    vpmovusdb xmm30{k7}{z},zmm29
    vpmovdw ymm30{k7},zmm29
    vpmovdw ymm30{k7}{z},zmm29
    vpmovsdw ymm30{k7},zmm29
    vpmovsdw ymm30{k7}{z},zmm29
    vpmovusdw ymm30{k7},zmm29
    vpmovusdw ymm30{k7}{z},zmm29

    vpmovqb qword ptr [rcx],zmm30
    vpmovqb qword ptr [rcx]{k7},zmm30
    vpmovqb qword ptr [rax+r14*8+0x123],zmm30
    vpmovqb qword ptr [rdx+0x3f8],zmm30
    vpmovqb qword ptr [rdx+0x400],zmm30
    vpmovqb qword ptr [rdx-0x400],zmm30
    vpmovqb qword ptr [rdx-0x408],zmm30

    vpmovqw oword ptr [rcx],zmm30
    vpmovqw oword ptr [rcx]{k7},zmm30
    vpmovqw oword ptr [rax+r14*8+0x123],zmm30
    vpmovqw oword ptr [rdx+0x7f0],zmm30
    vpmovqw oword ptr [rdx+0x800],zmm30
    vpmovqw oword ptr [rdx-0x800],zmm30
    vpmovqw oword ptr [rdx-0x810],zmm30

    vpmovqd ymmword ptr [rcx],zmm30
    vpmovqd ymmword ptr [rcx]{k7},zmm30
    vpmovqd ymmword ptr [rax+r14*8+0x123],zmm30
    vpmovqd ymmword ptr [rdx+0xfe0],zmm30
    vpmovqd ymmword ptr [rdx+0x1000],zmm30
    vpmovqd ymmword ptr [rdx-0x1000],zmm30
    vpmovqd ymmword ptr [rdx-0x1020],zmm30

    vpmovdb oword ptr [rcx],zmm30
    vpmovdb oword ptr [rcx]{k7},zmm30
    vpmovdb oword ptr [rax+r14*8+0x123],zmm30
    vpmovdb oword ptr [rdx+0x7f0],zmm30
    vpmovdb oword ptr [rdx+0x800],zmm30
    vpmovdb oword ptr [rdx-0x800],zmm30
    vpmovdb oword ptr [rdx-0x810],zmm30

    vpmovdw ymmword ptr [rcx],zmm30
    vpmovdw ymmword ptr [rcx]{k7},zmm30
    vpmovdw ymmword ptr [rax+r14*8+0x123],zmm30
    vpmovdw ymmword ptr [rdx+0xfe0],zmm30
    vpmovdw ymmword ptr [rdx+0x1000],zmm30
    vpmovdw ymmword ptr [rdx-0x1000],zmm30
    vpmovdw ymmword ptr [rdx-0x1020],zmm30

    vpmovwb xmm1{k1}{z},ymm2
    vpmovwb xmm1{k1}{z},xmm2
    vpmovwb ymm1{k1}{z},zmm2
    vpmovwb [rax],ymm2
    vpmovwb [rax],xmm2
    vpmovwb [rax],zmm2
    vpmovwb oword ptr [rax],ymm2
    vpmovwb qword ptr [rax],xmm2
    vpmovwb ymmword ptr [rax],zmm2

    vpmovsdb xmm30{k7},zmm29
    vpmovsdb xmm30{k7}{z},zmm29
    vpmovsdb oword ptr [rcx],zmm30
    vpmovsdb oword ptr [rcx]{k7},zmm30
    vpmovsdb oword ptr [rax+r14*8+0x123],zmm30
    vpmovsdb oword ptr [rdx+0x7f0],zmm30
    vpmovsdb oword ptr [rdx+0x800],zmm30
    vpmovsdb oword ptr [rdx-0x800],zmm30
    vpmovsdb oword ptr [rdx-0x810],zmm30

    vpmovsdw ymm30{k7},zmm29
    vpmovsdw ymm30{k7}{z},zmm29
    vpmovsdw ymmword ptr [rcx],zmm30
    vpmovsdw ymmword ptr [rcx]{k7},zmm30
    vpmovsdw ymmword ptr [rax+r14*8+0x123],zmm30
    vpmovsdw ymmword ptr [rdx+0xfe0],zmm30
    vpmovsdw ymmword ptr [rdx+0x1000],zmm30
    vpmovsdw ymmword ptr [rdx-0x1000],zmm30
    vpmovsdw ymmword ptr [rdx-0x1020],zmm30

    vpmovsqb xmm30{k7},zmm29
    vpmovsqb xmm30{k7}{z},zmm29
    vpmovsqb qword ptr [rcx],zmm30
    vpmovsqb qword ptr [rcx]{k7},zmm30
    vpmovsqb qword ptr [rax+r14*8+0x123],zmm30
    vpmovsqb qword ptr [rdx+0x3f8],zmm30
    vpmovsqb qword ptr [rdx+0x400],zmm30
    vpmovsqb qword ptr [rdx-0x400],zmm30
    vpmovsqb qword ptr [rdx-0x408],zmm30

    vpmovsqd ymm30{k7},zmm29
    vpmovsqd ymm30{k7}{z},zmm29
    vpmovsqd ymmword ptr [rcx],zmm30
    vpmovsqd ymmword ptr [rcx]{k7},zmm30
    vpmovsqd ymmword ptr [rax+r14*8+0x123],zmm30
    vpmovsqd ymmword ptr [rdx+0xfe0],zmm30
    vpmovsqd ymmword ptr [rdx+0x1000],zmm30
    vpmovsqd ymmword ptr [rdx-0x1000],zmm30
    vpmovsqd ymmword ptr [rdx-0x1020],zmm30

    vpmovsqw xmm30{k7},zmm29
    vpmovsqw xmm30{k7}{z},zmm29
    vpmovsqw oword ptr [rcx],zmm30
    vpmovsqw oword ptr [rcx]{k7},zmm30
    vpmovsqw oword ptr [rax+r14*8+0x123],zmm30
    vpmovsqw oword ptr [rdx+0x7f0],zmm30
    vpmovsqw oword ptr [rdx+0x800],zmm30
    vpmovsqw oword ptr [rdx-0x800],zmm30
    vpmovsqw oword ptr [rdx-0x810],zmm30

    vpmovswb xmm1{k1}{z},ymm2
    vpmovswb xmm1{k1}{z},xmm2
    vpmovswb ymm1{k1}{z},zmm2
    vpmovswb [rax],ymm2
    vpmovswb [rax],xmm2
    vpmovswb [rax],zmm2
    vpmovswb oword ptr [rax],ymm2
    vpmovswb qword ptr [rax],xmm2
    vpmovswb ymmword ptr [rax],zmm2

    vpmovusdb xmm30{k7},zmm29
    vpmovusdb xmm30{k7}{z},zmm29
    vpmovusdb oword ptr [rcx],zmm30
    vpmovusdb oword ptr [rcx]{k7},zmm30
    vpmovusdb oword ptr [rax+r14*8+0x123],zmm30
    vpmovusdb oword ptr [rdx+0x7f0],zmm30
    vpmovusdb oword ptr [rdx+0x800],zmm30
    vpmovusdb oword ptr [rdx-0x800],zmm30
    vpmovusdb oword ptr [rdx-0x810],zmm30

    vpmovusdw ymm30{k7},zmm29
    vpmovusdw ymm30{k7}{z},zmm29
    vpmovusdw ymmword ptr [rcx],zmm30
    vpmovusdw ymmword ptr [rcx]{k7},zmm30
    vpmovusdw ymmword ptr [rax+r14*8+0x123],zmm30
    vpmovusdw ymmword ptr [rdx+0xfe0],zmm30
    vpmovusdw ymmword ptr [rdx+0x1000],zmm30
    vpmovusdw ymmword ptr [rdx-0x1000],zmm30
    vpmovusdw ymmword ptr [rdx-0x1020],zmm30

    vpmovusqb xmm30{k7},zmm29
    vpmovusqb xmm30{k7}{z},zmm29
    vpmovusqb qword ptr [rcx],zmm30
    vpmovusqb qword ptr [rcx]{k7},zmm30
    vpmovusqb qword ptr [rax+r14*8+0x123],zmm30
    vpmovusqb qword ptr [rdx+0x3f8],zmm30
    vpmovusqb qword ptr [rdx+0x400],zmm30
    vpmovusqb qword ptr [rdx-0x400],zmm30
    vpmovusqb qword ptr [rdx-0x408],zmm30

    vpmovusqd ymm30{k7},zmm29
    vpmovusqd ymm30{k7}{z},zmm29
    vpmovusqd ymmword ptr [rcx],zmm30
    vpmovusqd ymmword ptr [rcx]{k7},zmm30
    vpmovusqd ymmword ptr [rax+r14*8+0x123],zmm30
    vpmovusqd ymmword ptr [rdx+0xfe0],zmm30
    vpmovusqd ymmword ptr [rdx+0x1000],zmm30
    vpmovusqd ymmword ptr [rdx-0x1000],zmm30
    vpmovusqd ymmword ptr [rdx-0x1020],zmm30

    vpmovusqw xmm30{k7},zmm29
    vpmovusqw xmm30{k7}{z},zmm29
    vpmovusqw oword ptr [rcx],zmm30
    vpmovusqw oword ptr [rcx]{k7},zmm30
    vpmovusqw oword ptr [rax+r14*8+0x123],zmm30
    vpmovusqw oword ptr [rdx+0x7f0],zmm30
    vpmovusqw oword ptr [rdx+0x800],zmm30
    vpmovusqw oword ptr [rdx-0x800],zmm30
    vpmovusqw oword ptr [rdx-0x810],zmm30

    vpmovuswb xmm1{k1}{z},ymm2
    vpmovuswb xmm1{k1}{z},xmm2
    vpmovuswb ymm1{k1}{z},zmm2
    vpmovuswb [rax],ymm2
    vpmovuswb [rax],xmm2
    vpmovuswb [rax],zmm2
    vpmovuswb oword ptr [rax],ymm2
    vpmovuswb qword ptr [rax],xmm2
    vpmovuswb ymmword ptr [rax],zmm2

    valignd zmm30,zmm29,zmm28,0xab
    valignd zmm30{k7},zmm29,zmm28,0xab
    valignd zmm30{k7}{z},zmm29,zmm28,0xab
    valignd zmm30,zmm29,zmm28,0x7b
    valignd zmm30,zmm29,zmmword ptr [rcx],0x7b
    valignd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123],0x7b
    valignd zmm30,zmm29,dword ptr [rcx]{1to16},0x7b
    valignd zmm30,zmm29,zmmword ptr [rdx+0x1fc0],0x7b
    valignd zmm30,zmm29,zmmword ptr [rdx+0x2000],0x7b
    valignd zmm30,zmm29,zmmword ptr [rdx-0x2000],0x7b
    valignd zmm30,zmm29,zmmword ptr [rdx-0x2040],0x7b
    valignd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16},0x7b
    valignd zmm30,zmm29,dword ptr [rdx+0x200]{1to16},0x7b
    valignd zmm30,zmm29,dword ptr [rdx-0x200]{1to16},0x7b
    valignd zmm30,zmm29,dword ptr [rdx-0x204]{1to16},0x7b

    vblendmpd zmm30,zmm29,zmm28
    vblendmpd zmm30{k7},zmm29,zmm28
    vblendmpd zmm30{k7}{z},zmm29,zmm28
    vblendmpd zmm30,zmm29,zmmword ptr [rcx]
    vblendmpd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vblendmpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vblendmpd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vblendmpd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vblendmpd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vblendmpd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vblendmpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vblendmpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vblendmpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vblendmpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vblendmps zmm30,zmm29,zmm28
    vblendmps zmm30{k7},zmm29,zmm28
    vblendmps zmm30{k7}{z},zmm29,zmm28
    vblendmps zmm30,zmm29,zmmword ptr [rcx]
    vblendmps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vblendmps zmm30,zmm29,dword ptr [rcx]{1to16}
    vblendmps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vblendmps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vblendmps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vblendmps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vblendmps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vblendmps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vblendmps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vblendmps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vbroadcastsd ymm20,qword ptr [rax]
    vbroadcastsd zmm30,qword ptr [rcx]
    vbroadcastsd zmm30{k7},qword ptr [rcx]
    vbroadcastsd zmm30{k7}{z},qword ptr [rcx]
    vbroadcastsd zmm30,qword ptr [rax+r14*8+0x123]
    vbroadcastsd zmm30,qword ptr [rdx+0x3f8]
    vbroadcastsd zmm30,qword ptr [rdx+0x400]
    vbroadcastsd zmm30,qword ptr [rdx-0x400]
    vbroadcastsd zmm30,qword ptr [rdx-0x408]
    vbroadcastsd zmm30{k7},xmm29
    vbroadcastsd zmm30{k7}{z},xmm29

    vbroadcastss xmm20,dword ptr [rax]
    vbroadcastss ymm20,dword ptr [rax]
    vbroadcastss zmm30,dword ptr [rcx]
    vbroadcastss zmm30{k7},dword ptr [rcx]
    vbroadcastss zmm30{k7}{z},dword ptr [rcx]
    vbroadcastss zmm30,dword ptr [rax+r14*8+0x123]
    vbroadcastss zmm30,dword ptr [rdx+0x1fc]
    vbroadcastss zmm30,dword ptr [rdx+0x200]
    vbroadcastss zmm30,dword ptr [rdx-0x200]
    vbroadcastss zmm30,dword ptr [rdx-0x204]
    vbroadcastss zmm30{k7},xmm29
    vbroadcastss zmm30{k7}{z},xmm29

    vcomisd xmm20,xmm1
    vcomisd xmm20,[rax]
    vcomiss xmm20,xmm1
    vcomiss xmm20,[rax]
    vcomisd xmm17,xmm16
    vcomisd xmm16,xmm0
    vcomisd xmm16,[rax]
    vcomisd xmm0,xmm31
    vcomisd xmm0,xmm16
    vcomisd xmm31,xmm1
    vcomisd xmm16,xmm0
    vcomisd xmm30,xmm29
    vcomisd xmm30,xmm29,{sae}
    vcomisd xmm30,qword ptr [rcx]
    vcomisd xmm30,qword ptr [rax+r14*8+0x123]
    vcomisd xmm30,qword ptr [rdx+0x3f8]
    vcomisd xmm30,qword ptr [rdx+0x400]
    vcomisd xmm30,qword ptr [rdx-0x400]
    vcomisd xmm30,qword ptr [rdx-0x408]

    vcomiss xmm30,xmm29
    vcomiss xmm30,xmm29,{sae}
    vcomiss xmm30,dword ptr [rcx]
    vcomiss xmm30,dword ptr [rax+r14*8+0x123]
    vcomiss xmm30,dword ptr [rdx+0x1fc]
    vcomiss xmm30,dword ptr [rdx+0x200]
    vcomiss xmm30,dword ptr [rdx-0x200]
    vcomiss xmm30,dword ptr [rdx-0x204]

    vcvttpd2dq xmm20,xmm1
    vcvttpd2dq xmm20,oword ptr [rax]
    vcvttpd2dq xmm20,ymm1
    vcvttpd2dq xmm20,ymmword ptr [rax]
    vcvttpd2dq ymm30{k7},zmm29
    vcvttpd2dq ymm30{k7}{z},zmm29
    vcvttpd2dq ymm30{k7},zmm29,{sae}
    vcvttpd2dq ymm30{k7},zmmword ptr [rcx]
    vcvttpd2dq ymm30{k7},zmmword ptr [rax+r14*8+0x123]
    vcvttpd2dq ymm30{k7},qword ptr [rcx]{1to8}
    vcvttpd2dq ymm30{k7},zmmword ptr [rdx+0x1fc0]
    vcvttpd2dq ymm30{k7},zmmword ptr [rdx+0x2000]
    vcvttpd2dq ymm30{k7},zmmword ptr [rdx-0x2000]
    vcvttpd2dq ymm30{k7},zmmword ptr [rdx-0x2040]
    vcvttpd2dq ymm30{k7},qword ptr [rdx+0x3f8]{1to8}
    vcvttpd2dq ymm30{k7},qword ptr [rdx+0x400]{1to8}
    vcvttpd2dq ymm30{k7},qword ptr [rdx-0x400]{1to8}
    vcvttpd2dq ymm30{k7},qword ptr [rdx-0x408]{1to8}

    vcvttps2dq xmm20,xmm1
    vcvttps2dq xmm20,oword ptr [rax]
    vcvttps2dq ymm20,ymm1
    vcvttps2dq ymm20,ymmword ptr [rax]
    vcvttps2dq zmm30,zmm29
    vcvttps2dq zmm1{k1}{z},zmm2
    vcvttps2dq zmm30{k7},zmm29
    vcvttps2dq zmm30{k7}{z},zmm29
    vcvttps2dq zmm30,zmm29,{sae}
    vcvttps2dq zmm30,zmmword ptr [rcx]
    vcvttps2dq zmm30,zmmword ptr [rax+r14*8+0x123]
    vcvttps2dq zmm30,dword ptr [rcx]{1to16}
    vcvttps2dq zmm30,zmmword ptr [rdx+0x1fc0]
    vcvttps2dq zmm30,zmmword ptr [rdx+0x2000]
    vcvttps2dq zmm30,zmmword ptr [rdx-0x2000]
    vcvttps2dq zmm30,zmmword ptr [rdx-0x2040]
    vcvttps2dq zmm30,dword ptr [rdx+0x1fc]{1to16}
    vcvttps2dq zmm30,dword ptr [rdx+0x200]{1to16}
    vcvttps2dq zmm30,dword ptr [rdx-0x200]{1to16}
    vcvttps2dq zmm30,dword ptr [rdx-0x204]{1to16}

    vfmadd132pd zmm30,zmm29,zmm28
    vfmadd132pd zmm30{k7},zmm29,zmm28
    vfmadd132pd zmm30{k7}{z},zmm29,zmm28
    vfmadd132pd zmm30,zmm29,zmm28,{rn-sae}
    vfmadd132pd zmm30,zmm29,zmm28,{ru-sae}
    vfmadd132pd zmm30,zmm29,zmm28,{rd-sae}
    vfmadd132pd zmm30,zmm29,zmm28,{rz-sae}
    vfmadd132pd zmm30,zmm29,zmmword ptr [rcx]
    vfmadd132pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmadd132pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmadd132pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmadd132pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmadd132pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmadd132pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmadd132pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmadd132pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmadd132pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmadd132pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfmadd132ps zmm30,zmm29,zmm28
    vfmadd132ps zmm30{k7},zmm29,zmm28
    vfmadd132ps zmm30{k7}{z},zmm29,zmm28
    vfmadd132ps zmm30,zmm29,zmm28,{rn-sae}
    vfmadd132ps zmm30,zmm29,zmm28,{ru-sae}
    vfmadd132ps zmm30,zmm29,zmm28,{rd-sae}
    vfmadd132ps zmm30,zmm29,zmm28,{rz-sae}
    vfmadd132ps zmm30,zmm29,zmmword ptr [rcx]
    vfmadd132ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmadd132ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmadd132ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmadd132ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmadd132ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmadd132ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmadd132ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmadd132ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmadd132ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmadd132ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfmadd132sd xmm30{k7},xmm29,xmm28
    vfmadd132sd xmm30{k7}{z},xmm29,xmm28
    vfmadd132sd xmm30{k7},xmm29,xmm28,{rn-sae}
    vfmadd132sd xmm30{k7},xmm29,xmm28,{ru-sae}
    vfmadd132sd xmm30{k7},xmm29,xmm28,{rd-sae}
    vfmadd132sd xmm30{k7},xmm29,xmm28,{rz-sae}
    vfmadd132sd xmm30{k7},xmm29,qword ptr [rcx]
    vfmadd132sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vfmadd132sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vfmadd132sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vfmadd132sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vfmadd132sd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vfmadd132ss xmm30{k7},xmm29,xmm28
    vfmadd132ss xmm30{k7}{z},xmm29,xmm28
    vfmadd132ss xmm30{k7},xmm29,xmm28,{rn-sae}
    vfmadd132ss xmm30{k7},xmm29,xmm28,{ru-sae}
    vfmadd132ss xmm30{k7},xmm29,xmm28,{rd-sae}
    vfmadd132ss xmm30{k7},xmm29,xmm28,{rz-sae}
    vfmadd132ss xmm30{k7},xmm29,dword ptr [rcx]
    vfmadd132ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vfmadd132ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vfmadd132ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vfmadd132ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vfmadd132ss xmm30{k7},xmm29,dword ptr [rdx-0x204]
    vfmadd213pd zmm30,zmm29,zmm28
    vfmadd213pd zmm30{k7},zmm29,zmm28
    vfmadd213pd zmm30{k7}{z},zmm29,zmm28
    vfmadd213pd zmm30,zmm29,zmm28,{rn-sae}
    vfmadd213pd zmm30,zmm29,zmm28,{ru-sae}
    vfmadd213pd zmm30,zmm29,zmm28,{rd-sae}
    vfmadd213pd zmm30,zmm29,zmm28,{rz-sae}
    vfmadd213pd zmm30,zmm29,zmmword ptr [rcx]
    vfmadd213pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmadd213pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmadd213pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmadd213pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmadd213pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmadd213pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmadd213pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmadd213pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmadd213pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmadd213pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfmadd213ps zmm30,zmm29,zmm28
    vfmadd213ps zmm30{k7},zmm29,zmm28
    vfmadd213ps zmm30{k7}{z},zmm29,zmm28
    vfmadd213ps zmm30,zmm29,zmm28,{rn-sae}
    vfmadd213ps zmm30,zmm29,zmm28,{ru-sae}
    vfmadd213ps zmm30,zmm29,zmm28,{rd-sae}
    vfmadd213ps zmm30,zmm29,zmm28,{rz-sae}
    vfmadd213ps zmm30,zmm29,zmmword ptr [rcx]
    vfmadd213ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmadd213ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmadd213ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmadd213ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmadd213ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmadd213ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmadd213ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmadd213ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmadd213ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmadd213ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfmadd213sd xmm30{k7},xmm29,xmm28
    vfmadd213sd xmm30{k7}{z},xmm29,xmm28
    vfmadd213sd xmm30{k7},xmm29,xmm28,{rn-sae}
    vfmadd213sd xmm30{k7},xmm29,xmm28,{ru-sae}
    vfmadd213sd xmm30{k7},xmm29,xmm28,{rd-sae}
    vfmadd213sd xmm30{k7},xmm29,xmm28,{rz-sae}
    vfmadd213sd xmm30{k7},xmm29,qword ptr [rcx]
    vfmadd213sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vfmadd213sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vfmadd213sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vfmadd213sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vfmadd213sd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vfmadd213ss xmm30{k7},xmm29,xmm28
    vfmadd213ss xmm30{k7}{z},xmm29,xmm28
    vfmadd213ss xmm30{k7},xmm29,xmm28,{rn-sae}
    vfmadd213ss xmm30{k7},xmm29,xmm28,{ru-sae}
    vfmadd213ss xmm30{k7},xmm29,xmm28,{rd-sae}
    vfmadd213ss xmm30{k7},xmm29,xmm28,{rz-sae}
    vfmadd213ss xmm30{k7},xmm29,dword ptr [rcx]
    vfmadd213ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vfmadd213ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vfmadd213ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vfmadd213ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vfmadd213ss xmm30{k7},xmm29,dword ptr [rdx-0x204]
    vfmadd231pd zmm30,zmm29,zmm28
    vfmadd231pd zmm30{k7},zmm29,zmm28
    vfmadd231pd zmm30{k7}{z},zmm29,zmm28
    vfmadd231pd zmm30,zmm29,zmm28,{rn-sae}
    vfmadd231pd zmm30,zmm29,zmm28,{ru-sae}
    vfmadd231pd zmm30,zmm29,zmm28,{rd-sae}
    vfmadd231pd zmm30,zmm29,zmm28,{rz-sae}
    vfmadd231pd zmm30,zmm29,zmmword ptr [rcx]
    vfmadd231pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmadd231pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmadd231pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmadd231pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmadd231pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmadd231pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmadd231pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmadd231pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmadd231pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmadd231pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfmadd231ps zmm30,zmm29,zmm28
    vfmadd231ps zmm30{k7},zmm29,zmm28
    vfmadd231ps zmm30{k7}{z},zmm29,zmm28
    vfmadd231ps zmm30,zmm29,zmm28,{rn-sae}
    vfmadd231ps zmm30,zmm29,zmm28,{ru-sae}
    vfmadd231ps zmm30,zmm29,zmm28,{rd-sae}
    vfmadd231ps zmm30,zmm29,zmm28,{rz-sae}
    vfmadd231ps zmm30,zmm29,zmmword ptr [rcx]
    vfmadd231ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmadd231ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmadd231ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmadd231ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmadd231ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmadd231ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmadd231ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmadd231ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmadd231ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmadd231ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfmadd231sd xmm30{k7},xmm29,xmm28
    vfmadd231sd xmm30{k7}{z},xmm29,xmm28
    vfmadd231sd xmm30{k7},xmm29,xmm28,{rn-sae}
    vfmadd231sd xmm30{k7},xmm29,xmm28,{ru-sae}
    vfmadd231sd xmm30{k7},xmm29,xmm28,{rd-sae}
    vfmadd231sd xmm30{k7},xmm29,xmm28,{rz-sae}
    vfmadd231sd xmm30{k7},xmm29,qword ptr [rcx]
    vfmadd231sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vfmadd231sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vfmadd231sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vfmadd231sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vfmadd231sd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vfmadd231ss xmm30{k7},xmm29,xmm28
    vfmadd231ss xmm30{k7}{z},xmm29,xmm28
    vfmadd231ss xmm30{k7},xmm29,xmm28,{rn-sae}
    vfmadd231ss xmm30{k7},xmm29,xmm28,{ru-sae}
    vfmadd231ss xmm30{k7},xmm29,xmm28,{rd-sae}
    vfmadd231ss xmm30{k7},xmm29,xmm28,{rz-sae}
    vfmadd231ss xmm30{k7},xmm29,dword ptr [rcx]
    vfmadd231ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vfmadd231ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vfmadd231ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vfmadd231ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vfmadd231ss xmm30{k7},xmm29,dword ptr [rdx-0x204]
    vfmaddsub132pd zmm30,zmm29,zmm28
    vfmaddsub132pd zmm30{k7},zmm29,zmm28
    vfmaddsub132pd zmm30{k7}{z},zmm29,zmm28
    vfmaddsub132pd zmm30,zmm29,zmm28,{rn-sae}
    vfmaddsub132pd zmm30,zmm29,zmm28,{ru-sae}
    vfmaddsub132pd zmm30,zmm29,zmm28,{rd-sae}
    vfmaddsub132pd zmm30,zmm29,zmm28,{rz-sae}
    vfmaddsub132pd zmm30,zmm29,zmmword ptr [rcx]
    vfmaddsub132pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmaddsub132pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmaddsub132pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmaddsub132pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmaddsub132pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmaddsub132pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmaddsub132pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmaddsub132pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmaddsub132pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmaddsub132pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfmaddsub132ps zmm30,zmm29,zmm28
    vfmaddsub132ps zmm30{k7},zmm29,zmm28
    vfmaddsub132ps zmm30{k7}{z},zmm29,zmm28
    vfmaddsub132ps zmm30,zmm29,zmm28,{rn-sae}
    vfmaddsub132ps zmm30,zmm29,zmm28,{ru-sae}
    vfmaddsub132ps zmm30,zmm29,zmm28,{rd-sae}
    vfmaddsub132ps zmm30,zmm29,zmm28,{rz-sae}
    vfmaddsub132ps zmm30,zmm29,zmmword ptr [rcx]
    vfmaddsub132ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmaddsub132ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmaddsub132ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmaddsub132ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmaddsub132ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmaddsub132ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmaddsub132ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmaddsub132ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmaddsub132ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmaddsub132ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfmaddsub213pd zmm30,zmm29,zmm28
    vfmaddsub213pd zmm30{k7},zmm29,zmm28
    vfmaddsub213pd zmm30{k7}{z},zmm29,zmm28
    vfmaddsub213pd zmm30,zmm29,zmm28,{rn-sae}
    vfmaddsub213pd zmm30,zmm29,zmm28,{ru-sae}
    vfmaddsub213pd zmm30,zmm29,zmm28,{rd-sae}
    vfmaddsub213pd zmm30,zmm29,zmm28,{rz-sae}
    vfmaddsub213pd zmm30,zmm29,zmmword ptr [rcx]
    vfmaddsub213pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmaddsub213pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmaddsub213pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmaddsub213pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmaddsub213pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmaddsub213pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmaddsub213pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmaddsub213pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmaddsub213pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmaddsub213pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfmaddsub213ps zmm30,zmm29,zmm28
    vfmaddsub213ps zmm30{k7},zmm29,zmm28
    vfmaddsub213ps zmm30{k7}{z},zmm29,zmm28
    vfmaddsub213ps zmm30,zmm29,zmm28,{rn-sae}
    vfmaddsub213ps zmm30,zmm29,zmm28,{ru-sae}
    vfmaddsub213ps zmm30,zmm29,zmm28,{rd-sae}
    vfmaddsub213ps zmm30,zmm29,zmm28,{rz-sae}
    vfmaddsub213ps zmm30,zmm29,zmmword ptr [rcx]
    vfmaddsub213ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmaddsub213ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmaddsub213ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmaddsub213ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmaddsub213ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmaddsub213ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmaddsub213ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmaddsub213ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmaddsub213ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmaddsub213ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfmaddsub231pd zmm30,zmm29,zmm28
    vfmaddsub231pd zmm30{k7},zmm29,zmm28
    vfmaddsub231pd zmm30{k7}{z},zmm29,zmm28
    vfmaddsub231pd zmm30,zmm29,zmm28,{rn-sae}
    vfmaddsub231pd zmm30,zmm29,zmm28,{ru-sae}
    vfmaddsub231pd zmm30,zmm29,zmm28,{rd-sae}
    vfmaddsub231pd zmm30,zmm29,zmm28,{rz-sae}
    vfmaddsub231pd zmm30,zmm29,zmmword ptr [rcx]
    vfmaddsub231pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmaddsub231pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmaddsub231pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmaddsub231pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmaddsub231pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmaddsub231pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmaddsub231pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmaddsub231pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmaddsub231pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmaddsub231pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfmaddsub231ps zmm30,zmm29,zmm28
    vfmaddsub231ps zmm30{k7},zmm29,zmm28
    vfmaddsub231ps zmm30{k7}{z},zmm29,zmm28
    vfmaddsub231ps zmm30,zmm29,zmm28,{rn-sae}
    vfmaddsub231ps zmm30,zmm29,zmm28,{ru-sae}
    vfmaddsub231ps zmm30,zmm29,zmm28,{rd-sae}
    vfmaddsub231ps zmm30,zmm29,zmm28,{rz-sae}
    vfmaddsub231ps zmm30,zmm29,zmmword ptr [rcx]
    vfmaddsub231ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmaddsub231ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmaddsub231ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmaddsub231ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmaddsub231ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmaddsub231ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmaddsub231ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmaddsub231ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmaddsub231ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmaddsub231ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfmsub132pd zmm30,zmm29,zmm28
    vfmsub132pd zmm30{k7},zmm29,zmm28
    vfmsub132pd zmm30{k7}{z},zmm29,zmm28
    vfmsub132pd zmm30,zmm29,zmm28,{rn-sae}
    vfmsub132pd zmm30,zmm29,zmm28,{ru-sae}
    vfmsub132pd zmm30,zmm29,zmm28,{rd-sae}
    vfmsub132pd zmm30,zmm29,zmm28,{rz-sae}
    vfmsub132pd zmm30,zmm29,zmmword ptr [rcx]
    vfmsub132pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmsub132pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmsub132pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmsub132pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmsub132pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmsub132pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmsub132pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmsub132pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmsub132pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmsub132pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfmsub132ps zmm30,zmm29,zmm28
    vfmsub132ps zmm30{k7},zmm29,zmm28
    vfmsub132ps zmm30{k7}{z},zmm29,zmm28
    vfmsub132ps zmm30,zmm29,zmm28,{rn-sae}
    vfmsub132ps zmm30,zmm29,zmm28,{ru-sae}
    vfmsub132ps zmm30,zmm29,zmm28,{rd-sae}
    vfmsub132ps zmm30,zmm29,zmm28,{rz-sae}
    vfmsub132ps zmm30,zmm29,zmmword ptr [rcx]
    vfmsub132ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmsub132ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmsub132ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmsub132ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmsub132ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmsub132ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmsub132ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmsub132ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmsub132ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmsub132ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfmsub132sd xmm30{k7},xmm29,xmm28
    vfmsub132sd xmm30{k7}{z},xmm29,xmm28
    vfmsub132sd xmm30{k7},xmm29,xmm28,{rn-sae}
    vfmsub132sd xmm30{k7},xmm29,xmm28,{ru-sae}
    vfmsub132sd xmm30{k7},xmm29,xmm28,{rd-sae}
    vfmsub132sd xmm30{k7},xmm29,xmm28,{rz-sae}
    vfmsub132sd xmm30{k7},xmm29,qword ptr [rcx]
    vfmsub132sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vfmsub132sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vfmsub132sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vfmsub132sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vfmsub132sd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vfmsub132ss xmm30{k7},xmm29,xmm28
    vfmsub132ss xmm30{k7}{z},xmm29,xmm28
    vfmsub132ss xmm30{k7},xmm29,xmm28,{rn-sae}
    vfmsub132ss xmm30{k7},xmm29,xmm28,{ru-sae}
    vfmsub132ss xmm30{k7},xmm29,xmm28,{rd-sae}
    vfmsub132ss xmm30{k7},xmm29,xmm28,{rz-sae}
    vfmsub132ss xmm30{k7},xmm29,dword ptr [rcx]
    vfmsub132ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vfmsub132ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vfmsub132ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vfmsub132ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vfmsub132ss xmm30{k7},xmm29,dword ptr [rdx-0x204]
    vfmsub213pd zmm30,zmm29,zmm28
    vfmsub213pd zmm30{k7},zmm29,zmm28
    vfmsub213pd zmm30{k7}{z},zmm29,zmm28
    vfmsub213pd zmm30,zmm29,zmm28,{rn-sae}
    vfmsub213pd zmm30,zmm29,zmm28,{ru-sae}
    vfmsub213pd zmm30,zmm29,zmm28,{rd-sae}
    vfmsub213pd zmm30,zmm29,zmm28,{rz-sae}
    vfmsub213pd zmm30,zmm29,zmmword ptr [rcx]
    vfmsub213pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmsub213pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmsub213pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmsub213pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmsub213pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmsub213pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmsub213pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmsub213pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmsub213pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmsub213pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfmsub213ps zmm30,zmm29,zmm28
    vfmsub213ps zmm30{k7},zmm29,zmm28
    vfmsub213ps zmm30{k7}{z},zmm29,zmm28
    vfmsub213ps zmm30,zmm29,zmm28,{rn-sae}
    vfmsub213ps zmm30,zmm29,zmm28,{ru-sae}
    vfmsub213ps zmm30,zmm29,zmm28,{rd-sae}
    vfmsub213ps zmm30,zmm29,zmm28,{rz-sae}
    vfmsub213ps zmm30,zmm29,zmmword ptr [rcx]
    vfmsub213ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmsub213ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmsub213ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmsub213ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmsub213ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmsub213ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmsub213ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmsub213ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmsub213ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmsub213ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfmsub213sd xmm30{k7},xmm29,xmm28
    vfmsub213sd xmm30{k7}{z},xmm29,xmm28
    vfmsub213sd xmm30{k7},xmm29,xmm28,{rn-sae}
    vfmsub213sd xmm30{k7},xmm29,xmm28,{ru-sae}
    vfmsub213sd xmm30{k7},xmm29,xmm28,{rd-sae}
    vfmsub213sd xmm30{k7},xmm29,xmm28,{rz-sae}
    vfmsub213sd xmm30{k7},xmm29,qword ptr [rcx]
    vfmsub213sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vfmsub213sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vfmsub213sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vfmsub213sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vfmsub213sd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vfmsub213ss xmm30{k7},xmm29,xmm28
    vfmsub213ss xmm30{k7}{z},xmm29,xmm28
    vfmsub213ss xmm30{k7},xmm29,xmm28,{rn-sae}
    vfmsub213ss xmm30{k7},xmm29,xmm28,{ru-sae}
    vfmsub213ss xmm30{k7},xmm29,xmm28,{rd-sae}
    vfmsub213ss xmm30{k7},xmm29,xmm28,{rz-sae}
    vfmsub213ss xmm30{k7},xmm29,dword ptr [rcx]
    vfmsub213ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vfmsub213ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vfmsub213ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vfmsub213ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vfmsub213ss xmm30{k7},xmm29,dword ptr [rdx-0x204]
    vfmsub231pd zmm30,zmm29,zmm28
    vfmsub231pd zmm30{k7},zmm29,zmm28
    vfmsub231pd zmm30{k7}{z},zmm29,zmm28
    vfmsub231pd zmm30,zmm29,zmm28,{rn-sae}
    vfmsub231pd zmm30,zmm29,zmm28,{ru-sae}
    vfmsub231pd zmm30,zmm29,zmm28,{rd-sae}
    vfmsub231pd zmm30,zmm29,zmm28,{rz-sae}
    vfmsub231pd zmm30,zmm29,zmmword ptr [rcx]
    vfmsub231pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmsub231pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmsub231pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmsub231pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmsub231pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmsub231pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmsub231pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmsub231pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmsub231pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmsub231pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfmsub231ps zmm30,zmm29,zmm28
    vfmsub231ps zmm30{k7},zmm29,zmm28
    vfmsub231ps zmm30{k7}{z},zmm29,zmm28
    vfmsub231ps zmm30,zmm29,zmm28,{rn-sae}
    vfmsub231ps zmm30,zmm29,zmm28,{ru-sae}
    vfmsub231ps zmm30,zmm29,zmm28,{rd-sae}
    vfmsub231ps zmm30,zmm29,zmm28,{rz-sae}
    vfmsub231ps zmm30,zmm29,zmmword ptr [rcx]
    vfmsub231ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmsub231ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmsub231ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmsub231ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmsub231ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmsub231ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmsub231ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmsub231ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmsub231ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmsub231ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfmsub231sd xmm30{k7},xmm29,xmm28
    vfmsub231sd xmm30{k7}{z},xmm29,xmm28
    vfmsub231sd xmm30{k7},xmm29,xmm28,{rn-sae}
    vfmsub231sd xmm30{k7},xmm29,xmm28,{ru-sae}
    vfmsub231sd xmm30{k7},xmm29,xmm28,{rd-sae}
    vfmsub231sd xmm30{k7},xmm29,xmm28,{rz-sae}
    vfmsub231sd xmm30{k7},xmm29,qword ptr [rcx]
    vfmsub231sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vfmsub231sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vfmsub231sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vfmsub231sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vfmsub231sd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vfmsub231ss xmm30{k7},xmm29,xmm28
    vfmsub231ss xmm30{k7}{z},xmm29,xmm28
    vfmsub231ss xmm30{k7},xmm29,xmm28,{rn-sae}
    vfmsub231ss xmm30{k7},xmm29,xmm28,{ru-sae}
    vfmsub231ss xmm30{k7},xmm29,xmm28,{rd-sae}
    vfmsub231ss xmm30{k7},xmm29,xmm28,{rz-sae}
    vfmsub231ss xmm30{k7},xmm29,dword ptr [rcx]
    vfmsub231ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vfmsub231ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vfmsub231ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vfmsub231ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vfmsub231ss xmm30{k7},xmm29,dword ptr [rdx-0x204]
    vfmsubadd132pd zmm30,zmm29,zmm28
    vfmsubadd132pd zmm30{k7},zmm29,zmm28
    vfmsubadd132pd zmm30{k7}{z},zmm29,zmm28
    vfmsubadd132pd zmm30,zmm29,zmm28,{rn-sae}
    vfmsubadd132pd zmm30,zmm29,zmm28,{ru-sae}
    vfmsubadd132pd zmm30,zmm29,zmm28,{rd-sae}
    vfmsubadd132pd zmm30,zmm29,zmm28,{rz-sae}
    vfmsubadd132pd zmm30,zmm29,zmmword ptr [rcx]
    vfmsubadd132pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmsubadd132pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmsubadd132pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmsubadd132pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmsubadd132pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmsubadd132pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmsubadd132pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmsubadd132pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmsubadd132pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmsubadd132pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfmsubadd132ps zmm30,zmm29,zmm28
    vfmsubadd132ps zmm30{k7},zmm29,zmm28
    vfmsubadd132ps zmm30{k7}{z},zmm29,zmm28
    vfmsubadd132ps zmm30,zmm29,zmm28,{rn-sae}
    vfmsubadd132ps zmm30,zmm29,zmm28,{ru-sae}
    vfmsubadd132ps zmm30,zmm29,zmm28,{rd-sae}
    vfmsubadd132ps zmm30,zmm29,zmm28,{rz-sae}
    vfmsubadd132ps zmm30,zmm29,zmmword ptr [rcx]
    vfmsubadd132ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmsubadd132ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmsubadd132ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmsubadd132ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmsubadd132ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmsubadd132ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmsubadd132ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmsubadd132ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmsubadd132ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmsubadd132ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfmsubadd213pd zmm30,zmm29,zmm28
    vfmsubadd213pd zmm30{k7},zmm29,zmm28
    vfmsubadd213pd zmm30{k7}{z},zmm29,zmm28
    vfmsubadd213pd zmm30,zmm29,zmm28,{rn-sae}
    vfmsubadd213pd zmm30,zmm29,zmm28,{ru-sae}
    vfmsubadd213pd zmm30,zmm29,zmm28,{rd-sae}
    vfmsubadd213pd zmm30,zmm29,zmm28,{rz-sae}
    vfmsubadd213pd zmm30,zmm29,zmmword ptr [rcx]
    vfmsubadd213pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmsubadd213pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmsubadd213pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmsubadd213pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmsubadd213pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmsubadd213pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmsubadd213pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmsubadd213pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmsubadd213pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmsubadd213pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfmsubadd213ps zmm30,zmm29,zmm28
    vfmsubadd213ps zmm30{k7},zmm29,zmm28
    vfmsubadd213ps zmm30{k7}{z},zmm29,zmm28
    vfmsubadd213ps zmm30,zmm29,zmm28,{rn-sae}
    vfmsubadd213ps zmm30,zmm29,zmm28,{ru-sae}
    vfmsubadd213ps zmm30,zmm29,zmm28,{rd-sae}
    vfmsubadd213ps zmm30,zmm29,zmm28,{rz-sae}
    vfmsubadd213ps zmm30,zmm29,zmmword ptr [rcx]
    vfmsubadd213ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmsubadd213ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmsubadd213ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmsubadd213ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmsubadd213ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmsubadd213ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmsubadd213ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmsubadd213ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmsubadd213ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmsubadd213ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfmsubadd231pd zmm30,zmm29,zmm28
    vfmsubadd231pd zmm30{k7},zmm29,zmm28
    vfmsubadd231pd zmm30{k7}{z},zmm29,zmm28
    vfmsubadd231pd zmm30,zmm29,zmm28,{rn-sae}
    vfmsubadd231pd zmm30,zmm29,zmm28,{ru-sae}
    vfmsubadd231pd zmm30,zmm29,zmm28,{rd-sae}
    vfmsubadd231pd zmm30,zmm29,zmm28,{rz-sae}
    vfmsubadd231pd zmm30,zmm29,zmmword ptr [rcx]
    vfmsubadd231pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmsubadd231pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfmsubadd231pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmsubadd231pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmsubadd231pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmsubadd231pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmsubadd231pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfmsubadd231pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfmsubadd231pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfmsubadd231pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfmsubadd231ps zmm30,zmm29,zmm28
    vfmsubadd231ps zmm30{k7},zmm29,zmm28
    vfmsubadd231ps zmm30{k7}{z},zmm29,zmm28
    vfmsubadd231ps zmm30,zmm29,zmm28,{rn-sae}
    vfmsubadd231ps zmm30,zmm29,zmm28,{ru-sae}
    vfmsubadd231ps zmm30,zmm29,zmm28,{rd-sae}
    vfmsubadd231ps zmm30,zmm29,zmm28,{rz-sae}
    vfmsubadd231ps zmm30,zmm29,zmmword ptr [rcx]
    vfmsubadd231ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfmsubadd231ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfmsubadd231ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfmsubadd231ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfmsubadd231ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfmsubadd231ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfmsubadd231ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfmsubadd231ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfmsubadd231ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfmsubadd231ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfnmadd132pd zmm30,zmm29,zmm28
    vfnmadd132pd zmm30{k7},zmm29,zmm28
    vfnmadd132pd zmm30{k7}{z},zmm29,zmm28
    vfnmadd132pd zmm30,zmm29,zmm28,{rn-sae}
    vfnmadd132pd zmm30,zmm29,zmm28,{ru-sae}
    vfnmadd132pd zmm30,zmm29,zmm28,{rd-sae}
    vfnmadd132pd zmm30,zmm29,zmm28,{rz-sae}
    vfnmadd132pd zmm30,zmm29,zmmword ptr [rcx]
    vfnmadd132pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfnmadd132pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfnmadd132pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfnmadd132pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfnmadd132pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfnmadd132pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfnmadd132pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfnmadd132pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfnmadd132pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfnmadd132pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfnmadd132ps zmm30,zmm29,zmm28
    vfnmadd132ps zmm30{k7},zmm29,zmm28
    vfnmadd132ps zmm30{k7}{z},zmm29,zmm28
    vfnmadd132ps zmm30,zmm29,zmm28,{rn-sae}
    vfnmadd132ps zmm30,zmm29,zmm28,{ru-sae}
    vfnmadd132ps zmm30,zmm29,zmm28,{rd-sae}
    vfnmadd132ps zmm30,zmm29,zmm28,{rz-sae}
    vfnmadd132ps zmm30,zmm29,zmmword ptr [rcx]
    vfnmadd132ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfnmadd132ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfnmadd132ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfnmadd132ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfnmadd132ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfnmadd132ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfnmadd132ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfnmadd132ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfnmadd132ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfnmadd132ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfnmadd132sd xmm30{k7},xmm29,xmm28
    vfnmadd132sd xmm30{k7}{z},xmm29,xmm28
    vfnmadd132sd xmm30{k7},xmm29,xmm28,{rn-sae}
    vfnmadd132sd xmm30{k7},xmm29,xmm28,{ru-sae}
    vfnmadd132sd xmm30{k7},xmm29,xmm28,{rd-sae}
    vfnmadd132sd xmm30{k7},xmm29,xmm28,{rz-sae}
    vfnmadd132sd xmm30{k7},xmm29,qword ptr [rcx]
    vfnmadd132sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vfnmadd132sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vfnmadd132sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vfnmadd132sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vfnmadd132sd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vfnmadd132ss xmm30{k7},xmm29,xmm28
    vfnmadd132ss xmm30{k7}{z},xmm29,xmm28
    vfnmadd132ss xmm30{k7},xmm29,xmm28,{rn-sae}
    vfnmadd132ss xmm30{k7},xmm29,xmm28,{ru-sae}
    vfnmadd132ss xmm30{k7},xmm29,xmm28,{rd-sae}
    vfnmadd132ss xmm30{k7},xmm29,xmm28,{rz-sae}
    vfnmadd132ss xmm30{k7},xmm29,dword ptr [rcx]
    vfnmadd132ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vfnmadd132ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vfnmadd132ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vfnmadd132ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vfnmadd132ss xmm30{k7},xmm29,dword ptr [rdx-0x204]
    vfnmadd213pd zmm30,zmm29,zmm28
    vfnmadd213pd zmm30{k7},zmm29,zmm28
    vfnmadd213pd zmm30{k7}{z},zmm29,zmm28
    vfnmadd213pd zmm30,zmm29,zmm28,{rn-sae}
    vfnmadd213pd zmm30,zmm29,zmm28,{ru-sae}
    vfnmadd213pd zmm30,zmm29,zmm28,{rd-sae}
    vfnmadd213pd zmm30,zmm29,zmm28,{rz-sae}
    vfnmadd213pd zmm30,zmm29,zmmword ptr [rcx]
    vfnmadd213pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfnmadd213pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfnmadd213pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfnmadd213pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfnmadd213pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfnmadd213pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfnmadd213pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfnmadd213pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfnmadd213pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfnmadd213pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfnmadd213ps zmm30,zmm29,zmm28
    vfnmadd213ps zmm30{k7},zmm29,zmm28
    vfnmadd213ps zmm30{k7}{z},zmm29,zmm28
    vfnmadd213ps zmm30,zmm29,zmm28,{rn-sae}
    vfnmadd213ps zmm30,zmm29,zmm28,{ru-sae}
    vfnmadd213ps zmm30,zmm29,zmm28,{rd-sae}
    vfnmadd213ps zmm30,zmm29,zmm28,{rz-sae}
    vfnmadd213ps zmm30,zmm29,zmmword ptr [rcx]
    vfnmadd213ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfnmadd213ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfnmadd213ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfnmadd213ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfnmadd213ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfnmadd213ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfnmadd213ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfnmadd213ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfnmadd213ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfnmadd213ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfnmadd213sd xmm30{k7},xmm29,xmm28
    vfnmadd213sd xmm30{k7}{z},xmm29,xmm28
    vfnmadd213sd xmm30{k7},xmm29,xmm28,{rn-sae}
    vfnmadd213sd xmm30{k7},xmm29,xmm28,{ru-sae}
    vfnmadd213sd xmm30{k7},xmm29,xmm28,{rd-sae}
    vfnmadd213sd xmm30{k7},xmm29,xmm28,{rz-sae}
    vfnmadd213sd xmm30{k7},xmm29,qword ptr [rcx]
    vfnmadd213sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vfnmadd213sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vfnmadd213sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vfnmadd213sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vfnmadd213sd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vfnmadd213ss xmm30{k7},xmm29,xmm28
    vfnmadd213ss xmm30{k7}{z},xmm29,xmm28
    vfnmadd213ss xmm30{k7},xmm29,xmm28,{rn-sae}
    vfnmadd213ss xmm30{k7},xmm29,xmm28,{ru-sae}
    vfnmadd213ss xmm30{k7},xmm29,xmm28,{rd-sae}
    vfnmadd213ss xmm30{k7},xmm29,xmm28,{rz-sae}
    vfnmadd213ss xmm30{k7},xmm29,dword ptr [rcx]
    vfnmadd213ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vfnmadd213ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vfnmadd213ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vfnmadd213ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vfnmadd213ss xmm30{k7},xmm29,dword ptr [rdx-0x204]
    vfnmadd231pd zmm30,zmm29,zmm28
    vfnmadd231pd zmm30{k7},zmm29,zmm28
    vfnmadd231pd zmm30{k7}{z},zmm29,zmm28
    vfnmadd231pd zmm30,zmm29,zmm28,{rn-sae}
    vfnmadd231pd zmm30,zmm29,zmm28,{ru-sae}
    vfnmadd231pd zmm30,zmm29,zmm28,{rd-sae}
    vfnmadd231pd zmm30,zmm29,zmm28,{rz-sae}
    vfnmadd231pd zmm30,zmm29,zmmword ptr [rcx]
    vfnmadd231pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfnmadd231pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfnmadd231pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfnmadd231pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfnmadd231pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfnmadd231pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfnmadd231pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfnmadd231pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfnmadd231pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfnmadd231pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfnmadd231ps zmm30,zmm29,zmm28
    vfnmadd231ps zmm30{k7},zmm29,zmm28
    vfnmadd231ps zmm30{k7}{z},zmm29,zmm28
    vfnmadd231ps zmm30,zmm29,zmm28,{rn-sae}
    vfnmadd231ps zmm30,zmm29,zmm28,{ru-sae}
    vfnmadd231ps zmm30,zmm29,zmm28,{rd-sae}
    vfnmadd231ps zmm30,zmm29,zmm28,{rz-sae}
    vfnmadd231ps zmm30,zmm29,zmmword ptr [rcx]
    vfnmadd231ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfnmadd231ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfnmadd231ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfnmadd231ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfnmadd231ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfnmadd231ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfnmadd231ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfnmadd231ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfnmadd231ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfnmadd231ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfnmadd231sd xmm30{k7},xmm29,xmm28
    vfnmadd231sd xmm30{k7}{z},xmm29,xmm28
    vfnmadd231sd xmm30{k7},xmm29,xmm28,{rn-sae}
    vfnmadd231sd xmm30{k7},xmm29,xmm28,{ru-sae}
    vfnmadd231sd xmm30{k7},xmm29,xmm28,{rd-sae}
    vfnmadd231sd xmm30{k7},xmm29,xmm28,{rz-sae}
    vfnmadd231sd xmm30{k7},xmm29,qword ptr [rcx]
    vfnmadd231sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vfnmadd231sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vfnmadd231sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vfnmadd231sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vfnmadd231sd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vfnmadd231ss xmm30{k7},xmm29,xmm28
    vfnmadd231ss xmm30{k7}{z},xmm29,xmm28
    vfnmadd231ss xmm30{k7},xmm29,xmm28,{rn-sae}
    vfnmadd231ss xmm30{k7},xmm29,xmm28,{ru-sae}
    vfnmadd231ss xmm30{k7},xmm29,xmm28,{rd-sae}
    vfnmadd231ss xmm30{k7},xmm29,xmm28,{rz-sae}
    vfnmadd231ss xmm30{k7},xmm29,dword ptr [rcx]
    vfnmadd231ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vfnmadd231ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vfnmadd231ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vfnmadd231ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vfnmadd231ss xmm30{k7},xmm29,dword ptr [rdx-0x204]
    vfnmsub132pd zmm30,zmm29,zmm28
    vfnmsub132pd zmm30{k7},zmm29,zmm28
    vfnmsub132pd zmm30{k7}{z},zmm29,zmm28
    vfnmsub132pd zmm30,zmm29,zmm28,{rn-sae}
    vfnmsub132pd zmm30,zmm29,zmm28,{ru-sae}
    vfnmsub132pd zmm30,zmm29,zmm28,{rd-sae}
    vfnmsub132pd zmm30,zmm29,zmm28,{rz-sae}
    vfnmsub132pd zmm30,zmm29,zmmword ptr [rcx]
    vfnmsub132pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfnmsub132pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfnmsub132pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfnmsub132pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfnmsub132pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfnmsub132pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfnmsub132pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfnmsub132pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfnmsub132pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfnmsub132pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfnmsub132ps zmm30,zmm29,zmm28
    vfnmsub132ps zmm30{k7},zmm29,zmm28
    vfnmsub132ps zmm30{k7}{z},zmm29,zmm28
    vfnmsub132ps zmm30,zmm29,zmm28,{rn-sae}
    vfnmsub132ps zmm30,zmm29,zmm28,{ru-sae}
    vfnmsub132ps zmm30,zmm29,zmm28,{rd-sae}
    vfnmsub132ps zmm30,zmm29,zmm28,{rz-sae}
    vfnmsub132ps zmm30,zmm29,zmmword ptr [rcx]
    vfnmsub132ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfnmsub132ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfnmsub132ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfnmsub132ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfnmsub132ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfnmsub132ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfnmsub132ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfnmsub132ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfnmsub132ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfnmsub132ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfnmsub132sd xmm30{k7},xmm29,xmm28
    vfnmsub132sd xmm30{k7}{z},xmm29,xmm28
    vfnmsub132sd xmm30{k7},xmm29,xmm28,{rn-sae}
    vfnmsub132sd xmm30{k7},xmm29,xmm28,{ru-sae}
    vfnmsub132sd xmm30{k7},xmm29,xmm28,{rd-sae}
    vfnmsub132sd xmm30{k7},xmm29,xmm28,{rz-sae}
    vfnmsub132sd xmm30{k7},xmm29,qword ptr [rcx]
    vfnmsub132sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vfnmsub132sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vfnmsub132sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vfnmsub132sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vfnmsub132sd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vfnmsub132ss xmm30{k7},xmm29,xmm28
    vfnmsub132ss xmm30{k7}{z},xmm29,xmm28
    vfnmsub132ss xmm30{k7},xmm29,xmm28,{rn-sae}
    vfnmsub132ss xmm30{k7},xmm29,xmm28,{ru-sae}
    vfnmsub132ss xmm30{k7},xmm29,xmm28,{rd-sae}
    vfnmsub132ss xmm30{k7},xmm29,xmm28,{rz-sae}
    vfnmsub132ss xmm30{k7},xmm29,dword ptr [rcx]
    vfnmsub132ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vfnmsub132ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vfnmsub132ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vfnmsub132ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vfnmsub132ss xmm30{k7},xmm29,dword ptr [rdx-0x204]
    vfnmsub213pd zmm30,zmm29,zmm28
    vfnmsub213pd zmm30{k7},zmm29,zmm28
    vfnmsub213pd zmm30{k7}{z},zmm29,zmm28
    vfnmsub213pd zmm30,zmm29,zmm28,{rn-sae}
    vfnmsub213pd zmm30,zmm29,zmm28,{ru-sae}
    vfnmsub213pd zmm30,zmm29,zmm28,{rd-sae}
    vfnmsub213pd zmm30,zmm29,zmm28,{rz-sae}
    vfnmsub213pd zmm30,zmm29,zmmword ptr [rcx]
    vfnmsub213pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfnmsub213pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfnmsub213pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfnmsub213pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfnmsub213pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfnmsub213pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfnmsub213pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfnmsub213pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfnmsub213pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfnmsub213pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfnmsub213ps zmm30,zmm29,zmm28
    vfnmsub213ps zmm30{k7},zmm29,zmm28
    vfnmsub213ps zmm30{k7}{z},zmm29,zmm28
    vfnmsub213ps zmm30,zmm29,zmm28,{rn-sae}
    vfnmsub213ps zmm30,zmm29,zmm28,{ru-sae}
    vfnmsub213ps zmm30,zmm29,zmm28,{rd-sae}
    vfnmsub213ps zmm30,zmm29,zmm28,{rz-sae}
    vfnmsub213ps zmm30,zmm29,zmmword ptr [rcx]
    vfnmsub213ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfnmsub213ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfnmsub213ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfnmsub213ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfnmsub213ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfnmsub213ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfnmsub213ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfnmsub213ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfnmsub213ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfnmsub213ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfnmsub213sd xmm30{k7},xmm29,xmm28
    vfnmsub213sd xmm30{k7}{z},xmm29,xmm28
    vfnmsub213sd xmm30{k7},xmm29,xmm28,{rn-sae}
    vfnmsub213sd xmm30{k7},xmm29,xmm28,{ru-sae}
    vfnmsub213sd xmm30{k7},xmm29,xmm28,{rd-sae}
    vfnmsub213sd xmm30{k7},xmm29,xmm28,{rz-sae}
    vfnmsub213sd xmm30{k7},xmm29,qword ptr [rcx]
    vfnmsub213sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vfnmsub213sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vfnmsub213sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vfnmsub213sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vfnmsub213sd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vfnmsub213ss xmm30{k7},xmm29,xmm28
    vfnmsub213ss xmm30{k7}{z},xmm29,xmm28
    vfnmsub213ss xmm30{k7},xmm29,xmm28,{rn-sae}
    vfnmsub213ss xmm30{k7},xmm29,xmm28,{ru-sae}
    vfnmsub213ss xmm30{k7},xmm29,xmm28,{rd-sae}
    vfnmsub213ss xmm30{k7},xmm29,xmm28,{rz-sae}
    vfnmsub213ss xmm30{k7},xmm29,dword ptr [rcx]
    vfnmsub213ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vfnmsub213ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vfnmsub213ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vfnmsub213ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vfnmsub213ss xmm30{k7},xmm29,dword ptr [rdx-0x204]
    vfnmsub231pd zmm30,zmm29,zmm28
    vfnmsub231pd zmm30{k7},zmm29,zmm28
    vfnmsub231pd zmm30{k7}{z},zmm29,zmm28
    vfnmsub231pd zmm30,zmm29,zmm28,{rn-sae}
    vfnmsub231pd zmm30,zmm29,zmm28,{ru-sae}
    vfnmsub231pd zmm30,zmm29,zmm28,{rd-sae}
    vfnmsub231pd zmm30,zmm29,zmm28,{rz-sae}
    vfnmsub231pd zmm30,zmm29,zmmword ptr [rcx]
    vfnmsub231pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfnmsub231pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vfnmsub231pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfnmsub231pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfnmsub231pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfnmsub231pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfnmsub231pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vfnmsub231pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vfnmsub231pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vfnmsub231pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}
    vfnmsub231ps zmm30,zmm29,zmm28
    vfnmsub231ps zmm30{k7},zmm29,zmm28
    vfnmsub231ps zmm30{k7}{z},zmm29,zmm28
    vfnmsub231ps zmm30,zmm29,zmm28,{rn-sae}
    vfnmsub231ps zmm30,zmm29,zmm28,{ru-sae}
    vfnmsub231ps zmm30,zmm29,zmm28,{rd-sae}
    vfnmsub231ps zmm30,zmm29,zmm28,{rz-sae}
    vfnmsub231ps zmm30,zmm29,zmmword ptr [rcx]
    vfnmsub231ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vfnmsub231ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vfnmsub231ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vfnmsub231ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vfnmsub231ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vfnmsub231ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vfnmsub231ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vfnmsub231ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vfnmsub231ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vfnmsub231ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vfnmsub231sd xmm30{k7},xmm29,xmm28
    vfnmsub231sd xmm30{k7}{z},xmm29,xmm28
    vfnmsub231sd xmm30{k7},xmm29,xmm28,{rn-sae}
    vfnmsub231sd xmm30{k7},xmm29,xmm28,{ru-sae}
    vfnmsub231sd xmm30{k7},xmm29,xmm28,{rd-sae}
    vfnmsub231sd xmm30{k7},xmm29,xmm28,{rz-sae}
    vfnmsub231sd xmm30{k7},xmm29,qword ptr [rcx]
    vfnmsub231sd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vfnmsub231sd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vfnmsub231sd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vfnmsub231sd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vfnmsub231sd xmm30{k7},xmm29,qword ptr [rdx-0x408]
    vfnmsub231ss xmm30{k7},xmm29,xmm28
    vfnmsub231ss xmm30{k7}{z},xmm29,xmm28
    vfnmsub231ss xmm30{k7},xmm29,xmm28,{rn-sae}
    vfnmsub231ss xmm30{k7},xmm29,xmm28,{ru-sae}
    vfnmsub231ss xmm30{k7},xmm29,xmm28,{rd-sae}
    vfnmsub231ss xmm30{k7},xmm29,xmm28,{rz-sae}
    vfnmsub231ss xmm30{k7},xmm29,dword ptr [rcx]
    vfnmsub231ss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vfnmsub231ss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vfnmsub231ss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vfnmsub231ss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vfnmsub231ss xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vgetmantpd zmm30,zmm29,0xab
    vgetmantpd zmm30{k7},zmm29,0xab
    vgetmantpd zmm30{k7}{z},zmm29,0xab
    vgetmantpd zmm30,zmm29,{sae},0xab
    vgetmantpd zmm30,zmm29,0x7b
    vgetmantpd zmm30,zmm29,{sae},0x7b
    vgetmantpd zmm30,zmmword ptr [rcx],0x7b
    vgetmantpd zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vgetmantpd zmm30,qword ptr [rcx]{1to8},0x7b
    vgetmantpd zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vgetmantpd zmm30,zmmword ptr [rdx+0x2000],0x7b
    vgetmantpd zmm30,zmmword ptr [rdx-0x2000],0x7b
    vgetmantpd zmm30,zmmword ptr [rdx-0x2040],0x7b
    vgetmantpd zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vgetmantpd zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vgetmantpd zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vgetmantpd zmm30,qword ptr [rdx-0x408]{1to8},0x7b
    vgetmantps zmm30,zmm29,0xab
    vgetmantps zmm30{k7},zmm29,0xab
    vgetmantps zmm30{k7}{z},zmm29,0xab
    vgetmantps zmm30,zmm29,{sae},0xab
    vgetmantps zmm30,zmm29,0x7b
    vgetmantps zmm30,zmm29,{sae},0x7b
    vgetmantps zmm30,zmmword ptr [rcx],0x7b
    vgetmantps zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vgetmantps zmm30,dword ptr [rcx]{1to16},0x7b
    vgetmantps zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vgetmantps zmm30,zmmword ptr [rdx+0x2000],0x7b
    vgetmantps zmm30,zmmword ptr [rdx-0x2000],0x7b
    vgetmantps zmm30,zmmword ptr [rdx-0x2040],0x7b
    vgetmantps zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vgetmantps zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vgetmantps zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vgetmantps zmm30,dword ptr [rdx-0x204]{1to16},0x7b
    vgetmantsd xmm30{k7},xmm29,xmm28,0xab
    vgetmantsd xmm30{k7}{z},xmm29,xmm28,0xab
    vgetmantsd xmm30{k7},xmm29,xmm28,{sae},0xab
    vgetmantsd xmm30{k7},xmm29,xmm28,0x7b
    vgetmantsd xmm30{k7},xmm29,xmm28,{sae},0x7b
    vgetmantsd xmm30{k7},xmm29,qword ptr [rcx],0x7b
    vgetmantsd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123],0x7b
    vgetmantsd xmm30{k7},xmm29,qword ptr [rdx+0x3f8],0x7b
    vgetmantsd xmm30{k7},xmm29,qword ptr [rdx+0x400],0x7b
    vgetmantsd xmm30{k7},xmm29,qword ptr [rdx-0x400],0x7b
    vgetmantsd xmm30{k7},xmm29,qword ptr [rdx-0x408],0x7b
    vgetmantss xmm30{k7},xmm29,xmm28,0xab
    vgetmantss xmm30{k7}{z},xmm29,xmm28,0xab
    vgetmantss xmm30{k7},xmm29,xmm28,{sae},0xab
    vgetmantss xmm30{k7},xmm29,xmm28,0x7b
    vgetmantss xmm30{k7},xmm29,xmm28,{sae},0x7b
    vgetmantss xmm30{k7},xmm29,dword ptr [rcx],0x7b
    vgetmantss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123],0x7b
    vgetmantss xmm30{k7},xmm29,dword ptr [rdx+0x1fc],0x7b
    vgetmantss xmm30{k7},xmm29,dword ptr [rdx+0x200],0x7b
    vgetmantss xmm30{k7},xmm29,dword ptr [rdx-0x200],0x7b
    vgetmantss xmm30{k7},xmm29,dword ptr [rdx-0x204],0x7b

    vinsertf32x4 zmm30{k7},zmm29,xmm28,0xab
    vinsertf32x4 zmm30{k7}{z},zmm29,xmm28,0xab
    vinsertf32x4 zmm30{k7},zmm29,xmm28,0x7b
    vinsertf32x4 zmm30{k7},zmm29,oword ptr [rcx],0x7b
    vinsertf32x4 zmm30{k7},zmm29,oword ptr [rax+r14*8+0x123],0x7b
    vinsertf32x4 zmm30{k7},zmm29,oword ptr [rdx+0x7f0],0x7b
    vinsertf32x4 zmm30{k7},zmm29,oword ptr [rdx+0x800],0x7b
    vinsertf32x4 zmm30{k7},zmm29,oword ptr [rdx-0x800],0x7b
    vinsertf32x4 zmm30{k7},zmm29,oword ptr [rdx-0x810],0x7b
    vinsertf64x4 zmm30{k7},zmm29,ymm28,0xab
    vinsertf64x4 zmm30{k7}{z},zmm29,ymm28,0xab
    vinsertf64x4 zmm30{k7},zmm29,ymm28,0x7b
    vinsertf64x4 zmm30{k7},zmm29,ymmword ptr [rcx],0x7b
    vinsertf64x4 zmm30{k7},zmm29,ymmword ptr [rax+r14*8+0x123],0x7b
    vinsertf64x4 zmm30{k7},zmm29,ymmword ptr [rdx+0xfe0],0x7b
    vinsertf64x4 zmm30{k7},zmm29,ymmword ptr [rdx+0x1000],0x7b
    vinsertf64x4 zmm30{k7},zmm29,ymmword ptr [rdx-0x1000],0x7b
    vinsertf64x4 zmm30{k7},zmm29,ymmword ptr [rdx-0x1020],0x7b
    vinserti32x4 zmm30{k7},zmm29,xmm28,0xab
    vinserti32x4 zmm30{k7}{z},zmm29,xmm28,0xab
    vinserti32x4 zmm30{k7},zmm29,xmm28,0x7b
    vinserti32x4 zmm30{k7},zmm29,oword ptr [rcx],0x7b
    vinserti32x4 zmm30{k7},zmm29,oword ptr [rax+r14*8+0x123],0x7b
    vinserti32x4 zmm30{k7},zmm29,oword ptr [rdx+0x7f0],0x7b
    vinserti32x4 zmm30{k7},zmm29,oword ptr [rdx+0x800],0x7b
    vinserti32x4 zmm30{k7},zmm29,oword ptr [rdx-0x800],0x7b
    vinserti32x4 zmm30{k7},zmm29,oword ptr [rdx-0x810],0x7b
    vinserti64x4 zmm30{k7},zmm29,ymm28,0xab
    vinserti64x4 zmm30{k7}{z},zmm29,ymm28,0xab
    vinserti64x4 zmm30{k7},zmm29,ymm28,0x7b
    vinserti64x4 zmm30{k7},zmm29,ymmword ptr [rcx],0x7b
    vinserti64x4 zmm30{k7},zmm29,ymmword ptr [rax+r14*8+0x123],0x7b
    vinserti64x4 zmm30{k7},zmm29,ymmword ptr [rdx+0xfe0],0x7b
    vinserti64x4 zmm30{k7},zmm29,ymmword ptr [rdx+0x1000],0x7b
    vinserti64x4 zmm30{k7},zmm29,ymmword ptr [rdx-0x1000],0x7b
    vinserti64x4 zmm30{k7},zmm29,ymmword ptr [rdx-0x1020],0x7b

    vmovddup xmm2,xmm1
    vmovddup xmm20,xmm1
    vmovddup xmm20,qword ptr [rax]
    vmovddup ymm20,ymm1
    vmovddup ymm20,ymmword ptr [rax]
    vmovddup zmm30,zmm29
    vmovddup zmm30{k7},zmm29
    vmovddup zmm30{k7}{z},zmm29
    vmovddup zmm30,zmmword ptr [rcx]
    vmovddup zmm30,zmmword ptr [rax+r14*8+0x123]
    vmovddup zmm30,zmmword ptr [rdx+0x1fc0]
    vmovddup zmm30,zmmword ptr [rdx+0x2000]
    vmovddup zmm30,zmmword ptr [rdx-0x2000]
    vmovddup zmm30,zmmword ptr [rdx-0x2040]

    vmovhpd xmm20,xmm1,qword ptr [rax]
    vmovhpd xmm29,xmm30,qword ptr [rcx]
    vmovhpd xmm29,xmm30,qword ptr [rax+r14*8+0x123]
    vmovhpd xmm29,xmm30,qword ptr [rdx+0x3f8]
    vmovhpd xmm29,xmm30,qword ptr [rdx+0x400]
    vmovhpd xmm29,xmm30,qword ptr [rdx-0x400]
    vmovhpd xmm29,xmm30,qword ptr [rdx-0x408]
    vmovhpd qword ptr [rax],xmm21
    vmovhpd qword ptr [rcx],xmm30
    vmovhpd qword ptr [rax+r14*8+0x123],xmm30
    vmovhpd qword ptr [rdx+0x3f8],xmm30
    vmovhpd qword ptr [rdx+0x400],xmm30
    vmovhpd qword ptr [rdx-0x400],xmm30
    vmovhpd qword ptr [rdx-0x408],xmm30

    vmovhps xmm20,xmm1,qword ptr [rax]
    vmovhps xmm29,xmm30,qword ptr [rcx]
    vmovhps xmm29,xmm30,qword ptr [rax+r14*8+0x123]
    vmovhps xmm29,xmm30,qword ptr [rdx+0x3f8]
    vmovhps xmm29,xmm30,qword ptr [rdx+0x400]
    vmovhps xmm29,xmm30,qword ptr [rdx-0x400]
    vmovhps xmm29,xmm30,qword ptr [rdx-0x408]
    vmovhps qword ptr [rax],xmm21
    vmovhps qword ptr [rcx],xmm30
    vmovhps qword ptr [rax+r14*8+0x123],xmm30
    vmovhps qword ptr [rdx+0x3f8],xmm30
    vmovhps qword ptr [rdx+0x400],xmm30
    vmovhps qword ptr [rdx-0x400],xmm30
    vmovhps qword ptr [rdx-0x408],xmm30

    vmovlpd xmm20,xmm1,qword ptr [rax]
    vmovlpd xmm29,xmm30,qword ptr [rcx]
    vmovlpd xmm29,xmm30,qword ptr [rax+r14*8+0x123]
    vmovlpd xmm29,xmm30,qword ptr [rdx+0x3f8]
    vmovlpd xmm29,xmm30,qword ptr [rdx+0x400]
    vmovlpd xmm29,xmm30,qword ptr [rdx-0x400]
    vmovlpd xmm29,xmm30,qword ptr [rdx-0x408]
    vmovlpd qword ptr [rax],xmm21
    vmovlpd qword ptr [rcx],xmm30
    vmovlpd qword ptr [rax+r14*8+0x123],xmm30
    vmovlpd qword ptr [rdx+0x3f8],xmm30
    vmovlpd qword ptr [rdx+0x400],xmm30
    vmovlpd qword ptr [rdx-0x400],xmm30
    vmovlpd qword ptr [rdx-0x408],xmm30

    vmovlps xmm20,xmm1,qword ptr [rax]
    vmovlps xmm29,xmm30,qword ptr [rcx]
    vmovlps xmm29,xmm30,qword ptr [rax+r14*8+0x123]
    vmovlps xmm29,xmm30,qword ptr [rdx+0x3f8]
    vmovlps xmm29,xmm30,qword ptr [rdx+0x400]
    vmovlps xmm29,xmm30,qword ptr [rdx-0x400]
    vmovlps xmm29,xmm30,qword ptr [rdx-0x408]
    vmovlps qword ptr [rax],xmm21
    vmovlps qword ptr [rcx],xmm30
    vmovlps qword ptr [rax+r14*8+0x123],xmm30
    vmovlps qword ptr [rdx+0x3f8],xmm30
    vmovlps qword ptr [rdx+0x400],xmm30
    vmovlps qword ptr [rdx-0x400],xmm30
    vmovlps qword ptr [rdx-0x408],xmm30

    vpabsq zmm30,zmm29
    vpabsq zmm30{k7},zmm29
    vpabsq zmm30{k7}{z},zmm29
    vpabsq zmm30,zmmword ptr [rcx]
    vpabsq zmm30,zmmword ptr [rax+r14*8+0x123]
    vpabsq zmm30,qword ptr [rcx]{1to8}
    vpabsq zmm30,zmmword ptr [rdx+0x1fc0]
    vpabsq zmm30,zmmword ptr [rdx+0x2000]
    vpabsq zmm30,zmmword ptr [rdx-0x2000]
    vpabsq zmm30,zmmword ptr [rdx-0x2040]
    vpabsq zmm30,qword ptr [rdx+0x3f8]{1to8}
    vpabsq zmm30,qword ptr [rdx+0x400]{1to8}
    vpabsq zmm30,qword ptr [rdx-0x400]{1to8}
    vpabsq zmm30,qword ptr [rdx-0x408]{1to8}

    vpblendmd zmm30,zmm29,zmm28
    vpblendmd zmm30{k7},zmm29,zmm28
    vpblendmd zmm30{k7}{z},zmm29,zmm28
    vpblendmd zmm30,zmm29,zmmword ptr [rcx]
    vpblendmd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpblendmd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpblendmd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpblendmd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpblendmd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpblendmd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpblendmd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpblendmd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpblendmd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpblendmd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpbroadcastd zmm30,dword ptr [rcx]
    vpbroadcastd zmm30{k7},dword ptr [rcx]
    vpbroadcastd zmm30{k7}{z},dword ptr [rcx]
    vpbroadcastd zmm30,dword ptr [rax+r14*8+0x123]
    vpbroadcastd zmm30,dword ptr [rdx+0x1fc]
    vpbroadcastd zmm30,dword ptr [rdx+0x200]
    vpbroadcastd zmm30,dword ptr [rdx-0x200]
    vpbroadcastd zmm30,dword ptr [rdx-0x204]
    vpbroadcastd zmm30{k7},xmm29
    vpbroadcastd zmm30{k7}{z},xmm29
    vpbroadcastd zmm30,eax
    vpbroadcastd zmm30{k7},eax
    vpbroadcastd zmm30{k7}{z},eax
    vpbroadcastd zmm30,ebp
    vpbroadcastd zmm30,r13d

    vpbroadcastq zmm30,qword ptr [rcx]
    vpbroadcastq zmm30{k7},qword ptr [rcx]
    vpbroadcastq zmm30{k7}{z},qword ptr [rcx]
    vpbroadcastq zmm30,qword ptr [rax+r14*8+0x123]
    vpbroadcastq zmm30,qword ptr [rdx+0x3f8]
    vpbroadcastq zmm30,qword ptr [rdx+0x400]
    vpbroadcastq zmm30,qword ptr [rdx-0x400]
    vpbroadcastq zmm30,qword ptr [rdx-0x408]
    vpbroadcastq zmm30{k7},xmm29
    vpbroadcastq zmm30{k7}{z},xmm29
    vpbroadcastq zmm30,rax
    vpbroadcastq zmm30{k7},rax
    vpbroadcastq zmm30{k7}{z},rax
    vpbroadcastq zmm30,r8

    vpcmpd k5,zmm30,zmm29,0xab
    vpcmpd k5{k7},zmm30,zmm29,0xab
    vpcmpd k5,zmm30,zmm29,0x7b
    vpcmpd k5,zmm30,zmmword ptr [rcx],0x7b
    vpcmpd k5,zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vpcmpd k5,zmm30,dword ptr [rcx]{1to16},0x7b
    vpcmpd k5,zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vpcmpd k5,zmm30,zmmword ptr [rdx+0x2000],0x7b
    vpcmpd k5,zmm30,zmmword ptr [rdx-0x2000],0x7b
    vpcmpd k5,zmm30,zmmword ptr [rdx-0x2040],0x7b
    vpcmpd k5,zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpcmpd k5,zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vpcmpd k5,zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vpcmpd k5,zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vpcmpq k5,zmm30,zmm29,0xab
    vpcmpq k5{k7},zmm30,zmm29,0xab
    vpcmpq k5,zmm30,zmm29,0x7b
    vpcmpq k5,zmm30,zmmword ptr [rcx],0x7b
    vpcmpq k5,zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vpcmpq k5,zmm30,qword ptr [rcx]{1to8},0x7b
    vpcmpq k5,zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vpcmpq k5,zmm30,zmmword ptr [rdx+0x2000],0x7b
    vpcmpq k5,zmm30,zmmword ptr [rdx-0x2000],0x7b
    vpcmpq k5,zmm30,zmmword ptr [rdx-0x2040],0x7b
    vpcmpq k5,zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpcmpq k5,zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpcmpq k5,zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpcmpq k5,zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vpcmpud k5,zmm30,zmm29,0xab
    vpcmpud k5{k7},zmm30,zmm29,0xab
    vpcmpud k5,zmm30,zmm29,0x7b
    vpcmpud k5,zmm30,zmmword ptr [rcx],0x7b
    vpcmpud k5,zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vpcmpud k5,zmm30,dword ptr [rcx]{1to16},0x7b
    vpcmpud k5,zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vpcmpud k5,zmm30,zmmword ptr [rdx+0x2000],0x7b
    vpcmpud k5,zmm30,zmmword ptr [rdx-0x2000],0x7b
    vpcmpud k5,zmm30,zmmword ptr [rdx-0x2040],0x7b
    vpcmpud k5,zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpcmpud k5,zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vpcmpud k5,zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vpcmpud k5,zmm30,dword ptr [rdx-0x204]{1to16},0x7b


    vpcmpuq k5,zmm30,zmm29,0xab
    vpcmpuq k5{k7},zmm30,zmm29,0xab
    vpcmpuq k5,zmm30,zmm29,0x7b
    vpcmpuq k5,zmm30,zmmword ptr [rcx],0x7b
    vpcmpuq k5,zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vpcmpuq k5,zmm30,qword ptr [rcx]{1to8},0x7b
    vpcmpuq k5,zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vpcmpuq k5,zmm30,zmmword ptr [rdx+0x2000],0x7b
    vpcmpuq k5,zmm30,zmmword ptr [rdx-0x2000],0x7b
    vpcmpuq k5,zmm30,zmmword ptr [rdx-0x2040],0x7b
    vpcmpuq k5,zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpcmpuq k5,zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpcmpuq k5,zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpcmpuq k5,zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vpblendmq zmm30,zmm29,zmm28
    vpblendmq zmm30{k7},zmm29,zmm28
    vpblendmq zmm30{k7}{z},zmm29,zmm28
    vpblendmq zmm30,zmm29,zmmword ptr [rcx]
    vpblendmq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpblendmq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpblendmq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpblendmq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpblendmq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpblendmq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpblendmq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpblendmq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpblendmq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpblendmq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpermd zmm30,zmm29,zmm28
    vpermd zmm30{k7},zmm29,zmm28
    vpermd zmm30{k7}{z},zmm29,zmm28
    vpermd zmm30,zmm29,zmmword ptr [rcx]
    vpermd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpermd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpermd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpermd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpermd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpermd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpermd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpermd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpermd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpermd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpermilpd xmm20,xmm1,xmm2
    vpermilpd xmm20,xmm1,oword ptr [rax]
    vpermilpd xmm20,xmm1,1
    vpermilpd ymm20,ymm1,ymm2
    vpermilpd ymm20,ymm1,ymmword ptr [rax]
    vpermilpd ymm20,ymm1,1
    vpermilpd zmm30,zmm29,0xab
    vpermilpd zmm30{k7},zmm29,0xab
    vpermilpd zmm30{k7}{z},zmm29,0xab
    vpermilpd zmm30,zmm29,0x7b
    vpermilpd zmm30,zmmword ptr [rcx],0x7b
    vpermilpd zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vpermilpd zmm30,qword ptr [rcx]{1to8},0x7b
    vpermilpd zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vpermilpd zmm30,zmmword ptr [rdx+0x2000],0x7b
    vpermilpd zmm30,zmmword ptr [rdx-0x2000],0x7b
    vpermilpd zmm30,zmmword ptr [rdx-0x2040],0x7b
    vpermilpd zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpermilpd zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpermilpd zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpermilpd zmm30,qword ptr [rdx-0x408]{1to8},0x7b
    vpermilpd zmm30,zmm29,zmm28
    vpermilpd zmm30{k7},zmm29,zmm28
    vpermilpd zmm30{k7}{z},zmm29,zmm28
    vpermilpd zmm30,zmm29,zmmword ptr [rcx]
    vpermilpd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpermilpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vpermilpd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpermilpd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpermilpd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpermilpd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpermilpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpermilpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpermilpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpermilpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpermilps xmm20,xmm1,xmm2
    vpermilps xmm20,xmm1,oword ptr [rax]
    vpermilps xmm20,xmm1,1
    vpermilps ymm20,ymm1,ymm2
    vpermilps ymm20,ymm1,ymmword ptr [rax]
    vpermilps ymm20,ymm1,1
    vpermilps zmm30,zmm29,0xab
    vpermilps zmm30{k7},zmm29,0xab
    vpermilps zmm30{k7}{z},zmm29,0xab
    vpermilps zmm30,zmm29,0x7b
    vpermilps zmm30,zmmword ptr [rcx],0x7b
    vpermilps zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vpermilps zmm30,dword ptr [rcx]{1to16},0x7b
    vpermilps zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vpermilps zmm30,zmmword ptr [rdx+0x2000],0x7b
    vpermilps zmm30,zmmword ptr [rdx-0x2000],0x7b
    vpermilps zmm30,zmmword ptr [rdx-0x2040],0x7b
    vpermilps zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpermilps zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vpermilps zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vpermilps zmm30,dword ptr [rdx-0x204]{1to16},0x7b
    vpermilps zmm30,zmm29,zmm28
    vpermilps zmm30{k7},zmm29,zmm28
    vpermilps zmm30{k7}{z},zmm29,zmm28
    vpermilps zmm30,zmm29,zmmword ptr [rcx]
    vpermilps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpermilps zmm30,zmm29,dword ptr [rcx]{1to16}
    vpermilps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpermilps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpermilps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpermilps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpermilps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpermilps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpermilps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpermilps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpermpd ymm20,ymm6,0x7
    vpermpd ymm20,ymmword ptr [rcx],0x7
    vpermpd zmm30,zmm29,0xab
    vpermpd zmm30{k7},zmm29,0xab
    vpermpd zmm30{k7}{z},zmm29,0xab
    vpermpd zmm30,zmm29,0x7b
    vpermpd zmm30,zmmword ptr [rcx],0x7b
    vpermpd zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vpermpd zmm30,qword ptr [rcx]{1to8},0x7b
    vpermpd zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vpermpd zmm30,zmmword ptr [rdx+0x2000],0x7b
    vpermpd zmm30,zmmword ptr [rdx-0x2000],0x7b
    vpermpd zmm30,zmmword ptr [rdx-0x2040],0x7b
    vpermpd zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpermpd zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpermpd zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpermpd zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vpermpd zmm30,zmm29,zmm28
    vpermpd zmm30{k7},zmm29,zmm28
    vpermpd zmm30{k7}{z},zmm29,zmm28
    vpermpd zmm30,zmm29,zmmword ptr [rcx]
    vpermpd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpermpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vpermpd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpermpd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpermpd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpermpd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpermpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpermpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpermpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpermpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpermps ymm20,ymm6,ymm4
    vpermps ymm20,ymm6,YMMWORD PTR [rcx]
    vpermps zmm30,zmm29,zmm28
    vpermps zmm30{k7},zmm29,zmm28
    vpermps zmm30{k7}{z},zmm29,zmm28
    vpermps zmm30,zmm29,zmmword ptr [rcx]
    vpermps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpermps zmm30,zmm29,dword ptr [rcx]{1to16}
    vpermps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpermps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpermps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpermps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpermps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpermps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpermps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpermps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vpermq ymm20,ymm6,0x7
    vpermq ymm20,YMMWORD PTR [rcx],0x7
    vpermd ymm20,ymm6,ymm4
    vpermd ymm20,ymm6,YMMWORD PTR [rcx]
    vpermq zmm30,zmm29,0xab
    vpermq zmm30{k7},zmm29,0xab
    vpermq zmm30{k7}{z},zmm29,0xab
    vpermq zmm30,zmm29,0x7b
    vpermq zmm30,zmmword ptr [rcx],0x7b
    vpermq zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vpermq zmm30,qword ptr [rcx]{1to8},0x7b
    vpermq zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vpermq zmm30,zmmword ptr [rdx+0x2000],0x7b
    vpermq zmm30,zmmword ptr [rdx-0x2000],0x7b
    vpermq zmm30,zmmword ptr [rdx-0x2040],0x7b
    vpermq zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpermq zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vpermq zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vpermq zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vpermq zmm30,zmm29,zmm28
    vpermq zmm30{k7},zmm29,zmm28
    vpermq zmm30{k7}{z},zmm29,zmm28
    vpermq zmm30,zmm29,zmmword ptr [rcx]
    vpermq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpermq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpermq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpermq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpermq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpermq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpermq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpermq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpermq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpermq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpmaxsq zmm30,zmm29,zmm28
    vpmaxsq zmm30{k7},zmm29,zmm28
    vpmaxsq zmm30{k7}{z},zmm29,zmm28
    vpmaxsq zmm30,zmm29,zmmword ptr [rcx]
    vpmaxsq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpmaxsq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpmaxsq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpmaxsq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpmaxsq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpmaxsq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpmaxsq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpmaxsq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpmaxsq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpmaxsq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpmaxuq zmm30,zmm29,zmm28
    vpmaxuq zmm30{k7},zmm29,zmm28
    vpmaxuq zmm30{k7}{z},zmm29,zmm28
    vpmaxuq zmm30,zmm29,zmmword ptr [rcx]
    vpmaxuq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpmaxuq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpmaxuq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpmaxuq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpmaxuq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpmaxuq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpmaxuq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpmaxuq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpmaxuq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpmaxuq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpminsq zmm30,zmm29,zmm28
    vpminsq zmm30{k7},zmm29,zmm28
    vpminsq zmm30{k7}{z},zmm29,zmm28
    vpminsq zmm30,zmm29,zmmword ptr [rcx]
    vpminsq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpminsq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpminsq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpminsq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpminsq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpminsq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpminsq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpminsq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpminsq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpminsq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpminuq zmm30,zmm29,zmm28
    vpminuq zmm30{k7},zmm29,zmm28
    vpminuq zmm30{k7}{z},zmm29,zmm28
    vpminuq zmm30,zmm29,zmmword ptr [rcx]
    vpminuq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpminuq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpminuq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpminuq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpminuq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpminuq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpminuq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpminuq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpminuq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpminuq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpord  zmm30,zmm29,zmm28
    vpord  zmm30{k7},zmm29,zmm28
    vpord  zmm30{k7}{z},zmm29,zmm28
    vpord  zmm30,zmm29,zmmword ptr [rcx]
    vpord  zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpord  zmm30,zmm29,dword ptr [rcx]{1to16}
    vpord  zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpord  zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpord  zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpord  zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpord  zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpord  zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpord  zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpord  zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vporq  zmm30,zmm29,zmm28
    vporq  zmm30{k7},zmm29,zmm28
    vporq  zmm30{k7}{z},zmm29,zmm28
    vporq  zmm30,zmm29,zmmword ptr [rcx]
    vporq  zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vporq  zmm30,zmm29,qword ptr [rcx]{1to8}
    vporq  zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vporq  zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vporq  zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vporq  zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vporq  zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vporq  zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vporq  zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vporq  zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpsllvd ymm20,ymm6,ymm4
    vpsllvd ymm20,ymm6,ymmword ptr [rcx]
    vpsllvq ymm20,ymm6,ymm4
    vpsllvq ymm20,ymm6,ymmword ptr [rcx]
    vpsravd ymm20,ymm6,ymm4
    vpsravd ymm20,ymm6,ymmword ptr [rcx]
    vpsrlvd ymm20,ymm6,ymm4
    vpsrlvd ymm20,ymm6,ymmword ptr [rcx]
    vpsrlvq ymm20,ymm6,ymm4
    vpsrlvq ymm20,ymm6,ymmword ptr [rcx]

    vpsllvd zmm30,zmm29,zmm28
    vpsllvd zmm30{k7},zmm29,zmm28
    vpsllvd zmm30{k7}{z},zmm29,zmm28
    vpsllvd zmm30,zmm29,zmmword ptr [rcx]
    vpsllvd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpsllvd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpsllvd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpsllvd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpsllvd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpsllvd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpsllvd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpsllvd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpsllvd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpsllvd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vpsllvq zmm30,zmm29,zmm28
    vpsllvq zmm30{k7},zmm29,zmm28
    vpsllvq zmm30{k7}{z},zmm29,zmm28
    vpsllvq zmm30,zmm29,zmmword ptr [rcx]
    vpsllvq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpsllvq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpsllvq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpsllvq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpsllvq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpsllvq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpsllvq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpsllvq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpsllvq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpsllvq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpsravd zmm30,zmm29,zmm28
    vpsravd zmm30{k7},zmm29,zmm28
    vpsravd zmm30{k7}{z},zmm29,zmm28
    vpsravd zmm30,zmm29,zmmword ptr [rcx]
    vpsravd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpsravd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpsravd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpsravd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpsravd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpsravd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpsravd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpsravd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpsravd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpsravd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vpsravq zmm30,zmm29,zmm28
    vpsravq zmm30{k7},zmm29,zmm28
    vpsravq zmm30{k7}{z},zmm29,zmm28
    vpsravq zmm30,zmm29,zmmword ptr [rcx]
    vpsravq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpsravq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpsravq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpsravq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpsravq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpsravq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpsravq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpsravq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpsravq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpsravq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpsrlvd zmm30,zmm29,zmm28
    vpsrlvd zmm30{k7},zmm29,zmm28
    vpsrlvd zmm30{k7}{z},zmm29,zmm28
    vpsrlvd zmm30,zmm29,zmmword ptr [rcx]
    vpsrlvd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpsrlvd zmm30,zmm29,dword ptr [rcx]{1to16}
    vpsrlvd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpsrlvd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpsrlvd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpsrlvd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpsrlvd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpsrlvd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpsrlvd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpsrlvd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vpsrlvq zmm30,zmm29,zmm28
    vpsrlvq zmm30{k7},zmm29,zmm28
    vpsrlvq zmm30{k7}{z},zmm29,zmm28
    vpsrlvq zmm30,zmm29,zmmword ptr [rcx]
    vpsrlvq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpsrlvq zmm30,zmm29,qword ptr [rcx]{1to8}
    vpsrlvq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpsrlvq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpsrlvq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpsrlvq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpsrlvq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpsrlvq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpsrlvq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpsrlvq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vptestmd k5,zmm30,zmm29
    vptestmd k5{k7},zmm30,zmm29
    vptestmd k5,zmm30,zmmword ptr [rcx]
    vptestmd k5,zmm30,zmmword ptr [rax+r14*8+0x123]
    vptestmd k5,zmm30,dword ptr [rcx]{1to16}
    vptestmd k5,zmm30,zmmword ptr [rdx+0x1fc0]
    vptestmd k5,zmm30,zmmword ptr [rdx+0x2000]
    vptestmd k5,zmm30,zmmword ptr [rdx-0x2000]
    vptestmd k5,zmm30,zmmword ptr [rdx-0x2040]
    vptestmd k5,zmm30,dword ptr [rdx+0x1fc]{1to16}
    vptestmd k5,zmm30,dword ptr [rdx+0x200]{1to16}
    vptestmd k5,zmm30,dword ptr [rdx-0x200]{1to16}
    vptestmd k5,zmm30,dword ptr [rdx-0x204]{1to16}
    vptestmq k5,zmm30,zmm29
    vptestmq k5{k7},zmm30,zmm29
    vptestmq k5,zmm30,zmmword ptr [rcx]
    vptestmq k5,zmm30,zmmword ptr [rax+r14*8+0x123]
    vptestmq k5,zmm30,qword ptr [rcx]{1to8}
    vptestmq k5,zmm30,zmmword ptr [rdx+0x1fc0]
    vptestmq k5,zmm30,zmmword ptr [rdx+0x2000]
    vptestmq k5,zmm30,zmmword ptr [rdx-0x2000]
    vptestmq k5,zmm30,zmmword ptr [rdx-0x2040]
    vptestmq k5,zmm30,qword ptr [rdx+0x3f8]{1to8}
    vptestmq k5,zmm30,qword ptr [rdx+0x400]{1to8}
    vptestmq k5,zmm30,qword ptr [rdx-0x400]{1to8}
    vptestmq k5,zmm30,qword ptr [rdx-0x408]{1to8}

    vucomisd xmm20,xmm1
    vucomisd xmm20,[rax]
    vucomisd xmm30,xmm29
    vucomisd xmm30,xmm29,{sae}
    vucomisd xmm30,qword ptr [rcx]
    vucomisd xmm30,qword ptr [rax+r14*8+0x123]
    vucomisd xmm30,qword ptr [rdx+0x3f8]
    vucomisd xmm30,qword ptr [rdx+0x400]
    vucomisd xmm30,qword ptr [rdx-0x400]
    vucomisd xmm30,qword ptr [rdx-0x408]

    vucomiss xmm20,xmm1
    vucomiss xmm20,[rax]
    vucomiss xmm30,xmm29
    vucomiss xmm30,xmm29,{sae}
    vucomiss xmm30,dword ptr [rcx]
    vucomiss xmm30,dword ptr [rax+r14*8+0x123]
    vucomiss xmm30,dword ptr [rdx+0x1fc]
    vucomiss xmm30,dword ptr [rdx+0x200]
    vucomiss xmm30,dword ptr [rdx-0x200]
    vucomiss xmm30,dword ptr [rdx-0x204]

    vpternlogd zmm30,zmm29,zmm28,0xab
    vpternlogd zmm30{k7},zmm29,zmm28,0xab
    vpternlogd zmm30{k7}{z},zmm29,zmm28,0xab
    vpternlogd zmm30,zmm29,zmm28,0x7b
    vpternlogd zmm30,zmm29,zmmword ptr [rcx],0x7b
    vpternlogd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123],0x7b
    vpternlogd zmm30,zmm29,dword ptr [rcx]{1to16},0x7b
    vpternlogd zmm30,zmm29,zmmword ptr [rdx+0x1fc0],0x7b
    vpternlogd zmm30,zmm29,zmmword ptr [rdx+0x2000],0x7b
    vpternlogd zmm30,zmm29,zmmword ptr [rdx-0x2000],0x7b
    vpternlogd zmm30,zmm29,zmmword ptr [rdx-0x2040],0x7b
    vpternlogd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16},0x7b
    vpternlogd zmm30,zmm29,dword ptr [rdx+0x200]{1to16},0x7b
    vpternlogd zmm30,zmm29,dword ptr [rdx-0x200]{1to16},0x7b
    vpternlogd zmm30,zmm29,dword ptr [rdx-0x204]{1to16},0x7b
    vpternlogq zmm30,zmm29,zmm28,0xab
    vpternlogq zmm30{k7},zmm29,zmm28,0xab
    vpternlogq zmm30{k7}{z},zmm29,zmm28,0xab
    vpternlogq zmm30,zmm29,zmm28,0x7b
    vpternlogq zmm30,zmm29,zmmword ptr [rcx],0x7b
    vpternlogq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123],0x7b
    vpternlogq zmm30,zmm29,qword ptr [rcx]{1to8},0x7b
    vpternlogq zmm30,zmm29,zmmword ptr [rdx+0x1fc0],0x7b
    vpternlogq zmm30,zmm29,zmmword ptr [rdx+0x2000],0x7b
    vpternlogq zmm30,zmm29,zmmword ptr [rdx-0x2000],0x7b
    vpternlogq zmm30,zmm29,zmmword ptr [rdx-0x2040],0x7b
    vpternlogq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8},0x7b
    vpternlogq zmm30,zmm29,qword ptr [rdx+0x400]{1to8},0x7b
    vpternlogq zmm30,zmm29,qword ptr [rdx-0x400]{1to8},0x7b
    vpternlogq zmm30,zmm29,qword ptr [rdx-0x408]{1to8},0x7b

    vshuff32x4 zmm30,zmm29,zmm28,0xab
    vshuff32x4 zmm30{k7},zmm29,zmm28,0xab
    vshuff32x4 zmm30{k7}{z},zmm29,zmm28,0xab
    vshuff32x4 zmm30,zmm29,zmm28,0x7b
    vshuff32x4 zmm30,zmm29,zmmword ptr [rcx],0x7b
    vshuff32x4 zmm30,zmm29,zmmword ptr [rax+r14*8+0x123],0x7b
    vshuff32x4 zmm30,zmm29,dword ptr [rcx]{1to16},0x7b
    vshuff32x4 zmm30,zmm29,zmmword ptr [rdx+0x1fc0],0x7b
    vshuff32x4 zmm30,zmm29,zmmword ptr [rdx+0x2000],0x7b
    vshuff32x4 zmm30,zmm29,zmmword ptr [rdx-0x2000],0x7b
    vshuff32x4 zmm30,zmm29,zmmword ptr [rdx-0x2040],0x7b
    vshuff32x4 zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16},0x7b
    vshuff32x4 zmm30,zmm29,dword ptr [rdx+0x200]{1to16},0x7b
    vshuff32x4 zmm30,zmm29,dword ptr [rdx-0x200]{1to16},0x7b
    vshuff32x4 zmm30,zmm29,dword ptr [rdx-0x204]{1to16},0x7b
    vshuff64x2 zmm30,zmm29,zmm28,0xab
    vshuff64x2 zmm30{k7},zmm29,zmm28,0xab
    vshuff64x2 zmm30{k7}{z},zmm29,zmm28,0xab
    vshuff64x2 zmm30,zmm29,zmm28,0x7b
    vshuff64x2 zmm30,zmm29,zmmword ptr [rcx],0x7b
    vshuff64x2 zmm30,zmm29,zmmword ptr [rax+r14*8+0x123],0x7b
    vshuff64x2 zmm30,zmm29,qword ptr [rcx]{1to8},0x7b
    vshuff64x2 zmm30,zmm29,zmmword ptr [rdx+0x1fc0],0x7b
    vshuff64x2 zmm30,zmm29,zmmword ptr [rdx+0x2000],0x7b
    vshuff64x2 zmm30,zmm29,zmmword ptr [rdx-0x2000],0x7b
    vshuff64x2 zmm30,zmm29,zmmword ptr [rdx-0x2040],0x7b
    vshuff64x2 zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8},0x7b
    vshuff64x2 zmm30,zmm29,qword ptr [rdx+0x400]{1to8},0x7b
    vshuff64x2 zmm30,zmm29,qword ptr [rdx-0x400]{1to8},0x7b
    vshuff64x2 zmm30,zmm29,qword ptr [rdx-0x408]{1to8},0x7b
    vshufi32x4 zmm30,zmm29,zmm28,0xab
    vshufi32x4 zmm30{k7},zmm29,zmm28,0xab
    vshufi32x4 zmm30{k7}{z},zmm29,zmm28,0xab
    vshufi32x4 zmm30,zmm29,zmm28,0x7b
    vshufi32x4 zmm30,zmm29,zmmword ptr [rcx],0x7b
    vshufi32x4 zmm30,zmm29,zmmword ptr [rax+r14*8+0x123],0x7b
    vshufi32x4 zmm30,zmm29,dword ptr [rcx]{1to16},0x7b
    vshufi32x4 zmm30,zmm29,zmmword ptr [rdx+0x1fc0],0x7b
    vshufi32x4 zmm30,zmm29,zmmword ptr [rdx+0x2000],0x7b
    vshufi32x4 zmm30,zmm29,zmmword ptr [rdx-0x2000],0x7b
    vshufi32x4 zmm30,zmm29,zmmword ptr [rdx-0x2040],0x7b
    vshufi32x4 zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16},0x7b
    vshufi32x4 zmm30,zmm29,dword ptr [rdx+0x200]{1to16},0x7b
    vshufi32x4 zmm30,zmm29,dword ptr [rdx-0x200]{1to16},0x7b
    vshufi32x4 zmm30,zmm29,dword ptr [rdx-0x204]{1to16},0x7b
    vshufi64x2 zmm30,zmm29,zmm28,0xab
    vshufi64x2 zmm30{k7},zmm29,zmm28,0xab
    vshufi64x2 zmm30{k7}{z},zmm29,zmm28,0xab
    vshufi64x2 zmm30,zmm29,zmm28,0x7b
    vshufi64x2 zmm30,zmm29,zmmword ptr [rcx],0x7b
    vshufi64x2 zmm30,zmm29,zmmword ptr [rax+r14*8+0x123],0x7b
    vshufi64x2 zmm30,zmm29,qword ptr [rcx]{1to8},0x7b
    vshufi64x2 zmm30,zmm29,zmmword ptr [rdx+0x1fc0],0x7b
    vshufi64x2 zmm30,zmm29,zmmword ptr [rdx+0x2000],0x7b
    vshufi64x2 zmm30,zmm29,zmmword ptr [rdx-0x2000],0x7b
    vshufi64x2 zmm30,zmm29,zmmword ptr [rdx-0x2040],0x7b
    vshufi64x2 zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8},0x7b
    vshufi64x2 zmm30,zmm29,qword ptr [rdx+0x400]{1to8},0x7b
    vshufi64x2 zmm30,zmm29,qword ptr [rdx-0x400]{1to8},0x7b
    vshufi64x2 zmm30,zmm29,qword ptr [rdx-0x408]{1to8},0x7b

    valignq zmm30,zmm29,zmm28,0xab
    valignq zmm30{k7},zmm29,zmm28,0xab
    valignq zmm30{k7}{z},zmm29,zmm28,0xab
    valignq zmm30,zmm29,zmm28,0x7b
    valignq zmm30,zmm29,zmmword ptr [rcx],0x7b
    valignq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123],0x7b
    valignq zmm30,zmm29,qword ptr [rcx]{1to8},0x7b
    valignq zmm30,zmm29,zmmword ptr [rdx+0x1fc0],0x7b
    valignq zmm30,zmm29,zmmword ptr [rdx+0x2000],0x7b
    valignq zmm30,zmm29,zmmword ptr [rdx-0x2000],0x7b
    valignq zmm30,zmm29,zmmword ptr [rdx-0x2040],0x7b
    valignq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8},0x7b
    valignq zmm30,zmm29,qword ptr [rdx+0x400]{1to8},0x7b
    valignq zmm30,zmm29,qword ptr [rdx-0x400]{1to8},0x7b
    valignq zmm30,zmm29,qword ptr [rdx-0x408]{1to8},0x7b

    vcvtsd2usi eax,xmm30
    vcvtsd2usi eax,xmm30,{rn-sae}
    vcvtsd2usi eax,xmm30,{ru-sae}
    vcvtsd2usi eax,xmm30,{rd-sae}
    vcvtsd2usi eax,xmm30,{rz-sae}
    vcvtsd2usi ebp,xmm30
    vcvtsd2usi ebp,xmm30,{rn-sae}
    vcvtsd2usi ebp,xmm30,{ru-sae}
    vcvtsd2usi ebp,xmm30,{rd-sae}
    vcvtsd2usi ebp,xmm30,{rz-sae}
    vcvtsd2usi r13d,xmm30
    vcvtsd2usi r13d,xmm30,{rn-sae}
    vcvtsd2usi r13d,xmm30,{ru-sae}
    vcvtsd2usi r13d,xmm30,{rd-sae}
    vcvtsd2usi r13d,xmm30,{rz-sae}
    vcvtsd2usi rax,xmm30
    vcvtsd2usi rax,xmm30,{rn-sae}
    vcvtsd2usi rax,xmm30,{ru-sae}
    vcvtsd2usi rax,xmm30,{rd-sae}
    vcvtsd2usi rax,xmm30,{rz-sae}

    vcvtsd2usi rax,qword ptr [rcx]
    vcvtsd2usi rax,qword ptr [rax+r14*8+0x123]
    vcvtsd2usi rax,qword ptr [rdx+0x3f8]
    vcvtsd2usi rax,qword ptr [rdx+0x400]
    vcvtsd2usi rax,qword ptr [rdx-0x400]
    vcvtsd2usi rax,qword ptr [rdx-0x408]
    vcvtsd2usi r8,xmm30
    vcvtsd2usi r8,xmm30,{rn-sae}
    vcvtsd2usi r8,xmm30,{ru-sae}
    vcvtsd2usi r8,xmm30,{rd-sae}
    vcvtsd2usi r8,xmm30,{rz-sae}
    vcvtsd2usi r8,qword ptr [rcx]
    vcvtsd2usi r8,qword ptr [rax+r14*8+0x123]
    vcvtsd2usi r8,qword ptr [rdx+0x3f8]
    vcvtsd2usi r8,qword ptr [rdx+0x400]
    vcvtsd2usi r8,qword ptr [rdx-0x400]
    vcvtsd2usi r8,qword ptr [rdx-0x408]

    vcvtsd2usi eax,qword ptr [rcx]
    vcvtsd2usi eax,qword ptr [rax+r14*8+0x123]
    vcvtsd2usi eax,qword ptr [rdx+0x3f8]
    vcvtsd2usi eax,qword ptr [rdx+0x400]
    vcvtsd2usi eax,qword ptr [rdx-0x400]
    vcvtsd2usi eax,qword ptr [rdx-0x408]
    vcvtsd2usi ebp,qword ptr [rcx]
    vcvtsd2usi ebp,qword ptr [rax+r14*8+0x123]
    vcvtsd2usi ebp,qword ptr [rdx+0x3f8]
    vcvtsd2usi ebp,qword ptr [rdx+0x400]
    vcvtsd2usi ebp,qword ptr [rdx-0x400]
    vcvtsd2usi ebp,qword ptr [rdx-0x408]
    vcvtsd2usi r13d,qword ptr [rcx]
    vcvtsd2usi r13d,qword ptr [rax+r14*8+0x123]
    vcvtsd2usi r13d,qword ptr [rdx+0x3f8]
    vcvtsd2usi r13d,qword ptr [rdx+0x400]
    vcvtsd2usi r13d,qword ptr [rdx-0x400]
    vcvtsd2usi r13d,qword ptr [rdx-0x408]

    vcvtss2usi eax,xmm30
    vcvtss2usi eax,xmm30,{rn-sae}
    vcvtss2usi eax,xmm30,{ru-sae}
    vcvtss2usi eax,xmm30,{rd-sae}
    vcvtss2usi eax,xmm30,{rz-sae}
    vcvtss2usi eax,dword ptr [rcx]
    vcvtss2usi eax,dword ptr [rax+r14*8+0x123]
    vcvtss2usi eax,dword ptr [rdx+0x1fc]
    vcvtss2usi eax,dword ptr [rdx+0x200]
    vcvtss2usi eax,dword ptr [rdx-0x200]
    vcvtss2usi eax,dword ptr [rdx-0x204]

    vcvtss2usi ebp,xmm30
    vcvtss2usi ebp,xmm30,{rn-sae}
    vcvtss2usi ebp,xmm30,{ru-sae}
    vcvtss2usi ebp,xmm30,{rd-sae}
    vcvtss2usi ebp,xmm30,{rz-sae}
    vcvtss2usi ebp,dword ptr [rcx]
    vcvtss2usi ebp,dword ptr [rax+r14*8+0x123]
    vcvtss2usi ebp,dword ptr [rdx+0x1fc]
    vcvtss2usi ebp,dword ptr [rdx+0x200]
    vcvtss2usi ebp,dword ptr [rdx-0x200]
    vcvtss2usi ebp,dword ptr [rdx-0x204]
    vcvtss2usi r13d,xmm30
    vcvtss2usi r13d,xmm30,{rn-sae}
    vcvtss2usi r13d,xmm30,{ru-sae}
    vcvtss2usi r13d,xmm30,{rd-sae}
    vcvtss2usi r13d,xmm30,{rz-sae}
    vcvtss2usi r13d,dword ptr [rcx]
    vcvtss2usi r13d,dword ptr [rax+r14*8+0x123]
    vcvtss2usi r13d,dword ptr [rdx+0x1fc]
    vcvtss2usi r13d,dword ptr [rdx+0x200]
    vcvtss2usi r13d,dword ptr [rdx-0x200]
    vcvtss2usi r13d,dword ptr [rdx-0x204]
    vcvtss2usi rax,xmm30
    vcvtss2usi rax,xmm30,{rn-sae}
    vcvtss2usi rax,xmm30,{ru-sae}
    vcvtss2usi rax,xmm30,{rd-sae}
    vcvtss2usi rax,xmm30,{rz-sae}
    vcvtss2usi r8,xmm30
    vcvtss2usi r8,xmm30,{rn-sae}
    vcvtss2usi r8,xmm30,{ru-sae}
    vcvtss2usi r8,xmm30,{rd-sae}
    vcvtss2usi r8,xmm30,{rz-sae}

    vcvtss2usi rax,dword ptr [rcx]
    vcvtss2usi rax,dword ptr [rax+r14*8+0x123]
    vcvtss2usi rax,dword ptr [rdx+0x1fc]
    vcvtss2usi rax,dword ptr [rdx+0x200]
    vcvtss2usi rax,dword ptr [rdx-0x200]
    vcvtss2usi rax,dword ptr [rdx-0x204]
    vcvtss2usi r8,dword ptr [rcx]
    vcvtss2usi r8,dword ptr [rax+r14*8+0x123]
    vcvtss2usi r8,dword ptr [rdx+0x1fc]
    vcvtss2usi r8,dword ptr [rdx+0x200]
    vcvtss2usi r8,dword ptr [rdx-0x200]
    vcvtss2usi r8,dword ptr [rdx-0x204]

    vcvtusi2sd xmm30,xmm29,eax
    vcvtusi2sd xmm30,xmm29,ebp
    vcvtusi2sd xmm30,xmm29,r13d
    vcvtusi2sd xmm30,xmm29,dword ptr [rcx]
    vcvtusi2sd xmm30,xmm29,dword ptr [rax+r14*8+0x123]
    vcvtusi2sd xmm30,xmm29,dword ptr [rdx+0x1fc]
    vcvtusi2sd xmm30,xmm29,dword ptr [rdx+0x200]
    vcvtusi2sd xmm30,xmm29,dword ptr [rdx-0x200]
    vcvtusi2sd xmm30,xmm29,dword ptr [rdx-0x204]
    vcvtusi2sd xmm30,xmm29,rax
    vcvtusi2sd xmm30,xmm29,{rn-sae},rax
    vcvtusi2sd xmm30,xmm29,{ru-sae},rax
    vcvtusi2sd xmm30,xmm29,{rd-sae},rax
    vcvtusi2sd xmm30,xmm29,{rz-sae},rax
    vcvtusi2sd xmm30,xmm29,r8
    vcvtusi2sd xmm30,xmm29,{rn-sae},r8
    vcvtusi2sd xmm30,xmm29,{ru-sae},r8
    vcvtusi2sd xmm30,xmm29,{rd-sae},r8
    vcvtusi2sd xmm30,xmm29,{rz-sae},r8
    vcvtusi2sd xmm30,xmm29,qword ptr [rcx]
    vcvtusi2sd xmm30,xmm29,qword ptr [rax+r14*8+0x123]
    vcvtusi2sd xmm30,xmm29,qword ptr [rdx+0x3f8]
    vcvtusi2sd xmm30,xmm29,qword ptr [rdx+0x400]
    vcvtusi2sd xmm30,xmm29,qword ptr [rdx-0x400]
    vcvtusi2sd xmm30,xmm29,qword ptr [rdx-0x408]

    vcvtusi2ss xmm30,xmm29,eax
    vcvtusi2ss xmm30,xmm29,{rn-sae},eax
    vcvtusi2ss xmm30,xmm29,{ru-sae},eax
    vcvtusi2ss xmm30,xmm29,{rd-sae},eax
    vcvtusi2ss xmm30,xmm29,{rz-sae},eax
    vcvtusi2ss xmm30,xmm29,ebp
    vcvtusi2ss xmm30,xmm29,{rn-sae},ebp
    vcvtusi2ss xmm30,xmm29,{ru-sae},ebp
    vcvtusi2ss xmm30,xmm29,{rd-sae},ebp
    vcvtusi2ss xmm30,xmm29,{rz-sae},ebp
    vcvtusi2ss xmm30,xmm29,r13d
    vcvtusi2ss xmm30,xmm29,{rn-sae},r13d
    vcvtusi2ss xmm30,xmm29,{ru-sae},r13d
    vcvtusi2ss xmm30,xmm29,{rd-sae},r13d
    vcvtusi2ss xmm30,xmm29,{rz-sae},r13d
    vcvtusi2ss xmm30,xmm29,dword ptr [rcx]
    vcvtusi2ss xmm30,xmm29,dword ptr [rax+r14*8+0x123]
    vcvtusi2ss xmm30,xmm29,dword ptr [rdx+0x1fc]
    vcvtusi2ss xmm30,xmm29,dword ptr [rdx+0x200]
    vcvtusi2ss xmm30,xmm29,dword ptr [rdx-0x200]
    vcvtusi2ss xmm30,xmm29,dword ptr [rdx-0x204]
    vcvtusi2ss xmm30,xmm29,rax
    vcvtusi2ss xmm30,xmm29,{rn-sae},rax
    vcvtusi2ss xmm30,xmm29,{ru-sae},rax
    vcvtusi2ss xmm30,xmm29,{rd-sae},rax
    vcvtusi2ss xmm30,xmm29,{rz-sae},rax
    vcvtusi2ss xmm30,xmm29,r8
    vcvtusi2ss xmm30,xmm29,{rn-sae},r8
    vcvtusi2ss xmm30,xmm29,{ru-sae},r8
    vcvtusi2ss xmm30,xmm29,{rd-sae},r8
    vcvtusi2ss xmm30,xmm29,{rz-sae},r8
    vcvtusi2ss xmm30,xmm29,qword ptr [rcx]
    vcvtusi2ss xmm30,xmm29,qword ptr [rax+r14*8+0x123]
    vcvtusi2ss xmm30,xmm29,qword ptr [rdx+0x3f8]
    vcvtusi2ss xmm30,xmm29,qword ptr [rdx+0x400]
    vcvtusi2ss xmm30,xmm29,qword ptr [rdx-0x400]
    vcvtusi2ss xmm30,xmm29,qword ptr [rdx-0x408]

    vscalefpd zmm30,zmm29,zmm28
    vscalefpd zmm30{k7},zmm29,zmm28
    vscalefpd zmm30{k7}{z},zmm29,zmm28
    vscalefpd zmm30,zmm29,zmm28,{rn-sae}
    vscalefpd zmm30,zmm29,zmm28,{ru-sae}
    vscalefpd zmm30,zmm29,zmm28,{rd-sae}
    vscalefpd zmm30,zmm29,zmm28,{rz-sae}
    vscalefpd zmm30,zmm29,zmmword ptr [rcx]
    vscalefpd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vscalefpd zmm30,zmm29,qword ptr [rcx]{1to8}
    vscalefpd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vscalefpd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vscalefpd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vscalefpd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vscalefpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vscalefpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vscalefpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vscalefpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vscalefps zmm30,zmm29,zmm28
    vscalefps zmm30{k7},zmm29,zmm28
    vscalefps zmm30{k7}{z},zmm29,zmm28
    vscalefps zmm30,zmm29,zmm28,{rn-sae}
    vscalefps zmm30,zmm29,zmm28,{ru-sae}
    vscalefps zmm30,zmm29,zmm28,{rd-sae}
    vscalefps zmm30,zmm29,zmm28,{rz-sae}
    vscalefps zmm30,zmm29,zmmword ptr [rcx]
    vscalefps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vscalefps zmm30,zmm29,dword ptr [rcx]{1to16}
    vscalefps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vscalefps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vscalefps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vscalefps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vscalefps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vscalefps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vscalefps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vscalefps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vscalefsd xmm30{k7},xmm29,xmm28
    vscalefsd xmm30{k7}{z},xmm29,xmm28
    vscalefsd xmm30{k7},xmm29,xmm28,{rn-sae}
    vscalefsd xmm30{k7},xmm29,xmm28,{ru-sae}
    vscalefsd xmm30{k7},xmm29,xmm28,{rd-sae}
    vscalefsd xmm30{k7},xmm29,xmm28,{rz-sae}
    vscalefsd xmm30{k7},xmm29,qword ptr [rcx]
    vscalefsd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123]
    vscalefsd xmm30{k7},xmm29,qword ptr [rdx+0x3f8]
    vscalefsd xmm30{k7},xmm29,qword ptr [rdx+0x400]
    vscalefsd xmm30{k7},xmm29,qword ptr [rdx-0x400]
    vscalefsd xmm30{k7},xmm29,qword ptr [rdx-0x408]

    vscalefss xmm30{k7},xmm29,xmm28
    vscalefss xmm30{k7}{z},xmm29,xmm28
    vscalefss xmm30{k7},xmm29,xmm28,{rn-sae}
    vscalefss xmm30{k7},xmm29,xmm28,{ru-sae}
    vscalefss xmm30{k7},xmm29,xmm28,{rd-sae}
    vscalefss xmm30{k7},xmm29,xmm28,{rz-sae}
    vscalefss xmm30{k7},xmm29,dword ptr [rcx]
    vscalefss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123]
    vscalefss xmm30{k7},xmm29,dword ptr [rdx+0x1fc]
    vscalefss xmm30{k7},xmm29,dword ptr [rdx+0x200]
    vscalefss xmm30{k7},xmm29,dword ptr [rdx-0x200]
    vscalefss xmm30{k7},xmm29,dword ptr [rdx-0x204]

    vfixupimmps zmm30,zmm29,zmm28,0xab
    vfixupimmps zmm30{k7},zmm29,zmm28,0xab
    vfixupimmps zmm30{k7}{z},zmm29,zmm28,0xab
    vfixupimmps zmm30,zmm29,zmm28,{sae},0xab
    vfixupimmps zmm30,zmm29,zmm28,0x7b
    vfixupimmps zmm30,zmm29,zmm28,{sae},0x7b
    vfixupimmps zmm30,zmm29,zmmword ptr [rcx],0x7b
    vfixupimmps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123],0x7b
    vfixupimmps zmm30,zmm29,dword ptr [rcx]{1to16},0x7b
    vfixupimmps zmm30,zmm29,zmmword ptr [rdx+0x1fc0],0x7b
    vfixupimmps zmm30,zmm29,zmmword ptr [rdx+0x2000],0x7b
    vfixupimmps zmm30,zmm29,zmmword ptr [rdx-0x2000],0x7b
    vfixupimmps zmm30,zmm29,zmmword ptr [rdx-0x2040],0x7b
    vfixupimmps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16},0x7b
    vfixupimmps zmm30,zmm29,dword ptr [rdx+0x200]{1to16},0x7b
    vfixupimmps zmm30,zmm29,dword ptr [rdx-0x200]{1to16},0x7b
    vfixupimmps zmm30,zmm29,dword ptr [rdx-0x204]{1to16},0x7b
    vfixupimmpd zmm30,zmm29,zmm28,0xab
    vfixupimmpd zmm30{k7},zmm29,zmm28,0xab
    vfixupimmpd zmm30{k7}{z},zmm29,zmm28,0xab
    vfixupimmpd zmm30,zmm29,zmm28,{sae},0xab
    vfixupimmpd zmm30,zmm29,zmm28,0x7b
    vfixupimmpd zmm30,zmm29,zmm28,{sae},0x7b
    vfixupimmpd zmm30,zmm29,zmmword ptr [rcx],0x7b
    vfixupimmpd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123],0x7b
    vfixupimmpd zmm30,zmm29,qword ptr [rcx]{1to8},0x7b
    vfixupimmpd zmm30,zmm29,zmmword ptr [rdx+0x1fc0],0x7b
    vfixupimmpd zmm30,zmm29,zmmword ptr [rdx+0x2000],0x7b
    vfixupimmpd zmm30,zmm29,zmmword ptr [rdx-0x2000],0x7b
    vfixupimmpd zmm30,zmm29,zmmword ptr [rdx-0x2040],0x7b
    vfixupimmpd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8},0x7b
    vfixupimmpd zmm30,zmm29,qword ptr [rdx+0x400]{1to8},0x7b
    vfixupimmpd zmm30,zmm29,qword ptr [rdx-0x400]{1to8},0x7b
    vfixupimmpd zmm30,zmm29,qword ptr [rdx-0x408]{1to8},0x7b
    vfixupimmss xmm30{k7},xmm29,xmm28,0xab
    vfixupimmss xmm30{k7}{z},xmm29,xmm28,0xab
    vfixupimmss xmm30{k7},xmm29,xmm28,{sae},0xab
    vfixupimmss xmm30{k7},xmm29,xmm28,0x7b
    vfixupimmss xmm30{k7},xmm29,xmm28,{sae},0x7b
    vfixupimmss xmm30{k7},xmm29,dword ptr [rcx],0x7b
    vfixupimmss xmm30{k7},xmm29,dword ptr [rax+r14*8+0x123],0x7b
    vfixupimmss xmm30{k7},xmm29,dword ptr [rdx+0x1fc],0x7b
    vfixupimmss xmm30{k7},xmm29,dword ptr [rdx+0x200],0x7b
    vfixupimmss xmm30{k7},xmm29,dword ptr [rdx-0x200],0x7b
    vfixupimmss xmm30{k7},xmm29,dword ptr [rdx-0x204],0x7b
    vfixupimmsd xmm30{k7},xmm29,xmm28,0xab
    vfixupimmsd xmm30{k7}{z},xmm29,xmm28,0xab
    vfixupimmsd xmm30{k7},xmm29,xmm28,{sae},0xab
    vfixupimmsd xmm30{k7},xmm29,xmm28,0x7b
    vfixupimmsd xmm30{k7},xmm29,xmm28,{sae},0x7b
    vfixupimmsd xmm30{k7},xmm29,qword ptr [rcx],0x7b
    vfixupimmsd xmm30{k7},xmm29,qword ptr [rax+r14*8+0x123],0x7b
    vfixupimmsd xmm30{k7},xmm29,qword ptr [rdx+0x3f8],0x7b
    vfixupimmsd xmm30{k7},xmm29,qword ptr [rdx+0x400],0x7b
    vfixupimmsd xmm30{k7},xmm29,qword ptr [rdx-0x400],0x7b
    vfixupimmsd xmm30{k7},xmm29,qword ptr [rdx-0x408],0x7b

    vprolvd zmm30,zmm29,zmm28
    vprolvd zmm30{k7},zmm29,zmm28
    vprolvd zmm30{k7}{z},zmm29,zmm28
    vprolvd zmm30,zmm29,zmmword ptr [rcx]
    vprolvd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vprolvd zmm30,zmm29,dword ptr [rcx]{1to16}
    vprolvd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vprolvd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vprolvd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vprolvd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vprolvd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vprolvd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vprolvd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vprolvd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vprold zmm30,zmm29,0xab
    vprold zmm30{k7},zmm29,0xab
    vprold zmm30{k7}{z},zmm29,0xab
    vprold zmm30,zmm29,0x7b
    vprold zmm30,zmmword ptr [rcx],0x7b
    vprold zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vprold zmm30,dword ptr [rcx]{1to16},0x7b
    vprold zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vprold zmm30,zmmword ptr [rdx+0x2000],0x7b
    vprold zmm30,zmmword ptr [rdx-0x2000],0x7b
    vprold zmm30,zmmword ptr [rdx-0x2040],0x7b
    vprold zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vprold zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vprold zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vprold zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vprolvq zmm30,zmm29,zmm28
    vprolvq zmm30{k7},zmm29,zmm28
    vprolvq zmm30{k7}{z},zmm29,zmm28
    vprolvq zmm30,zmm29,zmmword ptr [rcx]
    vprolvq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vprolvq zmm30,zmm29,qword ptr [rcx]{1to8}
    vprolvq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vprolvq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vprolvq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vprolvq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vprolvq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vprolvq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vprolvq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vprolvq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vprolq zmm30,zmm29,0xab
    vprolq zmm30{k7},zmm29,0xab
    vprolq zmm30{k7}{z},zmm29,0xab
    vprolq zmm30,zmm29,0x7b
    vprolq zmm30,zmmword ptr [rcx],0x7b
    vprolq zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vprolq zmm30,qword ptr [rcx]{1to8},0x7b
    vprolq zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vprolq zmm30,zmmword ptr [rdx+0x2000],0x7b
    vprolq zmm30,zmmword ptr [rdx-0x2000],0x7b
    vprolq zmm30,zmmword ptr [rdx-0x2040],0x7b
    vprolq zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vprolq zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vprolq zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vprolq zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vprorvd zmm30,zmm29,zmm28
    vprorvd zmm30{k7},zmm29,zmm28
    vprorvd zmm30{k7}{z},zmm29,zmm28
    vprorvd zmm30,zmm29,zmmword ptr [rcx]
    vprorvd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vprorvd zmm30,zmm29,dword ptr [rcx]{1to16}
    vprorvd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vprorvd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vprorvd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vprorvd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vprorvd zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vprorvd zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vprorvd zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vprorvd zmm30,zmm29,dword ptr [rdx-0x204]{1to16}

    vprord zmm30,zmm29,0xab
    vprord zmm30{k7},zmm29,0xab
    vprord zmm30{k7}{z},zmm29,0xab
    vprord zmm30,zmm29,0x7b
    vprord zmm30,zmmword ptr [rcx],0x7b
    vprord zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vprord zmm30,dword ptr [rcx]{1to16},0x7b
    vprord zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vprord zmm30,zmmword ptr [rdx+0x2000],0x7b
    vprord zmm30,zmmword ptr [rdx-0x2000],0x7b
    vprord zmm30,zmmword ptr [rdx-0x2040],0x7b
    vprord zmm30,dword ptr [rdx+0x1fc]{1to16},0x7b
    vprord zmm30,dword ptr [rdx+0x200]{1to16},0x7b
    vprord zmm30,dword ptr [rdx-0x200]{1to16},0x7b
    vprord zmm30,dword ptr [rdx-0x204]{1to16},0x7b

    vprorvq zmm30,zmm29,zmm28
    vprorvq zmm30{k7},zmm29,zmm28
    vprorvq zmm30{k7}{z},zmm29,zmm28
    vprorvq zmm30,zmm29,zmmword ptr [rcx]
    vprorvq zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vprorvq zmm30,zmm29,qword ptr [rcx]{1to8}
    vprorvq zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vprorvq zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vprorvq zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vprorvq zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vprorvq zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vprorvq zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vprorvq zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vprorvq zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vprorq zmm30,zmm29,0xab
    vprorq zmm30{k7},zmm29,0xab
    vprorq zmm30{k7}{z},zmm29,0xab
    vprorq zmm30,zmm29,0x7b
    vprorq zmm30,zmmword ptr [rcx],0x7b
    vprorq zmm30,zmmword ptr [rax+r14*8+0x123],0x7b
    vprorq zmm30,qword ptr [rcx]{1to8},0x7b
    vprorq zmm30,zmmword ptr [rdx+0x1fc0],0x7b
    vprorq zmm30,zmmword ptr [rdx+0x2000],0x7b
    vprorq zmm30,zmmword ptr [rdx-0x2000],0x7b
    vprorq zmm30,zmmword ptr [rdx-0x2040],0x7b
    vprorq zmm30,qword ptr [rdx+0x3f8]{1to8},0x7b
    vprorq zmm30,qword ptr [rdx+0x400]{1to8},0x7b
    vprorq zmm30,qword ptr [rdx-0x400]{1to8},0x7b
    vprorq zmm30,qword ptr [rdx-0x408]{1to8},0x7b

    vcvttsd2usi eax,xmm30
    vcvttsd2usi eax,xmm30,{sae}
    vcvttsd2usi eax,qword ptr [rcx]
    vcvttsd2usi eax,qword ptr [rax+r14*8+0x123]
    vcvttsd2usi eax,qword ptr [rdx+0x3f8]
    vcvttsd2usi eax,qword ptr [rdx+0x400]
    vcvttsd2usi eax,qword ptr [rdx-0x400]
    vcvttsd2usi eax,qword ptr [rdx-0x408]
    vcvttsd2usi ebp,xmm30
    vcvttsd2usi ebp,xmm30,{sae}
    vcvttsd2usi ebp,qword ptr [rcx]
    vcvttsd2usi ebp,qword ptr [rax+r14*8+0x123]
    vcvttsd2usi ebp,qword ptr [rdx+0x3f8]
    vcvttsd2usi ebp,qword ptr [rdx+0x400]
    vcvttsd2usi ebp,qword ptr [rdx-0x400]
    vcvttsd2usi ebp,qword ptr [rdx-0x408]
    vcvttsd2usi r13d,xmm30
    vcvttsd2usi r13d,xmm30,{sae}
    vcvttsd2usi r13d,qword ptr [rcx]
    vcvttsd2usi r13d,qword ptr [rax+r14*8+0x123]
    vcvttsd2usi r13d,qword ptr [rdx+0x3f8]
    vcvttsd2usi r13d,qword ptr [rdx+0x400]
    vcvttsd2usi r13d,qword ptr [rdx-0x400]
    vcvttsd2usi r13d,qword ptr [rdx-0x408]
    vcvttsd2usi rax,xmm30
    vcvttsd2usi rax,xmm30,{sae}
    vcvttsd2usi rax,qword ptr [rcx]
    vcvttsd2usi rax,qword ptr [rax+r14*8+0x123]
    vcvttsd2usi rax,qword ptr [rdx+0x3f8]
    vcvttsd2usi rax,qword ptr [rdx+0x400]
    vcvttsd2usi rax,qword ptr [rdx-0x400]
    vcvttsd2usi rax,qword ptr [rdx-0x408]
    vcvttsd2usi r8,xmm30
    vcvttsd2usi r8,xmm30,{sae}
    vcvttsd2usi r8,qword ptr [rcx]
    vcvttsd2usi r8,qword ptr [rax+r14*8+0x123]
    vcvttsd2usi r8,qword ptr [rdx+0x3f8]
    vcvttsd2usi r8,qword ptr [rdx+0x400]
    vcvttsd2usi r8,qword ptr [rdx-0x400]
    vcvttsd2usi r8,qword ptr [rdx-0x408]
    vcvttss2usi eax,xmm30
    vcvttss2usi eax,xmm30,{sae}
    vcvttss2usi eax,dword ptr [rcx]
    vcvttss2usi eax,dword ptr [rax+r14*8+0x123]
    vcvttss2usi eax,dword ptr [rdx+0x1fc]
    vcvttss2usi eax,dword ptr [rdx+0x200]
    vcvttss2usi eax,dword ptr [rdx-0x200]
    vcvttss2usi eax,dword ptr [rdx-0x204]
    vcvttss2usi ebp,xmm30
    vcvttss2usi ebp,xmm30,{sae}
    vcvttss2usi ebp,dword ptr [rcx]
    vcvttss2usi ebp,dword ptr [rax+r14*8+0x123]
    vcvttss2usi ebp,dword ptr [rdx+0x1fc]
    vcvttss2usi ebp,dword ptr [rdx+0x200]
    vcvttss2usi ebp,dword ptr [rdx-0x200]
    vcvttss2usi ebp,dword ptr [rdx-0x204]
    vcvttss2usi r13d,xmm30
    vcvttss2usi r13d,xmm30,{sae}
    vcvttss2usi r13d,dword ptr [rcx]
    vcvttss2usi r13d,dword ptr [rax+r14*8+0x123]
    vcvttss2usi r13d,dword ptr [rdx+0x1fc]
    vcvttss2usi r13d,dword ptr [rdx+0x200]
    vcvttss2usi r13d,dword ptr [rdx-0x200]
    vcvttss2usi r13d,dword ptr [rdx-0x204]
    vcvttss2usi rax,xmm30
    vcvttss2usi rax,xmm30,{sae}
    vcvttss2usi rax,dword ptr [rcx]
    vcvttss2usi rax,dword ptr [rax+r14*8+0x123]
    vcvttss2usi rax,dword ptr [rdx+0x1fc]
    vcvttss2usi rax,dword ptr [rdx+0x200]
    vcvttss2usi rax,dword ptr [rdx-0x200]
    vcvttss2usi rax,dword ptr [rdx-0x204]
    vcvttss2usi r8,xmm30
    vcvttss2usi r8,xmm30,{sae}
    vcvttss2usi r8,dword ptr [rcx]
    vcvttss2usi r8,dword ptr [rax+r14*8+0x123]
    vcvttss2usi r8,dword ptr [rdx+0x1fc]
    vcvttss2usi r8,dword ptr [rdx+0x200]
    vcvttss2usi r8,dword ptr [rdx-0x200]
    vcvttss2usi r8,dword ptr [rdx-0x204]

    vpermi2d zmm30,zmm29,zmm28
    vpermi2d zmm30{k7},zmm29,zmm28
    vpermi2d zmm30{k7}{z},zmm29,zmm28
    vpermi2d zmm30,zmm29,zmmword ptr [rcx]
    vpermi2d zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpermi2d zmm30,zmm29,dword ptr [rcx]{1to16}
    vpermi2d zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpermi2d zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpermi2d zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpermi2d zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpermi2d zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpermi2d zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpermi2d zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpermi2d zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vpermi2q zmm30,zmm29,zmm28
    vpermi2q zmm30{k7},zmm29,zmm28
    vpermi2q zmm30{k7}{z},zmm29,zmm28
    vpermi2q zmm30,zmm29,zmmword ptr [rcx]
    vpermi2q zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpermi2q zmm30,zmm29,qword ptr [rcx]{1to8}
    vpermi2q zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpermi2q zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpermi2q zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpermi2q zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpermi2q zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpermi2q zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpermi2q zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpermi2q zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    vpermi2ps zmm30,zmm29,zmm28
    vpermi2ps zmm30{k7},zmm29,zmm28
    vpermi2ps zmm30{k7}{z},zmm29,zmm28
    vpermi2ps zmm30,zmm29,zmmword ptr [rcx]
    vpermi2ps zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpermi2ps zmm30,zmm29,dword ptr [rcx]{1to16}
    vpermi2ps zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpermi2ps zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpermi2ps zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpermi2ps zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpermi2ps zmm30,zmm29,dword ptr [rdx+0x1fc]{1to16}
    vpermi2ps zmm30,zmm29,dword ptr [rdx+0x200]{1to16}
    vpermi2ps zmm30,zmm29,dword ptr [rdx-0x200]{1to16}
    vpermi2ps zmm30,zmm29,dword ptr [rdx-0x204]{1to16}
    vpermi2pd zmm30,zmm29,zmm28
    vpermi2pd zmm30{k7},zmm29,zmm28
    vpermi2pd zmm30{k7}{z},zmm29,zmm28
    vpermi2pd zmm30,zmm29,zmmword ptr [rcx]
    vpermi2pd zmm30,zmm29,zmmword ptr [rax+r14*8+0x123]
    vpermi2pd zmm30,zmm29,qword ptr [rcx]{1to8}
    vpermi2pd zmm30,zmm29,zmmword ptr [rdx+0x1fc0]
    vpermi2pd zmm30,zmm29,zmmword ptr [rdx+0x2000]
    vpermi2pd zmm30,zmm29,zmmword ptr [rdx-0x2000]
    vpermi2pd zmm30,zmm29,zmmword ptr [rdx-0x2040]
    vpermi2pd zmm30,zmm29,qword ptr [rdx+0x3f8]{1to8}
    vpermi2pd zmm30,zmm29,qword ptr [rdx+0x400]{1to8}
    vpermi2pd zmm30,zmm29,qword ptr [rdx-0x400]{1to8}
    vpermi2pd zmm30,zmm29,qword ptr [rdx-0x408]{1to8}

    end