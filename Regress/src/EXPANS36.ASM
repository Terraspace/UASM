
;--- expansion
;--- don't expand result of macro function if it's to become a <>-literal
;--- didn't work in v2.08

	.286
	.model small

abc textequ <0>
def textequ <0>
x	textequ @CatStr( <abc.def> )	;don't expand 'abc' and 'def'

	.data

%	db "&x"

end

