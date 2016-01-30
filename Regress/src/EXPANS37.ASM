
;--- expansion of EXITM argument with ! operator
;--- ! inside the EXITM literal are handled as macro operator
;--- as soon as a macro argument or local is inside.
;--- See also expans29.asm.

	.286
	.model small

	.code

GREATER macro v1,v2
	exitm <v1 !> v2>
endm

NOTEQ macro v1,v2
	exitm <v1 !!= v2>
endm

ISNOT macro v1
	exitm <!!v1>
endm

ISNOTZERO macro
	exitm <!Zero?>	;here the ! is NOT an operator.
endm

	.if GREATER(ax,bx)
		nop
	.endif

	.if NOTEQ(ax,bx)
		nop
	.endif

	.if ISNOT(ax)
		nop
	.endif

	.if ISNOTZERO()
		nop
	.endif

end
