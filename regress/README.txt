UASM regression runner
======================

Run from regress:
  go run .
  go run . -filter pr241
  go run . -audit
  go test ./...
  go build -o regress.exe .
  regress.exe

From the repository root:
  regress\regress.exe -root regress

The default assembler is <suite>\..\x64\Release\UASM.exe.
Override with -asm <path>. -timeout defaults to 30s per source.
No external Go modules or fcmp dependency are used.

Layout
------
src/        Merged original test sources/support files, clone taking precedence.
exp/        Merged expected outputs, clone taking precedence.
results/    Cleared before EVERY assembly run, including filtered runs.
groups.json Assembler arguments per source group, transcribed from runtests.cmd.

Audit mode does not clear results or invoke the assembler. Every .asm source
is audited. Sources lacking a baseline or command are INCOMPLETE, not passes;
no command or expected output is invented. Orphan expectations are reported.
Original source-folder build/cache extras were copied but are not test cases.
The old regress/ and original project directories remain untouched.

Comparison and reporting
------------------------
.bin and .err are compared byte for byte, including diagnostic path spelling,
capitalization, CRLFs, and trailing blank lines. A missing diagnostic file is
accepted only when its expected .err is empty (both mean no diagnostics).
No .err expectation means no diagnostics are expected; unexpected output fails.
Expected errors are identified by an "Error A<number>" entry in the baseline;
these require exit 1. All other cases require exit 0. Crashes and timeouts fail.
All expected files for a source stem are compared, including warning files.
ELF .o expectations map to the assembler's actual .obj output name.

Recognized x86/x64 COFF objects and PE executables ignore the four-byte COFF
TimeDateStamp. C13/CV8 COFF objects additionally normalize S_OBJNAME's object
pathname, S_ENVBLOCK's cwd/exe values, and S_COMPILE3's backend version tuple.
Source paths, other environment values, producer identity, compiler flags,
machine/frontend fields, types, checksums, line tables and other symbol records
remain exact. Derived record/section lengths, file pointers, debug relocation
positions and the debug section's auxiliary-symbol length are adjusted to the
canonical layout. Relocation targets/types and remaining bytes stay exact.
Malformed/unsupported layouts fall back to raw comparison, never a pass.
There are no broad header skips. ELF, DOS MZ, CV4 data and PE checksums get no
new exclusions. Normalization is reported in console and JSON results; byte
offsets for normalized comparisons refer to the canonical object layout.

Passing outputs are removed. For failures, all actual artifacts (including
matching companions) are kept under results/<group>/<source-stem>/, with run.txt
recording the command, exit status, differences and assembler console output.
Missing output is recorded explicitly; it cannot be retained if never generated.
Console output includes the first differing byte offset and both file sizes.
results/report.json contains per-case results and totals. Exit code 0 means all
selected tests passed; 1 means failures/incomplete cases; 2 means setup failure.
The runner does not update baselines. Results are ignored by Git; expected .obj
and .exe files are explicitly allowed by newregress/.gitignore.

Migration notes
---------------
Original: D:\HJWasm\HJWasm2.13.1s\HJWasm2.13.1s\regress
Clone:    D:\uasm\UASM\regress

Restored all 55 original-only expected files (36 .obj and 19 .exe). All six
conflicting shared baselines retain the clone's bytes. crc32.err already exists
in exp/plain_bin and also has an identical stray copy in src/plain_bin.
The clone's imm_64bit_err.asm and .err are retained.

The new PR #241 case lives in src/pr241, with explicit .x64 and USE64 so it
assembles as raw binary. Its baseline was generated with the rebuilt local
UASM.exe and independently checked against 62 C1 FD 48 28 FA C3: the expected
vmovapd zmm23,zmm10 followed by ret. No AVX-512 CPU or linker is needed.

Initial audit: 569 ASM sources, 522 configured with baselines, 47 incomplete.
See migration-audit.txt for every gap and orphan. The 47 incomplete sources
have neither baselines nor commands in the legacy batch runner. The configured
ooerr and avx512 source groups are absent in both input folders.

