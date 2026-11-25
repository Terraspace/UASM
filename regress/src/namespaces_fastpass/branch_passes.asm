.386
.model flat
option casemap:none
.code
namespace Outer
namespace Inner
entryLabel:
 jmp target
 db 200 dup (90h)
target:
 mov eax,1
 ret
endnamespace
endnamespace
end
