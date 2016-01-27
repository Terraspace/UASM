
;--- test .SAFESEH directive
;--- the assembler must be called with -coff and -safeseh

;--- problems:
;--- polink creates a faulty reference to the load config dir.

    .386
    .model flat, stdcall
    option dotname

    .safeseh exc_handler1
    .safeseh exc_handler2
    .safeseh exc_handler3

.drectve segment info discard
;--- the MS linker emits a warning telling that it will
;--- ignore the directive if it is supplied via .drectve.
;   db "-subsystem:console -safeseh"
    db "-subsystem:console"
.drectve ends

DWORD_PTR typedef ptr
PVOID     typedef ptr

;--- two externals resolved by the linker

extern __safe_se_handler_table:ptr   ; base of safe handler entry table
extern __safe_se_handler_count:BYTE  ;

IMAGE_LOAD_CONFIG_DIRECTORY32_2 struct
Size_             DWORD ?
TimeDateStamp     DWORD ?
MajorVersion      WORD  ?
MinorVersion      WORD  ?
GlobalFlagsClear  DWORD ?
GlobalFlagsSet    DWORD ?
CriticalSectionDefaultTimeout DWORD ?
DeCommitFreeBlockThreshold    DWORD ?
DeCommitTotalFreeThreshold    DWORD ?
LockPrefixTable         DWORD ? ; VA
MaximumAllocationSize   DWORD ?
VirtualMemoryThreshold  DWORD ?
ProcessHeapFlags        DWORD ?
ProcessAffinityMask     DWORD ?
CSDVersion              WORD  ?
Reserved1               WORD  ?
EditList                DWORD ? ; VA
SecurityCookie          DWORD_PTR  ?
SEHandlerTable          PVOID ?
SEHandlerCount          DWORD ?
IMAGE_LOAD_CONFIG_DIRECTORY32_2 ends

    .data

__security_cookie DWORD 0             ; /GS security cookie

;--- linker will search for public symbol _load_config_used!

    public _load_config_used

_load_config_used IMAGE_LOAD_CONFIG_DIRECTORY32_2 {\
    sizeof IMAGE_LOAD_CONFIG_DIRECTORY32_2, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, offset __security_cookie,
    offset __safe_se_handler_table,
    offset __safe_se_handler_count }

exc_handler3 proto	;third handler is an external

    .code

exc_handler1 proc
    ret
exc_handler1 endp

exc_handler2 proc
    ret
exc_handler2 endp

start:
    ret

    end start

