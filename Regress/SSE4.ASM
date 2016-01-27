
;--- SSE 4.1 instructions

	.686
	.model small, stdcall
	.xmm

	.data

vo	OWORD 0
vq	dq 0
vd	dd 0
vw	dw 0
vb	db 0

	.code
if 1
	blendpd xmm0, xmm7, 2
	blendpd xmm0, vo, 1
	blendpd xmm0, oword ptr [eax], 1
	blendpd xmm0, oword ptr [eax+8], 255
	blendpd xmm0, oword ptr [eax+1000], 255
	blendpd xmm0, oword ptr [esp], 1
	blendpd xmm0, oword ptr [esp+8], 255
	blendpd xmm0, oword ptr [esp+1000], 255

	blendps xmm1, xmm7, 2
	blendps xmm1, vo, 1
	blendps xmm1, oword ptr [eax], 1
	blendps xmm1, oword ptr [eax+8], 255
	blendps xmm1, oword ptr [eax+1000], 255
	blendps xmm1, oword ptr [esp], 1
	blendps xmm1, oword ptr [esp+8], 255
	blendps xmm1, oword ptr [esp+1000], 255
endif
if 1
	blendvpd xmm2, xmm7, xmm0
	blendvpd xmm2, vo, xmm0
	blendvpd xmm2, oword ptr [eax], xmm0
	blendvpd xmm2, oword ptr [eax+8], xmm0
	blendvpd xmm2, oword ptr [eax+1000], xmm0
	blendvpd xmm2, oword ptr [esp], xmm0
	blendvpd xmm2, oword ptr [esp+8], xmm0
	blendvpd xmm2, oword ptr [esp+1000], xmm0

	blendvps xmm3, xmm7, xmm0
	blendvps xmm3, vo, xmm0
	blendvps xmm3, oword ptr [eax], xmm0
	blendvps xmm3, oword ptr [eax+8], xmm0
	blendvps xmm3, oword ptr [eax+1000], xmm0
	blendvps xmm3, oword ptr [esp], xmm0
	blendvps xmm3, oword ptr [esp+8], xmm0
	blendvps xmm3, oword ptr [esp+1000], xmm0
endif
if 1
	dppd xmm4, xmm7, 2
	dpps xmm4, vo, 1
	dppd xmm4, oword ptr [eax], 1
	dppd xmm4, oword ptr [eax+8], 2
	dppd xmm4, oword ptr [eax+1000], 3
	dppd xmm4, oword ptr [esp], 4
	dppd xmm4, oword ptr [esp+8], 5
	dppd xmm4, oword ptr [esp+1000], 6

	dpps xmm5, xmm7, 2
	dpps xmm5, vo, 1
	dpps xmm5, oword ptr [eax], 1
	dpps xmm5, oword ptr [eax+8], 2
	dpps xmm5, oword ptr [eax+1000], 3
	dpps xmm5, oword ptr [esp], 4
	dpps xmm5, oword ptr [esp+8], 5
	dpps xmm5, oword ptr [esp+1000], 6
endif
if 1
	extractps ecx, xmm0, 0
	extractps vd, xmm1, 1
	extractps dword ptr [eax], xmm1, 1
	extractps dword ptr [eax+8], xmm1, 1
	extractps dword ptr [eax+1000], xmm1, 1
	extractps dword ptr [esp], xmm1, 1
	extractps dword ptr [esp+8], xmm1, 1
	extractps dword ptr [esp+1000], xmm1, 1

	insertps xmm2, xmm1, 0
	insertps xmm3, vd, 1
	insertps xmm3, dword ptr [eax], 1
	insertps xmm3, dword ptr [eax+8], 1
	insertps xmm3, dword ptr [eax+1000], 1
	insertps xmm3, dword ptr [esp], 1
	insertps xmm3, dword ptr [esp+8], 1
	insertps xmm3, dword ptr [esp+1000], 1
endif
if 1
	movntdqa xmm4, vo
	movntdqa xmm4, oword ptr [eax]
	movntdqa xmm4, oword ptr [eax+8]
	movntdqa xmm4, oword ptr [eax+1000]
	movntdqa xmm4, oword ptr [esp]
	movntdqa xmm4, oword ptr [esp+8]
	movntdqa xmm4, oword ptr [esp+1000]
