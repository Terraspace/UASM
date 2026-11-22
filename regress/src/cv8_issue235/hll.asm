my MACRO cond:REQ
 .IF cond
 nop
 .ENDIF
ENDM
.code
 mov eax,ebx
 my eax==1
 add eax,ecx
 nop
end
