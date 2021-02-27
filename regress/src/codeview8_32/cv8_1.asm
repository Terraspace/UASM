.686p
.model flat,stdcall

.data
symbol1 db "Hello world"
symbol2 db 1,2,3
symbol3 db 4

symbol4 dw 0x10
symbol5 dd 0x20
symbol6 dq 0x30

SomeOtherProc proto avar:DWORD, bvar:WORD

.code

mainCRTStartup proc
	LOCAL var1:DWORD
	LOCAL var2:BYTE
	LOCAL var3[4]:WORD
  mov eax,1
  sub eax,1
  invoke SomeOtherProc,1,2
  ret
mainCRTStartup endp

SomeOtherProc proc avar:DWORD, bvar:WORD

	ret
SomeOtherProc endp

END
