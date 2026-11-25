.386
.model flat
option casemap:none
value = 1
.data
 db value
namespace Late
value = 7
namespace Child
value = 9
 db value,::value,Late::value
endnamespace
endnamespace
namespace Late
value = value+1
 db value,Child::value
endnamespace
 db value
end
