; Hand-calculated bytes: 1,2,3,2,1,2,4,5,6,2,7,8.
.386
.model flat
option casemap:none
.data
value equ 1
namespace Alpha
value equ 2
Emit macro
 db value
endm
namespace Beta
value equ 3
 db ::value,Alpha::value,value
endnamespace
namespace Gamma
 db value,::value,Alpha::value
endnamespace
endnamespace
namespace Other
value equ 4
::Alpha::Emit
namespace Alpha
value equ 5
namespace Beta
value equ 6
endnamespace
endnamespace
 db Alpha::value,Alpha::Beta::value,::Alpha::value
endnamespace
namespace Alpha
namespace Beta
value2 equ 7
endnamespace
endnamespace
 db Alpha::Beta::value2
namespace Last
Thing struct
 first dd ?
 second dd ?
Thing ends
endnamespace
 db SIZEOF Last::Thing
end
