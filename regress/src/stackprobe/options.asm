; Issue #104: dependency-free Win64 probes.
option casemap:none
option frame:auto
option win64:7
.code
option stackprobe:off
disabled proc frame
 local storage[65536]:byte
 mov storage[0],1
 ret
disabled endp
option stackprobe:on
enabled proc frame uses r11
 local storage[4096]:byte
 mov storage[0],1
 ret
enabled endp
option prologue:none
option epilogue:none
manual proc frame
 sub rsp,65536
 .allocstack 65536
 .endprolog
 add rsp,65536
 ret
manual endp
option stackprobe:off
end
