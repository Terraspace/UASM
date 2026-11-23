ELF64 DWARF 4 and System V parameter homes
=========================================
Use -elf64 -Zi for types, globals, parameters, locals and source lines.
-Zd emits source lines and procedure information only. -elf64 -Zi8 is an
error: CodeView 8 is for COFF. Debug sections are non-allocated and use ELF
relocations. Debug output does not change machine code.

Types include integers, floats, pointers, recursive structs, unions,
typedefs, arrays and RECORD fields. Register parameters describe their
current registers, not a preserved original value after register clobbers.
Automatic System V frames use location lists: homed parameters transition
from incoming registers to stack slots after the prologue; locals become
available after the prologue. Stack locations are unavailable during the
generated epilogue. Custom/manual frame locations are not guessed.
Automatic System V frames now emit DWARF4 .debug_frame call-frame information,
including instruction-boundary prologue/epilogue changes, USES saves, frameless
procedures, red-zone frames and generated outgoing stack-argument adjustments.
Both -Zi and -Zd include it. Multiple return paths restore their body CFI state.
The records use final encoded instruction offsets, not assumed opcode lengths.
The same CFI is also emitted in allocated, read-only .eh_frame, using PC-relative
32-bit relocations for PIE/shared-library linkage. The linker generates
.eh_frame_hdr. Both sections are emitted with -Zi or -Zd; builds without these
switches do not generate automatic CFI. This supplies stack-unwind metadata,
not language-specific exception handlers or cleanup/personality routines.
Custom/manual prologues and arbitrary user-written stack/frame manipulation
are outside the automatic-frame contract. XMM save records describe the low
128 bits; full YMM/ZMM reconstruction and macro information are not implemented.

OPTION SYSVHOME:0 is the default and preserves register-alias semantics.
OPTION SYSVHOME:1 gives register parameters referenced by name callee-owned
stack slots, saved before user code or calls. Discovery uses assembly passes,
so first references after calls are covered. Direct-register-only parameters
need no slot. Incoming stack parameters retain their ABI locations. Slots
participate in existing frame sizing, alignment and red-zone handling.
This is not caller-provided Windows home space. It requires the automatic
System V RBP prologue and epilogue. Set the option outside PROC; it applies
to subsequent procedures. Explicit register access still accesses registers.

On Linux, from the repository root:
  python3 regress/validation/dwarf/check.py ./GccUnixR/uasm
Substitute the actual assembler executable. Requires gcc, objcopy, readelf,
GDB with Python; uses LLVM DWARF verification when installed. Fixtures are
self-contained. Run after the Go suite, which clears regress/results.

Artifacts stay in regress/results/dwarf-live. For manual variable inspection:
  gdb regress/results/dwarf-live/dwarf-variables
  break Params1Ready
  run
  info args
  info locals
  print *arg_ptr
  print GlobalFlags
  break VectorReady
  continue
  info args

Params1 deliberately clears incoming registers in a nested call before named
access. Homed arguments retain their values; unused register parameters show
the current cleared register values. Params0 demonstrates unchanged aliases.
HomeLeaf exercises red-zone homes; FloatStack checks a ninth floating-point
argument on the stack. Automated GDB checks also verify prologue transitions,
local lifetimes, arrays, recursive pointers, union/record and SIMD values.
The companion dwarf-lines fixture tests includes, code sections and linked
compilation units. Both linked programs exit zero on success.

Unwind validation runs automatically from check.py. check_unwind.py steps every
executed instruction and compares recovered caller PCs, RSP, nonvolatile GPRs
and an explicitly saved XMM register with snapshots taken before each CALL.
The frameless callee overwrites RBP to prevent frame-chain fallback from hiding
missing CFI. Tests cover SYSVHOME 0/1, both return paths, a large local frame,
red-zone locals, stack arguments, -Zd and FRAMEPRESERVEFLAGS:ON.
Manual inspection: gdb regress/results/dwarf-live/dwarf-unwind
  break NoFrame
  run
  bt
  stepi
  bt

GDB on AVX targets maps the AMD64 DWARF XMM numbers to its YMM register view.
For an explicitly saved XMM value in an older frame, inspect the low 128 bits
of $ymmN if $xmmN appears stale. The unsaved upper bits are not meaningful.
The live unwind check validates the actual mapped low bits, not the alias.
