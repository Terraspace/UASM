.386
.model flat
option casemap:none
.data
 dd OFFSET Future::item
namespace Future
item dd 1234h
endnamespace
 dd OFFSET ::Future::item
end
