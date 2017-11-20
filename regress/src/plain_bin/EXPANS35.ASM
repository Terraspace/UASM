
;--- expansion: be careful with expansion of items at position 0
;--- ( might turn out to be a text macro definition line ( EQU, CATSTR, TEXTEQU, SUBSTR )

TM_1 textequ <X>
;--- the next line must REDEFINE TM_1, but not define X!
    @CatStr(TM, _1 ) textequ <ABC>

_DATA segment
%	db "&X"
_DATA ends

	end
