
;--- test direct memory access with constant

	.486
	.MODEL FLAT
	option casemap:none

	.code

	mov eax, ds:[0ff000h]

	end

