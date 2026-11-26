option sysvhome:0
Child proto SYSTEMV (dword)
Sink proto SYSTEMV :dword,:dword
.code
Caller proc SYSTEMV value:dword
 Sink(Child(),value)
 ret
Caller endp
end
