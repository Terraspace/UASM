.x64
option casemap:none
option stackbase:rsp
option win64:11

.data
symbol1 db "Hello world"
symbol2 db 1,2,3
symbol3 db 4

symbol4 dw 0x10
symbol5 dd 0x20
symbol6 dq 0x30

afloat REAL4 2.2
adbl REAL8 3.3

mystruct struct
  aa db ?
  bb dw ?
  cc dd ?
  sdd dq ?
mystruct ends

align 16
struct1 mystruct <>

SomeOtherProc proto avar:DWORD, bvar:WORD

.code

mainCRTStartup proc frame
  mov eax,1
  sub eax,1
  invoke SomeOtherProc,1,2
  ret
mainCRTStartup endp

SomeOtherProc proc frame avar:DWORD, bvar:WORD
	LOCAL bob:QWORD
	LOCAL op:mystruct
	db 0x90
	mov bob,rcx
	mov eax,avar
	mov bx,bvar

	ret
SomeOtherProc endp

dataInCode dd 22

CONTEXT struct
Rip_ dq ?
CONTEXT ends

exchdl proc pRecord:ptr, ulframe:qword, pContext:ptr, x4:ptr
    add qword ptr [r8].CONTEXT.Rip_, 1  ;1=size of "in EAX, DX" opcode
    mov eax, 0  ;0=continue execution?
    ret
exchdl endp

align 16
VMwareInstalled proc FRAME:exchdl
    mov eax, 0564D5868h
    mov ebx, 08685D465h
    mov ecx, 10
    mov dx, 05658h
    in eax, dx
    cmp ebx, 564D5868h
    setz al
    movzx eax,al
    ret
VMwareInstalled endp
END
