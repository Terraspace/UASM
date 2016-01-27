
;--- caused problems with JWasm v2.07 and below!

	.386
	.model flat,stdcall
	.code

	.if (edx==28h && (eax==1 || eax==2)) || \
		(edx==26h && (eax==3 || eax==4)) || \
		(edx==21h && (eax==5 || eax==6)) || \
		(edx==22h && (eax==7 || eax==8))
		xor eax, eax
	.endif

	.if ((eax==1 || eax==2) && !ecx) || (eax==3 && ecx)
		xor ebx, ebx
	.endif

	ret

	end
