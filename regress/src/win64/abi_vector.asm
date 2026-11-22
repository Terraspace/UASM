; Win64 vectorcall interop: each signature is exercised under both stack bases.
; Paired with validation/win64_vector_driver.c; no SDK includes are needed here.
option casemap:none
option arch:sse
F1 struct
 m0 real4 ?
F1 ends
F2 struct
 m0 real4 ?
 m1 real4 ?
F2 ends
F3 struct
 m0 real4 ?
 m1 real4 ?
 m2 real4 ?
F3 ends
F4 struct
 m0 real4 ?
 m1 real4 ?
 m2 real4 ?
 m3 real4 ?
F4 ends
D1 struct
 m0 real8 ?
D1 ends
D2 struct
 m0 real8 ?
 m1 real8 ?
D2 ends
D3 struct
 m0 real8 ?
 m1 real8 ?
 m2 real8 ?
D3 ends
D4 struct
 m0 real8 ?
 m1 real8 ?
 m2 real8 ?
 m3 real8 ?
D4 ends
V1 struct
 m0 __m128f <>
V1 ends
V2 struct
 m0 __m128f <>
 m1 __m128f <>
V2 ends
V3 struct
 m0 __m128f <>
 m1 __m128f <>
 m2 __m128f <>
V3 ends
V4 struct
 m0 __m128f <>
 m1 __m128f <>
 m2 __m128f <>
 m3 __m128f <>
V4 ends
Y1 struct
 m0 __m256f <>
Y1 ends
Y2 struct
 m0 __m256f <>
 m1 __m256f <>
Y2 ends
Y3 struct
 m0 __m256f <>
 m1 __m256f <>
 m2 __m256f <>
Y3 ends
Y4 struct
 m0 __m256f <>
 m1 __m256f <>
 m2 __m256f <>
 m3 __m256f <>
Y4 ends
NF struct
 a F2 <>
 b F2 <>
NF ends
AF struct
 a real4 4 dup (?)
AF ends
Mixed struct
 a real4 ?
 b dword ?
Mixed ends
Ints struct
 a qword ?
 b qword ?
Ints ends
.data
align 64
data_F1 F1 <1.0>
align 64
data_F2 F2 <1.0,2.0>
align 64
data_F3 F3 <1.0,2.0,3.0>
align 64
data_F4 F4 <1.0,2.0,3.0,4.0>
align 64
data_D1 D1 <1.0>
align 64
data_D2 D2 <1.0,2.0>
align 64
data_D3 D3 <1.0,2.0,3.0>
align 64
data_D4 D4 <1.0,2.0,3.0,4.0>
align 64
data_V1 V1 <<1.0,1.0,1.0,1.0>>
align 64
data_V2 V2 <<1.0,1.0,1.0,1.0>,<2.0,2.0,2.0,2.0>>
align 64
data_V3 V3 <<1.0,1.0,1.0,1.0>,<2.0,2.0,2.0,2.0>,<3.0,3.0,3.0,3.0>>
align 64
data_V4 V4 <<1.0,1.0,1.0,1.0>,<2.0,2.0,2.0,2.0>,<3.0,3.0,3.0,3.0>,<4.0,4.0,4.0,4.0>>
align 64
data_Y1 Y1 <<1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0>>
align 64
data_Y2 Y2 <<1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0>,<2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0>>
align 64
data_Y3 Y3 <<1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0>,<2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0>,<3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0>>
align 64
data_Y4 Y4 <<1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0>,<2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0>,<3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0>,<4.0,4.0,4.0,4.0,4.0,4.0,4.0,4.0>>
align 64
data_NF NF <<1.0,2.0>,<3.0,4.0>>
align 64
data_AF AF < <1.0,2.0,3.0,4.0> >
align 64
data_Mixed Mixed <1.0,2>
align 64
data_Ints Ints <1,2>
align 64
data___m128f __m128f <1.0,2.0,3.0,4.0>
align 64
data___m256f __m256f <1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0>
.code
c_F1_alone proto vectorcall :F1
CASE_F1_alone macro base,mode
option stackbase:base
option win64:mode
a_F1_alone_&base&_&mode proc vectorcall frame a:F1
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F1_alone_&base&_&mode endp
call_F1_alone_&base&_&mode proc frame
invoke c_F1_alone,data_F1
ret
call_F1_alone_&base&_&mode endp
forward_F1_alone_&base&_&mode proc vectorcall frame a:F1
invoke c_F1_alone,a
ret
forward_F1_alone_&base&_&mode endp
endm
CASE_F1_alone rsp,1
CASE_F1_alone rsp,3
CASE_F1_alone rsp,5
CASE_F1_alone rsp,7
CASE_F1_alone rsp,11
CASE_F1_alone rsp,15
CASE_F1_alone rbp,1
CASE_F1_alone rbp,3
CASE_F1_alone rbp,5
CASE_F1_alone rbp,7
CASE_F1_alone rbp,11
CASE_F1_alone rbp,15

c_F1_holes proto vectorcall :F1,:real4,:qword,:real8,:qword,:real4
CASE_F1_holes macro base,mode
option stackbase:base
option win64:mode
a_F1_holes_&base&_&mode proc vectorcall frame a:F1,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F1_holes_&base&_&mode endp
call_F1_holes_&base&_&mode proc frame
invoke c_F1_holes,data_F1,11.0,12,13.0,14,15.0
ret
call_F1_holes_&base&_&mode endp
forward_F1_holes_&base&_&mode proc vectorcall frame a:F1,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_F1_holes,a,b,c1,d,e,f
ret
forward_F1_holes_&base&_&mode endp
endm
CASE_F1_holes rsp,1
CASE_F1_holes rsp,3
CASE_F1_holes rsp,5
CASE_F1_holes rsp,7
CASE_F1_holes rsp,11
CASE_F1_holes rsp,15
CASE_F1_holes rbp,1
CASE_F1_holes rbp,3
CASE_F1_holes rbp,5
CASE_F1_holes rbp,7
CASE_F1_holes rbp,11
CASE_F1_holes rbp,15

c_F1_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:F1
CASE_F1_fallback macro base,mode
option stackbase:base
option win64:mode
a_F1_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:F1
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F1_fallback_&base&_&mode endp
call_F1_fallback_&base&_&mode proc frame
invoke c_F1_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_F1
ret
call_F1_fallback_&base&_&mode endp
forward_F1_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:F1
invoke c_F1_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_F1_fallback_&base&_&mode endp
endm
CASE_F1_fallback rsp,1
CASE_F1_fallback rsp,3
CASE_F1_fallback rsp,5
CASE_F1_fallback rsp,7
CASE_F1_fallback rsp,11
CASE_F1_fallback rsp,15
CASE_F1_fallback rbp,1
CASE_F1_fallback rbp,3
CASE_F1_fallback rbp,5
CASE_F1_fallback rbp,7
CASE_F1_fallback rbp,11
CASE_F1_fallback rbp,15

c_F1_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:F1
CASE_F1_seventh macro base,mode
option stackbase:base
option win64:mode
a_F1_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:F1
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F1_seventh_&base&_&mode endp
call_F1_seventh_&base&_&mode proc frame
invoke c_F1_seventh,1,2,3,4,5,6,data_F1
ret
call_F1_seventh_&base&_&mode endp
forward_F1_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:F1
invoke c_F1_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_F1_seventh_&base&_&mode endp
endm
CASE_F1_seventh rsp,1
CASE_F1_seventh rsp,3
CASE_F1_seventh rsp,5
CASE_F1_seventh rsp,7
CASE_F1_seventh rsp,11
CASE_F1_seventh rsp,15
CASE_F1_seventh rbp,1
CASE_F1_seventh rbp,3
CASE_F1_seventh rbp,5
CASE_F1_seventh rbp,7
CASE_F1_seventh rbp,11
CASE_F1_seventh rbp,15

c_F2_alone proto vectorcall :F2
CASE_F2_alone macro base,mode
option stackbase:base
option win64:mode
a_F2_alone_&base&_&mode proc vectorcall frame a:F2
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F2_alone_&base&_&mode endp
call_F2_alone_&base&_&mode proc frame
invoke c_F2_alone,data_F2
ret
call_F2_alone_&base&_&mode endp
forward_F2_alone_&base&_&mode proc vectorcall frame a:F2
invoke c_F2_alone,a
ret
forward_F2_alone_&base&_&mode endp
endm
CASE_F2_alone rsp,1
CASE_F2_alone rsp,3
CASE_F2_alone rsp,5
CASE_F2_alone rsp,7
CASE_F2_alone rsp,11
CASE_F2_alone rsp,15
CASE_F2_alone rbp,1
CASE_F2_alone rbp,3
CASE_F2_alone rbp,5
CASE_F2_alone rbp,7
CASE_F2_alone rbp,11
CASE_F2_alone rbp,15

c_F2_holes proto vectorcall :F2,:real4,:qword,:real8,:qword,:real4
CASE_F2_holes macro base,mode
option stackbase:base
option win64:mode
a_F2_holes_&base&_&mode proc vectorcall frame a:F2,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F2_holes_&base&_&mode endp
call_F2_holes_&base&_&mode proc frame
invoke c_F2_holes,data_F2,11.0,12,13.0,14,15.0
ret
call_F2_holes_&base&_&mode endp
forward_F2_holes_&base&_&mode proc vectorcall frame a:F2,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_F2_holes,a,b,c1,d,e,f
ret
forward_F2_holes_&base&_&mode endp
endm
CASE_F2_holes rsp,1
CASE_F2_holes rsp,3
CASE_F2_holes rsp,5
CASE_F2_holes rsp,7
CASE_F2_holes rsp,11
CASE_F2_holes rsp,15
CASE_F2_holes rbp,1
CASE_F2_holes rbp,3
CASE_F2_holes rbp,5
CASE_F2_holes rbp,7
CASE_F2_holes rbp,11
CASE_F2_holes rbp,15

c_F2_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:F2
CASE_F2_fallback macro base,mode
option stackbase:base
option win64:mode
a_F2_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:F2
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F2_fallback_&base&_&mode endp
call_F2_fallback_&base&_&mode proc frame
invoke c_F2_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_F2
ret
call_F2_fallback_&base&_&mode endp
forward_F2_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:F2
invoke c_F2_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_F2_fallback_&base&_&mode endp
endm
CASE_F2_fallback rsp,1
CASE_F2_fallback rsp,3
CASE_F2_fallback rsp,5
CASE_F2_fallback rsp,7
CASE_F2_fallback rsp,11
CASE_F2_fallback rsp,15
CASE_F2_fallback rbp,1
CASE_F2_fallback rbp,3
CASE_F2_fallback rbp,5
CASE_F2_fallback rbp,7
CASE_F2_fallback rbp,11
CASE_F2_fallback rbp,15

c_F2_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:F2
CASE_F2_seventh macro base,mode
option stackbase:base
option win64:mode
a_F2_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:F2
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F2_seventh_&base&_&mode endp
call_F2_seventh_&base&_&mode proc frame
invoke c_F2_seventh,1,2,3,4,5,6,data_F2
ret
call_F2_seventh_&base&_&mode endp
forward_F2_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:F2
invoke c_F2_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_F2_seventh_&base&_&mode endp
endm
CASE_F2_seventh rsp,1
CASE_F2_seventh rsp,3
CASE_F2_seventh rsp,5
CASE_F2_seventh rsp,7
CASE_F2_seventh rsp,11
CASE_F2_seventh rsp,15
CASE_F2_seventh rbp,1
CASE_F2_seventh rbp,3
CASE_F2_seventh rbp,5
CASE_F2_seventh rbp,7
CASE_F2_seventh rbp,11
CASE_F2_seventh rbp,15

