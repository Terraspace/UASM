
;--- PUSH in 64-bit code

ifdef __JWASM__
	.x64
	.model flat
endif

	.data

vsq label sqword
vq	dq 0
vd	dd 0
vw	dw 0
vb	db 0

	.code

main proc

;--- register operands

	push ax
	push r8w
;	push eax
;	push r8d
	push rax
	push r8
	push fs
	push gs

;--- direct memory

	push [vw]
;	push [vd]
	push [vq]
	push [vsq]

;--- indirect memory

	push [ebx]
	push [r8d]
	push [rbx]
	push [r8]
	push word ptr [ebx]
	push word ptr [r8d]
	push word ptr [rbx]
	push word ptr [r8]
	push qword ptr [ebx]
	push qword ptr [r8d]
	push qword ptr [rbx]
	push qword ptr [r8]

	push [ebx+r8d*2]
	push [r8d+r9d*4]
	push [rbx+r9+1]
	push [r8+r10+15]

;--- immediate operand

	push 1
	push 7FFFFFFFh
	push 80000000h
	push 0FFFFFFFEh
	push -1
	push -32768

;--- special

	pushf
	pushfq

main endp

	END
