.xmm
option casemap:none
option dotname
option frame:auto
option win64:8
option stackbase:rsp


.code


TestProc proc Arg1:QWORD, Arg2:VARARG
    mov r8, Arg1
    mov r9, Arg2
    ret
TestProc endp



; VARARG immediates that don't fit in a signed dword should be promoted to qwords.

start proc
    invoke TestProc, 0123456789ABCDEFh, QWORD ptr 0123456789ABCDEFh, 0123456789ABCDEFh, 0123456789ABCDEFh, 0123456789ABCDEFh
    invoke TestProc, 0A23456789ABCDEFh, rax, rbx, rcx, rdx
    ret
start endp


end start