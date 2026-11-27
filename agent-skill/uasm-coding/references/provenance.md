# Version and evidence

Pack version: 1.0.0. Prepared 2026-11-27 for UASM 2.60 master snapshot `e693c8c2555c04980308910cac0dad834202ae39` in https://github.com/Terraspace/UASM.

This is a portable coding reference, not a transcript or a promise that every UASM 2.60 binary contains every post-release fix. Some original sample READMEs still say experimental/v2.60b; this pack describes the merged code at the snapshot above. No external machine's paths, tools or credentials are prerequisites.

`source-manifest.json` records the repository origin and SHA-256 of the copied example/build files. `assets/SOURCE-LICENSE.txt` preserves the repository's source license; existing notices remain in copied files. The new references summarize observed source/test contracts rather than importing a third-party manual.

## Source map for checking or updating the pack

Paths below are relative to a UASM checkout (not required to install the skill).

| Topic | Primary implementation / executable evidence |
|---|---|
| Tokens, expressions, HLL | tokenize.c, expreval.c, hll.c, parser.c; regress/src/namespaces and literal_calls64 |
| Namespaces and local shadowing | symbols.c, proc.c; regress/src/namespaces, namespaces_fastpass, namespaces_cv8, shadowing |
| Namespace keyword compatibility | regress/src/namespaces/keyword_fields.asm, keyword_parameters.asm; nested_calls64/namespace_keywords.asm |
| WIN64 flags and options | H/globals.h enum win64_flag_values; option.c SetWin64, SetSysvHome, SetStackProbe |
| ABI, prologue, invocation | proc.c and invoke.c; regress/src/win64, systemv, vcall; regress/runtime |
| Typed nested calls | hll.c and proc.c; regress/src/nested_calls64, nested_calls32, nested_callself and nested_call_errors* |
| OO/COM/RAW helpers | macrolib.c; regress/src/nested_calls64/interfaces_runtime.asm, oo_edges.asm; bundled OO/Direct2D projects |
| Literal strings | regress/src/literal_calls64/runtime.asm and corresponding 32/ELF/error groups |
| ELF relocation/visibility/GOT | elf.c, fixup.c, option.c and parser handling; regress/src/elf64_got, elf64_got_errors; regress/validation/elf64-pic.py |
| CodeView/DWARF | dbgcv.c, dwarf.c; regress/validation/dwarf; bundled debugger projects |

When updating: verify source syntax and option normalization, refresh copied files and hashes deliberately, assemble all examples, and rerun relevant runtime/debug checks when those contracts change. Record which target tests actually ran. Do not convert an unresolved limitation into a supported feature based on conversational recollection.
