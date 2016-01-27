
;--- macro with VARARG parameter attribute and % operator

	.386
	.model flat, stdcall
	option casemap :none

E2	equ 1

Check2 macro args:VARARG
	for arg, <args>
	mov eax, arg
	endm
endm

	.code

	Check2 1, %2, %3, 4

	end
