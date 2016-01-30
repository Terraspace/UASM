
;--- pointer dereference

	.386
	.model flat

S1 struct
f1  dw ?
f2  dw ?
S1 ends

	.code

	assume esi:ptr ptr S1	;2 levels of indirection!
	mov [esi].f2, 1			;shouldn't be accepted

end
