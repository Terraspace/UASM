
;--- test invoke with :VARARG prototype

	.286
	.model small,c

E1	equ 1
E2	equ -1
E3	equ 10002h

	.data

vd	dd 0
vw	dw 0
vb	db 0

	.data?

buffer db 128 dup (?)

	.code

printf proc c a1:ptr, args:VARARG
	ret
printf endp

	.8086

	invoke printf, addr buffer, 1, bx, cl, dh, ds, vb, vw, vd, E1, E2, E3, dx::ax

	.186

	invoke printf, addr buffer, 1, bx, cl, dh, ds, vb, vw, vd, E1, E2, E3, dx::ax

	.386

	invoke printf, addr buffer, 1, bx, cl, dh, ds, vb, vw, vd, E1, E2, E3, dx::ax

	end
