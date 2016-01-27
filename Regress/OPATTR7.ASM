
;--- 16-bit opattr specifics

	.286
	.model small

	.data

;	dw opattr [esp]	;register not accepted in current mode
;	dw opattr [ebp]	;register not accepted in current mode
	dw opattr [sp]
	dw opattr [bp]

END
