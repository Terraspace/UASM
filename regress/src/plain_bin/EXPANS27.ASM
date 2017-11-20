
;--- local located in quoted string with & operater AFTER the local
;--- didn't work until v2.08

_DATA segment

M1 MACRO Param
LOCAL data
	db "data&"
ENDM

M1 eax

_DATA ends

end
