; Reject source registers overwritten while INVOKE prepares earlier arguments.
option casemap:none
option stackbase:rsp
option win64:15
HF2 struct
 a real4 ?
 b real4 ?
HF2 ends
scalars proto vectorcall :real8,:real8
aggregate proto vectorcall :real8,:HF2
.code
entry proc frame
 invoke scalars,xmm1,xmm0
 invoke aggregate,1.0,[rax]
 ret
entry endp
end
