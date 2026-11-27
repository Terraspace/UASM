.x64
option evex:1
.data
vector zmmword ?
.code
 vmovdqu64 zmm1,vector+64
 vmovdqu64 vector+128,zmm2
 vmovdqu64 zmm3,vector-64
 vmovdqu64 zmm4,[rax+64]
 vmovdqu64 [rax+128],zmm5
end
