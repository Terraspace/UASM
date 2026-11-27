# Language, types and namespaces

## Data and pointers

Use MASM-style Intel syntax: destination first; `;` comments; `.data`, `.data?`, `.const`, `.code`; `db/dw/dd/dq` or BYTE/WORD/DWORD/QWORD; REAL4/REAL8 for floating data. `?` and LOCAL storage do not initialize memory. Arrays use `DUP`; offsets in memory expressions are byte offsets, not automatically C-scaled indexes. Use `SIZEOF`, `TYPE`, `LENGTHOF`, `OFFSET`, `ADDR` according to the operand/context.

```asm
Pair STRUCT
    first DWORD ?
    second DWORD ?
Pair ENDS
PPair TYPEDEF PTR Pair
.data
pairData Pair <5,7>
.code
ReadPair PROC p:PPair
    LOCAL temp:Pair
    mov rax,p
    mov eax,[rax].Pair.first
    mov temp.first,eax
    ret
ReadPair ENDP
```

This fragment needs target/ABI options; complete files are in assets/examples. STRUC is also supported; UNION shares storage. TYPEDEF can alias data or pointer types; RECORD defines bit fields, not a C struct layout. Match SDK packing and field widths explicitly. A pointer variable is storage containing an address: load the pointer before accessing its pointee. `ASSUME rbx:PTR Pair` supplies type information, not a runtime assignment; clear it with `ASSUME rbx:NOTHING` when no longer true. Typed access includes `[rbx].Pair.first` and `(Pair PTR [rbx]).first`; see the assembled language probe.

## Procedures and HLL

Write `Name PROC ...` / `Name ENDP`. Parameters are `name:type`; LOCAL declarations precede instructions. `USES` requests preservation of named registers through generated frames; it does not preserve every volatile register for you. Use `.IF/.ELSEIF/.ELSE/.ENDIF`, `.WHILE/.ENDW`, `.REPEAT/.UNTIL` for assembler-generated control flow. Conditions operate on machine values; they do not turn integer CMP into a floating comparison. Use UCOMISS/UCOMISD and appropriate branches for floating values, including unordered handling when needed.

Keep side-effecting calls out of relocated HLL condition expressions: in particular nested-call handling rejects inline calls in .WHILE/.ELSEIF. Compute values in explicit statements and test them. UASM is not a C expression compiler with general short-circuit call evaluation.

## Namespaces

```asm
option casemap:none
option proc:private
namespace Math
    bias EQU 3
    namespace Detail
        ; declarations belong to Math::Detail
    endnamespace
endnamespace
```

- NAMESPACE name / ENDNAMESPACE nest and reopen scopes. Define symbols inside blocks; do not define them with qualified names in arbitrary scopes.
- Unqualified lookup: procedure locals/parameters, current namespace, enclosing namespaces, global. Local/parameter shadowing is intentional.
- `A::B::name` qualifies lookup; `::name` explicitly starts globally. Once a qualified scope is selected, a missing member must not fall back to an unrelated parent member.
- Includes inherit the current namespace and must balance scope on return.
- Do not enter/leave namespaces inside PROC, STRUCT/STRUC/UNION or MACRO definitions. NAMESPACE and ENDNAMESPACE are contextual identifiers in these non-directive/member contexts, so fields and arguments named NameSpace remain valid. This exemption does not apply to all directives.
- Namespaces are enabled in this snapshot without an OPTION NAMESPACES switch. FASTPASS is supported; do not disable it merely because namespaces are used.
- Legacy public/unscoped labels need a separation: `Label:: MacroCall`. `Label::MacroCall` is a qualified name. Existing register-pair syntax such as `edx::eax` remains distinct.

### Macros and linkage

Macros use `name MACRO ...` / ENDM, with EXITM for macro functions and normal MASM text-substitution rules. A macro's unqualified references resolve at its expansion site, not permanently in the namespace where defined. Qualify references that must bind to a specific namespace. MACRO parameters and macro-local labels are not runtime PROC locals.

PROTO and its definition should be in the same namespace; put the shared declaration in a balanced include. `PUBLIC` and `EXTERN` remain declarations in the relevant source scope, while their external names use the ordinary leaf name and calling-convention decoration. They are not automatically moved into global source scope and there is no C++ namespace name mangling. Two public leaf names can still collide at link time. Use OPTION PROC:PRIVATE for internal same-leaf procedures; explicitly PUBLIC the intended exports. The namespace example demonstrates cross-object calls with private duplicate Calculate procedures.

## Literals in calls

`OPTION LITERALS:ON` enables direct `"text"` and `L"text"` arguments in INVOKE and C-style calls. Wide literals use UTF-16. Supported backslash escapes are only `\n`, `\r`, `\t`; other backslashes are preserved. Use MASM doubled quotes for embedded quotes, not C backslash-quote. Generated strings are NUL-terminated. Identical decoded strings of the same width share module-owned storage; do not assume unique addresses or modify borrowed literal storage. The standalone literal probe covers both call spellings.
