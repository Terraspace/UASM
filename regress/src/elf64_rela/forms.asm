.x64
option casemap:none
.data
padding db 7 dup(0)
target db "0123456789"
ptr_plus dq target+1
ptr_minus dq target-1
ptr_wide dq target+100000001h
ptr_wide_neg dq target-100000001h
ptr32 dd target+3
.code
public entry_point
entry_point:
 mov al,target[rdx]
 mov al,target[rdx+1]
 mov al,target[rdx-1]
 mov al,target[rbx+rdx*4+2]
 mov al,target+1
 mov al,target-1
 mov byte ptr target+2,7
 mov dword ptr target+3,12345678h
 mov rax,offset target+100000001h
 mov eax,offset target+3
 ret
end
