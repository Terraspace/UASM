
	.286
	.model small

	.code

start:

;--- case 1: the third lbl1 definition is the CURRENT definition
;--- when the jmp is assembled

	jmp lbl1
lbl1 = $
	db 1,2,3
lbl1 = $
	db 1,2,3
lbl1 = $

;--- case 2: the first lbl2 definition is the CURRENT definition
;--- when the jmp is assembled

lbl2 = $
	jmp lbl2
lbl2 = $
	db 1,2,3
lbl2 = $
	db 1,2,3
lbl2 = $

end start

