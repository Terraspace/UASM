
;--- pointer type arguments
;--- see invoke37.asm for 16-bit variant

	.386
	.MODEL small, c
	option casemap:none

;--- arguments: push 4, 8, 4, 4, 2, 4  bytes

p1 typedef proto :near ptr
p2 typedef proto :far ptr
p3 typedef proto :near16 ptr
p4 typedef proto :far16 ptr
p5 typedef proto far16 :near16 ptr
p6 typedef proto far16 :far16 ptr

	.data

dlbl label byte

	.CODE

	invoke p1 ptr [ebx], 0
	invoke p2 ptr [ebx], 0
	invoke p3 ptr [ebx], 0
	invoke p4 ptr [ebx], 0
	invoke p5 ptr [ebx], 0
	invoke p6 ptr [ebx], 0

;--- Masm won't accept p3-p6,
;--- returns error 'INVOKE argument type mismatch',
;--- JWasm accepts, but a "truncate" warning might be appropriate

	invoke p1 ptr [ebx], addr dlbl
	invoke p2 ptr [ebx], addr dlbl	;Masm v8+: error 'symbol type conflict'
ifdef __JWASM__
	invoke p3 ptr [ebx], addr dlbl	;supposed to be a dword ( zero-extended near16 )
	invoke p4 ptr [ebx], addr dlbl	;supposed to be a dword ( far16 )
	invoke p5 ptr [ebx], addr dlbl	;supposed to be a word ( near16 )
	invoke p6 ptr [ebx], addr dlbl	;supposed to be a dword ( far16 )
endif

	invoke p1 ptr [ebx], eax		;regs pushed as dword
	invoke p2 ptr [ebx], ds::eax	;regs pushed as qword
	invoke p3 ptr [ebx], ax			;regs pushed as dword!
	invoke p4 ptr [ebx], ds::ax		;regs pushed as dword!
	invoke p5 ptr [ebx], ax			;regs pushed as word!
	invoke p6 ptr [ebx], ds::ax		;regs pushed as dword!

	END
