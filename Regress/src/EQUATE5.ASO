
;--- test equate redefinition, subtract 2 labels.
;--- error 'symbol redefinition'

	.386
	.model flat

	.code

label2:
	mov al, 1
label3:
    RET

X4	EQU label3 - label2	;ok, numeric value
X4	EQU label3 - label3	;symbol redefinition

	end
