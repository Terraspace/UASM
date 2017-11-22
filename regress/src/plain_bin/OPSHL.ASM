
;--- test SHL operator

	.model small
	.386

	.data

	.code

	mov edx, -1 SHL 8
;	mov edx, (-1 SHL 8) SHR 8	;won't work with Masm v8+/JWasm v2.06+
;	mov edx, 0FFFFFFFFh SHL 8	;won't work with Masm v8+/JWasm v2.06+
	mov edx, (0FFFFFFFFh SHL 8) SHR 8
	ret

    END
