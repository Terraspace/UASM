
;--- test 64-bit invoke with ADDR

ifdef __JWASM__
	.x64
	.model flat, fastcall
endif

	.data
v1	db 0
v2	dw 0
	.code

p2 proc a1:qword,a2:dword,a3:ptr,a4:word,a5:dword,a6:qword,a7:ptr
p2 endp

	invoke p2, addr v1, addr [r8d], addr v2, 0, addr v2, addr [r10+r11], 0
	ret

	end
