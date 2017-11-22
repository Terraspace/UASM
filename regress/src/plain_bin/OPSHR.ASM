
;--- test SHL operator
;--- there are differences in code generation between
;--- Masm v6 and Masm v9++ ( expression evaluator changed to 64-bit )

	.model small
	.386

	.data

	dq -1
	dq -1 shr 1
	dq -1 shr 16
	dq -1 shr 32
	dq -1 shr 63
	dq -1 shr 64

	.code

	mov edx, -1 SHR 0
;	mov edx, -1 SHR 1   ;error 'constant value too large'
;	mov edx, -1 SHR 8   ;error 'constant value too large'
	mov edx, -1 SHR 32
	mov edx, -1 SHR 64
	ret

    END