c_F3_alone proto vectorcall :F3
CASE_F3_alone macro base,mode
option stackbase:base
option win64:mode
a_F3_alone_&base&_&mode proc vectorcall frame a:F3
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F3_alone_&base&_&mode endp
call_F3_alone_&base&_&mode proc frame
invoke c_F3_alone,data_F3
ret
call_F3_alone_&base&_&mode endp
forward_F3_alone_&base&_&mode proc vectorcall frame a:F3
invoke c_F3_alone,a
ret
forward_F3_alone_&base&_&mode endp
endm
CASE_F3_alone rsp,1
CASE_F3_alone rsp,3
CASE_F3_alone rsp,5
CASE_F3_alone rsp,7
CASE_F3_alone rsp,11
CASE_F3_alone rsp,15
CASE_F3_alone rbp,1
CASE_F3_alone rbp,3
CASE_F3_alone rbp,5
CASE_F3_alone rbp,7
CASE_F3_alone rbp,11
CASE_F3_alone rbp,15

c_F3_holes proto vectorcall :F3,:real4,:qword,:real8,:qword,:real4
CASE_F3_holes macro base,mode
option stackbase:base
option win64:mode
a_F3_holes_&base&_&mode proc vectorcall frame a:F3,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F3_holes_&base&_&mode endp
call_F3_holes_&base&_&mode proc frame
invoke c_F3_holes,data_F3,11.0,12,13.0,14,15.0
ret
call_F3_holes_&base&_&mode endp
forward_F3_holes_&base&_&mode proc vectorcall frame a:F3,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_F3_holes,a,b,c1,d,e,f
ret
forward_F3_holes_&base&_&mode endp
endm
CASE_F3_holes rsp,1
CASE_F3_holes rsp,3
CASE_F3_holes rsp,5
CASE_F3_holes rsp,7
CASE_F3_holes rsp,11
CASE_F3_holes rsp,15
CASE_F3_holes rbp,1
CASE_F3_holes rbp,3
CASE_F3_holes rbp,5
CASE_F3_holes rbp,7
CASE_F3_holes rbp,11
CASE_F3_holes rbp,15

c_F3_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:F3
CASE_F3_fallback macro base,mode
option stackbase:base
option win64:mode
a_F3_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:F3
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F3_fallback_&base&_&mode endp
call_F3_fallback_&base&_&mode proc frame
invoke c_F3_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_F3
ret
call_F3_fallback_&base&_&mode endp
forward_F3_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:F3
invoke c_F3_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_F3_fallback_&base&_&mode endp
endm
CASE_F3_fallback rsp,1
CASE_F3_fallback rsp,3
CASE_F3_fallback rsp,5
CASE_F3_fallback rsp,7
CASE_F3_fallback rsp,11
CASE_F3_fallback rsp,15
CASE_F3_fallback rbp,1
CASE_F3_fallback rbp,3
CASE_F3_fallback rbp,5
CASE_F3_fallback rbp,7
CASE_F3_fallback rbp,11
CASE_F3_fallback rbp,15

c_F3_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:F3
CASE_F3_seventh macro base,mode
option stackbase:base
option win64:mode
a_F3_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:F3
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F3_seventh_&base&_&mode endp
call_F3_seventh_&base&_&mode proc frame
invoke c_F3_seventh,1,2,3,4,5,6,data_F3
ret
call_F3_seventh_&base&_&mode endp
forward_F3_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:F3
invoke c_F3_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_F3_seventh_&base&_&mode endp
endm
CASE_F3_seventh rsp,1
CASE_F3_seventh rsp,3
CASE_F3_seventh rsp,5
CASE_F3_seventh rsp,7
CASE_F3_seventh rsp,11
CASE_F3_seventh rsp,15
CASE_F3_seventh rbp,1
CASE_F3_seventh rbp,3
CASE_F3_seventh rbp,5
CASE_F3_seventh rbp,7
CASE_F3_seventh rbp,11
CASE_F3_seventh rbp,15

c_F4_alone proto vectorcall :F4
CASE_F4_alone macro base,mode
option stackbase:base
option win64:mode
a_F4_alone_&base&_&mode proc vectorcall frame a:F4
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F4_alone_&base&_&mode endp
call_F4_alone_&base&_&mode proc frame
invoke c_F4_alone,data_F4
ret
call_F4_alone_&base&_&mode endp
forward_F4_alone_&base&_&mode proc vectorcall frame a:F4
invoke c_F4_alone,a
ret
forward_F4_alone_&base&_&mode endp
endm
CASE_F4_alone rsp,1
CASE_F4_alone rsp,3
CASE_F4_alone rsp,5
CASE_F4_alone rsp,7
CASE_F4_alone rsp,11
CASE_F4_alone rsp,15
CASE_F4_alone rbp,1
CASE_F4_alone rbp,3
CASE_F4_alone rbp,5
CASE_F4_alone rbp,7
CASE_F4_alone rbp,11
CASE_F4_alone rbp,15

c_F4_holes proto vectorcall :F4,:real4,:qword,:real8,:qword,:real4
CASE_F4_holes macro base,mode
option stackbase:base
option win64:mode
a_F4_holes_&base&_&mode proc vectorcall frame a:F4,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F4_holes_&base&_&mode endp
call_F4_holes_&base&_&mode proc frame
invoke c_F4_holes,data_F4,11.0,12,13.0,14,15.0
ret
call_F4_holes_&base&_&mode endp
forward_F4_holes_&base&_&mode proc vectorcall frame a:F4,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_F4_holes,a,b,c1,d,e,f
ret
forward_F4_holes_&base&_&mode endp
endm
CASE_F4_holes rsp,1
CASE_F4_holes rsp,3
CASE_F4_holes rsp,5
CASE_F4_holes rsp,7
CASE_F4_holes rsp,11
CASE_F4_holes rsp,15
CASE_F4_holes rbp,1
CASE_F4_holes rbp,3
CASE_F4_holes rbp,5
CASE_F4_holes rbp,7
CASE_F4_holes rbp,11
CASE_F4_holes rbp,15

c_F4_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:F4
CASE_F4_fallback macro base,mode
option stackbase:base
option win64:mode
a_F4_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:F4
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F4_fallback_&base&_&mode endp
call_F4_fallback_&base&_&mode proc frame
invoke c_F4_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_F4
ret
call_F4_fallback_&base&_&mode endp
forward_F4_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:F4
invoke c_F4_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_F4_fallback_&base&_&mode endp
endm
CASE_F4_fallback rsp,1
CASE_F4_fallback rsp,3
CASE_F4_fallback rsp,5
CASE_F4_fallback rsp,7
CASE_F4_fallback rsp,11
CASE_F4_fallback rsp,15
CASE_F4_fallback rbp,1
CASE_F4_fallback rbp,3
CASE_F4_fallback rbp,5
CASE_F4_fallback rbp,7
CASE_F4_fallback rbp,11
CASE_F4_fallback rbp,15

c_F4_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:F4
CASE_F4_seventh macro base,mode
option stackbase:base
option win64:mode
a_F4_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:F4
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_F4_seventh_&base&_&mode endp
call_F4_seventh_&base&_&mode proc frame
invoke c_F4_seventh,1,2,3,4,5,6,data_F4
ret
call_F4_seventh_&base&_&mode endp
forward_F4_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:F4
invoke c_F4_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_F4_seventh_&base&_&mode endp
endm
CASE_F4_seventh rsp,1
CASE_F4_seventh rsp,3
CASE_F4_seventh rsp,5
CASE_F4_seventh rsp,7
CASE_F4_seventh rsp,11
CASE_F4_seventh rsp,15
CASE_F4_seventh rbp,1
CASE_F4_seventh rbp,3
CASE_F4_seventh rbp,5
CASE_F4_seventh rbp,7
CASE_F4_seventh rbp,11
CASE_F4_seventh rbp,15

c_D1_alone proto vectorcall :D1
CASE_D1_alone macro base,mode
option stackbase:base
option win64:mode
a_D1_alone_&base&_&mode proc vectorcall frame a:D1
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D1_alone_&base&_&mode endp
call_D1_alone_&base&_&mode proc frame
invoke c_D1_alone,data_D1
ret
call_D1_alone_&base&_&mode endp
forward_D1_alone_&base&_&mode proc vectorcall frame a:D1
invoke c_D1_alone,a
ret
forward_D1_alone_&base&_&mode endp
endm
CASE_D1_alone rsp,1
CASE_D1_alone rsp,3
CASE_D1_alone rsp,5
CASE_D1_alone rsp,7
CASE_D1_alone rsp,11
CASE_D1_alone rsp,15
CASE_D1_alone rbp,1
CASE_D1_alone rbp,3
CASE_D1_alone rbp,5
CASE_D1_alone rbp,7
CASE_D1_alone rbp,11
CASE_D1_alone rbp,15

c_D1_holes proto vectorcall :D1,:real4,:qword,:real8,:qword,:real4
CASE_D1_holes macro base,mode
option stackbase:base
option win64:mode
a_D1_holes_&base&_&mode proc vectorcall frame a:D1,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D1_holes_&base&_&mode endp
call_D1_holes_&base&_&mode proc frame
invoke c_D1_holes,data_D1,11.0,12,13.0,14,15.0
ret
call_D1_holes_&base&_&mode endp
forward_D1_holes_&base&_&mode proc vectorcall frame a:D1,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_D1_holes,a,b,c1,d,e,f
ret
forward_D1_holes_&base&_&mode endp
endm
CASE_D1_holes rsp,1
CASE_D1_holes rsp,3
CASE_D1_holes rsp,5
CASE_D1_holes rsp,7
CASE_D1_holes rsp,11
CASE_D1_holes rsp,15
CASE_D1_holes rbp,1
CASE_D1_holes rbp,3
CASE_D1_holes rbp,5
CASE_D1_holes rbp,7
CASE_D1_holes rbp,11
CASE_D1_holes rbp,15

c_D1_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:D1
CASE_D1_fallback macro base,mode
option stackbase:base
option win64:mode
a_D1_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:D1
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D1_fallback_&base&_&mode endp
call_D1_fallback_&base&_&mode proc frame
invoke c_D1_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_D1
ret
call_D1_fallback_&base&_&mode endp
forward_D1_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:D1
invoke c_D1_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_D1_fallback_&base&_&mode endp
endm
CASE_D1_fallback rsp,1
CASE_D1_fallback rsp,3
CASE_D1_fallback rsp,5
CASE_D1_fallback rsp,7
CASE_D1_fallback rsp,11
CASE_D1_fallback rsp,15
CASE_D1_fallback rbp,1
CASE_D1_fallback rbp,3
CASE_D1_fallback rbp,5
CASE_D1_fallback rbp,7
CASE_D1_fallback rbp,11
CASE_D1_fallback rbp,15

c_D1_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:D1
CASE_D1_seventh macro base,mode
option stackbase:base
option win64:mode
a_D1_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:D1
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D1_seventh_&base&_&mode endp
call_D1_seventh_&base&_&mode proc frame
invoke c_D1_seventh,1,2,3,4,5,6,data_D1
ret
call_D1_seventh_&base&_&mode endp
forward_D1_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:D1
invoke c_D1_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_D1_seventh_&base&_&mode endp
endm
CASE_D1_seventh rsp,1
CASE_D1_seventh rsp,3
CASE_D1_seventh rsp,5
CASE_D1_seventh rsp,7
CASE_D1_seventh rsp,11
CASE_D1_seventh rsp,15
CASE_D1_seventh rbp,1
CASE_D1_seventh rbp,3
CASE_D1_seventh rbp,5
CASE_D1_seventh rbp,7
CASE_D1_seventh rbp,11
CASE_D1_seventh rbp,15

c_D2_alone proto vectorcall :D2
CASE_D2_alone macro base,mode
option stackbase:base
option win64:mode
a_D2_alone_&base&_&mode proc vectorcall frame a:D2
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D2_alone_&base&_&mode endp
call_D2_alone_&base&_&mode proc frame
invoke c_D2_alone,data_D2
ret
call_D2_alone_&base&_&mode endp
forward_D2_alone_&base&_&mode proc vectorcall frame a:D2
invoke c_D2_alone,a
ret
forward_D2_alone_&base&_&mode endp
endm
CASE_D2_alone rsp,1
CASE_D2_alone rsp,3
CASE_D2_alone rsp,5
CASE_D2_alone rsp,7
CASE_D2_alone rsp,11
CASE_D2_alone rsp,15
CASE_D2_alone rbp,1
CASE_D2_alone rbp,3
CASE_D2_alone rbp,5
CASE_D2_alone rbp,7
CASE_D2_alone rbp,11
CASE_D2_alone rbp,15

