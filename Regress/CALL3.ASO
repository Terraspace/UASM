
;--- invalid calls/jmps

	.286
	.MODEL small

_TEXT2 segment 'CODE'
p2 label near
_TEXT2 ends

	.CODE

p1 label near

	call p1, p1	;masm: syntax error; jwasm: invalid instruction operands
	call 12     ;jump destination must specify a label
	call 1.0    ;masm: real or BCD number not allowed; jwasm: syntax error
	call ds:12	;instruction operand must have size (jwasm emits error in pass 2 only!)
	call al		;masm: instruction operand must have size; jwasm: invalid instruction operands
	call p2		;cannot have implicit far jump or call to near label

	END
