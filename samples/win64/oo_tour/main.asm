; Self-contained Win64 OO tour. Build with build.cmd in a VS x64 tools prompt.
option casemap:none
ifdef STACK_RBP
 option stackbase:rbp
else
 option stackbase:rsp
endif
option win64:15
option frame:auto
option literals:on
option vtable:on
option arch:sse
; MEMALLOC/MEMFREE resolve these names internally.
GetProcessHeap proto (qword)
HeapAlloc proto (qword) :qword,:dword,:qword
HeapFree proto (dword) :qword,:dword,:qword
namespace Win32
GetStdHandle proto (qword) :dword
WriteFile proto (dword) :qword,:ptr,:dword,:ptr,:ptr
ExitProcess proto (void) :dword
endnamespace
Identity proto (dword) :dword
FloatIdentity proto (real4) :real4

namespace Model
; OINTERFACE has the two constructor/destructor slots used by CLASS.
; This is a layout view, not COM QueryInterface or automatic inheritance.
OINTERFACE Entity
 CVIRTUAL GetAge, <DWORD>
 CVIRTUAL SetAge, <VOIDARG>, :DWORD
ENDMETHODS
ENDOINTERFACE
CLASS Company
 CMETHOD Adjust
ENDMETHODS
 factor real4 1.0
ENDCLASS
METHOD Company, Init, <QWORD>, <>
 mov rax,thisPtr
 ret
ENDMETHOD
METHOD Company, Destroy, <VOIDARG>, <>
 ret
ENDMETHOD
METHOD Company, Adjust, <REAL4>, <>, amount:real4
 movss xmm0,amount
 addss xmm0,[rcx].factor
 ret
ENDMETHOD

CLASS Person
 CMETHOD GetAge
 CMETHOD SetAge
 CMETHOD SetName
 CMETHOD Calc
 CMETHOD Sum
 CMETHOD VectorSum
 CSTATIC IsHuman
ENDMETHODS
 age dword 0
 human dword 1
 nameText dq 0             ; borrowed string; caller keeps it alive
 company psrCompany 0   ; owned Company; released by Destroy
ENDCLASS
METHOD Person, Init, <QWORD>, <USES rsi rdi>, years:dword,namePtr:ptr
 mov eax,years
 mov [rcx].age,eax
 mov rax,namePtr
 mov [rcx].nameText,rax
 ; Company is attached by the owner after allocation.
 mov rax,thisPtr         ; constructor contract: return this, even after calls
 ret
ENDMETHOD
METHOD Person, Destroy, <VOIDARG>, <>
 LOCAL owned:psrCompany
 mov rax,[rcx].company
 mov owned,rax
 .if rax
  _DELETE(owned)         ; LOCAL survives destructor/HeapFree register clobbers
 .endif
 ret
ENDMETHOD
METHOD Person, GetAge, <DWORD>, <>
 mov eax,[rcx].age
 ret
ENDMETHOD
METHOD Person, SetAge, <VOIDARG>, <>, years:dword
 mov eax,years
 mov [rcx].age,eax
 ret
ENDMETHOD
METHOD Person, SetName, <VOIDARG>, <>, textPtr:ptr
 mov rax,textPtr
 mov [rcx].nameText,rax
 ret
ENDMETHOD
METHOD Person, Calc, <REAL4>, <>, amount:real4
 movss xmm0,amount
 addss xmm0,FP4(1.0)
 ret
ENDMETHOD
METHOD Person, Sum, <DWORD>, <>, first:dword,second:dword
 mov eax,first
 add eax,second
 ret
ENDMETHOD
VECMETHOD Person, VectorSum, <XMMWORD>, <>, first:xmmword,second:xmmword
 movups xmm0,xmm1
 addps xmm0,xmm2
 ret
ENDMETHOD
STATICMETHOD Person, IsHuman, <DWORD>, <>, who:ptr Person
 mov rax,who
 mov eax,[rax].Person.human
 ret
ENDMETHOD
endnamespace

.data
person Model::psrPerson 0
PEntity typedef ptr Model::Entity
entView PEntity 0
newName db 'Grace',0
align 16
vecA real4 1.0,2.0,3.0,4.0
vecB real4 4.0,3.0,2.0,1.0
vecOut real4 4 dup(0.0)
passText db 'PASS: namespaces, OO, interfaces, arrows, typed nested calls and vectorcall',13,10
passLength equ $-passText
failText db 'FAIL: OO tour',13,10
failLength equ $-failText
.code
Identity proc value:dword
 mov eax,value
 ret
