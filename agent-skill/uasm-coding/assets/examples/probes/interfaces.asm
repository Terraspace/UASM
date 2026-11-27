; Self-contained COM/RAW dispatch and typed result checks. Exit status 0 = pass.
option casemap:none
option stackbase:rsp
option win64:15
option frame:auto
option vtable:on
ExitProcess proto :dword
Identity proto (dword) :dword
namespace Contracts
COMINTERFACE IExample
 CVIRTUAL One, <DWORD>, :DWORD
 CVIRTUAL Sum, <DWORD>, :DWORD,:DWORD
ENDCOMINTERFACE
RAWINTERFACE RawOps
 STDFUNC Value, <DWORD>, :DWORD
 STDFUNC AddValues, <DWORD>, :DWORD,:DWORD
 STDFUNC Wide, <QWORD>, :QWORD
 STDFUNC FloatValue, <REAL4>, :REAL4
 STDFUNC Five, <QWORD>, :QWORD,:QWORD,:QWORD,:QWORD,:QWORD
ENDRAWINTERFACE
PRaw TYPEDEF PTR RawOps
endnamespace
UseRaw proto (dword) :ptr Contracts::RawOps
.data
instance Contracts::IExample <0>
PExample TYPEDEF PTR Contracts::IExample
pObject PExample 0
ops Contracts::RawOps <0,0,0,0,0>
pOps Contracts::PRaw 0
iid dd 1,0,0,0
outObject dq 0
wideResult dq 0
floatResult real4 0.0
oneFloat real4 1.0
bad dd 0
.code
QueryImpl proc
 lea rax,instance
 cmp rcx,rax
 jne badQuery
 lea rax,iid
 cmp rdx,rax
 jne badQuery
 lea rax,instance
 mov [r8],rax
 xor eax,eax
 ret
badQuery:
 mov eax,80004002h
 ret
QueryImpl endp
OneImpl proc
 mov eax,edx
 ret
OneImpl endp
SumImpl proc
 mov eax,edx
 add eax,r8d
 ret
SumImpl endp
ValueImpl proc
 mov eax,ecx
 ret
ValueImpl endp
AddImpl proc
 mov eax,ecx
 add eax,edx
 ret
AddImpl endp
WideImpl proc
 mov rax,rcx
 ret
WideImpl endp
FloatImpl proc
 ret
FloatImpl endp
FiveImpl proc a0:qword,a1:qword,a2:qword,a3:qword,a4:qword
 mov rax,a0
 add rax,a1
 add rax,a2
 add rax,a3
 add rax,a4
 ret
FiveImpl endp
Identity proc value:dword
 mov eax,value
 ret
Identity endp
UseRaw proc rawArg:ptr Contracts::RawOps
 rawArg->Value(7)
 ret
UseRaw endp
Start proc frame uses rbx rsi rdi r15
 LOCAL localRaw:Contracts::PRaw,directRaw:ptr Contracts::RawOps
 lea rax,Contracts::_statIExamplevtbl
 mov instance.pVtbl,rax
 lea rax,QueryImpl
 mov Contracts::_statIExamplevtbl.QueryInterface,rax
 lea rax,OneImpl
 mov Contracts::_statIExamplevtbl.One,rax
 lea rax,SumImpl
 mov Contracts::_statIExamplevtbl.Sum,rax
 lea rax,instance
 mov pObject,rax
 pObject->One(0)
 test eax,eax
 jne failed
 pObject->One(7)
 cmp eax,7
 jne failed
 Identity(pObject->One(9))
 cmp eax,9
 jne failed
 pObject->Sum(pObject->One(1),pObject->One(2))
 cmp eax,3
 jne failed
 pObject->QueryInterface(ADDR iid,ADDR outObject)
 test eax,eax
 jne failed
 mov rax,outObject
 cmp rax,pObject
 jne failed
 _VINVOKE pObject,Contracts::IExample,One,7
 cmp eax,7
 jne failed
 mov ebx,_V(pObject,Contracts::IExample,One,9)
 cmp ebx,9
 jne failed
 lea rax,ValueImpl
 mov ops.Value,rax
 lea rax,AddImpl
 mov ops.AddValues,rax
 lea rax,WideImpl
 mov ops.Wide,rax
 lea rax,FloatImpl
 mov ops.FloatValue,rax
 lea rax,FiveImpl
 mov ops.Five,rax
 lea rax,ops
 mov pOps,rax
 mov localRaw,rax
 mov directRaw,rax
 localRaw->Value(7)
 cmp eax,7
 jne failed
 directRaw->Value(9)
 cmp eax,9
 jne failed
 UseRaw(pOps)
 cmp eax,7
 jne failed
 Identity(localRaw->Value(7))
 cmp eax,7
 jne failed
 localRaw->AddValues(pOps->Value(7),directRaw->Value(8))
 cmp eax,15
 jne failed
 mov wideResult,localRaw->Wide(1122334455667788h)
 mov rax,1122334455667788h
 cmp wideResult,rax
 jne failed
 movss floatResult,localRaw->FloatValue(1.0)
 movss xmm0,floatResult
 ucomiss xmm0,oneFloat
 jne failed
 localRaw->Five(1,2,3,4,5)
 cmp rax,15
 jne failed
 ; Typed-memory target must survive float-immediate materialization in RAX.
 mov rax,pOps
 movss floatResult,[rax].Contracts::RawOps->FloatValue(1.0)
 movss xmm0,floatResult
 ucomiss xmm0,oneFloat
 jne failed
 mov rbx,pOps
 assume rbx:ptr Contracts::RawOps
 Identity(rbx->Value(7))
 cmp eax,7
 jne failed
 Identity([rbx].Contracts::RawOps->Value(8))
 cmp eax,8
 jne failed
 assume rbx:nothing
 invoke ExitProcess,0
failed:
 invoke ExitProcess,1
 ret
Start endp
end
