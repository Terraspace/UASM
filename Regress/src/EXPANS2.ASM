
;--- numeric expansion

	.model small

E1	equ 12
E2	equ 5
TE1	textequ <8>
TE2	textequ <3+TE1>

	.data

SrcLine1 textequ @CatStr( %E1, !, ,%E1+1, !, ,%E1+2 )
	dw SrcLine1

SrcLine2 textequ @CatStr( %E1 + E2 )
	dw SrcLine2

SrcLine3 textequ @CatStr( %E1 + TE1 )
	dw SrcLine3

SrcLine4 textequ @CatStr( %TE2 )
	dw SrcLine4

SrcLine5 textequ @CatStr( %TE1 + TE2 )
	dw SrcLine5

?VMAJOR equ 3
?VMINOR equ 13

version db "V",?VMAJOR+'0',".",@CatStr(!",%?VMINOR/10,%?VMINOR mod 10,!"),0


END
