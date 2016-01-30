
;--- JWasm prior to v2.06 rejects

_DATA segment
dot_position equ @InStr(2, <0.0049999998882413>, <.>)
local_double textequ @CatStr(<_DBL_>, @SubStr(<0.0049999998882413>, 1, dot_position - 1), <_>, @SubStr(<0.0049999998882413>, dot_position + 1))
%	db "&local_double"
_DATA ends

end
