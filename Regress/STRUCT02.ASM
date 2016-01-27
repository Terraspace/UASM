
;--- struct alignment test

	.model small

s01 struct DWORD	;expected size: 6
v1	dw ?
v2	dw ?
v3	dw ?
s01 ends

s02 struct DWORD	;expected size: 8
v1	dd ?
v2	dw ?
s02 ends

s03 struct DWORD	;expected size: 8
v1	dw ?
v2	dd ?
s03 ends

s04 struct DWORD	;expected size: 12
v1	dw ?
v2	s03 <> ;starts at offset 4
s04 ends

s05 struct QWORD	;expected size: 12
v1	dw ?
v2	s03 <> ;starts at offset 4
s05 ends

s06 struct DWORD	;expected size: 12
v1	dq ?
v2	dw ?
s06 ends

s07 struct DWORD	;expected size: 16
v1	dw ?
v2	s06 <> ;starts at offset 4
s07 ends

s08 struct DWORD	;expected size: 8
v1	dw ?
v2	s01 <> ;starts at offset 2
s08 ends

;--- structs with embedded structs

s11 struct DWORD	;expected size: 4
v1	dw ?
struct
v2	dw ?
ends
s11 ends

;--- s12, s13, s14 make Masm crash (tested v6.15, v8, v9)

ifdef __JWASM__
s12 struct DWORD	;expected size: 8
v1	dw ?
struct    ;starts at offset 4
v2	dd ?
ends
s12 ends

s13 struct DWORD	;expected size: 12
v1	dw ?
struct    ;starts at offset 4
v2	dw ?
v3	dd ?
ends
s13 ends

s14 struct DWORD	;expected size: 12
v1	dw ?
struct es1 ;starts at offset 4
v2	db ?
v3	dd ?
ends
s14 ends

s21 struct DWORD	;expected size: 8
struct
v1	db ?
ends
struct
v2	dw ?
ends
struct
v3	dd ?
ends
s21 ends

;--- structs with embedded arrays 

s31 struct DWORD	;expected size: 10
v1	db 3 dup (?)
struct
v2	dw ? ;starts at offset 4
ends
struct   ;starts at offset 6
v3	db 3 dup (?)
ends
s31 ends

endif

;--- structs with embedded records

r1	RECORD rf1:1, rf2:3, rf3:2

s41 struct DWORD	;expected size: 2
v1	db ?
v2	r1 <>			;starts at offset 1
s41 ends

s42 struct DWORD	;expected size: 8
v1	db ?
v2	r1 <>			;starts at offset 1
v3	dd ?
s42 ends

@DefS macro sname, init
	db @CatStr(!",sname,!>!")
	sname <init>
	db '<'
	endm

	.data

	@DefS s01, <1,2,3>
	@DefS s02, <1,2>
	@DefS s03, <1,2>
	@DefS s04, <1,{2,3}>
	@DefS s05, <1,{2,3}>
	@DefS s06, <1,2>
	@DefS s07, <1,{2,3}>
	@DefS s08, <1,{2,3,4}>
	@DefS s11, <1,{2}>
ifdef __JWASM__
	@DefS s12, <1,{2}>
	@DefS s13, <1,{2,3}>
	@DefS s14, <1,{2,3}>
	@DefS s21, <<1>,<2>,<3>>
	@DefS s31, <<1,2,3>,<4>,<<5,6,7>>>
endif
	@DefS s41, <1,<1,2>>
	@DefS s42, <1,<1,2>,3>

	END
