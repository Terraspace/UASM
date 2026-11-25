INVOKE and C-style string literals
=================================
OPTION LITERALS:ON accepts double-quoted narrow strings and L-prefixed UTF-16
strings. The supported backslash escapes remain only n, r and t. Other
backslashes are preserved; embedded quotes use MASM doubled quotes. Backslash-
quote is not an added C escape and malformed arguments are diagnosed.

The literal_calls64, literal_calls32 and literal_callself groups check direct
INVOKE/C-style parity, quotes, punctuation/call-like text, UTF-8/UTF-16, case
collisions, repeated literals, pointer aliases, mixed STDCALL parameters,
variadics and the old buffer boundaries. literal_call_errors checks diagnostics.
Data payloads were checked independently against explicit byte/UTF-16 values.

The runtime.asm files additionally check the actual bytes through the argument
pointers, including every terminating NUL. Assemble with the group's normal
flags. They can be linked and run without third-party dependencies:

Windows (x64 Native Tools prompt, from regress/results):
  ..\..\x64\Release\UASM.exe -win64 -Fo runtime.obj ..\src\literal_calls64\runtime.asm
  link /subsystem:console /entry:Start /out:literal-runtime.exe runtime.obj kernel32.lib
  literal-runtime.exe

Linux (from regress/results, adjust assembler build folder if needed):
  ../../GccUnixR/uasm -elf64 -Fo runtime.obj ../src/literal_callself/runtime.asm
  gcc -no-pie -Wl,-z,noexecstack runtime.obj -o literal-runtime
  ./literal-runtime

Exit status zero means all pointer/content checks passed. Expected object files
are fixtures; build runtime objects from source with the assembler being tested.

Identical decoded strings of the same width share one module-owned literal.
Narrow and wide forms remain distinct. Hashes only suggest symbol names; exact
contents establish identity. Namespace lookup cannot capture generated names.
