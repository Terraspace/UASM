.x64
.model flat,fastcall
option casemap:none
option stackbase:rsp
option win64:15
option frame:auto
.data
unused dd 7
used dd 9
.code
Smart proto :dword,:dword
Smart proc unused:dword,used:dword
 mov eax,used
 ret
Smart endp
end
