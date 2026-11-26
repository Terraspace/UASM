; Namespaced allocation, three-link receiver chains and typed expressions.
option casemap:none
ifdef STACK_RBP
 option stackbase:rbp
else
 option stackbase:rsp
endif
option win64:15
option frame:auto
option vtable:on
GetProcessHeap proto (qword)
HeapAlloc proto (qword) :qword,:dword,:qword
HeapFree proto (dword) :qword,:dword,:qword
ExitProcess proto (void) :dword
FloatIdentity proto (real4) :real4
namespace LongObjectNamespace
.data
made dd 0
gone dd 0
.code
CLASS Leaf
 CMETHOD Value
 CMETHOD Wrapper
 CMETHOD AddValue
 CMETHOD AddFloat
 CMETHOD Sum
 CMETHOD VarValue
ENDMETHODS
 number dword 0
ENDCLASS
METHOD Leaf,Init,<QWORD>,<>,seed:dword
 mov eax,seed
 mov [rcx].number,eax
 inc made
 mov rax,thisPtr
 ret
ENDMETHOD
METHOD Leaf,Destroy,<VOIDARG>,<>
 inc gone
 ret
ENDMETHOD
METHOD Leaf,Value,<DWORD>,<>
 mov eax,[rcx].number
 ret
ENDMETHOD
METHOD Leaf,AddValue,<DWORD>,<>,amount:dword
 mov eax,amount
 add eax,[rcx].number
 ret
ENDMETHOD
METHOD Leaf,AddFloat,<REAL4>,<>,amount:real4
 movss xmm0,amount
 addss xmm0,FP4(1.0)
 ret
ENDMETHOD
METHOD Leaf,Sum,<DWORD>,<>,first:dword,second:dword
 mov eax,first
 add eax,second
 ret
ENDMETHOD
METHOD Leaf,VarValue,<DWORD>,<>,formatPtr:ptr,args:vararg
 mov eax,r8d
 ret
ENDMETHOD
METHOD Leaf,Wrapper,<DWORD>,<USES r15>
 _INVOKE Leaf,AddValue,thisPtr,7
 cmp eax,9
 jne badValue
 mov eax,_I(Leaf,Value,thisPtr)
 cmp eax,2
 jne badValue
 _VINVOKE thisPtr,Leaf,Value
 cmp eax,2
 jne badValue
 mov eax,_V(thisPtr,Leaf,Value)
 ret
badValue:
 mov eax,-1
 ret
ENDMETHOD
CLASS Branch
ENDMETHODS
 leaf psrLeaf 0
ENDCLASS
METHOD Branch,Init,<QWORD>,<USES rsi rdi>
 mov rax,_NEW(Leaf,2)
 mov rcx,thisPtr
 mov [rcx].leaf,rax
 inc made
 mov rax,thisPtr
 ret
ENDMETHOD
METHOD Branch,Destroy,<VOIDARG>,<>
 LOCAL owned:psrLeaf
 mov rax,[rcx].leaf
 mov owned,rax
 .if owned
  _DELETE(owned)
 .endif
 inc gone
 ret
ENDMETHOD
CLASS Root
ENDMETHODS
 branch psrBranch 0
ENDCLASS
METHOD Root,Init,<QWORD>,<USES rbx rsi rdi>
 xor ebx,ebx
 mov rax,_RBXNEW(Branch)
 mov rcx,thisPtr
 mov [rcx].branch,rax
 inc made
 mov rax,thisPtr
 ret
ENDMETHOD
METHOD Root,Destroy,<VOIDARG>,<>
 LOCAL owned:psrBranch
 mov rax,[rcx].branch
 mov owned,rax
 .if owned
  _DELETE(owned)
 .endif
 inc gone
 ret
ENDMETHOD
endnamespace
.data
rootPtr LongObjectNamespace::psrRoot 0
rootTwo LongObjectNamespace::psrRoot 0
.code
FloatIdentity proc value:real4
 movss xmm0,value
 ret
FloatIdentity endp
Start proc frame uses rbx rsi rdi r15
 LOCAL result:real4,leafPtr:LongObjectNamespace::psrLeaf,status:dword
 mov status,1
 mov rootPtr,_NEW(LongObjectNamespace::Root)
 mov rootTwo,_NEW(LongObjectNamespace::Root)
 cmp LongObjectNamespace::made,6
 jne failed
 rootPtr->branch->leaf->Wrapper()
 cmp eax,2
 jne failed
 ; Memory, register and typed-memory receivers; long names must not corrupt tokens.
 rootPtr->branch->leaf->AddValue(7)
 cmp eax,9
 jne failed
 mov rbx,rootPtr
 assume rbx:ptr LongObjectNamespace::Root
 rbx->branch->leaf->Value()
 cmp eax,2
 jne failed
 assume rbx:nothing
 lea rsi,rootPtr
 [rsi].LongObjectNamespace::Root->branch->leaf->AddValue(7)
 cmp eax,9
 jne failed
 mov rax,rootPtr
 mov rax,[rax].LongObjectNamespace::Root.branch
 mov rax,[rax].LongObjectNamespace::Branch.leaf
 mov leafPtr,rax
 mov ebx,_I(LongObjectNamespace::Leaf,Value,leafPtr)
 cmp ebx,2
 jne failed
 ; Chain scratch RCX is generated after nested results; it is not a user operand.
 movss result,rootPtr->branch->leaf->AddFloat(FloatIdentity(1.0))
 movss xmm0,result
 ucomiss xmm0,FP4(2.0)
 jne failed
 rootPtr->branch->leaf->Sum(rootTwo->branch->leaf->Value(),7)
 cmp eax,9
 jne failed
 mov ebx,rootPtr->branch->leaf->Sum(rootTwo->branch->leaf->Value(),7)
 cmp ebx,9
 jne failed
 rootPtr->branch->leaf->VarValue(CSTR("a,b"),7)
 cmp eax,7
 jne failed
 mov status,0
failed:
 .if rootPtr
  _DELETE(rootPtr)
 .endif
 .if rootTwo
  _DELETE(rootTwo)
 .endif
 cmp LongObjectNamespace::gone,6
 je done
 mov status,1
done:
 invoke ExitProcess,status
 ret
Start endp
end
