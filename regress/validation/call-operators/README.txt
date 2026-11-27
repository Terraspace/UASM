C-style call token boundaries
============================
Fixtures: nested_calls32, nested_calls64, nested_callself/operator_boundaries.asm.

The unfixed assembler concatenates adjacent token words while rebuilding INVOKE,
for example MB_OK or MB_ICONERROR -> MB_OKorMB_ICONERROR.

The EXP objects were independently assembled with the pre-fix executable from
identical fixtures using INVOKE Target,arguments instead of Target(arguments).
The last nested call used Target(Inner(95),8,5,2), the independently evaluated
values of Flags OR Bits, 1 SHL 3, Flags AND Bits, and 17 MOD 5.
Use the same relative ../src/<group>/operator_boundaries.asm input path when
recreating references, because COFF stores the source name in its file record.

Coverage: OR, AND, XOR, NOT, SHL, SHR, MOD, EQ/NE/LT/LE/GT/GE, SIZEOF,
TYPE, LENGTHOF, LOW/HIGH/LOWWORD/HIGHWORD, parenthesized mixed expressions,
DWORD PTR/member access, namespace qualification, and nested typed returns.
Every expression appears in all four argument positions on Win32, Win64 and
System V ELF64. Existing literal, OO/RAW, namespace and nested-call suites cover
punctuation and quoted-string handling alongside these fixtures.
