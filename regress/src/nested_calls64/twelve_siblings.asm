option frame:auto
option stackbase:rsp
option win64:15
Get proto (dword)
Sink proto :dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword
.code
Caller proc frame
 Sink(Get(),Get(),Get(),Get(),Get(),Get(),Get(),Get(),Get(),Get(),Get(),Get())
 ret
Caller endp
end
