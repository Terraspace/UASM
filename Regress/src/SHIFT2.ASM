
;--- SHLD/SHRD operations 
;--- with forward references

	.386
	.model small

	.data

vd	dd 0
vw	dw 0

	.code

;--- the first operand may be a register or a memory reference

main proc

	shld ax,bx,cl
	shld ax,bx,1
	shld ax,bx,3
	shld vw,bx,5
	shld vw2,bx,2

	shrd ax,bx,cl
	shrd ax,bx,7
	shrd vw,bx,129
	shrd vw2,bx,15

	shld eax,ebx,cl
	shld eax,ebx,1
	shld eax,ebx,3
	shld vd,ebx,5
	shld vd2,ebx,2

	shrd eax,ebx,cl
	shrd eax,ebx,7
	shrd vd,ebx,129
	shrd vd2,ebx,31

	ret
main endp

	.data

vd2	dd 0
vw2	dw 0

    END
