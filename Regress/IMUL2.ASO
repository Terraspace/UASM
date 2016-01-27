
;--- due to its 3 argument format,
;--- IMUL needs special treatment in the parser.

	.286
	.model small

	.data

vb  label byte
vw  label word
vd	dd 0

	.code

	.386
;--- if first operand is memory, no second op is allowed
;--- this was accepted by JWasm v2.05-
	imul [vb],1
	imul [vw],2
	imul [vd],3

;--- byte operand is only allowed if single
;--- this was also accepted by JWasm v2.05-
	imul  al,bl
	imul  al,[vb]
	imul  al,[vbx]

	ret

	.data

vbx	label byte
vwx	label word
vdx	dd 0

    END
