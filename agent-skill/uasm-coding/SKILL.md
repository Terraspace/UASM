---
name: uasm-coding
description: Write, review, build and debug UASM assembly using its typed calls, namespaces, HLL constructs, OO/COM/RAW interfaces and Windows or Linux ABIs. Use for UASM application code and porting MASM-style code to UASM.
---

# UASM coding

Target UASM, not a generic MASM/NASM dialect. This pack describes the UASM 2.60 source snapshot recorded in [provenance](references/provenance.md). Check the project's assembler binary and options before relying on newer features; an older binary bearing the same major/minor version may lack fixes.

## Working approach

1. Identify target OS, bitness, object format, calling convention, assembler path and existing build command. Preserve project conventions. Use the bundled sample nearest the task as a syntax reference, not as mandatory architecture.
2. Read only the references needed:
   - [Language and namespaces](references/language.md): declarations, structures, macros, HLL, literal strings, lookup and linkage.
   - [Calls and objects](references/calls-and-objects.md): typed returns, nested calls, OO, COM, RAW and arrow dispatch.
   - [ABI and debugging](references/abi-and-debugging.md): WIN64 modes, stack bases, vectorcall, System V, stack probes and debug formats.
   - [Platforms and builds](references/platforms.md): linking, startup, ELF PIC/PIE, visibility, PLT/GOT and validation.
   - [Example catalog](references/examples.md): complete source-only projects and small probes.
3. Prefer typed PROC/PROTO, INVOKE, namespaces and HLL/OO features when they clarify the requested code. Do not simulate C++ ownership, expression evaluation or arbitrary register preservation that UASM does not provide.
4. Assemble changed code with the intended target flags. For calls, frames or pointer changes, also link/run a bounded test when the target environment is available. Distinguish assembly success, runtime correctness and debugger verification. Do not silently accept freshly generated output as an independent correctness baseline.

## Essential boundaries

- `->` is OO/COM/RAW dispatch, not general C structure dereferencing. Use typed dot/memory operands for ordinary data.
- C-style calls lower to INVOKE; typed nested results have bounded depth and caller-frame spills. Ordinary arguments are not automatically snapshotted. Read the call reference before composing nested expressions.
- Symbol namespaces do not namespace the operating system's exported linker identities. Keep shared PROTO/EXTERN declarations consistent across modules.
- Keep ABI types, alignment, nonvolatile register preservation, ownership and callback lifetime explicit. LOCAL storage is uninitialized.
- Use `-win64 -Zi8` for Windows CV8; `-elf64 -Zi` for Linux DWARF. Do not use `-Zi8` for ELF64.
- No personal include paths, SDK locations, SSH setup or previous-chat state are assumed by this pack. Obtain tool paths from the current project/environment.
- The `UASM` environment variable can contain assembler options. Use an independent tool-path variable such as `ASSEMBLER` in new build scripts.

For an unfamiliar form, consult the bundled source and the repository tests listed in provenance. If the current assembler rejects it, reduce it to a small case; do not invent a plausible-looking directive. Updating this pack does not authorize changing the assembler or its regression baselines.
