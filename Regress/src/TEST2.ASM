
;--- TEST instruction

	.286
	.model small
	.386

	.data

m08	label byte
m16	label word
m32	label dword

	.code

	test al,80h
	test ax,8000h
	test eax,80000000h
	test bl,80h
	test bx,8000h
	test ebx,80000000h
	test m08,80h
	test m16,8000h
	test m32,80000000h

	end

