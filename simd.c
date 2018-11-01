
/* 
Create the predefined SIMD data types 
__m128
__m256
__m512
and their sub-types
*/

#include "simd.h"
#include "globals.h"
#include "symbols.h"

extern void     AddLineQueue(const char *line);
extern void     AddLineQueueX(const char *fmt, ...);

void AddSimdTypes()
{
	struct asym* sym = 0;

	AddLineQueue("__m128b struct");
	AddLineQueue("b0 BYTE ?");
	AddLineQueue("b1 BYTE ?");
	AddLineQueue("b2 BYTE ?");
	AddLineQueue("b3 BYTE ?");
	AddLineQueue("b4 BYTE ?");
	AddLineQueue("b5 BYTE ?");
	AddLineQueue("b6 BYTE ?");
	AddLineQueue("b7 BYTE ?");
	AddLineQueue("b8 BYTE ?");
	AddLineQueue("b9 BYTE ?");
	AddLineQueue("b10 BYTE ?");
	AddLineQueue("b11 BYTE ?");
	AddLineQueue("b12 BYTE ?");
	AddLineQueue("b13 BYTE ?");
	AddLineQueue("b14 BYTE ?");
	AddLineQueue("b15 BYTE ?");
	AddLineQueue("__m128b ends");

	AddLineQueue("__m128w struct");
	AddLineQueue("w0 WORD ?");
	AddLineQueue("w1 WORD ?");
	AddLineQueue("w2 WORD ?");
	AddLineQueue("w3 WORD ?");
	AddLineQueue("w4 WORD ?");
	AddLineQueue("w5 WORD ?");
	AddLineQueue("w6 WORD ?");
	AddLineQueue("w7 WORD ?");
	AddLineQueue("__m128w ends");

	AddLineQueue("__m128i struct");
	AddLineQueue("i0 DWORD ?");
	AddLineQueue("i1 DWORD ?");
	AddLineQueue("i2 DWORD ?");
	AddLineQueue("i3 DWORD ?");
	AddLineQueue("__m128i ends");

	AddLineQueue("__m128f struct");
	AddLineQueue("f0 real4 ?");
	AddLineQueue("f1 real4 ?");
	AddLineQueue("f2 real4 ?");
	AddLineQueue("f3 real4 ?");
	AddLineQueue("__m128f ends");

	AddLineQueue("__m128d struct");
	AddLineQueue("d0 real8 ?");
	AddLineQueue("d1 real8 ?");
	AddLineQueue("__m128d ends");

	AddLineQueue("__m128q struct");
	AddLineQueue("q0 QWORD ?");
	AddLineQueue("q1 QWORD ?");
	AddLineQueue("__m128q ends");

	AddLineQueue("__m128 union");
	AddLineQueue("f32 __m128f <>");
	AddLineQueue("i8  __m128b <>");
	AddLineQueue("i16 __m128w <>");
	AddLineQueue("i32 __m128i <>");
	AddLineQueue("d64 __m128d <>");
	AddLineQueue("q64 __m128q <>");
	AddLineQueue("__m128 ends");

	AddLineQueue("__m256b struct");
	AddLineQueue("b0 BYTE ?");
	AddLineQueue("b1 BYTE ?");
	AddLineQueue("b2 BYTE ?");
	AddLineQueue("b3 BYTE ?");
	AddLineQueue("b4 BYTE ?");
	AddLineQueue("b5 BYTE ?");
	AddLineQueue("b6 BYTE ?");
	AddLineQueue("b7 BYTE ?");
	AddLineQueue("b8 BYTE ?");
	AddLineQueue("b9 BYTE ?");
	AddLineQueue("b10 BYTE ?");
	AddLineQueue("b11 BYTE ?");
	AddLineQueue("b12 BYTE ?");
	AddLineQueue("b13 BYTE ?");
	AddLineQueue("b14 BYTE ?");
	AddLineQueue("b15 BYTE ?");
	AddLineQueue("b16 BYTE ?");
	AddLineQueue("b17 BYTE ?");
	AddLineQueue("b18 BYTE ?");
	AddLineQueue("b19 BYTE ?");
	AddLineQueue("b20 BYTE ?");
	AddLineQueue("b21 BYTE ?");
	AddLineQueue("b22 BYTE ?");
	AddLineQueue("b23 BYTE ?");
	AddLineQueue("b24 BYTE ?");
	AddLineQueue("b25 BYTE ?");
	AddLineQueue("b26 BYTE ?");
	AddLineQueue("b27 BYTE ?");
	AddLineQueue("b28 BYTE ?");
	AddLineQueue("b29 BYTE ?");
	AddLineQueue("b30 BYTE ?");
	AddLineQueue("b31 BYTE ?");
	AddLineQueue("__m256b ends");
	
	AddLineQueue("__m256w struct");
	AddLineQueue("w0 WORD ?");
	AddLineQueue("w1 WORD ?");
	AddLineQueue("w2 WORD ?");
	AddLineQueue("w3 WORD ?");
	AddLineQueue("w4 WORD ?");
	AddLineQueue("w5 WORD ?");
	AddLineQueue("w6 WORD ?");
	AddLineQueue("w7 WORD ?");
	AddLineQueue("w8 WORD ?");
	AddLineQueue("w9 WORD ?");
	AddLineQueue("w10 WORD ?");
	AddLineQueue("w11 WORD ?");
	AddLineQueue("w12 WORD ?");
	AddLineQueue("w13 WORD ?");
	AddLineQueue("w14 WORD ?");
	AddLineQueue("w15 WORD ?");
	AddLineQueue("__m256w ends");

	AddLineQueue("__m256i struct");
	AddLineQueue("i0 DWORD ?");
	AddLineQueue("i1 DWORD ?");
	AddLineQueue("i2 DWORD ?");
	AddLineQueue("i3 DWORD ?");
	AddLineQueue("i4 DWORD ?");
	AddLineQueue("i5 DWORD ?");
	AddLineQueue("i6 DWORD ?");
	AddLineQueue("i7 DWORD ?");
	AddLineQueue("__m256i ends");

	AddLineQueue("__m256f struct");
	AddLineQueue("f0 real4 ?");
	AddLineQueue("f1 real4 ?");
	AddLineQueue("f2 real4 ?");
	AddLineQueue("f3 real4 ?");
	AddLineQueue("f4 real4 ?");
	AddLineQueue("f5 real4 ?");
	AddLineQueue("f6 real4 ?");
	AddLineQueue("f7 real4 ?");
	AddLineQueue("__m256f ends");

	AddLineQueue("__m256d struct");
	AddLineQueue("d0 real8 ?");
	AddLineQueue("d1 real8 ?");
	AddLineQueue("d2 real8 ?");
	AddLineQueue("d3 real8 ?");
	AddLineQueue("__m256d ends");

	AddLineQueue("__m256q struct");
	AddLineQueue("q0 QWORD ?");
	AddLineQueue("q1 QWORD ?");
	AddLineQueue("q2 QWORD ?");
	AddLineQueue("q3 QWORD ?");
	AddLineQueue("__m256q ends");

	AddLineQueue("__m256 union");
	AddLineQueue("f32 __m256f <>");
	AddLineQueue("i8  __m256b <>");
	AddLineQueue("i16 __m256w <>");
	AddLineQueue("i32 __m256i <>");
	AddLineQueue("d64 __m256d <>");
	AddLineQueue("q64 __m256q <>");
	AddLineQueue("__m256 ends");
	
	AddLineQueue("__m512b struct");
	AddLineQueue("b0 BYTE ?");
	AddLineQueue("b1 BYTE ?");
	AddLineQueue("b2 BYTE ?");
	AddLineQueue("b3 BYTE ?");
	AddLineQueue("b4 BYTE ?");
	AddLineQueue("b5 BYTE ?");
	AddLineQueue("b6 BYTE ?");
	AddLineQueue("b7 BYTE ?");
	AddLineQueue("b8 BYTE ?");
	AddLineQueue("b9 BYTE ?");
	AddLineQueue("b10 BYTE ?");
	AddLineQueue("b11 BYTE ?");
	AddLineQueue("b12 BYTE ?");
	AddLineQueue("b13 BYTE ?");
	AddLineQueue("b14 BYTE ?");
	AddLineQueue("b15 BYTE ?");
	AddLineQueue("b16 BYTE ?");
	AddLineQueue("b17 BYTE ?");
	AddLineQueue("b18 BYTE ?");
	AddLineQueue("b19 BYTE ?");
	AddLineQueue("b20 BYTE ?");
	AddLineQueue("b21 BYTE ?");
	AddLineQueue("b22 BYTE ?");
	AddLineQueue("b23 BYTE ?");
	AddLineQueue("b24 BYTE ?");
	AddLineQueue("b25 BYTE ?");
	AddLineQueue("b26 BYTE ?");
	AddLineQueue("b27 BYTE ?");
	AddLineQueue("b28 BYTE ?");
	AddLineQueue("b29 BYTE ?");
	AddLineQueue("b30 BYTE ?");
	AddLineQueue("b31 BYTE ?");
	AddLineQueue("b32 BYTE ?");
	AddLineQueue("b33 BYTE ?");
	AddLineQueue("b34 BYTE ?");
	AddLineQueue("b35 BYTE ?");
	AddLineQueue("b36 BYTE ?");
	AddLineQueue("b37 BYTE ?");
	AddLineQueue("b38 BYTE ?");
	AddLineQueue("b39 BYTE ?");
	AddLineQueue("b40 BYTE ?");
	AddLineQueue("b41 BYTE ?");
	AddLineQueue("b42 BYTE ?");
	AddLineQueue("b43 BYTE ?");
	AddLineQueue("b44 BYTE ?");
	AddLineQueue("b45 BYTE ?");
	AddLineQueue("b46 BYTE ?");
	AddLineQueue("b47 BYTE ?");
	AddLineQueue("b48 BYTE ?");
	AddLineQueue("b49 BYTE ?");
	AddLineQueue("b50 BYTE ?");
	AddLineQueue("b51 BYTE ?");
	AddLineQueue("b52 BYTE ?");
	AddLineQueue("b53 BYTE ?");
	AddLineQueue("b54 BYTE ?");
	AddLineQueue("b55 BYTE ?");
	AddLineQueue("b56 BYTE ?");
	AddLineQueue("b57 BYTE ?");
	AddLineQueue("b58 BYTE ?");
	AddLineQueue("b59 BYTE ?");
	AddLineQueue("b60 BYTE ?");
	AddLineQueue("b61 BYTE ?");
	AddLineQueue("b62 BYTE ?");
	AddLineQueue("b63 BYTE ?");
	AddLineQueue("__m512b ends");

	AddLineQueue("__m512w struct");
	AddLineQueue("w0 WORD ?");
	AddLineQueue("w1 WORD ?");
	AddLineQueue("w2 WORD ?");
	AddLineQueue("w3 WORD ?");
	AddLineQueue("w4 WORD ?");
	AddLineQueue("w5 WORD ?");
	AddLineQueue("w6 WORD ?");
	AddLineQueue("w7 WORD ?");
	AddLineQueue("w8 WORD ?");
	AddLineQueue("w9 WORD ?");
	AddLineQueue("w10 WORD ?");
	AddLineQueue("w11 WORD ?");
	AddLineQueue("w12 WORD ?");
	AddLineQueue("w13 WORD ?");
	AddLineQueue("w14 WORD ?");
	AddLineQueue("w15 WORD ?");
	AddLineQueue("w16 WORD ?");
	AddLineQueue("w17 WORD ?");
	AddLineQueue("w18 WORD ?");
	AddLineQueue("w19 WORD ?");
	AddLineQueue("w20 WORD ?");
	AddLineQueue("w21 WORD ?");
	AddLineQueue("w22 WORD ?");
	AddLineQueue("w23 WORD ?");
	AddLineQueue("w24 WORD ?");
	AddLineQueue("w25 WORD ?");
	AddLineQueue("w26 WORD ?");
	AddLineQueue("w27 WORD ?");
	AddLineQueue("w28 WORD ?");
	AddLineQueue("w29 WORD ?");
	AddLineQueue("w30 WORD ?");
	AddLineQueue("w31 WORD ?");
	AddLineQueue("__m512w ends");

	AddLineQueue("__m512i struct");
	AddLineQueue("i0 DWORD ?");
	AddLineQueue("i1 DWORD ?");
	AddLineQueue("i2 DWORD ?");
	AddLineQueue("i3 DWORD ?");
	AddLineQueue("i4 DWORD ?");
	AddLineQueue("i5 DWORD ?");
	AddLineQueue("i6 DWORD ?");
	AddLineQueue("i7 DWORD ?");
	AddLineQueue("i8 DWORD ?");
	AddLineQueue("i9 DWORD ?");
	AddLineQueue("i10 DWORD ?");
	AddLineQueue("i11 DWORD ?");
	AddLineQueue("i12 DWORD ?");
	AddLineQueue("i13 DWORD ?");
	AddLineQueue("i14 DWORD ?");
	AddLineQueue("i15 DWORD ?");
	AddLineQueue("__m512i ends");

	AddLineQueue("__m512f struct");
	AddLineQueue("f0 real4 ?");
	AddLineQueue("f1 real4 ?");
	AddLineQueue("f2 real4 ?");
	AddLineQueue("f3 real4 ?");
	AddLineQueue("f4 real4 ?");
	AddLineQueue("f5 real4 ?");
	AddLineQueue("f6 real4 ?");
	AddLineQueue("f7 real4 ?");
	AddLineQueue("f8 real4 ?");
	AddLineQueue("f9 real4 ?");
	AddLineQueue("f10 real4 ?");
	AddLineQueue("f11 real4 ?");
	AddLineQueue("f12 real4 ?");
	AddLineQueue("f13 real4 ?");
	AddLineQueue("f14 real4 ?");
	AddLineQueue("f15 real4 ?");
	AddLineQueue("__m512f ends");

	AddLineQueue("__m512d struct");
	AddLineQueue("d0 real8 ?");
	AddLineQueue("d1 real8 ?");
	AddLineQueue("d2 real8 ?");
	AddLineQueue("d3 real8 ?");
	AddLineQueue("d4 real8 ?");
	AddLineQueue("d5 real8 ?");
	AddLineQueue("d6 real8 ?");
	AddLineQueue("d7 real8 ?");
	AddLineQueue("__m512d ends");

	AddLineQueue("__m512q struct");
	AddLineQueue("q0 QWORD ?");
	AddLineQueue("q1 QWORD ?");
	AddLineQueue("q2 QWORD ?");
	AddLineQueue("q3 QWORD ?");
	AddLineQueue("q4 QWORD ?");
	AddLineQueue("q5 QWORD ?");
	AddLineQueue("q6 QWORD ?");
	AddLineQueue("q7 QWORD ?");
	AddLineQueue("__m512q ends");

	AddLineQueue("__m512 union");
	AddLineQueue("f32 __m512f <>");
	AddLineQueue("i8  __m512b <>");
	AddLineQueue("i16 __m512w <>");
	AddLineQueue("i32 __m512i <>");
	AddLineQueue("d64 __m512d <>");
	AddLineQueue("q64 __m512q <>");
	AddLineQueue("__m512 ends");
	
	RunLineQueue();

}