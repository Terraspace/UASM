
;--- AVX, 32-bit
;--- unsized memory operand

	.686
	.model flat
	.xmm

	.code

;--- new AVX instructions
	vbroadcastss xmm0, [ebx]
	vbroadcastss ymm0, [ebx]
	vbroadcastsd ymm0, [ebx]
	vbroadcastf128 ymm0, [ebx]

	vinsertf128 ymm0, ymm1, [ebx], 2
	vextractf128 [ebx], ymm0, 2

	vmaskmovps xmm0, xmm1, [ebx]
	vmaskmovps ymm0, ymm1, [ebx]
	vmaskmovps [ebx], xmm0, xmm1
	vmaskmovps [ebx], ymm0, ymm1	;ok with v2.08

	vmaskmovpd xmm0, xmm1, [ebx]
	vmaskmovpd ymm0, ymm1, [ebx]
	vmaskmovpd [ebx], xmm0, xmm1
	vmaskmovpd [ebx], ymm0, ymm1	;ok with v2.08

	vpermilpd xmm0, xmm1, [ebx]
	vpermilpd ymm0, ymm1, [ebx]

	vpermilps xmm0, xmm1, [ebx]
	vpermilps ymm0, ymm1, [ebx]

	vperm2f128 ymm0, ymm1, [ebx], 1	;ok with v2.08

	vtestps xmm0, [ebx]
	vtestps ymm0, [ebx]

	vtestpd xmm0, [ebx]
	vtestpd ymm0, [ebx]

;--- ADD, DIV, MAX, MIN, MUL, SQRT, SUB
	addpd xmm0, [ebx]

	vaddpd xmm0, xmm1, [ebx]
	vaddpd ymm0, ymm1, [ebx]

	vaddps xmm0, xmm1, [ebx]
	vaddps ymm0, ymm1, [ebx]

	vaddsd xmm0, xmm1, [ebx]
	vaddss xmm0, xmm1, [ebx]

	divpd xmm0, [ebx]
	vdivpd xmm0, xmm1, [ebx]
	vdivpd ymm0, ymm1, [ebx]

	vdivps xmm0, xmm1, [ebx]
	vdivps ymm0, ymm1, [ebx]

	vdivsd xmm0, xmm1, [ebx]
	vdivss xmm0, xmm1, [ebx]

	vaddsubpd xmm0, xmm1, [ebx]
	vaddsubpd ymm0, ymm1, [ebx]

	vaddsubps xmm0, xmm1, [ebx]
	vaddsubps ymm0, ymm1, [ebx]

	blendpd xmm0, [ebx], 1
	vblendpd xmm0, xmm1, [ebx], 1
	vblendpd ymm0, ymm1, [ebx], 2

	blendps xmm0, [ebx], 3
	vblendps xmm0, xmm1, [ebx], 3
	vblendps ymm0, ymm1, [ebx], 4

	blendvpd xmm0, [ebx], xmm0
	vblendvpd xmm0, xmm1, [ebx], xmm3
	vblendvpd ymm0, ymm1, [ebx], ymm3

	blendvps xmm0, [ebx], xmm0
	vblendvps xmm0, xmm1, [ebx], xmm3
	vblendvps ymm0, ymm1, [ebx], ymm3

	pblendvb xmm0, [ebx], xmm0
	vpblendvb xmm0, xmm1, [ebx], xmm3

	vdppd xmm0, xmm1, [ebx], 2
	;no VEX.256
	vdpps xmm0, xmm1, [ebx], 2
	vdpps ymm0, ymm1, [ebx], 4

	vldmxcsr [ebx]
	vstmxcsr [ebx]

	vcmppd xmm0, xmm1, [ebx], 1
	vcmppd ymm0, ymm1, [ebx], 2

	vcmpps xmm0, xmm1, [ebx], 3
	vcmpps ymm0, ymm1, [ebx], 4

	vcmpsd xmm0, xmm1, [ebx],  1
	vcmpss xmm0, xmm1, [ebx],  3

	vpsrlw  xmm0, xmm1, [ebx]
	vpsrld  xmm0, xmm1, [ebx]
	vpsrlq  xmm0, xmm1, [ebx]
	vpsraw  xmm0, xmm1, [ebx]
	vpsrad  xmm0, xmm1, [ebx]
	vpsllw  xmm0, xmm1, [ebx]
	vpslld  xmm0, xmm1, [ebx]
	vpsllq  xmm0, xmm1, [ebx]

	movd xmm0, [ebx]
	movd [ebx],  xmm0
	vmovd  xmm0, [ebx]
	vmovd  [ebx],  xmm0

	movq  xmm0, [ebx]
	movq  [ebx],  xmm0
	vmovq  xmm0, [ebx]
	vmovq  [ebx],  xmm0

