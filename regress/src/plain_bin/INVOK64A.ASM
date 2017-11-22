
;--- error prior to v2.09:
;--- expression foo.y did return a mem_type != EMPTY,
;--- and that mem_type wasn't ignored.

ifdef __JWASM__
	.x64
	.model flat, fastcall
endif

foo struct
x WORD ?
y WORD ?
foo ends

	.code

XXX proc a1:dword, a2:dword, a3:dword
XXX endp

	invoke XXX,0,foo.y,0

end
