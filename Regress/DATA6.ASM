
;--- temp macro parameter expansion problem in v2.08

	.386
	.model flat, stdcall
	option casemap:none

POINT struct
x	dd ?
y	dd ?
POINT ends

defv macro var, init
var	POINT init
	endm

	.data

	defv xxx,{<1,2>}

end