;--- VEX.NDS
	vpsrlw  xmm0, xmm1, [ebx]
	vpsrld  xmm0, xmm1, [ebx]
	vpsrlq  xmm0, xmm1, [ebx]
	vpsraw  xmm0, xmm1, [ebx]
	vpsrad  xmm0, xmm1, [ebx]
	vpsllw  xmm0, xmm1, [ebx]
	vpslld  xmm0, xmm1, [ebx]
	vpsllq  xmm0, xmm1, [ebx]

	vpabsb xmm0, [ebx]
	vpabsw xmm0, [ebx]
	vpabsd xmm0, [ebx]

	vcomisd xmm0, [ebx]
	vcomiss xmm0, [ebx]
	vucomisd xmm0, [ebx]
	vucomiss xmm0, [ebx]

	vptest xmm0, [ebx]
	vptest ymm0, [ebx]
	vtestps xmm0, [ebx]
	vtestps ymm0, [ebx]
	vtestpd xmm0, [ebx]
	vtestpd ymm0, [ebx]
	vrcpps xmm0, [ebx]
	vrcpps ymm0, [ebx]
	vrcpss xmm0, xmm1, [ebx]

	vpmovsxbw xmm0, [ebx]
	vpmovsxbd xmm0, [ebx]
	vpmovsxbq xmm0, [ebx]
	vpmovsxwd xmm0, [ebx]
	vpmovsxwq xmm0, [ebx]
	vpmovsxdq xmm0, [ebx]

	vphminposuw xmm0, [ebx]

	vextractps [ebx], xmm1, 1

	vinsertps xmm0, xmm1, [ebx], 1

	vhaddpd xmm0, xmm1, [ebx]
	vhaddpd ymm0, ymm1, [ebx]

	vhaddps xmm0, xmm1, [ebx]
	vhaddps ymm0, ymm1, [ebx]

	vhsubpd xmm0, xmm1, [ebx]
	vhsubpd ymm0, ymm1, [ebx]

	vhsubps xmm0, xmm1, [ebx]
	vhsubps ymm0, ymm1, [ebx]

	vlddqu xmm0, [ebx]
	vlddqu ymm0, [ebx]

	vcvtdq2pd xmm0, [ebx]
	vcvtdq2pd ymm0, [ebx]   ;ok with v2.08

	vcvtdq2ps xmm0, [ebx]
	vcvtdq2ps ymm0, [ebx]

;	vcvtpd2dq xmm0, [ebx]	;error with v2.08 (operand must have size)
;	vcvttpd2dq xmm0, [ebx]	;error with v2.08 (operand must have size)
;	vcvtpd2ps xmm0, [ebx]	;error with v2.08 (operand must have size)

	vcvtps2dq xmm0, [ebx]
	vcvtps2dq ymm0, [ebx]

	vcvttps2dq xmm0, [ebx]
	vcvttps2dq ymm0, [ebx]

	vcvtps2pd xmm0, [ebx]
	vcvtps2pd ymm0, [ebx]   ;ok with v2.08

	vcvtsd2si eax, [ebx]

	vcvttsd2si eax, [ebx]

	vcvtsd2ss xmm0, xmm1, [ebx]

	vcvtsi2sd xmm0, xmm1, [ebx]

	vcvtsi2ss xmm0, xmm1, [ebx]

	vcvtss2sd xmm0, xmm1, [ebx]

	vcvtss2si eax, [ebx]

	vcvttss2si eax, [ebx]

	vmovapd xmm0, [ebx]
	vmovapd [ebx], xmm1
	vmovapd ymm0, [ebx]
	vmovapd [ebx], ymm1		;ok with v2.08

	vmovaps xmm0, [ebx]
	vmovaps [ebx], xmm1
	vmovaps ymm0, [ebx]
	vmovaps [ebx], ymm1		;ok with v2.08

	vmovupd xmm0, [ebx]
	vmovupd [ebx], xmm1
	vmovupd ymm0, [ebx]
	vmovupd [ebx], ymm1		;ok with v2.08

	vmovups xmm0, [ebx]
	vmovups [ebx], xmm1
	vmovups ymm0, [ebx]
	vmovups [ebx], ymm1		;ok with v2.08

	vmovhpd xmm0, xmm1, [ebx]
	vmovhpd [ebx], xmm1
	vmovhps xmm0, xmm1, [ebx]
	vmovhps [ebx], xmm1

	vmovlpd xmm0, xmm1, [ebx]
	vmovlpd [ebx], xmm1
	vmovlps xmm0, xmm1, [ebx]
	vmovlps [ebx], xmm1

	vpextrb [ebx], xmm1, 1
	vpextrw [ebx], xmm1, 2
	vpextrd [ebx], xmm1, 3
	;vpextrq is 64-bit only
	;vpextrq rax, xmm1, 4
	;vpextrq [ebx], xmm1, 4

	vpinsrb xmm0, xmm1, [ebx], 1
	vpinsrw xmm0, xmm1, [ebx], 2
	vpinsrd xmm0, xmm1, [ebx], 3
	;vpinsrq is 64-bit only
	;vpinsrq xmm0, xmm1, rax, 4
	;vpinsrq xmm0, xmm1, [ebx], 4

	vmovddup xmm0, [ebx]
	vmovddup ymm0, [ebx]	;ok with v2.08

end
