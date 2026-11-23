option casemap:none
option elfpic:1
.code
first:
 call later
 jmp later
later:
 ret
public later
end
