
;--- invoke tests for far data ptrs

	.286
	.model compact, stdcall

p1 proto :ptr, :near ptr, :ptr near, :far ptr, :ptr far

	.CODE

	invoke p1, 1, 2, 3, 4, 5
	ret

p1 proc a1:ptr, a2:near ptr, a3:ptr near, a4:far ptr, a5:ptr far
	mov ax,a2
	mov cx,a3
	les dx,a4
	les bx,a5
p1 endp

	END
