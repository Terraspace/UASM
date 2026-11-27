option casemap:none
option literals:on
option stackbase:rsp
option win64:15
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
 invoke Target,CStr("Error")
 invoke Target,CStr("Error")
 invoke Target,WStr("Error")
 invoke Target,WStr("Error")
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
