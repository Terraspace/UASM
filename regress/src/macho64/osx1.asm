
_printf proto systemv :PTR, :VARARG

.data

_str db "Hello world!",10,0

.code

_main:
	push rbp
	mov rbp,rsp
	lea rdi,_str
	xor al,al
	call _printf
	pop rbp
	mov eax,0x2000001
	syscall

end _main
