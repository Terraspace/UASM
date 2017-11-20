
;--- v2.08pre temporarily had problems in FORC if the item was a blank
;--- the L() macro function has problems with !,<,> and quotes

	 .386
	 .model flat, stdcall
	 option casemap:none

;---- L() defines a wide string

L macro parms:VARARG
local wstr,i,c,tstr
    wstr textequ <>
    i = 0
    for parm,<parms>
      c SubStr <parm>,1,1
      ifidn c,<">
        tstr SubStr <parm>,2,@SizeStr(parm)-2    
%       forc chr$,<tstr>
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

	dw L("abc def")
	dw L("%&a")
;	dw L("!!!!")  ;these "disappear" in Masm

	END
