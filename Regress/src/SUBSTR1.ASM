
TM1	SUBSTR <abc!def>,5
TM2	SUBSTR <abc!!def>,4

;%echo TM1
;%echo TM2

_DATA segment
%	db "&TM1"
%	db "&TM2"
_DATA ends

	end
