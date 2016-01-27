
;--- extend register arguments to DWORD and SDWORD params in 32-bit

	.386
	.model flat

	.code

ux proc c a1:dword, a2:dword, a3:dword, a4:dword
	ret
ux endp

sx proc c a1:sdword, a2:sdword, a3:sdword, a4:sdword
	ret
sx endp

	invoke sx, cl, dh, bx, ax

;--- with type coercion, the values are sign-extended,
;--- no matter if the target is signed or not.

	invoke sx, sbyte ptr cl, sbyte ptr dh, sword ptr bx, sword ptr ax
	invoke ux, sbyte ptr cl, sbyte ptr dh, sword ptr bx, sword ptr ax

	end
