
option flat:1

.data

.code

	use64

	; Verify opnd immediate size reductions
	bt eax,400				; Simple case, 400 is greater than signed OR unsigned byte -> ERROR not valid instruction

	; MASM accepts -200 (low byte 38h), but rejects the positive value 300.
	mov al,-200
	mov al,300
	mov cl,-200
	mov cl,300
