.386
.model flat
option casemap:none
namespace Outer
namespace Inner
value equ 1
endnamespace
endnamespace
namespace LocalScope
namespace Outer
endnamespace
.data
 dd Outer::Inner::value
endnamespace
end