c_D2_holes proto vectorcall :D2,:real4,:qword,:real8,:qword,:real4
CASE_D2_holes macro base,mode
option stackbase:base
option win64:mode
a_D2_holes_&base&_&mode proc vectorcall frame a:D2,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D2_holes_&base&_&mode endp
call_D2_holes_&base&_&mode proc frame
invoke c_D2_holes,data_D2,11.0,12,13.0,14,15.0
ret
call_D2_holes_&base&_&mode endp
forward_D2_holes_&base&_&mode proc vectorcall frame a:D2,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_D2_holes,a,b,c1,d,e,f
ret
forward_D2_holes_&base&_&mode endp
endm
CASE_D2_holes rsp,1
CASE_D2_holes rsp,3
CASE_D2_holes rsp,5
CASE_D2_holes rsp,7
CASE_D2_holes rsp,11
CASE_D2_holes rsp,15
CASE_D2_holes rbp,1
CASE_D2_holes rbp,3
CASE_D2_holes rbp,5
CASE_D2_holes rbp,7
CASE_D2_holes rbp,11
CASE_D2_holes rbp,15

c_D2_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:D2
CASE_D2_fallback macro base,mode
option stackbase:base
option win64:mode
a_D2_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:D2
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D2_fallback_&base&_&mode endp
call_D2_fallback_&base&_&mode proc frame
invoke c_D2_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_D2
ret
call_D2_fallback_&base&_&mode endp
forward_D2_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:D2
invoke c_D2_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_D2_fallback_&base&_&mode endp
endm
CASE_D2_fallback rsp,1
CASE_D2_fallback rsp,3
CASE_D2_fallback rsp,5
CASE_D2_fallback rsp,7
CASE_D2_fallback rsp,11
CASE_D2_fallback rsp,15
CASE_D2_fallback rbp,1
CASE_D2_fallback rbp,3
CASE_D2_fallback rbp,5
CASE_D2_fallback rbp,7
CASE_D2_fallback rbp,11
CASE_D2_fallback rbp,15

c_D2_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:D2
CASE_D2_seventh macro base,mode
option stackbase:base
option win64:mode
a_D2_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:D2
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D2_seventh_&base&_&mode endp
call_D2_seventh_&base&_&mode proc frame
invoke c_D2_seventh,1,2,3,4,5,6,data_D2
ret
call_D2_seventh_&base&_&mode endp
forward_D2_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:D2
invoke c_D2_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_D2_seventh_&base&_&mode endp
endm
CASE_D2_seventh rsp,1
CASE_D2_seventh rsp,3
CASE_D2_seventh rsp,5
CASE_D2_seventh rsp,7
CASE_D2_seventh rsp,11
CASE_D2_seventh rsp,15
CASE_D2_seventh rbp,1
CASE_D2_seventh rbp,3
CASE_D2_seventh rbp,5
CASE_D2_seventh rbp,7
CASE_D2_seventh rbp,11
CASE_D2_seventh rbp,15

c_D3_alone proto vectorcall :D3
CASE_D3_alone macro base,mode
option stackbase:base
option win64:mode
a_D3_alone_&base&_&mode proc vectorcall frame a:D3
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+16]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D3_alone_&base&_&mode endp
call_D3_alone_&base&_&mode proc frame
invoke c_D3_alone,data_D3
ret
call_D3_alone_&base&_&mode endp
forward_D3_alone_&base&_&mode proc vectorcall frame a:D3
invoke c_D3_alone,a
ret
forward_D3_alone_&base&_&mode endp
endm
CASE_D3_alone rsp,1
CASE_D3_alone rsp,3
CASE_D3_alone rsp,5
CASE_D3_alone rsp,7
CASE_D3_alone rsp,11
CASE_D3_alone rsp,15
CASE_D3_alone rbp,1
CASE_D3_alone rbp,3
CASE_D3_alone rbp,5
CASE_D3_alone rbp,7
CASE_D3_alone rbp,11
CASE_D3_alone rbp,15

c_D3_holes proto vectorcall :D3,:real4,:qword,:real8,:qword,:real4
CASE_D3_holes macro base,mode
option stackbase:base
option win64:mode
a_D3_holes_&base&_&mode proc vectorcall frame a:D3,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D3_holes_&base&_&mode endp
call_D3_holes_&base&_&mode proc frame
invoke c_D3_holes,data_D3,11.0,12,13.0,14,15.0
ret
call_D3_holes_&base&_&mode endp
forward_D3_holes_&base&_&mode proc vectorcall frame a:D3,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_D3_holes,a,b,c1,d,e,f
ret
forward_D3_holes_&base&_&mode endp
endm
CASE_D3_holes rsp,1
CASE_D3_holes rsp,3
CASE_D3_holes rsp,5
CASE_D3_holes rsp,7
CASE_D3_holes rsp,11
CASE_D3_holes rsp,15
CASE_D3_holes rbp,1
CASE_D3_holes rbp,3
CASE_D3_holes rbp,5
CASE_D3_holes rbp,7
CASE_D3_holes rbp,11
CASE_D3_holes rbp,15

c_D3_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:D3
CASE_D3_fallback macro base,mode
option stackbase:base
option win64:mode
a_D3_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:D3
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+16]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D3_fallback_&base&_&mode endp
call_D3_fallback_&base&_&mode proc frame
invoke c_D3_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_D3
ret
call_D3_fallback_&base&_&mode endp
forward_D3_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:D3
invoke c_D3_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_D3_fallback_&base&_&mode endp
endm
CASE_D3_fallback rsp,1
CASE_D3_fallback rsp,3
CASE_D3_fallback rsp,5
CASE_D3_fallback rsp,7
CASE_D3_fallback rsp,11
CASE_D3_fallback rsp,15
CASE_D3_fallback rbp,1
CASE_D3_fallback rbp,3
CASE_D3_fallback rbp,5
CASE_D3_fallback rbp,7
CASE_D3_fallback rbp,11
CASE_D3_fallback rbp,15

c_D3_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:D3
CASE_D3_seventh macro base,mode
option stackbase:base
option win64:mode
a_D3_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:D3
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+16]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D3_seventh_&base&_&mode endp
call_D3_seventh_&base&_&mode proc frame
invoke c_D3_seventh,1,2,3,4,5,6,data_D3
ret
call_D3_seventh_&base&_&mode endp
forward_D3_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:D3
invoke c_D3_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_D3_seventh_&base&_&mode endp
endm
CASE_D3_seventh rsp,1
CASE_D3_seventh rsp,3
CASE_D3_seventh rsp,5
CASE_D3_seventh rsp,7
CASE_D3_seventh rsp,11
CASE_D3_seventh rsp,15
CASE_D3_seventh rbp,1
CASE_D3_seventh rbp,3
CASE_D3_seventh rbp,5
CASE_D3_seventh rbp,7
CASE_D3_seventh rbp,11
CASE_D3_seventh rbp,15

c_D4_alone proto vectorcall :D4
CASE_D4_alone macro base,mode
option stackbase:base
option win64:mode
a_D4_alone_&base&_&mode proc vectorcall frame a:D4
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+16]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+24]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D4_alone_&base&_&mode endp
call_D4_alone_&base&_&mode proc frame
invoke c_D4_alone,data_D4
ret
call_D4_alone_&base&_&mode endp
forward_D4_alone_&base&_&mode proc vectorcall frame a:D4
invoke c_D4_alone,a
ret
forward_D4_alone_&base&_&mode endp
endm
CASE_D4_alone rsp,1
CASE_D4_alone rsp,3
CASE_D4_alone rsp,5
CASE_D4_alone rsp,7
CASE_D4_alone rsp,11
CASE_D4_alone rsp,15
CASE_D4_alone rbp,1
CASE_D4_alone rbp,3
CASE_D4_alone rbp,5
CASE_D4_alone rbp,7
CASE_D4_alone rbp,11
CASE_D4_alone rbp,15

c_D4_holes proto vectorcall :D4,:real4,:qword,:real8,:qword,:real4
CASE_D4_holes macro base,mode
option stackbase:base
option win64:mode
a_D4_holes_&base&_&mode proc vectorcall frame a:D4,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+16]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D4_holes_&base&_&mode endp
call_D4_holes_&base&_&mode proc frame
invoke c_D4_holes,data_D4,11.0,12,13.0,14,15.0
ret
call_D4_holes_&base&_&mode endp
forward_D4_holes_&base&_&mode proc vectorcall frame a:D4,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_D4_holes,a,b,c1,d,e,f
ret
forward_D4_holes_&base&_&mode endp
endm
CASE_D4_holes rsp,1
CASE_D4_holes rsp,3
CASE_D4_holes rsp,5
CASE_D4_holes rsp,7
CASE_D4_holes rsp,11
CASE_D4_holes rsp,15
CASE_D4_holes rbp,1
CASE_D4_holes rbp,3
CASE_D4_holes rbp,5
CASE_D4_holes rbp,7
CASE_D4_holes rbp,11
CASE_D4_holes rbp,15

c_D4_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:D4
CASE_D4_fallback macro base,mode
option stackbase:base
option win64:mode
a_D4_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:D4
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+16]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+24]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D4_fallback_&base&_&mode endp
call_D4_fallback_&base&_&mode proc frame
invoke c_D4_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_D4
ret
call_D4_fallback_&base&_&mode endp
forward_D4_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:D4
invoke c_D4_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_D4_fallback_&base&_&mode endp
endm
CASE_D4_fallback rsp,1
CASE_D4_fallback rsp,3
CASE_D4_fallback rsp,5
CASE_D4_fallback rsp,7
CASE_D4_fallback rsp,11
CASE_D4_fallback rsp,15
CASE_D4_fallback rbp,1
CASE_D4_fallback rbp,3
CASE_D4_fallback rbp,5
CASE_D4_fallback rbp,7
CASE_D4_fallback rbp,11
CASE_D4_fallback rbp,15

c_D4_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:D4
CASE_D4_seventh macro base,mode
option stackbase:base
option win64:mode
a_D4_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:D4
pxor xmm5,xmm5
mov rax,a
movsd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+16]
addsd xmm5,xmm4
movsd xmm4,qword ptr [rax+24]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_D4_seventh_&base&_&mode endp
call_D4_seventh_&base&_&mode proc frame
invoke c_D4_seventh,1,2,3,4,5,6,data_D4
ret
call_D4_seventh_&base&_&mode endp
forward_D4_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:D4
invoke c_D4_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_D4_seventh_&base&_&mode endp
endm
CASE_D4_seventh rsp,1
CASE_D4_seventh rsp,3
CASE_D4_seventh rsp,5
CASE_D4_seventh rsp,7
CASE_D4_seventh rsp,11
CASE_D4_seventh rsp,15
CASE_D4_seventh rbp,1
CASE_D4_seventh rbp,3
CASE_D4_seventh rbp,5
CASE_D4_seventh rbp,7
CASE_D4_seventh rbp,11
CASE_D4_seventh rbp,15

c_V1_alone proto vectorcall :V1
CASE_V1_alone macro base,mode
option stackbase:base
option win64:mode
a_V1_alone_&base&_&mode proc vectorcall frame a:V1
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V1_alone_&base&_&mode endp
call_V1_alone_&base&_&mode proc frame
invoke c_V1_alone,data_V1
ret
call_V1_alone_&base&_&mode endp
forward_V1_alone_&base&_&mode proc vectorcall frame a:V1
invoke c_V1_alone,a
ret
forward_V1_alone_&base&_&mode endp
endm
CASE_V1_alone rsp,1
CASE_V1_alone rsp,3
CASE_V1_alone rsp,5
CASE_V1_alone rsp,7
CASE_V1_alone rsp,11
CASE_V1_alone rsp,15
CASE_V1_alone rbp,1
CASE_V1_alone rbp,3
CASE_V1_alone rbp,5
CASE_V1_alone rbp,7
CASE_V1_alone rbp,11
CASE_V1_alone rbp,15

