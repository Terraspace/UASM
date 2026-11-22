; A non-FRAME automatic prologue must preserve explicit USES R11.
option casemap:none
option frame:noauto
option stackbase:rbp
.code
generic proc uses r11
 local storage[4096]:byte
 mov storage[0],1
 ret
generic endp
end
