
;--- extend register arguments to WORD and SWORD params in 32-bit

	.386
	.model flat

	.code

ux proc c a1:word, a2:word, a3:word, a4:word
	ret
ux endp

sx proc c a1:sword, a2:sword, a3:sword, a4:sword
	ret
sx endp

	invoke sx, cl, dh, bx, ax

;--- with type coercion, the values are sign-extended,
;--- no matter if the target is signed or not.

	invoke sx, sbyte ptr cl, sbyte ptr dh, sword ptr bx, sword ptr ax
	invoke ux, sbyte ptr cl, sbyte ptr dh, sword ptr bx, sword ptr ax

	end