c_V1_holes proto vectorcall :V1,:real4,:qword,:real8,:qword,:real4
CASE_V1_holes macro base,mode
option stackbase:base
option win64:mode
a_V1_holes_&base&_&mode proc vectorcall frame a:V1,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V1_holes_&base&_&mode endp
call_V1_holes_&base&_&mode proc frame
invoke c_V1_holes,data_V1,11.0,12,13.0,14,15.0
ret
call_V1_holes_&base&_&mode endp
forward_V1_holes_&base&_&mode proc vectorcall frame a:V1,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_V1_holes,a,b,c1,d,e,f
ret
forward_V1_holes_&base&_&mode endp
endm
CASE_V1_holes rsp,1
CASE_V1_holes rsp,3
CASE_V1_holes rsp,5
CASE_V1_holes rsp,7
CASE_V1_holes rsp,11
CASE_V1_holes rsp,15
CASE_V1_holes rbp,1
CASE_V1_holes rbp,3
CASE_V1_holes rbp,5
CASE_V1_holes rbp,7
CASE_V1_holes rbp,11
CASE_V1_holes rbp,15

c_V1_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:V1
CASE_V1_fallback macro base,mode
option stackbase:base
option win64:mode
a_V1_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:V1
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V1_fallback_&base&_&mode endp
call_V1_fallback_&base&_&mode proc frame
invoke c_V1_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_V1
ret
call_V1_fallback_&base&_&mode endp
forward_V1_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:V1
invoke c_V1_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_V1_fallback_&base&_&mode endp
endm
CASE_V1_fallback rsp,1
CASE_V1_fallback rsp,3
CASE_V1_fallback rsp,5
CASE_V1_fallback rsp,7
CASE_V1_fallback rsp,11
CASE_V1_fallback rsp,15
CASE_V1_fallback rbp,1
CASE_V1_fallback rbp,3
CASE_V1_fallback rbp,5
CASE_V1_fallback rbp,7
CASE_V1_fallback rbp,11
CASE_V1_fallback rbp,15

c_V1_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:V1
CASE_V1_seventh macro base,mode
option stackbase:base
option win64:mode
a_V1_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:V1
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V1_seventh_&base&_&mode endp
call_V1_seventh_&base&_&mode proc frame
invoke c_V1_seventh,1,2,3,4,5,6,data_V1
ret
call_V1_seventh_&base&_&mode endp
forward_V1_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:V1
invoke c_V1_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_V1_seventh_&base&_&mode endp
endm
CASE_V1_seventh rsp,1
CASE_V1_seventh rsp,3
CASE_V1_seventh rsp,5
CASE_V1_seventh rsp,7
CASE_V1_seventh rsp,11
CASE_V1_seventh rsp,15
CASE_V1_seventh rbp,1
CASE_V1_seventh rbp,3
CASE_V1_seventh rbp,5
CASE_V1_seventh rbp,7
CASE_V1_seventh rbp,11
CASE_V1_seventh rbp,15

c_V2_alone proto vectorcall :V2
CASE_V2_alone macro base,mode
option stackbase:base
option win64:mode
a_V2_alone_&base&_&mode proc vectorcall frame a:V2
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V2_alone_&base&_&mode endp
call_V2_alone_&base&_&mode proc frame
invoke c_V2_alone,data_V2
ret
call_V2_alone_&base&_&mode endp
forward_V2_alone_&base&_&mode proc vectorcall frame a:V2
invoke c_V2_alone,a
ret
forward_V2_alone_&base&_&mode endp
endm
CASE_V2_alone rsp,1
CASE_V2_alone rsp,3
CASE_V2_alone rsp,5
CASE_V2_alone rsp,7
CASE_V2_alone rsp,11
CASE_V2_alone rsp,15
CASE_V2_alone rbp,1
CASE_V2_alone rbp,3
CASE_V2_alone rbp,5
CASE_V2_alone rbp,7
CASE_V2_alone rbp,11
CASE_V2_alone rbp,15

c_V2_holes proto vectorcall :V2,:real4,:qword,:real8,:qword,:real4
CASE_V2_holes macro base,mode
option stackbase:base
option win64:mode
a_V2_holes_&base&_&mode proc vectorcall frame a:V2,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V2_holes_&base&_&mode endp
call_V2_holes_&base&_&mode proc frame
invoke c_V2_holes,data_V2,11.0,12,13.0,14,15.0
ret
call_V2_holes_&base&_&mode endp
forward_V2_holes_&base&_&mode proc vectorcall frame a:V2,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_V2_holes,a,b,c1,d,e,f
ret
forward_V2_holes_&base&_&mode endp
endm
CASE_V2_holes rsp,1
CASE_V2_holes rsp,3
CASE_V2_holes rsp,5
CASE_V2_holes rsp,7
CASE_V2_holes rsp,11
CASE_V2_holes rsp,15
CASE_V2_holes rbp,1
CASE_V2_holes rbp,3
CASE_V2_holes rbp,5
CASE_V2_holes rbp,7
CASE_V2_holes rbp,11
CASE_V2_holes rbp,15

c_V2_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:V2
CASE_V2_fallback macro base,mode
option stackbase:base
option win64:mode
a_V2_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:V2
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V2_fallback_&base&_&mode endp
call_V2_fallback_&base&_&mode proc frame
invoke c_V2_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_V2
ret
call_V2_fallback_&base&_&mode endp
forward_V2_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:V2
invoke c_V2_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_V2_fallback_&base&_&mode endp
endm
CASE_V2_fallback rsp,1
CASE_V2_fallback rsp,3
CASE_V2_fallback rsp,5
CASE_V2_fallback rsp,7
CASE_V2_fallback rsp,11
CASE_V2_fallback rsp,15
CASE_V2_fallback rbp,1
CASE_V2_fallback rbp,3
CASE_V2_fallback rbp,5
CASE_V2_fallback rbp,7
CASE_V2_fallback rbp,11
CASE_V2_fallback rbp,15

c_V2_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:V2
CASE_V2_seventh macro base,mode
option stackbase:base
option win64:mode
a_V2_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:V2
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V2_seventh_&base&_&mode endp
call_V2_seventh_&base&_&mode proc frame
invoke c_V2_seventh,1,2,3,4,5,6,data_V2
ret
call_V2_seventh_&base&_&mode endp
forward_V2_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:V2
invoke c_V2_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_V2_seventh_&base&_&mode endp
endm
CASE_V2_seventh rsp,1
CASE_V2_seventh rsp,3
CASE_V2_seventh rsp,5
CASE_V2_seventh rsp,7
CASE_V2_seventh rsp,11
CASE_V2_seventh rsp,15
CASE_V2_seventh rbp,1
CASE_V2_seventh rbp,3
CASE_V2_seventh rbp,5
CASE_V2_seventh rbp,7
CASE_V2_seventh rbp,11
CASE_V2_seventh rbp,15

c_V3_alone proto vectorcall :V3
CASE_V3_alone macro base,mode
option stackbase:base
option win64:mode
a_V3_alone_&base&_&mode proc vectorcall frame a:V3
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V3_alone_&base&_&mode endp
call_V3_alone_&base&_&mode proc frame
invoke c_V3_alone,data_V3
ret
call_V3_alone_&base&_&mode endp
forward_V3_alone_&base&_&mode proc vectorcall frame a:V3
invoke c_V3_alone,a
ret
forward_V3_alone_&base&_&mode endp
endm
CASE_V3_alone rsp,1
CASE_V3_alone rsp,3
CASE_V3_alone rsp,5
CASE_V3_alone rsp,7
CASE_V3_alone rsp,11
CASE_V3_alone rsp,15
CASE_V3_alone rbp,1
CASE_V3_alone rbp,3
CASE_V3_alone rbp,5
CASE_V3_alone rbp,7
CASE_V3_alone rbp,11
CASE_V3_alone rbp,15

c_V3_holes proto vectorcall :V3,:real4,:qword,:real8,:qword,:real4
CASE_V3_holes macro base,mode
option stackbase:base
option win64:mode
a_V3_holes_&base&_&mode proc vectorcall frame a:V3,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V3_holes_&base&_&mode endp
call_V3_holes_&base&_&mode proc frame
invoke c_V3_holes,data_V3,11.0,12,13.0,14,15.0
ret
call_V3_holes_&base&_&mode endp
forward_V3_holes_&base&_&mode proc vectorcall frame a:V3,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_V3_holes,a,b,c1,d,e,f
ret
forward_V3_holes_&base&_&mode endp
endm
CASE_V3_holes rsp,1
CASE_V3_holes rsp,3
CASE_V3_holes rsp,5
CASE_V3_holes rsp,7
CASE_V3_holes rsp,11
CASE_V3_holes rsp,15
CASE_V3_holes rbp,1
CASE_V3_holes rbp,3
CASE_V3_holes rbp,5
CASE_V3_holes rbp,7
CASE_V3_holes rbp,11
CASE_V3_holes rbp,15

c_V3_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:V3
CASE_V3_fallback macro base,mode
option stackbase:base
option win64:mode
a_V3_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:V3
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V3_fallback_&base&_&mode endp
call_V3_fallback_&base&_&mode proc frame
invoke c_V3_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_V3
ret
call_V3_fallback_&base&_&mode endp
forward_V3_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:V3
invoke c_V3_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_V3_fallback_&base&_&mode endp
endm
CASE_V3_fallback rsp,1
CASE_V3_fallback rsp,3
CASE_V3_fallback rsp,5
CASE_V3_fallback rsp,7
CASE_V3_fallback rsp,11
CASE_V3_fallback rsp,15
CASE_V3_fallback rbp,1
CASE_V3_fallback rbp,3
CASE_V3_fallback rbp,5
CASE_V3_fallback rbp,7
CASE_V3_fallback rbp,11
CASE_V3_fallback rbp,15

c_V3_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:V3
CASE_V3_seventh macro base,mode
option stackbase:base
option win64:mode
a_V3_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:V3
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V3_seventh_&base&_&mode endp
call_V3_seventh_&base&_&mode proc frame
invoke c_V3_seventh,1,2,3,4,5,6,data_V3
ret
call_V3_seventh_&base&_&mode endp
forward_V3_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:V3
invoke c_V3_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_V3_seventh_&base&_&mode endp
endm
CASE_V3_seventh rsp,1
CASE_V3_seventh rsp,3
CASE_V3_seventh rsp,5
CASE_V3_seventh rsp,7
CASE_V3_seventh rsp,11
CASE_V3_seventh rsp,15
CASE_V3_seventh rbp,1
CASE_V3_seventh rbp,3
CASE_V3_seventh rbp,5
CASE_V3_seventh rbp,7
CASE_V3_seventh rbp,11
CASE_V3_seventh rbp,15

c_V4_alone proto vectorcall :V4
CASE_V4_alone macro base,mode
option stackbase:base
option win64:mode
a_V4_alone_&base&_&mode proc vectorcall frame a:V4
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V4_alone_&base&_&mode endp
call_V4_alone_&base&_&mode proc frame
invoke c_V4_alone,data_V4
ret
call_V4_alone_&base&_&mode endp
forward_V4_alone_&base&_&mode proc vectorcall frame a:V4
invoke c_V4_alone,a
ret
forward_V4_alone_&base&_&mode endp
endm
CASE_V4_alone rsp,1
CASE_V4_alone rsp,3
CASE_V4_alone rsp,5
CASE_V4_alone rsp,7
CASE_V4_alone rsp,11
CASE_V4_alone rsp,15
CASE_V4_alone rbp,1
CASE_V4_alone rbp,3
CASE_V4_alone rbp,5
CASE_V4_alone rbp,7
CASE_V4_alone rbp,11
CASE_V4_alone rbp,15

