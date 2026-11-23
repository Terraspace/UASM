option casemap:none
option elfpic:1
extern optional(fallback):proc
extern fallback:proc
public public_fn, hidden_fn
option elfvisibility:hidden_fn:hidden
first segment use64 'CODE'
 call optional
 call public_fn
 call hidden_fn
 call private_fn
 call rax
 jmp rbx
first ends
second segment use64 'CODE'
public_fn:
 ret
hidden_fn:
 ret
private_fn:
 ret
second ends
end
