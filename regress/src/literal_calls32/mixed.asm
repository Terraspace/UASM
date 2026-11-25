.386
.model flat,stdcall
option casemap:none
option literals:on
PText typedef ptr byte
First proto :ptr,:dword
Last proto :dword,:PText
Varargs proto C :dword,:vararg
.data
.code
invoke First,"Hello",123
First("Hello",123)
invoke Last,456,"World"
Last(456,"World")
invoke Varargs,1,"Hello",L"World"
end