c_V4_holes proto vectorcall :V4,:real4,:qword,:real8,:qword,:real4
CASE_V4_holes macro base,mode
option stackbase:base
option win64:mode
a_V4_holes_&base&_&mode proc vectorcall frame a:V4,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V4_holes_&base&_&mode endp
call_V4_holes_&base&_&mode proc frame
invoke c_V4_holes,data_V4,11.0,12,13.0,14,15.0
ret
call_V4_holes_&base&_&mode endp
forward_V4_holes_&base&_&mode proc vectorcall frame a:V4,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_V4_holes,a,b,c1,d,e,f
ret
forward_V4_holes_&base&_&mode endp
endm
CASE_V4_holes rsp,1
CASE_V4_holes rsp,3
CASE_V4_holes rsp,5
CASE_V4_holes rsp,7
CASE_V4_holes rsp,11
CASE_V4_holes rsp,15
CASE_V4_holes rbp,1
CASE_V4_holes rbp,3
CASE_V4_holes rbp,5
CASE_V4_holes rbp,7
CASE_V4_holes rbp,11
CASE_V4_holes rbp,15

c_V4_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:V4
CASE_V4_fallback macro base,mode
option stackbase:base
option win64:mode
a_V4_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:V4
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V4_fallback_&base&_&mode endp
call_V4_fallback_&base&_&mode proc frame
invoke c_V4_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_V4
ret
call_V4_fallback_&base&_&mode endp
forward_V4_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:V4
invoke c_V4_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_V4_fallback_&base&_&mode endp
endm
CASE_V4_fallback rsp,1
CASE_V4_fallback rsp,3
CASE_V4_fallback rsp,5
CASE_V4_fallback rsp,7
CASE_V4_fallback rsp,11
CASE_V4_fallback rsp,15
CASE_V4_fallback rbp,1
CASE_V4_fallback rbp,3
CASE_V4_fallback rbp,5
CASE_V4_fallback rbp,7
CASE_V4_fallback rbp,11
CASE_V4_fallback rbp,15

c_V4_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:V4
CASE_V4_seventh macro base,mode
option stackbase:base
option win64:mode
a_V4_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:V4
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_V4_seventh_&base&_&mode endp
call_V4_seventh_&base&_&mode proc frame
invoke c_V4_seventh,1,2,3,4,5,6,data_V4
ret
call_V4_seventh_&base&_&mode endp
forward_V4_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:V4
invoke c_V4_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_V4_seventh_&base&_&mode endp
endm
CASE_V4_seventh rsp,1
CASE_V4_seventh rsp,3
CASE_V4_seventh rsp,5
CASE_V4_seventh rsp,7
CASE_V4_seventh rsp,11
CASE_V4_seventh rsp,15
CASE_V4_seventh rbp,1
CASE_V4_seventh rbp,3
CASE_V4_seventh rbp,5
CASE_V4_seventh rbp,7
CASE_V4_seventh rbp,11
CASE_V4_seventh rbp,15

c_Y1_alone proto vectorcall :Y1
CASE_Y1_alone macro base,mode
option stackbase:base
option win64:mode
a_Y1_alone_&base&_&mode proc vectorcall frame a:Y1
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y1_alone_&base&_&mode endp
call_Y1_alone_&base&_&mode proc frame
invoke c_Y1_alone,data_Y1
ret
call_Y1_alone_&base&_&mode endp
forward_Y1_alone_&base&_&mode proc vectorcall frame a:Y1
invoke c_Y1_alone,a
ret
forward_Y1_alone_&base&_&mode endp
endm
CASE_Y1_alone rsp,1
CASE_Y1_alone rsp,3
CASE_Y1_alone rsp,5
CASE_Y1_alone rsp,7
CASE_Y1_alone rsp,11
CASE_Y1_alone rsp,15
CASE_Y1_alone rbp,1
CASE_Y1_alone rbp,3
CASE_Y1_alone rbp,5
CASE_Y1_alone rbp,7
CASE_Y1_alone rbp,11
CASE_Y1_alone rbp,15

c_Y1_holes proto vectorcall :Y1,:real4,:qword,:real8,:qword,:real4
CASE_Y1_holes macro base,mode
option stackbase:base
option win64:mode
a_Y1_holes_&base&_&mode proc vectorcall frame a:Y1,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y1_holes_&base&_&mode endp
call_Y1_holes_&base&_&mode proc frame
invoke c_Y1_holes,data_Y1,11.0,12,13.0,14,15.0
ret
call_Y1_holes_&base&_&mode endp
forward_Y1_holes_&base&_&mode proc vectorcall frame a:Y1,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_Y1_holes,a,b,c1,d,e,f
ret
forward_Y1_holes_&base&_&mode endp
endm
CASE_Y1_holes rsp,1
CASE_Y1_holes rsp,3
CASE_Y1_holes rsp,5
CASE_Y1_holes rsp,7
CASE_Y1_holes rsp,11
CASE_Y1_holes rsp,15
CASE_Y1_holes rbp,1
CASE_Y1_holes rbp,3
CASE_Y1_holes rbp,5
CASE_Y1_holes rbp,7
CASE_Y1_holes rbp,11
CASE_Y1_holes rbp,15

c_Y1_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:Y1
CASE_Y1_fallback macro base,mode
option stackbase:base
option win64:mode
a_Y1_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:Y1
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y1_fallback_&base&_&mode endp
call_Y1_fallback_&base&_&mode proc frame
invoke c_Y1_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_Y1
ret
call_Y1_fallback_&base&_&mode endp
forward_Y1_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:Y1
invoke c_Y1_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_Y1_fallback_&base&_&mode endp
endm
CASE_Y1_fallback rsp,1
CASE_Y1_fallback rsp,3
CASE_Y1_fallback rsp,5
CASE_Y1_fallback rsp,7
CASE_Y1_fallback rsp,11
CASE_Y1_fallback rsp,15
CASE_Y1_fallback rbp,1
CASE_Y1_fallback rbp,3
CASE_Y1_fallback rbp,5
CASE_Y1_fallback rbp,7
CASE_Y1_fallback rbp,11
CASE_Y1_fallback rbp,15

c_Y1_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:Y1
CASE_Y1_seventh macro base,mode
option stackbase:base
option win64:mode
a_Y1_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:Y1
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y1_seventh_&base&_&mode endp
call_Y1_seventh_&base&_&mode proc frame
invoke c_Y1_seventh,1,2,3,4,5,6,data_Y1
ret
call_Y1_seventh_&base&_&mode endp
forward_Y1_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:Y1
invoke c_Y1_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_Y1_seventh_&base&_&mode endp
endm
CASE_Y1_seventh rsp,1
CASE_Y1_seventh rsp,3
CASE_Y1_seventh rsp,5
CASE_Y1_seventh rsp,7
CASE_Y1_seventh rsp,11
CASE_Y1_seventh rsp,15
CASE_Y1_seventh rbp,1
CASE_Y1_seventh rbp,3
CASE_Y1_seventh rbp,5
CASE_Y1_seventh rbp,7
CASE_Y1_seventh rbp,11
CASE_Y1_seventh rbp,15

c_Y2_alone proto vectorcall :Y2
CASE_Y2_alone macro base,mode
option stackbase:base
option win64:mode
a_Y2_alone_&base&_&mode proc vectorcall frame a:Y2
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y2_alone_&base&_&mode endp
call_Y2_alone_&base&_&mode proc frame
invoke c_Y2_alone,data_Y2
ret
call_Y2_alone_&base&_&mode endp
forward_Y2_alone_&base&_&mode proc vectorcall frame a:Y2
invoke c_Y2_alone,a
ret
forward_Y2_alone_&base&_&mode endp
endm
CASE_Y2_alone rsp,1
CASE_Y2_alone rsp,3
CASE_Y2_alone rsp,5
CASE_Y2_alone rsp,7
CASE_Y2_alone rsp,11
CASE_Y2_alone rsp,15
CASE_Y2_alone rbp,1
CASE_Y2_alone rbp,3
CASE_Y2_alone rbp,5
CASE_Y2_alone rbp,7
CASE_Y2_alone rbp,11
CASE_Y2_alone rbp,15

c_Y2_holes proto vectorcall :Y2,:real4,:qword,:real8,:qword,:real4
CASE_Y2_holes macro base,mode
option stackbase:base
option win64:mode
a_Y2_holes_&base&_&mode proc vectorcall frame a:Y2,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y2_holes_&base&_&mode endp
call_Y2_holes_&base&_&mode proc frame
invoke c_Y2_holes,data_Y2,11.0,12,13.0,14,15.0
ret
call_Y2_holes_&base&_&mode endp
forward_Y2_holes_&base&_&mode proc vectorcall frame a:Y2,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_Y2_holes,a,b,c1,d,e,f
ret
forward_Y2_holes_&base&_&mode endp
endm
CASE_Y2_holes rsp,1
CASE_Y2_holes rsp,3
CASE_Y2_holes rsp,5
CASE_Y2_holes rsp,7
CASE_Y2_holes rsp,11
CASE_Y2_holes rsp,15
CASE_Y2_holes rbp,1
CASE_Y2_holes rbp,3
CASE_Y2_holes rbp,5
CASE_Y2_holes rbp,7
CASE_Y2_holes rbp,11
CASE_Y2_holes rbp,15

c_Y2_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:Y2
CASE_Y2_fallback macro base,mode
option stackbase:base
option win64:mode
a_Y2_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:Y2
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y2_fallback_&base&_&mode endp
call_Y2_fallback_&base&_&mode proc frame
invoke c_Y2_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_Y2
ret
call_Y2_fallback_&base&_&mode endp
forward_Y2_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:Y2
invoke c_Y2_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_Y2_fallback_&base&_&mode endp
endm
CASE_Y2_fallback rsp,1
CASE_Y2_fallback rsp,3
CASE_Y2_fallback rsp,5
CASE_Y2_fallback rsp,7
CASE_Y2_fallback rsp,11
CASE_Y2_fallback rsp,15
CASE_Y2_fallback rbp,1
CASE_Y2_fallback rbp,3
CASE_Y2_fallback rbp,5
CASE_Y2_fallback rbp,7
CASE_Y2_fallback rbp,11
CASE_Y2_fallback rbp,15

c_Y2_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:Y2
CASE_Y2_seventh macro base,mode
option stackbase:base
option win64:mode
a_Y2_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:Y2
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y2_seventh_&base&_&mode endp
call_Y2_seventh_&base&_&mode proc frame
invoke c_Y2_seventh,1,2,3,4,5,6,data_Y2
ret
call_Y2_seventh_&base&_&mode endp
forward_Y2_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:Y2
invoke c_Y2_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_Y2_seventh_&base&_&mode endp
endm
CASE_Y2_seventh rsp,1
CASE_Y2_seventh rsp,3
CASE_Y2_seventh rsp,5
CASE_Y2_seventh rsp,7
CASE_Y2_seventh rsp,11
CASE_Y2_seventh rsp,15
CASE_Y2_seventh rbp,1
CASE_Y2_seventh rbp,3
CASE_Y2_seventh rbp,5
CASE_Y2_seventh rbp,7
CASE_Y2_seventh rbp,11
CASE_Y2_seventh rbp,15

c_Y3_alone proto vectorcall :Y3
CASE_Y3_alone macro base,mode
option stackbase:base
option win64:mode
a_Y3_alone_&base&_&mode proc vectorcall frame a:Y3
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+64]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+68]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+72]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+76]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+80]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+84]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+88]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+92]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y3_alone_&base&_&mode endp
call_Y3_alone_&base&_&mode proc frame
invoke c_Y3_alone,data_Y3
ret
call_Y3_alone_&base&_&mode endp
forward_Y3_alone_&base&_&mode proc vectorcall frame a:Y3
invoke c_Y3_alone,a
ret
forward_Y3_alone_&base&_&mode endp
endm
CASE_Y3_alone rsp,1
CASE_Y3_alone rsp,3
CASE_Y3_alone rsp,5
CASE_Y3_alone rsp,7
CASE_Y3_alone rsp,11
CASE_Y3_alone rsp,15
CASE_Y3_alone rbp,1
CASE_Y3_alone rbp,3
CASE_Y3_alone rbp,5
CASE_Y3_alone rbp,7
CASE_Y3_alone rbp,11
CASE_Y3_alone rbp,15

