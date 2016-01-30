
;--- PROC params with size 0
;--- gives errors

	.286
	.model small,c

S1 struct
S1 ends

	.code

p1 proc a1:S1

	ret

p1 endp

	invoke p1,0

	end