Identity endp
FloatIdentity proc value:real4
 movss xmm0,value
 ret
FloatIdentity endp

Start proc frame uses rbx rsi rdi r15
 LOCAL other:Model::psrPerson,typedEntity:ptr Model::Entity,employer:Model::psrCompany
 LOCAL result:real4,exitCode:dword,written:dword,output:qword
 mov other,0
 mov exitCode,1
 mov person,_NEW(Model::Person,30,"Ada")
 cmp person,0
 je cleanup
 mov rax,_NEW(Model::Company)
 test rax,rax
 jz cleanup
 mov rcx,person
 mov [rcx].Model::Person.company,rax
 mov other,_NEW(Model::Person,40,"Alan")
 cmp other,0
 je cleanup
 ; Single-character argument; fixed bug used to fail here.
 person->SetAge(7)
 Identity(person->GetAge())
 cmp eax,7
 jne cleanup
 ; Each typed nested result is spilled to the caller's frame before the next call.
 person->Sum(person->GetAge(),other->GetAge())
 cmp eax,47
 jne cleanup
 person->SetAge(Identity(Identity(9))) ; maximum supported depth: three calls
 person->GetAge()
 cmp eax,9
 jne cleanup
 person->Calc(FloatIdentity(1.0))
 movss result,xmm0
 movss xmm0,result
 ucomiss xmm0,FP4(2.0)
 jne cleanup
 ; chained object pointers can also be loaded into a typed LOCAL
 mov rax,person
 mov rax,[rax].Model::Person.company
 mov employer,rax
 employer->Adjust(2.0)
 ucomiss xmm0,FP4(3.0)
 jne cleanup
 ; Direct and vtable legacy helpers also accept namespace-qualified types.
 _INVOKE Model::Person,SetAge,person,7
 _VINVOKE person,Model::Person,SetAge,8
 movss result,_I(Model::Person,Calc,person,1.0)
 movss xmm0,result
 ucomiss xmm0,FP4(2.0)
 jne cleanup
 mov ebx,_V(person,Model::Person,GetAge)
 cmp ebx,8
 jne cleanup
 ; Arrow with an assumed register, then an address of a pointer slot.
 mov rbx,person
 assume rbx:ptr Model::Person
 rbx->GetAge()
 cmp eax,8
 jne cleanup
 lea rbx,person
 [rbx]->GetAge()
 cmp eax,8
 jne cleanup
 assume rbx:nothing
 [rbx].Model::Person->GetAge()
 cmp eax,8
 jne cleanup
 ; Explicit interface view, same first user-method slots as Person.
 mov rax,person
 mov entView,rax
 mov typedEntity,rax
 entView->SetAge(6)
 typedEntity->GetAge()
 cmp eax,6
 jne cleanup
 person->SetName(&newName)
 Model::Person.IsHuman(person)
 cmp eax,1
 jne cleanup
 mov ebx,_STATIC(Model::Person,IsHuman,person)
 cmp ebx,1
 jne cleanup
 ; Direct dispatch is an assembly-time choice, not a change to object layout.
 option vtable:off
 person->SetAge(5)
 person->GetAge()
 cmp eax,5
 jne cleanup
 option vtable:on
 ; SIMD method uses Win64 vectorcall. Memory arguments avoid volatile conflicts.
 person->VectorSum(vecA,vecB)
 movups vecOut,xmm0
 mov eax,40a00000h ; 5.0f
 cmp dword ptr vecOut,eax
 jne cleanup
 cmp dword ptr vecOut[4],eax
 jne cleanup
 cmp dword ptr vecOut[8],eax
 jne cleanup
 cmp dword ptr vecOut[12],eax
 jne cleanup
 ; Debugger checkpoint: inspect person, other, typedEntity, result and vecOut.
 mov exitCode,0
cleanup:
 .if other
  _DELETE(other)
  mov other,0
 .endif
 .if person
  _DELETE(person)
  mov person,0
 .endif
 Win32::GetStdHandle(-11)
 mov output,rax
 .if exitCode == 0
  Win32::WriteFile(output,&passText,passLength,&written,0)
 .else
  Win32::WriteFile(output,&failText,failLength,&written,0)
 .endif
 Win32::ExitProcess(exitCode)
 ret
Start endp
end
