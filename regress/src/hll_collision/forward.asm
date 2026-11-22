.386
.model flat
my MACRO cond:REQ
 .IF cond
 nop
 .ENDIF
ENDM
.code
 jmp @C0001
 mov eax,ebx
 my eax==1
 add eax,ecx
@C0001:
 nop
end
