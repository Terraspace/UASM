option frame:auto
option stackbase:rsp
option win64:15
Read proto (dword) :ptr
Sink proto :dword
.data
value dd 42
.code
Caller proc frame
 Sink(Read(&value))
 ret
Caller endp
end
