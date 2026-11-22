; Issue #104: dependency-free Win64 probes.
option casemap:none
option frame:auto
option stackbase:rsp
option win64:15
.code
frame_4080 proc frame
 local storage[4080]:byte
 mov storage[0],1
 mov storage[4079],2
 ret
frame_4080 endp
frame_4096 proc frame
 local storage[4096]:byte
 mov storage[0],1
 mov storage[4095],2
 ret
frame_4096 endp
frame_4112 proc frame
 local storage[4112]:byte
 mov storage[0],1
 mov storage[4111],2
 ret
frame_4112 endp
frame_8192 proc frame
 local storage[8192]:byte
 mov storage[0],1
 mov storage[8191],2
 ret
frame_8192 endp
frame_12288 proc frame
 local storage[12288]:byte
 mov storage[0],1
 mov storage[12287],2
 ret
frame_12288 endp
frame_12304 proc frame
 local storage[12304]:byte
 mov storage[0],1
 mov storage[12303],2
 ret
frame_12304 endp
frame_65536 proc frame
 local storage[65536]:byte
 mov storage[0],1
 mov storage[65535],2
 ret
frame_65536 endp
frame_1048576 proc frame
 local storage[1048576]:byte
 mov storage[0],1
 mov storage[1048575],2
 ret
frame_1048576 endp
option noscoped
.radix 16
end
