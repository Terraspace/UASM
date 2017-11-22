
;--- test invoke with register assumes

	.286
	.model small,c
	.386

	.code

proto1 typedef proto stdcall :dword
LPFN1 typedef ptr proto1

	assume bx:ptr proto1
	invoke bx, 1
	invoke (bx), 1
	invoke ((bx)), 1
	assume bx:LPFN1
	invoke bx, 1

	end
