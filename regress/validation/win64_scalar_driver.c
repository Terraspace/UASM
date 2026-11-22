#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <intrin.h>
typedef uint64_t (*sum_fn)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
extern sum_fn ScalarSums[30];
extern uint64_t (*ScalarCalls[30])(void), (*ScalarVariadics[30])(void);
__declspec(noinline) uint64_t scalar_sink(uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t e,uint64_t f) {
    return a+b+c+d+e+f + (((uintptr_t)_AddressOfReturnAddress() & 15) == 8 ? 0 : 10000);
}
uint64_t scalar_variadic(unsigned n,...) {
    static const double expect[] = {1.5,2.5,3.5,1.5,4.5};
    va_list ap; unsigned i; uint64_t bad = n != 5;
    va_start(ap,n); for(i=0;i<5;i++) bad += va_arg(ap,double) != expect[i]; va_end(ap);
    return bad;
}
uint64_t scalar_fixed(double first,...) {
    static const double expect[] = {1.5,3.5,1.5,4.5};
    va_list ap; unsigned i; uint64_t bad = first != 2.5;
    va_start(ap,first); for(i=0;i<4;i++) bad += va_arg(ap,double) != expect[i]; va_end(ap);
    return bad;
}
uint64_t scalar_fixed4(float first,...) {
    static const double expect[] = {2.5,3.5,1.5,4.5};
    va_list ap; unsigned i; uint64_t bad = first != 1.5f;
    va_start(ap,first); for(i=0;i<4;i++) bad += va_arg(ap,double) != expect[i]; va_end(ap);
    return bad;
}
int main(void) {
    unsigned i,failures=0;
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
    for(i=0;i<30;i++) {
        uint64_t s=ScalarSums[i](1,2,3,4,0x100000005ULL,0x200000006ULL), c=ScalarCalls[i]();
        if(s!=0x300000015ULL || c!=220) {printf("FAIL scalar case %u: sum %llx call %llu\n",i,s,c);failures++;}
    }
    for(i=0;i<30;i++) {uint64_t v=ScalarVariadics[i]();if(v){printf("FAIL variadic case %u: %llu\n",i,v);failures++;}}
    printf("Scalar ABI: 30 mode/base pairs, 30 variadic combinations, %u failures\n",failures);
    return failures != 0;
}
