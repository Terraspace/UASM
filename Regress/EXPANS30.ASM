
;--- numeric expansion of macro arguments

	.model small

E1	equ 12
E2	equ 5
TE1	textequ <8>
TE2	textequ <3+TE1>

TE3	textequ <MF>
TE4	textequ <1()>

MF1 macro
	exitm <12>
	endm

MF2 macro
	exitm <1+TE1>
	endm

	.data

xxx	macro x
;	echo x
%	db "&x"
	endm

	xxx TE1 TE2
%	xxx TE1 TE2
	xxx TE3&TE4
	xxx %TE3%TE4
%	xxx TE3&TE4

	xxx MF1() MF2()
%	xxx MF1() MF2()
	xxx MF1()&MF2()
	xxx %MF1()%MF2()
%	xxx MF1()&MF2()

END
