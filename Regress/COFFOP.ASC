
	.386
	.MODEL FLAT
	.DATA

v1 db 0

	.CODE

	xor eax, eax
	mov eax, imagerel v1
	mov eax, sectionrel v1
	mov eax, [eax + imagerel v1]
	mov eax, [eax + sectionrel v1]
	mov eax, [eax + ecx + imagerel v1]
	mov eax, [eax + ecx + sectionrel v1]
	mov eax, [eax + ecx*4 + imagerel v1]
	mov eax, [eax + ecx*4 + sectionrel v1]
	ret

	END
