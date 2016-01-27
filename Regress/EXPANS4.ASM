
;--- macro expansion
;--- test ifidn
;--- test expansion operator at start of line
;--- test literal character operator in a FORC string

	.386
	.model flat, stdcall
	option casemap:none

L macro parms:VARARG
local wstr,i,c,tstr
	wstr textequ <>
	i = 0
	for parm,<parms>
	  c SubStr <parm>,1,1
	  ifidn c,<!">
		tstr SubStr <parm>,2,@SizeStr(parm)-2
%		forc chr$,<tstr>
		  if i
			wstr CatStr wstr,<,>
		  endif
		  wstr CatStr wstr,<'&chr$'>
		  i = i + 1
		endm
	  else
		if i
		  wstr CatStr wstr,<,>
		endif
		wstr CatStr wstr,<parm>
	  endif
	endm
	exitm <wstr>
endm

	.data

	dw L("ab!c")

	end
