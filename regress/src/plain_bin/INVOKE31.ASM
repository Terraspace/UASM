
;--- extend register arguments to DWORD and SDWORD params in 16-bit

	.286
	.model small

	.code

ux proc c a1:dword, a2:dword, a3:dword, a4:dword
	ret
ux endp

sx proc c a1:sdword, a2:sdword, a3:sdword, a4:sdword
	ret
sx endp

	.8086
	invoke ux, cl, dh, bx, bp	;ax can't be used ( register value overwritten... )
	.186
	invoke ux, cl, dh, bx, ax
	.386
	invoke ux, cl, dh, bx, ax

;--- it doesn't matter whether the target are signed values, it's always zero-extended!
	.8086
	invoke sx, cl, dh, bx, bp	;ax can't be used ( register value overwritten... )
	.186
	invoke sx, cl, dh, bx, ax
	.386
	invoke sx, cl, dh, bx, ax

;--- with type coercion, the values are sign-extended!
;--- if cpu < 386, registers dl, dh and dx cannot be used as arguments 
;--- because they're overwritten ( Masm won't detect this!)
	.8086
	invoke sx, sbyte ptr cl, sbyte ptr ch, sword ptr bx, sword ptr ax
	.186
	invoke sx, sbyte ptr cl, sbyte ptr ch, sword ptr bx, sword ptr ax
	.386
	invoke sx, sbyte ptr cl, sbyte ptr dh, sword ptr bx, sword ptr ax

	end
