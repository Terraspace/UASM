
;--- AVX, 64-bit

ifdef __JWASM__
if type near eq 0ff02h
	.x64
	.model flat, fastcall
endif
endif

	.data

m08  label byte
m16  label word
m32  label dword
m64  label mmword
m128 label xmmword
m256 label ymmword

	.code

if 1
	movd xmm0, eax
	movd xmm0, rax
	movd xmm0, m32
	movd xmm0, m64
	movd eax,  xmm0
	movd rax,  xmm0
	movd m32,  xmm0
	movd m64,  xmm0
	vmovd  xmm0, eax
	vmovd  xmm0, rax
	vmovd  xmm0, m32
	vmovd  xmm0, m64
	vmovd  eax,  xmm0
	vmovd  rax,  xmm0
	vmovd  m32,  xmm0
	vmovd  m64,  xmm0

	movq  xmm0, m64
	movq  m64,  xmm0
	vmovq  xmm0, m64
	vmovq  m64,  xmm0
endif
if 1
	vpextrb eax, xmm1, 1
	vpextrb m08, xmm1, 1
	vpextrw eax, xmm1, 2
	vpextrw m16, xmm1, 2
	vpextrd eax, xmm1, 3
	vpextrd m32, xmm1, 3
	vpextrq rax, xmm1, 4
	vpextrq m64, xmm1, 4

	vpinsrb xmm0, xmm1, eax, 1
	vpinsrb xmm0, xmm1, m08, 1
	vpinsrw xmm0, xmm1, eax, 2
	vpinsrw xmm0, xmm1, m16, 2
	vpinsrd xmm0, xmm1, eax, 3
	vpinsrd xmm0, xmm1, m32, 3
	vpinsrq xmm0, xmm1, rax, 4
	vpinsrq xmm0, xmm1, m64, 4
endif

	vcvtsd2si eax, xmm1
	vcvtsd2si rax, xmm1
	vcvtsd2si eax, m64
	vcvtsd2si rax, m64

	vcvttsd2si eax, xmm1
	vcvttsd2si eax, m64
	vcvttsd2si rax, m64

	vcvtss2si eax, xmm1
	vcvtss2si rax, xmm1
	vcvtss2si eax, m32
	vcvtss2si rax, m32

	vcvttss2si eax, xmm1
	vcvttss2si rax, xmm1
	vcvttss2si eax, m32
	vcvttss2si rax, m32

	vpmovmskb eax, xmm1
	vpmovmskb rax, xmm1
;	vmovapd ymm0, ymm1

end
