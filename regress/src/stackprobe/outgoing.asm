; Outgoing INVOKE space crosses the probe threshold on later passes.
option casemap:none
option stackbase:rsp
option win64:15
callee proto :qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword,:qword
.code
outgoing_4000 proc frame
 local storage[4000]:byte
 invoke callee,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 ret
outgoing_4000 endp
outgoing_12240 proc frame
 local storage[12240]:byte
 invoke callee,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 ret
outgoing_12240 endp
end
