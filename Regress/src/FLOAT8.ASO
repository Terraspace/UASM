
;--- float limits
;--- 1.18e-38   - 3.40e38   is range for real4
;--- 2.23e-308  - 1.79e308  is range for real8
;--- 3.37e-4932 - 1.18e4932 is range for real10


	.386

_DATA segment 'DATA'

	real4  1.17e-38		;rejected by ml + jwasm ( since v2.11 )
	real4  3.41e+38     ;rejected by ml + jwasm ( since v2.06 )
	real8  2.22e-308	;rejected by ml + jwasm ( since v2.11 )
	real8  1.80e+308	;rejected by ml + jwasm ( since v2.11 )
	real10 3.36e-4932	;accepted by ml + jwasm
	real10 1.19e+4932	;rejected by ml, accepted by jwasm

;--- rejected by ml + jwasm ( since v2.11 )
	real4 3ff0000000000000r
	real8 3fff8000000000000000r
	real10 3fff8000000000000000000000000000r

_DATA ends

	end
