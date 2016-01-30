
;--- test initialization structured variables with arrays
;--- expected error: initializer must be a string or single item

	.386
	.model flat

S1 struct
V0	db 3 dup (?)
V1	dw ?
S1 ends

	.data

var1 S1 <1,2>			;Masm: error, jwasm v2.08: ok, jwasm v2.09: error
var2 S1 <1 dup (1),2>	;ok
var3 S1 <3 dup (1),2>	;ok
var4 S1 <1 dup (1,2,3),2>	;Masm: too many initial values ???

	END
