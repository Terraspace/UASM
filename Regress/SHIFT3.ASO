
;--- shift operations with invalid operands

	.model small

	.data

m08 label byte
m16 label word
m32 label dword
m64 label qword
m80 label tbyte
m128 label oword

	.code

main proc
	shl al,dl
	shl ax,dl
	shl [m32],cl
	shl [m64],cl
	shl [m80],cl
	shl [m128],cl
	shl [m32],1
	shl [m64],1
	shl [m80],1
	.186
	shl al,2
	shl ax,2
	shl ax,256
	shl [m32],2
	shl [m64],2
	shl [m80],2
	shl [m128],2
	.386
	shl eax,dl
	shl [m64],cl
	shl eax,256
	shl [m64],1
	shl [m64],2
	shl [m80],1
	shl [m128],1
	shl [m128],2
	.8086
	ret
main endp

    END
