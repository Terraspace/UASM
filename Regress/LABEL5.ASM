
;--- anonymous labels in hll expressions didn't fully work prior to v2.06

	.386
	.MODEL FLAT, stdcall
	option casemap:none

	.code

	mov eax, @F
	xor ecx, ecx
	.if ( eax == @F )
		inc ecx
	.endif
@@:
	.if ( eax == @F || eax == @B )
		inc ecx
	.endif
@@:
	end
