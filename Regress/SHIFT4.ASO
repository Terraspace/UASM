
;--- shift operations with warnings.
;--- warnings since v2.11

	.model small

	.code

main proc
	shl [bx],1
	shr [bx],cl
	.186
	rol [bx],2
	.386
	ror [ebx],1
	rcl [ebx],cl
	rcr [ebx],2
	ret
main endp

    END
