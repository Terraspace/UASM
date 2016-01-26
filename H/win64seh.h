
/* some structures for Win64 SEH */

/* .pdata items */

typedef struct _IMAGE_RUNTIME_FUNCTION_ENTRY
{
    uint_32 BeginAddress;
    uint_32 EndAddress;
    uint_32 UnwindData; /* RVA of UNWIND_INFO */
} IMAGE_RUNTIME_FUNCTION_ENTRY;

/* .xdata items */

enum {
    UWOP_PUSH_NONVOL     = 0, /* .PUSHREG    - push nonvolative gpr */
    UWOP_ALLOC_LARGE     = 1, /* .ALLOCSTACK - alloc large-sized area on stack */
    UWOP_ALLOC_SMALL     = 2, /* .ALLOCSTACK - alloc small-sized area (8-128) on stack */
    UWOP_SET_FPREG       = 3, /* .SETFRAME   - set frame pointer */
    UWOP_SAVE_NONVOL     = 4, /* .SAVEREG    - save nonvolative gpr using MOV instead of PUSH */
    UWOP_SAVE_NONVOL_FAR = 5, /* .SAVEREG    - save nonvolative gpr using MOV instead of PUSH */
    UWOP_SAVE_XMM        = 6, /* */
    UWOP_SAVE_XMM_FAR    = 7, /* */
    UWOP_SAVE_XMM128     = 8, /* .SAVEXMM128 - save all 128bits of nonvolative XMM register on stack */
    UWOP_SAVE_XMM128_FAR = 9, /* .SAVEXMM128 - save all 128bits of nonvolative XMM register on stack */
    UWOP_PUSH_MACHFRAME  = 10 /* .PUSHFRAME  - push a machine frame ( SS, RSP, EFL, CS, RIP [ERRCODE] ) */
};

typedef union _UNWIND_CODE {
    struct {
        uint_8 CodeOffset;    /* offset within prolog */
        uint_8 UnwindOp : 4;  /* see UWOP_ values */
        uint_8 OpInfo   : 4;
    };
    uint_16 FrameOffset;
} UNWIND_CODE;

enum {
    UNW_FLAG_NHANDLER = 0,
    UNW_FLAG_EHANDLER = 1, /* function to examine exceptions */
    UNW_FLAG_UHANDLER = 2, /* function to unwind an exception */
    UNW_FLAG_FHANDLER = 3, /* inofficial, is E+U */
    UNW_FLAG_CHAININFO = 4
};

typedef struct _UNWIND_INFO {
    uint_8 Version       : 3; /* is 1 */
    uint_8 Flags         : 5; /* see UNW_FLAG_ values */
    uint_8 SizeOfProlog;      /* size of prolog in bytes */
    uint_8 CountOfCodes;      /* number of UNWIND_CODE entries */
    uint_8 FrameRegister : 4; /* if nonzero, function uses a frame pointer */
    uint_8 FrameOffset   : 4; /* offset frame reg from RSP * 16 */
#if 0
    UNWIND_CODE UnwindCode[1]; /* unwind codes array */
    union {
        uint_32 ExceptionHandler; /* if UNW_FLAG_EHANDLER or UNW_FLAG_UHANDLER is set: RVA of language specific handler */
        uint_32 FunctionEntry;    /* if UNW_FLAG_CHAININFO is set: see IMAGE_RUNTIME_FUNCTION_ENTRY */
    };
    uint_32 ExceptionData[];
#endif
} UNWIND_INFO;

#define UNW_VERSION 1

