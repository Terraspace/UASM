; Include from global scope in each module. No external assembly headers needed.
option casemap:none
option stackbase:rsp
option win64:15
option frame:auto
option proc:private

namespace Model
Pair struct
 first dword ?
 second dword ?
Pair ends
endnamespace

namespace Services
ComputeTotal proto (dword) first:dword,second:dword
endnamespace

namespace Win32
GetStdHandle proto :dword
WriteFile proto :qword,:ptr,:dword,:ptr,:ptr
ExitProcess proto :dword
endnamespace
