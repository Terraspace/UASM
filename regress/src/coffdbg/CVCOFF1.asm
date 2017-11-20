
;--- assembler crash if coff line number info was generated ( -Zd or -Zi )
;--- and source contained multiple sections with code outside of procs.

	.386
	.model flat,stdcall
	option casemap:none

	.code

start:
	mov eax, 1
	call anothersection
	ret

	.code XXX
	nop
anothersection:
	add eax,eax
	ret

	.code
	nop
	nop

end start
