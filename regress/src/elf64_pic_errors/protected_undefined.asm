option casemap:none
option elfpic:1
extern target:proc
option elfvisibility:target:protected
.code
call target
end
