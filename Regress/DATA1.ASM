
;--- test simple data initialization

	.386

_DATA16 segment word use16 public 'DATA'
v1	db 1,2,3
v2	dw 2,3,4
v3	dd 4,5,6
_DATA16 ends

_DATA32 segment dword use32 public 'DATA'

vb1		db 1
vb2		db "abc!def"
vb3		db 10t
vb4		db 1,2,3,4,"abc",3 dup (9),"abc"
vb5		db ?,1,?,2,"abc"
vb6		db LOW offset vb1, HIGH offset vb1
vb7		BYTE 1
vb8		SBYTE 2
vb9		SBYTE -20
vw1		dw 1
vw2		dw 1,3,3,4,5 dup (8),3 dup (4)
vw3		dw ds:12h		;this shouldn't create a fixup
;vw4	dw seg v1, seg vb1
vw5		dw LOWWORD(offset vb1), LOWWORD(offset vb2)
vw6		dw LOW(offset vb4) ;, HIGH(offset vb5)
vw7		WORD 5,6
vw8		SWORD -5,6
vd1		dd 10q
vd2		dd _DATA32:12h	;this should create a fixup
vd3		DWORD 1,1,1
vf1		df 6,7,8
;vf2	df var4, var5, var6
vf3		FWORD 0
vq1		dq 8,9,10
vq2		QWORD 8,9,10
vr41	REAL4 1.0
vr81	REAL8 2.0
vr101	REAL10 3.0
vt1		dt 1
vt2		dt 4.0
vo1		OWORD 1.23456

if 0;def __JWASM__
vq3		SQWORD 8,9,10       ;Masm v6.15 doesn't know SQWORD
vo2		OWORD 16,17,18,-1	;MASM rejects, needs FP initializer
endif

_DATA32 ends

	END
