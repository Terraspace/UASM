option casemap:none
option elfpic:1
extern imported:proc
extern hidden_import:proc
option elfvisibility:hidden_import:hidden
public entry_point, exported, hidden_fn, protected_fn
option elfvisibility:hidden_fn:hidden
option elfvisibility:protected_fn:protected
.code
entry_point:
 call imported
 call imported+3
 call hidden_import
 call exported
 call hidden_fn
 call protected_fn
 call private_fn
 jmp imported
exported:
 mov eax,11
 ret
hidden_fn:
 mov eax,12
 ret
protected_fn:
 mov eax,13
 ret
private_fn:
 mov eax,14
 ret
backwards:
 call exported
 jmp exported
end
