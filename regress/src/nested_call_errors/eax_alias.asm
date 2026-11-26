option casemap:none
option frame:auto
option stackbase:rsp
option win64:15
Known proto (dword) :dword
Unknown proto
Nothing proto (void)
Sink proto :dword,:dword
.code
Caller proc frame
 Sink(Known(1),ax)
 ret
Caller endp
end
