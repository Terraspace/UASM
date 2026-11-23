UASM Linux64: PIE application + shared library + GTK4 + DWARF

This project follows the PROC SYSTEMV / INVOKE style of the older Lin64_2
example. All application and library code is assembly; GCC is only the linker
driver supplying the normal C runtime. The console and GTK frontends share the
same small library API and data structure. No personal SDK paths or external
assembly includes are required.

BUILD FROM A FRESH CLONE (repository root)

  sudo apt install build-essential pkg-config libgtk-4-dev gdb python3 xvfb xauth dbus-daemon
  make -f Makefile-Linux-GCC-64.mak -j4
  cd samples/linux64/pltgot-gtk
  make
  make check
  make check-gui
  ./build/gtk

For a different assembler build:
  make ASSEMBLER=/absolute/path/to/uasm
The default is ../../../GccUnixR/uasm. CC can select the linker driver.
ASMFLAGS defaults to -q -elf64 -Zi. Do not use -Zi8 with ELF64.

The command-line test needs no GTK development files or display:
  make console check
The GUI tests use a temporary Xvfb display and DBus session and finish by
themselves. Normal ./build/gtk stays open until you close its window.

OUTPUTS

  build/console            PIE command-line verification program
  build/gtk                PIE GTK4 application
  build/libuasm_sample.so  UASM shared library used by both

Keep the executable and SO together. $ORIGIN RUNPATH finds the adjacent SO;
there is no LD_LIBRARY_PATH requirement. Both executables use main and return
to the C runtime on exit. The shared library has an SONAME and hidden internal
helper. Link checks require a non-executable stack and forbid text relocations.

SOURCE MAP

  api.inc         Shared structure, options and exported API declarations.
  samplelib.asm   Shared model, homed parameters, floating-point locals, hidden
                  helper, exported data and an explicit atomic GOT update.
  console.asm     Three updates; verifies count=3, total=3.00 and events=3.
  gtk4.inc        Only the GTK4/GLib ABI declarations actually used.
  gtk.asm         Activation/button/timer callbacks; button adds 1.25 through
                  the SO and displays count, total and exported event count.
  verify.py       Executes the console program and checks ELF/linker metadata.
  debug_check.py  Automated GDB checks for either frontend.

GTK's g_signal_connect is a C macro; assembly calls g_signal_connect_data.
NULLPTR is an explicitly QWORD-sized zero for INVOKE pointer parameters.
The makefile uses ASSEMBLER, not UASM, as its tool-path variable because UASM
itself interprets the UASM environment variable as assembler options. Recipes
clear that environment variable; use ASMFLAGS for reproducible options.

PLT/GOT EXAMPLES

  invoke sample_add,ADDR sample_model,requested
  mov eax,GOT(sample_model.count,r11)
  movsd xmm0,GOT(sample_model.total,r11)
  mov rax,sample_events
  lock inc GOT(sample_events,r11)

External function calls use PLT-capable relocations; imported data addresses
come through the GOT. The explicit helper declares its register clobber on
that operand. Internal private constants remain RIP-relative. Symbols in the
shared library retain normal ELF interposition semantics.

DEBUG MANUALLY

  gdb ./build/console
  (gdb) break sample_add
  (gdb) run
  (gdb) next
  (gdb) info args
  (gdb) info locals
  (gdb) print *state
  (gdb) print sample_events
  (gdb) backtrace

For the GUI, use gdb ./build/gtk, run, and click Add 1.25. Set a breakpoint on
the DEBUG_STOP line in samplelib.asm to inspect initialized before/after locals.
Parameters and locals are not all initialized at the PROC entry instruction.

SYSVHOME:1 homes parameters referenced by name. The sample deliberately names
parameters intended for inspection so their values survive calls. Unused
register arguments are not automatically preserved merely for debugging.
sample_adjust uses SYSVHOME:0 to demonstrate a register-backed float parameter.

make debug-check / make debug-gui verify a register parameter, homed parameters,
struct fields, floating locals, a global, a source breakpoint and source-level
step, and a backtrace across the SO boundary (and GTK/GObject for the GUI).
The GUI smoke test emits two actual clicked signals and checks the resulting
count, total and event count before cleanly quitting. Python is used only by
these verification tools, not by the assembled applications.

The assembler emits both .debug_frame and allocated, PIC-safe .eh_frame for
automatic System V frames with -Zi/-Zd. The linker creates .eh_frame_hdr.
This sample verifies stack unwinding, not C++ exception handlers or cleanups.

LEGACY SAMPLE REVIEW

The original D:/HJWasm/Samples/Linux64 files are left unchanged.
Lin64_1 is a raw _start/syscall example: its old plain gcc link command conflicts
with GCC's normal startup objects. Raw entrypoints need a no-CRT link strategy.
Lin64_2 is the closest conceptual basis for this project. Here main returns
through the C runtime rather than issuing SYS_EXIT from a CRT-started program.
Lin64_3 demonstrates the OO/macrolib extensions; Lin64_4 demonstrates sockets
and threading. Those deserve separate modern Linux/PIC audits rather than
being silently assumed compatible with the new shared-library example.

REFERENCES

GTK4 application/callback lifecycle:
https://docs.gtk.org/gtk4/getting_started.html
RAD Linux build and debug-info conversion:
https://github.com/EpicGames/raddebugger

RAD DEBUGGER (optional)

The Linux build at commit 5b0d5f6 (development version 0.9.30) successfully
converted console, gtk and libuasm_sample.so DWARF into RDI, including source
files, functions and SampleState. The current release assets checked during
this work were Windows-only, so the VM has a source-built Linux debugger at:
  ~/uasm-tools/raddebugger/build/raddbg
  ~/uasm-tools/raddebugger/build/radbin
These paths describe this test VM, not a build requirement for a fresh clone.

Conversion commands (RAD binaries on PATH):
  radbin --rdi build/console --out:build/console.rdi
  radbin --rdi build/gtk --out:build/gtk.rdi
  radbin --rdi build/libuasm_sample.so --out:build/libuasm_sample.so.rdi
  radbin --dump build/libuasm_sample.so.rdi

For an interactive trial, launch raddbg from the VM desktop and add build/gtk
as the executable, with this sample directory as the working directory.
Repeat the source/args/locals/struct/backtrace checks above. RDI conversion was
verified here; full interactive RAD debugging has not yet been verified.
GDB remains the completed debugger validation for this sample.
