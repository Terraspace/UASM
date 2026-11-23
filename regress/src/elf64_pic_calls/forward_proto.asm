option casemap:none
option elfpic:1
hidden_proc proto SYSTEMV
protected_proc proto SYSTEMV
option elfvisibility:hidden_proc:hidden
option elfvisibility:protected_proc:protected
.code
start:
 call hidden_proc
 call protected_proc
 ret
hidden_proc proc SYSTEMV
 ret
hidden_proc endp
protected_proc proc SYSTEMV
 ret
protected_proc endp
end
