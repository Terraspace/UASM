
;--- test FOR loops

	.286
	.model small
	option dotname

	.code

;--- empty loop
	for x,<>
	endm

;--- formal parameter is a reserved word
	for eax,<>
	endm

TE1 CatStr <>
	for x:req, <a,b,c>
TE1 CatStr TE1,<x>
	endm
	db @CatStr(!",%TE1,!")

	end
