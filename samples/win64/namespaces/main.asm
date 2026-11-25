; UASM experimental namespace tour. Build with build.cmd in a VS x64 prompt.
include api.inc
option vtable:on
include counter.inc

bias equ 1
namespace Helpers
; Unqualified bias resolves at the expansion site, not where this macro lives.
ApplyBias macro target
 add target,bias
endm
endnamespace
namespace Demo
bias equ 3
namespace Details
CheckBias proto (dword)
.code
CheckBias proc
 mov eax,10
 ::Helpers::ApplyBias eax
 add eax,::bias
 ret
CheckBias endp
endnamespace
endnamespace

namespace Console
.data
success db "PASS: namespaces, nested scopes, macro lookup, OO, cross-module INVOKE and Win64 frames",13,10
success_size equ $-success
failure db "FAIL: namespace sample",13,10
failure_size equ $-failure
.code
Print proc message:ptr,byteCount:dword
 LOCAL written:dword
 invoke Win32::GetStdHandle,-11
 invoke Win32::WriteFile,rax,message,byteCount,ADDR written,0
 ret
Print endp
endnamespace

.code
public Start
Start proc frame uses rbx rsi rdi r15
 LOCAL pair:Model::Pair
 LOCAL obj:Objects::Counter
 LOCAL counterPtr:ptr Objects::Counter

 mov pair.first,5
 mov pair.second,7
 ; High-level call syntax retains namespace qualification when emitting INVOKE.
 Services::ComputeTotal(pair.first,pair.second)
 cmp eax,24
 jne failed

 invoke Demo::Details::CheckBias
 cmp eax,14
 jne failed

 Objects::Counter.NextValue(40)
 cmp eax,41
 jne failed
 ; Initialize the stack object's vtable, then call its instance method.
 lea rax,Objects::_statCountervtbl
 mov obj.pVtbl,rax
 mov obj.value,42
 lea rax,obj
 mov counterPtr,rax
 counterPtr->GetValue()
 cmp eax,42
 jne failed

 Console::Print(&Console::success,Console::success_size)
 invoke Win32::ExitProcess,0
failed:
 Console::Print(&Console::failure,Console::failure_size)
 invoke Win32::ExitProcess,1
Start endp
end




