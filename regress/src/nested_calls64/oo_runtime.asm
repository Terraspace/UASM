option casemap:none
option stackbase:rsp
option frame:auto
option win64:15
option arch:sse
option vtable:on
ExitProcess proto (void) :dword
Normal proto (real4) :real4
IntValue proto (dword)
Identity proto (dword) :dword
namespace Objects
CLASS Counter
 CSTATIC Twice
 CMETHOD Calc
 CMETHOD Sum
ENDMETHODS
 value dword 0
ENDCLASS
STATICMETHOD Counter,Twice,<dword>,<>, value:dword
 mov eax,value
 add eax,eax
 ret
ENDMETHOD
METHOD Counter,Calc,<real4>,<>, value:real4
 movss xmm0,value
 addss xmm0,value
 ret
ENDMETHOD
METHOD Counter,Sum,<real4>,<>, a0:real4,a1:real4
 movss xmm0,a0
 addss xmm0,a1
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
.data
one real4 1.0
three real4 3.0
four real4 4.0
five real4 5.0
.code
Normal proc value:real4
 movss xmm0,value
 addss xmm0,one
 ret
Normal endp
IntValue proc
 mov eax,21
 ret
IntValue endp
Identity proc value:dword
 mov eax,value
 ret
Identity endp
Start proc frame uses r15
 LOCAL obj:Objects::Counter,object:ptr Objects::Counter
 lea rax,Objects::_statCountervtbl
 mov obj.pVtbl,rax
 lea rax,obj
 mov object,rax
 object->Calc(object->Calc(1.0))
 ucomiss xmm0,four
 jne failed
 Normal(object->Calc(1.0))
 ucomiss xmm0,three
 jne failed
 object->Calc(Normal(1.0))
 ucomiss xmm0,four
 jne failed
 object->Sum(object->Calc(1.0),Normal(2.0))
 ucomiss xmm0,five
 jne failed
 Identity(Objects::Counter.Twice(21))
 cmp eax,42
 jne failed
 Objects::Counter.Twice(IntValue())
 cmp eax,42
 jne failed
 Objects::Counter.Twice(Objects::Counter.Twice(1))
 cmp eax,4
 jne failed
 invoke ExitProcess,0
failed:
 invoke ExitProcess,1
 ret
Start endp
end
