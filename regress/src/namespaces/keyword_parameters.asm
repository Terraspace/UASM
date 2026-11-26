; Header parameters, body locals, macro expansion and subsequent scope changes.
.386
.model flat,stdcall
option casemap:none
Read proto namespace:dword,endnamespace:dword
.code
jmp tail
Read proc namespace:dword,endnamespace:dword
 mov eax,namespace
 add eax,endnamespace
 ret
Read endp
ReadLocals proc
 LOCAL namespace:dword,endnamespace:dword
 mov namespace,7
 mov endnamespace,9
 mov eax,namespace
 add eax,endnamespace
 ret
ReadLocals endp
ReadMacro macro target
 mov target,namespace
 add target,endnamespace
endm
ReadExpanded proc namespace:dword,endnamespace:dword
 ReadMacro eax
 ret
ReadExpanded endp
 db 160 dup(90h)
tail:
 invoke Read,3,4
namespace After
answer equ 55
endnamespace
mov eax,After::answer
end
