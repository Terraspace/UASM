.x64
option evex:1
option arch:avx
option sysvhome:0
option frame:auto
option redzone:no
P128 proto SYSTEMV :oword
P256 proto SYSTEMV :ymmword
.data
vector zmmword ?
.code
Receiver proc SYSTEMV uses rbx xmm6 ymm7 zmm8 xmm20 ymm21 zmm22, arg:zmmword
 vmovdqu64 zmm9,arg
 ret
Receiver endp
Caller proc SYSTEMV
 invoke Receiver,vector
 invoke Receiver,zmm16
 invoke P128,xmm20
 invoke P256,ymm21
 ret
Caller endp
end
