option casemap:none
option stackbase:rsp
option win64:15
option frame:auto
ExitProcess proto :dword
First proto (dword)
Second proto (dword)
FirstArg proto (dword) :dword
SecondArg proto (dword) :dword
Check proto (dword) :dword,:dword
FloatFirst proto (real8) :dword
FloatSecond proto (real8) :dword
CheckFloat proto (dword) :real8,:real8
.data
f1 real8 1.5
f2 real8 2.5
.code
First proc
 mov ecx,111
 mov edx,222
 mov eax,11
 ret
First endp
Second proc
 mov ecx,333
 mov edx,444
 mov eax,22
 ret
Second endp
FirstArg proc p:dword
 mov ecx,111
 mov edx,222
 mov eax,11
 ret
FirstArg endp
SecondArg proc p:dword
 mov ecx,333
 mov edx,444
 mov eax,22
 ret
SecondArg endp
Check proc a:dword,b:dword
 cmp a,11
 jne bad
 cmp b,22
 jne bad
 xor eax,eax
 ret
bad:
 mov eax,1
 ret
Check endp
FloatFirst proc p:dword
 movsd xmm0,f1
 ret
FloatFirst endp
FloatSecond proc p:dword
 movsd xmm0,f2
 ret
FloatSecond endp
CheckFloat proc a:real8,b:real8
 movsd xmm4,a
 ucomisd xmm4,f1
 jne bad
 movsd xmm4,b
 ucomisd xmm4,f2
 jne bad
 xor eax,eax
 ret
bad:
 mov eax,1
 ret
CheckFloat endp
Start proc frame
 mov ecx,11
Check(FirstArg(0),SecondArg(0))
 invoke ExitProcess,eax
 ret
Start endp
end
