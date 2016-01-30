
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
if 1
;--- new AVX instructions
	vbroadcastss xmm0, m32
	vbroadcastss ymm0, m32
	vbroadcastsd ymm0, m64
	vbroadcastf128 ymm0, m128

	vinsertf128 ymm0, ymm1, xmm1, 1
	vinsertf128 ymm0, ymm1, m128, 2
	vextractf128 xmm0, ymm0, 1
	vextractf128 m128, ymm0, 2

	vmaskmovps xmm0, xmm1, m128
	vmaskmovps ymm0, ymm1, m256
	vmaskmovps m128, xmm0, xmm1
	vmaskmovps m256, ymm0, ymm1

	vmaskmovpd xmm0, xmm1, m128
	vmaskmovpd ymm0, ymm1, m256
	vmaskmovpd m128, xmm0, xmm1
	vmaskmovpd m256, ymm0, ymm1

	vpermilpd xmm0, xmm1, xmm2
	vpermilpd xmm0, xmm1, m128
	vpermilpd xmm0, xmm1, 1
	vpermilpd ymm0, ymm1, ymm2
	vpermilpd ymm0, ymm1, m256
	vpermilpd ymm0, ymm1, 1

	vpermilps xmm0, xmm1, xmm2
	vpermilps xmm0, xmm1, m128
	vpermilps xmm0, xmm1, 1
	vpermilps ymm0, ymm1, ymm2
	vpermilps ymm0, ymm1, m256
	vpermilps ymm0, ymm1, 1

	vperm2f128 ymm0, ymm1, ymm2, 1
	vperm2f128 ymm0, ymm1, m256, 1

	vtestps xmm0, xmm1
	vtestps xmm0, m128
	vtestps ymm0, ymm1
	vtestps ymm0, m256

	vtestpd xmm0, xmm1
	vtestpd xmm0, m128
	vtestpd ymm0, ymm1
	vtestpd ymm0, m256

	vzeroall
	vzeroupper

endif
if 1
;--- ADD, DIV, MAX, MIN, MUL, SQRT, SUB
	addpd xmm0, xmm1
	addpd xmm0, m128

	vaddpd xmm0, xmm1, xmm2
	vaddpd xmm0, xmm1, m128
	vaddpd ymm0, ymm1, ymm2
	vaddpd ymm0, ymm1, m256

	vaddps xmm0, xmm1, xmm2
	vaddps xmm0, xmm1, m128
	vaddps ymm0, ymm1, ymm2
	vaddps ymm0, ymm1, m256

	vaddsd xmm0, xmm1, xmm2
	vaddsd xmm0, xmm1, m64
	vaddss xmm0, xmm1, xmm2
	vaddss xmm0, xmm1, m32

	divpd xmm0, xmm1
	divpd xmm0, m128
	vdivpd xmm0, xmm1, xmm2
	vdivpd xmm0, xmm1, m128
	vdivpd ymm0, ymm1, ymm2
	vdivpd ymm0, ymm1, m256

	vdivps xmm0, xmm1, xmm2
	vdivps xmm0, xmm1, m128
	vdivps ymm0, ymm1, ymm2
	vdivps ymm0, ymm1, m256

	vdivsd xmm0, xmm1, xmm2
	vdivsd xmm0, xmm1, m64
	vdivss xmm0, xmm1, xmm2
	vdivss xmm0, xmm1, m32
endif
if 1
	vandpd xmm0, xmm1, xmm2
	vandpd ymm0, ymm1, ymm2
	vandps xmm0, xmm1, xmm2
	vandps ymm0, ymm1, ymm2

	vandnpd xmm0, xmm1, xmm2
	vandnpd ymm0, ymm1, ymm2
	vandnps xmm0, xmm1, xmm2
	vandnps ymm0, ymm1, ymm2
