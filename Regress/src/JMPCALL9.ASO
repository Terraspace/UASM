
;--- error messages with call/jmp + direct operand

	.386

_TEXT16 segment use16 'CODE'
p16n label near
p16f label far
_TEXT16 ends

_TEXT segment use32 'CODE'

p32n label near
p32f label far

	call p16n	;cannot have implicit far jump or call to near label
	call far ptr p16n
	call p16f
	call p32n
	call p32f
	call 0		;jump destination must specify a label
	call p16f,1	;Masm: syntax error, JWasm: invalid instruction operands
	call short p16f	;Masm cannot access label ..., JWasm: cannot use SHORT with CALL
	jmp p16n
	jmp short p16n	;Masm: cannot access label through segment registers, JWasm: cannot have implicit...

_TEXT ends

	end
