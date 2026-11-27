# ABIs and debugging

## Win64

A useful new-project baseline, also used by the supplied samples:

```asm
option casemap:none
option stackbase:rsp
option win64:15
option frame:auto
option arch:sse
```

Use the project's chosen mode rather than overriding it casually. Windows x64 uses RCX/RDX/R8/R9 for the first four integer/pointer argument positions and XMM0–3 for corresponding floating positions, with caller shadow space and correctly aligned call sites. Preserve the ABI's nonvolatile registers you modify, including XMM6–15's required portions. Named homing and USES are generated code, not a reason to ignore the ABI. INVOKE handles supported variadic float duplication; do not independently duplicate/reorder arguments on top of it.

### OPTION WIN64:n, as implemented in this snapshot

Bits: 1 = register parameter saving, 2 = outgoing INVOKE stack allocation, 4 = stack-variable 16-byte alignment, 8 = smart mode. These are implementation flags, not four independent options for every numeric spelling:

| Requested mode | Effective bits | Meaning |
|---|---|---|
| 1 | 1 | Save register parameters |
| 2 | 2 | Automatic outgoing stack space |
| 3 | 1+2 | Both |
| 4 | 4 | Local alignment |
| 5 | 1+4 | Saving + local alignment |
| 6 | 2+4 | Outgoing space + local alignment |
| 7 | 1+2+4 | All three non-smart flags |
| 8–14 | 11 = 1+2+8 | Aliases of smart mode 11 |
| 15 | 15 = 1+2+4+8 | Smart mode plus local alignment |

Smart mode homes parameters when referenced by name and optimizes frame/outgoing allocation. Do not replace it with unconditional copies of every incoming register. Explicit STACKBASE:RBP or RSP is respected, including smart modes; without an explicit choice smart mode retains its historical RSP default. RSP frees RBP but frame offsets, pushes, outgoing space, alignment and unwind records must all agree. Do not assume every low mode independently produces a convenient complete calling frame.

`OPTION STACKPROBE:ON` is the default. Keep probing enabled for large automatic frames on platforms requiring stack guard-page traversal; OFF is an explicit environment-specific opt-out, not a general performance optimization. Probing is internally generated and does not require linking an external probe library.

### Vectorcall and vector saves

Vectorcall supports both explicit RSP and RBP stack bases in this snapshot. Use typed PROTO/PROC VECTORCALL or VECMETHOD contracts; distinguish normal Win64 rules from vectorcall's scalar/vector and homogeneous-aggregate register allocation. When the convention requires an aggregate pointer, UASM intentionally retains its documented referential behaviour: an INVOKE can pass the original storage rather than creating the C/C++ by-value temporary. Copy explicitly when value isolation is required. Varargs and unsupported operand forms must not be assumed valid just because ordinary INVOKE accepts them.

`OPTION ARCH:SSE/AVX` controls generated vector save/load forms; it does not establish that the machine running the program supports AVX. Do not assume the stack is naturally aligned to 32 or 64 bytes for YMM/ZMM operations; use supported unaligned accesses or arrange and verify stronger alignment.

## Linux x86-64 System V

Use `PROC SYSTEMV` / `PROTO SYSTEMV` explicitly in portable examples. Integer/pointer register sequence is RDI, RSI, RDX, RCX, R8, R9; floating arguments use the separate XMM allocation rules. There is no Win64 caller shadow space. Overflow/classified arguments use the stack; arbitrary C aggregates need classification rather than assuming all structs pass like scalars. INVOKE tracks supported call setup and variadic vector count. Do not carry Windows home-space or nonvolatile-XMM assumptions into System V.

`OPTION SYSVHOME:0` is default: register parameters remain register-backed aliases, and named stack parameters refer to their stack locations. Calls can clobber register-backed names. With `OPTION SYSVHOME:1`, parameters referenced by name receive callee-owned stack homes under automatic frame handling. Arguments used only by their incoming registers are not automatically homed. Select the option before PROC. This is not a new ABI and does not require callers to allocate Windows-style homes.

Keep stack alignment and red-zone use consistent with the complete routine. The ABI's red zone is not safe storage across arbitrary nested calls or in kernel/interrupt contexts. Do not invent red-zone frame optimizations independently of the assembler's generated prologue.

## Debug formats and verification

- COFF Win64: assemble `-win64 -Zi8`, link `/DEBUG:FULL /INCREMENTAL:NO`; keep the PDB, sources and binary matching. Samples use normal Visual Studio debugger projects. CV8 contains namespaced types and correct parameter/local locations for supported automatic frames.
- ELF64: `-elf64 -Zi` emits DWARF types, source lines, globals, parameters and locals. `-Zd` is the line-oriented mode; do not treat it as a substitute for full types. `-Zi8` with ELF64 is rejected.
- Automatic System V frames with debug output emit `.debug_frame` and PIC-safe allocated `.eh_frame`. The linker can generate `.eh_frame_hdr`. Stack unwinding support is not a claim of C++ exception cleanup/personality support.
- Stop after prologue/initialization before judging local values. Register-backed arguments may become unavailable or changed after clobbers; SYSVHOME:1 makes intentionally named arguments durable. Uninitialized locals remain meaningless.
- Use GDB for a reproducible Linux baseline: break a source/function, step, inspect args/locals and dereferenced structs, and backtrace across an SO. RAD testing previously reached function breakpoints and F10; F11 into the SO remained problematic. Do not claim that current RAD stepping is universally fixed.

For assembler changes, independently inspect generated unwind/debug records and runtime state; an executable that happens to run does not prove unwind correctness.