Initial scratch verification: 441 PASS, 81 FAIL, 47 INCOMPLETE. Legacy baselines
were not changed to make tests pass. Consult the latest report.json for the
current run; debug objects can reflect source paths as well as compiler version.

Cleanup review (2026-11-20)
---------------------------
Current active coverage: 567 ASM sources; 511 passed, 9 failed, 47 incomplete.
Removed the two Mach-O fixtures and their expectations/configuration from this
suite. Removed 68 obsolete A4299-only .err files (64 active plus four orphans).
Corrected CONTEXT2.bin, f16c.bin, CodeGenV2/MOV64_6.err and Linux64/Lin64_1.o.
Added .gitattributes to protect binary fixtures from line-ending conversion.

Refreshed c_invoke.obj, seh64_auto.obj and win64_struct.obj only after a scratch
build restoring the historical REX.W prefix rule reproduced their old objects
exactly except timestamps. The three oo baselines remain unchanged: even with
the old prefix rule restored, each has 132 differing debug-type bytes requiring
separate review. No assembler source was changed during this cleanup.

Remaining failures:
  CodeGenV2Error/IMMSIZE64_ERR.ASM   Negative immediate diagnostic policy
  CodeGenV2Error/MOV64_6.ASM        Silent 64-bit immediate truncation
  codeview8_32/cv8_1.asm            Debug metadata/path comparison
  codeview8_64/cv8_2.asm            Debug metadata/path comparison
  oo/oo1.asm                       Prefix changes plus debug-type differences
  oo/oo2.asm                       Prefix changes plus debug-type differences
  oo/oo3.asm                       Prefix changes plus debug-type differences
  plain_bin/avx512.asm             Wrong high ZMM register encoding
  win64/record64.asm               Error diagnostics and stale object contract

The legacy regress/ directory and external original archive are unchanged.

VCVTPS2PH fix and issue #231 coverage (2026-11-20)
------------------------------------------------
Latest full run: 515 passed, 8 failed, 47 incomplete (570 source files).
codegen.c used operand 1 to form EVEX.R for a memory-destination VCVTPS2PH.
It now selects operand 2, which supplies ModRM.reg. This fixes ZMM30 becoming
ZMM22. codegenv2.c and parser.c were not changed. The existing 46,899-byte
avx512.bin expectation is unchanged and now matches completely.

New evex_encoding fixtures: vcvtps2ph_minimal (7 bytes) and vcvtps2ph_highreg
(94 bytes: register banks, masking, extended base/index addressing).
New pr241/issue231 fixture (32 bytes) covers a macro/OPATTR condition followed
by vmovapd and broadcast vfmadd132pd using the issue's original address.
All three baselines were independently checked with GNU as. Issue #231 is the
separate stale-decorator problem already fixed in tokenize.c; its new fixture
passes current UASM and fails with A2018/A2023 before that tokenizer fix.

The complete x64 Release assembler was rebuilt with MSVC and its UASM.rc
version resource, and installed in x64/Release/UASM.exe. No legacy baseline
was regenerated for this fix. The remaining failures are the two CodeGenV2Error
cases, two CodeView cases, three oo cases, and win64/record64.

Qword memory-immediate range fix (2026-11-20)
--------------------------------------------
Latest full run: 518 passed, 7 failed, 47 incomplete (572 sources).
CodeGenV2Error/MOV64_6 now matches its original A2237 error baseline exactly.
The parser previously narrowed the immediate to data32l before validating a
qword memory destination; the existing check only covered non-MOV r64 operands.
parser.c now checks the full expression before narrowing MOV memory immediates.
No encoder changes or existing expectation changes were needed for this fix.

The allowed literal range preserves signed/unsigned 32-bit compatibility:
-UINT_MAX through UINT_MAX. Like MASM, UASM accepts unsigned imm32 bit patterns
and negative 32-bit literals; the CPU sign-extends the actual 32 encoded bits.
This is distinct from silently dropping upper bits of a wider immediate such
as 1122334455667788h. Full imm64 remains allowed for any r64, including RBX/R15.

