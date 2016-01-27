
;--- SSE2 CMPSD/MOVSD instruction test

	.686
	.model flat, stdcall
	.xmm

	.data

m64	label qword
m128 label oword

	.code

;--- 128-bit memory op
	movapd xmm0, xmm2
	movapd xmm1, m128
	movapd m128, xmm3
	movapd xmm0, [eax]
	movapd [eax], xmm0

	movaps xmm0, xmm2
	movaps xmm1, m128
	movaps m128, xmm3
	movaps xmm0, [eax]
	movaps [eax], xmm0

	movdqa xmm0, xmm2
	movdqa xmm1, m128
	movdqa m128, xmm3
	movdqa xmm0, [eax]
	movdqa [eax], xmm0

	movdqu xmm0, xmm2
	movdqu xmm1, m128
	movdqu m128, xmm3
	movdqu xmm0, [eax]
	movdqu [eax], xmm0

	movupd xmm0, xmm2
	movupd xmm1, m128
	movupd m128, xmm3
	movupd xmm0, [eax]
	movupd [eax], xmm0

	movups xmm0, xmm2
	movups xmm1, m128
	movups m128, xmm3
	movups xmm0, [eax]
	movups [eax], xmm0

;--- 64-bit memory op
	movhpd xmm1, m64
	movhpd m64, xmm3
	movhpd xmm0, [eax]	;masm v8+ rejects
	movhpd [eax], xmm0	;masm v8+ rejects

	movhps xmm1, m64
	movhps m64, xmm3
	movhps xmm0, [eax]	;masm v8+ rejects
	movhps [eax], xmm0	;masm v8+ rejects

	movlpd xmm1, m64
	movlpd m64, xmm3
	movlpd xmm0, [eax]	;masm v8+ rejects
	movlpd [eax], xmm0	;masm v8+ rejects

	movlps xmm1, m64
	movlps m64, xmm3
	movlps xmm0, [eax]	;masm v8+ rejects
	movlps [eax], xmm0	;masm v8+ rejects

	ret

	End
