option casemap:none
option prologue:none
option epilogue:none
extern OtherValue:proc
.code
public main
main proc
 push rbp
 mov rbp,rsp
 mov edi,20
 mov esi,22
 call AddValues
 cmp eax,42
 jne failed
 call IncludedValue
 cmp eax,7
 jne failed
 call ColdValue
 cmp eax,9
 jne failed
 call OtherValue
 cmp eax,11
 jne failed
 xor eax,eax
 pop rbp
 ret
failed:
 mov eax,1
 pop rbp
 ret
main endp
AddValues proc
 mov eax,edi
 add eax,esi
 ret
AddValues endp
include dwarf_lines.inc
.code cold
ColdValue proc
 mov eax,9
 ret
ColdValue endp
end
