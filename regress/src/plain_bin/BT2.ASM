
;--- BT, limits of immediate argument

	.386
	.model small

	.data

vw	label word
vd	label dword

	.code

	bt ax, -1
	bt ax, -128
	bt ax, 255
	bt eax, -1
	bt eax, -128
	bt eax, 255
	bt vw, -1
	bt vw, -128
	bt vw, 255
	bt vd, -1
	bt vd, -128
	bt vd, 255

end
