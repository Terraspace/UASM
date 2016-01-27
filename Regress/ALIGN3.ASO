
	.386
	.model flat, stdcall
	option casemap:none

	.data

v1	db 0

	align E1	;error 'symbol not defined'
E1	equ 4
	align 3		;must be power of 2

	align 64	;incompatible with segment alignment

S1 struct 5		;must be power of 2
S1 ends

S2 struct 256
	db ?
S2 ends

S3 struct
	db ?
	align 65536	;should work, no integer overflow
S3 ends

S4 struct E2	;err 'symbol not defined'
	db ?
S4 ends

E2 equ 4

S5 struct
	db ?
	align 5		;must be power of 2
	db ?
S5 ends

	align v1	;constant expected

S6 struct v1	;constant expected
	db ?
S6 ends

	end
