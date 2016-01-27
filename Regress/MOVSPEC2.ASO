
	.286

_TEXT16 segment 'CODE'
	mov eax, cr0	;not accepted
_TEXT16 ends

	.386

_TEXT32 segment use32 'CODE'

	push cr0		;only MOV allowed
	add eax, cr0	;only MOV allowed
	mov eax, cr0
	mov eax, dr0
	mov eax, tr6
	mov eax, tr3	;386 acceots tr6/7 only
	mov eax, cr4	;requires 586

	.486
	mov eax, tr3	;ok
	.586
	mov eax, tr3	;ok
	mov eax, cr4	;ok

	.686
	mov eax, tr3	;686+ accepts no tr register
	mov eax, tr7	;686+ accepts no tr register

_TEXT32 ends

	end

