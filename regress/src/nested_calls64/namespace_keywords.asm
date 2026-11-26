; RAW and COM method names, global dot access and RSP/RBP local/parameter names.
option casemap:none
option stackbase:rsp
option win64:15
option frame:auto
option vtable:on
namespace Contracts
RAWINTERFACE RawOps
 STDFUNC NameSpace, <DWORD>, :DWORD
 STDFUNC EndNameSpace, <DWORD>, :DWORD
ENDRAWINTERFACE
PRaw typedef ptr RawOps
COMINTERFACE ObjectOps
 CVIRTUAL NameSpace, <DWORD>, :DWORD
 CVIRTUAL EndNameSpace, <DWORD>, :DWORD
ENDCOMINTERFACE
PObject typedef ptr ObjectOps
endnamespace
.data
ops Contracts::RawOps <0,0>
pOps Contracts::PRaw 0
obj Contracts::ObjectOps <0>
pObj Contracts::PObject 0
.code
mov rax,ops.NameSpace
mov rax,ops.EndNameSpace
Read64 proto (dword) namespace:dword,endnamespace:dword
Read64 proc namespace:dword,endnamespace:dword
 mov eax,namespace
 add eax,endnamespace
 ret
Read64 endp
CallMembers proc frame
 LOCAL namespace:Contracts::PRaw,endnamespace:Contracts::PObject
 lea rax,ops
 mov namespace,rax
 lea rax,obj
 mov endnamespace,rax
 pOps->NameSpace(7)
 pOps->EndNameSpace(8)
 namespace->NameSpace(9)
 namespace->EndNameSpace(10)
 pObj->NameSpace(11)
 pObj->EndNameSpace(12)
 endnamespace->NameSpace(13)
 endnamespace->EndNameSpace(14)
 ret
CallMembers endp
option stackbase:rbp
ReadRbp proc namespace:qword,endnamespace:qword
 mov rax,namespace
 add rax,endnamespace
 ret
ReadRbp endp
ReadLocalRbp proc
 LOCAL namespace:qword,endnamespace:qword
 mov namespace,15
 mov endnamespace,16
 mov rax,namespace
 add rax,endnamespace
 ret
ReadLocalRbp endp
namespace After
marker equ 77
endnamespace
mov eax,After::marker
end
