option stackbase:rsp
option win64:15
option frame:auto
Fn proto (dword)
Sink proto :dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword,:dword
.code
Caller proc
 Sink(1,1,1,1,1,1,1,1,1,Fn())
 ret
Caller endp
end
