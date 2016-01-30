
;--- invalid PUSH/POP in 64-bit code

ifdef __JWASM__
	.x64
	.model flat
endif

	.data

vd	dd 0
vb	db 0

	.code

	push eax
	pop eax
	push r8d
	pop r8d

	push vb
	pop vb
	push vd
	pop vd

	push dword ptr [rbx]
	pop dword ptr [rbx]
	push dword ptr [ebx]
	pop dword ptr [ebx]

;--- segment registers: only FS/GS can be pushed/poped
	push ds
	pop ds
	push cs
	pop cs

;--- pushd is invalid in 64-bit
	pushd 1

;--- can't push 64-bit immediates
	push 123456789Ah

	pushfd
	popfd

	END
