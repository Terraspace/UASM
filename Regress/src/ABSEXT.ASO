
;--- "absolute" externals

	.286
	.model small

externdef E1:abs

	.code

	mov ax, seg E1		;is to fail
	mov ax, offset E1
	mov ax, low E1
	mov ax, high E1
	mov ax, lowword E1
	mov ax, highword E1	;is to fail
	mov ax, type E1
	mov ax, opattr E1
	mov ax, .type E1

	mov ax, length E1
	mov ax, size E1
	mov ax, lengthof E1	;jwasm rejects
	mov ax, sizeof E1	;jwasm rejects

	end
