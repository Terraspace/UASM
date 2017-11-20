
;--- SSE2 CMPSD/MOVSD instruction test

	.686
	.model flat, stdcall
	.xmm

	.code

;--- if both base + index register are used for
;--- addressing, then Masm will generate slightly
;--- different code than JWasm!

start:
	mov eax, offset v1
	movsd xmm0, qword ptr [eax]
	movsd xmm1, qword ptr [eax]
	mov ecx, eax
	movsd xmm2, qword ptr [ecx]
	movsd xmm3, qword ptr [ecx]
	xor ecx, ecx
	movsd xmm4, qword ptr [eax+ecx]
	movsd xmm5, qword ptr [eax+ecx]

;	movsd xmm0, [eax] ;not accepted by Masm v8

	cmpsd xmm0, qword ptr [eax], 0
	cmpsd xmm1, qword ptr [eax], 2
	cmpsd xmm2, qword ptr [eax], 0
	cmpsd xmm3, qword ptr [eax], 2
	mov ecx, eax
	cmpsd xmm4, qword ptr [ecx], 0
	cmpsd xmm5, qword ptr [ecx], 2
	cmpsd xmm6, qword ptr [ecx], 0
	cmpsd xmm7, qword ptr [ecx], 2
	xor ecx, ecx
	cmpsd xmm0, qword ptr [eax+ecx], 0
	cmpsd xmm1, qword ptr [eax+ecx], 2
	ret

v1	db "12345678"

	End start
