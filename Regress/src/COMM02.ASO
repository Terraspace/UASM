
;--- communal variables
;--- must assemble with errors

	.286
	.model small

	.data

v1	dw 1
comm v1:word 	;symbol redefinition

comm v2:word
comm v2:word	;ok

extern v3:word
comm v3:word 	;symbol redefinition

comm v4:word	;size differs
comm v4:dword

comm v5:word
	public v5

comm v6:0		;positive value expected

comm ax:word	;invalid identifier
comm v7,word	;syntax error
comm v7:44ud	;missing operator in expression

	end
