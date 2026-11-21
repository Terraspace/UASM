; Unmasked signed byte-to-qword extension; masked forms as controls.
.x64
option evex:1
_TEXT SEGMENT USE64
vpmovsxbq zmm0,xmm1
vpmovsxbq zmm30,xmm29
vpmovsxbq zmm0,qword ptr [rax]
vpmovsxbq zmm15,qword ptr [rcx+rdx*4]
vpmovsxbq zmm0{k1},xmm1
vpmovsxbq zmm0{k1}{z},xmm1
_TEXT ENDS
END
