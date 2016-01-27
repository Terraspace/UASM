
;--- test assembly time variable variants

	.386
	.model flat

externdef X1:abs
externdef X2:abs

COMM X3:byte

	.code
l1:
	mov eax, 1
l2:

l3 proc c a1:word
	ret
l3 endp

X1 = l2
X1 = l2+1
X1 = l2-l1
	db X1 dup (90h)
X1 = l3

	invoke X1,0

X1 = l3+1

	invoke X1,0

X1 = 1

	invoke X1,0		;wont work

X1 = X2	;constant expected
X1 = X3	;constant expected

	end
