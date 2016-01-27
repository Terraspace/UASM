
;--- test FORC loops

	.286
	.model small
	option dotname

	.code

TE1 CatStr <>
	forc x,abc!def,ab d f
TE1 CatStr TE1,<x>
	endm
	db @CatStr(!",%TE1,!")

TE1 CatStr <>
	forc .x,<gjk>
TE1 CatStr TE1,<.x>
	endm
	db @CatStr(!",%TE1,!")

TE1 CatStr <>
	forc x, <lmn>
TE1 CatStr TE1,<x>
	endm
	db @CatStr(!",%TE1,!")

TE1 CatStr <>
	forc x,<opq!rst>
TE1 CatStr TE1,<x>
	endm
	db @CatStr(!",%TE1,!")

	end
