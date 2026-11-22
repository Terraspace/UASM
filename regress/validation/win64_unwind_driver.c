/* Windows x64 conformance check. Single-step real UASM frames and ask Windows
 * to unwind a COPY of the context at every instruction boundary, including
 * partial prologues/epilogues. No debugger or third-party libraries required.
 * See win64_unwind.cmd. */
#include <windows.h>
#include <stdio.h>
#include <string.h>

extern void RunUnwind(void (*fn)(void));
extern void (*UnwindCases[])(void);
extern unsigned long long UnwindCaseCount;
extern unsigned long long UnwindFailures;
static DWORD64 image, begin, end, return_pc, entry_rsp;
static PRUNTIME_FUNCTION function;
static CONTEXT entry;
static unsigned checks, failures, started, finished, case_number;

static LONG CALLBACK step(EXCEPTION_POINTERS *ep)
{
    CONTEXT *live = ep->ContextRecord;
    CONTEXT copy;
    DWORD64 frame;
    PVOID handler;
    int good;
    if (ep->ExceptionRecord->ExceptionCode != EXCEPTION_SINGLE_STEP) {
        fprintf(stderr, "Exception %lx case %u pc %llx offset %lld\n", ep->ExceptionRecord->ExceptionCode, case_number, live->Rip, (long long)(live->Rip-begin));
        return EXCEPTION_CONTINUE_SEARCH;
    }
    live->EFlags |= 0x100;
    if (live->Rip == begin && !started) {
        entry = *live;
        entry_rsp = live->Rsp;
        return_pc = *(DWORD64 *)live->Rsp;
        started = 1;
    }
    if (started && live->Rip == return_pc) {
        live->EFlags &= ~0x100;
        finished = 1;
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    if (started && live->Rip >= begin && live->Rip < end) {
        unsigned char *unwind = (unsigned char *)(image + function->UnwindData);
        if (live->Rip == begin + unwind[1] && (live->Rsp & 15)) {
            fprintf(stderr, "Unaligned body RSP in case %u\n", case_number);
            failures++;
        }
        copy = *live;
        __try {
            RtlVirtualUnwind(UNW_FLAG_NHANDLER, image, copy.Rip, function,
                            &copy, &handler, &frame, NULL);
        } __except(EXCEPTION_EXECUTE_HANDLER) {
            fprintf(stderr, "Unwind fault case %u offset %llu, rsp delta %lld\n",
                    case_number, live->Rip - begin, (long long)(live->Rsp-entry_rsp));
            ExitProcess(2);
        }
        good = copy.Rip == return_pc && copy.Rsp == entry_rsp + 8 &&
            copy.Rbx == entry.Rbx && copy.Rbp == entry.Rbp &&
            copy.Rsi == entry.Rsi && copy.Rdi == entry.Rdi &&
            copy.R12 == entry.R12 && copy.R13 == entry.R13 &&
            copy.R14 == entry.R14 && copy.R15 == entry.R15 &&
            memcmp(&copy.Xmm6, &entry.Xmm6, 10 * sizeof(M128A)) == 0;
        checks++;
        if (!good) {
            if (failures < 20)
                printf("FAIL case %u offset %llu: RIP %llx/%llx RSP %llx/%llx RBX %llx/%llx\n",
                    case_number, live->Rip - begin, copy.Rip, return_pc,
                    copy.Rsp, entry_rsp + 8, copy.Rbx, entry.Rbx);
            failures++;
        }
    }
    return EXCEPTION_CONTINUE_EXECUTION;
}

int main(void)
{
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
    PVOID veh = AddVectoredExceptionHandler(1, step);
    if (!veh) return 2;
    for (case_number = 0; case_number < UnwindCaseCount; case_number++) {
        begin = (DWORD64)UnwindCases[case_number];
        function = RtlLookupFunctionEntry(begin, &image, NULL);
        if (!function) { fprintf(stderr, "Missing unwind record: %u\n", case_number); return 2; }
        end = image + function->EndAddress;
        started = finished = 0;
        RunUnwind(UnwindCases[case_number]);
        if (!started || !finished) { fprintf(stderr, "Trace incomplete: %u\n", case_number); return 2; }
    }
    RemoveVectoredExceptionHandler(veh);
    printf("Win64 unwind: %llu frames, %u instruction boundaries, %u failures\n",
           UnwindCaseCount, checks, failures);
    printf("Parameter/local/call-alignment assertion failures: %llu\n", UnwindFailures);
    return failures != 0 || UnwindFailures != 0;
}
