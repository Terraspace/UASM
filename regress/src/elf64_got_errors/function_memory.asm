option casemap:none
option elfpic:1
extern function:proc
.code
mov rax,GOT(function,r11)
end
