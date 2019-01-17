;
; 2.48 allow function call expansion after comma, check code/data section order and offsets.
;
option flat:1

	.data

	d1 dd 32

	.code

	use32

foo	proc stdcall a:dword
	ret
foo	endp

bar	proc stdcall
local	l1
	mov	edi,[ebx + foo(0)]
	add	esi,foo(0xFFFFFFFF)
	mov	d1,foo(1)
	mov dl2,foo(1)
	mov	l1,foo(1)
	ret
bar	endp

	.data

	dl2 dd 64
	
	end
	