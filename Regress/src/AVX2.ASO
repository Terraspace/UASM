
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

	vbroadcastss xmm0, m64
	vbroadcastss ymm0, ymm1
	vbroadcastsd ymm0, m128
	vbroadcastf128 ymm0, ymm1
	vinsertf128 ymm0, ymm1, xmm1, xmm0
	vinsertf128 ymm0, ymm1, m128
	vextractf128 xmm0, ymm0, ymm0
	vextractf128 m128, ymm0
	vmaskmovps xmm0, xmm1
	vmaskmovps ymm0, ymm1, ymm2
	vmaskmovps m128, xmm0
	vmaskmovps m256, ymm0
	vmaskmovpd xmm0, xmm1
	vmaskmovpd ymm0, ymm1, ymm2
	vmaskmovpd m128, xmm0
	vmaskmovpd m256, ymm0
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
	vaddpd xmm0, xmm1
	vaddpd xmm0, xmm1, m128
	vaddpd ymm0, ymm1, ymm2
	vaddpd ymm0, ymm1, m256
	vaddsubpd xmm0, xmm1
	vblendpd xmm0, xmm1, xmm2
	vblendpd xmm0, xmm1
	vblendpd ymm0, ymm1, ymm2
	vblendpd ymm0, ymm1
	vblendps xmm0, xmm1, xmm2
	vblendps xmm0, xmm1
	vblendps ymm0, ymm1, ymm2
	vblendps ymm0, ymm1
	vblendvpd xmm0, xmm1, xmm2
	vblendvpd xmm0, xmm1, m128
	vblendvpd ymm0, ymm1, ymm2
	vblendvpd ymm0, ymm1, m256
	vblendvps xmm0, xmm1
	vblendvps xmm0, xmm1
	vblendvps ymm0, ymm1
	vblendvps ymm0, ymm1
	vpblendvb xmm0, xmm1, xmm2
	vpblendvb xmm0, xmm1
	vdppd xmm0, xmm1, xmm2
	vdppd xmm0, xmm1
	vdpps xmm0, xmm1, eax
	vdpps xmm0, xmm1, m08
	vdpps ymm0, ymm1
	vdpps ymm0, ymm1, eax

	vcvtpd2dq   xmm0, [ebx] 	;untyped memory is to be rejected!
	vcvttpd2dq  xmm0, [ebx] 	;untyped memory is to be rejected!
	vcvtpd2ps   xmm0, [ebx] 	;untyped memory is to be rejected!

end