endif
if 1
	mpsadbw xmm4, vo, 0
	mpsadbw xmm4, oword ptr [eax], 0
	mpsadbw xmm4, oword ptr [eax+8], 0
	mpsadbw xmm4, oword ptr [eax+1000], 0
	mpsadbw xmm4, oword ptr [esp], 0
	mpsadbw xmm4, oword ptr [esp+8], 0
	mpsadbw xmm4, oword ptr [esp+1000], 0
endif
if 1
	packusdw xmm5, xmm7
	packusdw xmm5, vo
	packusdw xmm5, oword ptr [eax]
	packusdw xmm5, oword ptr [eax+8]
	packusdw xmm5, oword ptr [eax+1000]
	packusdw xmm5, oword ptr [esp]
	packusdw xmm5, oword ptr [esp+8]
	packusdw xmm5, oword ptr [esp+1000]
endif
if 1
	pblendvb xmm2, xmm7, xmm0
	pblendvb xmm2, vo, xmm0
	pblendvb xmm2, oword ptr [eax], xmm0
	pblendvb xmm2, oword ptr [eax+8], xmm0
	pblendvb xmm2, oword ptr [eax+1000], xmm0
	pblendvb xmm2, oword ptr [esp], xmm0
	pblendvb xmm2, oword ptr [esp+8], xmm0
	pblendvb xmm2, oword ptr [esp+1000], xmm0
endif
if 1
	pblendw xmm3, xmm7, 3
	pblendw xmm3, vo, 2
	pblendw xmm3, oword ptr [eax], 1
	pblendw xmm3, oword ptr [eax+8], 0
	pblendw xmm3, oword ptr [eax+1000], 3
	pblendw xmm3, oword ptr [esp], 2
	pblendw xmm3, oword ptr [esp+8], 1
	pblendw xmm3, oword ptr [esp+1000], 0
endif
if 1
	pcmpeqq xmm1, xmm7
	pcmpeqq xmm1, vo
	pcmpeqq xmm1, oword ptr [eax]
	pcmpeqq xmm1, oword ptr [eax+8]
	pcmpeqq xmm1, oword ptr [eax+1000]
	pcmpeqq xmm1, oword ptr [esp]
	pcmpeqq xmm1, oword ptr [esp+8]
	pcmpeqq xmm1, oword ptr [esp+1000]
endif
if 1
	pextrb ecx, xmm7, 0
	pextrb vb, xmm7, 0
	pextrb byte ptr [eax], xmm7, 0
	pextrb byte ptr [esp], xmm7, 0
	pextrd ecx, xmm7, 1
	pextrd vd, xmm7, 1
	pextrd dword ptr [eax], xmm7, 1
	pextrd dword ptr [esp], xmm7, 1
;--- pextrq is for 64-bit only
	pextrw ecx, xmm7, 0
	pextrw vw, xmm7, 0
	pextrw word ptr [eax], xmm7, 0
	pextrw word ptr [esp], xmm7, 0
endif
if 1
	phminposuw xmm2, xmm7
	phminposuw xmm2, vo
	phminposuw xmm2, oword ptr [eax]
	phminposuw xmm2, oword ptr [eax+8]
	phminposuw xmm2, oword ptr [eax+1000]
	phminposuw xmm2, oword ptr [esp]
	phminposuw xmm2, oword ptr [esp+8]
	phminposuw xmm2, oword ptr [esp+1000]
endif
if 1
	pinsrb xmm6, ecx, 0
	pinsrb xmm6, vb, 0
	pinsrb xmm6, byte ptr [eax], 0
	pinsrb xmm6, byte ptr [esp], 0
	pinsrd xmm6, ecx, 1
	pinsrd xmm6, vd, 1
	pinsrd xmm6, dword ptr [eax], 1
	pinsrd xmm6, dword ptr [esp], 1
