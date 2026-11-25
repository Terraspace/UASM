Namespace regression expectations
================================
Positive BIN expectations are constructed from explicit values/encodings,
not blindly accepted assembler output:

scope.bin: 01 02 03 02 01 02 04 05 06 02 07 08
  Global, parent, child/reopened scope and expansion-site macro lookup.
forward.bin: three little-endian DWORDs: 4, 0x1234, 4.
  Forward and absolute qualified addresses both identify offset 4.
includes.bin: 0C; balanced include inherits its enclosing namespace.
labels.bin: 90 C3 E8 F9 FF FF FF E8 F5 FF FF FF.
  NOP/RET then two relative calls to the intended namespace-local labels.
types.bin: DWORD 0x1234, WORD 0x5678, DWORDs 4, 2, 4, 0xE0, 0x1F,
  then BYTE 9. Covers distinct structures/typedef sizes, RECORD masks,
  namespaced data and text equate expansion.

ERR expectations require assembly failure for ordinary symbol/namespace
collisions in both declaration orders; duplicate exported linker names;
unbalanced include scope; namespace changes in macro definitions, procedures
or structures; qualified source definitions; strict qualified lookup that
must not fall back to a parent; and unmatched/unclosed namespace blocks.

The Win64 runtime/CodeView demonstration is in samples/win64/namespaces.
Its build.cmd checks nested calls, same-leaf private procedures, cross-object
linking, macro expansion scope, and static/instance OO calls at runtime.
