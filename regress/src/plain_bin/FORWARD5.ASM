
;--- there was an undetected phase error
;--- ( and, consecutively, improper code generated ),
;--- if an equate was assigned a forward ref to a relocatable address.

	.286
	.model small

	.code

start:
	jmp forward   ;assumed short in pass 1, later changed to near32 ( size 2 -> 5 )
	dw lbl2-lbl1
lbl1 = $          ;an alias defined via '=' and forward referenced has problems to trigger a phase error!
	db 80h dup (?)
lbl2:
forward:
	nop

end start