;--- pinsrq is for 64-bit only
endif
if 1
	pmaxsb xmm2, xmm7
	pmaxsb xmm2, vo
	pmaxsb xmm2, oword ptr [eax]
	pmaxsb xmm2, oword ptr [eax+8]
	pmaxsb xmm2, oword ptr [eax+1000]
	pmaxsb xmm2, oword ptr [esp]
	pmaxsb xmm2, oword ptr [esp+8]
	pmaxsb xmm2, oword ptr [esp+1000]

	pmaxsd xmm2, xmm7
	pmaxsd xmm2, vo
	pmaxsd xmm2, oword ptr [eax]
	pmaxsd xmm2, oword ptr [eax+8]
	pmaxsd xmm2, oword ptr [eax+1000]
	pmaxsd xmm2, oword ptr [esp]
	pmaxsd xmm2, oword ptr [esp+8]
	pmaxsd xmm2, oword ptr [esp+1000]

	pmaxud xmm2, xmm7
	pmaxud xmm2, vo
	pmaxud xmm2, oword ptr [eax]
	pmaxud xmm2, oword ptr [eax+8]
	pmaxud xmm2, oword ptr [eax+1000]
	pmaxud xmm2, oword ptr [esp]
	pmaxud xmm2, oword ptr [esp+8]
	pmaxud xmm2, oword ptr [esp+1000]

	pmaxuw xmm2, xmm7
	pmaxuw xmm2, vo
	pmaxuw xmm2, oword ptr [eax]
	pmaxuw xmm2, oword ptr [eax+8]
	pmaxuw xmm2, oword ptr [eax+1000]
	pmaxuw xmm2, oword ptr [esp]
	pmaxuw xmm2, oword ptr [esp+8]
	pmaxuw xmm2, oword ptr [esp+1000]
endif
if 1
	pminsb xmm2, xmm7
	pminsb xmm2, vo
	pminsb xmm2, oword ptr [eax]
	pminsb xmm2, oword ptr [eax+8]
	pminsb xmm2, oword ptr [eax+1000]
	pminsb xmm2, oword ptr [esp]
	pminsb xmm2, oword ptr [esp+8]
	pminsb xmm2, oword ptr [esp+1000]

	pminsd xmm2, xmm7
	pminsd xmm2, vo
	pminsd xmm2, oword ptr [eax]
	pminsd xmm2, oword ptr [eax+8]
	pminsd xmm2, oword ptr [eax+1000]
	pminsd xmm2, oword ptr [esp]
	pminsd xmm2, oword ptr [esp+8]
	pminsd xmm2, oword ptr [esp+1000]

	pminud xmm2, xmm7
	pminud xmm2, vo
	pminud xmm2, oword ptr [eax]
	pminud xmm2, oword ptr [eax+8]
	pminud xmm2, oword ptr [eax+1000]
	pminud xmm2, oword ptr [esp]
	pminud xmm2, oword ptr [esp+8]
	pminud xmm2, oword ptr [esp+1000]

	pminuw xmm2, xmm7
	pminuw xmm2, vo
	pminuw xmm2, oword ptr [eax]
	pminuw xmm2, oword ptr [eax+8]
	pminuw xmm2, oword ptr [eax+1000]
	pminuw xmm2, oword ptr [esp]
	pminuw xmm2, oword ptr [esp+8]
	pminuw xmm2, oword ptr [esp+1000]
endif
if 1
;--- Masm v9 rejects valid memory references
;--- Masm v10 accepts
	pmovsxbd xmm2, xmm7    ;4 sbytes -> 4 sdwords
	pmovsxbd xmm2, vd
	pmovsxbd xmm2, dword ptr [eax]
	pmovsxbd xmm2, dword ptr [esp]

	pmovsxbq xmm2, xmm7    ;2 sbytes -> 2 sqwords
	pmovsxbq xmm2, vw
	pmovsxbq xmm2, word ptr [eax]
	pmovsxbq xmm2, word ptr [esp]

	pmovsxbw xmm2, xmm7    ;8 sbytes -> 8 swords
	pmovsxbw xmm2, vq
	pmovsxbw xmm2, qword ptr [eax]
	pmovsxbw xmm2, qword ptr [esp]

	pmovsxdq xmm2, xmm7    ;2 sdwords -> 2 sqwords
	pmovsxdq xmm2, vq
	pmovsxdq xmm2, qword ptr [eax]
	pmovsxdq xmm2, qword ptr [esp]

	pmovsxwd xmm2, xmm7    ;4 swords -> 4 sdwords
	pmovsxwd xmm2, vq
	pmovsxwd xmm2, qword ptr [eax]
	pmovsxwd xmm2, qword ptr [esp]

	pmovsxwq xmm2, xmm7    ;2 swords -> 2 sqwords
	pmovsxwq xmm2, vd
	pmovsxwq xmm2, dword ptr [eax]
	pmovsxwq xmm2, dword ptr [esp]
