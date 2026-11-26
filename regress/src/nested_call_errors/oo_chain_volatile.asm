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
 assume rcx:ptr LongObjectNamespace::Root
 rcx->branch->leaf->AddFloat(FloatIdentity(1.0))
 assume rcx:nothing
 ret
Start endp
end
