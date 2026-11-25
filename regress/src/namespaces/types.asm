.386
.model flat
option casemap:none
namespace One
Item struct
 field dd ?
Item ends
Flags record lowbits:3,highbits:5
ItemAlias typedef Item
text textequ <9>
.data
itemValue Item <1234h>
endnamespace
namespace Two
Item struct
 field dw ?
Item ends
.data
itemValue Item <5678h>
endnamespace
.data
 dd SIZEOF One::Item, SIZEOF Two::Item, SIZEOF One::ItemAlias
 dd MASK One::lowbits, MASK One::highbits
 db One::text
end