c_Y3_holes proto vectorcall :Y3,:real4,:qword,:real8,:qword,:real4
CASE_Y3_holes macro base,mode
option stackbase:base
option win64:mode
a_Y3_holes_&base&_&mode proc vectorcall frame a:Y3,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+64]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+68]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+72]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+76]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+80]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+84]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+88]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+92]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y3_holes_&base&_&mode endp
call_Y3_holes_&base&_&mode proc frame
invoke c_Y3_holes,data_Y3,11.0,12,13.0,14,15.0
ret
call_Y3_holes_&base&_&mode endp
forward_Y3_holes_&base&_&mode proc vectorcall frame a:Y3,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_Y3_holes,a,b,c1,d,e,f
ret
forward_Y3_holes_&base&_&mode endp
endm
CASE_Y3_holes rsp,1
CASE_Y3_holes rsp,3
CASE_Y3_holes rsp,5
CASE_Y3_holes rsp,7
CASE_Y3_holes rsp,11
CASE_Y3_holes rsp,15
CASE_Y3_holes rbp,1
CASE_Y3_holes rbp,3
CASE_Y3_holes rbp,5
CASE_Y3_holes rbp,7
CASE_Y3_holes rbp,11
CASE_Y3_holes rbp,15

c_Y3_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:Y3
CASE_Y3_fallback macro base,mode
option stackbase:base
option win64:mode
a_Y3_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:Y3
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+64]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+68]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+72]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+76]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+80]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+84]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+88]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+92]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y3_fallback_&base&_&mode endp
call_Y3_fallback_&base&_&mode proc frame
invoke c_Y3_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_Y3
ret
call_Y3_fallback_&base&_&mode endp
forward_Y3_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:Y3
invoke c_Y3_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_Y3_fallback_&base&_&mode endp
endm
CASE_Y3_fallback rsp,1
CASE_Y3_fallback rsp,3
CASE_Y3_fallback rsp,5
CASE_Y3_fallback rsp,7
CASE_Y3_fallback rsp,11
CASE_Y3_fallback rsp,15
CASE_Y3_fallback rbp,1
CASE_Y3_fallback rbp,3
CASE_Y3_fallback rbp,5
CASE_Y3_fallback rbp,7
CASE_Y3_fallback rbp,11
CASE_Y3_fallback rbp,15

c_Y3_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:Y3
CASE_Y3_seventh macro base,mode
option stackbase:base
option win64:mode
a_Y3_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:Y3
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+64]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+68]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+72]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+76]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+80]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+84]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+88]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+92]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y3_seventh_&base&_&mode endp
call_Y3_seventh_&base&_&mode proc frame
invoke c_Y3_seventh,1,2,3,4,5,6,data_Y3
ret
call_Y3_seventh_&base&_&mode endp
forward_Y3_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:Y3
invoke c_Y3_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_Y3_seventh_&base&_&mode endp
endm
CASE_Y3_seventh rsp,1
CASE_Y3_seventh rsp,3
CASE_Y3_seventh rsp,5
CASE_Y3_seventh rsp,7
CASE_Y3_seventh rsp,11
CASE_Y3_seventh rsp,15
CASE_Y3_seventh rbp,1
CASE_Y3_seventh rbp,3
CASE_Y3_seventh rbp,5
CASE_Y3_seventh rbp,7
CASE_Y3_seventh rbp,11
CASE_Y3_seventh rbp,15

c_Y4_alone proto vectorcall :Y4
CASE_Y4_alone macro base,mode
option stackbase:base
option win64:mode
a_Y4_alone_&base&_&mode proc vectorcall frame a:Y4
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+64]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+68]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+72]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+76]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+80]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+84]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+88]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+92]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+96]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+100]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+104]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+108]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+112]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+116]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+120]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+124]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y4_alone_&base&_&mode endp
call_Y4_alone_&base&_&mode proc frame
invoke c_Y4_alone,data_Y4
ret
call_Y4_alone_&base&_&mode endp
forward_Y4_alone_&base&_&mode proc vectorcall frame a:Y4
invoke c_Y4_alone,a
ret
forward_Y4_alone_&base&_&mode endp
endm
CASE_Y4_alone rsp,1
CASE_Y4_alone rsp,3
CASE_Y4_alone rsp,5
CASE_Y4_alone rsp,7
CASE_Y4_alone rsp,11
CASE_Y4_alone rsp,15
CASE_Y4_alone rbp,1
CASE_Y4_alone rbp,3
CASE_Y4_alone rbp,5
CASE_Y4_alone rbp,7
CASE_Y4_alone rbp,11
CASE_Y4_alone rbp,15

c_Y4_holes proto vectorcall :Y4,:real4,:qword,:real8,:qword,:real4
CASE_Y4_holes macro base,mode
option stackbase:base
option win64:mode
a_Y4_holes_&base&_&mode proc vectorcall frame a:Y4,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+64]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+68]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+72]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+76]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+80]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+84]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+88]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+92]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+96]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+100]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+104]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+108]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+112]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+116]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+120]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+124]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y4_holes_&base&_&mode endp
call_Y4_holes_&base&_&mode proc frame
invoke c_Y4_holes,data_Y4,11.0,12,13.0,14,15.0
ret
call_Y4_holes_&base&_&mode endp
forward_Y4_holes_&base&_&mode proc vectorcall frame a:Y4,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_Y4_holes,a,b,c1,d,e,f
ret
forward_Y4_holes_&base&_&mode endp
endm
CASE_Y4_holes rsp,1
CASE_Y4_holes rsp,3
CASE_Y4_holes rsp,5
CASE_Y4_holes rsp,7
CASE_Y4_holes rsp,11
CASE_Y4_holes rsp,15
CASE_Y4_holes rbp,1
CASE_Y4_holes rbp,3
CASE_Y4_holes rbp,5
CASE_Y4_holes rbp,7
CASE_Y4_holes rbp,11
CASE_Y4_holes rbp,15

c_Y4_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:Y4
CASE_Y4_fallback macro base,mode
option stackbase:base
option win64:mode
a_Y4_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:Y4
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+64]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+68]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+72]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+76]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+80]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+84]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+88]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+92]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+96]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+100]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+104]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+108]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+112]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+116]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+120]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+124]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y4_fallback_&base&_&mode endp
call_Y4_fallback_&base&_&mode proc frame
invoke c_Y4_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_Y4
ret
call_Y4_fallback_&base&_&mode endp
forward_Y4_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:Y4
invoke c_Y4_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_Y4_fallback_&base&_&mode endp
endm
CASE_Y4_fallback rsp,1
CASE_Y4_fallback rsp,3
CASE_Y4_fallback rsp,5
CASE_Y4_fallback rsp,7
CASE_Y4_fallback rsp,11
CASE_Y4_fallback rsp,15
CASE_Y4_fallback rbp,1
CASE_Y4_fallback rbp,3
CASE_Y4_fallback rbp,5
CASE_Y4_fallback rbp,7
CASE_Y4_fallback rbp,11
CASE_Y4_fallback rbp,15

c_Y4_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:Y4
CASE_Y4_seventh macro base,mode
option stackbase:base
option win64:mode
a_Y4_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:Y4
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+32]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+36]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+40]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+44]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+48]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+52]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+56]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+60]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+64]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+68]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+72]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+76]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+80]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+84]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+88]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+92]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+96]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+100]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+104]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+108]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+112]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+116]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+120]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+124]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Y4_seventh_&base&_&mode endp
call_Y4_seventh_&base&_&mode proc frame
invoke c_Y4_seventh,1,2,3,4,5,6,data_Y4
ret
call_Y4_seventh_&base&_&mode endp
forward_Y4_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:Y4
invoke c_Y4_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_Y4_seventh_&base&_&mode endp
endm
CASE_Y4_seventh rsp,1
CASE_Y4_seventh rsp,3
CASE_Y4_seventh rsp,5
CASE_Y4_seventh rsp,7
CASE_Y4_seventh rsp,11
CASE_Y4_seventh rsp,15
CASE_Y4_seventh rbp,1
CASE_Y4_seventh rbp,3
CASE_Y4_seventh rbp,5
CASE_Y4_seventh rbp,7
CASE_Y4_seventh rbp,11
CASE_Y4_seventh rbp,15

c_NF_alone proto vectorcall :NF
CASE_NF_alone macro base,mode
option stackbase:base
option win64:mode
a_NF_alone_&base&_&mode proc vectorcall frame a:NF
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_NF_alone_&base&_&mode endp
call_NF_alone_&base&_&mode proc frame
invoke c_NF_alone,data_NF
ret
call_NF_alone_&base&_&mode endp
forward_NF_alone_&base&_&mode proc vectorcall frame a:NF
invoke c_NF_alone,a
ret
forward_NF_alone_&base&_&mode endp
endm
CASE_NF_alone rsp,1
CASE_NF_alone rsp,3
CASE_NF_alone rsp,5
CASE_NF_alone rsp,7
CASE_NF_alone rsp,11
CASE_NF_alone rsp,15
CASE_NF_alone rbp,1
CASE_NF_alone rbp,3
CASE_NF_alone rbp,5
CASE_NF_alone rbp,7
CASE_NF_alone rbp,11
CASE_NF_alone rbp,15

c_NF_holes proto vectorcall :NF,:real4,:qword,:real8,:qword,:real4
CASE_NF_holes macro base,mode
option stackbase:base
option win64:mode
a_NF_holes_&base&_&mode proc vectorcall frame a:NF,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_NF_holes_&base&_&mode endp
call_NF_holes_&base&_&mode proc frame
invoke c_NF_holes,data_NF,11.0,12,13.0,14,15.0
ret
call_NF_holes_&base&_&mode endp
forward_NF_holes_&base&_&mode proc vectorcall frame a:NF,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_NF_holes,a,b,c1,d,e,f
ret
forward_NF_holes_&base&_&mode endp
endm
CASE_NF_holes rsp,1
CASE_NF_holes rsp,3
CASE_NF_holes rsp,5
CASE_NF_holes rsp,7
CASE_NF_holes rsp,11
CASE_NF_holes rsp,15
CASE_NF_holes rbp,1
CASE_NF_holes rbp,3
CASE_NF_holes rbp,5
CASE_NF_holes rbp,7
CASE_NF_holes rbp,11
CASE_NF_holes rbp,15

c_NF_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:NF
CASE_NF_fallback macro base,mode
option stackbase:base
option win64:mode
a_NF_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:NF
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_NF_fallback_&base&_&mode endp
call_NF_fallback_&base&_&mode proc frame
invoke c_NF_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_NF
ret
call_NF_fallback_&base&_&mode endp
forward_NF_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:NF
invoke c_NF_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_NF_fallback_&base&_&mode endp
endm
CASE_NF_fallback rsp,1
CASE_NF_fallback rsp,3
CASE_NF_fallback rsp,5
CASE_NF_fallback rsp,7
CASE_NF_fallback rsp,11
CASE_NF_fallback rsp,15
CASE_NF_fallback rbp,1
CASE_NF_fallback rbp,3
CASE_NF_fallback rbp,5
CASE_NF_fallback rbp,7
CASE_NF_fallback rbp,11
CASE_NF_fallback rbp,15

c_NF_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:NF
CASE_NF_seventh macro base,mode
option stackbase:base
option win64:mode
a_NF_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:NF
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_NF_seventh_&base&_&mode endp
call_NF_seventh_&base&_&mode proc frame
invoke c_NF_seventh,1,2,3,4,5,6,data_NF
ret
call_NF_seventh_&base&_&mode endp
forward_NF_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:NF
invoke c_NF_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_NF_seventh_&base&_&mode endp
endm
CASE_NF_seventh rsp,1
CASE_NF_seventh rsp,3
CASE_NF_seventh rsp,5
CASE_NF_seventh rsp,7
CASE_NF_seventh rsp,11
CASE_NF_seventh rsp,15
CASE_NF_seventh rbp,1
CASE_NF_seventh rbp,3
CASE_NF_seventh rbp,5
CASE_NF_seventh rbp,7
CASE_NF_seventh rbp,11
CASE_NF_seventh rbp,15

