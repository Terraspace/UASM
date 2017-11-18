LPVOID TYPEDEF PTR VOID
EXCEPTION_MAXIMUM_PARAMETERS EQU 15
UNWIND_HISTORY_TABLE_SIZE EQU 12
ExceptionContinueExecution EQU 0
ExceptionContinueSearch	EQU 1

EXCEPTION_NONCONTINUABLE EQU 1    ;; Noncontinuable exception
EXCEPTION_UNWINDING EQU 2         ;; Unwind is in progress
EXCEPTION_EXIT_UNWIND EQU 4       ;; Exit unwind is in progress
EXCEPTION_STACK_INVALID EQU 8     ;; Stack out of limits or unaligned
EXCEPTION_NESTED_CALL EQU 10h     ;; Nested exception handler call
EXCEPTION_TARGET_UNWIND EQU 20h   ;; Target unwind in progress
EXCEPTION_COLLIDED_UNWIND EQU 40h ;; Collided exception handler call
EXCEPTION_UNWIND EQU 66h

UNW_FLAG_NHANDLER  EQU 0
UNW_FLAG_EHANDLER EQU 1
UNW_FLAG_UHANDLER EQU 2
UNW_FLAG_CHAININFO EQU 4

UNW_FLAG_NO_EPILOGUE EQU 80000000h    ;; Software only flag

IMAGE_RUNTIME_FUNCTION_ENTRY STRUCT
    BeginAddress DWORD ?
    EndAddress DWORD ?
    UNION 
        UnwindInfoAddress DWORD ?
        UnwindData DWORD ?
    ENDS
IMAGE_RUNTIME_FUNCTION_ENTRY ENDS 

SCOPE_TABLE STRUCT
	Count DWORD ?
	STRUCT
		BeginAddress DWORD ?
		EndAddress DWORD ?
		HandlerAddress DWORD ?
		JumpTarget DWORD ?
	ENDS
SCOPE_TABLE ENDS

PIMAGE_RUNTIME_FUNCTION_ENTRY TYPEDEF PTR IMAGE_RUNTIME_FUNCTION_ENTRY

UNWIND_HISTORY_TABLE_ENTRY STRUCT
	ImageBase QWORD ?
	FunctionEntry PIMAGE_RUNTIME_FUNCTION_ENTRY ?
UNWIND_HISTORY_TABLE_ENTRY ENDS

UNWIND_HISTORY_TABLE STRUCT
    Count DWORD ?
    LocalHint BYTE ?
    GlobalHint BYTE ?
    Search BYTE ?
    Once BYTE ?
    LowAddress QWORD ?
    HighAddress QWORD ?
    Entry UNWIND_HISTORY_TABLE_ENTRY UNWIND_HISTORY_TABLE_SIZE dup (<>)
UNWIND_HISTORY_TABLE ENDS

DISPATCHER_CONTEXT STRUCT
    ControlPc QWORD ? 
    ImageBase QWORD ?
    FunctionEntry LPVOID ?
    EstablisherFrame QWORD ?
    TargetIp QWORD ?
    ContextRecord LPVOID ?
    LanguageHandler LPVOID ?
    HandlerData LPVOID ?
    HistoryTable LPVOID ?
    ScopeIndex DWORD ?
    Fill0 DWORD ?
DISPATCHER_CONTEXT ENDS

EXCEPTION_RECORD STRUCT
	ExceptionCode DWORD ?
	ExceptionFlags DWORD ?
	ExceptionRecord LPVOID ?
	ExceptionAddress LPVOID ?
	NumberParameters DWORD ?
	ExceptionInformation QWORD EXCEPTION_MAXIMUM_PARAMETERS dup (?)
EXCEPTION_RECORD ENDS

; Must align to 16 bytes
M128A STRUCT 16
    _Low   QWORD ?
    _High  SQWORD ?
M128A ENDS

; Must align to 16 bytes
XMM_SAVE_AREA32 STRUC 16
  ControlWord    WORD ?
  StatusWord    WORD ?
  TagWord      BYTE ?
  Reserved1    BYTE ?
  ErrorOpcode    WORD ?
  ErrorOffset    DWORD ?
  ErrorSelector  WORD ?
  Reserved2    WORD ?
  DataOffset    DWORD ?
  DataSelector  WORD ?
  Reserved3    WORD ?
  MxCsr      DWORD ?
  MxCsr_Mask    DWORD ?

  FloatRegisters  M128A 8 dup(<>)	
  XmmRegisters  M128A 16 dup(<>)
  Reserved4    BYTE 96 dup(?)
XMM_SAVE_AREA32 ENDS

