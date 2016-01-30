
;--- up to v2.11, there was a problem to
;--- detect macro placeholders that were preceded by a '!'.

	.386
	.model flat

X1 macro xxx
	.if !xxx
	.endif
endm

X2 macro
local xxx
xxx equ 1
	.if !xxx
	.endif
endm

X3 macro xxx
	.if !!xxx
	.endif
endm

	.code

	X1 eax
	X2
	X3 eax

end