New imm64 fixtures cover 14 valid instructions (106 bytes, independently matched
against ML64 and GNU as with equivalent encoded literals) and three invalid
constants, with explicit A2237 diagnostics and no binary. Both existing MOV64
positive fixtures remain passing. record64 now also reports its previously
missing out-of-range qword-memory MOV diagnostics, but still needs its separate
baseline/expected-output review. The remaining seven failures are IMMSIZE64_ERR,
the two CodeView cases, three oo cases, and record64.

References: Intel SDM MOV forms REX.W+B8+rd io (r64,imm64) and REX.W+C7 /0 id
(r/m64,imm32 sign-extended). The local MSVC ML64 was used to check literal
compatibility, not just the hardware instruction's operand width.

Byte-immediate MASM compatibility (2026-11-20)
---------------------------------------------
Latest full run: 520 passed, 6 failed, 47 incomplete (573 sources).
IMMSIZE64_ERR had stale expectations: ML64 accepts MOV AL,-200 and MOV CL,-200,
encoding the low byte 38h. Removed only those two expected errors and corrected
its source comment; BT EAX,400 and positive byte immediates 300 still error.
No assembler source change was needed.

New imm8/mov_imm8_valid covers AL, CL, R8B and byte memory destinations with
-255, -200, -129, -128, -1, 0, 127, 128 and 255. All 90 expected bytes were
independently extracted from local ML64 output and match current UASM exactly.
A separate boundary sweep found UASM accepts -256 while ML64 rejects it.
That explicitly documented UASM 2.58 parser allowance is unchanged; this fixture
does not establish a new expectation for that separate compatibility decision.
Remaining failures: codeview8_32/cv8_1, codeview8_64/cv8_2, oo/oo1, oo/oo2,
oo/oo3, and win64/record64. The 47 incomplete cases remain unchanged.

