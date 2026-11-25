option casemap:none
option literals:on
Target proto :ptr
.data
__ls43309 db 77
.code
invoke Target,"A"
namespace One
invoke Target,"a"
namespace Child
invoke Target,"A"
endnamespace
endnamespace
namespace Two
Target("a")
endnamespace
end
