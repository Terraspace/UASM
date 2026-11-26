option stackbase:rsp
option win64:15
option frame:auto
Child proto (dword) :dword
Sink proto :dword,:dword
.code
Caller proc frame
 Sink(Child(ecx),Child(1))
 ret
Caller endp
end
