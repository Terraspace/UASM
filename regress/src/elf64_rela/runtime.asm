option casemap:none
.data
String byte "0123456789"
pointer_value dq String+1
.code
public _start
_start:
 mov rdx,1
 mov al,String[rdx]
 cmp al,'1'
 jne failed
 mov al,String[1][rdx]
 cmp al,'2'
 jne failed
 xor edi,edi
 jmp finish
failed:
 mov edi,1
finish:
 mov eax,60
 syscall
end
