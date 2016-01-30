
;--- float limits
;--- 1.18e-38   - 3.40e38   is range for real4
;--- 2.23e-308  - 1.79e308  is range for real8
;--- 3.37e-4932 - 1.18e4932 is range for real10


	.386

_DATA segment 'DATA'

	real4  0.0
	real4  1.18e-38
	real4  3.40e+38
	real8  2.23e-308
	real8  1.79e+308
	real10 3.37e-4932
	real10 1.18e+4932

;--- 1.0 as hexadecimal values with real-number designator 'r'
	real4 3f800000r
	real8 3ff0000000000000r
	real10 3fff8000000000000000r

_DATA ends

	end
