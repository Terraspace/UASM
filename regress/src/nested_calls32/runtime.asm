.386
.model flat,stdcall
option casemap:none
ExitProcess proto :dword
First proto (dword)
Second proto (dword)
Identity proto (dword) :dword
Check proto (dword) :dword,:dword
.code
First proc
 mov ecx,123
 mov edx,456
 mov eax,11
 ret
First endp
Second proc
 mov ecx,789
 mov edx,987
 mov eax,22
 ret
Second endp
Identity proc value:dword
 mov eax,value
 ret
Identity endp
Check proc a0:dword,a1:dword
 cmp a0,11
 jne bad
 cmp a1,22
 jne bad
 xor eax,eax
 ret
bad:
 mov eax,1
 ret
Check endp
Start proc
 Check(Identity(First()),Second())
 invoke ExitProcess,eax
 ret
Start endp
end
