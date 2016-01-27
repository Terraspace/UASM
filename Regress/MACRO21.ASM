
;--- purge test

	.386
	.model flat, stdcall
	option casemap:none

M1 macro x
	db x
endm

	.code

	M1 0
	purge M1
	M1 1

end
