
;--- MOV 64-bit offsets
;--- ML64 won't accept "near32"!

if 0;def __JWASM__
	.x64
	.model flat
endif

	.data

dlbl1 dd 0

v1	dq dlbl1, dlbl2, clbl1, clbl2
v2	dd dlbl1, clbl1

	.code

clbl1:
	mov rax, offset dlbl1
	mov rax, offset clbl1
	mov rax, offset dlbl2
	mov rax, offset clbl2
	mov rax, clbl1
	mov rax, clbl2
;--- 32bit offsets
	mov rax, near32 ptr dlbl1
	mov rax, near32 ptr clbl1
	mov rax, near32 ptr clbl2
	ret
clbl2:

	.data

dlbl2 dd 0


end
