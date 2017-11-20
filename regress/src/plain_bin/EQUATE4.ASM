
;--- 64-bit assembly time variables and equates

ifdef __JWASM__
	.x64
	.model flat
endif

num1 =  1234567800000000h
num2 =  7fffffff00000000h
num3 =  8000000000000000h
num4 = 0ffffffff00000000h

	.code

	mov rax, num1
	mov rbx, num2
	mov rcx, num3
	mov rdx, num4
	mov rax,  123456789ABCDEF0h
	mov rbx, 0FEDCBA9876543210h
	mov rcx, 0ffffffffh	;requires long format
	mov rdx, -1			;short format ok

	end