endif
if 1
	vaddsubpd xmm0, xmm1, xmm2
	vaddsubpd xmm0, xmm1, m128
	vaddsubpd ymm0, ymm1, ymm2
	vaddsubpd ymm0, ymm1, m256

	vaddsubps xmm0, xmm1, xmm2
	vaddsubps xmm0, xmm1, m128
	vaddsubps ymm0, ymm1, ymm2
	vaddsubps ymm0, ymm1, m256

	blendpd xmm0, xmm2, 1
	blendpd xmm0, m128, 1
	vblendpd xmm0, xmm1, xmm2, 1
	vblendpd xmm0, xmm1, m128, 1
	vblendpd ymm0, ymm1, ymm2, 2
	vblendpd ymm0, ymm1, m256, 2

	blendps xmm0, xmm2, 3
	blendps xmm0, m128, 3
	vblendps xmm0, xmm1, xmm2, 3
	vblendps xmm0, xmm1, m128, 3
	vblendps ymm0, ymm1, ymm2, 4
	vblendps ymm0, ymm1, m256, 4

	blendvpd xmm0, xmm2, xmm0
	blendvpd xmm0, m128, xmm0
	vblendvpd xmm0, xmm1, xmm2, xmm3
	vblendvpd xmm0, xmm1, m128, xmm3
	vblendvpd ymm0, ymm1, ymm2, ymm3
	vblendvpd ymm0, ymm1, m256, ymm3

	blendvps xmm0, xmm2, xmm0
	blendvps xmm0, m128, xmm0
	vblendvps xmm0, xmm1, xmm2, xmm3
	vblendvps xmm0, xmm1, m128, xmm3
	vblendvps ymm0, ymm1, ymm2, ymm3
	vblendvps ymm0, ymm1, m256, ymm3

	pblendvb xmm0, xmm2, xmm0
	pblendvb xmm0, m128, xmm0
	vpblendvb xmm0, xmm1, xmm2, xmm3
	vpblendvb xmm0, xmm1, m128, xmm3

	vdppd xmm0, xmm1, xmm2, 1
	vdppd xmm0, xmm1, m128, 2
	;no VEX.256
	vdpps xmm0, xmm1, xmm2, 1
	vdpps xmm0, xmm1, m128, 2
	vdpps ymm0, ymm1, ymm2, 3
	vdpps ymm0, ymm1, m256, 4

	vldmxcsr m32
	vstmxcsr m32

endif
if 1
	vcmppd xmm0, xmm1, xmm2, 1
	vcmppd xmm0, xmm1, m128, 1
	vcmppd ymm0, ymm1, ymm2, 2
	vcmppd ymm0, ymm1, m256, 2

	vcmpps xmm0, xmm1, xmm2, 3
	vcmpps xmm0, xmm1, m128, 3
	vcmpps ymm0, ymm1, ymm2, 4
	vcmpps ymm0, ymm1, m256, 4

	vcmpsd xmm0, xmm1, xmm2, 1
	vcmpsd xmm0, xmm1, m64,  1
	vcmpss xmm0, xmm1, xmm2, 3
	vcmpss xmm0, xmm1, m32,  3
endif
if 1
	vpsrlw  xmm0, xmm1, xmm2
	vpsrlw  xmm0, xmm1, m128
	vpsrld  xmm0, xmm1, xmm2
	vpsrld  xmm0, xmm1, m128
	vpsrlq  xmm0, xmm1, xmm2
	vpsrlq  xmm0, xmm1, m128
	vpsraw  xmm0, xmm1, xmm2
	vpsraw  xmm0, xmm1, m128
	vpsrad  xmm0, xmm1, xmm2
	vpsrad  xmm0, xmm1, m128
	vpsllw  xmm0, xmm1, xmm2
	vpsllw  xmm0, xmm1, m128
	vpslld  xmm0, xmm1, xmm2
	vpslld  xmm0, xmm1, m128
	vpsllq  xmm0, xmm1, xmm2
	vpsllq  xmm0, xmm1, m128
endif
if 1
	movd xmm0, eax
	movd xmm0, m32
	movd eax,  xmm0
	movd m32,  xmm0
	vmovd  xmm0, eax
	vmovd  xmm0, m32
	vmovd  eax,  xmm0
	vmovd  m32,  xmm0

	movq  xmm0, m64
	movq  m64,  xmm0
	vmovq  xmm0, m64
	vmovq  m64,  xmm0
endif
if 1
;--- VEX.NDD
	vpslldq xmm0, xmm1, 1
	vpsrldq xmm0, xmm1, 2
	vpsrlw  xmm0, xmm1, 3
	vpsrld  xmm0, xmm1, 4
	vpsrlq  xmm0, xmm1, 5
	vpsraw  xmm0, xmm1, 6
	vpsrad  xmm0, xmm1, 7
	vpsllw  xmm0, xmm1, 8
	vpslld  xmm0, xmm1, 9
	vpsllq  xmm0, xmm1, 10

