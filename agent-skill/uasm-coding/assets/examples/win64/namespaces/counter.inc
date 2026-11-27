; A small real OO class, with namespace-qualified static and instance calls.
namespace Objects
CLASS Counter
 CSTATIC NextValue
 CMETHOD GetValue
ENDMETHODS
 value dword 0
ENDCLASS

STATICMETHOD Counter,NextValue,<dword>,<>, inputValue:dword
 mov eax,inputValue
 inc eax
 ret
ENDMETHOD
METHOD Counter,GetValue,<dword>,<>
 mov eax,[rcx].value
 ret
ENDMETHOD
METHOD Counter,Init,<qword>,<>
 mov rax,rcx
 ret
ENDMETHOD
METHOD Counter,Destroy,<VOIDARG>,<>
 ret
ENDMETHOD
endnamespace
