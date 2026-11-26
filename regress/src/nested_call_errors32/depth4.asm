option casemap:none
.386
.model flat,stdcall
Fn proto (dword) :dword
.code
Caller proc 
 Fn(Fn(Fn(Fn(1))))
 ret
Caller endp
end
