.386
.model flat
option casemap:none
.code
namespace Ns
DoNop macro
 nop
endm
EntryPoint:: DoNop
Other::
 ret
endnamespace
 call Ns::EntryPoint
 call Ns::Other
end
