// MSVC is the independent vectorcall ABI oracle. Compile with /arch:AVX.
#include <windows.h>
#include <stdio.h>
#include <immintrin.h>
typedef struct { float m0; } F1;
typedef struct { float m0;float m1; } F2;
typedef struct { float m0;float m1;float m2; } F3;
typedef struct { float m0;float m1;float m2;float m3; } F4;
typedef struct { double m0; } D1;
typedef struct { double m0;double m1; } D2;
typedef struct { double m0;double m1;double m2; } D3;
typedef struct { double m0;double m1;double m2;double m3; } D4;
typedef struct { __m128 m0; } V1;
typedef struct { __m128 m0;__m128 m1; } V2;
typedef struct { __m128 m0;__m128 m1;__m128 m2; } V3;
typedef struct { __m128 m0;__m128 m1;__m128 m2;__m128 m3; } V4;
typedef struct { __m256 m0; } Y1;
typedef struct { __m256 m0;__m256 m1; } Y2;
typedef struct { __m256 m0;__m256 m1;__m256 m2; } Y3;
typedef struct { __m256 m0;__m256 m1;__m256 m2;__m256 m3; } Y4;
typedef struct {F2 a,b;} NF;
typedef struct {float a[4];} AF;
typedef struct {float a;int b;} Mixed;
typedef struct {long long a,b;} Ints;
typedef __m128 __m128f;
typedef __m256 __m256f;
static F1 data_F1={1};
static F2 data_F2={1,2};
static F3 data_F3={1,2,3};
static F4 data_F4={1,2,3,4};
static D1 data_D1={1};
static D2 data_D2={1,2};
static D3 data_D3={1,2,3};
static D4 data_D4={1,2,3,4};
static V1 data_V1={{1,1,1,1}};
static V2 data_V2={{1,1,1,1},{2,2,2,2}};
static V3 data_V3={{1,1,1,1},{2,2,2,2},{3,3,3,3}};
static V4 data_V4={{1,1,1,1},{2,2,2,2},{3,3,3,3},{4,4,4,4}};
static Y1 data_Y1={{1,1,1,1,1,1,1,1}};
static Y2 data_Y2={{1,1,1,1,1,1,1,1},{2,2,2,2,2,2,2,2}};
static Y3 data_Y3={{1,1,1,1,1,1,1,1},{2,2,2,2,2,2,2,2},{3,3,3,3,3,3,3,3}};
static Y4 data_Y4={{1,1,1,1,1,1,1,1},{2,2,2,2,2,2,2,2},{3,3,3,3,3,3,3,3},{4,4,4,4,4,4,4,4}};
static NF data_NF={{1,2},{3,4}};
static AF data_AF={{1,2,3,4}};
static Mixed data_Mixed={1,2};
static Ints data_Ints={1,2};
static __m128f data___m128f={1,2,3,4};
static __m256f data___m256f={1,2,3,4,5,6,7,8};
double __vectorcall c_F1_alone(F1 a){ return a.m0; }
double __vectorcall c_F1_holes(F1 a,float b,long long c1,double d,long long e,float f){ return a.m0+b+c1+d+e+f; }
double __vectorcall c_F1_fallback(double p0,double p1,double p2,double p3,double p4,double p5,F1 a){ return a.m0+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_F1_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,F1 a){ return a.m0+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_F2_alone(F2 a){ return a.m0+a.m1; }
double __vectorcall c_F2_holes(F2 a,float b,long long c1,double d,long long e,float f){ return a.m0+a.m1+b+c1+d+e+f; }
double __vectorcall c_F2_fallback(double p0,double p1,double p2,double p3,double p4,double p5,F2 a){ return a.m0+a.m1+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_F2_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,F2 a){ return a.m0+a.m1+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_F3_alone(F3 a){ return a.m0+a.m1+a.m2; }
double __vectorcall c_F3_holes(F3 a,float b,long long c1,double d,long long e,float f){ return a.m0+a.m1+a.m2+b+c1+d+e+f; }
double __vectorcall c_F3_fallback(double p0,double p1,double p2,double p3,double p4,double p5,F3 a){ return a.m0+a.m1+a.m2+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_F3_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,F3 a){ return a.m0+a.m1+a.m2+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_F4_alone(F4 a){ return a.m0+a.m1+a.m2+a.m3; }
double __vectorcall c_F4_holes(F4 a,float b,long long c1,double d,long long e,float f){ return a.m0+a.m1+a.m2+a.m3+b+c1+d+e+f; }
double __vectorcall c_F4_fallback(double p0,double p1,double p2,double p3,double p4,double p5,F4 a){ return a.m0+a.m1+a.m2+a.m3+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_F4_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,F4 a){ return a.m0+a.m1+a.m2+a.m3+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_D1_alone(D1 a){ return a.m0; }
double __vectorcall c_D1_holes(D1 a,float b,long long c1,double d,long long e,float f){ return a.m0+b+c1+d+e+f; }
double __vectorcall c_D1_fallback(double p0,double p1,double p2,double p3,double p4,double p5,D1 a){ return a.m0+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_D1_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,D1 a){ return a.m0+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_D2_alone(D2 a){ return a.m0+a.m1; }
double __vectorcall c_D2_holes(D2 a,float b,long long c1,double d,long long e,float f){ return a.m0+a.m1+b+c1+d+e+f; }
double __vectorcall c_D2_fallback(double p0,double p1,double p2,double p3,double p4,double p5,D2 a){ return a.m0+a.m1+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_D2_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,D2 a){ return a.m0+a.m1+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_D3_alone(D3 a){ return a.m0+a.m1+a.m2; }
double __vectorcall c_D3_holes(D3 a,float b,long long c1,double d,long long e,float f){ return a.m0+a.m1+a.m2+b+c1+d+e+f; }
double __vectorcall c_D3_fallback(double p0,double p1,double p2,double p3,double p4,double p5,D3 a){ return a.m0+a.m1+a.m2+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_D3_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,D3 a){ return a.m0+a.m1+a.m2+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_D4_alone(D4 a){ return a.m0+a.m1+a.m2+a.m3; }
double __vectorcall c_D4_holes(D4 a,float b,long long c1,double d,long long e,float f){ return a.m0+a.m1+a.m2+a.m3+b+c1+d+e+f; }
double __vectorcall c_D4_fallback(double p0,double p1,double p2,double p3,double p4,double p5,D4 a){ return a.m0+a.m1+a.m2+a.m3+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_D4_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,D4 a){ return a.m0+a.m1+a.m2+a.m3+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_V1_alone(V1 a){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3]); }
double __vectorcall c_V1_holes(V1 a,float b,long long c1,double d,long long e,float f){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3])+b+c1+d+e+f; }
double __vectorcall c_V1_fallback(double p0,double p1,double p2,double p3,double p4,double p5,V1 a){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_V1_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,V1 a){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_V2_alone(V2 a){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3])+(a.m1.m128_f32[0]+a.m1.m128_f32[1]+a.m1.m128_f32[2]+a.m1.m128_f32[3]); }
double __vectorcall c_V2_holes(V2 a,float b,long long c1,double d,long long e,float f){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3])+(a.m1.m128_f32[0]+a.m1.m128_f32[1]+a.m1.m128_f32[2]+a.m1.m128_f32[3])+b+c1+d+e+f; }
double __vectorcall c_V2_fallback(double p0,double p1,double p2,double p3,double p4,double p5,V2 a){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3])+(a.m1.m128_f32[0]+a.m1.m128_f32[1]+a.m1.m128_f32[2]+a.m1.m128_f32[3])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_V2_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,V2 a){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3])+(a.m1.m128_f32[0]+a.m1.m128_f32[1]+a.m1.m128_f32[2]+a.m1.m128_f32[3])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_V3_alone(V3 a){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3])+(a.m1.m128_f32[0]+a.m1.m128_f32[1]+a.m1.m128_f32[2]+a.m1.m128_f32[3])+(a.m2.m128_f32[0]+a.m2.m128_f32[1]+a.m2.m128_f32[2]+a.m2.m128_f32[3]); }
double __vectorcall c_V3_holes(V3 a,float b,long long c1,double d,long long e,float f){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3])+(a.m1.m128_f32[0]+a.m1.m128_f32[1]+a.m1.m128_f32[2]+a.m1.m128_f32[3])+(a.m2.m128_f32[0]+a.m2.m128_f32[1]+a.m2.m128_f32[2]+a.m2.m128_f32[3])+b+c1+d+e+f; }
double __vectorcall c_V3_fallback(double p0,double p1,double p2,double p3,double p4,double p5,V3 a){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3])+(a.m1.m128_f32[0]+a.m1.m128_f32[1]+a.m1.m128_f32[2]+a.m1.m128_f32[3])+(a.m2.m128_f32[0]+a.m2.m128_f32[1]+a.m2.m128_f32[2]+a.m2.m128_f32[3])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_V3_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,V3 a){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3])+(a.m1.m128_f32[0]+a.m1.m128_f32[1]+a.m1.m128_f32[2]+a.m1.m128_f32[3])+(a.m2.m128_f32[0]+a.m2.m128_f32[1]+a.m2.m128_f32[2]+a.m2.m128_f32[3])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_V4_alone(V4 a){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3])+(a.m1.m128_f32[0]+a.m1.m128_f32[1]+a.m1.m128_f32[2]+a.m1.m128_f32[3])+(a.m2.m128_f32[0]+a.m2.m128_f32[1]+a.m2.m128_f32[2]+a.m2.m128_f32[3])+(a.m3.m128_f32[0]+a.m3.m128_f32[1]+a.m3.m128_f32[2]+a.m3.m128_f32[3]); }
double __vectorcall c_V4_holes(V4 a,float b,long long c1,double d,long long e,float f){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3])+(a.m1.m128_f32[0]+a.m1.m128_f32[1]+a.m1.m128_f32[2]+a.m1.m128_f32[3])+(a.m2.m128_f32[0]+a.m2.m128_f32[1]+a.m2.m128_f32[2]+a.m2.m128_f32[3])+(a.m3.m128_f32[0]+a.m3.m128_f32[1]+a.m3.m128_f32[2]+a.m3.m128_f32[3])+b+c1+d+e+f; }
double __vectorcall c_V4_fallback(double p0,double p1,double p2,double p3,double p4,double p5,V4 a){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3])+(a.m1.m128_f32[0]+a.m1.m128_f32[1]+a.m1.m128_f32[2]+a.m1.m128_f32[3])+(a.m2.m128_f32[0]+a.m2.m128_f32[1]+a.m2.m128_f32[2]+a.m2.m128_f32[3])+(a.m3.m128_f32[0]+a.m3.m128_f32[1]+a.m3.m128_f32[2]+a.m3.m128_f32[3])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_V4_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,V4 a){ return (a.m0.m128_f32[0]+a.m0.m128_f32[1]+a.m0.m128_f32[2]+a.m0.m128_f32[3])+(a.m1.m128_f32[0]+a.m1.m128_f32[1]+a.m1.m128_f32[2]+a.m1.m128_f32[3])+(a.m2.m128_f32[0]+a.m2.m128_f32[1]+a.m2.m128_f32[2]+a.m2.m128_f32[3])+(a.m3.m128_f32[0]+a.m3.m128_f32[1]+a.m3.m128_f32[2]+a.m3.m128_f32[3])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_Y1_alone(Y1 a){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7]); }
double __vectorcall c_Y1_holes(Y1 a,float b,long long c1,double d,long long e,float f){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7])+b+c1+d+e+f; }
double __vectorcall c_Y1_fallback(double p0,double p1,double p2,double p3,double p4,double p5,Y1 a){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_Y1_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,Y1 a){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_Y2_alone(Y2 a){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7])+(a.m1.m256_f32[0]+a.m1.m256_f32[1]+a.m1.m256_f32[2]+a.m1.m256_f32[3]+a.m1.m256_f32[4]+a.m1.m256_f32[5]+a.m1.m256_f32[6]+a.m1.m256_f32[7]); }
double __vectorcall c_Y2_holes(Y2 a,float b,long long c1,double d,long long e,float f){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7])+(a.m1.m256_f32[0]+a.m1.m256_f32[1]+a.m1.m256_f32[2]+a.m1.m256_f32[3]+a.m1.m256_f32[4]+a.m1.m256_f32[5]+a.m1.m256_f32[6]+a.m1.m256_f32[7])+b+c1+d+e+f; }
double __vectorcall c_Y2_fallback(double p0,double p1,double p2,double p3,double p4,double p5,Y2 a){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7])+(a.m1.m256_f32[0]+a.m1.m256_f32[1]+a.m1.m256_f32[2]+a.m1.m256_f32[3]+a.m1.m256_f32[4]+a.m1.m256_f32[5]+a.m1.m256_f32[6]+a.m1.m256_f32[7])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_Y2_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,Y2 a){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7])+(a.m1.m256_f32[0]+a.m1.m256_f32[1]+a.m1.m256_f32[2]+a.m1.m256_f32[3]+a.m1.m256_f32[4]+a.m1.m256_f32[5]+a.m1.m256_f32[6]+a.m1.m256_f32[7])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_Y3_alone(Y3 a){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7])+(a.m1.m256_f32[0]+a.m1.m256_f32[1]+a.m1.m256_f32[2]+a.m1.m256_f32[3]+a.m1.m256_f32[4]+a.m1.m256_f32[5]+a.m1.m256_f32[6]+a.m1.m256_f32[7])+(a.m2.m256_f32[0]+a.m2.m256_f32[1]+a.m2.m256_f32[2]+a.m2.m256_f32[3]+a.m2.m256_f32[4]+a.m2.m256_f32[5]+a.m2.m256_f32[6]+a.m2.m256_f32[7]); }
double __vectorcall c_Y3_holes(Y3 a,float b,long long c1,double d,long long e,float f){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7])+(a.m1.m256_f32[0]+a.m1.m256_f32[1]+a.m1.m256_f32[2]+a.m1.m256_f32[3]+a.m1.m256_f32[4]+a.m1.m256_f32[5]+a.m1.m256_f32[6]+a.m1.m256_f32[7])+(a.m2.m256_f32[0]+a.m2.m256_f32[1]+a.m2.m256_f32[2]+a.m2.m256_f32[3]+a.m2.m256_f32[4]+a.m2.m256_f32[5]+a.m2.m256_f32[6]+a.m2.m256_f32[7])+b+c1+d+e+f; }
double __vectorcall c_Y3_fallback(double p0,double p1,double p2,double p3,double p4,double p5,Y3 a){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7])+(a.m1.m256_f32[0]+a.m1.m256_f32[1]+a.m1.m256_f32[2]+a.m1.m256_f32[3]+a.m1.m256_f32[4]+a.m1.m256_f32[5]+a.m1.m256_f32[6]+a.m1.m256_f32[7])+(a.m2.m256_f32[0]+a.m2.m256_f32[1]+a.m2.m256_f32[2]+a.m2.m256_f32[3]+a.m2.m256_f32[4]+a.m2.m256_f32[5]+a.m2.m256_f32[6]+a.m2.m256_f32[7])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_Y3_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,Y3 a){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7])+(a.m1.m256_f32[0]+a.m1.m256_f32[1]+a.m1.m256_f32[2]+a.m1.m256_f32[3]+a.m1.m256_f32[4]+a.m1.m256_f32[5]+a.m1.m256_f32[6]+a.m1.m256_f32[7])+(a.m2.m256_f32[0]+a.m2.m256_f32[1]+a.m2.m256_f32[2]+a.m2.m256_f32[3]+a.m2.m256_f32[4]+a.m2.m256_f32[5]+a.m2.m256_f32[6]+a.m2.m256_f32[7])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_Y4_alone(Y4 a){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7])+(a.m1.m256_f32[0]+a.m1.m256_f32[1]+a.m1.m256_f32[2]+a.m1.m256_f32[3]+a.m1.m256_f32[4]+a.m1.m256_f32[5]+a.m1.m256_f32[6]+a.m1.m256_f32[7])+(a.m2.m256_f32[0]+a.m2.m256_f32[1]+a.m2.m256_f32[2]+a.m2.m256_f32[3]+a.m2.m256_f32[4]+a.m2.m256_f32[5]+a.m2.m256_f32[6]+a.m2.m256_f32[7])+(a.m3.m256_f32[0]+a.m3.m256_f32[1]+a.m3.m256_f32[2]+a.m3.m256_f32[3]+a.m3.m256_f32[4]+a.m3.m256_f32[5]+a.m3.m256_f32[6]+a.m3.m256_f32[7]); }
double __vectorcall c_Y4_holes(Y4 a,float b,long long c1,double d,long long e,float f){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7])+(a.m1.m256_f32[0]+a.m1.m256_f32[1]+a.m1.m256_f32[2]+a.m1.m256_f32[3]+a.m1.m256_f32[4]+a.m1.m256_f32[5]+a.m1.m256_f32[6]+a.m1.m256_f32[7])+(a.m2.m256_f32[0]+a.m2.m256_f32[1]+a.m2.m256_f32[2]+a.m2.m256_f32[3]+a.m2.m256_f32[4]+a.m2.m256_f32[5]+a.m2.m256_f32[6]+a.m2.m256_f32[7])+(a.m3.m256_f32[0]+a.m3.m256_f32[1]+a.m3.m256_f32[2]+a.m3.m256_f32[3]+a.m3.m256_f32[4]+a.m3.m256_f32[5]+a.m3.m256_f32[6]+a.m3.m256_f32[7])+b+c1+d+e+f; }
double __vectorcall c_Y4_fallback(double p0,double p1,double p2,double p3,double p4,double p5,Y4 a){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7])+(a.m1.m256_f32[0]+a.m1.m256_f32[1]+a.m1.m256_f32[2]+a.m1.m256_f32[3]+a.m1.m256_f32[4]+a.m1.m256_f32[5]+a.m1.m256_f32[6]+a.m1.m256_f32[7])+(a.m2.m256_f32[0]+a.m2.m256_f32[1]+a.m2.m256_f32[2]+a.m2.m256_f32[3]+a.m2.m256_f32[4]+a.m2.m256_f32[5]+a.m2.m256_f32[6]+a.m2.m256_f32[7])+(a.m3.m256_f32[0]+a.m3.m256_f32[1]+a.m3.m256_f32[2]+a.m3.m256_f32[3]+a.m3.m256_f32[4]+a.m3.m256_f32[5]+a.m3.m256_f32[6]+a.m3.m256_f32[7])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_Y4_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,Y4 a){ return (a.m0.m256_f32[0]+a.m0.m256_f32[1]+a.m0.m256_f32[2]+a.m0.m256_f32[3]+a.m0.m256_f32[4]+a.m0.m256_f32[5]+a.m0.m256_f32[6]+a.m0.m256_f32[7])+(a.m1.m256_f32[0]+a.m1.m256_f32[1]+a.m1.m256_f32[2]+a.m1.m256_f32[3]+a.m1.m256_f32[4]+a.m1.m256_f32[5]+a.m1.m256_f32[6]+a.m1.m256_f32[7])+(a.m2.m256_f32[0]+a.m2.m256_f32[1]+a.m2.m256_f32[2]+a.m2.m256_f32[3]+a.m2.m256_f32[4]+a.m2.m256_f32[5]+a.m2.m256_f32[6]+a.m2.m256_f32[7])+(a.m3.m256_f32[0]+a.m3.m256_f32[1]+a.m3.m256_f32[2]+a.m3.m256_f32[3]+a.m3.m256_f32[4]+a.m3.m256_f32[5]+a.m3.m256_f32[6]+a.m3.m256_f32[7])+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_NF_alone(NF a){ return a.a.m0+a.a.m1+a.b.m0+a.b.m1; }
double __vectorcall c_NF_holes(NF a,float b,long long c1,double d,long long e,float f){ return a.a.m0+a.a.m1+a.b.m0+a.b.m1+b+c1+d+e+f; }
double __vectorcall c_NF_fallback(double p0,double p1,double p2,double p3,double p4,double p5,NF a){ return a.a.m0+a.a.m1+a.b.m0+a.b.m1+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_NF_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,NF a){ return a.a.m0+a.a.m1+a.b.m0+a.b.m1+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_AF_alone(AF a){ return a.a[0]+a.a[1]+a.a[2]+a.a[3]; }
double __vectorcall c_AF_holes(AF a,float b,long long c1,double d,long long e,float f){ return a.a[0]+a.a[1]+a.a[2]+a.a[3]+b+c1+d+e+f; }
double __vectorcall c_AF_fallback(double p0,double p1,double p2,double p3,double p4,double p5,AF a){ return a.a[0]+a.a[1]+a.a[2]+a.a[3]+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_AF_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,AF a){ return a.a[0]+a.a[1]+a.a[2]+a.a[3]+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_Mixed_alone(Mixed a){ return a.a+a.b; }
double __vectorcall c_Mixed_holes(Mixed a,float b,long long c1,double d,long long e,float f){ return a.a+a.b+b+c1+d+e+f; }
double __vectorcall c_Mixed_fallback(double p0,double p1,double p2,double p3,double p4,double p5,Mixed a){ return a.a+a.b+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_Mixed_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,Mixed a){ return a.a+a.b+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_Ints_alone(Ints a){ return a.a+a.b; }
double __vectorcall c_Ints_holes(Ints a,float b,long long c1,double d,long long e,float f){ return a.a+a.b+b+c1+d+e+f; }
double __vectorcall c_Ints_fallback(double p0,double p1,double p2,double p3,double p4,double p5,Ints a){ return a.a+a.b+p0+p1+p2+p3+p4+p5; }
double __vectorcall c_Ints_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,Ints a){ return a.a+a.b+p0+p1+p2+p3+p4+p5; }
double __vectorcall c___m128f_alone(__m128f a){ return a.m128_f32[0]+a.m128_f32[1]+a.m128_f32[2]+a.m128_f32[3]; }
double __vectorcall c___m128f_holes(__m128f a,float b,long long c1,double d,long long e,float f){ return a.m128_f32[0]+a.m128_f32[1]+a.m128_f32[2]+a.m128_f32[3]+b+c1+d+e+f; }
double __vectorcall c___m128f_fallback(double p0,double p1,double p2,double p3,double p4,double p5,__m128f a){ return a.m128_f32[0]+a.m128_f32[1]+a.m128_f32[2]+a.m128_f32[3]+p0+p1+p2+p3+p4+p5; }
double __vectorcall c___m128f_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,__m128f a){ return a.m128_f32[0]+a.m128_f32[1]+a.m128_f32[2]+a.m128_f32[3]+p0+p1+p2+p3+p4+p5; }
double __vectorcall c___m256f_alone(__m256f a){ return a.m256_f32[0]+a.m256_f32[1]+a.m256_f32[2]+a.m256_f32[3]+a.m256_f32[4]+a.m256_f32[5]+a.m256_f32[6]+a.m256_f32[7]; }
double __vectorcall c___m256f_holes(__m256f a,float b,long long c1,double d,long long e,float f){ return a.m256_f32[0]+a.m256_f32[1]+a.m256_f32[2]+a.m256_f32[3]+a.m256_f32[4]+a.m256_f32[5]+a.m256_f32[6]+a.m256_f32[7]+b+c1+d+e+f; }
double __vectorcall c___m256f_fallback(double p0,double p1,double p2,double p3,double p4,double p5,__m256f a){ return a.m256_f32[0]+a.m256_f32[1]+a.m256_f32[2]+a.m256_f32[3]+a.m256_f32[4]+a.m256_f32[5]+a.m256_f32[6]+a.m256_f32[7]+p0+p1+p2+p3+p4+p5; }
double __vectorcall c___m256f_seventh(long long p0,long long p1,long long p2,long long p3,long long p4,long long p5,__m256f a){ return a.m256_f32[0]+a.m256_f32[1]+a.m256_f32[2]+a.m256_f32[3]+a.m256_f32[4]+a.m256_f32[5]+a.m256_f32[6]+a.m256_f32[7]+p0+p1+p2+p3+p4+p5; }
#define CASE_F1_alone(S) extern double __vectorcall a_##S(F1); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(F1); \
static double check_a_##S(void) { return a_##S(data_F1); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_F1); }
CASE_F1_alone(F1_alone_rsp_1)
CASE_F1_alone(F1_alone_rsp_3)
CASE_F1_alone(F1_alone_rsp_5)
CASE_F1_alone(F1_alone_rsp_7)
CASE_F1_alone(F1_alone_rsp_11)
CASE_F1_alone(F1_alone_rsp_15)
CASE_F1_alone(F1_alone_rbp_1)
CASE_F1_alone(F1_alone_rbp_3)
CASE_F1_alone(F1_alone_rbp_5)
CASE_F1_alone(F1_alone_rbp_7)
CASE_F1_alone(F1_alone_rbp_11)
CASE_F1_alone(F1_alone_rbp_15)
#define CASE_F1_holes(S) extern double __vectorcall a_##S(F1,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(F1,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_F1,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_F1,11.0,12,13.0,14,15.0); }
CASE_F1_holes(F1_holes_rsp_1)
CASE_F1_holes(F1_holes_rsp_3)
CASE_F1_holes(F1_holes_rsp_5)
CASE_F1_holes(F1_holes_rsp_7)
CASE_F1_holes(F1_holes_rsp_11)
CASE_F1_holes(F1_holes_rsp_15)
CASE_F1_holes(F1_holes_rbp_1)
CASE_F1_holes(F1_holes_rbp_3)
CASE_F1_holes(F1_holes_rbp_5)
CASE_F1_holes(F1_holes_rbp_7)
CASE_F1_holes(F1_holes_rbp_11)
CASE_F1_holes(F1_holes_rbp_15)
#define CASE_F1_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,F1); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,F1); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_F1); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_F1); }
CASE_F1_fallback(F1_fallback_rsp_1)
CASE_F1_fallback(F1_fallback_rsp_3)
CASE_F1_fallback(F1_fallback_rsp_5)
CASE_F1_fallback(F1_fallback_rsp_7)
CASE_F1_fallback(F1_fallback_rsp_11)
CASE_F1_fallback(F1_fallback_rsp_15)
CASE_F1_fallback(F1_fallback_rbp_1)
CASE_F1_fallback(F1_fallback_rbp_3)
CASE_F1_fallback(F1_fallback_rbp_5)
CASE_F1_fallback(F1_fallback_rbp_7)
CASE_F1_fallback(F1_fallback_rbp_11)
CASE_F1_fallback(F1_fallback_rbp_15)
#define CASE_F1_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,F1); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,F1); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_F1); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_F1); }
CASE_F1_seventh(F1_seventh_rsp_1)
CASE_F1_seventh(F1_seventh_rsp_3)
CASE_F1_seventh(F1_seventh_rsp_5)
CASE_F1_seventh(F1_seventh_rsp_7)
CASE_F1_seventh(F1_seventh_rsp_11)
CASE_F1_seventh(F1_seventh_rsp_15)
CASE_F1_seventh(F1_seventh_rbp_1)
CASE_F1_seventh(F1_seventh_rbp_3)
CASE_F1_seventh(F1_seventh_rbp_5)
CASE_F1_seventh(F1_seventh_rbp_7)
CASE_F1_seventh(F1_seventh_rbp_11)
CASE_F1_seventh(F1_seventh_rbp_15)
#define CASE_F2_alone(S) extern double __vectorcall a_##S(F2); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(F2); \
static double check_a_##S(void) { return a_##S(data_F2); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_F2); }
CASE_F2_alone(F2_alone_rsp_1)
CASE_F2_alone(F2_alone_rsp_3)
CASE_F2_alone(F2_alone_rsp_5)
CASE_F2_alone(F2_alone_rsp_7)
CASE_F2_alone(F2_alone_rsp_11)
CASE_F2_alone(F2_alone_rsp_15)
CASE_F2_alone(F2_alone_rbp_1)
CASE_F2_alone(F2_alone_rbp_3)
CASE_F2_alone(F2_alone_rbp_5)
CASE_F2_alone(F2_alone_rbp_7)
CASE_F2_alone(F2_alone_rbp_11)
CASE_F2_alone(F2_alone_rbp_15)
#define CASE_F2_holes(S) extern double __vectorcall a_##S(F2,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(F2,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_F2,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_F2,11.0,12,13.0,14,15.0); }
CASE_F2_holes(F2_holes_rsp_1)
CASE_F2_holes(F2_holes_rsp_3)
CASE_F2_holes(F2_holes_rsp_5)
CASE_F2_holes(F2_holes_rsp_7)
CASE_F2_holes(F2_holes_rsp_11)
CASE_F2_holes(F2_holes_rsp_15)
CASE_F2_holes(F2_holes_rbp_1)
CASE_F2_holes(F2_holes_rbp_3)
CASE_F2_holes(F2_holes_rbp_5)
CASE_F2_holes(F2_holes_rbp_7)
CASE_F2_holes(F2_holes_rbp_11)
CASE_F2_holes(F2_holes_rbp_15)
#define CASE_F2_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,F2); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,F2); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_F2); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_F2); }
CASE_F2_fallback(F2_fallback_rsp_1)
CASE_F2_fallback(F2_fallback_rsp_3)
CASE_F2_fallback(F2_fallback_rsp_5)
CASE_F2_fallback(F2_fallback_rsp_7)
CASE_F2_fallback(F2_fallback_rsp_11)
CASE_F2_fallback(F2_fallback_rsp_15)
CASE_F2_fallback(F2_fallback_rbp_1)
CASE_F2_fallback(F2_fallback_rbp_3)
CASE_F2_fallback(F2_fallback_rbp_5)
CASE_F2_fallback(F2_fallback_rbp_7)
CASE_F2_fallback(F2_fallback_rbp_11)
CASE_F2_fallback(F2_fallback_rbp_15)
#define CASE_F2_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,F2); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,F2); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_F2); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_F2); }
CASE_F2_seventh(F2_seventh_rsp_1)
CASE_F2_seventh(F2_seventh_rsp_3)
CASE_F2_seventh(F2_seventh_rsp_5)
CASE_F2_seventh(F2_seventh_rsp_7)
CASE_F2_seventh(F2_seventh_rsp_11)
CASE_F2_seventh(F2_seventh_rsp_15)
CASE_F2_seventh(F2_seventh_rbp_1)
CASE_F2_seventh(F2_seventh_rbp_3)
CASE_F2_seventh(F2_seventh_rbp_5)
CASE_F2_seventh(F2_seventh_rbp_7)
CASE_F2_seventh(F2_seventh_rbp_11)
CASE_F2_seventh(F2_seventh_rbp_15)
#define CASE_F3_alone(S) extern double __vectorcall a_##S(F3); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(F3); \
static double check_a_##S(void) { return a_##S(data_F3); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_F3); }
CASE_F3_alone(F3_alone_rsp_1)
CASE_F3_alone(F3_alone_rsp_3)
CASE_F3_alone(F3_alone_rsp_5)
CASE_F3_alone(F3_alone_rsp_7)
CASE_F3_alone(F3_alone_rsp_11)
CASE_F3_alone(F3_alone_rsp_15)
CASE_F3_alone(F3_alone_rbp_1)
CASE_F3_alone(F3_alone_rbp_3)
CASE_F3_alone(F3_alone_rbp_5)
CASE_F3_alone(F3_alone_rbp_7)
CASE_F3_alone(F3_alone_rbp_11)
CASE_F3_alone(F3_alone_rbp_15)
#define CASE_F3_holes(S) extern double __vectorcall a_##S(F3,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(F3,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_F3,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_F3,11.0,12,13.0,14,15.0); }
CASE_F3_holes(F3_holes_rsp_1)
CASE_F3_holes(F3_holes_rsp_3)
CASE_F3_holes(F3_holes_rsp_5)
CASE_F3_holes(F3_holes_rsp_7)
CASE_F3_holes(F3_holes_rsp_11)
CASE_F3_holes(F3_holes_rsp_15)
CASE_F3_holes(F3_holes_rbp_1)
CASE_F3_holes(F3_holes_rbp_3)
CASE_F3_holes(F3_holes_rbp_5)
CASE_F3_holes(F3_holes_rbp_7)
CASE_F3_holes(F3_holes_rbp_11)
CASE_F3_holes(F3_holes_rbp_15)
#define CASE_F3_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,F3); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,F3); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_F3); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_F3); }
CASE_F3_fallback(F3_fallback_rsp_1)
CASE_F3_fallback(F3_fallback_rsp_3)
CASE_F3_fallback(F3_fallback_rsp_5)
CASE_F3_fallback(F3_fallback_rsp_7)
CASE_F3_fallback(F3_fallback_rsp_11)
CASE_F3_fallback(F3_fallback_rsp_15)
CASE_F3_fallback(F3_fallback_rbp_1)
CASE_F3_fallback(F3_fallback_rbp_3)
CASE_F3_fallback(F3_fallback_rbp_5)
CASE_F3_fallback(F3_fallback_rbp_7)
CASE_F3_fallback(F3_fallback_rbp_11)
CASE_F3_fallback(F3_fallback_rbp_15)
#define CASE_F3_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,F3); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,F3); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_F3); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_F3); }
CASE_F3_seventh(F3_seventh_rsp_1)
CASE_F3_seventh(F3_seventh_rsp_3)
CASE_F3_seventh(F3_seventh_rsp_5)
CASE_F3_seventh(F3_seventh_rsp_7)
CASE_F3_seventh(F3_seventh_rsp_11)
CASE_F3_seventh(F3_seventh_rsp_15)
CASE_F3_seventh(F3_seventh_rbp_1)
CASE_F3_seventh(F3_seventh_rbp_3)
CASE_F3_seventh(F3_seventh_rbp_5)
CASE_F3_seventh(F3_seventh_rbp_7)
CASE_F3_seventh(F3_seventh_rbp_11)
CASE_F3_seventh(F3_seventh_rbp_15)
#define CASE_F4_alone(S) extern double __vectorcall a_##S(F4); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(F4); \
static double check_a_##S(void) { return a_##S(data_F4); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_F4); }
CASE_F4_alone(F4_alone_rsp_1)
CASE_F4_alone(F4_alone_rsp_3)
CASE_F4_alone(F4_alone_rsp_5)
CASE_F4_alone(F4_alone_rsp_7)
CASE_F4_alone(F4_alone_rsp_11)
CASE_F4_alone(F4_alone_rsp_15)
CASE_F4_alone(F4_alone_rbp_1)
CASE_F4_alone(F4_alone_rbp_3)
CASE_F4_alone(F4_alone_rbp_5)
CASE_F4_alone(F4_alone_rbp_7)
CASE_F4_alone(F4_alone_rbp_11)
CASE_F4_alone(F4_alone_rbp_15)
#define CASE_F4_holes(S) extern double __vectorcall a_##S(F4,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(F4,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_F4,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_F4,11.0,12,13.0,14,15.0); }
CASE_F4_holes(F4_holes_rsp_1)
CASE_F4_holes(F4_holes_rsp_3)
CASE_F4_holes(F4_holes_rsp_5)
CASE_F4_holes(F4_holes_rsp_7)
CASE_F4_holes(F4_holes_rsp_11)
CASE_F4_holes(F4_holes_rsp_15)
CASE_F4_holes(F4_holes_rbp_1)
CASE_F4_holes(F4_holes_rbp_3)
CASE_F4_holes(F4_holes_rbp_5)
CASE_F4_holes(F4_holes_rbp_7)
CASE_F4_holes(F4_holes_rbp_11)
CASE_F4_holes(F4_holes_rbp_15)
#define CASE_F4_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,F4); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,F4); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_F4); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_F4); }
CASE_F4_fallback(F4_fallback_rsp_1)
CASE_F4_fallback(F4_fallback_rsp_3)
CASE_F4_fallback(F4_fallback_rsp_5)
CASE_F4_fallback(F4_fallback_rsp_7)
CASE_F4_fallback(F4_fallback_rsp_11)
CASE_F4_fallback(F4_fallback_rsp_15)
CASE_F4_fallback(F4_fallback_rbp_1)
CASE_F4_fallback(F4_fallback_rbp_3)
CASE_F4_fallback(F4_fallback_rbp_5)
CASE_F4_fallback(F4_fallback_rbp_7)
CASE_F4_fallback(F4_fallback_rbp_11)
CASE_F4_fallback(F4_fallback_rbp_15)
#define CASE_F4_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,F4); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,F4); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_F4); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_F4); }
CASE_F4_seventh(F4_seventh_rsp_1)
CASE_F4_seventh(F4_seventh_rsp_3)
CASE_F4_seventh(F4_seventh_rsp_5)
CASE_F4_seventh(F4_seventh_rsp_7)
CASE_F4_seventh(F4_seventh_rsp_11)
CASE_F4_seventh(F4_seventh_rsp_15)
CASE_F4_seventh(F4_seventh_rbp_1)
CASE_F4_seventh(F4_seventh_rbp_3)
CASE_F4_seventh(F4_seventh_rbp_5)
CASE_F4_seventh(F4_seventh_rbp_7)
CASE_F4_seventh(F4_seventh_rbp_11)
CASE_F4_seventh(F4_seventh_rbp_15)
#define CASE_D1_alone(S) extern double __vectorcall a_##S(D1); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(D1); \
static double check_a_##S(void) { return a_##S(data_D1); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_D1); }
CASE_D1_alone(D1_alone_rsp_1)
CASE_D1_alone(D1_alone_rsp_3)
CASE_D1_alone(D1_alone_rsp_5)
CASE_D1_alone(D1_alone_rsp_7)
CASE_D1_alone(D1_alone_rsp_11)
CASE_D1_alone(D1_alone_rsp_15)
CASE_D1_alone(D1_alone_rbp_1)
CASE_D1_alone(D1_alone_rbp_3)
CASE_D1_alone(D1_alone_rbp_5)
CASE_D1_alone(D1_alone_rbp_7)
CASE_D1_alone(D1_alone_rbp_11)
CASE_D1_alone(D1_alone_rbp_15)
#define CASE_D1_holes(S) extern double __vectorcall a_##S(D1,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(D1,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_D1,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_D1,11.0,12,13.0,14,15.0); }
CASE_D1_holes(D1_holes_rsp_1)
CASE_D1_holes(D1_holes_rsp_3)
CASE_D1_holes(D1_holes_rsp_5)
CASE_D1_holes(D1_holes_rsp_7)
CASE_D1_holes(D1_holes_rsp_11)
CASE_D1_holes(D1_holes_rsp_15)
CASE_D1_holes(D1_holes_rbp_1)
CASE_D1_holes(D1_holes_rbp_3)
CASE_D1_holes(D1_holes_rbp_5)
CASE_D1_holes(D1_holes_rbp_7)
CASE_D1_holes(D1_holes_rbp_11)
CASE_D1_holes(D1_holes_rbp_15)
#define CASE_D1_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,D1); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,D1); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_D1); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_D1); }
CASE_D1_fallback(D1_fallback_rsp_1)
CASE_D1_fallback(D1_fallback_rsp_3)
CASE_D1_fallback(D1_fallback_rsp_5)
CASE_D1_fallback(D1_fallback_rsp_7)
CASE_D1_fallback(D1_fallback_rsp_11)
CASE_D1_fallback(D1_fallback_rsp_15)
CASE_D1_fallback(D1_fallback_rbp_1)
CASE_D1_fallback(D1_fallback_rbp_3)
CASE_D1_fallback(D1_fallback_rbp_5)
CASE_D1_fallback(D1_fallback_rbp_7)
CASE_D1_fallback(D1_fallback_rbp_11)
CASE_D1_fallback(D1_fallback_rbp_15)
#define CASE_D1_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,D1); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,D1); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_D1); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_D1); }
CASE_D1_seventh(D1_seventh_rsp_1)
CASE_D1_seventh(D1_seventh_rsp_3)
CASE_D1_seventh(D1_seventh_rsp_5)
CASE_D1_seventh(D1_seventh_rsp_7)
CASE_D1_seventh(D1_seventh_rsp_11)
CASE_D1_seventh(D1_seventh_rsp_15)
CASE_D1_seventh(D1_seventh_rbp_1)
CASE_D1_seventh(D1_seventh_rbp_3)
CASE_D1_seventh(D1_seventh_rbp_5)
CASE_D1_seventh(D1_seventh_rbp_7)
CASE_D1_seventh(D1_seventh_rbp_11)
CASE_D1_seventh(D1_seventh_rbp_15)
#define CASE_D2_alone(S) extern double __vectorcall a_##S(D2); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(D2); \
static double check_a_##S(void) { return a_##S(data_D2); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_D2); }
CASE_D2_alone(D2_alone_rsp_1)
CASE_D2_alone(D2_alone_rsp_3)
CASE_D2_alone(D2_alone_rsp_5)
CASE_D2_alone(D2_alone_rsp_7)
CASE_D2_alone(D2_alone_rsp_11)
CASE_D2_alone(D2_alone_rsp_15)
CASE_D2_alone(D2_alone_rbp_1)
CASE_D2_alone(D2_alone_rbp_3)
CASE_D2_alone(D2_alone_rbp_5)
CASE_D2_alone(D2_alone_rbp_7)
CASE_D2_alone(D2_alone_rbp_11)
CASE_D2_alone(D2_alone_rbp_15)
#define CASE_D2_holes(S) extern double __vectorcall a_##S(D2,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(D2,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_D2,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_D2,11.0,12,13.0,14,15.0); }
CASE_D2_holes(D2_holes_rsp_1)
CASE_D2_holes(D2_holes_rsp_3)
CASE_D2_holes(D2_holes_rsp_5)
CASE_D2_holes(D2_holes_rsp_7)
CASE_D2_holes(D2_holes_rsp_11)
CASE_D2_holes(D2_holes_rsp_15)
CASE_D2_holes(D2_holes_rbp_1)
CASE_D2_holes(D2_holes_rbp_3)
CASE_D2_holes(D2_holes_rbp_5)
CASE_D2_holes(D2_holes_rbp_7)
CASE_D2_holes(D2_holes_rbp_11)
CASE_D2_holes(D2_holes_rbp_15)
#define CASE_D2_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,D2); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,D2); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_D2); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_D2); }
CASE_D2_fallback(D2_fallback_rsp_1)
CASE_D2_fallback(D2_fallback_rsp_3)
CASE_D2_fallback(D2_fallback_rsp_5)
CASE_D2_fallback(D2_fallback_rsp_7)
CASE_D2_fallback(D2_fallback_rsp_11)
CASE_D2_fallback(D2_fallback_rsp_15)
CASE_D2_fallback(D2_fallback_rbp_1)
CASE_D2_fallback(D2_fallback_rbp_3)
CASE_D2_fallback(D2_fallback_rbp_5)
CASE_D2_fallback(D2_fallback_rbp_7)
CASE_D2_fallback(D2_fallback_rbp_11)
CASE_D2_fallback(D2_fallback_rbp_15)
#define CASE_D2_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,D2); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,D2); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_D2); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_D2); }
CASE_D2_seventh(D2_seventh_rsp_1)
CASE_D2_seventh(D2_seventh_rsp_3)
CASE_D2_seventh(D2_seventh_rsp_5)
CASE_D2_seventh(D2_seventh_rsp_7)
CASE_D2_seventh(D2_seventh_rsp_11)
CASE_D2_seventh(D2_seventh_rsp_15)
CASE_D2_seventh(D2_seventh_rbp_1)
CASE_D2_seventh(D2_seventh_rbp_3)
CASE_D2_seventh(D2_seventh_rbp_5)
CASE_D2_seventh(D2_seventh_rbp_7)
CASE_D2_seventh(D2_seventh_rbp_11)
CASE_D2_seventh(D2_seventh_rbp_15)
#define CASE_D3_alone(S) extern double __vectorcall a_##S(D3); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(D3); \
static double check_a_##S(void) { return a_##S(data_D3); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_D3); }
CASE_D3_alone(D3_alone_rsp_1)
CASE_D3_alone(D3_alone_rsp_3)
CASE_D3_alone(D3_alone_rsp_5)
CASE_D3_alone(D3_alone_rsp_7)
CASE_D3_alone(D3_alone_rsp_11)
CASE_D3_alone(D3_alone_rsp_15)
CASE_D3_alone(D3_alone_rbp_1)
CASE_D3_alone(D3_alone_rbp_3)
CASE_D3_alone(D3_alone_rbp_5)
CASE_D3_alone(D3_alone_rbp_7)
CASE_D3_alone(D3_alone_rbp_11)
CASE_D3_alone(D3_alone_rbp_15)
#define CASE_D3_holes(S) extern double __vectorcall a_##S(D3,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(D3,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_D3,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_D3,11.0,12,13.0,14,15.0); }
CASE_D3_holes(D3_holes_rsp_1)
CASE_D3_holes(D3_holes_rsp_3)
CASE_D3_holes(D3_holes_rsp_5)
CASE_D3_holes(D3_holes_rsp_7)
CASE_D3_holes(D3_holes_rsp_11)
CASE_D3_holes(D3_holes_rsp_15)
CASE_D3_holes(D3_holes_rbp_1)
CASE_D3_holes(D3_holes_rbp_3)
CASE_D3_holes(D3_holes_rbp_5)
CASE_D3_holes(D3_holes_rbp_7)
CASE_D3_holes(D3_holes_rbp_11)
CASE_D3_holes(D3_holes_rbp_15)
#define CASE_D3_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,D3); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,D3); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_D3); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_D3); }
CASE_D3_fallback(D3_fallback_rsp_1)
CASE_D3_fallback(D3_fallback_rsp_3)
CASE_D3_fallback(D3_fallback_rsp_5)
CASE_D3_fallback(D3_fallback_rsp_7)
CASE_D3_fallback(D3_fallback_rsp_11)
CASE_D3_fallback(D3_fallback_rsp_15)
CASE_D3_fallback(D3_fallback_rbp_1)
CASE_D3_fallback(D3_fallback_rbp_3)
CASE_D3_fallback(D3_fallback_rbp_5)
CASE_D3_fallback(D3_fallback_rbp_7)
CASE_D3_fallback(D3_fallback_rbp_11)
CASE_D3_fallback(D3_fallback_rbp_15)
#define CASE_D3_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,D3); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,D3); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_D3); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_D3); }
CASE_D3_seventh(D3_seventh_rsp_1)
CASE_D3_seventh(D3_seventh_rsp_3)
CASE_D3_seventh(D3_seventh_rsp_5)
CASE_D3_seventh(D3_seventh_rsp_7)
CASE_D3_seventh(D3_seventh_rsp_11)
CASE_D3_seventh(D3_seventh_rsp_15)
CASE_D3_seventh(D3_seventh_rbp_1)
CASE_D3_seventh(D3_seventh_rbp_3)
CASE_D3_seventh(D3_seventh_rbp_5)
CASE_D3_seventh(D3_seventh_rbp_7)
CASE_D3_seventh(D3_seventh_rbp_11)
CASE_D3_seventh(D3_seventh_rbp_15)
#define CASE_D4_alone(S) extern double __vectorcall a_##S(D4); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(D4); \
static double check_a_##S(void) { return a_##S(data_D4); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_D4); }
CASE_D4_alone(D4_alone_rsp_1)
CASE_D4_alone(D4_alone_rsp_3)
CASE_D4_alone(D4_alone_rsp_5)
CASE_D4_alone(D4_alone_rsp_7)
CASE_D4_alone(D4_alone_rsp_11)
CASE_D4_alone(D4_alone_rsp_15)
CASE_D4_alone(D4_alone_rbp_1)
CASE_D4_alone(D4_alone_rbp_3)
CASE_D4_alone(D4_alone_rbp_5)
CASE_D4_alone(D4_alone_rbp_7)
CASE_D4_alone(D4_alone_rbp_11)
CASE_D4_alone(D4_alone_rbp_15)
#define CASE_D4_holes(S) extern double __vectorcall a_##S(D4,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(D4,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_D4,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_D4,11.0,12,13.0,14,15.0); }
CASE_D4_holes(D4_holes_rsp_1)
CASE_D4_holes(D4_holes_rsp_3)
CASE_D4_holes(D4_holes_rsp_5)
CASE_D4_holes(D4_holes_rsp_7)
CASE_D4_holes(D4_holes_rsp_11)
CASE_D4_holes(D4_holes_rsp_15)
CASE_D4_holes(D4_holes_rbp_1)
CASE_D4_holes(D4_holes_rbp_3)
CASE_D4_holes(D4_holes_rbp_5)
CASE_D4_holes(D4_holes_rbp_7)
CASE_D4_holes(D4_holes_rbp_11)
CASE_D4_holes(D4_holes_rbp_15)
#define CASE_D4_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,D4); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,D4); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_D4); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_D4); }
CASE_D4_fallback(D4_fallback_rsp_1)
CASE_D4_fallback(D4_fallback_rsp_3)
CASE_D4_fallback(D4_fallback_rsp_5)
CASE_D4_fallback(D4_fallback_rsp_7)
CASE_D4_fallback(D4_fallback_rsp_11)
CASE_D4_fallback(D4_fallback_rsp_15)
CASE_D4_fallback(D4_fallback_rbp_1)
CASE_D4_fallback(D4_fallback_rbp_3)
CASE_D4_fallback(D4_fallback_rbp_5)
CASE_D4_fallback(D4_fallback_rbp_7)
CASE_D4_fallback(D4_fallback_rbp_11)
CASE_D4_fallback(D4_fallback_rbp_15)
#define CASE_D4_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,D4); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,D4); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_D4); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_D4); }
CASE_D4_seventh(D4_seventh_rsp_1)
CASE_D4_seventh(D4_seventh_rsp_3)
CASE_D4_seventh(D4_seventh_rsp_5)
CASE_D4_seventh(D4_seventh_rsp_7)
CASE_D4_seventh(D4_seventh_rsp_11)
CASE_D4_seventh(D4_seventh_rsp_15)
CASE_D4_seventh(D4_seventh_rbp_1)
CASE_D4_seventh(D4_seventh_rbp_3)
CASE_D4_seventh(D4_seventh_rbp_5)
CASE_D4_seventh(D4_seventh_rbp_7)
CASE_D4_seventh(D4_seventh_rbp_11)
CASE_D4_seventh(D4_seventh_rbp_15)
#define CASE_V1_alone(S) extern double __vectorcall a_##S(V1); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(V1); \
static double check_a_##S(void) { return a_##S(data_V1); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_V1); }
CASE_V1_alone(V1_alone_rsp_1)
CASE_V1_alone(V1_alone_rsp_3)
CASE_V1_alone(V1_alone_rsp_5)
CASE_V1_alone(V1_alone_rsp_7)
CASE_V1_alone(V1_alone_rsp_11)
CASE_V1_alone(V1_alone_rsp_15)
CASE_V1_alone(V1_alone_rbp_1)
CASE_V1_alone(V1_alone_rbp_3)
CASE_V1_alone(V1_alone_rbp_5)
CASE_V1_alone(V1_alone_rbp_7)
CASE_V1_alone(V1_alone_rbp_11)
CASE_V1_alone(V1_alone_rbp_15)
#define CASE_V1_holes(S) extern double __vectorcall a_##S(V1,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(V1,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_V1,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_V1,11.0,12,13.0,14,15.0); }
CASE_V1_holes(V1_holes_rsp_1)
CASE_V1_holes(V1_holes_rsp_3)
CASE_V1_holes(V1_holes_rsp_5)
CASE_V1_holes(V1_holes_rsp_7)
CASE_V1_holes(V1_holes_rsp_11)
CASE_V1_holes(V1_holes_rsp_15)
CASE_V1_holes(V1_holes_rbp_1)
CASE_V1_holes(V1_holes_rbp_3)
CASE_V1_holes(V1_holes_rbp_5)
CASE_V1_holes(V1_holes_rbp_7)
CASE_V1_holes(V1_holes_rbp_11)
CASE_V1_holes(V1_holes_rbp_15)
#define CASE_V1_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,V1); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,V1); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_V1); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_V1); }
CASE_V1_fallback(V1_fallback_rsp_1)
CASE_V1_fallback(V1_fallback_rsp_3)
CASE_V1_fallback(V1_fallback_rsp_5)
CASE_V1_fallback(V1_fallback_rsp_7)
CASE_V1_fallback(V1_fallback_rsp_11)
CASE_V1_fallback(V1_fallback_rsp_15)
CASE_V1_fallback(V1_fallback_rbp_1)
CASE_V1_fallback(V1_fallback_rbp_3)
CASE_V1_fallback(V1_fallback_rbp_5)
CASE_V1_fallback(V1_fallback_rbp_7)
CASE_V1_fallback(V1_fallback_rbp_11)
CASE_V1_fallback(V1_fallback_rbp_15)
#define CASE_V1_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,V1); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,V1); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_V1); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_V1); }
CASE_V1_seventh(V1_seventh_rsp_1)
CASE_V1_seventh(V1_seventh_rsp_3)
CASE_V1_seventh(V1_seventh_rsp_5)
CASE_V1_seventh(V1_seventh_rsp_7)
CASE_V1_seventh(V1_seventh_rsp_11)
CASE_V1_seventh(V1_seventh_rsp_15)
CASE_V1_seventh(V1_seventh_rbp_1)
CASE_V1_seventh(V1_seventh_rbp_3)
CASE_V1_seventh(V1_seventh_rbp_5)
CASE_V1_seventh(V1_seventh_rbp_7)
CASE_V1_seventh(V1_seventh_rbp_11)
CASE_V1_seventh(V1_seventh_rbp_15)
#define CASE_V2_alone(S) extern double __vectorcall a_##S(V2); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(V2); \
static double check_a_##S(void) { return a_##S(data_V2); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_V2); }
CASE_V2_alone(V2_alone_rsp_1)
CASE_V2_alone(V2_alone_rsp_3)
CASE_V2_alone(V2_alone_rsp_5)
CASE_V2_alone(V2_alone_rsp_7)
CASE_V2_alone(V2_alone_rsp_11)
CASE_V2_alone(V2_alone_rsp_15)
CASE_V2_alone(V2_alone_rbp_1)
CASE_V2_alone(V2_alone_rbp_3)
CASE_V2_alone(V2_alone_rbp_5)
CASE_V2_alone(V2_alone_rbp_7)
CASE_V2_alone(V2_alone_rbp_11)
CASE_V2_alone(V2_alone_rbp_15)
#define CASE_V2_holes(S) extern double __vectorcall a_##S(V2,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(V2,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_V2,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_V2,11.0,12,13.0,14,15.0); }
CASE_V2_holes(V2_holes_rsp_1)
CASE_V2_holes(V2_holes_rsp_3)
CASE_V2_holes(V2_holes_rsp_5)
CASE_V2_holes(V2_holes_rsp_7)
CASE_V2_holes(V2_holes_rsp_11)
CASE_V2_holes(V2_holes_rsp_15)
CASE_V2_holes(V2_holes_rbp_1)
CASE_V2_holes(V2_holes_rbp_3)
CASE_V2_holes(V2_holes_rbp_5)
CASE_V2_holes(V2_holes_rbp_7)
CASE_V2_holes(V2_holes_rbp_11)
CASE_V2_holes(V2_holes_rbp_15)
#define CASE_V2_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,V2); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,V2); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_V2); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_V2); }
CASE_V2_fallback(V2_fallback_rsp_1)
CASE_V2_fallback(V2_fallback_rsp_3)
CASE_V2_fallback(V2_fallback_rsp_5)
CASE_V2_fallback(V2_fallback_rsp_7)
CASE_V2_fallback(V2_fallback_rsp_11)
CASE_V2_fallback(V2_fallback_rsp_15)
CASE_V2_fallback(V2_fallback_rbp_1)
CASE_V2_fallback(V2_fallback_rbp_3)
CASE_V2_fallback(V2_fallback_rbp_5)
CASE_V2_fallback(V2_fallback_rbp_7)
CASE_V2_fallback(V2_fallback_rbp_11)
CASE_V2_fallback(V2_fallback_rbp_15)
#define CASE_V2_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,V2); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,V2); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_V2); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_V2); }
CASE_V2_seventh(V2_seventh_rsp_1)
CASE_V2_seventh(V2_seventh_rsp_3)
CASE_V2_seventh(V2_seventh_rsp_5)
CASE_V2_seventh(V2_seventh_rsp_7)
CASE_V2_seventh(V2_seventh_rsp_11)
CASE_V2_seventh(V2_seventh_rsp_15)
CASE_V2_seventh(V2_seventh_rbp_1)
CASE_V2_seventh(V2_seventh_rbp_3)
CASE_V2_seventh(V2_seventh_rbp_5)
CASE_V2_seventh(V2_seventh_rbp_7)
CASE_V2_seventh(V2_seventh_rbp_11)
CASE_V2_seventh(V2_seventh_rbp_15)
#define CASE_V3_alone(S) extern double __vectorcall a_##S(V3); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(V3); \
static double check_a_##S(void) { return a_##S(data_V3); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_V3); }
CASE_V3_alone(V3_alone_rsp_1)
CASE_V3_alone(V3_alone_rsp_3)
CASE_V3_alone(V3_alone_rsp_5)
CASE_V3_alone(V3_alone_rsp_7)
CASE_V3_alone(V3_alone_rsp_11)
CASE_V3_alone(V3_alone_rsp_15)
CASE_V3_alone(V3_alone_rbp_1)
CASE_V3_alone(V3_alone_rbp_3)
CASE_V3_alone(V3_alone_rbp_5)
CASE_V3_alone(V3_alone_rbp_7)
CASE_V3_alone(V3_alone_rbp_11)
CASE_V3_alone(V3_alone_rbp_15)
#define CASE_V3_holes(S) extern double __vectorcall a_##S(V3,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(V3,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_V3,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_V3,11.0,12,13.0,14,15.0); }
CASE_V3_holes(V3_holes_rsp_1)
CASE_V3_holes(V3_holes_rsp_3)
CASE_V3_holes(V3_holes_rsp_5)
CASE_V3_holes(V3_holes_rsp_7)
CASE_V3_holes(V3_holes_rsp_11)
CASE_V3_holes(V3_holes_rsp_15)
CASE_V3_holes(V3_holes_rbp_1)
CASE_V3_holes(V3_holes_rbp_3)
CASE_V3_holes(V3_holes_rbp_5)
CASE_V3_holes(V3_holes_rbp_7)
CASE_V3_holes(V3_holes_rbp_11)
CASE_V3_holes(V3_holes_rbp_15)
#define CASE_V3_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,V3); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,V3); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_V3); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_V3); }
CASE_V3_fallback(V3_fallback_rsp_1)
CASE_V3_fallback(V3_fallback_rsp_3)
CASE_V3_fallback(V3_fallback_rsp_5)
CASE_V3_fallback(V3_fallback_rsp_7)
CASE_V3_fallback(V3_fallback_rsp_11)
CASE_V3_fallback(V3_fallback_rsp_15)
CASE_V3_fallback(V3_fallback_rbp_1)
CASE_V3_fallback(V3_fallback_rbp_3)
CASE_V3_fallback(V3_fallback_rbp_5)
CASE_V3_fallback(V3_fallback_rbp_7)
CASE_V3_fallback(V3_fallback_rbp_11)
CASE_V3_fallback(V3_fallback_rbp_15)
#define CASE_V3_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,V3); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,V3); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_V3); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_V3); }
CASE_V3_seventh(V3_seventh_rsp_1)
CASE_V3_seventh(V3_seventh_rsp_3)
CASE_V3_seventh(V3_seventh_rsp_5)
CASE_V3_seventh(V3_seventh_rsp_7)
CASE_V3_seventh(V3_seventh_rsp_11)
CASE_V3_seventh(V3_seventh_rsp_15)
CASE_V3_seventh(V3_seventh_rbp_1)
CASE_V3_seventh(V3_seventh_rbp_3)
CASE_V3_seventh(V3_seventh_rbp_5)
CASE_V3_seventh(V3_seventh_rbp_7)
CASE_V3_seventh(V3_seventh_rbp_11)
CASE_V3_seventh(V3_seventh_rbp_15)
#define CASE_V4_alone(S) extern double __vectorcall a_##S(V4); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(V4); \
static double check_a_##S(void) { return a_##S(data_V4); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_V4); }
CASE_V4_alone(V4_alone_rsp_1)
CASE_V4_alone(V4_alone_rsp_3)
CASE_V4_alone(V4_alone_rsp_5)
CASE_V4_alone(V4_alone_rsp_7)
CASE_V4_alone(V4_alone_rsp_11)
CASE_V4_alone(V4_alone_rsp_15)
CASE_V4_alone(V4_alone_rbp_1)
CASE_V4_alone(V4_alone_rbp_3)
CASE_V4_alone(V4_alone_rbp_5)
CASE_V4_alone(V4_alone_rbp_7)
CASE_V4_alone(V4_alone_rbp_11)
CASE_V4_alone(V4_alone_rbp_15)
#define CASE_V4_holes(S) extern double __vectorcall a_##S(V4,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(V4,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_V4,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_V4,11.0,12,13.0,14,15.0); }
CASE_V4_holes(V4_holes_rsp_1)
CASE_V4_holes(V4_holes_rsp_3)
CASE_V4_holes(V4_holes_rsp_5)
CASE_V4_holes(V4_holes_rsp_7)
CASE_V4_holes(V4_holes_rsp_11)
CASE_V4_holes(V4_holes_rsp_15)
CASE_V4_holes(V4_holes_rbp_1)
CASE_V4_holes(V4_holes_rbp_3)
CASE_V4_holes(V4_holes_rbp_5)
CASE_V4_holes(V4_holes_rbp_7)
CASE_V4_holes(V4_holes_rbp_11)
CASE_V4_holes(V4_holes_rbp_15)
#define CASE_V4_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,V4); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,V4); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_V4); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_V4); }
CASE_V4_fallback(V4_fallback_rsp_1)
CASE_V4_fallback(V4_fallback_rsp_3)
CASE_V4_fallback(V4_fallback_rsp_5)
CASE_V4_fallback(V4_fallback_rsp_7)
CASE_V4_fallback(V4_fallback_rsp_11)
CASE_V4_fallback(V4_fallback_rsp_15)
CASE_V4_fallback(V4_fallback_rbp_1)
CASE_V4_fallback(V4_fallback_rbp_3)
CASE_V4_fallback(V4_fallback_rbp_5)
CASE_V4_fallback(V4_fallback_rbp_7)
CASE_V4_fallback(V4_fallback_rbp_11)
CASE_V4_fallback(V4_fallback_rbp_15)
#define CASE_V4_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,V4); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,V4); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_V4); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_V4); }
CASE_V4_seventh(V4_seventh_rsp_1)
CASE_V4_seventh(V4_seventh_rsp_3)
CASE_V4_seventh(V4_seventh_rsp_5)
CASE_V4_seventh(V4_seventh_rsp_7)
CASE_V4_seventh(V4_seventh_rsp_11)
CASE_V4_seventh(V4_seventh_rsp_15)
CASE_V4_seventh(V4_seventh_rbp_1)
CASE_V4_seventh(V4_seventh_rbp_3)
CASE_V4_seventh(V4_seventh_rbp_5)
CASE_V4_seventh(V4_seventh_rbp_7)
CASE_V4_seventh(V4_seventh_rbp_11)
CASE_V4_seventh(V4_seventh_rbp_15)
#define CASE_Y1_alone(S) extern double __vectorcall a_##S(Y1); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(Y1); \
static double check_a_##S(void) { return a_##S(data_Y1); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_Y1); }
CASE_Y1_alone(Y1_alone_rsp_1)
CASE_Y1_alone(Y1_alone_rsp_3)
CASE_Y1_alone(Y1_alone_rsp_5)
CASE_Y1_alone(Y1_alone_rsp_7)
CASE_Y1_alone(Y1_alone_rsp_11)
CASE_Y1_alone(Y1_alone_rsp_15)
CASE_Y1_alone(Y1_alone_rbp_1)
CASE_Y1_alone(Y1_alone_rbp_3)
CASE_Y1_alone(Y1_alone_rbp_5)
CASE_Y1_alone(Y1_alone_rbp_7)
CASE_Y1_alone(Y1_alone_rbp_11)
CASE_Y1_alone(Y1_alone_rbp_15)
#define CASE_Y1_holes(S) extern double __vectorcall a_##S(Y1,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(Y1,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_Y1,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_Y1,11.0,12,13.0,14,15.0); }
CASE_Y1_holes(Y1_holes_rsp_1)
CASE_Y1_holes(Y1_holes_rsp_3)
CASE_Y1_holes(Y1_holes_rsp_5)
CASE_Y1_holes(Y1_holes_rsp_7)
CASE_Y1_holes(Y1_holes_rsp_11)
CASE_Y1_holes(Y1_holes_rsp_15)
CASE_Y1_holes(Y1_holes_rbp_1)
CASE_Y1_holes(Y1_holes_rbp_3)
CASE_Y1_holes(Y1_holes_rbp_5)
CASE_Y1_holes(Y1_holes_rbp_7)
CASE_Y1_holes(Y1_holes_rbp_11)
CASE_Y1_holes(Y1_holes_rbp_15)
#define CASE_Y1_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,Y1); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,Y1); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_Y1); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_Y1); }
CASE_Y1_fallback(Y1_fallback_rsp_1)
CASE_Y1_fallback(Y1_fallback_rsp_3)
CASE_Y1_fallback(Y1_fallback_rsp_5)
CASE_Y1_fallback(Y1_fallback_rsp_7)
CASE_Y1_fallback(Y1_fallback_rsp_11)
CASE_Y1_fallback(Y1_fallback_rsp_15)
CASE_Y1_fallback(Y1_fallback_rbp_1)
CASE_Y1_fallback(Y1_fallback_rbp_3)
CASE_Y1_fallback(Y1_fallback_rbp_5)
CASE_Y1_fallback(Y1_fallback_rbp_7)
CASE_Y1_fallback(Y1_fallback_rbp_11)
CASE_Y1_fallback(Y1_fallback_rbp_15)
#define CASE_Y1_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,Y1); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,Y1); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_Y1); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_Y1); }
CASE_Y1_seventh(Y1_seventh_rsp_1)
CASE_Y1_seventh(Y1_seventh_rsp_3)
CASE_Y1_seventh(Y1_seventh_rsp_5)
CASE_Y1_seventh(Y1_seventh_rsp_7)
CASE_Y1_seventh(Y1_seventh_rsp_11)
CASE_Y1_seventh(Y1_seventh_rsp_15)
CASE_Y1_seventh(Y1_seventh_rbp_1)
CASE_Y1_seventh(Y1_seventh_rbp_3)
CASE_Y1_seventh(Y1_seventh_rbp_5)
CASE_Y1_seventh(Y1_seventh_rbp_7)
CASE_Y1_seventh(Y1_seventh_rbp_11)
CASE_Y1_seventh(Y1_seventh_rbp_15)
#define CASE_Y2_alone(S) extern double __vectorcall a_##S(Y2); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(Y2); \
static double check_a_##S(void) { return a_##S(data_Y2); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_Y2); }
CASE_Y2_alone(Y2_alone_rsp_1)
CASE_Y2_alone(Y2_alone_rsp_3)
CASE_Y2_alone(Y2_alone_rsp_5)
CASE_Y2_alone(Y2_alone_rsp_7)
CASE_Y2_alone(Y2_alone_rsp_11)
CASE_Y2_alone(Y2_alone_rsp_15)
CASE_Y2_alone(Y2_alone_rbp_1)
CASE_Y2_alone(Y2_alone_rbp_3)
CASE_Y2_alone(Y2_alone_rbp_5)
CASE_Y2_alone(Y2_alone_rbp_7)
CASE_Y2_alone(Y2_alone_rbp_11)
CASE_Y2_alone(Y2_alone_rbp_15)
#define CASE_Y2_holes(S) extern double __vectorcall a_##S(Y2,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(Y2,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_Y2,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_Y2,11.0,12,13.0,14,15.0); }
CASE_Y2_holes(Y2_holes_rsp_1)
CASE_Y2_holes(Y2_holes_rsp_3)
CASE_Y2_holes(Y2_holes_rsp_5)
CASE_Y2_holes(Y2_holes_rsp_7)
CASE_Y2_holes(Y2_holes_rsp_11)
CASE_Y2_holes(Y2_holes_rsp_15)
CASE_Y2_holes(Y2_holes_rbp_1)
CASE_Y2_holes(Y2_holes_rbp_3)
CASE_Y2_holes(Y2_holes_rbp_5)
CASE_Y2_holes(Y2_holes_rbp_7)
CASE_Y2_holes(Y2_holes_rbp_11)
CASE_Y2_holes(Y2_holes_rbp_15)
#define CASE_Y2_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,Y2); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,Y2); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_Y2); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_Y2); }
CASE_Y2_fallback(Y2_fallback_rsp_1)
CASE_Y2_fallback(Y2_fallback_rsp_3)
CASE_Y2_fallback(Y2_fallback_rsp_5)
CASE_Y2_fallback(Y2_fallback_rsp_7)
CASE_Y2_fallback(Y2_fallback_rsp_11)
CASE_Y2_fallback(Y2_fallback_rsp_15)
CASE_Y2_fallback(Y2_fallback_rbp_1)
CASE_Y2_fallback(Y2_fallback_rbp_3)
CASE_Y2_fallback(Y2_fallback_rbp_5)
CASE_Y2_fallback(Y2_fallback_rbp_7)
CASE_Y2_fallback(Y2_fallback_rbp_11)
CASE_Y2_fallback(Y2_fallback_rbp_15)
#define CASE_Y2_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,Y2); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,Y2); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_Y2); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_Y2); }
CASE_Y2_seventh(Y2_seventh_rsp_1)
CASE_Y2_seventh(Y2_seventh_rsp_3)
CASE_Y2_seventh(Y2_seventh_rsp_5)
CASE_Y2_seventh(Y2_seventh_rsp_7)
CASE_Y2_seventh(Y2_seventh_rsp_11)
CASE_Y2_seventh(Y2_seventh_rsp_15)
CASE_Y2_seventh(Y2_seventh_rbp_1)
CASE_Y2_seventh(Y2_seventh_rbp_3)
CASE_Y2_seventh(Y2_seventh_rbp_5)
CASE_Y2_seventh(Y2_seventh_rbp_7)
CASE_Y2_seventh(Y2_seventh_rbp_11)
CASE_Y2_seventh(Y2_seventh_rbp_15)
#define CASE_Y3_alone(S) extern double __vectorcall a_##S(Y3); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(Y3); \
static double check_a_##S(void) { return a_##S(data_Y3); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_Y3); }
CASE_Y3_alone(Y3_alone_rsp_1)
CASE_Y3_alone(Y3_alone_rsp_3)
CASE_Y3_alone(Y3_alone_rsp_5)
CASE_Y3_alone(Y3_alone_rsp_7)
CASE_Y3_alone(Y3_alone_rsp_11)
CASE_Y3_alone(Y3_alone_rsp_15)
CASE_Y3_alone(Y3_alone_rbp_1)
CASE_Y3_alone(Y3_alone_rbp_3)
CASE_Y3_alone(Y3_alone_rbp_5)
CASE_Y3_alone(Y3_alone_rbp_7)
CASE_Y3_alone(Y3_alone_rbp_11)
CASE_Y3_alone(Y3_alone_rbp_15)
#define CASE_Y3_holes(S) extern double __vectorcall a_##S(Y3,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(Y3,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_Y3,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_Y3,11.0,12,13.0,14,15.0); }
CASE_Y3_holes(Y3_holes_rsp_1)
CASE_Y3_holes(Y3_holes_rsp_3)
CASE_Y3_holes(Y3_holes_rsp_5)
CASE_Y3_holes(Y3_holes_rsp_7)
CASE_Y3_holes(Y3_holes_rsp_11)
CASE_Y3_holes(Y3_holes_rsp_15)
CASE_Y3_holes(Y3_holes_rbp_1)
CASE_Y3_holes(Y3_holes_rbp_3)
CASE_Y3_holes(Y3_holes_rbp_5)
CASE_Y3_holes(Y3_holes_rbp_7)
CASE_Y3_holes(Y3_holes_rbp_11)
CASE_Y3_holes(Y3_holes_rbp_15)
#define CASE_Y3_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,Y3); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,Y3); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_Y3); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_Y3); }
CASE_Y3_fallback(Y3_fallback_rsp_1)
CASE_Y3_fallback(Y3_fallback_rsp_3)
CASE_Y3_fallback(Y3_fallback_rsp_5)
CASE_Y3_fallback(Y3_fallback_rsp_7)
CASE_Y3_fallback(Y3_fallback_rsp_11)
CASE_Y3_fallback(Y3_fallback_rsp_15)
CASE_Y3_fallback(Y3_fallback_rbp_1)
CASE_Y3_fallback(Y3_fallback_rbp_3)
CASE_Y3_fallback(Y3_fallback_rbp_5)
CASE_Y3_fallback(Y3_fallback_rbp_7)
CASE_Y3_fallback(Y3_fallback_rbp_11)
CASE_Y3_fallback(Y3_fallback_rbp_15)
#define CASE_Y3_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,Y3); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,Y3); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_Y3); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_Y3); }
CASE_Y3_seventh(Y3_seventh_rsp_1)
CASE_Y3_seventh(Y3_seventh_rsp_3)
CASE_Y3_seventh(Y3_seventh_rsp_5)
CASE_Y3_seventh(Y3_seventh_rsp_7)
CASE_Y3_seventh(Y3_seventh_rsp_11)
CASE_Y3_seventh(Y3_seventh_rsp_15)
CASE_Y3_seventh(Y3_seventh_rbp_1)
CASE_Y3_seventh(Y3_seventh_rbp_3)
CASE_Y3_seventh(Y3_seventh_rbp_5)
CASE_Y3_seventh(Y3_seventh_rbp_7)
CASE_Y3_seventh(Y3_seventh_rbp_11)
CASE_Y3_seventh(Y3_seventh_rbp_15)
#define CASE_Y4_alone(S) extern double __vectorcall a_##S(Y4); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(Y4); \
static double check_a_##S(void) { return a_##S(data_Y4); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_Y4); }
CASE_Y4_alone(Y4_alone_rsp_1)
CASE_Y4_alone(Y4_alone_rsp_3)
CASE_Y4_alone(Y4_alone_rsp_5)
CASE_Y4_alone(Y4_alone_rsp_7)
CASE_Y4_alone(Y4_alone_rsp_11)
CASE_Y4_alone(Y4_alone_rsp_15)
CASE_Y4_alone(Y4_alone_rbp_1)
CASE_Y4_alone(Y4_alone_rbp_3)
CASE_Y4_alone(Y4_alone_rbp_5)
CASE_Y4_alone(Y4_alone_rbp_7)
CASE_Y4_alone(Y4_alone_rbp_11)
CASE_Y4_alone(Y4_alone_rbp_15)
#define CASE_Y4_holes(S) extern double __vectorcall a_##S(Y4,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(Y4,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_Y4,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_Y4,11.0,12,13.0,14,15.0); }
CASE_Y4_holes(Y4_holes_rsp_1)
CASE_Y4_holes(Y4_holes_rsp_3)
CASE_Y4_holes(Y4_holes_rsp_5)
CASE_Y4_holes(Y4_holes_rsp_7)
CASE_Y4_holes(Y4_holes_rsp_11)
CASE_Y4_holes(Y4_holes_rsp_15)
CASE_Y4_holes(Y4_holes_rbp_1)
CASE_Y4_holes(Y4_holes_rbp_3)
CASE_Y4_holes(Y4_holes_rbp_5)
CASE_Y4_holes(Y4_holes_rbp_7)
CASE_Y4_holes(Y4_holes_rbp_11)
CASE_Y4_holes(Y4_holes_rbp_15)
#define CASE_Y4_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,Y4); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,Y4); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_Y4); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_Y4); }
CASE_Y4_fallback(Y4_fallback_rsp_1)
CASE_Y4_fallback(Y4_fallback_rsp_3)
CASE_Y4_fallback(Y4_fallback_rsp_5)
CASE_Y4_fallback(Y4_fallback_rsp_7)
CASE_Y4_fallback(Y4_fallback_rsp_11)
CASE_Y4_fallback(Y4_fallback_rsp_15)
CASE_Y4_fallback(Y4_fallback_rbp_1)
CASE_Y4_fallback(Y4_fallback_rbp_3)
CASE_Y4_fallback(Y4_fallback_rbp_5)
CASE_Y4_fallback(Y4_fallback_rbp_7)
CASE_Y4_fallback(Y4_fallback_rbp_11)
CASE_Y4_fallback(Y4_fallback_rbp_15)
#define CASE_Y4_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,Y4); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,Y4); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_Y4); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_Y4); }
CASE_Y4_seventh(Y4_seventh_rsp_1)
CASE_Y4_seventh(Y4_seventh_rsp_3)
CASE_Y4_seventh(Y4_seventh_rsp_5)
CASE_Y4_seventh(Y4_seventh_rsp_7)
CASE_Y4_seventh(Y4_seventh_rsp_11)
CASE_Y4_seventh(Y4_seventh_rsp_15)
CASE_Y4_seventh(Y4_seventh_rbp_1)
CASE_Y4_seventh(Y4_seventh_rbp_3)
CASE_Y4_seventh(Y4_seventh_rbp_5)
CASE_Y4_seventh(Y4_seventh_rbp_7)
CASE_Y4_seventh(Y4_seventh_rbp_11)
CASE_Y4_seventh(Y4_seventh_rbp_15)
#define CASE_NF_alone(S) extern double __vectorcall a_##S(NF); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(NF); \
static double check_a_##S(void) { return a_##S(data_NF); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_NF); }
CASE_NF_alone(NF_alone_rsp_1)
CASE_NF_alone(NF_alone_rsp_3)
CASE_NF_alone(NF_alone_rsp_5)
CASE_NF_alone(NF_alone_rsp_7)
CASE_NF_alone(NF_alone_rsp_11)
CASE_NF_alone(NF_alone_rsp_15)
CASE_NF_alone(NF_alone_rbp_1)
CASE_NF_alone(NF_alone_rbp_3)
CASE_NF_alone(NF_alone_rbp_5)
CASE_NF_alone(NF_alone_rbp_7)
CASE_NF_alone(NF_alone_rbp_11)
CASE_NF_alone(NF_alone_rbp_15)
#define CASE_NF_holes(S) extern double __vectorcall a_##S(NF,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(NF,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_NF,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_NF,11.0,12,13.0,14,15.0); }
CASE_NF_holes(NF_holes_rsp_1)
CASE_NF_holes(NF_holes_rsp_3)
CASE_NF_holes(NF_holes_rsp_5)
CASE_NF_holes(NF_holes_rsp_7)
CASE_NF_holes(NF_holes_rsp_11)
CASE_NF_holes(NF_holes_rsp_15)
CASE_NF_holes(NF_holes_rbp_1)
CASE_NF_holes(NF_holes_rbp_3)
CASE_NF_holes(NF_holes_rbp_5)
CASE_NF_holes(NF_holes_rbp_7)
CASE_NF_holes(NF_holes_rbp_11)
CASE_NF_holes(NF_holes_rbp_15)
#define CASE_NF_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,NF); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,NF); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_NF); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_NF); }
CASE_NF_fallback(NF_fallback_rsp_1)
CASE_NF_fallback(NF_fallback_rsp_3)
CASE_NF_fallback(NF_fallback_rsp_5)
CASE_NF_fallback(NF_fallback_rsp_7)
CASE_NF_fallback(NF_fallback_rsp_11)
CASE_NF_fallback(NF_fallback_rsp_15)
CASE_NF_fallback(NF_fallback_rbp_1)
CASE_NF_fallback(NF_fallback_rbp_3)
CASE_NF_fallback(NF_fallback_rbp_5)
CASE_NF_fallback(NF_fallback_rbp_7)
CASE_NF_fallback(NF_fallback_rbp_11)
CASE_NF_fallback(NF_fallback_rbp_15)
#define CASE_NF_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,NF); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,NF); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_NF); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_NF); }
CASE_NF_seventh(NF_seventh_rsp_1)
CASE_NF_seventh(NF_seventh_rsp_3)
CASE_NF_seventh(NF_seventh_rsp_5)
CASE_NF_seventh(NF_seventh_rsp_7)
CASE_NF_seventh(NF_seventh_rsp_11)
CASE_NF_seventh(NF_seventh_rsp_15)
CASE_NF_seventh(NF_seventh_rbp_1)
CASE_NF_seventh(NF_seventh_rbp_3)
CASE_NF_seventh(NF_seventh_rbp_5)
CASE_NF_seventh(NF_seventh_rbp_7)
CASE_NF_seventh(NF_seventh_rbp_11)
CASE_NF_seventh(NF_seventh_rbp_15)
#define CASE_AF_alone(S) extern double __vectorcall a_##S(AF); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(AF); \
static double check_a_##S(void) { return a_##S(data_AF); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_AF); }
CASE_AF_alone(AF_alone_rsp_1)
CASE_AF_alone(AF_alone_rsp_3)
CASE_AF_alone(AF_alone_rsp_5)
CASE_AF_alone(AF_alone_rsp_7)
CASE_AF_alone(AF_alone_rsp_11)
CASE_AF_alone(AF_alone_rsp_15)
CASE_AF_alone(AF_alone_rbp_1)
CASE_AF_alone(AF_alone_rbp_3)
CASE_AF_alone(AF_alone_rbp_5)
CASE_AF_alone(AF_alone_rbp_7)
CASE_AF_alone(AF_alone_rbp_11)
CASE_AF_alone(AF_alone_rbp_15)
#define CASE_AF_holes(S) extern double __vectorcall a_##S(AF,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(AF,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_AF,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_AF,11.0,12,13.0,14,15.0); }
CASE_AF_holes(AF_holes_rsp_1)
CASE_AF_holes(AF_holes_rsp_3)
CASE_AF_holes(AF_holes_rsp_5)
CASE_AF_holes(AF_holes_rsp_7)
CASE_AF_holes(AF_holes_rsp_11)
CASE_AF_holes(AF_holes_rsp_15)
CASE_AF_holes(AF_holes_rbp_1)
CASE_AF_holes(AF_holes_rbp_3)
CASE_AF_holes(AF_holes_rbp_5)
CASE_AF_holes(AF_holes_rbp_7)
CASE_AF_holes(AF_holes_rbp_11)
CASE_AF_holes(AF_holes_rbp_15)
#define CASE_AF_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,AF); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,AF); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_AF); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_AF); }
CASE_AF_fallback(AF_fallback_rsp_1)
CASE_AF_fallback(AF_fallback_rsp_3)
CASE_AF_fallback(AF_fallback_rsp_5)
CASE_AF_fallback(AF_fallback_rsp_7)
CASE_AF_fallback(AF_fallback_rsp_11)
CASE_AF_fallback(AF_fallback_rsp_15)
CASE_AF_fallback(AF_fallback_rbp_1)
CASE_AF_fallback(AF_fallback_rbp_3)
CASE_AF_fallback(AF_fallback_rbp_5)
CASE_AF_fallback(AF_fallback_rbp_7)
CASE_AF_fallback(AF_fallback_rbp_11)
CASE_AF_fallback(AF_fallback_rbp_15)
#define CASE_AF_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,AF); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,AF); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_AF); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_AF); }
CASE_AF_seventh(AF_seventh_rsp_1)
CASE_AF_seventh(AF_seventh_rsp_3)
CASE_AF_seventh(AF_seventh_rsp_5)
CASE_AF_seventh(AF_seventh_rsp_7)
CASE_AF_seventh(AF_seventh_rsp_11)
CASE_AF_seventh(AF_seventh_rsp_15)
CASE_AF_seventh(AF_seventh_rbp_1)
CASE_AF_seventh(AF_seventh_rbp_3)
CASE_AF_seventh(AF_seventh_rbp_5)
CASE_AF_seventh(AF_seventh_rbp_7)
CASE_AF_seventh(AF_seventh_rbp_11)
CASE_AF_seventh(AF_seventh_rbp_15)
#define CASE_Mixed_alone(S) extern double __vectorcall a_##S(Mixed); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(Mixed); \
static double check_a_##S(void) { return a_##S(data_Mixed); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_Mixed); }
CASE_Mixed_alone(Mixed_alone_rsp_1)
CASE_Mixed_alone(Mixed_alone_rsp_3)
CASE_Mixed_alone(Mixed_alone_rsp_5)
CASE_Mixed_alone(Mixed_alone_rsp_7)
CASE_Mixed_alone(Mixed_alone_rsp_11)
CASE_Mixed_alone(Mixed_alone_rsp_15)
CASE_Mixed_alone(Mixed_alone_rbp_1)
CASE_Mixed_alone(Mixed_alone_rbp_3)
CASE_Mixed_alone(Mixed_alone_rbp_5)
CASE_Mixed_alone(Mixed_alone_rbp_7)
CASE_Mixed_alone(Mixed_alone_rbp_11)
CASE_Mixed_alone(Mixed_alone_rbp_15)
#define CASE_Mixed_holes(S) extern double __vectorcall a_##S(Mixed,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(Mixed,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_Mixed,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_Mixed,11.0,12,13.0,14,15.0); }
CASE_Mixed_holes(Mixed_holes_rsp_1)
CASE_Mixed_holes(Mixed_holes_rsp_3)
CASE_Mixed_holes(Mixed_holes_rsp_5)
CASE_Mixed_holes(Mixed_holes_rsp_7)
CASE_Mixed_holes(Mixed_holes_rsp_11)
CASE_Mixed_holes(Mixed_holes_rsp_15)
CASE_Mixed_holes(Mixed_holes_rbp_1)
CASE_Mixed_holes(Mixed_holes_rbp_3)
CASE_Mixed_holes(Mixed_holes_rbp_5)
CASE_Mixed_holes(Mixed_holes_rbp_7)
CASE_Mixed_holes(Mixed_holes_rbp_11)
CASE_Mixed_holes(Mixed_holes_rbp_15)
#define CASE_Mixed_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,Mixed); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,Mixed); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_Mixed); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_Mixed); }
CASE_Mixed_fallback(Mixed_fallback_rsp_1)
CASE_Mixed_fallback(Mixed_fallback_rsp_3)
CASE_Mixed_fallback(Mixed_fallback_rsp_5)
CASE_Mixed_fallback(Mixed_fallback_rsp_7)
CASE_Mixed_fallback(Mixed_fallback_rsp_11)
CASE_Mixed_fallback(Mixed_fallback_rsp_15)
CASE_Mixed_fallback(Mixed_fallback_rbp_1)
CASE_Mixed_fallback(Mixed_fallback_rbp_3)
CASE_Mixed_fallback(Mixed_fallback_rbp_5)
CASE_Mixed_fallback(Mixed_fallback_rbp_7)
CASE_Mixed_fallback(Mixed_fallback_rbp_11)
CASE_Mixed_fallback(Mixed_fallback_rbp_15)
#define CASE_Mixed_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,Mixed); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,Mixed); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_Mixed); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_Mixed); }
CASE_Mixed_seventh(Mixed_seventh_rsp_1)
CASE_Mixed_seventh(Mixed_seventh_rsp_3)
CASE_Mixed_seventh(Mixed_seventh_rsp_5)
CASE_Mixed_seventh(Mixed_seventh_rsp_7)
CASE_Mixed_seventh(Mixed_seventh_rsp_11)
CASE_Mixed_seventh(Mixed_seventh_rsp_15)
CASE_Mixed_seventh(Mixed_seventh_rbp_1)
CASE_Mixed_seventh(Mixed_seventh_rbp_3)
CASE_Mixed_seventh(Mixed_seventh_rbp_5)
CASE_Mixed_seventh(Mixed_seventh_rbp_7)
CASE_Mixed_seventh(Mixed_seventh_rbp_11)
CASE_Mixed_seventh(Mixed_seventh_rbp_15)
#define CASE_Ints_alone(S) extern double __vectorcall a_##S(Ints); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(Ints); \
static double check_a_##S(void) { return a_##S(data_Ints); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_Ints); }
CASE_Ints_alone(Ints_alone_rsp_1)
CASE_Ints_alone(Ints_alone_rsp_3)
CASE_Ints_alone(Ints_alone_rsp_5)
CASE_Ints_alone(Ints_alone_rsp_7)
CASE_Ints_alone(Ints_alone_rsp_11)
CASE_Ints_alone(Ints_alone_rsp_15)
CASE_Ints_alone(Ints_alone_rbp_1)
CASE_Ints_alone(Ints_alone_rbp_3)
CASE_Ints_alone(Ints_alone_rbp_5)
CASE_Ints_alone(Ints_alone_rbp_7)
CASE_Ints_alone(Ints_alone_rbp_11)
CASE_Ints_alone(Ints_alone_rbp_15)
#define CASE_Ints_holes(S) extern double __vectorcall a_##S(Ints,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(Ints,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data_Ints,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data_Ints,11.0,12,13.0,14,15.0); }
CASE_Ints_holes(Ints_holes_rsp_1)
CASE_Ints_holes(Ints_holes_rsp_3)
CASE_Ints_holes(Ints_holes_rsp_5)
CASE_Ints_holes(Ints_holes_rsp_7)
CASE_Ints_holes(Ints_holes_rsp_11)
CASE_Ints_holes(Ints_holes_rsp_15)
CASE_Ints_holes(Ints_holes_rbp_1)
CASE_Ints_holes(Ints_holes_rbp_3)
CASE_Ints_holes(Ints_holes_rbp_5)
CASE_Ints_holes(Ints_holes_rbp_7)
CASE_Ints_holes(Ints_holes_rbp_11)
CASE_Ints_holes(Ints_holes_rbp_15)
#define CASE_Ints_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,Ints); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,Ints); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_Ints); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data_Ints); }
CASE_Ints_fallback(Ints_fallback_rsp_1)
CASE_Ints_fallback(Ints_fallback_rsp_3)
CASE_Ints_fallback(Ints_fallback_rsp_5)
CASE_Ints_fallback(Ints_fallback_rsp_7)
CASE_Ints_fallback(Ints_fallback_rsp_11)
CASE_Ints_fallback(Ints_fallback_rsp_15)
CASE_Ints_fallback(Ints_fallback_rbp_1)
CASE_Ints_fallback(Ints_fallback_rbp_3)
CASE_Ints_fallback(Ints_fallback_rbp_5)
CASE_Ints_fallback(Ints_fallback_rbp_7)
CASE_Ints_fallback(Ints_fallback_rbp_11)
CASE_Ints_fallback(Ints_fallback_rbp_15)
#define CASE_Ints_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,Ints); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,Ints); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data_Ints); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data_Ints); }
CASE_Ints_seventh(Ints_seventh_rsp_1)
CASE_Ints_seventh(Ints_seventh_rsp_3)
CASE_Ints_seventh(Ints_seventh_rsp_5)
CASE_Ints_seventh(Ints_seventh_rsp_7)
CASE_Ints_seventh(Ints_seventh_rsp_11)
CASE_Ints_seventh(Ints_seventh_rsp_15)
CASE_Ints_seventh(Ints_seventh_rbp_1)
CASE_Ints_seventh(Ints_seventh_rbp_3)
CASE_Ints_seventh(Ints_seventh_rbp_5)
CASE_Ints_seventh(Ints_seventh_rbp_7)
CASE_Ints_seventh(Ints_seventh_rbp_11)
CASE_Ints_seventh(Ints_seventh_rbp_15)
#define CASE___m128f_alone(S) extern double __vectorcall a_##S(__m128f); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(__m128f); \
static double check_a_##S(void) { return a_##S(data___m128f); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data___m128f); }
CASE___m128f_alone(__m128f_alone_rsp_1)
CASE___m128f_alone(__m128f_alone_rsp_3)
CASE___m128f_alone(__m128f_alone_rsp_5)
CASE___m128f_alone(__m128f_alone_rsp_7)
CASE___m128f_alone(__m128f_alone_rsp_11)
CASE___m128f_alone(__m128f_alone_rsp_15)
CASE___m128f_alone(__m128f_alone_rbp_1)
CASE___m128f_alone(__m128f_alone_rbp_3)
CASE___m128f_alone(__m128f_alone_rbp_5)
CASE___m128f_alone(__m128f_alone_rbp_7)
CASE___m128f_alone(__m128f_alone_rbp_11)
CASE___m128f_alone(__m128f_alone_rbp_15)
#define CASE___m128f_holes(S) extern double __vectorcall a_##S(__m128f,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(__m128f,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data___m128f,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data___m128f,11.0,12,13.0,14,15.0); }
CASE___m128f_holes(__m128f_holes_rsp_1)
CASE___m128f_holes(__m128f_holes_rsp_3)
CASE___m128f_holes(__m128f_holes_rsp_5)
CASE___m128f_holes(__m128f_holes_rsp_7)
CASE___m128f_holes(__m128f_holes_rsp_11)
CASE___m128f_holes(__m128f_holes_rsp_15)
CASE___m128f_holes(__m128f_holes_rbp_1)
CASE___m128f_holes(__m128f_holes_rbp_3)
CASE___m128f_holes(__m128f_holes_rbp_5)
CASE___m128f_holes(__m128f_holes_rbp_7)
CASE___m128f_holes(__m128f_holes_rbp_11)
CASE___m128f_holes(__m128f_holes_rbp_15)
#define CASE___m128f_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,__m128f); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,__m128f); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data___m128f); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data___m128f); }
CASE___m128f_fallback(__m128f_fallback_rsp_1)
CASE___m128f_fallback(__m128f_fallback_rsp_3)
CASE___m128f_fallback(__m128f_fallback_rsp_5)
CASE___m128f_fallback(__m128f_fallback_rsp_7)
CASE___m128f_fallback(__m128f_fallback_rsp_11)
CASE___m128f_fallback(__m128f_fallback_rsp_15)
CASE___m128f_fallback(__m128f_fallback_rbp_1)
CASE___m128f_fallback(__m128f_fallback_rbp_3)
CASE___m128f_fallback(__m128f_fallback_rbp_5)
CASE___m128f_fallback(__m128f_fallback_rbp_7)
CASE___m128f_fallback(__m128f_fallback_rbp_11)
CASE___m128f_fallback(__m128f_fallback_rbp_15)
#define CASE___m128f_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,__m128f); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,__m128f); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data___m128f); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data___m128f); }
CASE___m128f_seventh(__m128f_seventh_rsp_1)
CASE___m128f_seventh(__m128f_seventh_rsp_3)
CASE___m128f_seventh(__m128f_seventh_rsp_5)
CASE___m128f_seventh(__m128f_seventh_rsp_7)
CASE___m128f_seventh(__m128f_seventh_rsp_11)
CASE___m128f_seventh(__m128f_seventh_rsp_15)
CASE___m128f_seventh(__m128f_seventh_rbp_1)
CASE___m128f_seventh(__m128f_seventh_rbp_3)
CASE___m128f_seventh(__m128f_seventh_rbp_5)
CASE___m128f_seventh(__m128f_seventh_rbp_7)
CASE___m128f_seventh(__m128f_seventh_rbp_11)
CASE___m128f_seventh(__m128f_seventh_rbp_15)
#define CASE___m256f_alone(S) extern double __vectorcall a_##S(__m256f); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(__m256f); \
static double check_a_##S(void) { return a_##S(data___m256f); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data___m256f); }
CASE___m256f_alone(__m256f_alone_rsp_1)
CASE___m256f_alone(__m256f_alone_rsp_3)
CASE___m256f_alone(__m256f_alone_rsp_5)
CASE___m256f_alone(__m256f_alone_rsp_7)
CASE___m256f_alone(__m256f_alone_rsp_11)
CASE___m256f_alone(__m256f_alone_rsp_15)
CASE___m256f_alone(__m256f_alone_rbp_1)
CASE___m256f_alone(__m256f_alone_rbp_3)
CASE___m256f_alone(__m256f_alone_rbp_5)
CASE___m256f_alone(__m256f_alone_rbp_7)
CASE___m256f_alone(__m256f_alone_rbp_11)
CASE___m256f_alone(__m256f_alone_rbp_15)
#define CASE___m256f_holes(S) extern double __vectorcall a_##S(__m256f,float,long long,double,long long,float); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(__m256f,float,long long,double,long long,float); \
static double check_a_##S(void) { return a_##S(data___m256f,11.0,12,13.0,14,15.0); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(data___m256f,11.0,12,13.0,14,15.0); }
CASE___m256f_holes(__m256f_holes_rsp_1)
CASE___m256f_holes(__m256f_holes_rsp_3)
CASE___m256f_holes(__m256f_holes_rsp_5)
CASE___m256f_holes(__m256f_holes_rsp_7)
CASE___m256f_holes(__m256f_holes_rsp_11)
CASE___m256f_holes(__m256f_holes_rsp_15)
CASE___m256f_holes(__m256f_holes_rbp_1)
CASE___m256f_holes(__m256f_holes_rbp_3)
CASE___m256f_holes(__m256f_holes_rbp_5)
CASE___m256f_holes(__m256f_holes_rbp_7)
CASE___m256f_holes(__m256f_holes_rbp_11)
CASE___m256f_holes(__m256f_holes_rbp_15)
#define CASE___m256f_fallback(S) extern double __vectorcall a_##S(double,double,double,double,double,double,__m256f); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(double,double,double,double,double,double,__m256f); \
static double check_a_##S(void) { return a_##S(1.0,2.0,3.0,4.0,5.0,6.0,data___m256f); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1.0,2.0,3.0,4.0,5.0,6.0,data___m256f); }
CASE___m256f_fallback(__m256f_fallback_rsp_1)
CASE___m256f_fallback(__m256f_fallback_rsp_3)
CASE___m256f_fallback(__m256f_fallback_rsp_5)
CASE___m256f_fallback(__m256f_fallback_rsp_7)
CASE___m256f_fallback(__m256f_fallback_rsp_11)
CASE___m256f_fallback(__m256f_fallback_rsp_15)
CASE___m256f_fallback(__m256f_fallback_rbp_1)
CASE___m256f_fallback(__m256f_fallback_rbp_3)
CASE___m256f_fallback(__m256f_fallback_rbp_5)
CASE___m256f_fallback(__m256f_fallback_rbp_7)
CASE___m256f_fallback(__m256f_fallback_rbp_11)
CASE___m256f_fallback(__m256f_fallback_rbp_15)
#define CASE___m256f_seventh(S) extern double __vectorcall a_##S(long long,long long,long long,long long,long long,long long,__m256f); \
extern double call_##S(void); \
extern double __vectorcall forward_##S(long long,long long,long long,long long,long long,long long,__m256f); \
static double check_a_##S(void) { return a_##S(1,2,3,4,5,6,data___m256f); } \
static double check_call_##S(void) { return call_##S(); } \
static double check_forward_##S(void) { return forward_##S(1,2,3,4,5,6,data___m256f); }
CASE___m256f_seventh(__m256f_seventh_rsp_1)
CASE___m256f_seventh(__m256f_seventh_rsp_3)
CASE___m256f_seventh(__m256f_seventh_rsp_5)
CASE___m256f_seventh(__m256f_seventh_rsp_7)
CASE___m256f_seventh(__m256f_seventh_rsp_11)
CASE___m256f_seventh(__m256f_seventh_rsp_15)
CASE___m256f_seventh(__m256f_seventh_rbp_1)
CASE___m256f_seventh(__m256f_seventh_rbp_3)
CASE___m256f_seventh(__m256f_seventh_rbp_5)
CASE___m256f_seventh(__m256f_seventh_rbp_7)
CASE___m256f_seventh(__m256f_seventh_rbp_11)
CASE___m256f_seventh(__m256f_seventh_rbp_15)
typedef double (*checkfn)(void);
struct testcase {checkfn fn;const char *name;double expected;};
#define ENTRY(S,E) {check_a_##S,"a_" #S,E},{check_call_##S,"call_" #S,E},{check_forward_##S,"forward_" #S,E},
static const struct testcase tests[] = {
ENTRY(F1_alone_rsp_1,1)
ENTRY(F1_alone_rsp_3,1)
ENTRY(F1_alone_rsp_5,1)
ENTRY(F1_alone_rsp_7,1)
ENTRY(F1_alone_rsp_11,1)
ENTRY(F1_alone_rsp_15,1)
ENTRY(F1_alone_rbp_1,1)
ENTRY(F1_alone_rbp_3,1)
ENTRY(F1_alone_rbp_5,1)
ENTRY(F1_alone_rbp_7,1)
ENTRY(F1_alone_rbp_11,1)
ENTRY(F1_alone_rbp_15,1)
ENTRY(F1_holes_rsp_1,66)
ENTRY(F1_holes_rsp_3,66)
ENTRY(F1_holes_rsp_5,66)
ENTRY(F1_holes_rsp_7,66)
ENTRY(F1_holes_rsp_11,66)
ENTRY(F1_holes_rsp_15,66)
ENTRY(F1_holes_rbp_1,66)
ENTRY(F1_holes_rbp_3,66)
ENTRY(F1_holes_rbp_5,66)
ENTRY(F1_holes_rbp_7,66)
ENTRY(F1_holes_rbp_11,66)
ENTRY(F1_holes_rbp_15,66)
ENTRY(F1_fallback_rsp_1,22)
ENTRY(F1_fallback_rsp_3,22)
ENTRY(F1_fallback_rsp_5,22)
ENTRY(F1_fallback_rsp_7,22)
ENTRY(F1_fallback_rsp_11,22)
ENTRY(F1_fallback_rsp_15,22)
ENTRY(F1_fallback_rbp_1,22)
ENTRY(F1_fallback_rbp_3,22)
ENTRY(F1_fallback_rbp_5,22)
ENTRY(F1_fallback_rbp_7,22)
ENTRY(F1_fallback_rbp_11,22)
ENTRY(F1_fallback_rbp_15,22)
ENTRY(F1_seventh_rsp_1,22)
ENTRY(F1_seventh_rsp_3,22)
ENTRY(F1_seventh_rsp_5,22)
ENTRY(F1_seventh_rsp_7,22)
ENTRY(F1_seventh_rsp_11,22)
ENTRY(F1_seventh_rsp_15,22)
ENTRY(F1_seventh_rbp_1,22)
ENTRY(F1_seventh_rbp_3,22)
ENTRY(F1_seventh_rbp_5,22)
ENTRY(F1_seventh_rbp_7,22)
ENTRY(F1_seventh_rbp_11,22)
ENTRY(F1_seventh_rbp_15,22)
ENTRY(F2_alone_rsp_1,3)
ENTRY(F2_alone_rsp_3,3)
ENTRY(F2_alone_rsp_5,3)
ENTRY(F2_alone_rsp_7,3)
ENTRY(F2_alone_rsp_11,3)
ENTRY(F2_alone_rsp_15,3)
ENTRY(F2_alone_rbp_1,3)
ENTRY(F2_alone_rbp_3,3)
ENTRY(F2_alone_rbp_5,3)
ENTRY(F2_alone_rbp_7,3)
ENTRY(F2_alone_rbp_11,3)
ENTRY(F2_alone_rbp_15,3)
ENTRY(F2_holes_rsp_1,68)
ENTRY(F2_holes_rsp_3,68)
ENTRY(F2_holes_rsp_5,68)
ENTRY(F2_holes_rsp_7,68)
ENTRY(F2_holes_rsp_11,68)
ENTRY(F2_holes_rsp_15,68)
ENTRY(F2_holes_rbp_1,68)
ENTRY(F2_holes_rbp_3,68)
ENTRY(F2_holes_rbp_5,68)
ENTRY(F2_holes_rbp_7,68)
ENTRY(F2_holes_rbp_11,68)
ENTRY(F2_holes_rbp_15,68)
ENTRY(F2_fallback_rsp_1,24)
ENTRY(F2_fallback_rsp_3,24)
ENTRY(F2_fallback_rsp_5,24)
ENTRY(F2_fallback_rsp_7,24)
ENTRY(F2_fallback_rsp_11,24)
ENTRY(F2_fallback_rsp_15,24)
ENTRY(F2_fallback_rbp_1,24)
ENTRY(F2_fallback_rbp_3,24)
ENTRY(F2_fallback_rbp_5,24)
ENTRY(F2_fallback_rbp_7,24)
ENTRY(F2_fallback_rbp_11,24)
ENTRY(F2_fallback_rbp_15,24)
ENTRY(F2_seventh_rsp_1,24)
ENTRY(F2_seventh_rsp_3,24)
ENTRY(F2_seventh_rsp_5,24)
ENTRY(F2_seventh_rsp_7,24)
ENTRY(F2_seventh_rsp_11,24)
ENTRY(F2_seventh_rsp_15,24)
ENTRY(F2_seventh_rbp_1,24)
ENTRY(F2_seventh_rbp_3,24)
ENTRY(F2_seventh_rbp_5,24)
ENTRY(F2_seventh_rbp_7,24)
ENTRY(F2_seventh_rbp_11,24)
ENTRY(F2_seventh_rbp_15,24)
ENTRY(F3_alone_rsp_1,6)
ENTRY(F3_alone_rsp_3,6)
ENTRY(F3_alone_rsp_5,6)
ENTRY(F3_alone_rsp_7,6)
ENTRY(F3_alone_rsp_11,6)
ENTRY(F3_alone_rsp_15,6)
ENTRY(F3_alone_rbp_1,6)
ENTRY(F3_alone_rbp_3,6)
ENTRY(F3_alone_rbp_5,6)
ENTRY(F3_alone_rbp_7,6)
ENTRY(F3_alone_rbp_11,6)
ENTRY(F3_alone_rbp_15,6)
ENTRY(F3_holes_rsp_1,71)
ENTRY(F3_holes_rsp_3,71)
ENTRY(F3_holes_rsp_5,71)
ENTRY(F3_holes_rsp_7,71)
ENTRY(F3_holes_rsp_11,71)
ENTRY(F3_holes_rsp_15,71)
ENTRY(F3_holes_rbp_1,71)
ENTRY(F3_holes_rbp_3,71)
ENTRY(F3_holes_rbp_5,71)
ENTRY(F3_holes_rbp_7,71)
ENTRY(F3_holes_rbp_11,71)
ENTRY(F3_holes_rbp_15,71)
ENTRY(F3_fallback_rsp_1,27)
ENTRY(F3_fallback_rsp_3,27)
ENTRY(F3_fallback_rsp_5,27)
ENTRY(F3_fallback_rsp_7,27)
ENTRY(F3_fallback_rsp_11,27)
ENTRY(F3_fallback_rsp_15,27)
ENTRY(F3_fallback_rbp_1,27)
ENTRY(F3_fallback_rbp_3,27)
ENTRY(F3_fallback_rbp_5,27)
ENTRY(F3_fallback_rbp_7,27)
ENTRY(F3_fallback_rbp_11,27)
ENTRY(F3_fallback_rbp_15,27)
ENTRY(F3_seventh_rsp_1,27)
ENTRY(F3_seventh_rsp_3,27)
ENTRY(F3_seventh_rsp_5,27)
ENTRY(F3_seventh_rsp_7,27)
ENTRY(F3_seventh_rsp_11,27)
ENTRY(F3_seventh_rsp_15,27)
ENTRY(F3_seventh_rbp_1,27)
ENTRY(F3_seventh_rbp_3,27)
ENTRY(F3_seventh_rbp_5,27)
ENTRY(F3_seventh_rbp_7,27)
ENTRY(F3_seventh_rbp_11,27)
ENTRY(F3_seventh_rbp_15,27)
ENTRY(F4_alone_rsp_1,10)
ENTRY(F4_alone_rsp_3,10)
ENTRY(F4_alone_rsp_5,10)
ENTRY(F4_alone_rsp_7,10)
ENTRY(F4_alone_rsp_11,10)
ENTRY(F4_alone_rsp_15,10)
ENTRY(F4_alone_rbp_1,10)
ENTRY(F4_alone_rbp_3,10)
ENTRY(F4_alone_rbp_5,10)
ENTRY(F4_alone_rbp_7,10)
ENTRY(F4_alone_rbp_11,10)
ENTRY(F4_alone_rbp_15,10)
ENTRY(F4_holes_rsp_1,75)
ENTRY(F4_holes_rsp_3,75)
ENTRY(F4_holes_rsp_5,75)
ENTRY(F4_holes_rsp_7,75)
ENTRY(F4_holes_rsp_11,75)
ENTRY(F4_holes_rsp_15,75)
ENTRY(F4_holes_rbp_1,75)
ENTRY(F4_holes_rbp_3,75)
ENTRY(F4_holes_rbp_5,75)
ENTRY(F4_holes_rbp_7,75)
ENTRY(F4_holes_rbp_11,75)
ENTRY(F4_holes_rbp_15,75)
ENTRY(F4_fallback_rsp_1,31)
ENTRY(F4_fallback_rsp_3,31)
ENTRY(F4_fallback_rsp_5,31)
ENTRY(F4_fallback_rsp_7,31)
ENTRY(F4_fallback_rsp_11,31)
ENTRY(F4_fallback_rsp_15,31)
ENTRY(F4_fallback_rbp_1,31)
ENTRY(F4_fallback_rbp_3,31)
ENTRY(F4_fallback_rbp_5,31)
ENTRY(F4_fallback_rbp_7,31)
ENTRY(F4_fallback_rbp_11,31)
ENTRY(F4_fallback_rbp_15,31)
ENTRY(F4_seventh_rsp_1,31)
ENTRY(F4_seventh_rsp_3,31)
ENTRY(F4_seventh_rsp_5,31)
ENTRY(F4_seventh_rsp_7,31)
ENTRY(F4_seventh_rsp_11,31)
ENTRY(F4_seventh_rsp_15,31)
ENTRY(F4_seventh_rbp_1,31)
ENTRY(F4_seventh_rbp_3,31)
ENTRY(F4_seventh_rbp_5,31)
ENTRY(F4_seventh_rbp_7,31)
ENTRY(F4_seventh_rbp_11,31)
ENTRY(F4_seventh_rbp_15,31)
ENTRY(D1_alone_rsp_1,1)
ENTRY(D1_alone_rsp_3,1)
ENTRY(D1_alone_rsp_5,1)
ENTRY(D1_alone_rsp_7,1)
ENTRY(D1_alone_rsp_11,1)
ENTRY(D1_alone_rsp_15,1)
ENTRY(D1_alone_rbp_1,1)
ENTRY(D1_alone_rbp_3,1)
ENTRY(D1_alone_rbp_5,1)
ENTRY(D1_alone_rbp_7,1)
ENTRY(D1_alone_rbp_11,1)
ENTRY(D1_alone_rbp_15,1)
ENTRY(D1_holes_rsp_1,66)
ENTRY(D1_holes_rsp_3,66)
ENTRY(D1_holes_rsp_5,66)
ENTRY(D1_holes_rsp_7,66)
ENTRY(D1_holes_rsp_11,66)
ENTRY(D1_holes_rsp_15,66)
ENTRY(D1_holes_rbp_1,66)
ENTRY(D1_holes_rbp_3,66)
ENTRY(D1_holes_rbp_5,66)
ENTRY(D1_holes_rbp_7,66)
ENTRY(D1_holes_rbp_11,66)
ENTRY(D1_holes_rbp_15,66)
ENTRY(D1_fallback_rsp_1,22)
ENTRY(D1_fallback_rsp_3,22)
ENTRY(D1_fallback_rsp_5,22)
ENTRY(D1_fallback_rsp_7,22)
ENTRY(D1_fallback_rsp_11,22)
ENTRY(D1_fallback_rsp_15,22)
ENTRY(D1_fallback_rbp_1,22)
ENTRY(D1_fallback_rbp_3,22)
ENTRY(D1_fallback_rbp_5,22)
ENTRY(D1_fallback_rbp_7,22)
ENTRY(D1_fallback_rbp_11,22)
ENTRY(D1_fallback_rbp_15,22)
ENTRY(D1_seventh_rsp_1,22)
ENTRY(D1_seventh_rsp_3,22)
ENTRY(D1_seventh_rsp_5,22)
ENTRY(D1_seventh_rsp_7,22)
ENTRY(D1_seventh_rsp_11,22)
ENTRY(D1_seventh_rsp_15,22)
ENTRY(D1_seventh_rbp_1,22)
ENTRY(D1_seventh_rbp_3,22)
ENTRY(D1_seventh_rbp_5,22)
ENTRY(D1_seventh_rbp_7,22)
ENTRY(D1_seventh_rbp_11,22)
ENTRY(D1_seventh_rbp_15,22)
ENTRY(D2_alone_rsp_1,3)
ENTRY(D2_alone_rsp_3,3)
ENTRY(D2_alone_rsp_5,3)
ENTRY(D2_alone_rsp_7,3)
ENTRY(D2_alone_rsp_11,3)
ENTRY(D2_alone_rsp_15,3)
ENTRY(D2_alone_rbp_1,3)
ENTRY(D2_alone_rbp_3,3)
ENTRY(D2_alone_rbp_5,3)
ENTRY(D2_alone_rbp_7,3)
ENTRY(D2_alone_rbp_11,3)
ENTRY(D2_alone_rbp_15,3)
ENTRY(D2_holes_rsp_1,68)
ENTRY(D2_holes_rsp_3,68)
ENTRY(D2_holes_rsp_5,68)
ENTRY(D2_holes_rsp_7,68)
ENTRY(D2_holes_rsp_11,68)
ENTRY(D2_holes_rsp_15,68)
ENTRY(D2_holes_rbp_1,68)
ENTRY(D2_holes_rbp_3,68)
ENTRY(D2_holes_rbp_5,68)
ENTRY(D2_holes_rbp_7,68)
ENTRY(D2_holes_rbp_11,68)
ENTRY(D2_holes_rbp_15,68)
ENTRY(D2_fallback_rsp_1,24)
ENTRY(D2_fallback_rsp_3,24)
ENTRY(D2_fallback_rsp_5,24)
ENTRY(D2_fallback_rsp_7,24)
ENTRY(D2_fallback_rsp_11,24)
ENTRY(D2_fallback_rsp_15,24)
ENTRY(D2_fallback_rbp_1,24)
ENTRY(D2_fallback_rbp_3,24)
ENTRY(D2_fallback_rbp_5,24)
ENTRY(D2_fallback_rbp_7,24)
ENTRY(D2_fallback_rbp_11,24)
ENTRY(D2_fallback_rbp_15,24)
ENTRY(D2_seventh_rsp_1,24)
ENTRY(D2_seventh_rsp_3,24)
ENTRY(D2_seventh_rsp_5,24)
ENTRY(D2_seventh_rsp_7,24)
ENTRY(D2_seventh_rsp_11,24)
ENTRY(D2_seventh_rsp_15,24)
ENTRY(D2_seventh_rbp_1,24)
ENTRY(D2_seventh_rbp_3,24)
ENTRY(D2_seventh_rbp_5,24)
ENTRY(D2_seventh_rbp_7,24)
ENTRY(D2_seventh_rbp_11,24)
ENTRY(D2_seventh_rbp_15,24)
ENTRY(D3_alone_rsp_1,6)
ENTRY(D3_alone_rsp_3,6)
ENTRY(D3_alone_rsp_5,6)
ENTRY(D3_alone_rsp_7,6)
ENTRY(D3_alone_rsp_11,6)
ENTRY(D3_alone_rsp_15,6)
ENTRY(D3_alone_rbp_1,6)
ENTRY(D3_alone_rbp_3,6)
ENTRY(D3_alone_rbp_5,6)
ENTRY(D3_alone_rbp_7,6)
ENTRY(D3_alone_rbp_11,6)
ENTRY(D3_alone_rbp_15,6)
ENTRY(D3_holes_rsp_1,71)
ENTRY(D3_holes_rsp_3,71)
ENTRY(D3_holes_rsp_5,71)
ENTRY(D3_holes_rsp_7,71)
ENTRY(D3_holes_rsp_11,71)
ENTRY(D3_holes_rsp_15,71)
ENTRY(D3_holes_rbp_1,71)
ENTRY(D3_holes_rbp_3,71)
ENTRY(D3_holes_rbp_5,71)
ENTRY(D3_holes_rbp_7,71)
ENTRY(D3_holes_rbp_11,71)
ENTRY(D3_holes_rbp_15,71)
ENTRY(D3_fallback_rsp_1,27)
ENTRY(D3_fallback_rsp_3,27)
ENTRY(D3_fallback_rsp_5,27)
ENTRY(D3_fallback_rsp_7,27)
ENTRY(D3_fallback_rsp_11,27)
ENTRY(D3_fallback_rsp_15,27)
ENTRY(D3_fallback_rbp_1,27)
ENTRY(D3_fallback_rbp_3,27)
ENTRY(D3_fallback_rbp_5,27)
ENTRY(D3_fallback_rbp_7,27)
ENTRY(D3_fallback_rbp_11,27)
ENTRY(D3_fallback_rbp_15,27)
ENTRY(D3_seventh_rsp_1,27)
ENTRY(D3_seventh_rsp_3,27)
ENTRY(D3_seventh_rsp_5,27)
ENTRY(D3_seventh_rsp_7,27)
ENTRY(D3_seventh_rsp_11,27)
ENTRY(D3_seventh_rsp_15,27)
ENTRY(D3_seventh_rbp_1,27)
ENTRY(D3_seventh_rbp_3,27)
ENTRY(D3_seventh_rbp_5,27)
ENTRY(D3_seventh_rbp_7,27)
ENTRY(D3_seventh_rbp_11,27)
ENTRY(D3_seventh_rbp_15,27)
ENTRY(D4_alone_rsp_1,10)
ENTRY(D4_alone_rsp_3,10)
ENTRY(D4_alone_rsp_5,10)
ENTRY(D4_alone_rsp_7,10)
ENTRY(D4_alone_rsp_11,10)
ENTRY(D4_alone_rsp_15,10)
ENTRY(D4_alone_rbp_1,10)
ENTRY(D4_alone_rbp_3,10)
ENTRY(D4_alone_rbp_5,10)
ENTRY(D4_alone_rbp_7,10)
ENTRY(D4_alone_rbp_11,10)
ENTRY(D4_alone_rbp_15,10)
ENTRY(D4_holes_rsp_1,75)
ENTRY(D4_holes_rsp_3,75)
ENTRY(D4_holes_rsp_5,75)
ENTRY(D4_holes_rsp_7,75)
ENTRY(D4_holes_rsp_11,75)
ENTRY(D4_holes_rsp_15,75)
ENTRY(D4_holes_rbp_1,75)
ENTRY(D4_holes_rbp_3,75)
ENTRY(D4_holes_rbp_5,75)
ENTRY(D4_holes_rbp_7,75)
ENTRY(D4_holes_rbp_11,75)
ENTRY(D4_holes_rbp_15,75)
ENTRY(D4_fallback_rsp_1,31)
ENTRY(D4_fallback_rsp_3,31)
ENTRY(D4_fallback_rsp_5,31)
ENTRY(D4_fallback_rsp_7,31)
ENTRY(D4_fallback_rsp_11,31)
ENTRY(D4_fallback_rsp_15,31)
ENTRY(D4_fallback_rbp_1,31)
ENTRY(D4_fallback_rbp_3,31)
ENTRY(D4_fallback_rbp_5,31)
ENTRY(D4_fallback_rbp_7,31)
ENTRY(D4_fallback_rbp_11,31)
ENTRY(D4_fallback_rbp_15,31)
ENTRY(D4_seventh_rsp_1,31)
ENTRY(D4_seventh_rsp_3,31)
ENTRY(D4_seventh_rsp_5,31)
ENTRY(D4_seventh_rsp_7,31)
ENTRY(D4_seventh_rsp_11,31)
ENTRY(D4_seventh_rsp_15,31)
ENTRY(D4_seventh_rbp_1,31)
ENTRY(D4_seventh_rbp_3,31)
ENTRY(D4_seventh_rbp_5,31)
ENTRY(D4_seventh_rbp_7,31)
ENTRY(D4_seventh_rbp_11,31)
ENTRY(D4_seventh_rbp_15,31)
ENTRY(V1_alone_rsp_1,4)
ENTRY(V1_alone_rsp_3,4)
ENTRY(V1_alone_rsp_5,4)
ENTRY(V1_alone_rsp_7,4)
ENTRY(V1_alone_rsp_11,4)
ENTRY(V1_alone_rsp_15,4)
ENTRY(V1_alone_rbp_1,4)
ENTRY(V1_alone_rbp_3,4)
ENTRY(V1_alone_rbp_5,4)
ENTRY(V1_alone_rbp_7,4)
ENTRY(V1_alone_rbp_11,4)
ENTRY(V1_alone_rbp_15,4)
ENTRY(V1_holes_rsp_1,69)
ENTRY(V1_holes_rsp_3,69)
ENTRY(V1_holes_rsp_5,69)
ENTRY(V1_holes_rsp_7,69)
ENTRY(V1_holes_rsp_11,69)
ENTRY(V1_holes_rsp_15,69)
ENTRY(V1_holes_rbp_1,69)
ENTRY(V1_holes_rbp_3,69)
ENTRY(V1_holes_rbp_5,69)
ENTRY(V1_holes_rbp_7,69)
ENTRY(V1_holes_rbp_11,69)
ENTRY(V1_holes_rbp_15,69)
ENTRY(V1_fallback_rsp_1,25)
ENTRY(V1_fallback_rsp_3,25)
ENTRY(V1_fallback_rsp_5,25)
ENTRY(V1_fallback_rsp_7,25)
ENTRY(V1_fallback_rsp_11,25)
ENTRY(V1_fallback_rsp_15,25)
ENTRY(V1_fallback_rbp_1,25)
ENTRY(V1_fallback_rbp_3,25)
ENTRY(V1_fallback_rbp_5,25)
ENTRY(V1_fallback_rbp_7,25)
ENTRY(V1_fallback_rbp_11,25)
ENTRY(V1_fallback_rbp_15,25)
ENTRY(V1_seventh_rsp_1,25)
ENTRY(V1_seventh_rsp_3,25)
ENTRY(V1_seventh_rsp_5,25)
ENTRY(V1_seventh_rsp_7,25)
ENTRY(V1_seventh_rsp_11,25)
ENTRY(V1_seventh_rsp_15,25)
ENTRY(V1_seventh_rbp_1,25)
ENTRY(V1_seventh_rbp_3,25)
ENTRY(V1_seventh_rbp_5,25)
ENTRY(V1_seventh_rbp_7,25)
ENTRY(V1_seventh_rbp_11,25)
ENTRY(V1_seventh_rbp_15,25)
ENTRY(V2_alone_rsp_1,12)
ENTRY(V2_alone_rsp_3,12)
ENTRY(V2_alone_rsp_5,12)
ENTRY(V2_alone_rsp_7,12)
ENTRY(V2_alone_rsp_11,12)
ENTRY(V2_alone_rsp_15,12)
ENTRY(V2_alone_rbp_1,12)
ENTRY(V2_alone_rbp_3,12)
ENTRY(V2_alone_rbp_5,12)
ENTRY(V2_alone_rbp_7,12)
ENTRY(V2_alone_rbp_11,12)
ENTRY(V2_alone_rbp_15,12)
ENTRY(V2_holes_rsp_1,77)
ENTRY(V2_holes_rsp_3,77)
ENTRY(V2_holes_rsp_5,77)
ENTRY(V2_holes_rsp_7,77)
ENTRY(V2_holes_rsp_11,77)
ENTRY(V2_holes_rsp_15,77)
ENTRY(V2_holes_rbp_1,77)
ENTRY(V2_holes_rbp_3,77)
ENTRY(V2_holes_rbp_5,77)
ENTRY(V2_holes_rbp_7,77)
ENTRY(V2_holes_rbp_11,77)
ENTRY(V2_holes_rbp_15,77)
ENTRY(V2_fallback_rsp_1,33)
ENTRY(V2_fallback_rsp_3,33)
ENTRY(V2_fallback_rsp_5,33)
ENTRY(V2_fallback_rsp_7,33)
ENTRY(V2_fallback_rsp_11,33)
ENTRY(V2_fallback_rsp_15,33)
ENTRY(V2_fallback_rbp_1,33)
ENTRY(V2_fallback_rbp_3,33)
ENTRY(V2_fallback_rbp_5,33)
ENTRY(V2_fallback_rbp_7,33)
ENTRY(V2_fallback_rbp_11,33)
ENTRY(V2_fallback_rbp_15,33)
ENTRY(V2_seventh_rsp_1,33)
ENTRY(V2_seventh_rsp_3,33)
ENTRY(V2_seventh_rsp_5,33)
ENTRY(V2_seventh_rsp_7,33)
ENTRY(V2_seventh_rsp_11,33)
ENTRY(V2_seventh_rsp_15,33)
ENTRY(V2_seventh_rbp_1,33)
ENTRY(V2_seventh_rbp_3,33)
ENTRY(V2_seventh_rbp_5,33)
ENTRY(V2_seventh_rbp_7,33)
ENTRY(V2_seventh_rbp_11,33)
ENTRY(V2_seventh_rbp_15,33)
ENTRY(V3_alone_rsp_1,24)
ENTRY(V3_alone_rsp_3,24)
ENTRY(V3_alone_rsp_5,24)
ENTRY(V3_alone_rsp_7,24)
ENTRY(V3_alone_rsp_11,24)
ENTRY(V3_alone_rsp_15,24)
ENTRY(V3_alone_rbp_1,24)
ENTRY(V3_alone_rbp_3,24)
ENTRY(V3_alone_rbp_5,24)
ENTRY(V3_alone_rbp_7,24)
ENTRY(V3_alone_rbp_11,24)
ENTRY(V3_alone_rbp_15,24)
ENTRY(V3_holes_rsp_1,89)
ENTRY(V3_holes_rsp_3,89)
ENTRY(V3_holes_rsp_5,89)
ENTRY(V3_holes_rsp_7,89)
ENTRY(V3_holes_rsp_11,89)
ENTRY(V3_holes_rsp_15,89)
ENTRY(V3_holes_rbp_1,89)
ENTRY(V3_holes_rbp_3,89)
ENTRY(V3_holes_rbp_5,89)
ENTRY(V3_holes_rbp_7,89)
ENTRY(V3_holes_rbp_11,89)
ENTRY(V3_holes_rbp_15,89)
ENTRY(V3_fallback_rsp_1,45)
ENTRY(V3_fallback_rsp_3,45)
ENTRY(V3_fallback_rsp_5,45)
ENTRY(V3_fallback_rsp_7,45)
ENTRY(V3_fallback_rsp_11,45)
ENTRY(V3_fallback_rsp_15,45)
ENTRY(V3_fallback_rbp_1,45)
ENTRY(V3_fallback_rbp_3,45)
ENTRY(V3_fallback_rbp_5,45)
ENTRY(V3_fallback_rbp_7,45)
ENTRY(V3_fallback_rbp_11,45)
ENTRY(V3_fallback_rbp_15,45)
ENTRY(V3_seventh_rsp_1,45)
ENTRY(V3_seventh_rsp_3,45)
ENTRY(V3_seventh_rsp_5,45)
ENTRY(V3_seventh_rsp_7,45)
ENTRY(V3_seventh_rsp_11,45)
ENTRY(V3_seventh_rsp_15,45)
ENTRY(V3_seventh_rbp_1,45)
ENTRY(V3_seventh_rbp_3,45)
ENTRY(V3_seventh_rbp_5,45)
ENTRY(V3_seventh_rbp_7,45)
ENTRY(V3_seventh_rbp_11,45)
ENTRY(V3_seventh_rbp_15,45)
ENTRY(V4_alone_rsp_1,40)
ENTRY(V4_alone_rsp_3,40)
ENTRY(V4_alone_rsp_5,40)
ENTRY(V4_alone_rsp_7,40)
ENTRY(V4_alone_rsp_11,40)
ENTRY(V4_alone_rsp_15,40)
ENTRY(V4_alone_rbp_1,40)
ENTRY(V4_alone_rbp_3,40)
ENTRY(V4_alone_rbp_5,40)
ENTRY(V4_alone_rbp_7,40)
ENTRY(V4_alone_rbp_11,40)
ENTRY(V4_alone_rbp_15,40)
ENTRY(V4_holes_rsp_1,105)
ENTRY(V4_holes_rsp_3,105)
ENTRY(V4_holes_rsp_5,105)
ENTRY(V4_holes_rsp_7,105)
ENTRY(V4_holes_rsp_11,105)
ENTRY(V4_holes_rsp_15,105)
ENTRY(V4_holes_rbp_1,105)
ENTRY(V4_holes_rbp_3,105)
ENTRY(V4_holes_rbp_5,105)
ENTRY(V4_holes_rbp_7,105)
ENTRY(V4_holes_rbp_11,105)
ENTRY(V4_holes_rbp_15,105)
ENTRY(V4_fallback_rsp_1,61)
ENTRY(V4_fallback_rsp_3,61)
ENTRY(V4_fallback_rsp_5,61)
ENTRY(V4_fallback_rsp_7,61)
ENTRY(V4_fallback_rsp_11,61)
ENTRY(V4_fallback_rsp_15,61)
ENTRY(V4_fallback_rbp_1,61)
ENTRY(V4_fallback_rbp_3,61)
ENTRY(V4_fallback_rbp_5,61)
ENTRY(V4_fallback_rbp_7,61)
ENTRY(V4_fallback_rbp_11,61)
ENTRY(V4_fallback_rbp_15,61)
ENTRY(V4_seventh_rsp_1,61)
ENTRY(V4_seventh_rsp_3,61)
ENTRY(V4_seventh_rsp_5,61)
ENTRY(V4_seventh_rsp_7,61)
ENTRY(V4_seventh_rsp_11,61)
ENTRY(V4_seventh_rsp_15,61)
ENTRY(V4_seventh_rbp_1,61)
ENTRY(V4_seventh_rbp_3,61)
ENTRY(V4_seventh_rbp_5,61)
ENTRY(V4_seventh_rbp_7,61)
ENTRY(V4_seventh_rbp_11,61)
ENTRY(V4_seventh_rbp_15,61)
ENTRY(Y1_alone_rsp_1,8)
ENTRY(Y1_alone_rsp_3,8)
ENTRY(Y1_alone_rsp_5,8)
ENTRY(Y1_alone_rsp_7,8)
ENTRY(Y1_alone_rsp_11,8)
ENTRY(Y1_alone_rsp_15,8)
ENTRY(Y1_alone_rbp_1,8)
ENTRY(Y1_alone_rbp_3,8)
ENTRY(Y1_alone_rbp_5,8)
ENTRY(Y1_alone_rbp_7,8)
ENTRY(Y1_alone_rbp_11,8)
ENTRY(Y1_alone_rbp_15,8)
ENTRY(Y1_holes_rsp_1,73)
ENTRY(Y1_holes_rsp_3,73)
ENTRY(Y1_holes_rsp_5,73)
ENTRY(Y1_holes_rsp_7,73)
ENTRY(Y1_holes_rsp_11,73)
ENTRY(Y1_holes_rsp_15,73)
ENTRY(Y1_holes_rbp_1,73)
ENTRY(Y1_holes_rbp_3,73)
ENTRY(Y1_holes_rbp_5,73)
ENTRY(Y1_holes_rbp_7,73)
ENTRY(Y1_holes_rbp_11,73)
ENTRY(Y1_holes_rbp_15,73)
ENTRY(Y1_fallback_rsp_1,29)
ENTRY(Y1_fallback_rsp_3,29)
ENTRY(Y1_fallback_rsp_5,29)
ENTRY(Y1_fallback_rsp_7,29)
ENTRY(Y1_fallback_rsp_11,29)
ENTRY(Y1_fallback_rsp_15,29)
ENTRY(Y1_fallback_rbp_1,29)
ENTRY(Y1_fallback_rbp_3,29)
ENTRY(Y1_fallback_rbp_5,29)
ENTRY(Y1_fallback_rbp_7,29)
ENTRY(Y1_fallback_rbp_11,29)
ENTRY(Y1_fallback_rbp_15,29)
ENTRY(Y1_seventh_rsp_1,29)
ENTRY(Y1_seventh_rsp_3,29)
ENTRY(Y1_seventh_rsp_5,29)
ENTRY(Y1_seventh_rsp_7,29)
ENTRY(Y1_seventh_rsp_11,29)
ENTRY(Y1_seventh_rsp_15,29)
ENTRY(Y1_seventh_rbp_1,29)
ENTRY(Y1_seventh_rbp_3,29)
ENTRY(Y1_seventh_rbp_5,29)
ENTRY(Y1_seventh_rbp_7,29)
ENTRY(Y1_seventh_rbp_11,29)
ENTRY(Y1_seventh_rbp_15,29)
ENTRY(Y2_alone_rsp_1,24)
ENTRY(Y2_alone_rsp_3,24)
ENTRY(Y2_alone_rsp_5,24)
ENTRY(Y2_alone_rsp_7,24)
ENTRY(Y2_alone_rsp_11,24)
ENTRY(Y2_alone_rsp_15,24)
ENTRY(Y2_alone_rbp_1,24)
ENTRY(Y2_alone_rbp_3,24)
ENTRY(Y2_alone_rbp_5,24)
ENTRY(Y2_alone_rbp_7,24)
ENTRY(Y2_alone_rbp_11,24)
ENTRY(Y2_alone_rbp_15,24)
ENTRY(Y2_holes_rsp_1,89)
ENTRY(Y2_holes_rsp_3,89)
ENTRY(Y2_holes_rsp_5,89)
ENTRY(Y2_holes_rsp_7,89)
ENTRY(Y2_holes_rsp_11,89)
ENTRY(Y2_holes_rsp_15,89)
ENTRY(Y2_holes_rbp_1,89)
ENTRY(Y2_holes_rbp_3,89)
ENTRY(Y2_holes_rbp_5,89)
ENTRY(Y2_holes_rbp_7,89)
ENTRY(Y2_holes_rbp_11,89)
ENTRY(Y2_holes_rbp_15,89)
ENTRY(Y2_fallback_rsp_1,45)
ENTRY(Y2_fallback_rsp_3,45)
ENTRY(Y2_fallback_rsp_5,45)
ENTRY(Y2_fallback_rsp_7,45)
ENTRY(Y2_fallback_rsp_11,45)
ENTRY(Y2_fallback_rsp_15,45)
ENTRY(Y2_fallback_rbp_1,45)
ENTRY(Y2_fallback_rbp_3,45)
ENTRY(Y2_fallback_rbp_5,45)
ENTRY(Y2_fallback_rbp_7,45)
ENTRY(Y2_fallback_rbp_11,45)
ENTRY(Y2_fallback_rbp_15,45)
ENTRY(Y2_seventh_rsp_1,45)
ENTRY(Y2_seventh_rsp_3,45)
ENTRY(Y2_seventh_rsp_5,45)
ENTRY(Y2_seventh_rsp_7,45)
ENTRY(Y2_seventh_rsp_11,45)
ENTRY(Y2_seventh_rsp_15,45)
ENTRY(Y2_seventh_rbp_1,45)
ENTRY(Y2_seventh_rbp_3,45)
ENTRY(Y2_seventh_rbp_5,45)
ENTRY(Y2_seventh_rbp_7,45)
ENTRY(Y2_seventh_rbp_11,45)
ENTRY(Y2_seventh_rbp_15,45)
ENTRY(Y3_alone_rsp_1,48)
ENTRY(Y3_alone_rsp_3,48)
ENTRY(Y3_alone_rsp_5,48)
ENTRY(Y3_alone_rsp_7,48)
ENTRY(Y3_alone_rsp_11,48)
ENTRY(Y3_alone_rsp_15,48)
ENTRY(Y3_alone_rbp_1,48)
ENTRY(Y3_alone_rbp_3,48)
ENTRY(Y3_alone_rbp_5,48)
ENTRY(Y3_alone_rbp_7,48)
ENTRY(Y3_alone_rbp_11,48)
ENTRY(Y3_alone_rbp_15,48)
ENTRY(Y3_holes_rsp_1,113)
ENTRY(Y3_holes_rsp_3,113)
ENTRY(Y3_holes_rsp_5,113)
ENTRY(Y3_holes_rsp_7,113)
ENTRY(Y3_holes_rsp_11,113)
ENTRY(Y3_holes_rsp_15,113)
ENTRY(Y3_holes_rbp_1,113)
ENTRY(Y3_holes_rbp_3,113)
ENTRY(Y3_holes_rbp_5,113)
ENTRY(Y3_holes_rbp_7,113)
ENTRY(Y3_holes_rbp_11,113)
ENTRY(Y3_holes_rbp_15,113)
ENTRY(Y3_fallback_rsp_1,69)
ENTRY(Y3_fallback_rsp_3,69)
ENTRY(Y3_fallback_rsp_5,69)
ENTRY(Y3_fallback_rsp_7,69)
ENTRY(Y3_fallback_rsp_11,69)
ENTRY(Y3_fallback_rsp_15,69)
ENTRY(Y3_fallback_rbp_1,69)
ENTRY(Y3_fallback_rbp_3,69)
ENTRY(Y3_fallback_rbp_5,69)
ENTRY(Y3_fallback_rbp_7,69)
ENTRY(Y3_fallback_rbp_11,69)
ENTRY(Y3_fallback_rbp_15,69)
ENTRY(Y3_seventh_rsp_1,69)
ENTRY(Y3_seventh_rsp_3,69)
ENTRY(Y3_seventh_rsp_5,69)
ENTRY(Y3_seventh_rsp_7,69)
ENTRY(Y3_seventh_rsp_11,69)
ENTRY(Y3_seventh_rsp_15,69)
ENTRY(Y3_seventh_rbp_1,69)
ENTRY(Y3_seventh_rbp_3,69)
ENTRY(Y3_seventh_rbp_5,69)
ENTRY(Y3_seventh_rbp_7,69)
ENTRY(Y3_seventh_rbp_11,69)
ENTRY(Y3_seventh_rbp_15,69)
ENTRY(Y4_alone_rsp_1,80)
ENTRY(Y4_alone_rsp_3,80)
ENTRY(Y4_alone_rsp_5,80)
ENTRY(Y4_alone_rsp_7,80)
ENTRY(Y4_alone_rsp_11,80)
ENTRY(Y4_alone_rsp_15,80)
ENTRY(Y4_alone_rbp_1,80)
ENTRY(Y4_alone_rbp_3,80)
ENTRY(Y4_alone_rbp_5,80)
ENTRY(Y4_alone_rbp_7,80)
ENTRY(Y4_alone_rbp_11,80)
ENTRY(Y4_alone_rbp_15,80)
ENTRY(Y4_holes_rsp_1,145)
ENTRY(Y4_holes_rsp_3,145)
ENTRY(Y4_holes_rsp_5,145)
ENTRY(Y4_holes_rsp_7,145)
ENTRY(Y4_holes_rsp_11,145)
ENTRY(Y4_holes_rsp_15,145)
ENTRY(Y4_holes_rbp_1,145)
ENTRY(Y4_holes_rbp_3,145)
ENTRY(Y4_holes_rbp_5,145)
ENTRY(Y4_holes_rbp_7,145)
ENTRY(Y4_holes_rbp_11,145)
ENTRY(Y4_holes_rbp_15,145)
ENTRY(Y4_fallback_rsp_1,101)
ENTRY(Y4_fallback_rsp_3,101)
ENTRY(Y4_fallback_rsp_5,101)
ENTRY(Y4_fallback_rsp_7,101)
ENTRY(Y4_fallback_rsp_11,101)
ENTRY(Y4_fallback_rsp_15,101)
ENTRY(Y4_fallback_rbp_1,101)
ENTRY(Y4_fallback_rbp_3,101)
ENTRY(Y4_fallback_rbp_5,101)
ENTRY(Y4_fallback_rbp_7,101)
ENTRY(Y4_fallback_rbp_11,101)
ENTRY(Y4_fallback_rbp_15,101)
ENTRY(Y4_seventh_rsp_1,101)
ENTRY(Y4_seventh_rsp_3,101)
ENTRY(Y4_seventh_rsp_5,101)
ENTRY(Y4_seventh_rsp_7,101)
ENTRY(Y4_seventh_rsp_11,101)
ENTRY(Y4_seventh_rsp_15,101)
ENTRY(Y4_seventh_rbp_1,101)
ENTRY(Y4_seventh_rbp_3,101)
ENTRY(Y4_seventh_rbp_5,101)
ENTRY(Y4_seventh_rbp_7,101)
ENTRY(Y4_seventh_rbp_11,101)
ENTRY(Y4_seventh_rbp_15,101)
ENTRY(NF_alone_rsp_1,10)
ENTRY(NF_alone_rsp_3,10)
ENTRY(NF_alone_rsp_5,10)
ENTRY(NF_alone_rsp_7,10)
ENTRY(NF_alone_rsp_11,10)
ENTRY(NF_alone_rsp_15,10)
ENTRY(NF_alone_rbp_1,10)
ENTRY(NF_alone_rbp_3,10)
ENTRY(NF_alone_rbp_5,10)
ENTRY(NF_alone_rbp_7,10)
ENTRY(NF_alone_rbp_11,10)
ENTRY(NF_alone_rbp_15,10)
ENTRY(NF_holes_rsp_1,75)
ENTRY(NF_holes_rsp_3,75)
ENTRY(NF_holes_rsp_5,75)
ENTRY(NF_holes_rsp_7,75)
ENTRY(NF_holes_rsp_11,75)
ENTRY(NF_holes_rsp_15,75)
ENTRY(NF_holes_rbp_1,75)
ENTRY(NF_holes_rbp_3,75)
ENTRY(NF_holes_rbp_5,75)
ENTRY(NF_holes_rbp_7,75)
ENTRY(NF_holes_rbp_11,75)
ENTRY(NF_holes_rbp_15,75)
ENTRY(NF_fallback_rsp_1,31)
ENTRY(NF_fallback_rsp_3,31)
ENTRY(NF_fallback_rsp_5,31)
ENTRY(NF_fallback_rsp_7,31)
ENTRY(NF_fallback_rsp_11,31)
ENTRY(NF_fallback_rsp_15,31)
ENTRY(NF_fallback_rbp_1,31)
ENTRY(NF_fallback_rbp_3,31)
ENTRY(NF_fallback_rbp_5,31)
ENTRY(NF_fallback_rbp_7,31)
ENTRY(NF_fallback_rbp_11,31)
ENTRY(NF_fallback_rbp_15,31)
ENTRY(NF_seventh_rsp_1,31)
ENTRY(NF_seventh_rsp_3,31)
ENTRY(NF_seventh_rsp_5,31)
ENTRY(NF_seventh_rsp_7,31)
ENTRY(NF_seventh_rsp_11,31)
ENTRY(NF_seventh_rsp_15,31)
ENTRY(NF_seventh_rbp_1,31)
ENTRY(NF_seventh_rbp_3,31)
ENTRY(NF_seventh_rbp_5,31)
ENTRY(NF_seventh_rbp_7,31)
ENTRY(NF_seventh_rbp_11,31)
ENTRY(NF_seventh_rbp_15,31)
ENTRY(AF_alone_rsp_1,10)
ENTRY(AF_alone_rsp_3,10)
ENTRY(AF_alone_rsp_5,10)
ENTRY(AF_alone_rsp_7,10)
ENTRY(AF_alone_rsp_11,10)
ENTRY(AF_alone_rsp_15,10)
ENTRY(AF_alone_rbp_1,10)
ENTRY(AF_alone_rbp_3,10)
ENTRY(AF_alone_rbp_5,10)
ENTRY(AF_alone_rbp_7,10)
ENTRY(AF_alone_rbp_11,10)
ENTRY(AF_alone_rbp_15,10)
ENTRY(AF_holes_rsp_1,75)
ENTRY(AF_holes_rsp_3,75)
ENTRY(AF_holes_rsp_5,75)
ENTRY(AF_holes_rsp_7,75)
ENTRY(AF_holes_rsp_11,75)
ENTRY(AF_holes_rsp_15,75)
ENTRY(AF_holes_rbp_1,75)
ENTRY(AF_holes_rbp_3,75)
ENTRY(AF_holes_rbp_5,75)
ENTRY(AF_holes_rbp_7,75)
ENTRY(AF_holes_rbp_11,75)
ENTRY(AF_holes_rbp_15,75)
ENTRY(AF_fallback_rsp_1,31)
ENTRY(AF_fallback_rsp_3,31)
ENTRY(AF_fallback_rsp_5,31)
ENTRY(AF_fallback_rsp_7,31)
ENTRY(AF_fallback_rsp_11,31)
ENTRY(AF_fallback_rsp_15,31)
ENTRY(AF_fallback_rbp_1,31)
ENTRY(AF_fallback_rbp_3,31)
ENTRY(AF_fallback_rbp_5,31)
ENTRY(AF_fallback_rbp_7,31)
ENTRY(AF_fallback_rbp_11,31)
ENTRY(AF_fallback_rbp_15,31)
ENTRY(AF_seventh_rsp_1,31)
ENTRY(AF_seventh_rsp_3,31)
ENTRY(AF_seventh_rsp_5,31)
ENTRY(AF_seventh_rsp_7,31)
ENTRY(AF_seventh_rsp_11,31)
ENTRY(AF_seventh_rsp_15,31)
ENTRY(AF_seventh_rbp_1,31)
ENTRY(AF_seventh_rbp_3,31)
ENTRY(AF_seventh_rbp_5,31)
ENTRY(AF_seventh_rbp_7,31)
ENTRY(AF_seventh_rbp_11,31)
ENTRY(AF_seventh_rbp_15,31)
ENTRY(Mixed_alone_rsp_1,3)
ENTRY(Mixed_alone_rsp_3,3)
ENTRY(Mixed_alone_rsp_5,3)
ENTRY(Mixed_alone_rsp_7,3)
ENTRY(Mixed_alone_rsp_11,3)
ENTRY(Mixed_alone_rsp_15,3)
ENTRY(Mixed_alone_rbp_1,3)
ENTRY(Mixed_alone_rbp_3,3)
ENTRY(Mixed_alone_rbp_5,3)
ENTRY(Mixed_alone_rbp_7,3)
ENTRY(Mixed_alone_rbp_11,3)
ENTRY(Mixed_alone_rbp_15,3)
ENTRY(Mixed_holes_rsp_1,68)
ENTRY(Mixed_holes_rsp_3,68)
ENTRY(Mixed_holes_rsp_5,68)
ENTRY(Mixed_holes_rsp_7,68)
ENTRY(Mixed_holes_rsp_11,68)
ENTRY(Mixed_holes_rsp_15,68)
ENTRY(Mixed_holes_rbp_1,68)
ENTRY(Mixed_holes_rbp_3,68)
ENTRY(Mixed_holes_rbp_5,68)
ENTRY(Mixed_holes_rbp_7,68)
ENTRY(Mixed_holes_rbp_11,68)
ENTRY(Mixed_holes_rbp_15,68)
ENTRY(Mixed_fallback_rsp_1,24)
ENTRY(Mixed_fallback_rsp_3,24)
ENTRY(Mixed_fallback_rsp_5,24)
ENTRY(Mixed_fallback_rsp_7,24)
ENTRY(Mixed_fallback_rsp_11,24)
ENTRY(Mixed_fallback_rsp_15,24)
ENTRY(Mixed_fallback_rbp_1,24)
ENTRY(Mixed_fallback_rbp_3,24)
ENTRY(Mixed_fallback_rbp_5,24)
ENTRY(Mixed_fallback_rbp_7,24)
ENTRY(Mixed_fallback_rbp_11,24)
ENTRY(Mixed_fallback_rbp_15,24)
ENTRY(Mixed_seventh_rsp_1,24)
ENTRY(Mixed_seventh_rsp_3,24)
ENTRY(Mixed_seventh_rsp_5,24)
ENTRY(Mixed_seventh_rsp_7,24)
ENTRY(Mixed_seventh_rsp_11,24)
ENTRY(Mixed_seventh_rsp_15,24)
ENTRY(Mixed_seventh_rbp_1,24)
ENTRY(Mixed_seventh_rbp_3,24)
ENTRY(Mixed_seventh_rbp_5,24)
ENTRY(Mixed_seventh_rbp_7,24)
ENTRY(Mixed_seventh_rbp_11,24)
ENTRY(Mixed_seventh_rbp_15,24)
ENTRY(Ints_alone_rsp_1,3)
ENTRY(Ints_alone_rsp_3,3)
ENTRY(Ints_alone_rsp_5,3)
ENTRY(Ints_alone_rsp_7,3)
ENTRY(Ints_alone_rsp_11,3)
ENTRY(Ints_alone_rsp_15,3)
ENTRY(Ints_alone_rbp_1,3)
ENTRY(Ints_alone_rbp_3,3)
ENTRY(Ints_alone_rbp_5,3)
ENTRY(Ints_alone_rbp_7,3)
ENTRY(Ints_alone_rbp_11,3)
ENTRY(Ints_alone_rbp_15,3)
ENTRY(Ints_holes_rsp_1,68)
ENTRY(Ints_holes_rsp_3,68)
ENTRY(Ints_holes_rsp_5,68)
ENTRY(Ints_holes_rsp_7,68)
ENTRY(Ints_holes_rsp_11,68)
ENTRY(Ints_holes_rsp_15,68)
ENTRY(Ints_holes_rbp_1,68)
ENTRY(Ints_holes_rbp_3,68)
ENTRY(Ints_holes_rbp_5,68)
ENTRY(Ints_holes_rbp_7,68)
ENTRY(Ints_holes_rbp_11,68)
ENTRY(Ints_holes_rbp_15,68)
ENTRY(Ints_fallback_rsp_1,24)
ENTRY(Ints_fallback_rsp_3,24)
ENTRY(Ints_fallback_rsp_5,24)
ENTRY(Ints_fallback_rsp_7,24)
ENTRY(Ints_fallback_rsp_11,24)
ENTRY(Ints_fallback_rsp_15,24)
ENTRY(Ints_fallback_rbp_1,24)
ENTRY(Ints_fallback_rbp_3,24)
ENTRY(Ints_fallback_rbp_5,24)
ENTRY(Ints_fallback_rbp_7,24)
ENTRY(Ints_fallback_rbp_11,24)
ENTRY(Ints_fallback_rbp_15,24)
ENTRY(Ints_seventh_rsp_1,24)
ENTRY(Ints_seventh_rsp_3,24)
ENTRY(Ints_seventh_rsp_5,24)
ENTRY(Ints_seventh_rsp_7,24)
ENTRY(Ints_seventh_rsp_11,24)
ENTRY(Ints_seventh_rsp_15,24)
ENTRY(Ints_seventh_rbp_1,24)
ENTRY(Ints_seventh_rbp_3,24)
ENTRY(Ints_seventh_rbp_5,24)
ENTRY(Ints_seventh_rbp_7,24)
ENTRY(Ints_seventh_rbp_11,24)
ENTRY(Ints_seventh_rbp_15,24)
ENTRY(__m128f_alone_rsp_1,10)
ENTRY(__m128f_alone_rsp_3,10)
ENTRY(__m128f_alone_rsp_5,10)
ENTRY(__m128f_alone_rsp_7,10)
ENTRY(__m128f_alone_rsp_11,10)
ENTRY(__m128f_alone_rsp_15,10)
ENTRY(__m128f_alone_rbp_1,10)
ENTRY(__m128f_alone_rbp_3,10)
ENTRY(__m128f_alone_rbp_5,10)
ENTRY(__m128f_alone_rbp_7,10)
ENTRY(__m128f_alone_rbp_11,10)
ENTRY(__m128f_alone_rbp_15,10)
ENTRY(__m128f_holes_rsp_1,75)
ENTRY(__m128f_holes_rsp_3,75)
ENTRY(__m128f_holes_rsp_5,75)
ENTRY(__m128f_holes_rsp_7,75)
ENTRY(__m128f_holes_rsp_11,75)
ENTRY(__m128f_holes_rsp_15,75)
ENTRY(__m128f_holes_rbp_1,75)
ENTRY(__m128f_holes_rbp_3,75)
ENTRY(__m128f_holes_rbp_5,75)
ENTRY(__m128f_holes_rbp_7,75)
ENTRY(__m128f_holes_rbp_11,75)
ENTRY(__m128f_holes_rbp_15,75)
ENTRY(__m128f_fallback_rsp_1,31)
ENTRY(__m128f_fallback_rsp_3,31)
ENTRY(__m128f_fallback_rsp_5,31)
ENTRY(__m128f_fallback_rsp_7,31)
ENTRY(__m128f_fallback_rsp_11,31)
ENTRY(__m128f_fallback_rsp_15,31)
ENTRY(__m128f_fallback_rbp_1,31)
ENTRY(__m128f_fallback_rbp_3,31)
ENTRY(__m128f_fallback_rbp_5,31)
ENTRY(__m128f_fallback_rbp_7,31)
ENTRY(__m128f_fallback_rbp_11,31)
ENTRY(__m128f_fallback_rbp_15,31)
ENTRY(__m128f_seventh_rsp_1,31)
ENTRY(__m128f_seventh_rsp_3,31)
ENTRY(__m128f_seventh_rsp_5,31)
ENTRY(__m128f_seventh_rsp_7,31)
ENTRY(__m128f_seventh_rsp_11,31)
ENTRY(__m128f_seventh_rsp_15,31)
ENTRY(__m128f_seventh_rbp_1,31)
ENTRY(__m128f_seventh_rbp_3,31)
ENTRY(__m128f_seventh_rbp_5,31)
ENTRY(__m128f_seventh_rbp_7,31)
ENTRY(__m128f_seventh_rbp_11,31)
ENTRY(__m128f_seventh_rbp_15,31)
ENTRY(__m256f_alone_rsp_1,36)
ENTRY(__m256f_alone_rsp_3,36)
ENTRY(__m256f_alone_rsp_5,36)
ENTRY(__m256f_alone_rsp_7,36)
ENTRY(__m256f_alone_rsp_11,36)
ENTRY(__m256f_alone_rsp_15,36)
ENTRY(__m256f_alone_rbp_1,36)
ENTRY(__m256f_alone_rbp_3,36)
ENTRY(__m256f_alone_rbp_5,36)
ENTRY(__m256f_alone_rbp_7,36)
ENTRY(__m256f_alone_rbp_11,36)
ENTRY(__m256f_alone_rbp_15,36)
ENTRY(__m256f_holes_rsp_1,101)
ENTRY(__m256f_holes_rsp_3,101)
ENTRY(__m256f_holes_rsp_5,101)
ENTRY(__m256f_holes_rsp_7,101)
ENTRY(__m256f_holes_rsp_11,101)
ENTRY(__m256f_holes_rsp_15,101)
ENTRY(__m256f_holes_rbp_1,101)
ENTRY(__m256f_holes_rbp_3,101)
ENTRY(__m256f_holes_rbp_5,101)
ENTRY(__m256f_holes_rbp_7,101)
ENTRY(__m256f_holes_rbp_11,101)
ENTRY(__m256f_holes_rbp_15,101)
ENTRY(__m256f_fallback_rsp_1,57)
ENTRY(__m256f_fallback_rsp_3,57)
ENTRY(__m256f_fallback_rsp_5,57)
ENTRY(__m256f_fallback_rsp_7,57)
ENTRY(__m256f_fallback_rsp_11,57)
ENTRY(__m256f_fallback_rsp_15,57)
ENTRY(__m256f_fallback_rbp_1,57)
ENTRY(__m256f_fallback_rbp_3,57)
ENTRY(__m256f_fallback_rbp_5,57)
ENTRY(__m256f_fallback_rbp_7,57)
ENTRY(__m256f_fallback_rbp_11,57)
ENTRY(__m256f_fallback_rbp_15,57)
ENTRY(__m256f_seventh_rsp_1,57)
ENTRY(__m256f_seventh_rsp_3,57)
ENTRY(__m256f_seventh_rsp_5,57)
ENTRY(__m256f_seventh_rsp_7,57)
ENTRY(__m256f_seventh_rsp_11,57)
ENTRY(__m256f_seventh_rsp_15,57)
ENTRY(__m256f_seventh_rbp_1,57)
ENTRY(__m256f_seventh_rbp_3,57)
ENTRY(__m256f_seventh_rbp_5,57)
ENTRY(__m256f_seventh_rbp_7,57)
ENTRY(__m256f_seventh_rbp_11,57)
ENTRY(__m256f_seventh_rbp_15,57)
};
static int check(const struct testcase *t) { double got; __try {got=t->fn();} __except(EXCEPTION_EXECUTE_HANDLER) {printf("%s: exception %08lx\n",t->name,GetExceptionCode());return 1;} if(got==t->expected)return 0;printf("%s: %.17g expected %.17g\n",t->name,got,t->expected);return 1;}
int main(void) {unsigned i;int failed=0;SetErrorMode(SEM_FAILCRITICALERRORS|SEM_NOGPFAULTERRORBOX);
for(i=0;i<sizeof(tests)/sizeof(tests[0]);i++)failed+=check(&tests[i]);
printf("Vectorcall ABI: %u checks, %d failures\n",i,failed);return failed!=0;}
