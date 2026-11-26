Child proto SYSTEMV (dword)
Sink proto SYSTEMV :dword,:dword
.code
Caller proc SYSTEMV
 Sink(Child(),edi)
 ret
Caller endp
end
