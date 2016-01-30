
;--- TEST instruction

	.286
	.model small
	.386

	.data

m08	label byte
m16	label word
m32	label dword

	.code

	test al,1
	test ax,2
	test eax,-1
	test bl,1
	test bx,2
	test ebx,32
	test al,bl
	test ax,cx
	test eax,edx
	test bl,cl
	test bx,cx
	test ebx,edx
	test al,m08
	test ax,m16
	test eax,m32
	test bl,m08
	test bx,m16
	test ebx,m32
	test m08,al
	test m16,ax
	test m32,eax
	test m08,bl
	test m16,bx
	test m32,ebx
	test m08,1
	test m08,-1
	test m16,2
	test m16,-1
	test m32,3

	end