;--- VEX.NDS
	vpsrlw  xmm0, xmm1, xmm2
	vpsrlw  xmm0, xmm1, m128
	vpsrld  xmm0, xmm1, xmm2
	vpsrld  xmm0, xmm1, m128
	vpsrlq  xmm0, xmm1, xmm2
	vpsrlq  xmm0, xmm1, m128
	vpsraw  xmm0, xmm1, xmm2
	vpsraw  xmm0, xmm1, m128
	vpsrad  xmm0, xmm1, xmm2
	vpsrad  xmm0, xmm1, m128
	vpsllw  xmm0, xmm1, xmm2
	vpsllw  xmm0, xmm1, m128
	vpslld  xmm0, xmm1, xmm2
	vpslld  xmm0, xmm1, m128
	vpsllq  xmm0, xmm1, xmm2
	vpsllq  xmm0, xmm1, m128
endif
if 1
	vpabsb xmm0, xmm1
	vpabsb xmm0, m128
	vpabsw xmm0, xmm1
	vpabsw xmm0, m128
	vpabsd xmm0, xmm1
	vpabsd xmm0, m128

	vrsqrtps xmm0, xmm1
	vrsqrtss xmm0, xmm1, xmm2

	vcomisd xmm0, xmm1
	vcomisd xmm0, m64
	vcomiss xmm0, xmm1
	vcomiss xmm0, m32
	vucomisd xmm0, xmm1
	vucomisd xmm0, m64
	vucomiss xmm0, xmm1
	vucomiss xmm0, m32

	vptest xmm0, xmm1
	vptest xmm0, m128
	vptest ymm0, ymm1
	vptest ymm0, m256
	vtestps xmm0, xmm1
	vtestps xmm0, m128
	vtestps ymm0, ymm1
	vtestps ymm0, m256
	vtestpd xmm0, xmm1
	vtestpd xmm0, m128
	vtestpd ymm0, ymm1
	vtestpd ymm0, m256
	vrcpps xmm0, xmm1
	vrcpps xmm0, m128
	vrcpps ymm0, ymm1
	vrcpps ymm0, m256
	vrcpss xmm0, xmm1, xmm2
	vrcpss xmm0, xmm1, m32

	vpmovsxbw xmm0, xmm1
	vpmovsxbw xmm0, m64
	vpmovsxbd xmm0, xmm1
	vpmovsxbd xmm0, m32
	vpmovsxbq xmm0, xmm1
	vpmovsxbq xmm0, m16
	vpmovsxwd xmm0, xmm1
	vpmovsxwd xmm0, m64
	vpmovsxwq xmm0, xmm1
	vpmovsxwq xmm0, m32
	vpmovsxdq xmm0, xmm1
	vpmovsxdq xmm0, m64

	vphminposuw xmm0, xmm1
	vphminposuw xmm0, m128

	vextractps eax, xmm1, 1
	vextractps m32, xmm1, 1

	vinsertps xmm0, xmm1, xmm3, 0
	vinsertps xmm0, xmm1, m32, 1

	vhaddpd xmm0, xmm1, xmm2
	vhaddpd xmm0, xmm1, m128
	vhaddpd ymm0, ymm1, ymm2
	vhaddpd ymm0, ymm1, m256

	vhaddps xmm0, xmm1, xmm2
	vhaddps xmm0, xmm1, m128
	vhaddps ymm0, ymm1, ymm2
	vhaddps ymm0, ymm1, m256

	vhsubpd xmm0, xmm1, xmm2
	vhsubpd xmm0, xmm1, m128
	vhsubpd ymm0, ymm1, ymm2
	vhsubpd ymm0, ymm1, m256

	vhsubps xmm0, xmm1, xmm2
	vhsubps xmm0, xmm1, m128
	vhsubps ymm0, ymm1, ymm2
	vhsubps ymm0, ymm1, m256

	vlddqu xmm0, m128
	vlddqu ymm0, m256

	vmaskmovdqu xmm0, xmm1
	vpmovmskb eax, xmm1

