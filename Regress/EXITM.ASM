
;--- expansion of EXITM argument 
;--- with @CatStr() and text macro

;--- @CatStr()
mf1 macro
	exitm @CatStr(2 !> 1)
endm
x2 textequ mf1()

;--- local text macro
mf2 macro
local TMP
TMP textequ <2 !> 1>
	exitm TMP
endm
x3 textequ mf2()

;--- global text macro
mf3 macro
TM1 textequ <2 !> 1>
	exitm TM1
endm
x4 textequ mf3()

_DATA segment
%	db "&x2"
	db ","
%	db "&x3"
	db ","
%	db "&x4"
_DATA ends

end

