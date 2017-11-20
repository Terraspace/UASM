
;--- test expanding of text macros containing a macro function call
;--- plus additional characters.
;--- bugfix in v2.03

	.386
	.model flat, stdcall
	option casemap :none

	.data

RGB macro Red:req, Green:req, Blue:req, Alpha:=<0>
    exitm <256*(256*(256*Alpha+Blue)+Green)+Red>
endm

COLOR equ RGB( 64, 64, 255 )

Params CatStr <+15,>
Params CatStr <COLOR>, Params
Params2 SubStr Params, 1, @SizeStr(%Params) - 1

	dd Params2

	end
