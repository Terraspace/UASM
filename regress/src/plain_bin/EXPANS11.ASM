
;--- EQU expansion

	.286
	.model small

TE1 textequ <def>
TE2 textequ <  jkl>
MF1 macro
	exitm <ghi>
	endm

E1	equ
E2	equ abc
E3	equ  abc
E4	equ TE1
%E5	equ TE1
E6	equ MF1()
%E7	equ MF1()

%E8	equ TE2

MF1	macro p
	exitm <p shl 1>
	endm
TE3	textequ <MF1(2)>

E8	equ MF1(1)
%E9	equ MF1(1)	;with %, the macro function is expanded!
E10	equ TE3
;%E10 equ TE3	;Masm/JWasm complains: syntax error: integer


	.data
TX  CatStr <db ">,E2,E3,E4,E5,E6,E7,E8,E10,<">
	TX

	end
