; Bounded typed C-style calls. Build with build.cmd in a VS x64 prompt.
option casemap:none
option frame:auto
option stackbase:rsp
option win64:15
option arch:sse

ExitProcess proto (void) :dword
GetStdHandle proto (ptr) :dword
WriteFile proto (dword) :ptr,:ptr,:dword,:ptr,:ptr
NextValue proto (dword)
DoubleValue proto (dword) :dword
Sum proto (dword) :dword,:dword
Reenter proto (dword)
LeftReal proto (real8)
RightReal proto (real8)
AddReal proto (real8) :real8,:real8
ObjectAddress proto (ptr)
ReadValue proto (dword) :ptr
Print proto (void) :ptr,:dword

Pair struct
 first dword ?
 second dword ?
Pair ends
.data
counter dword 0
pairData Pair <42,7>
leftValue real8 1.5
rightValue real8 2.5
expectedReal real8 4.0
success db "PASS: typed nested calls, sibling results, re-entry, pointers and floats",13,10
successSize equ $-success
failure db "FAIL: nested-call sample",13,10
failureSize equ $-failure
.code

NextValue proc
 inc counter
 mov eax,counter
 ; These volatile registers are deliberately destroyed.
 mov ecx,111
 mov edx,222
 ret
NextValue endp

DoubleValue proc value:dword
 mov eax,value
 add eax,eax
 ret
DoubleValue endp

Sum proc first:dword,second:dword
 LOCAL result:dword
 mov eax,first
 add eax,second
 mov result,eax
 ret
Sum endp

Reenter proc
 ; This call has its own temporary result slots in this activation's frame.
 Sum(NextValue(),NextValue())
 ret
Reenter endp

LeftReal proc
 movsd xmm0,leftValue
 ret
LeftReal endp
RightReal proc
 movsd xmm0,rightValue
 ret
RightReal endp
AddReal proc first:real8,second:real8
 LOCAL result:real8
 movsd xmm0,first
 addsd xmm0,second
 movsd result,xmm0
 ret
AddReal endp

ObjectAddress proc
 lea rax,pairData
 ret
ObjectAddress endp
ReadValue proc object:ptr
 mov rax,object
 mov eax,[rax].Pair.first
 ret
ReadValue endp

Print proc message:ptr,byteCount:dword
 LOCAL written:dword
 ; An explicitly typed external return is usable as a nested argument.
 WriteFile(GetStdHandle(-11),message,byteCount,ADDR written,0)
 ret
Print endp

public Start
Start proc frame
 LOCAL integerTotal:dword,reentryTotal:dword,pointerValue:dword
 LOCAL floatingTotal:real8
 mov counter,0
 ; Three calls deep; leaf calls execute from left to right: 1 + (2 * 2).
 Sum(NextValue(),DoubleValue(NextValue()))
 mov integerTotal,eax
 cmp eax,5
 jne failed

 mov counter,0
 ; Outer result 1 survives the nested work in Reenter (2 + 3).
 Sum(NextValue(),Reenter())
 mov reentryTotal,eax
 cmp eax,6
 jne failed

 AddReal(LeftReal(),RightReal())
 movsd floatingTotal,xmm0
 ucomisd xmm0,expectedReal
 jne failed

 ReadValue(ObjectAddress())
 mov pointerValue,eax
 cmp eax,42
 jne failed

 ; Break here to inspect integerTotal=5, reentryTotal=6,
 ; floatingTotal=4.0 and pointerValue=42 in Visual Studio.
 Print(ADDR success,successSize)
 ExitProcess(0)
failed:
 Print(ADDR failure,failureSize)
 ExitProcess(1)
 ret
Start endp

; Rejected examples (copy one into Start to see its diagnostic):
; Sum(NextValue(),eax)          ; EAX may be overwritten by NextValue.
; Sum(NextValue(),[rcx])        ; Address depends on a volatile register.
; DoubleValue(DoubleValue(DoubleValue(NextValue()))) ; Depth four.
; Sum(Print(ADDR success,successSize),1) ; VOID is not a value.
end