c_AF_alone proto vectorcall :AF
CASE_AF_alone macro base,mode
option stackbase:base
option win64:mode
a_AF_alone_&base&_&mode proc vectorcall frame a:AF
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_AF_alone_&base&_&mode endp
call_AF_alone_&base&_&mode proc frame
invoke c_AF_alone,data_AF
ret
call_AF_alone_&base&_&mode endp
forward_AF_alone_&base&_&mode proc vectorcall frame a:AF
invoke c_AF_alone,a
ret
forward_AF_alone_&base&_&mode endp
endm
CASE_AF_alone rsp,1
CASE_AF_alone rsp,3
CASE_AF_alone rsp,5
CASE_AF_alone rsp,7
CASE_AF_alone rsp,11
CASE_AF_alone rsp,15
CASE_AF_alone rbp,1
CASE_AF_alone rbp,3
CASE_AF_alone rbp,5
CASE_AF_alone rbp,7
CASE_AF_alone rbp,11
CASE_AF_alone rbp,15

c_AF_holes proto vectorcall :AF,:real4,:qword,:real8,:qword,:real4
CASE_AF_holes macro base,mode
option stackbase:base
option win64:mode
a_AF_holes_&base&_&mode proc vectorcall frame a:AF,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_AF_holes_&base&_&mode endp
call_AF_holes_&base&_&mode proc frame
invoke c_AF_holes,data_AF,11.0,12,13.0,14,15.0
ret
call_AF_holes_&base&_&mode endp
forward_AF_holes_&base&_&mode proc vectorcall frame a:AF,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_AF_holes,a,b,c1,d,e,f
ret
forward_AF_holes_&base&_&mode endp
endm
CASE_AF_holes rsp,1
CASE_AF_holes rsp,3
CASE_AF_holes rsp,5
CASE_AF_holes rsp,7
CASE_AF_holes rsp,11
CASE_AF_holes rsp,15
CASE_AF_holes rbp,1
CASE_AF_holes rbp,3
CASE_AF_holes rbp,5
CASE_AF_holes rbp,7
CASE_AF_holes rbp,11
CASE_AF_holes rbp,15

c_AF_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:AF
CASE_AF_fallback macro base,mode
option stackbase:base
option win64:mode
a_AF_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:AF
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_AF_fallback_&base&_&mode endp
call_AF_fallback_&base&_&mode proc frame
invoke c_AF_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_AF
ret
call_AF_fallback_&base&_&mode endp
forward_AF_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:AF
invoke c_AF_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_AF_fallback_&base&_&mode endp
endm
CASE_AF_fallback rsp,1
CASE_AF_fallback rsp,3
CASE_AF_fallback rsp,5
CASE_AF_fallback rsp,7
CASE_AF_fallback rsp,11
CASE_AF_fallback rsp,15
CASE_AF_fallback rbp,1
CASE_AF_fallback rbp,3
CASE_AF_fallback rbp,5
CASE_AF_fallback rbp,7
CASE_AF_fallback rbp,11
CASE_AF_fallback rbp,15

c_AF_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:AF
CASE_AF_seventh macro base,mode
option stackbase:base
option win64:mode
a_AF_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:AF
pxor xmm5,xmm5
mov rax,a
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_AF_seventh_&base&_&mode endp
call_AF_seventh_&base&_&mode proc frame
invoke c_AF_seventh,1,2,3,4,5,6,data_AF
ret
call_AF_seventh_&base&_&mode endp
forward_AF_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:AF
invoke c_AF_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_AF_seventh_&base&_&mode endp
endm
CASE_AF_seventh rsp,1
CASE_AF_seventh rsp,3
CASE_AF_seventh rsp,5
CASE_AF_seventh rsp,7
CASE_AF_seventh rsp,11
CASE_AF_seventh rsp,15
CASE_AF_seventh rbp,1
CASE_AF_seventh rbp,3
CASE_AF_seventh rbp,5
CASE_AF_seventh rbp,7
CASE_AF_seventh rbp,11
CASE_AF_seventh rbp,15

c_Mixed_alone proto vectorcall :Mixed
CASE_Mixed_alone macro base,mode
option stackbase:base
option win64:mode
a_Mixed_alone_&base&_&mode proc vectorcall frame a:Mixed
pxor xmm5,xmm5
cvtss2sd xmm4,dword ptr a
addsd xmm5,xmm4
cvtsi2sd xmm4,dword ptr a+4
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Mixed_alone_&base&_&mode endp
call_Mixed_alone_&base&_&mode proc frame
invoke c_Mixed_alone,data_Mixed
ret
call_Mixed_alone_&base&_&mode endp
forward_Mixed_alone_&base&_&mode proc vectorcall frame a:Mixed
invoke c_Mixed_alone,a
ret
forward_Mixed_alone_&base&_&mode endp
endm
CASE_Mixed_alone rsp,1
CASE_Mixed_alone rsp,3
CASE_Mixed_alone rsp,5
CASE_Mixed_alone rsp,7
CASE_Mixed_alone rsp,11
CASE_Mixed_alone rsp,15
CASE_Mixed_alone rbp,1
CASE_Mixed_alone rbp,3
CASE_Mixed_alone rbp,5
CASE_Mixed_alone rbp,7
CASE_Mixed_alone rbp,11
CASE_Mixed_alone rbp,15

c_Mixed_holes proto vectorcall :Mixed,:real4,:qword,:real8,:qword,:real4
CASE_Mixed_holes macro base,mode
option stackbase:base
option win64:mode
a_Mixed_holes_&base&_&mode proc vectorcall frame a:Mixed,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
cvtss2sd xmm4,dword ptr a
addsd xmm5,xmm4
cvtsi2sd xmm4,dword ptr a+4
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Mixed_holes_&base&_&mode endp
call_Mixed_holes_&base&_&mode proc frame
invoke c_Mixed_holes,data_Mixed,11.0,12,13.0,14,15.0
ret
call_Mixed_holes_&base&_&mode endp
forward_Mixed_holes_&base&_&mode proc vectorcall frame a:Mixed,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_Mixed_holes,a,b,c1,d,e,f
ret
forward_Mixed_holes_&base&_&mode endp
endm
CASE_Mixed_holes rsp,1
CASE_Mixed_holes rsp,3
CASE_Mixed_holes rsp,5
CASE_Mixed_holes rsp,7
CASE_Mixed_holes rsp,11
CASE_Mixed_holes rsp,15
CASE_Mixed_holes rbp,1
CASE_Mixed_holes rbp,3
CASE_Mixed_holes rbp,5
CASE_Mixed_holes rbp,7
CASE_Mixed_holes rbp,11
CASE_Mixed_holes rbp,15

c_Mixed_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:Mixed
CASE_Mixed_fallback macro base,mode
option stackbase:base
option win64:mode
a_Mixed_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:Mixed
pxor xmm5,xmm5
cvtss2sd xmm4,dword ptr a
addsd xmm5,xmm4
cvtsi2sd xmm4,dword ptr a+4
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Mixed_fallback_&base&_&mode endp
call_Mixed_fallback_&base&_&mode proc frame
invoke c_Mixed_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_Mixed
ret
call_Mixed_fallback_&base&_&mode endp
forward_Mixed_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:Mixed
invoke c_Mixed_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_Mixed_fallback_&base&_&mode endp
endm
CASE_Mixed_fallback rsp,1
CASE_Mixed_fallback rsp,3
CASE_Mixed_fallback rsp,5
CASE_Mixed_fallback rsp,7
CASE_Mixed_fallback rsp,11
CASE_Mixed_fallback rsp,15
CASE_Mixed_fallback rbp,1
CASE_Mixed_fallback rbp,3
CASE_Mixed_fallback rbp,5
CASE_Mixed_fallback rbp,7
CASE_Mixed_fallback rbp,11
CASE_Mixed_fallback rbp,15

c_Mixed_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:Mixed
CASE_Mixed_seventh macro base,mode
option stackbase:base
option win64:mode
a_Mixed_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:Mixed
pxor xmm5,xmm5
cvtss2sd xmm4,dword ptr a
addsd xmm5,xmm4
cvtsi2sd xmm4,dword ptr a+4
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Mixed_seventh_&base&_&mode endp
call_Mixed_seventh_&base&_&mode proc frame
invoke c_Mixed_seventh,1,2,3,4,5,6,data_Mixed
ret
call_Mixed_seventh_&base&_&mode endp
forward_Mixed_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:Mixed
invoke c_Mixed_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_Mixed_seventh_&base&_&mode endp
endm
CASE_Mixed_seventh rsp,1
CASE_Mixed_seventh rsp,3
CASE_Mixed_seventh rsp,5
CASE_Mixed_seventh rsp,7
CASE_Mixed_seventh rsp,11
CASE_Mixed_seventh rsp,15
CASE_Mixed_seventh rbp,1
CASE_Mixed_seventh rbp,3
CASE_Mixed_seventh rbp,5
CASE_Mixed_seventh rbp,7
CASE_Mixed_seventh rbp,11
CASE_Mixed_seventh rbp,15

c_Ints_alone proto vectorcall :Ints
CASE_Ints_alone macro base,mode
option stackbase:base
option win64:mode
a_Ints_alone_&base&_&mode proc vectorcall frame a:Ints
pxor xmm5,xmm5
mov rax,a
cvtsi2sd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
cvtsi2sd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Ints_alone_&base&_&mode endp
call_Ints_alone_&base&_&mode proc frame
invoke c_Ints_alone,data_Ints
ret
call_Ints_alone_&base&_&mode endp
forward_Ints_alone_&base&_&mode proc vectorcall frame a:Ints
invoke c_Ints_alone,a
ret
forward_Ints_alone_&base&_&mode endp
endm
CASE_Ints_alone rsp,1
CASE_Ints_alone rsp,3
CASE_Ints_alone rsp,5
CASE_Ints_alone rsp,7
CASE_Ints_alone rsp,11
CASE_Ints_alone rsp,15
CASE_Ints_alone rbp,1
CASE_Ints_alone rbp,3
CASE_Ints_alone rbp,5
CASE_Ints_alone rbp,7
CASE_Ints_alone rbp,11
CASE_Ints_alone rbp,15

c_Ints_holes proto vectorcall :Ints,:real4,:qword,:real8,:qword,:real4
CASE_Ints_holes macro base,mode
option stackbase:base
option win64:mode
a_Ints_holes_&base&_&mode proc vectorcall frame a:Ints,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
cvtsi2sd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
cvtsi2sd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Ints_holes_&base&_&mode endp
call_Ints_holes_&base&_&mode proc frame
invoke c_Ints_holes,data_Ints,11.0,12,13.0,14,15.0
ret
call_Ints_holes_&base&_&mode endp
forward_Ints_holes_&base&_&mode proc vectorcall frame a:Ints,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c_Ints_holes,a,b,c1,d,e,f
ret
forward_Ints_holes_&base&_&mode endp
endm
CASE_Ints_holes rsp,1
CASE_Ints_holes rsp,3
CASE_Ints_holes rsp,5
CASE_Ints_holes rsp,7
CASE_Ints_holes rsp,11
CASE_Ints_holes rsp,15
CASE_Ints_holes rbp,1
CASE_Ints_holes rbp,3
CASE_Ints_holes rbp,5
CASE_Ints_holes rbp,7
CASE_Ints_holes rbp,11
CASE_Ints_holes rbp,15

c_Ints_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:Ints
CASE_Ints_fallback macro base,mode
option stackbase:base
option win64:mode
a_Ints_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:Ints
pxor xmm5,xmm5
mov rax,a
cvtsi2sd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
cvtsi2sd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Ints_fallback_&base&_&mode endp
call_Ints_fallback_&base&_&mode proc frame
invoke c_Ints_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data_Ints
ret
call_Ints_fallback_&base&_&mode endp
forward_Ints_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:Ints
invoke c_Ints_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward_Ints_fallback_&base&_&mode endp
endm
CASE_Ints_fallback rsp,1
CASE_Ints_fallback rsp,3
CASE_Ints_fallback rsp,5
CASE_Ints_fallback rsp,7
CASE_Ints_fallback rsp,11
CASE_Ints_fallback rsp,15
CASE_Ints_fallback rbp,1
CASE_Ints_fallback rbp,3
CASE_Ints_fallback rbp,5
CASE_Ints_fallback rbp,7
CASE_Ints_fallback rbp,11
CASE_Ints_fallback rbp,15

