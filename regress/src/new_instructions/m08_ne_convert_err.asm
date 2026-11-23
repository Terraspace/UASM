; Invalid widths/memory forms/decorators.
.x64
.model flat
option evex:1
.code
vbcstnebf162ps xmm1, xmm2
vbcstnesh2ps ymm1, dword ptr [rax]
vcvtneebf162ps xmm1, xmm2
vcvtneeph2ps ymm1, xmmword ptr [rax]
vcvtneobf162ps zmm1, [rax]
vcvtneoph2ps xmm17, [rax]
vbcstnebf162ps xmm1{k1}, [rax]
vcvtneeph2ps xmm1, word ptr [rax]
{evex} vcvtneebf162ps xmm1, [rax]
end
