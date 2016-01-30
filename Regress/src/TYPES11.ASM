
;--- forward reference in a type expression, used as left operand for PTR

	.386
	.model flat

	.code

	mov eax, (type var) ptr [ebx]

var dd 0

end

