option casemap:none
.386
.model flat,stdcall
option literals:on
Target proto :ptr
.data
.code
invoke Target,""
invoke Target,"A"
invoke Target,"a"
invoke Target,"a""b"
invoke Target,"a\nb\rc\td"
invoke Target,"\0\q\\"
invoke Target,"arginvoke(%%,%%,(((,)))"
invoke Target,L""
invoke Target,L"A"
invoke Target,L"Kuća😀"
invoke Target,L"a\nb\rc\td"
invoke Target,L"a""b"
invoke Target,"A"
end
