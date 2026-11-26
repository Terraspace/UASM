; Namespace delimiters are member names inside STRUCT/STRUC/UNION.
.386
.model flat
option casemap:none
IShellDispatch STRUCT
 QueryInterface dd ?
 AddRef dd ?
 Release dd ?
 GetTypeInfoCount dd ?
 GetTypeInfo dd ?
 GetIDsOfNames dd ?
 Invoke_ dd ?
 get_Application dd ?
 get_Parent dd ?
 NameSpace dd ?
 BrowseForFolder dd ?
IShellDispatch ENDS
Pair STRUC
 namespace word ?
 endnamespace word ?
Pair ENDS
Overlay UNION
 namespace dword ?
 endnamespace Pair <>
Overlay ENDS
EmitFields macro
 NameSpace byte ?
 EndNameSpace word ?
endm
Generated STRUCT
 EmitFields
Generated ENDS
Typed STRUCT
 namespace Pair <>
 endnamespace Overlay <>
Typed ENDS
.errnz IShellDispatch.NameSpace-36
.errnz sizeof IShellDispatch-44
.errnz Pair.endnamespace-2
.errnz Overlay.namespace
.errnz Overlay.endnamespace
.errnz Generated.EndNameSpace-1
.errnz Typed.endnamespace-4
.data
obj IShellDispatch <>
value Typed <>
.code
mov eax,obj.NameSpace
mov ax,value.namespace.endnamespace
mov eax,value.endnamespace.namespace
mov ecx,IShellDispatch.NameSpace
; A genuine namespace must still work after leaving every type.
namespace Live
answer equ 42
endnamespace
mov eax,Live::answer
end
