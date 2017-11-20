; MM128 = yes
; HFA   = no
; HVA   = no
__m128b struct
	b0 BYTE ?
	b1 BYTE ?
	b2 BYTE ?
	b3 BYTE ?
	b4 BYTE ?
	b5 BYTE ?
	b6 BYTE ?
	b7 BYTE ?
	b8 BYTE ?
	b9 BYTE ?
	b10 BYTE ?
	b11 BYTE ?
	b12 BYTE ?
	b13 BYTE ?
	b14 BYTE ?
	b15 BYTE ?	
__m128b ends

; MM128 = yes
; HFA   = no
; HVA   = no
__m128w struct
	w0 WORD ?
	w1 WORD ?
	w2 WORD ?
	w3 WORD ?
	w4 WORD ?
	w5 WORD ?
	w6 WORD ?
	w7 WORD ?	
__m128w ends

; MM128 = yes
; HFA   = no
; HVA   = no
__m128i struct
	i0 DWORD ?
	i1 DWORD ?
	i2 DWORD ?
	i3 DWORD ?	
__m128i ends

; MM128 = yes
; HFA   = no
; HVA   = no
__m128f struct
	f0 real4 ?
	f1 real4 ?
	f2 real4 ?
	f3 real4 ?
__m128f ends

; MM128 = yes
; HFA   = no
; HVA   = no
__m128d struct
	d0 real8 ?
	d1 real8 ?	
__m128d ends

; MM128 = yes
; HFA   = no
; HVA   = no
__m128q struct
	q0 QWORD ?
	q1 QWORD ?
__m128q ends

; MM128 = yes
; HFA   = no
; HVA   = no
__m128 union
	f32 __m128f <>
	i8  __m128b <>
	i16 __m128w <>	
	i32 __m128i <>
	d64 __m128d <>
	q64 __m128q <> 
__m128 ends

; MM256 = yes
; HFA   = no
; HVA   = no
__m256b struct
	b0 BYTE ?
	b1 BYTE ?
	b2 BYTE ?
	b3 BYTE ?
	b4 BYTE ?
	b5 BYTE ?
	b6 BYTE ?
	b7 BYTE ?
	b8 BYTE ?
	b9 BYTE ?
	b10 BYTE ?
	b11 BYTE ?
	b12 BYTE ?
	b13 BYTE ?
	b14 BYTE ?
	b15 BYTE ?	
	b16 BYTE ?
	b17 BYTE ?
	b18 BYTE ?
	b19 BYTE ?
	b20 BYTE ?
	b21 BYTE ?
	b22 BYTE ?
	b23 BYTE ?
	b24 BYTE ?
	b25 BYTE ?
	b26 BYTE ?
	b27 BYTE ?
	b28 BYTE ?
	b29 BYTE ?
	b30 BYTE ?
	b31 BYTE ?
__m256b ends

; MM256 = yes
; HFA   = no
; HVA   = no
__m256w struct
	w0 WORD ?
	w1 WORD ?
	w2 WORD ?
	w3 WORD ?
	w4 WORD ?
	w5 WORD ?
	w6 WORD ?
	w7 WORD ?	
	w8 WORD ?
	w9 WORD ?
	w10 WORD ?
	w11 WORD ?
	w12 WORD ?
	w13 WORD ?
	w14 WORD ?
	w15 WORD ?
__m256w ends

; MM256 = yes
; HFA   = no
; HVA   = no
__m256i struct
	i0 DWORD ?
	i1 DWORD ?
	i2 DWORD ?
	i3 DWORD ?
	i4 DWORD ?
	i5 DWORD ?
	i6 DWORD ?
	i7 DWORD ?
__m256i ends

; MM256 = yes
; HFA   = no
; HVA   = no
__m256f struct
	f0 real4 ?
	f1 real4 ?
	f2 real4 ?
	f3 real4 ?
	f4 real4 ?
	f5 real4 ?
	f6 real4 ?
	f7 real4 ?
__m256f ends

; MM256 = yes
; HFA   = no
; HVA   = no
__m256d struct
	d0 real8 ?
	d1 real8 ?
	d2 real8 ?
	d3 real8 ?	
__m256d ends

; MM256 = yes
; HFA   = no
; HVA   = no
__m256q struct
	q0 QWORD ?
	q1 QWORD ?
	q2 QWORD ?
	q3 QWORD ?
__m256q ends

; MM256 = yes
; HFA   = no
; HVA   = no
__m256 union
	f32 __m256f <>
	i8  __m256b <>
	i16 __m256w <>	
	i32 __m256i <>
	d64 __m256d <>
	q64 __m256q <> 
__m256 ends
