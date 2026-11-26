option casemap:none
option stackbase:rsp
option win64:15
option frame:auto
option literals:on
namespace Demo
Read proto (dword) :ptr
Sink proto (void) :dword,:dword
Run macro
 Sink(Read("left"),Read(L"right"))
endm
.code
Caller proc frame
 Run
 ret
Caller endp
endnamespace
end
