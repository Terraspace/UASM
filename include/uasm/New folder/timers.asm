  ; ---------------------------------------------------------------------
  ; These two macros perform the grunt work involved in measuring the
  ; processor clock cycle count for a block of code. These macros must
  ; be used in pairs, and the block of code must be placed in between
  ; the counter_begin and counter_end macro calls. The counter_end macro
  ; returns the clock cycle count for a single pass through the block of
  ; code, corrected for the test loop overhead, in EAX.
  ;
  ; These macros require a .586 or higher processor directive.
  ;
  ; If your code is using MMX instructions and not executing an EMMS
  ; at the end of each MMX instruction sequence, defining the symbol
  ; _EMMS will cause the ctr_end macro to insert an EMMS in front of
  ; the FPU instructions.
  ;
  ; The loopcount parameter should be set to a relatively high value to
  ; produce repeatable results.
  ;
  ; Note that setting the priority parameter to REALTIME_PRIORITY_CLASS
  ; involves some risk, as it will cause your process to preempt *all*
  ; other processes, including critical Windows processes. Setting the
  ; priority parameter to HIGH_PRIORITY_CLASS instead will significantly
  ; reduce the risk, and in most cases will produce the same cycle count.
  ; ---------------------------------------------------------------------
    counter_begin MACRO loopcount:REQ, priority
        LOCAL label

        IFNDEF __counter__stuff__defined__
          __counter__stuff__defined__ equ <1>
          .data
          ALIGN 8             ;; Optimal alignment for QWORD
            __counter__qword__count__  dq 0
            __counter__loop__count__   dd 0
            __counter__loop__counter__ dd 0
          .code
        ENDIF

        mov __counter__loop__count__, loopcount
        IFNB <priority>
          invoke GetCurrentProcess
          invoke SetPriorityClass, eax, priority
        ENDIF
        xor   eax, eax        ;; Use same CPUID input value for each call
        cpuid                 ;; Flush pipe & wait for pending ops to finish
        rdtsc                 ;; Read Time Stamp Counter

        push  edx             ;; Preserve high-order 32 bits of start count
        push  eax             ;; Preserve low-order 32 bits of start count
        mov   __counter__loop__counter__, loopcount
        xor   eax, eax
        cpuid                 ;; Make sure loop setup instructions finish
      ALIGN 16                ;; Optimal loop alignment for P6
      @@:                     ;; Start an empty reference loop
        sub   __counter__loop__counter__, 1
        jnz   @B

        xor   eax, eax
        cpuid                 ;; Make sure loop instructions finish
        rdtsc                 ;; Read end count
        pop   ecx             ;; Recover low-order 32 bits of start count
        sub   eax, ecx        ;; Low-order 32 bits of overhead count in EAX
        pop   ecx             ;; Recover high-order 32 bits of start count
        sbb   edx, ecx        ;; High-order 32 bits of overhead count in EDX
        push  edx             ;; Preserve high-order 32 bits of overhead count
        push  eax             ;; Preserve low-order 32 bits of overhead count

        xor   eax, eax
        cpuid
        rdtsc
        push  edx             ;; Preserve high-order 32 bits of start count
        push  eax             ;; Preserve low-order 32 bits of start count
        mov   __counter__loop__counter__, loopcount
        xor   eax, eax
        cpuid                 ;; Make sure loop setup instructions finish
      ALIGN 16                ;; Optimal loop alignment for P6
      label:                  ;; Start test loop
        __counter__loop__label__ equ <label>
    ENDM

    counter_end MACRO
        sub   __counter__loop__counter__, 1
        jnz   __counter__loop__label__

        xor   eax, eax
        cpuid                 ;; Make sure loop instructions finish
        rdtsc                 ;; Read end count
        pop   ecx             ;; Recover low-order 32 bits of start count
        sub   eax, ecx        ;; Low-order 32 bits of test count in EAX
        pop   ecx             ;; Recover high-order 32 bits of start count
        sbb   edx, ecx        ;; High-order 32 bits of test count in EDX
        pop   ecx             ;; Recover low-order 32 bits of overhead count
        sub   eax, ecx        ;; Low-order 32 bits of adjusted count in EAX
        pop   ecx             ;; Recover high-order 32 bits of overhead count
        sbb   edx, ecx        ;; High-order 32 bits of adjusted count in EDX

        mov   DWORD PTR __counter__qword__count__, eax
        mov   DWORD PTR __counter__qword__count__ + 4, edx

        invoke GetCurrentProcess
        invoke SetPriorityClass, eax, NORMAL_PRIORITY_CLASS

        IFDEF _EMMS
          EMMS
        ENDIF

        finit
        fild  __counter__qword__count__
        fild  __counter__loop__count__
        fdiv
        fistp __counter__qword__count__

        mov   eax, DWORD PTR __counter__qword__count__
    ENDM

  ; ---------------------------------------------------------------------
  ; These two macros perform the grunt work involved in measuring the
  ; execution time in milliseconds for a specified number of loops
  ; through a block of code. These macros must be used in pairs, and
  ; the block of code must be placed in between the timer_begin and
  ; timer_end macro calls. The timer_end macro returns the elapsed
  ; milliseconds for the entire loop in EAX.
  ;
  ; These macros utilize the high-resolution performance counter.
  ; The return value will be zero if the high-resolution performance
  ; counter is not available.
  ;
  ; If your code is using MMX instructions and not executing an EMMS
  ; at the end of each MMX instruction sequence, defining the symbol
  ; _EMMS will cause the timer_end macro to insert an EMMS in front of
  ; the FPU instructions.
  ;
  ; The loopcount parameter should be set to a relatively high value to
  ; produce repeatable results.
  ;
  ; Note that setting the priority parameter to REALTIME_PRIORITY_CLASS
  ; involves some risk, as it will cause your process to preempt *all*
  ; other processes, including critical Windows processes. Setting the
  ; priority parameter to HIGH_PRIORITY_CLASS instead will significantly
  ; reduce the risk, and in most cases will produce very nearly the same
  ; result.
  ; ---------------------------------------------------------------------
    timer_begin MACRO loopcount:REQ, priority
        LOCAL label

        IFNDEF __timer__stuff__defined__
          __timer__stuff__defined__ equ <1>
          .data
          ALIGN 8             ;; Optimal alignment for QWORD
            __timer__pc__frequency__    dq 0
            __timer__pc__count__        dq 0
            __timer__loop__counter__    dd 0
            __timer__dw_count__         dd 0
          .code
        ENDIF

        invoke QueryPerformanceFrequency, ADDR __timer__pc__frequency__
        .IF eax != 0

            IFNB <priority>
              invoke GetCurrentProcess
              invoke SetPriorityClass, eax, priority
            ENDIF

            invoke QueryPerformanceCounter, ADDR __timer__pc__count__
            push    DWORD PTR __timer__pc__count__ + 4
            push    DWORD PTR __timer__pc__count__

            mov   __timer__loop__counter__, loopcount
          ALIGN 16              ;; Optimal loop alignment for P6
          @@:                   ;; Start an empty reference loop
            sub   __timer__loop__counter__, 1
            jnz   @B

            invoke QueryPerformanceCounter, ADDR __timer__pc__count__

            pop   ecx           ;; Recover low-order 32 bits of start count
            sub   DWORD PTR __timer__pc__count__, ecx
            pop   ecx           ;; Recover high-order 32 bits of start count
            sbb   DWORD PTR __timer__pc__count__ + 4, ecx

            push    DWORD PTR __timer__pc__count__ + 4 ;; Overhead count
            push    DWORD PTR __timer__pc__count__     ;; Overhead count

            invoke QueryPerformanceCounter, ADDR __timer__pc__count__

            push    DWORD PTR __timer__pc__count__ + 4 ;; Start count
            push    DWORD PTR __timer__pc__count__     ;; Start count

            mov   __timer__loop__counter__, loopcount
          ALIGN 16              ;; Optimal loop alignment for P6
          label:                ;; Start test loop
            __timer__loop__label__ equ <label>
        .ENDIF
    ENDM

    timer_end MACRO
        sub   __timer__loop__counter__, 1
        jnz   __timer__loop__label__

        invoke QueryPerformanceFrequency, ADDR __timer__pc__frequency__
        .IF eax != 0

            invoke QueryPerformanceCounter, ADDR __timer__pc__count__
            pop   ecx           ;; Recover low-order 32 bits of start count
            sub   DWORD PTR __timer__pc__count__, ecx
            pop   ecx           ;; Recover high-order 32 bits of start count
            sbb   DWORD PTR __timer__pc__count__ + 4, ecx
            pop   ecx           ;; Recover low-order 32 bits of overhead count
            sub   DWORD PTR __timer__pc__count__, ecx
            pop   ecx           ;; Recover high-order 32 bits of overhead count
            sbb   DWORD PTR __timer__pc__count__ + 4, ecx

            invoke GetCurrentProcess
            invoke SetPriorityClass, eax, NORMAL_PRIORITY_CLASS

            IFDEF _EMMS
              EMMS
            ENDIF

            finit
            fild  __timer__pc__count__
            fild  __timer__pc__frequency__
            fdiv
            mov   __timer__dw_count__, 1000
            fild  __timer__dw_count__
            fmul
            fistp __timer__dw_count__
            mov   eax, __timer__dw_count__
        .ELSE
          xor   eax, eax        ;; No performance counter
        .ENDIF
    ENDM
