;
; v2.21 allow function call expansion after comma
;
	.486
	.model	flat, stdcall
	.data
	d1 dd ?
	.code

foo	proc a
	ret
foo	endp

bar	proc
local	l1
	mov	edi,[ebx + foo(0)]
	add	esi,foo(0xFFFFFFFF)
	mov	d1,foo(1)
	mov	l1,foo(1)
	ret
bar	endp

	end
