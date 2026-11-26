option casemap:none
option stackbase:rsp
option frame:auto
option win64:15
Fn proto (dword) :dword
.code
Caller proc 
 Fn(Fn(Fn(1)))
 ret
Caller endp
end
