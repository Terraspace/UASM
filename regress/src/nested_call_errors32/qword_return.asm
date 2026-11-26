.386
.model flat,stdcall
Wide proto (qword)
Sink proto :qword
.code
Caller proc
 Sink(Wide())
 ret
Caller endp
end
