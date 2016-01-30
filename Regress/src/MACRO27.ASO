
;--- an undefined macro function may cause weird error msgs,
;--- while the most important info, the name of the macro, 
;--- is not displayed.
;--- improved in v2.12 - if the macro call has 2 or more arguments

	.386
	.MODEL FLAT, stdcall

printf proto c :vararg

	.CODE

;--- macro CStr() is not defined
	invoke printf, CStr(1,2), eax

;--- macro CStr2() is also not defined -
;--- but since just 1 argument is used, jwasm cannot
;--- detect in pass one that it's an error.
	invoke printf, CStr2(1), eax


END
