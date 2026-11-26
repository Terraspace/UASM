Bounded C-style calls -- Win64 / Visual Studio sample
====================================================

Requirements: UASM built from this branch and a Visual Studio x64 C++ toolchain
with the Windows SDK. No third-party includes or libraries are required.

Build in an x64 Native Tools Command Prompt:
  build.cmd
or supply a release executable explicitly:
  build.cmd C:\tools\uasm64.exe

The script assembles with -win64 -Zi8, links debug information and runs the
self-check. Expected output starts "PASS: typed nested calls"; exit status is 0.
All generated OBJ/PDB/EXE files are under build/.

Visual Studio:
  Open nested_calls.sln, select Debug / x64, and build.
  UasmPath defaults to the repository's x64\Release\UASM.exe. For a standalone
  distribution, set the UasmPath MSBuild property or build.cmd's ASSEMBLER path.
  Alternatively open build\nested_calls.exe as a project in Visual Studio.
  Set a breakpoint at Sum(NextValue(),DoubleValue(NextValue())) in Start.
  Step into NextValue, DoubleValue and Sum; inspect their parameters and locals.
  At Print(ADDR success,successSize), Start's locals should be:
    integerTotal=5, reentryTotal=6, floatingTotal=4.0, pointerValue=42.
  A single ASM source line can represent several calls/stores; use Disassembly
  when inspecting each emitted instruction rather than source-line stepping.

Rules demonstrated
------------------
* Maximum depth is three calls, including the outermost, on Win64, Win32 and
  ELF64. Arithmetic parentheses do not increase call depth.
* A call used as a value needs an explicit supported PROC/PROTO return type.
  A standalone call can remain untyped. (void) is valid only without a result.
* Nested calls execute in left-to-right, depth-first order. Their results are
  saved in private caller-frame slots before subsequent calls. Re-entry and
  recursion use separate stack frames; there is no shared global scratch area.
* Only call RESULTS are saved. Ordinary arguments are evaluated when their
  enclosing INVOKE executes, after its child calls. They are not snapshots of
  memory or registers from the start of the statement.
* A register-dependent operand which must survive an earlier call is rejected
  if the ABI permits that call to overwrite the register. Checks include
  subregister aliases, SIMD registers and registers inside memory addresses.
  A register operand consumed by the first leaf before any call is permitted.
* Nested calls requiring storage must be inside a PROC with an automatic frame.
  Manual frames and OPTION PROLOGUE:NONE are rejected. Temporaries share the
  normal frame allocator, preserving RBP/RSP handling and outgoing argument space.
* Inline calls in .WHILE/.ELSEIF conditions are rejected: those directives
  relocate/control condition execution. Use explicit calls and control flow.
  This feature does not implement C expression short-circuit evaluation.
* OO static/instance helpers use their generated typed method prototypes and
  the same result-spill rules; unresolved method return contracts are rejected.
* At most 32 nested result slots are supported in a statement. The slots are
  reused by subsequent statements in the same PROC and sized for the largest
  return stored there. Wide SIMD stores use unaligned instructions.
* Integer, pointer, REAL4/REAL8 and x64 SIMD return contracts are supported.
  UASM's explicit REAL4/REAL8 convention uses XMM0, including Win32; it is NOT
  an assertion that an arbitrary external Win32 C function uses XMM0 (many
  native Win32 floating returns use x87). Unknown/unsupported conventions,
  including Win32 multi-register QWORD returns and x87 REAL10, are rejected.

The comments at the end of main.asm show deliberately invalid calls.
The regression suite contains matching success/error fixtures and ABI variants.
