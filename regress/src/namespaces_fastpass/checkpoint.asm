.386
.model flat
option casemap:none
value = 1
.data
namespace Outer
value = 10
namespace Inner
value = 20
 db value,Outer::value,::value
value = value+1
 db value
endnamespace
value = value+2
 db value
endnamespace
 db value
namespace Outer
namespace Inner
 db value
endnamespace
endnamespace
end
