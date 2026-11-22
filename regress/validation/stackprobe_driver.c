/* Windows runtime validation: fresh 4KB-commit threads, ABI preservation,
 * and RtlVirtualUnwind at helper prologue/body/epilogue instruction boundaries.
 * No external test libraries. See README.txt for the build command. */
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
typedef void (*probe_fn)(void);
extern void RunProbe(probe_fn, uint64_t *);
extern void probe_m1(void);
extern void probe_m2(void);
extern void probe_m3(void);
extern void probe_m4(void);
extern void probe_m5(void);
extern void probe_m6(void);
extern void probe_m7(void);
extern void probe_m8(void);
extern void probe_m9(void);
extern void probe_m10(void);
extern void probe_m11(void);
extern void probe_m12(void);
extern void probe_m13(void);
extern void probe_m14(void);
extern void probe_m15(void);
static probe_fn probes[] = {probe_m1,probe_m2,probe_m3,probe_m4,probe_m5,probe_m6,probe_m7,probe_m8,probe_m9,probe_m10,probe_m11,probe_m12,probe_m13,probe_m14,probe_m15};
static DWORD WINAPI exercise(void *arg) {
    uint64_t out[19] = {0};
    const uint64_t expected[] = {0x456789ab,0x11223344,0x55667788,
                                0x12345678,0x23456789,0x3456789a};
    unsigned i;
    RunProbe(probes[(size_t)arg], out);
    for (i=0;i<6;++i) if(out[i]!=expected[i]) return 10+i;
    if ((out[6]&0x8d5)!=0x45) return 20; /* OF/SF/ZF/AF/PF/CF */
    for (i=7;i<19;++i) if(out[i]!=UINT64_MAX) return 30+i;
    return 0;
}
static int unwind_helper(void) {
    DWORD64 image, frame;
    PRUNTIME_FUNCTION fn, caller;
    PVOID handler;
    unsigned char *code=(unsigned char *)probes[0], *helper=NULL;
    uint64_t stack[64]={0}, *entry=&stack[48];
    const uint64_t saved_rbp=0x123456789abcdef0ULL, return_pc=0x87654321;
    unsigned i, len;
    /* Locate the direct helper call within the first caller's prologue. */
    caller=RtlLookupFunctionEntry((DWORD64)code,&image,NULL);
    if(!caller) return 1;
    len=*((unsigned char *)(image+caller->UnwindData)+1);
    for(i=0;i+5<=len;++i) if(code[i]==0xe8) {
        int32_t rel; memcpy(&rel,code+i+1,4); helper=code+i+5+rel; break;
    }
    if(!helper) return 2;
    fn=RtlLookupFunctionEntry((DWORD64)helper,&image,NULL);
    if(!fn) return 3;
    len=fn->EndAddress-fn->BeginAddress;
    entry[0]=return_pc; entry[-1]=saved_rbp; entry[-2]=0x202;
    /* Instruction boundaries around every change to the helper's stack/frame. */
    for(i=0;i<9;++i) {
        CONTEXT ctx={0};
        unsigned offsets[9]={0,1,2,7,12,0,0,0,0};
        offsets[5]=len-7; /* popfq, transient pushed flags still on stack */
        offsets[6]=len-6; /* lea rsp,[rbp] */
        offsets[7]=len-2; /* pop rbp */
        offsets[8]=len-1; /* ret */
        ctx.Rip=(DWORD64)(helper+offsets[i]);
        ctx.Rbp=i<4 ? saved_rbp : (DWORD64)(entry-1);
        ctx.Rsp=(DWORD64)(entry-(i==0 ? 0 : i==1 ? 1 : i==2 ? 2 : 5));
        if(i==5) ctx.Rsp=(DWORD64)(entry-6);
        if(i==7) ctx.Rsp=(DWORD64)(entry-1);
        if(i==8) {ctx.Rsp=(DWORD64)entry;ctx.Rbp=saved_rbp;}
        RtlVirtualUnwind(UNW_FLAG_NHANDLER,image,ctx.Rip,fn,&ctx,&handler,&frame,NULL);
        if(ctx.Rip!=return_pc || ctx.Rsp!=(DWORD64)(entry+1) || ctx.Rbp!=saved_rbp) {
            printf("helper unwind failed at offset %u\n",offsets[i]); return 4;
        }
    }
    return 0;
}
int main(void) {
    unsigned i;
    for(i=0;i<15;++i) {
        DWORD result=1;
        HANDLE t=CreateThread(NULL,4096,exercise,(void *)(size_t)i,0,NULL);
        if(!t) return 1;
        WaitForSingleObject(t,INFINITE);
        GetExitCodeThread(t,&result);CloseHandle(t);
        if(result) {printf("WIN64:%u failed: %lu\n",i+1,result);return 1;}
    }
    {int u=unwind_helper(); if(u) {printf("unwind result: %d\n",u);return 1;}}
    puts("PASS: WIN64:1-15, fresh-thread stack growth, registers/flags, helper unwind");
    return 0;
}
