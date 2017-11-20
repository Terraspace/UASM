
;--- float constants
;--- including LOW32, HIGH32

	.386

_TEXT segment 'CODE'

	mov eax, low32 1.0
	mov edx, high32 1.0

	mov eax, low32 3.01
	mov edx, high32 3.01

	real4 1.0
	real8 1.0
	real4 3.01
	real8 3.01

	dd low32 1.0
	dd high32 1.0
	dd low32 3.01
	dd high32 3.01

_TEXT ends

	end
