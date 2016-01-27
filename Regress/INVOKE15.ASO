
;--- size of constants too large

	.386
	.model flat, stdcall

	.code

x1 proc a1:byte, a2:word
x1 endp

x2 proc a1:dword
x2 endp

	invoke x1, 100h, -10000h
	invoke x1, 1.0, 2.0

	invoke x2, 1.0	;accepted
	invoke x2, 123456789Ah

	end
