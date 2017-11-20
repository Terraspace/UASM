
;--- AVX, 32-bit

	.686
	.model flat
	.xmm

	.data

m128 label xmmword
m256 label ymmword
	oword 0,0

	.code

	vmovmskpd eax,  xmm0
	vmovmskps eax,  xmm0

	vmovmskpd eax,  ymm0	;accepted since 2.11
	vmovmskps eax,  ymm0	;accepted since 2.11

	vmovntdq  m128, xmm0
	vmovntdqa xmm0, m128
	vmovntpd  m128, xmm0
	vmovntps  m128, xmm0

	vmovntdq  m256, ymm0	;accepted since 2.11
;	vmovntdqa ymm0, m256	;this will work in AVX2 only
	vmovntpd  m256, ymm0	;accepted since 2.11
	vmovntps  m256, ymm0	;accepted since 2.11

end
