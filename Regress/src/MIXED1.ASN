
;--- using mixed - 16-bit and 32-bit - code segments

	.286
	.model small
	.386
	.dosseg

	.stack 100h

	.code

	call p16f			;translated to "push cs, call near16 pf16f"
	call far16 ptr p16f	;encoded as far16 call
	call p32f			;encoded as far32 call
	call far32 ptr p32f	;encoded as far32 call
;	dd 0AAh

CGROUP16 group _TEXT, _TEXT2

	.code _TEXT2

	db 33h,33h,33h,33h,33h,33h,33h

p16f proc far
	mov eax, offset p32f
	mov eax, offset p16f
	nop
	push offset p32f
	push offset p16f
	push offset _TEXT32:p32f
	push offset _TEXT2:p16f
	nop
	push seg p16f
	push seg p32f
	nop
	push _TEXT
	push _TEXT2
	push _TEXT32X
	push _TEXT32
	nop
	push CGROUP16
	push CGROUP32
	push DGROUP
	nop
	mov ah,4Ch
	int 21h
p16f endp
	db 0BBh

_TEXT32X segment use32 'CODE'
	db 11h dup (55h)
_TEXT32X ends

CGROUP32 group _TEXT32X, _TEXT32

_TEXT32 segment use32 'CODE'

	db 77h,77h,77h,77h,77h

p32f proc far
	mov eax, offset p32f
	mov eax, offset p16f
	push offset p32f
	push offset p16f
	push offset _TEXT32:p32f
	push offset _TEXT2:p16f
	ret
p32f endp
	db 0AAh

_TEXT32 ends

	end p16f	;start address in 2. segment of a group
