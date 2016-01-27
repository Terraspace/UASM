
;--- TEXTEQU expansion and % operator

	.286
	.model small

	.data
ByteSize textequ %(4)
Check textequ %((7/ByteSize)*ByteSize)
	db Check
	end
