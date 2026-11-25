.386
.model flat
option casemap:none
value = 1
.data
namespace Helpers
Emit macro
 db value
 value = value+1
 db value
endm
endnamespace
namespace Left
value = 3
 ::Helpers::Emit
endnamespace
namespace Right
value = 8
 ::Helpers::Emit
endnamespace
namespace Left
 ::Helpers::Emit
endnamespace
 db ::value
end
