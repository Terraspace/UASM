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
CheckSix proto (dword) :dword,:dword,:dword,:dword,:dword,:dword
Fifth proto (dword)
Sixth proto (dword) :dword,:dword,:dword,:dword,:dword,:dword
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
Fifth proc
 mov eax,55
 ret
Fifth endp
Sixth proc a0:dword,a1:dword,a2:dword,a3:dword,a4:dword,a5:dword
 mov eax,66
 ret
Sixth endp
CheckSix proc a0:dword,a1:dword,a2:dword,a3:dword,a4:dword,a5:dword
 cmp a4,55
 jne bad
 cmp a5,66
 jne bad
 xor eax,eax
 ret
bad:
 mov eax,1
 ret
CheckSix endp
Start proc frame
 mov ecx,11
CheckSix(1,2,3,4,Fifth(),Sixth(1,2,3,4,999,888))
 invoke ExitProcess,eax
 ret
Start endp
end