c_Ints_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:Ints
CASE_Ints_seventh macro base,mode
option stackbase:base
option win64:mode
a_Ints_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:Ints
pxor xmm5,xmm5
mov rax,a
cvtsi2sd xmm4,qword ptr [rax+0]
addsd xmm5,xmm4
cvtsi2sd xmm4,qword ptr [rax+8]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a_Ints_seventh_&base&_&mode endp
call_Ints_seventh_&base&_&mode proc frame
invoke c_Ints_seventh,1,2,3,4,5,6,data_Ints
ret
call_Ints_seventh_&base&_&mode endp
forward_Ints_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:Ints
invoke c_Ints_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward_Ints_seventh_&base&_&mode endp
endm
CASE_Ints_seventh rsp,1
CASE_Ints_seventh rsp,3
CASE_Ints_seventh rsp,5
CASE_Ints_seventh rsp,7
CASE_Ints_seventh rsp,11
CASE_Ints_seventh rsp,15
CASE_Ints_seventh rbp,1
CASE_Ints_seventh rbp,3
CASE_Ints_seventh rbp,5
CASE_Ints_seventh rbp,7
CASE_Ints_seventh rbp,11
CASE_Ints_seventh rbp,15

c___m128f_alone proto vectorcall :__m128f
CASE___m128f_alone macro base,mode
option stackbase:base
option win64:mode
a___m128f_alone_&base&_&mode proc vectorcall frame a:__m128f
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a___m128f_alone_&base&_&mode endp
call___m128f_alone_&base&_&mode proc frame
invoke c___m128f_alone,data___m128f
ret
call___m128f_alone_&base&_&mode endp
forward___m128f_alone_&base&_&mode proc vectorcall frame a:__m128f
invoke c___m128f_alone,a
ret
forward___m128f_alone_&base&_&mode endp
endm
CASE___m128f_alone rsp,1
CASE___m128f_alone rsp,3
CASE___m128f_alone rsp,5
CASE___m128f_alone rsp,7
CASE___m128f_alone rsp,11
CASE___m128f_alone rsp,15
CASE___m128f_alone rbp,1
CASE___m128f_alone rbp,3
CASE___m128f_alone rbp,5
CASE___m128f_alone rbp,7
CASE___m128f_alone rbp,11
CASE___m128f_alone rbp,15

c___m128f_holes proto vectorcall :__m128f,:real4,:qword,:real8,:qword,:real4
CASE___m128f_holes macro base,mode
option stackbase:base
option win64:mode
a___m128f_holes_&base&_&mode proc vectorcall frame a:__m128f,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a___m128f_holes_&base&_&mode endp
call___m128f_holes_&base&_&mode proc frame
invoke c___m128f_holes,data___m128f,11.0,12,13.0,14,15.0
ret
call___m128f_holes_&base&_&mode endp
forward___m128f_holes_&base&_&mode proc vectorcall frame a:__m128f,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c___m128f_holes,a,b,c1,d,e,f
ret
forward___m128f_holes_&base&_&mode endp
endm
CASE___m128f_holes rsp,1
CASE___m128f_holes rsp,3
CASE___m128f_holes rsp,5
CASE___m128f_holes rsp,7
CASE___m128f_holes rsp,11
CASE___m128f_holes rsp,15
CASE___m128f_holes rbp,1
CASE___m128f_holes rbp,3
CASE___m128f_holes rbp,5
CASE___m128f_holes rbp,7
CASE___m128f_holes rbp,11
CASE___m128f_holes rbp,15

c___m128f_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:__m128f
CASE___m128f_fallback macro base,mode
option stackbase:base
option win64:mode
a___m128f_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:__m128f
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a___m128f_fallback_&base&_&mode endp
call___m128f_fallback_&base&_&mode proc frame
invoke c___m128f_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data___m128f
ret
call___m128f_fallback_&base&_&mode endp
forward___m128f_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:__m128f
invoke c___m128f_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward___m128f_fallback_&base&_&mode endp
endm
CASE___m128f_fallback rsp,1
CASE___m128f_fallback rsp,3
CASE___m128f_fallback rsp,5
CASE___m128f_fallback rsp,7
CASE___m128f_fallback rsp,11
CASE___m128f_fallback rsp,15
CASE___m128f_fallback rbp,1
CASE___m128f_fallback rbp,3
CASE___m128f_fallback rbp,5
CASE___m128f_fallback rbp,7
CASE___m128f_fallback rbp,11
CASE___m128f_fallback rbp,15

c___m128f_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:__m128f
CASE___m128f_seventh macro base,mode
option stackbase:base
option win64:mode
a___m128f_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:__m128f
pxor xmm5,xmm5
mov rax,a
movaps xmm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a___m128f_seventh_&base&_&mode endp
call___m128f_seventh_&base&_&mode proc frame
invoke c___m128f_seventh,1,2,3,4,5,6,data___m128f
ret
call___m128f_seventh_&base&_&mode endp
forward___m128f_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:__m128f
invoke c___m128f_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward___m128f_seventh_&base&_&mode endp
endm
CASE___m128f_seventh rsp,1
CASE___m128f_seventh rsp,3
CASE___m128f_seventh rsp,5
CASE___m128f_seventh rsp,7
CASE___m128f_seventh rsp,11
CASE___m128f_seventh rsp,15
CASE___m128f_seventh rbp,1
CASE___m128f_seventh rbp,3
CASE___m128f_seventh rbp,5
CASE___m128f_seventh rbp,7
CASE___m128f_seventh rbp,11
CASE___m128f_seventh rbp,15

c___m256f_alone proto vectorcall :__m256f
CASE___m256f_alone macro base,mode
option stackbase:base
option win64:mode
a___m256f_alone_&base&_&mode proc vectorcall frame a:__m256f
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a___m256f_alone_&base&_&mode endp
call___m256f_alone_&base&_&mode proc frame
invoke c___m256f_alone,data___m256f
ret
call___m256f_alone_&base&_&mode endp
forward___m256f_alone_&base&_&mode proc vectorcall frame a:__m256f
invoke c___m256f_alone,a
ret
forward___m256f_alone_&base&_&mode endp
endm
CASE___m256f_alone rsp,1
CASE___m256f_alone rsp,3
CASE___m256f_alone rsp,5
CASE___m256f_alone rsp,7
CASE___m256f_alone rsp,11
CASE___m256f_alone rsp,15
CASE___m256f_alone rbp,1
CASE___m256f_alone rbp,3
CASE___m256f_alone rbp,5
CASE___m256f_alone rbp,7
CASE___m256f_alone rbp,11
CASE___m256f_alone rbp,15

c___m256f_holes proto vectorcall :__m256f,:real4,:qword,:real8,:qword,:real4
CASE___m256f_holes macro base,mode
option stackbase:base
option win64:mode
a___m256f_holes_&base&_&mode proc vectorcall frame a:__m256f,b:real4,c1:qword,d:real8,e:qword,f:real4
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtss2sd xmm4,b
addsd xmm5,xmm4
cvtsi2sd xmm4,c1
addsd xmm5,xmm4
movsd xmm4,d
addsd xmm5,xmm4
cvtsi2sd xmm4,e
addsd xmm5,xmm4
cvtss2sd xmm4,f
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a___m256f_holes_&base&_&mode endp
call___m256f_holes_&base&_&mode proc frame
invoke c___m256f_holes,data___m256f,11.0,12,13.0,14,15.0
ret
call___m256f_holes_&base&_&mode endp
forward___m256f_holes_&base&_&mode proc vectorcall frame a:__m256f,b:real4,c1:qword,d:real8,e:qword,f:real4
invoke c___m256f_holes,a,b,c1,d,e,f
ret
forward___m256f_holes_&base&_&mode endp
endm
CASE___m256f_holes rsp,1
CASE___m256f_holes rsp,3
CASE___m256f_holes rsp,5
CASE___m256f_holes rsp,7
CASE___m256f_holes rsp,11
CASE___m256f_holes rsp,15
CASE___m256f_holes rbp,1
CASE___m256f_holes rbp,3
CASE___m256f_holes rbp,5
CASE___m256f_holes rbp,7
CASE___m256f_holes rbp,11
CASE___m256f_holes rbp,15

c___m256f_fallback proto vectorcall :real8,:real8,:real8,:real8,:real8,:real8,:__m256f
CASE___m256f_fallback macro base,mode
option stackbase:base
option win64:mode
a___m256f_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:__m256f
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
movsd xmm4,p0
addsd xmm5,xmm4
movsd xmm4,p1
addsd xmm5,xmm4
movsd xmm4,p2
addsd xmm5,xmm4
movsd xmm4,p3
addsd xmm5,xmm4
movsd xmm4,p4
addsd xmm5,xmm4
movsd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a___m256f_fallback_&base&_&mode endp
call___m256f_fallback_&base&_&mode proc frame
invoke c___m256f_fallback,1.0,2.0,3.0,4.0,5.0,6.0,data___m256f
ret
call___m256f_fallback_&base&_&mode endp
forward___m256f_fallback_&base&_&mode proc vectorcall frame p0:real8,p1:real8,p2:real8,p3:real8,p4:real8,p5:real8,a:__m256f
invoke c___m256f_fallback,p0,p1,p2,p3,p4,p5,a
ret
forward___m256f_fallback_&base&_&mode endp
endm
CASE___m256f_fallback rsp,1
CASE___m256f_fallback rsp,3
CASE___m256f_fallback rsp,5
CASE___m256f_fallback rsp,7
CASE___m256f_fallback rsp,11
CASE___m256f_fallback rsp,15
CASE___m256f_fallback rbp,1
CASE___m256f_fallback rbp,3
CASE___m256f_fallback rbp,5
CASE___m256f_fallback rbp,7
CASE___m256f_fallback rbp,11
CASE___m256f_fallback rbp,15

c___m256f_seventh proto vectorcall :qword,:qword,:qword,:qword,:qword,:qword,:__m256f
CASE___m256f_seventh macro base,mode
option stackbase:base
option win64:mode
a___m256f_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:__m256f
pxor xmm5,xmm5
mov rax,a
vmovaps ymm4,[rax]
cvtss2sd xmm4,dword ptr [rax+0]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+4]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+8]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+12]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+16]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+20]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+24]
addsd xmm5,xmm4
cvtss2sd xmm4,dword ptr [rax+28]
addsd xmm5,xmm4
cvtsi2sd xmm4,p0
addsd xmm5,xmm4
cvtsi2sd xmm4,p1
addsd xmm5,xmm4
cvtsi2sd xmm4,p2
addsd xmm5,xmm4
cvtsi2sd xmm4,p3
addsd xmm5,xmm4
cvtsi2sd xmm4,p4
addsd xmm5,xmm4
cvtsi2sd xmm4,p5
addsd xmm5,xmm4
movapd xmm0,xmm5
ret
a___m256f_seventh_&base&_&mode endp
call___m256f_seventh_&base&_&mode proc frame
invoke c___m256f_seventh,1,2,3,4,5,6,data___m256f
ret
call___m256f_seventh_&base&_&mode endp
forward___m256f_seventh_&base&_&mode proc vectorcall frame p0:qword,p1:qword,p2:qword,p3:qword,p4:qword,p5:qword,a:__m256f
invoke c___m256f_seventh,p0,p1,p2,p3,p4,p5,a
ret
forward___m256f_seventh_&base&_&mode endp
endm
CASE___m256f_seventh rsp,1
CASE___m256f_seventh rsp,3
CASE___m256f_seventh rsp,5
CASE___m256f_seventh rsp,7
CASE___m256f_seventh rsp,11
CASE___m256f_seventh rsp,15
CASE___m256f_seventh rbp,1
CASE___m256f_seventh rbp,3
CASE___m256f_seventh rbp,5
CASE___m256f_seventh rbp,7
CASE___m256f_seventh rbp,11
CASE___m256f_seventh rbp,15

end