endif
if 1
	vcvtdq2pd xmm0, xmm1
	vcvtdq2pd xmm0, m64
	vcvtdq2pd ymm0, xmm1   ;!
	vcvtdq2pd ymm0, m128   ;!

	vcvtdq2ps xmm0, xmm1
	vcvtdq2ps xmm0, m128
	vcvtdq2ps ymm0, ymm1
	vcvtdq2ps ymm0, m256

	vcvtpd2dq xmm0, xmm1
	vcvtpd2dq xmm0, m128
	vcvtpd2dq xmm0, ymm1
	vcvtpd2dq xmm0, m256   ;L bit set?

	vcvttpd2dq xmm0, xmm1
	vcvttpd2dq xmm0, m128
	vcvttpd2dq xmm0, ymm1
	vcvttpd2dq xmm0, m256  ;L bit set?

	vcvtpd2ps xmm0, xmm1
	vcvtpd2ps xmm0, m128
	vcvtpd2ps xmm0, ymm1
	vcvtpd2ps xmm0, m256   ;L bit set?

	vcvtps2dq xmm0, xmm1
	vcvtps2dq xmm0, m128
	vcvtps2dq ymm0, ymm1
	vcvtps2dq ymm0, m256

	vcvttps2dq xmm0, xmm1
	vcvttps2dq xmm0, m128
	vcvttps2dq ymm0, ymm1
	vcvttps2dq ymm0, m256

	vcvtps2pd xmm0, xmm1
	vcvtps2pd xmm0, m64
	vcvtps2pd ymm0, xmm1   ;!
	vcvtps2pd ymm0, m128   ;!

	vcvtsd2si eax, xmm1
	vcvtsd2si eax, m64

	vcvttsd2si eax, xmm1
	vcvttsd2si eax, m64

	vcvtsd2ss xmm0, xmm1, xmm2
	vcvtsd2ss xmm0, xmm1, m64

	vcvtsi2sd xmm0, xmm1, eax
	vcvtsi2sd xmm0, xmm1, m32

	vcvtsi2ss xmm0, xmm1, eax
	vcvtsi2ss xmm0, xmm1, m32

	vcvtss2sd xmm0, xmm1, xmm2
	vcvtss2sd xmm0, xmm1, m32

	vcvtss2si eax, xmm1
	vcvtss2si eax, m32

	vcvttss2si eax, xmm1
	vcvttss2si eax, m32
endif
if 1
	vmovapd xmm0, xmm1
	vmovapd xmm0, m128
	vmovapd m128, xmm1
	vmovapd ymm0, ymm1
	vmovapd ymm0, m256
	vmovapd m256, ymm1

	vmovaps xmm0, xmm1
	vmovaps xmm0, m128
	vmovaps m128, xmm1
	vmovaps ymm0, ymm1
	vmovaps ymm0, m256
	vmovaps m256, ymm1

	vmovupd xmm0, xmm1
	vmovupd xmm0, m128
	vmovupd m128, xmm1
	vmovupd ymm0, ymm1
	vmovupd ymm0, m256
	vmovupd m256, ymm1

	vmovups xmm0, xmm1
	vmovups xmm0, m128
	vmovups m128, xmm1
	vmovups ymm0, ymm1
	vmovups ymm0, m256
	vmovups m256, ymm1

	vmovhlps xmm0, xmm1, xmm2
	vmovlhps xmm0, xmm1, xmm2

	vmovhpd xmm0, xmm1, m64
	vmovhpd m64, xmm1
	vmovhps xmm0, xmm1, m64
	vmovhps m64, xmm1

	vmovlpd xmm0, xmm1, m64
	vmovlpd m64, xmm1
	vmovlps xmm0, xmm1, m64
	vmovlps m64, xmm1
endif
if 1
	vpextrb eax, xmm1, 1
	vpextrb m08, xmm1, 1
	vpextrw eax, xmm1, 2
	vpextrw m16, xmm1, 2
	vpextrd eax, xmm1, 3
	vpextrd m32, xmm1, 3
	;vpextrq is 64-bit only
	;vpextrq rax, xmm1, 4
	;vpextrq m64, xmm1, 4

	vpinsrb xmm0, xmm1, eax, 1
	vpinsrb xmm0, xmm1, m08, 1
	vpinsrw xmm0, xmm1, eax, 2
	vpinsrw xmm0, xmm1, m16, 2
	vpinsrd xmm0, xmm1, eax, 3
	vpinsrd xmm0, xmm1, m32, 3
	;vpinsrq is 64-bit only
	;vpinsrq xmm0, xmm1, rax, 4
	;vpinsrq xmm0, xmm1, m64, 4
endif
	vmovddup xmm0, xmm1
	vmovddup xmm0, m64
	vmovddup ymm0, ymm1
	vmovddup ymm0, m256

end
