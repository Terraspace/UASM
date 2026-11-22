option casemap:none
option arch:sse
HF2 struct
a real4 ?
b real4 ?
HF2 ends
HV4 struct
a __m256f <>
b __m256f <>
c1 __m256f <>
d __m256f <>
HV4 ends
Pair struct
a qword ?
b qword ?
Pair ends
c_multi proto vectorcall :HF2,:HV4,:__m256f,:HF2
c_seven128 proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:__m128f
c_seven256 proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:qword,:__m256f
c_mutate proto vectorcall :Pair
.data
hf HF2 <1.0,2.0>
hv HV4 <<3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0>,<4.0,4.0,4.0,4.0,4.0,4.0,4.0,4.0>,<5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0>,<6.0,6.0,6.0,6.0,6.0,6.0,6.0,6.0>>
v128 __m128f <1.0,2.0,3.0,4.0>
v256 __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>
storage Pair <1,2>
.code
option stackbase:rsp
option win64:1
multi_rsp_1 proc frame
invoke c_multi,hf,hv,v256,hf
ret
multi_rsp_1 endp
reg128_rsp_1 proc frame
movups xmm0,v128
invoke c_seven128,1,2,3,4,5,6,xmm0
ret
reg128_rsp_1 endp
reg256_rsp_1 proc frame
vmovups ymm0,v256
invoke c_seven256,1,2,3,4,5,6,7,ymm0
ret
reg256_rsp_1 endp
referential_rsp_1 proc frame
mov storage.a,1
invoke c_mutate,storage
mov rax,storage.a
ret
referential_rsp_1 endp
option stackbase:rsp
option win64:3
multi_rsp_3 proc frame
invoke c_multi,hf,hv,v256,hf
ret
multi_rsp_3 endp
reg128_rsp_3 proc frame
movups xmm0,v128
invoke c_seven128,1,2,3,4,5,6,xmm0
ret
reg128_rsp_3 endp
reg256_rsp_3 proc frame
vmovups ymm0,v256
invoke c_seven256,1,2,3,4,5,6,7,ymm0
ret
reg256_rsp_3 endp
referential_rsp_3 proc frame
mov storage.a,1
invoke c_mutate,storage
mov rax,storage.a
ret
referential_rsp_3 endp
option stackbase:rsp
option win64:5
multi_rsp_5 proc frame
invoke c_multi,hf,hv,v256,hf
ret
multi_rsp_5 endp
reg128_rsp_5 proc frame
movups xmm0,v128
invoke c_seven128,1,2,3,4,5,6,xmm0
ret
reg128_rsp_5 endp
reg256_rsp_5 proc frame
vmovups ymm0,v256
invoke c_seven256,1,2,3,4,5,6,7,ymm0
ret
reg256_rsp_5 endp
referential_rsp_5 proc frame
mov storage.a,1
invoke c_mutate,storage
mov rax,storage.a
ret
referential_rsp_5 endp
option stackbase:rsp
option win64:7
multi_rsp_7 proc frame
invoke c_multi,hf,hv,v256,hf
ret
multi_rsp_7 endp
reg128_rsp_7 proc frame
movups xmm0,v128
invoke c_seven128,1,2,3,4,5,6,xmm0
ret
reg128_rsp_7 endp
reg256_rsp_7 proc frame
vmovups ymm0,v256
invoke c_seven256,1,2,3,4,5,6,7,ymm0
ret
reg256_rsp_7 endp
referential_rsp_7 proc frame
mov storage.a,1
invoke c_mutate,storage
mov rax,storage.a
ret
referential_rsp_7 endp
option stackbase:rsp
option win64:11
multi_rsp_11 proc frame
invoke c_multi,hf,hv,v256,hf
ret
multi_rsp_11 endp
reg128_rsp_11 proc frame
movups xmm0,v128
invoke c_seven128,1,2,3,4,5,6,xmm0
ret
reg128_rsp_11 endp
reg256_rsp_11 proc frame
vmovups ymm0,v256
invoke c_seven256,1,2,3,4,5,6,7,ymm0
ret
reg256_rsp_11 endp
referential_rsp_11 proc frame
mov storage.a,1
invoke c_mutate,storage
mov rax,storage.a
ret
referential_rsp_11 endp
option stackbase:rsp
option win64:15
multi_rsp_15 proc frame
invoke c_multi,hf,hv,v256,hf
ret
multi_rsp_15 endp
reg128_rsp_15 proc frame
movups xmm0,v128
invoke c_seven128,1,2,3,4,5,6,xmm0
ret
reg128_rsp_15 endp
reg256_rsp_15 proc frame
vmovups ymm0,v256
invoke c_seven256,1,2,3,4,5,6,7,ymm0
ret
reg256_rsp_15 endp
referential_rsp_15 proc frame
mov storage.a,1
invoke c_mutate,storage
mov rax,storage.a
ret
referential_rsp_15 endp
option stackbase:rbp
option win64:1
multi_rbp_1 proc frame
invoke c_multi,hf,hv,v256,hf
ret
multi_rbp_1 endp
reg128_rbp_1 proc frame
movups xmm0,v128
invoke c_seven128,1,2,3,4,5,6,xmm0
ret
reg128_rbp_1 endp
reg256_rbp_1 proc frame
vmovups ymm0,v256
invoke c_seven256,1,2,3,4,5,6,7,ymm0
ret
reg256_rbp_1 endp
referential_rbp_1 proc frame
mov storage.a,1
invoke c_mutate,storage
mov rax,storage.a
ret
referential_rbp_1 endp
option stackbase:rbp
option win64:3
multi_rbp_3 proc frame
invoke c_multi,hf,hv,v256,hf
ret
multi_rbp_3 endp
reg128_rbp_3 proc frame
movups xmm0,v128
invoke c_seven128,1,2,3,4,5,6,xmm0
ret
reg128_rbp_3 endp
reg256_rbp_3 proc frame
vmovups ymm0,v256
invoke c_seven256,1,2,3,4,5,6,7,ymm0
ret
reg256_rbp_3 endp
referential_rbp_3 proc frame
mov storage.a,1
invoke c_mutate,storage
mov rax,storage.a
ret
referential_rbp_3 endp
option stackbase:rbp
option win64:5
multi_rbp_5 proc frame
invoke c_multi,hf,hv,v256,hf
ret
multi_rbp_5 endp
reg128_rbp_5 proc frame
movups xmm0,v128
invoke c_seven128,1,2,3,4,5,6,xmm0
ret
reg128_rbp_5 endp
reg256_rbp_5 proc frame
vmovups ymm0,v256
invoke c_seven256,1,2,3,4,5,6,7,ymm0
ret
reg256_rbp_5 endp
referential_rbp_5 proc frame
mov storage.a,1
invoke c_mutate,storage
mov rax,storage.a
ret
referential_rbp_5 endp
option stackbase:rbp
option win64:7
multi_rbp_7 proc frame
invoke c_multi,hf,hv,v256,hf
ret
multi_rbp_7 endp
reg128_rbp_7 proc frame
movups xmm0,v128
invoke c_seven128,1,2,3,4,5,6,xmm0
ret
reg128_rbp_7 endp
reg256_rbp_7 proc frame
vmovups ymm0,v256
invoke c_seven256,1,2,3,4,5,6,7,ymm0
ret
reg256_rbp_7 endp
referential_rbp_7 proc frame
mov storage.a,1
invoke c_mutate,storage
mov rax,storage.a
ret
referential_rbp_7 endp
option stackbase:rbp
option win64:11
multi_rbp_11 proc frame
invoke c_multi,hf,hv,v256,hf
ret
multi_rbp_11 endp
reg128_rbp_11 proc frame
movups xmm0,v128
invoke c_seven128,1,2,3,4,5,6,xmm0
ret
reg128_rbp_11 endp
reg256_rbp_11 proc frame
vmovups ymm0,v256
invoke c_seven256,1,2,3,4,5,6,7,ymm0
ret
reg256_rbp_11 endp
referential_rbp_11 proc frame
mov storage.a,1
invoke c_mutate,storage
mov rax,storage.a
ret
referential_rbp_11 endp
option stackbase:rbp
option win64:15
multi_rbp_15 proc frame
invoke c_multi,hf,hv,v256,hf
ret
multi_rbp_15 endp
reg128_rbp_15 proc frame
movups xmm0,v128
invoke c_seven128,1,2,3,4,5,6,xmm0
ret
reg128_rbp_15 endp
reg256_rbp_15 proc frame
vmovups ymm0,v256
invoke c_seven256,1,2,3,4,5,6,7,ymm0
ret
reg256_rbp_15 endp
referential_rbp_15 proc frame
mov storage.a,1
invoke c_mutate,storage
mov rax,storage.a
ret
referential_rbp_15 endp
raw_c proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:real8
option stackbase:rsp
option win64:1
raw_rsp_1 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rsp_1 endp
rawcall_rsp_1 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rsp_1 endp
option stackbase:rsp
option win64:2
raw_rsp_2 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rsp_2 endp
rawcall_rsp_2 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rsp_2 endp
option stackbase:rsp
option win64:3
raw_rsp_3 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rsp_3 endp
rawcall_rsp_3 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rsp_3 endp
option stackbase:rsp
option win64:4
raw_rsp_4 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rsp_4 endp
rawcall_rsp_4 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rsp_4 endp
option stackbase:rsp
option win64:5
raw_rsp_5 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rsp_5 endp
rawcall_rsp_5 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rsp_5 endp
option stackbase:rsp
option win64:6
raw_rsp_6 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rsp_6 endp
rawcall_rsp_6 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rsp_6 endp
option stackbase:rsp
option win64:7
raw_rsp_7 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rsp_7 endp
rawcall_rsp_7 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rsp_7 endp
option stackbase:rsp
option win64:8
raw_rsp_8 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rsp_8 endp
rawcall_rsp_8 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rsp_8 endp
option stackbase:rsp
option win64:9
raw_rsp_9 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rsp_9 endp
rawcall_rsp_9 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rsp_9 endp
option stackbase:rsp
option win64:10
raw_rsp_10 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rsp_10 endp
rawcall_rsp_10 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rsp_10 endp
option stackbase:rsp
option win64:11
raw_rsp_11 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rsp_11 endp
rawcall_rsp_11 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rsp_11 endp
option stackbase:rsp
option win64:12
raw_rsp_12 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rsp_12 endp
rawcall_rsp_12 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rsp_12 endp
option stackbase:rsp
option win64:13
raw_rsp_13 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rsp_13 endp
rawcall_rsp_13 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rsp_13 endp
option stackbase:rsp
option win64:14
raw_rsp_14 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rsp_14 endp
rawcall_rsp_14 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rsp_14 endp
option stackbase:rsp
option win64:15
raw_rsp_15 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rsp_15 endp
rawcall_rsp_15 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rsp_15 endp
option stackbase:rbp
option win64:1
raw_rbp_1 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rbp_1 endp
rawcall_rbp_1 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rbp_1 endp
option stackbase:rbp
option win64:2
raw_rbp_2 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rbp_2 endp
rawcall_rbp_2 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rbp_2 endp
option stackbase:rbp
option win64:3
raw_rbp_3 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rbp_3 endp
rawcall_rbp_3 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rbp_3 endp
option stackbase:rbp
option win64:4
raw_rbp_4 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rbp_4 endp
rawcall_rbp_4 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rbp_4 endp
option stackbase:rbp
option win64:5
raw_rbp_5 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rbp_5 endp
rawcall_rbp_5 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rbp_5 endp
option stackbase:rbp
option win64:6
raw_rbp_6 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rbp_6 endp
rawcall_rbp_6 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rbp_6 endp
option stackbase:rbp
option win64:7
raw_rbp_7 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rbp_7 endp
rawcall_rbp_7 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rbp_7 endp
option stackbase:rbp
option win64:8
raw_rbp_8 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rbp_8 endp
rawcall_rbp_8 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rbp_8 endp
option stackbase:rbp
option win64:9
raw_rbp_9 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rbp_9 endp
rawcall_rbp_9 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rbp_9 endp
option stackbase:rbp
option win64:10
raw_rbp_10 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rbp_10 endp
rawcall_rbp_10 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rbp_10 endp
option stackbase:rbp
option win64:11
raw_rbp_11 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rbp_11 endp
rawcall_rbp_11 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rbp_11 endp
option stackbase:rbp
option win64:12
raw_rbp_12 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rbp_12 endp
rawcall_rbp_12 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rbp_12 endp
option stackbase:rbp
option win64:13
raw_rbp_13 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rbp_13 endp
rawcall_rbp_13 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rbp_13 endp
option stackbase:rbp
option win64:14
raw_rbp_14 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rbp_14 endp
rawcall_rbp_14 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rbp_14 endp
option stackbase:rbp
option win64:15
raw_rbp_15 proc vectorcall frame a:real8,b:real8,c1:real8,d:real8,e:real8,f:real8,g:real8
addsd xmm0,xmm1
addsd xmm0,xmm2
addsd xmm0,xmm3
addsd xmm0,xmm4
addsd xmm0,xmm5
addsd xmm0,g
ret
raw_rbp_15 endp
rawcall_rbp_15 proc frame
invoke raw_c,1.0,2.0,3.0,4.0,5.0,6.0,7.0
ret
rawcall_rbp_15 endp
end
