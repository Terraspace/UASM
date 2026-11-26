option casemap:none

option stackbase:rsp
option win64:15
Known proto (dword) :dword
Unknown proto
Nothing proto (void)
Sink proto :dword,:dword
.code
option frame:noauto
Caller proc frame
 Sink(Known(1),1)
 ret
Caller endp
end