; Must align to 16 bytes
CONTEXT STRUCT 16
	; Register parameter home addresses (for future extension)
	P1Home		QWORD ?
	P2Home		QWORD ?
	P3Home		QWORD ?
	P4Home		QWORD ?
	P5Home		QWORD ?
	P6Home		QWORD ?
	; Control flags.
	ContextFlags	DWORD ?
	MxCsr			DWORD ?
	; Segment Registers and processor flags
	SegCs			WORD ?
	SegDs			WORD ?
	SegEs			WORD ?
	SegFs			WORD ?
	SegGs			WORD ?
	SegSs			WORD ?
	EFlags		DWORD ?
	; Debug registers
	_Dr0			QWORD ?
	_Dr1			QWORD ?
	_Dr2			QWORD ?
	_Dr3			QWORD ?
	_Dr6			QWORD ?
	_Dr7			QWORD ?
	; Integer registers.
	_Rax			QWORD ?
	_Rcx			QWORD ?
	_Rdx			QWORD ?
	_Rbx			QWORD ?
	_Rsp			QWORD ?
	_Rbp			QWORD ?
	_Rsi			QWORD ?
	_Rdi			QWORD ?
	_R8			QWORD ?
	_R9			QWORD ?
	_R10			QWORD ?
	_R11			QWORD ?
	_R12			QWORD ?
	_R13			QWORD ?
	_R14			QWORD ?
	_R15			QWORD ?
	; Program counter.
	_Rip			QWORD ?
	UNION
		FltSave	XMM_SAVE_AREA32 <>
		STRUCT
			Header	M128A 2 dup(<>)
			Legacy	M128A 8 dup(<>)
			_Xmm0		M128A <>
			_Xmm1		M128A <>
			_Xmm2		M128A <>
			_Xmm3		M128A <>
			_Xmm4		M128A <>
			_Xmm5		M128A <>
			_Xmm6		M128A <>
			_Xmm7		M128A <>
			_Xmm8		M128A <>
			_Xmm9		M128A <>
			_Xmm10	M128A <>
			_Xmm11	M128A <>
			_Xmm12	M128A <>
			_Xmm13	M128A <>
			_Xmm14	M128A <>
			_Xmm15	M128A <>		
		ENDS
	ENDS
	; Vector registers.
	VectorRegister		M128A 26 dup(<>)
	VectorControl		QWORD ?
	; Special debug control registers	
	DebugControl		QWORD ?
	LastBranchToRip		QWORD ?
	LastBranchFromRip		QWORD ?
	LastExceptionToRip	QWORD ?
	LastExceptionFromRip	QWORD ?
CONTEXT ENDS

UWOP_PUSH_NONVOL EQU 0		;info == register number 
UWOP_ALLOC_LARGE EQU 1		;no info, alloc size in next 2 slots
UWOP_ALLOC_SMALL EQU 2		;info == size of allocation / 8 - 1
UWOP_SET_FPREG EQU 3		;no info, FP = RSP + UNWIND_INFO.FPRegOffset*16
UWOP_SAVE_NONVOL EQU 4		;info == register number, offset in next slot
UWOP_SAVE_NONVOL_FAR EQU 5	;info == register number, offset in next 2 slots
UWOP_SAVE_XMM128 EQU 6		;info == XMM reg number, offset in next slot
UWOP_SAVE_XMM128_FAR EQU 7	;info == XMM reg number, offset in next 2 slots
UWOP_PUSH_MACHFRAME EQU 8	;info == 0: no error-code, 1: error-code

UNWIND_CODE_REC RECORD OpInfo:4, UnwindOp:4

UNWIND_CODE UNION
    STRUCT  
        CodeOffset BYTE ?  
	  xOp UNWIND_CODE_REC <>
    ENDS
    FrameOffset WORD ?
UNWIND_CODE ENDS

UNWIND_INFO_VERFLAGS RECORD Flags:5, Version:3
UNWIND_FRAME RECORD FrameOffset:4, FrameRegister:4

UNWIND_INFO STRUCT
	x1 UNWIND_INFO_VERFLAGS <>
	SizeOfProlog BYTE ?
	CountOfCodes BYTE ?
	
	x2 UNWIND_FRAME <>
	UnwindCode UNWIND_CODE <>
	
	COMMENT #
	union {
        //
        // If (Flags & UNW_FLAG_EHANDLER)
        //
        OPTIONAL ULONG ExceptionHandler;
        //
        // Else if (Flags & UNW_FLAG_CHAININFO)
        //
        OPTIONAL ULONG FunctionEntry;
	};
	//
	// If (Flags & UNW_FLAG_EHANDLER)
	//
	OPTIONAL ULONG ExceptionData[]; 
	#
UNWIND_INFO ENDS    