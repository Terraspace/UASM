
;--- dot operator with OPTION OLDSTRUCTS

	.386
	.model flat
	option oldstructs

S1 struct
f1	dd ?
S1 ends

	.code

xxx S1 <>

;--- needs OPTION OLDSTRUCTS

	mov eax, [S1.f1].[eax]
	mov eax, [S1.f1].[eax+ecx]
	mov eax, [S1.f1].[xxx]
	mov eax, [xxx].[eax]
	mov eax, [eax].[xxx]
	mov eax, [eax].DWORD
	mov eax, [eax].4
	mov eax, [4].[eax]

	END
