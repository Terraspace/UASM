.x64
.model flat
option evex:1

.data

YMM_ONE DD 1,0,1,0,1,0,1,0

.code

vpbroadcastd ymm3, YMM_ONE ; Load constant 1
vpbroadcastd zmm13, YMM_ONE ; Load constant 1

end