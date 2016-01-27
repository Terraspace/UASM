
;--- AVX, 32-bit

	.686
	.model flat
	.xmm

	.data

m08  label byte
m16  label word
m32  label dword
m64  label mmword
m128 label xmmword
m256 label ymmword

	.code

	vldmxcsr eax
	vstmxcsr xmm0
	vcmppd xmm0, xmm1, xmm2
	vcmppd ymm0, ymm1, ymm2
	vcmppd ymm0, ymm1
	vpsrlw  xmm0, xmm1, ymm2
	vpsrld  xmm0, xmm1, ymm2
	vpsrld  xmm0, xmm1, m64
	vmovd  xmm0, ax
	vmovd  ymm0, m64
	vmovd  m16,  xmm0
	vmovq  xmm0, m128
	vmovq  m64,  xmm0, xmm1
	vpslldq xmm0, 1
	vpsllq  xmm0, xmm1, xmm2
	vpsrlw  xmm0, xmm1, m64
	vpabsb xmm0, xmm1, xmm2
	vpabsb xmm0, xmm1, m128
	vpmovsxbw xmm0, xmm1, xmm2
	vpmovsxbw xmm0, xmm1, m64
	vphminposuw xmm0, xmm1, xmm2
	vphminposuw xmm0, m64
	vextractps eax, xmm1, xmm2
	vextractps m32, xmm1, xmm2
	vinsertps xmm0, xmm1, xmm3
	vhaddpd xmm0, xmm1
	vlddqu xmm0, xmm1, m128
	vlddqu ymm0, m64
	vmaskmovdqu xmm0, xmm1, xmm2
	vpmovmskb eax, xmm1, xmm2
	vcvtdq2pd xmm0, xmm1, xmm2
	vcvtdq2pd xmm0, m128
	vcvtdq2pd ymm0, xmm1, xmm2
	vcvtdq2pd ymm0, m256
	vcvtpd2dq xmm0, xmm1, xmm2
	vcvtps2pd xmm0, xmm1, xmm2
	vcvtsd2si eax, ymm1, ymm2
	vcvttsd2si eax, ymm1, ymm2
	vcvtsd2ss xmm0, xmm1, xmm2
	vcvtsi2sd xmm0, xmm1, m32
	vcvtsi2ss xmm0, xmm1, eax
	vcvtss2sd xmm0, xmm1, xmm2
	vcvtss2si eax, xmm1
	vcvttss2si eax, xmm1
	vmovapd xmm0, xmm1, xmm2
	vmovapd ymm0, ymm1, m256
	vmovaps xmm0, xmm1
	vmovaps ymm0, m256
	vmovupd xmm0, xmm1
	vmovupd ymm0, m256
	vmovups ymm0, m256
	vmovups m256, ymm1
	vmovhlps xmm0, xmm1, xmm2
	vmovlhps xmm0, xmm1, xmm2
	vmovhpd xmm0, xmm1
	vmovhpd m64, xmm1, xmm2
	vmovhps xmm0, xmm1, xmm2
	vmovhps m64, xmm1
	vmovlpd xmm0, xmm1, xmm2
	vmovlpd m64, xmm1, xmm2
	vmovlps m64, xmm1, xmm2
	vpextrb xmm0, xmm1, xmm2
	vpextrb m64, xmm1, 1
	vpinsrb xmm0, xmm1, eax
	vpinsrw xmm0, xmm1, eax
	vpinsrw xmm0, xmm1, xmm2

end
