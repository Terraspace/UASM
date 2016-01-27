
;--- % operator for text equates, unsigned values

	.386
	.model flat

T1	textequ %(0-4)

	.data
	db @CatStr(!",%T1,!")

	end
