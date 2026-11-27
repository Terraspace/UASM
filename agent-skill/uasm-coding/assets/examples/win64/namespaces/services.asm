include api.inc

; These two private functions deliberately have identical leaf names.
namespace Arithmetic
namespace Plain
.code
Calculate proc first:dword,second:dword
 mov eax,first
 add eax,second
 ret
Calculate endp
endnamespace
namespace Scaled
.code
Calculate proc first:dword,second:dword
 invoke ::Arithmetic::Plain::Calculate,first,second
 add eax,eax
 ret
Calculate endp
endnamespace
endnamespace

; Reopen the namespace declared in api.inc. PUBLIC exports the ordinary
; linker spelling ComputeTotal; the source spelling is Services::ComputeTotal.
namespace Services
public ComputeTotal
.code
ComputeTotal proc first:dword,second:dword
 Arithmetic::Scaled::Calculate(first,second)
 ret
ComputeTotal endp
endnamespace
end
