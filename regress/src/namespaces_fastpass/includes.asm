.386
.model flat
option casemap:none
value = 1
.data
namespace Parent
value = 5
 include before.inc
 db value
 include after.inc
 db value,Child::value
endnamespace
 db value
end
