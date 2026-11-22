#include <windows.h>
#include <immintrin.h>
#include <stdio.h>
typedef struct {float a,b;} HF2;
typedef struct {__m256 a,b,c,d;} HV4;
typedef struct {long long a,b;} Pair;
double __vectorcall c_multi(HF2 a,HV4 b,__m256 c,HF2 d){return a.a+a.b+b.a.m256_f32[0]+b.b.m256_f32[0]+b.c.m256_f32[0]+b.d.m256_f32[0]+c.m256_f32[0]+d.a+d.b;}
double __vectorcall c_seven128(long long a,long long b,long long c,long long d,long long e,long long f,__m128 g){return a+b+c+d+e+f+g.m128_f32[0]+g.m128_f32[3];}
double __vectorcall c_seven256(long long a,long long b,long long c,long long d,long long e,long long f,long long g,__m256 h){return a+b+c+d+e+f+g+h.m256_f32[0]+h.m256_f32[7];}
void __vectorcall c_mutate(Pair a){volatile Pair *p=&a;p->a=77;}
extern double multi_rsp_1(void);
extern double reg128_rsp_1(void);
extern double reg256_rsp_1(void);
extern long long referential_rsp_1(void);
extern double multi_rsp_3(void);
extern double reg128_rsp_3(void);
extern double reg256_rsp_3(void);
extern long long referential_rsp_3(void);
extern double multi_rsp_5(void);
extern double reg128_rsp_5(void);
extern double reg256_rsp_5(void);
extern long long referential_rsp_5(void);
extern double multi_rsp_7(void);
extern double reg128_rsp_7(void);
extern double reg256_rsp_7(void);
extern long long referential_rsp_7(void);
extern double multi_rsp_11(void);
extern double reg128_rsp_11(void);
extern double reg256_rsp_11(void);
extern long long referential_rsp_11(void);
extern double multi_rsp_15(void);
extern double reg128_rsp_15(void);
extern double reg256_rsp_15(void);
extern long long referential_rsp_15(void);
extern double multi_rbp_1(void);
extern double reg128_rbp_1(void);
extern double reg256_rbp_1(void);
extern long long referential_rbp_1(void);
extern double multi_rbp_3(void);
extern double reg128_rbp_3(void);
extern double reg256_rbp_3(void);
extern long long referential_rbp_3(void);
extern double multi_rbp_5(void);
extern double reg128_rbp_5(void);
extern double reg256_rbp_5(void);
extern long long referential_rbp_5(void);
extern double multi_rbp_7(void);
extern double reg128_rbp_7(void);
extern double reg256_rbp_7(void);
extern long long referential_rbp_7(void);
extern double multi_rbp_11(void);
extern double reg128_rbp_11(void);
extern double reg256_rbp_11(void);
extern long long referential_rbp_11(void);
extern double multi_rbp_15(void);
extern double reg128_rbp_15(void);
extern double reg256_rbp_15(void);
extern long long referential_rbp_15(void);
double __vectorcall raw_c(double a,double b,double c,double d,double e,double f,double g){return a+b+c+d+e+f+g;}
extern double __vectorcall raw_rsp_1(double,double,double,double,double,double,double);
extern double rawcall_rsp_1(void);
extern double __vectorcall raw_rsp_2(double,double,double,double,double,double,double);
extern double rawcall_rsp_2(void);
extern double __vectorcall raw_rsp_3(double,double,double,double,double,double,double);
extern double rawcall_rsp_3(void);
extern double __vectorcall raw_rsp_4(double,double,double,double,double,double,double);
extern double rawcall_rsp_4(void);
extern double __vectorcall raw_rsp_5(double,double,double,double,double,double,double);
extern double rawcall_rsp_5(void);
extern double __vectorcall raw_rsp_6(double,double,double,double,double,double,double);
extern double rawcall_rsp_6(void);
extern double __vectorcall raw_rsp_7(double,double,double,double,double,double,double);
extern double rawcall_rsp_7(void);
extern double __vectorcall raw_rsp_8(double,double,double,double,double,double,double);
extern double rawcall_rsp_8(void);
extern double __vectorcall raw_rsp_9(double,double,double,double,double,double,double);
extern double rawcall_rsp_9(void);
extern double __vectorcall raw_rsp_10(double,double,double,double,double,double,double);
extern double rawcall_rsp_10(void);
extern double __vectorcall raw_rsp_11(double,double,double,double,double,double,double);
extern double rawcall_rsp_11(void);
extern double __vectorcall raw_rsp_12(double,double,double,double,double,double,double);
extern double rawcall_rsp_12(void);
extern double __vectorcall raw_rsp_13(double,double,double,double,double,double,double);
extern double rawcall_rsp_13(void);
extern double __vectorcall raw_rsp_14(double,double,double,double,double,double,double);
extern double rawcall_rsp_14(void);
extern double __vectorcall raw_rsp_15(double,double,double,double,double,double,double);
extern double rawcall_rsp_15(void);
extern double __vectorcall raw_rbp_1(double,double,double,double,double,double,double);
extern double rawcall_rbp_1(void);
extern double __vectorcall raw_rbp_2(double,double,double,double,double,double,double);
extern double rawcall_rbp_2(void);
extern double __vectorcall raw_rbp_3(double,double,double,double,double,double,double);
extern double rawcall_rbp_3(void);
extern double __vectorcall raw_rbp_4(double,double,double,double,double,double,double);
extern double rawcall_rbp_4(void);
extern double __vectorcall raw_rbp_5(double,double,double,double,double,double,double);
extern double rawcall_rbp_5(void);
extern double __vectorcall raw_rbp_6(double,double,double,double,double,double,double);
extern double rawcall_rbp_6(void);
extern double __vectorcall raw_rbp_7(double,double,double,double,double,double,double);
extern double rawcall_rbp_7(void);
extern double __vectorcall raw_rbp_8(double,double,double,double,double,double,double);
extern double rawcall_rbp_8(void);
extern double __vectorcall raw_rbp_9(double,double,double,double,double,double,double);
extern double rawcall_rbp_9(void);
extern double __vectorcall raw_rbp_10(double,double,double,double,double,double,double);
extern double rawcall_rbp_10(void);
extern double __vectorcall raw_rbp_11(double,double,double,double,double,double,double);
extern double rawcall_rbp_11(void);
extern double __vectorcall raw_rbp_12(double,double,double,double,double,double,double);
extern double rawcall_rbp_12(void);
extern double __vectorcall raw_rbp_13(double,double,double,double,double,double,double);
extern double rawcall_rbp_13(void);
extern double __vectorcall raw_rbp_14(double,double,double,double,double,double,double);
extern double rawcall_rbp_14(void);
extern double __vectorcall raw_rbp_15(double,double,double,double,double,double,double);
extern double rawcall_rbp_15(void);
int main(void){int failed=0;double got;SetErrorMode(SEM_FAILCRITICALERRORS|SEM_NOGPFAULTERRORBOX);
got=multi_rsp_1();if(got!=25){printf("multi_rsp_1: %g expected 25\n",got);failed++;}
got=reg128_rsp_1();if(got!=26){printf("reg128_rsp_1: %g expected 26\n",got);failed++;}
got=reg256_rsp_1();if(got!=37){printf("reg256_rsp_1: %g expected 37\n",got);failed++;}
got=referential_rsp_1();if(got!=77){printf("referential_rsp_1: %g expected 77\n",got);failed++;}
got=multi_rsp_3();if(got!=25){printf("multi_rsp_3: %g expected 25\n",got);failed++;}
got=reg128_rsp_3();if(got!=26){printf("reg128_rsp_3: %g expected 26\n",got);failed++;}
got=reg256_rsp_3();if(got!=37){printf("reg256_rsp_3: %g expected 37\n",got);failed++;}
got=referential_rsp_3();if(got!=77){printf("referential_rsp_3: %g expected 77\n",got);failed++;}
got=multi_rsp_5();if(got!=25){printf("multi_rsp_5: %g expected 25\n",got);failed++;}
got=reg128_rsp_5();if(got!=26){printf("reg128_rsp_5: %g expected 26\n",got);failed++;}
got=reg256_rsp_5();if(got!=37){printf("reg256_rsp_5: %g expected 37\n",got);failed++;}
got=referential_rsp_5();if(got!=77){printf("referential_rsp_5: %g expected 77\n",got);failed++;}
got=multi_rsp_7();if(got!=25){printf("multi_rsp_7: %g expected 25\n",got);failed++;}
got=reg128_rsp_7();if(got!=26){printf("reg128_rsp_7: %g expected 26\n",got);failed++;}
got=reg256_rsp_7();if(got!=37){printf("reg256_rsp_7: %g expected 37\n",got);failed++;}
got=referential_rsp_7();if(got!=77){printf("referential_rsp_7: %g expected 77\n",got);failed++;}
got=multi_rsp_11();if(got!=25){printf("multi_rsp_11: %g expected 25\n",got);failed++;}
got=reg128_rsp_11();if(got!=26){printf("reg128_rsp_11: %g expected 26\n",got);failed++;}
got=reg256_rsp_11();if(got!=37){printf("reg256_rsp_11: %g expected 37\n",got);failed++;}
got=referential_rsp_11();if(got!=77){printf("referential_rsp_11: %g expected 77\n",got);failed++;}
got=multi_rsp_15();if(got!=25){printf("multi_rsp_15: %g expected 25\n",got);failed++;}
got=reg128_rsp_15();if(got!=26){printf("reg128_rsp_15: %g expected 26\n",got);failed++;}
got=reg256_rsp_15();if(got!=37){printf("reg256_rsp_15: %g expected 37\n",got);failed++;}
got=referential_rsp_15();if(got!=77){printf("referential_rsp_15: %g expected 77\n",got);failed++;}
got=multi_rbp_1();if(got!=25){printf("multi_rbp_1: %g expected 25\n",got);failed++;}
got=reg128_rbp_1();if(got!=26){printf("reg128_rbp_1: %g expected 26\n",got);failed++;}
got=reg256_rbp_1();if(got!=37){printf("reg256_rbp_1: %g expected 37\n",got);failed++;}
got=referential_rbp_1();if(got!=77){printf("referential_rbp_1: %g expected 77\n",got);failed++;}
got=multi_rbp_3();if(got!=25){printf("multi_rbp_3: %g expected 25\n",got);failed++;}
got=reg128_rbp_3();if(got!=26){printf("reg128_rbp_3: %g expected 26\n",got);failed++;}
got=reg256_rbp_3();if(got!=37){printf("reg256_rbp_3: %g expected 37\n",got);failed++;}
got=referential_rbp_3();if(got!=77){printf("referential_rbp_3: %g expected 77\n",got);failed++;}
got=multi_rbp_5();if(got!=25){printf("multi_rbp_5: %g expected 25\n",got);failed++;}
got=reg128_rbp_5();if(got!=26){printf("reg128_rbp_5: %g expected 26\n",got);failed++;}
got=reg256_rbp_5();if(got!=37){printf("reg256_rbp_5: %g expected 37\n",got);failed++;}
got=referential_rbp_5();if(got!=77){printf("referential_rbp_5: %g expected 77\n",got);failed++;}
got=multi_rbp_7();if(got!=25){printf("multi_rbp_7: %g expected 25\n",got);failed++;}
got=reg128_rbp_7();if(got!=26){printf("reg128_rbp_7: %g expected 26\n",got);failed++;}
got=reg256_rbp_7();if(got!=37){printf("reg256_rbp_7: %g expected 37\n",got);failed++;}
got=referential_rbp_7();if(got!=77){printf("referential_rbp_7: %g expected 77\n",got);failed++;}
got=multi_rbp_11();if(got!=25){printf("multi_rbp_11: %g expected 25\n",got);failed++;}
got=reg128_rbp_11();if(got!=26){printf("reg128_rbp_11: %g expected 26\n",got);failed++;}
got=reg256_rbp_11();if(got!=37){printf("reg256_rbp_11: %g expected 37\n",got);failed++;}
got=referential_rbp_11();if(got!=77){printf("referential_rbp_11: %g expected 77\n",got);failed++;}
got=multi_rbp_15();if(got!=25){printf("multi_rbp_15: %g expected 25\n",got);failed++;}
got=reg128_rbp_15();if(got!=26){printf("reg128_rbp_15: %g expected 26\n",got);failed++;}
got=reg256_rbp_15();if(got!=37){printf("reg256_rbp_15: %g expected 37\n",got);failed++;}
got=referential_rbp_15();if(got!=77){printf("referential_rbp_15: %g expected 77\n",got);failed++;}
got=raw_rsp_1(1,2,3,4,5,6,7);if(got!=28){printf("raw_rsp_1: %g expected 28\n",got);failed++;}
got=rawcall_rsp_1();if(got!=28){printf("rawcall_rsp_1: %g expected 28\n",got);failed++;}
got=raw_rsp_2(1,2,3,4,5,6,7);if(got!=28){printf("raw_rsp_2: %g expected 28\n",got);failed++;}
got=rawcall_rsp_2();if(got!=28){printf("rawcall_rsp_2: %g expected 28\n",got);failed++;}
got=raw_rsp_3(1,2,3,4,5,6,7);if(got!=28){printf("raw_rsp_3: %g expected 28\n",got);failed++;}
got=rawcall_rsp_3();if(got!=28){printf("rawcall_rsp_3: %g expected 28\n",got);failed++;}
got=raw_rsp_4(1,2,3,4,5,6,7);if(got!=28){printf("raw_rsp_4: %g expected 28\n",got);failed++;}
got=rawcall_rsp_4();if(got!=28){printf("rawcall_rsp_4: %g expected 28\n",got);failed++;}
got=raw_rsp_5(1,2,3,4,5,6,7);if(got!=28){printf("raw_rsp_5: %g expected 28\n",got);failed++;}
got=rawcall_rsp_5();if(got!=28){printf("rawcall_rsp_5: %g expected 28\n",got);failed++;}
got=raw_rsp_6(1,2,3,4,5,6,7);if(got!=28){printf("raw_rsp_6: %g expected 28\n",got);failed++;}
got=rawcall_rsp_6();if(got!=28){printf("rawcall_rsp_6: %g expected 28\n",got);failed++;}
got=raw_rsp_7(1,2,3,4,5,6,7);if(got!=28){printf("raw_rsp_7: %g expected 28\n",got);failed++;}
got=rawcall_rsp_7();if(got!=28){printf("rawcall_rsp_7: %g expected 28\n",got);failed++;}
got=raw_rsp_8(1,2,3,4,5,6,7);if(got!=28){printf("raw_rsp_8: %g expected 28\n",got);failed++;}
got=rawcall_rsp_8();if(got!=28){printf("rawcall_rsp_8: %g expected 28\n",got);failed++;}
got=raw_rsp_9(1,2,3,4,5,6,7);if(got!=28){printf("raw_rsp_9: %g expected 28\n",got);failed++;}
got=rawcall_rsp_9();if(got!=28){printf("rawcall_rsp_9: %g expected 28\n",got);failed++;}
got=raw_rsp_10(1,2,3,4,5,6,7);if(got!=28){printf("raw_rsp_10: %g expected 28\n",got);failed++;}
got=rawcall_rsp_10();if(got!=28){printf("rawcall_rsp_10: %g expected 28\n",got);failed++;}
got=raw_rsp_11(1,2,3,4,5,6,7);if(got!=28){printf("raw_rsp_11: %g expected 28\n",got);failed++;}
got=rawcall_rsp_11();if(got!=28){printf("rawcall_rsp_11: %g expected 28\n",got);failed++;}
got=raw_rsp_12(1,2,3,4,5,6,7);if(got!=28){printf("raw_rsp_12: %g expected 28\n",got);failed++;}
got=rawcall_rsp_12();if(got!=28){printf("rawcall_rsp_12: %g expected 28\n",got);failed++;}
got=raw_rsp_13(1,2,3,4,5,6,7);if(got!=28){printf("raw_rsp_13: %g expected 28\n",got);failed++;}
got=rawcall_rsp_13();if(got!=28){printf("rawcall_rsp_13: %g expected 28\n",got);failed++;}
got=raw_rsp_14(1,2,3,4,5,6,7);if(got!=28){printf("raw_rsp_14: %g expected 28\n",got);failed++;}
got=rawcall_rsp_14();if(got!=28){printf("rawcall_rsp_14: %g expected 28\n",got);failed++;}
got=raw_rsp_15(1,2,3,4,5,6,7);if(got!=28){printf("raw_rsp_15: %g expected 28\n",got);failed++;}
got=rawcall_rsp_15();if(got!=28){printf("rawcall_rsp_15: %g expected 28\n",got);failed++;}
got=raw_rbp_1(1,2,3,4,5,6,7);if(got!=28){printf("raw_rbp_1: %g expected 28\n",got);failed++;}
got=rawcall_rbp_1();if(got!=28){printf("rawcall_rbp_1: %g expected 28\n",got);failed++;}
got=raw_rbp_2(1,2,3,4,5,6,7);if(got!=28){printf("raw_rbp_2: %g expected 28\n",got);failed++;}
got=rawcall_rbp_2();if(got!=28){printf("rawcall_rbp_2: %g expected 28\n",got);failed++;}
got=raw_rbp_3(1,2,3,4,5,6,7);if(got!=28){printf("raw_rbp_3: %g expected 28\n",got);failed++;}
got=rawcall_rbp_3();if(got!=28){printf("rawcall_rbp_3: %g expected 28\n",got);failed++;}
got=raw_rbp_4(1,2,3,4,5,6,7);if(got!=28){printf("raw_rbp_4: %g expected 28\n",got);failed++;}
got=rawcall_rbp_4();if(got!=28){printf("rawcall_rbp_4: %g expected 28\n",got);failed++;}
got=raw_rbp_5(1,2,3,4,5,6,7);if(got!=28){printf("raw_rbp_5: %g expected 28\n",got);failed++;}
got=rawcall_rbp_5();if(got!=28){printf("rawcall_rbp_5: %g expected 28\n",got);failed++;}
got=raw_rbp_6(1,2,3,4,5,6,7);if(got!=28){printf("raw_rbp_6: %g expected 28\n",got);failed++;}
got=rawcall_rbp_6();if(got!=28){printf("rawcall_rbp_6: %g expected 28\n",got);failed++;}
got=raw_rbp_7(1,2,3,4,5,6,7);if(got!=28){printf("raw_rbp_7: %g expected 28\n",got);failed++;}
got=rawcall_rbp_7();if(got!=28){printf("rawcall_rbp_7: %g expected 28\n",got);failed++;}
got=raw_rbp_8(1,2,3,4,5,6,7);if(got!=28){printf("raw_rbp_8: %g expected 28\n",got);failed++;}
got=rawcall_rbp_8();if(got!=28){printf("rawcall_rbp_8: %g expected 28\n",got);failed++;}
got=raw_rbp_9(1,2,3,4,5,6,7);if(got!=28){printf("raw_rbp_9: %g expected 28\n",got);failed++;}
got=rawcall_rbp_9();if(got!=28){printf("rawcall_rbp_9: %g expected 28\n",got);failed++;}
got=raw_rbp_10(1,2,3,4,5,6,7);if(got!=28){printf("raw_rbp_10: %g expected 28\n",got);failed++;}
got=rawcall_rbp_10();if(got!=28){printf("rawcall_rbp_10: %g expected 28\n",got);failed++;}
got=raw_rbp_11(1,2,3,4,5,6,7);if(got!=28){printf("raw_rbp_11: %g expected 28\n",got);failed++;}
got=rawcall_rbp_11();if(got!=28){printf("rawcall_rbp_11: %g expected 28\n",got);failed++;}
got=raw_rbp_12(1,2,3,4,5,6,7);if(got!=28){printf("raw_rbp_12: %g expected 28\n",got);failed++;}
got=rawcall_rbp_12();if(got!=28){printf("rawcall_rbp_12: %g expected 28\n",got);failed++;}
got=raw_rbp_13(1,2,3,4,5,6,7);if(got!=28){printf("raw_rbp_13: %g expected 28\n",got);failed++;}
got=rawcall_rbp_13();if(got!=28){printf("rawcall_rbp_13: %g expected 28\n",got);failed++;}
got=raw_rbp_14(1,2,3,4,5,6,7);if(got!=28){printf("raw_rbp_14: %g expected 28\n",got);failed++;}
got=rawcall_rbp_14();if(got!=28){printf("rawcall_rbp_14: %g expected 28\n",got);failed++;}
got=raw_rbp_15(1,2,3,4,5,6,7);if(got!=28){printf("raw_rbp_15: %g expected 28\n",got);failed++;}
got=rawcall_rbp_15();if(got!=28){printf("rawcall_rbp_15: %g expected 28\n",got);failed++;}
printf("Vectorcall edge cases: 108 checks, %d failures\n",failed);return failed!=0;}
