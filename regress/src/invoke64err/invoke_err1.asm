.xmm
option casemap:none 
option dotname      
option frame:auto   
option win64:8      
option stackbase:rsp

.code

Test1 proc Arg1:QWORD, Arg2: QWORD
    mov r10, Arg1
    mov r11, Arg2
    ret
Test1 endp

Test2 proc Arg1:DWORD, Arg2:QWORD
    mov r10d, Arg1
    mov r11, Arg2
    ret
Test2 endp


start proc uses rbx
    invoke Test1, rdx, rcx
    invoke Test1, rdx, ecx
    invoke Test1, SDWORD PTR edx, rcx
    invoke Test1, edx, ecx

    invoke Test2, edx, rcx
    invoke Test2, edx, rcx

    ret
start endp


end start

;reported by biterider Dec 19th 2017 - rdx/rcx not detecting overwritten registers when only using a sub-register.
;issue is actually that we're allowing a 32bit register to be passed to a 64bit parameter, invoke.c line 1258.
;this feature was added in jwasm 2.11, allow argument extension.. but it doesn't flag the parent register.