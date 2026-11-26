option casemap:none
option sysvhome:1


exit proto SYSTEMV :dword
First proto SYSTEMV (dword)
Second proto SYSTEMV (dword)
FirstArg proto SYSTEMV (dword) :dword
SecondArg proto SYSTEMV (dword) :dword
Check proto SYSTEMV (dword) :dword,:dword
FloatFirst proto SYSTEMV (real8) :dword
FloatSecond proto SYSTEMV (real8) :dword
CheckFloat proto SYSTEMV (dword) :real8,:real8
.data
f1 real8 1.5
f2 real8 2.5
.code
public main
First proc SYSTEMV
 mov edi,111
 mov esi,222
 mov ecx,111
 mov edx,222
 mov eax,11
 ret
First endp
Second proc SYSTEMV
 mov edi,333
 mov esi,444
 mov ecx,333
 mov edx,444
 mov eax,22
 ret
Second endp
FirstArg proc SYSTEMV p:dword
 mov edi,111
 mov esi,222
 mov ecx,111
 mov edx,222
 mov eax,11
 ret
FirstArg endp
SecondArg proc SYSTEMV p:dword
 mov edi,333
 mov esi,444
 mov ecx,333
 mov edx,444
 mov eax,22
 ret
SecondArg endp
Check proc SYSTEMV a:dword,b:dword
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
FloatFirst proc SYSTEMV p:dword
 movsd xmm0,f1
 ret
FloatFirst endp
FloatSecond proc SYSTEMV p:dword
 movsd xmm0,f2
 ret
FloatSecond endp
CheckFloat proc SYSTEMV a:real8,b:real8
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
main proc SYSTEMV
 mov ecx,11
Check(First(),Second())
 invoke exit,eax
 ret
main endp
end
