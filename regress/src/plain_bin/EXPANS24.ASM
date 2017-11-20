
	.286
	.model small


	.data

TM1 textequ <abc>
TM2 textequ <4>

	db @CatStr(!",<%TM1>,< def !<![esp+%TM2!]!>>,!")

end

