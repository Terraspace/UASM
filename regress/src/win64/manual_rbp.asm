; Manual RBP frames must keep MASM offsets even with automatic WIN64 options.
; Compare .text with ML64: it assembles all copies without UASM-only options.
option casemap:none
option prologue:none
option epilogue:none
.code
ifdef __UASM__
option win64:0
option stackbase:rbp
endif
Manual0 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual0 endp
ifdef __UASM__
option win64:1
option stackbase:rbp
endif
Manual1 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual1 endp
ifdef __UASM__
option win64:2
option stackbase:rbp
endif
Manual2 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual2 endp
ifdef __UASM__
option win64:3
option stackbase:rbp
endif
Manual3 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual3 endp
ifdef __UASM__
option win64:4
option stackbase:rbp
endif
Manual4 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual4 endp
ifdef __UASM__
option win64:5
option stackbase:rbp
endif
Manual5 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual5 endp
ifdef __UASM__
option win64:6
option stackbase:rbp
endif
Manual6 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual6 endp
ifdef __UASM__
option win64:7
option stackbase:rbp
endif
Manual7 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual7 endp
ifdef __UASM__
option win64:8
option stackbase:rbp
endif
Manual8 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual8 endp
ifdef __UASM__
option win64:9
option stackbase:rbp
endif
Manual9 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual9 endp
ifdef __UASM__
option win64:10
option stackbase:rbp
endif
Manual10 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual10 endp
ifdef __UASM__
option win64:11
option stackbase:rbp
endif
Manual11 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual11 endp
ifdef __UASM__
option win64:12
option stackbase:rbp
endif
Manual12 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual12 endp
ifdef __UASM__
option win64:13
option stackbase:rbp
endif
Manual13 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual13 endp
ifdef __UASM__
option win64:14
option stackbase:rbp
endif
Manual14 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual14 endp
ifdef __UASM__
option win64:15
option stackbase:rbp
endif
Manual15 proc frame a:qword,b:qword,arg3:qword,d:dword
local wc[80]:byte,msg[48]:byte,handle:qword
push rbp
.pushreg rbp
sub rsp,240
.allocstack 240
lea rbp,[rsp+240]
.setframe rbp,240
.endprolog
mov a,rcx
mov b,rdx
mov arg3,r8
mov d,r9d
lea rax,wc
lea rdx,msg
mov handle,rax
mov rax,handle
mov rax,a
mov rdx,b
mov r8,arg3
mov r9d,d
lea rsp,[rbp]
pop rbp
ret 0
Manual15 endp
end
