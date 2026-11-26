option casemap:none
option stackbase:rsp
option win64:15
option frame:auto
Child proto (dword)
CLASS Counter
 CSTATIC NextValue
ENDMETHODS
ENDCLASS
STATICMETHOD Counter,NextValue,<dword>,<>, value:dword
 mov eax,value
 ret
ENDMETHOD
METHOD Counter,Init,<qword>,<>
 mov rax,rcx
 ret
ENDMETHOD
METHOD Counter,Destroy,<VOIDARG>,<>
 ret
ENDMETHOD
.code
Caller proc frame
 Counter.NextValue(Child())
 ret
Caller endp
end
