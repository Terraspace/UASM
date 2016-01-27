
;--- regression test
;--- code generation
;--- MOVD/MOVQ in 16-bit code segment

	.model small
	.686
	.xmm

	.data

vo	OWORD 112233445566778899AABBCCDDEEFF00h
vq	dq 123456789ABCDEF0h
vd	dd 12345678h
vw	dw 1234h

	.code

;--- MOVD
;--- with MOVD, one can transfer content from R32/M32
;--- to MMX/XMM or from MMX/XMM to R32/M32

	movd mm1, eax         ;mm, r32
	movd xmm1, eax        ;xmm, r32
	movd mm1, vd          ;mm, mem32
	movd xmm1, vd         ;xmm, mem32
	movd mm1, dword ptr [ebx]
if 0;@Version eq 615
	movd mm1, [ebx]       ;masm v8 gives 'invalid instruction operands'
endif
	movd eax, mm1         ;r32, mm
	movd eax, xmm1        ;r32, xmm
	movd vd, mm1          ;mem32, mm
	movd vd, xmm1         ;mem32, xmm
	movd dword ptr [ebx], mm1
if 0;@Version eq 615
	movd [ebx], mm1       ;masm v8 gives 'invalid instruction operands'
endif

;--- MOVQ
;--- with MOVQ, one can transfer content to/from MMX/XMM/M64 to MMX/XMM/M64

	movq xmm1, xmm0       ;xmm, xmm
	movq mm1, mm0         ;mm, mm
	movq xmm1, vq         ;xmm, mem64
	movq mm0, vq          ;mm, mem64
	movq mm1, qword ptr [ebx]
	movq mm1, [ebx]
	movq vq, xmm0         ;mem64, xmm
	movq vq, mm0          ;mem64, mm
	movq qword ptr [ebx], mm0
	movq qword ptr [ebx], xmm0
	movq [ebx], mm1

	ret

	end
