.386
.model flat,c
option casemap:none
alias_name textequ <actual_name>
.data
reference dd later_name
.code
Forward proc later_name:dword
 LOCAL alias_name:dword
 mov eax,later_name
 mov actual_name,eax
 ret
Forward endp
.data
later_name dd 7
.code
 mov eax,later_name
end
