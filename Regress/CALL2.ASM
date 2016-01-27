
;--- indirect call with TYPE coercion

	.286
	.MODEL small
	.386
	option casemap:none

p1 typedef proto near   stdcall :word
p2 typedef proto far    stdcall :word
p3 typedef proto near32 stdcall :word
p4 typedef proto far32  stdcall :word

;--- duplicate type definition ( was a problem in 2.09-2.10 )
p3 typedef proto near32 stdcall :word
p4 typedef proto far32  stdcall :word

	.CODE

	call near32 ptr [bx]
	call far32  ptr [bx]

	call p1 ptr [bx]
	call p2 ptr [bx]
	call p3 ptr [bx]
	call p4 ptr [bx]
	invoke p1 ptr [bx], 1
	invoke p2 ptr [bx], 1
	invoke p3 ptr [bx], 1
	invoke p4 ptr [bx], 1

	END
