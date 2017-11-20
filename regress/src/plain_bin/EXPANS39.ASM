
;--- macro function calls with <>-literals as arguments of hll directives
;--- this was a problem before v2.11 because hll directives .if, .while, .until, .elseif
;--- trigger a special tokenize-mode that handles < and > differently

	.386
	.model flat
	.code

	.if @SubStr(<ebx==1 && edi==2, xxx>, 1, 16)
	.endif

;--- this was accepted prior to v2.11, but result of @InStr() was wrong
	.if @InStr(,<abc>,<c>)
	.endif

end
