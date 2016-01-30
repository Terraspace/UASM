
;--- access to a struct with incompatible size must be flagged

	.386
	.model flat
	option casemap:none

S1 STRUCT
x  dd ?
S1 ENDS

S3 STRUCT
x  dd ?
y  dw ?
S3 ENDS

	.code

	mov ax, [ebx.S1]          ;error (wrong size)
	mov ax, [ebx+S1]          ;ok
	mov ax, [ebx.S3.x]        ;error (wrong size)
	mov ax, [ebx+S3.x]        ;error (wrong size)
	mov ax, [ebx.S3.y]        ;ok
	mov ax, [ebx+S3.y]        ;ok

	end