endif
if 1
;--- Masm v9 rejects valid memory references
;--- Masm v10 accepts
	pmovzxbd xmm2, xmm7    ;4 bytes -> 4 dwords
	pmovzxbd xmm2, vd
	pmovzxbd xmm2, dword ptr [eax]
	pmovzxbd xmm2, dword ptr [esp]

	pmovzxbq xmm2, xmm7    ;2 bytes -> 2 qwords
	pmovzxbq xmm2, vw
	pmovzxbq xmm2, word ptr [eax]
	pmovzxbq xmm2, word ptr [esp]

	pmovzxbw xmm2, xmm7    ;8 bytes -> 8 words
	pmovzxbw xmm2, vq
	pmovzxbw xmm2, qword ptr [eax]
	pmovzxbw xmm2, qword ptr [esp]

	pmovzxdq xmm2, xmm7    ;2 dwords -> 2 qwords
	pmovzxdq xmm2, vq
	pmovzxdq xmm2, qword ptr [eax]
	pmovzxdq xmm2, qword ptr [esp]

	pmovzxwd xmm2, xmm7    ;4 words -> 4 dwords
	pmovzxwd xmm2, vq
	pmovzxwd xmm2, qword ptr [eax]
	pmovzxwd xmm2, qword ptr [esp]

	pmovzxwq xmm2, xmm7    ;2 words -> 2 qwords
	pmovzxwq xmm2, vd
	pmovzxwq xmm2, dword ptr [eax]
	pmovzxwq xmm2, dword ptr [esp]
endif
if 1
	pmuldq xmm3, xmm7
	pmuldq xmm3, vo
	pmuldq xmm3, oword ptr [eax]
	pmuldq xmm3, oword ptr [eax+8]
	pmuldq xmm3, oword ptr [eax+1000]
	pmuldq xmm3, oword ptr [esp]
	pmuldq xmm3, oword ptr [esp+8]
	pmuldq xmm3, oword ptr [esp+1000]

	pmulld xmm4, xmm7
	pmulld xmm4, vo
	pmulld xmm4, oword ptr [eax]
	pmulld xmm4, oword ptr [eax+8]
	pmulld xmm4, oword ptr [eax+1000]
	pmulld xmm4, oword ptr [esp]
	pmulld xmm4, oword ptr [esp+8]
	pmulld xmm4, oword ptr [esp+1000]
endif
if 1
	ptest xmm4, xmm7
	ptest xmm4, vo
	ptest xmm4, oword ptr [eax]
	ptest xmm4, oword ptr [eax+8]
	ptest xmm4, oword ptr [eax+1000]
	ptest xmm4, oword ptr [esp]
	ptest xmm4, oword ptr [esp+8]
	ptest xmm4, oword ptr [esp+1000]
endif
if 1
	roundpd xmm4, xmm7, 0
	roundpd xmm4, vo, 1
	roundpd xmm4, oword ptr [eax], 2
	roundpd xmm4, oword ptr [eax+8], 3
	roundpd xmm4, oword ptr [eax+1000], 0
	roundpd xmm4, oword ptr [esp], 1
	roundpd xmm4, oword ptr [esp+8], 2
	roundpd xmm4, oword ptr [esp+1000], 3

	roundps xmm4, xmm7, 0
	roundps xmm4, vo, 1
	roundps xmm4, oword ptr [eax], 2
	roundps xmm4, oword ptr [eax+8], 3
	roundps xmm4, oword ptr [eax+1000], 0
	roundps xmm4, oword ptr [esp], 1
	roundps xmm4, oword ptr [esp+8], 2
	roundps xmm4, oword ptr [esp+1000], 3

	roundsd xmm4, xmm7, 0
	roundsd xmm4, vq, 1
	roundsd xmm4, qword ptr [eax], 2
	roundsd xmm4, qword ptr [eax+8], 3
	roundsd xmm4, qword ptr [eax+1000], 0
	roundsd xmm4, qword ptr [esp], 1
	roundsd xmm4, qword ptr [esp+8], 2
	roundsd xmm4, qword ptr [esp+1000], 3

	roundss xmm4, xmm7, 0
	roundss xmm4, vd, 1
	roundss xmm4, dword ptr [eax], 2
	roundss xmm4, dword ptr [eax+8], 3
	roundss xmm4, dword ptr [eax+1000], 0
	roundss xmm4, dword ptr [esp], 1
	roundss xmm4, dword ptr [esp+8], 2
	roundss xmm4, dword ptr [esp+1000], 3
endif
	ret

	End
