option casemap:none
option literals:on
Target proto SYSTEMV :ptr
.data
before db 17
.code
Caller proc SYSTEMV 
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
