
OPTION LITERALS:ON

_printf proto systemv :PTR, :VARARG
MyFunc  proto

.code

_main:
	sub rsp,8
	invoke MyFunc	
	add rsp,8
	mov eax,0x2000001
	syscall

MyFunc PROC
	invoke _printf, "Hello world!\n"
	ret
MyFunc ENDP

end _main 
