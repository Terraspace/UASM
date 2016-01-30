
;--- this wasn't rejected before v2.09
;--- because MakeConst() in expreval.c changes
;--- expression to EXPR_CONST and CreateAssemblyTimeVariable()
;--- in equate.c did check EXPR_ADDR for undefined symbols only.

	.386
	.model flat, stdcall

E1 = E1 and -2
E1 = E1 or  2

	END
