; Direct ASM operators in C-style calls, including a typed nested result.
option casemap:none
option stackbase:rsp
option win64:15
option frame:auto
MB_OK equ 0
MB_ICONERROR equ 40h
Target proto :dword,:dword
Inner proto (dword) :dword
.code
Caller proc frame
 Target(MB_OK or MB_ICONERROR, (7 AND 3) SHL 2)
 Target(Inner(1 OR 2), NOT 0)
 ret
Caller endp
end
