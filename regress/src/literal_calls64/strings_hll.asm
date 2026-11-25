option casemap:none
option literals:on
Target proto :ptr
.data
.code
Target("")
Target("A")
Target("a")
Target("a""b")
Target("a\nb\rc\td")
Target("\0\q\\")
Target("arginvoke(%%,%%,(((,)))")
Target(L"")
Target(L"A")
Target(L"Kuća😀")
Target(L"a\nb\rc\td")
Target(L"a""b")
Target("A")
end
