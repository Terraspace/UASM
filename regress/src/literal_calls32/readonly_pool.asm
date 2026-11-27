option casemap:none
option literals:on
.386
.model flat,stdcall
Target proto :ptr
.data
before db 17
.code
Caller proc 
rept 100
 Target("Error")
endm
 Target(L"Error")
 Target(L"Error")
 invoke Target,CSTR("Error")
 invoke Target,CSTR("Error")
 invoke Target,WSTR("Error")
 invoke Target,WSTR("Error")
 ret
Caller endp
namespace Nested
invoke Target,"Error"
endnamespace
.const
marker db 99
.data
after db 34
end

