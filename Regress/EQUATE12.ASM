
;--- test EXTERN after internal definition
;--- works for ABS symbols only

X1 equ 0
extern X1:abs

X2 = 1
extern X2:abs

_DATA segment
	db X1
_DATA ends

	end
