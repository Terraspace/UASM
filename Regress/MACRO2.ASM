
;--- test text macro expansion
;--- text macro contains 2 macro function calls

	.286
	.model small
	.386

argy CATSTR <@SubStr(<mov nEvents:eax>,1,11) , @SubStr(<mov nEvents:eax>,13)>

	.data

nEvents dd 0

	.code

	argy

	ret

	End