PR #242, #243, #238 and unmasked VPMOVSXBQ (2026-11-21)
------------------------------------------------------
Latest full run: 524 passed, 6 failed, 47 incomplete (577 sources).
Applied the two overlapping-operand memcpy -> memmove fixes in parser.c (#242).
Legacy codegen now checks the token before indexing vex_flags for forced EVEX
and emits A2302 for unsupported legacy instructions (#243).
Applied #238's AVX-512BW instruction/operand table and legacy codegen fixes.
Extended the same decoflags -> evex correction to the signed/unsigned
byte-to-qword widening branch, fixing unmasked VPMOVSXBQ ZMM forms.
CodeGenV2 was unchanged. Previous source fixes and existing EXPs are preserved.

Four standalone fixtures under src/exp/pr238_243:
  avx512bw       PR #238's supplied test and verified 85-byte baseline.
  invalid_evex   Forced-EVEX ADD and MOV must report A2302; no binary expected.
  unmasked_sxbq  Register/high-register/memory and masked controls, 37 bytes.
  vex_operands   NDS and immediate NDD operand shifts, 20 bytes.
All three positive baselines match GNU as bytes independently. The operand
shift fixture checks encoding; detecting memcpy overlap itself requires a
sanitizer, which was not run for this Windows build.

Rebuilt all C sources with MSVC x64 Release flags and the version resource,
and installed x64/Release/UASM.exe. Full suite used this executable in place.
Remaining failures unchanged: two CodeView cases, three OO cases, record64.
PR #237's replacement avx512 baseline was not applied: it encodes ZMM22 where
ZMM30 is required, accepting the previously fixed VCVTPS2PH register bug.
Sources: https://github.com/Terraspace/UASM/pull/242
         https://github.com/Terraspace/UASM/pull/243
         https://github.com/Terraspace/UASM/pull/238

128-bit RECORD MASK expansion (2026-11-21)
-----------------------------------------
Latest full run: 526 passed, 5 failed, 47 incomplete (578 sources).
record64 now matches its original .err exactly: the stackbase warning and two
A2237 errors for unencodable qword-memory immediates. Removed its stale expected
OBJ; an assembly with those errors must not produce an object. No diagnostic
baseline was changed.

Replaced expreval.c's GetMask128 expansion, which retokenized the active input
inside expression evaluation and reused writable GMASK storage. Direct XMM
MASK operands now reference immutable, 16-byte constants in _UASM_MASK.
Constants are named by value and reused; the normal line queue preserves the
active input and nested segment context. Emission accounts for FASTPASS keeping
symbols defined between passes. No codegen or CodeGenV2 changes were needed.

record_masks/mask128 is a positive raw-binary test covering full-record masks,
fields above/across bit 64, lower fields, high XMM registers, SSE/AVX loads,
POR, and repeated masks inside a procedure. Its 112-byte expectation was
calculated independently from instruction encodings, RIP displacements and
128-bit mask arithmetic, and matched explicit data-label assembly. COFF output
was also inspected for data contents and relocations. The constants require no
runtime stores and leave general-purpose registers and flags untouched.

Rebuilt MSVC x64 assembler and installed x64/Release/UASM.exe. Existing
regressions remain passing; the five remaining failures are codeview8_32/cv8_1,
codeview8_64/cv8_2, oo/oo1, oo/oo2 and oo/oo3.

CV8 metadata comparison (2026-11-21)
-----------------------------------
Latest full run: 528 passed, 3 failed, 47 incomplete (578 sources).
Both codeview8 cases now pass against their original UASM 2.55 EXP objects.
Added structural C13 metadata normalization in codeview.go (see Comparison
and reporting above). No assembler source or EXP files changed.
Tests cover different-length metadata and derived layout, archived x86/x64
objects, retained source/producer/compiler fields, symbol/type/line/checksum
changes, relocation offsets/targets/types, truncation and malformed sizes.
Go tests and go vet passed; regress.exe rebuilt and the complete suite rerun.
Only oo/oo1, oo/oo2 and oo/oo3 remain failing; incomplete count is unchanged.

Legacy CodeView pointer encoding (2026-11-21)
-------------------------------------------
Latest full run: 532 passed, 3 failed, 47 incomplete (582 sources).
Restored attributes-before-utype in H/dbgcv.h's CV_POINTER_16t. The reversed
layout produced corrupt pointee/mode data in Microsoft's resulting PDB.
For 64-bit pointers, dbgcv.c now emits LF_POINTER (32-bit type indices) even
inside a C7 type stream. Microsoft LINK accepts this mixed stream and retains
Near64, unlike LF_POINTER_16t/Near64 which reproduced LNK1102. Legacy 16/32-bit
pointers retain their correctly ordered LF_POINTER_16t records.

Pointer targets not yet emitted receive named forward type records, completed
after the type walk. This preserves struct/union/record targets, including
cycles, instead of substituting an invalid void/nullptr type. Untyped USE64
pointers now use ST_64PVOID (0x0603), not ST_PVOID (0x0103).

New standalone fixtures:
  cvptr32/pointers32       Legacy 32-bit scalar/void/struct/recursive pointers.
  cvptr64/pointers64       Legacy 64-bit equivalent, using modern pointer leaves.
  cvptr8/pointers64_cv8    C13 equivalent, covering shared target handling.
  cvptr64/issue194         Original minimal linker failure reproducer.
The runner checks their OBJ baselines. Separately, each was linked using MSVC
LINK /debug /dll /noentry /incremental:no (kernel32.lib for issue194), and its
fresh PDB inspected with llvm-pdbutil. Width, signed/unsigned pointees, void
pointer type, named structure targets and forward definitions were verified.
The extended source was also accepted by ML64 as an independent syntax oracle.
A successful link alone is insufficient: the old swapped form could link while
producing a 16-bit reference to unknown type 0x000C.

The existing codeview8_64/cv8_2 EXP received only six byte corrections: three
argument-list entries and three parameter symbol entries changed type 0x0103
to 0x0603 for x64 ptr parameters. Other old metadata and bytes are untouched.
OO EXP objects are byte-for-byte unchanged. All three current OO objects link
successfully with Microsoft's linker but intentionally still fail comparison:
their corrected types/forward records and earlier prologue changes differ from
the archived baseline. Their baseline review remains pending.
Rebuilt all C sources and the version resource; installed x64/Release/UASM.exe.

OO baseline verification and refresh (2026-11-21)
------------------------------------------------
Latest full run: 535 passed, 0 failed, 47 incomplete (582 sources).
All 535 runnable cases pass. The 47 incomplete cases still lack configuration
and/or expected outputs; they are not passes, and the runner still exits 1
when incomplete cases are present.

Before updating oo1/oo2/oo3 EXPs, an isolated build reversed only the intended
prologue change (restored redundant REX.W) and the recent CodeView writer fixes,
while retaining the documented legacy pointer field order used by the archive.
It reproduced each original OO EXP byte-for-byte except its COFF timestamp:
  oo1: 144538 bytes; zero other differences.
  oo2: 144502 bytes; zero other differences.
  oo3: 144848 bytes; zero other differences.
This establishes that the current object differences are fully accounted for
by the prologue and debug changes. Their current objects had also passed MSVC
LINK validation in the pointer-fix work above. Updated only the three OO EXPs
to these verified current objects, then reran the entire suite successfully.
No assembler/runner code changed in this baseline-refresh step.
The legacy regress directory, newregress name and Git commit state were left
for the author's planned cleanup, rename and manual verification.

Incomplete coverage cleanup (2026-11-21)
---------------------------------------
Latest full run: 535 passed, 0 failed, 14 incomplete (549 sources).
Removed 33 incomplete cases: omf (22), omf2 (3), omfcu (1), zd (1), ifdef (1),
Xc (2), crossplatform/tplat (1), directx/ddraw_raw (1), pe/PE2 (1).
Removed OMF companion libraries and all 11 orphan EXP files. Empty avx512 and
ooerr group settings were removed. Audit has no orphan EXPs or empty configured
groups. Empty source/EXP directories may remain; their final removal was blocked
by automatic approval review (approval required by policy but that approval
category was disabled). All intended file deletions completed beforehand.

All passing tests, including externally dependent OO/cinvoke cases, were kept
per the author's clarification. ELF/ELF64, System V, SafeSEH and extern remain.
System V's missing misc/xmmtypes.inc include was replaced by a comment using
UASM's built-in SIMD types; the standalone file assembles with -elf64.
The -Zg tests are format-independent and both pass assembly with -bin -Zg.
No new EXPs were generated. Legacy regress and the original archive are untouched.

Remaining incomplete: borland_register (1), dllimp (1), elf (1), elf64 (2),
extern (1), pe (3), safeseh (1), systemv (1), zg (2), zne (1).
All need verified settings/EXPs; pe4 also needs its default-mode assumptions
reviewed. The runner still exits 1 while incomplete cases exist.

Reviewed missing baselines (2026-11-21)
--------------------------------------
Added settings for all 14 previously incomplete cases and accepted 13 new
EXPs from the installed x64/Release/UASM.exe (2.59). These capture reviewed
current behavior, not independent proof of every instruction or ABI detail.
No assembler code or runner comparison rules changed.

Checks performed:
- borland_register/fast32 (-coff): decoded register/stack parameter passing;
  byte/word parameters use AL/AX, procX receives its pointer in ECX and floats
  at EBP+16/+12/+8, with RET 12. Historical error comments are now obsolete.
- dllimp/DLLIMP (-coff): indirect ExitProcess call and DIR32 relocation to
  __imp__ExitProcess@4. This baseline tests assembly, not JWlink's optional -Fd.
- elf/ELF1 (-elf): ELF32 relocatable; BSS has SHT_NOBITS, size 32, no stored
  payload; both code sections contain RET.
- elf64/elf641 (-elf64): ELF64 relocatable; integer parameter aliases use
  RDI/RSI/RDX/RCX/R8/R9 at the requested widths, vector arguments use XMM0-5.
- elf64/elf642 (-elf64): linked using LLVM ld.lld and decoded the result;
  six stores target string+0..5 and LEA RCX,$ resolves to its own address.
- extern/EXTERN4 (-coff): weak aliases point to v1/p1; Microsoft LINK resolved
  the object successfully without runtime libraries or other objects.
- pe/PE1, PE3, pe4 (-pe): checked PE headers, entry points, imports and code.
  PE1 is PE32 with RET; PE3 is PE64 importing GetCurrentProcess/ExitProcess;
  pe4 is PE64 importing msvcrt exit with ECX=0 and shadow-space allocation.
  pe4 now declares .x64 / .model flat,fastcall explicitly: its old comment
  assumed implicit defaults that UASM's -pe option does not provide.
- safeseh/safeseh (-coff -safeseh): .sxdata contains three handler references;
  linked with Microsoft LINK /SAFESEH plus a scratch-only definition of the
  deliberately external third handler. Decoded load config reports count 3
  and the three correct handler addresses. No helper dependency was added.
  Reference: https://learn.microsoft.com/en-us/cpp/build/reference/safeseh-image-has-safe-exception-handlers
- zg/INVOKE21 and LOCAL3 (-bin -Zg): decoded as 32-bit code (.386 precedes
  .model). INVOKE21 uses ADD ESP,-8, OR EAX,EAX, non-EAX-clobbering word
  extension and LEAVE. LOCAL3 addresses [EBP+ESI-128] with implicit SS.
  Its historical comment asks for an explicit SS prefix with reversed SIB
  registers; current encoding has equivalent addressing without that prefix.
- zne/OVERRID3 (-coff -Zne): expected exit 1, eight A2171 diagnostics at lines
  10,11,12,13,16,18,21,23; no OBJ. EXP preserves the runner's relative paths.

System V baseline deliberately withheld
--------------------------------------
The sysv1 output assembles and has valid ELF structure, but calls to testProc4,
testProc7 and testProc8 reserve 8 alignment bytes and PUSH three stack arguments
(24 bytes), then emit only ADD RSP,8 after CALL. The callee uses plain RET.
Each call therefore leaks 24 bytes; subsequent calls/epilogue use the wrong RSP.
This is an assembler-generated stack cleanup error, not an EXP discrepancy.

Minimal single-file reproducer: test/systemv_stack_cleanup.asm
Command: ..\x64\Release\UASM.exe -q -elf64 test\systemv_stack_cleanup.asm
(the output lands in the working directory; use a scratch directory).
The call-site ADD RSP must restore 32 bytes, not 8; the caller's own separate
8-byte prologue allocation is restored separately in its epilogue.
The reproducer is outside src until the bug is fixed and a correct EXP exists.
The original src/systemv/sysv1.asm remains incomplete with no accepted EXP.

Full rerun after baseline additions: 548 passed, 0 failed, 1 incomplete.
Audit: 549 sources; only systemv/sysv1.asm lacks EXP; no orphan expectations.
Exit status remains 1 because that incomplete case is intentionally retained.

System V review completed (2026-11-21)
------------------------------------
The previously withheld sysv1 baseline is now accepted after fixing stack cleanup.
Added eight positive System V ASM fixtures and five diagnostic fixtures. 162 ABI
checks passed by native execution; the additional AVX-512 instruction cases were
validated by assembly/disassembly (host lacks AVX-512). See SYSTEMV-REVIEW.txt for
coverage, implementation fixes, explicit limits and optional Linux execution.
Only the pre-existing Lin64_4 EXP needed updating, for direct-CALL stack alignment.
Full suite: 562 passed, 0 failed, 0 incomplete. No comparator rules changed.

PR #240 listing fixes (2026-11-21)
---------------------------------
The in-segment equate field no longer pads a 20-character string into a
20-byte destination plus a terminating NUL. Macro depth is formatted into a
separate buffer; the listing space-fill loop stays within the 32-byte field.
Procedure-local type names have room for MAX_ID_LEN plus an array suffix,
rather than being truncated or overflowing a 32-byte temporary.

New pr240 equate and macro_depth fixtures compare both .bin and .lst outputs;
pr240_locals/locals compares the COFF object and listing, including a long
structure type name used by a scalar local and an array local. The previous
Windows build crashes on this locals case; the fixed build succeeds.
The equate fixture independently checks values 2 and 3 and one NOP byte.
The macro fixture exercises two-digit nesting and emits one NOP byte.

The runner recognizes .lst baselines. Only a recognized initial UASM version
and build-date banner and the final summary's numeric elapsed-millisecond
field are excluded; all remaining listing bytes are exact. Filenames, line
and pass counts, warning counts and error counts remain significant.
Unit tests verify changed content and unrecognized banners still fail and
that this exception does not apply to other file types. Listing baselines
are marked -text to preserve their exact line endings.

Linux portability update (2026-11-21)
------------------------------------
See ../BUILD-LINUX.txt for reproducible GCC/Clang builds, make test, portable
comparison rules and self-contained SDK fixture changes. The cross-platform
text/path rules described there supersede the original migration's exact
Windows path and line-ending policy. No instruction/data bytes are ignored.
Debug builds emit internal listing additions only with the debug-output option.

Issue #235: CV8 generated labels (v2.60)
--------------------------------------
Generated anonymous/HLL code labels no longer create source-level CV8 label
records. Required COFF relocation targets, including $$000000 and anonymous
labels used by data relocations, remain. Named user labels are unaffected.
Three cv8_issue235 fixtures cover the original anonymous and macro/HLL examples
and user labels, macro-defined labels, and an anonymous address relocation.
Code bytes and C13 line tables were checked unchanged against 2.59; Microsoft
LINK accepted all three objects with /DEBUG and produced PDBs. ML64 also keeps
the $$000000 line anchor but omits the anonymous debug label.
Windows MSVC and Linux GCC 16.2: 569 passed, 0 failed, 0 incomplete.
The source-name collision with explicit @C0001 is separate and unchanged.

HLL generated-name collisions (v2.60)
-----------------------------------
Microsoft ML 14.51 and UASM both reject explicit @C0001 definitions colliding
with the first .IF-generated label. Checked definitions before/after the HLL
macro and a forward reference, with debug output enabled and disabled. ML
reports A2005 and UASM A2056. No assembler change is needed for compatibility.
Six negative fixtures in hll_collision and hll_collision_cv8 preserve these
diagnostics and require no object output. ML64 does not support .IF, so the
MASM comparison uses ML /coff with .386 / .model flat.

Issue #212: ELF64 RELA addends (v2.60)
-----------------------------------
Capture explicit addends before clearing relocated fields, including full-width
64-bit constants. PC-relative addends account for trailing immediate bytes.
Use R_X86_64_32S for sign-extended 64-bit addressing displacements; retain
R_X86_64_32 for unsigned 32-bit address constants/data. ELF32 is unchanged.
elf64_rela/forms covers positive/negative indexed and RIP-relative offsets,
base+scaled-index addressing, trailing imm8/imm32, nonzero symbol offsets,
32-bit constants, and positive/negative 64-bit addends beyond 32 bits. All 15
relocations and text/data bytes independently match GNU as after resolving
symbol-relative versus section-relative targets. GNU ld-linked code/data
also match byte for byte at identical section addresses.
elf64_rela/runtime is a standalone Linux syscall check of the original bug:
link with ld -e _start and run; success is exit 0 (previous build exits 1).
elf642 and Lin64_4 EXP changes were independently verified to contain only
zeroed PC32 relocation fields; relocation addends and other bytes unchanged.

Issue #221: unnamed DW string initializers (v2.60)
------------------------------------------------
DW literal string emission now depends on element width rather than a label.
UTF-8 conversion no longer dereferences an unnamed symbol, changes a named
array's WORD type, or rewrites the token length used by DUP. The temporary
conversion buffer is sized to MAX_STRING_LEN and its capacity is passed to
the converter. Non-word strings retain ordinary packed-integer emission.
Four plain_bin/issue221 fixtures independently specify UTF-16LE bytes for
named/unnamed ASCII and Unicode, mixed initializers, a surrogate pair, DUP,
WORD type/size assertions, 300 Unicode characters, and literals-off controls.
Windows MSVC and Linux GCC 16.2: 581 passed, 0 failed, 0 incomplete.
