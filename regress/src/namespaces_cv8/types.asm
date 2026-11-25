; CV type names retain scope identity but omit the leading source :: operator.
option casemap:none
option stackbase:rsp
option win64:15
option frame:auto
option proc:private
namespace One
Item struct
 value dword ?
Item ends
endnamespace
namespace Two
Item struct
 value qword ?
Item ends
endnamespace
.code
option stackbase:rsp
CheckRsp proc frame
 LOCAL first:One::Item,second:Two::Item,pointer:ptr One::Item
 mov first.value,5
 mov second.value,7
 lea rax,first
 mov pointer,rax
 ret
CheckRsp endp
option stackbase:rbp
CheckRbp proc frame
 LOCAL first:One::Item,second:Two::Item,pointer:ptr Two::Item
 mov first.value,11
 mov second.value,13
 lea rax,second
 mov pointer,rax
 ret
CheckRbp endp
end
