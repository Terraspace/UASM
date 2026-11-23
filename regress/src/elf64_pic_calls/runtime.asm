option casemap:none
option elfpic:1
option frame:auto
extern supplied:proc
imported proto SYSTEMV
public exported, hidden_fn, protected_fn, call_exported, call_hidden, call_protected, call_supplied, call_imported
option elfvisibility:hidden_fn:hidden
option elfvisibility:protected_fn:protected
.code
exported:
 mov eax,11
 ret
hidden_fn:
 mov eax,12
 ret
protected_fn:
 mov eax,13
 ret
call_exported:
 jmp exported
call_hidden:
 jmp hidden_fn
call_protected:
 jmp protected_fn
call_supplied:
 jmp supplied
call_imported proc SYSTEMV
 invoke imported
 ret
call_imported endp
end
