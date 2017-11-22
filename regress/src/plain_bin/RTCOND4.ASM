
	.386
	.model flat,stdcall
	.code

	.if ( ( (edx==28h && (eax==1 || eax==2) ) || \
			(edx==26h && (eax==3 || eax==4) ) || \
			(edx==21h && (eax==5 || eax==6) ) || \
			(edx==22h && (eax==7 || eax==8) ) ) || \
			(ecx==1 && ebx==2) ) || \
			(esi==5 && edi==6)
		dd -1
	.endif

	ret

	end
