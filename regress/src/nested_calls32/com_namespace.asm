; Win32 COM uses stdcall and preserves the two explicit QueryInterface arguments.
.686
.model flat,stdcall
option casemap:none
namespace Contracts
COMINTERFACE IExample
 CVIRTUAL One, <(DWORD)>, :DWORD
ENDCOMINTERFACE
endnamespace
.data
PExample typedef ptr Contracts::IExample
objectPtr PExample 0
identifier dd 4 dup(0)
resultPtr dd 0
.code
RunCase proc
 _VINVOKE objectPtr,Contracts::IExample,QueryInterface,ADDR identifier,ADDR resultPtr
 _VINVOKE objectPtr,Contracts::IExample,One,7
 mov ebx,_V(objectPtr,Contracts::IExample,One,9)
 ret
RunCase endp
end
