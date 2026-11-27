# Typed calls, OO, COM and RAW

## PROC/PROTO and C-style calls

```asm
Sum PROTO (DWORD) first:DWORD,second:DWORD
NextValue PROTO (DWORD)
Sink PROTO (void) value:DWORD
; In an automatic-frame PROC:
Sum(NextValue(),NextValue())
mov result,eax
Sink(result)
```

PROTO `(type)` describes the return contract. Prefer `Run PROTO (DWORD)` followed by `Run PROC FRAME` (parameters still appear on the definition as needed). The current parser also accepts `Run PROC (DWORD) FRAME`, but **not** `Run PROC FRAME (DWORD)`: ordering matters. Use separate `PUBLIC Start` then `Start PROC FRAME`; `PROC FRAME PUBLIC` is rejected. A standalone call can be untyped; a nested call used as a value requires an explicit supported non-void PROC/PROTO return type. Return values still arrive in ABI registers, not a magical expression object. Plain INVOKE and HLL `Name(args)` share call generation; `&local` is the preferred C-style address-of syntax translated to ADDR. ADDR is also accepted in C-style argument lists, but use `&` for consistency; use ADDR with INVOKE. Do not substitute OFFSET for an address of a stack local.

Current nested-call limits:

- Maximum depth three including the outer call on Win32, Win64 and ELF64. Arithmetic grouping is not call depth.
- Left-to-right depth-first execution. Only nested call results are spilled into private automatic caller-frame slots, with up to 32 result slots per statement. Slots are reused across statements; recursion gets distinct stack frames.
- Ordinary memory arguments are read when the enclosing INVOKE runs, after its child calls. They are not snapshots of state at the beginning of the statement.
- A volatile register argument/address that must survive a preceding call is rejected, including aliases and SIMD registers. `Sum(NextValue(),eax)` is unsafe; an argument consumed by the first leaf before a call may be valid. Spill the intended input yourself or rearrange explicit statements.
- Nested result storage requires a PROC with automatic frames; do not use manual/prologue-none frames for it.
- Integers, pointers, REAL4/REAL8 and supported x64 SIMD return contracts are handled. Explicit REAL4/REAL8 contracts use XMM0, including Win32: this does NOT make external Win32 x87-returning C functions compatible. Win32 multi-register QWORD and x87 REAL10 returns are not supported nested-result contracts.
- Refer to the complete nested_calls project for siblings, re-entry, floats, pointers and deliberately rejected forms.

## CLASS and OINTERFACE

```asm
namespace Objects
CLASS Counter
    CMETHOD GetValue
    CSTATIC NextValue
ENDMETHODS
    value DWORD 0
ENDCLASS
METHOD Counter,GetValue,<DWORD>,<>
    mov eax,[rcx].value
    ret
ENDMETHOD
STATICMETHOD Counter,NextValue,<DWORD>,<>,inputValue:DWORD
    mov eax,inputValue
    inc eax
    ret
ENDMETHOD
endnamespace
```

This is the Win64 form; see oo_tour for complete Init/Destroy definitions and allocation. CLASS generates a layout/template, typed method prototypes and a `psrClassName` pointer type. The `<...>` method option field can contain `USES ...`; VECMETHOD and STATICVECMETHOD select vectorcall methods. Instance methods have implicit `thisPtr`; do not assume RCX survives another call. Reload from thisPtr if necessary, following the configured homing rules.

`_NEW(Type,...)` copies the class template, allocates and calls Init. Init must return the constructed object pointer in RAX, even after making other calls. `_DELETE(pointer)` invokes Destroy and releases memory. Ownership, null/error paths and nested owned objects remain the programmer's responsibility. These Windows helpers use heap APIs; declare their prototypes as in oo_tour, including GetProcessHeap/HeapAlloc/HeapFree in the scope the helpers expect. Preserve helper-used nonvolatile registers in the caller: the tour uses RBX/RSI/RDI/R15. Do not assume auto-RAII or inheritance.

`OPTION VTABLE:ON` enables virtual dispatch; OFF selects direct forms where supported. OINTERFACE is a compatible layout view with the CLASS constructor/destructor slots; its order must match the actual object. It is not COM QueryInterface or C++ inheritance. COMINTERFACE has the IUnknown layout instead.

## Arrow access and legacy helpers

Typed OO/COM/RAW pointer globals and LOCALs, ASSUME registers and supported typed pointer-slot memory can dispatch via `obj->Method(...)`. OO-typed fields can chain: `person->company->Adjust(2.0)`. Nested typed method results use the ordinary nested-result rules. Use dot/typed memory for ordinary fields; `plainStruct->field` is not supported.

Do not guess whether a typed-memory form represents an object address or a slot containing an object pointer. Adapt the precise forms in oo_tour. It covers pointer slots, explicit casts, namespace-qualified `_INVOKE`/`_I`, virtual `_VINVOKE`/`_V`, `_STATIC`, no-argument methods and chained calls.

## COM and RAW

COMINTERFACE / ENDCOMINTERFACE model COM's vtable, starting with QueryInterface, AddRef, Release. Additional `CVIRTUAL Method,<ReturnType>,...` entries must exactly match SDK order and signature. QueryInterface has explicit REFIID and output-pointer arguments plus implicit This; HRESULT is a signed 32-bit result. Check failure with signed HRESULT semantics, not merely nonzero. Balance AddRef/Release and COM initialization where required by the APIs used. The Direct2D project supplies the actual interface declarations, factory creation, a Win32 window and drawing/lifetime handling.

RAWINTERFACE / ENDRAWINTERFACE with `STDFUNC Name,<ReturnType>,...` models direct function-pointer tables such as UEFI. It does not insert COM's three methods. Explicit parameters such as This must follow the real API contract; do not add/remove one by analogy with COM. Dispatch uses scratch registers and rejects conflicting live operands: do not silence an R11 conflict diagnostic without inspecting the call. The included RAW probe exercises global and LOCAL pointer receivers and typed nested returns, without requiring firmware or an external EFI include.

When interoping with external code, a plausible prototype is insufficient: verify pointer depth, width, signedness, by-value/by-reference aggregate rules, register convention and return contract against the actual API.

## Verified C-style constant-expression boundary

The reviewed starter's `MessageBoxW(..., MB_OK or MB_ICONERROR)` fails in this snapshot: the argument becomes `MB_OKorMB_ICONERROR`. Adding parentheses does not repair it. Precompute `ERROR_MESSAGE_FLAGS EQU MB_OK or MB_ICONERROR` and pass the constant, or use a separately verified INVOKE form. This is a confirmed assembler bug in preproc.c ExpandHllCalls: token rebuilding loses the separators around OR before the generated INVOKE is rescanned. The intended language supports this expression; it is not a valid language restriction. Report it if it affects the requested task; do not silently change the assembler while writing an application.
