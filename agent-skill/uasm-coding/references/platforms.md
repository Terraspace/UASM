# Targets, linking and ELF PIC

## Tools and build shape

Windows x64 projects: use UASM `-win64`, MS LINK from an x64 Visual Studio tools prompt and the applicable Windows SDK libraries. A custom `Start` entry point normally terminates via ExitProcess. A function named main does not supply CRT startup by itself: either link the matching CRT/startup arrangement or use a deliberate custom entry point. Import libraries such as an old msvcrt.lib do not guarantee a valid mainCRTStartup definition.

Win32 projects: select `.386`/`.686` and `.model flat,<convention>` as required, `-coff`, and x86 linker/libraries. Account for STDCALL/C decoration and cleanup. The host assembler being XP-compatible does not make an arbitrary assembled application XP-compatible: APIs, imports and linker settings also matter.

Linux x64: assemble `-elf64`, then use GCC/Clang as a linker driver when relying on C runtime main/startup. It is not compiling the ASM. Match PROC SYSTEMV and external prototypes. Use a real linker test; COFF and ELF objects are not interchangeable despite both containing x86-64 code.

For building UASM itself, inspect the checkout's Makefile-Linux-GCC-64.mak, Makefile-Linux-Clang-64.mak and common makefile. Do not revive old warning-suppression workarounds or assume the current machine has a particular compiler installed. This pack primarily teaches application assembly, not maintenance of every compiler/toolchain variant.

## ELF64 PIC, PIE and shared libraries

Enable `OPTION ELFPIC:1` before procedures. It is opt-in and ELF64-only. The linker creates the final PLT/GOT; UASM emits relocations with the necessary semantics. Local/non-preemptible references can remain direct; default-visible interposable symbols must retain ELF semantics. A symbol in another OBJ is not automatically a shared-library import, and a function defined in the same SO is not necessarily non-preemptible.

Visibility applies after a PUBLIC/external declaration:

```asm
public helper
option elfvisibility:helper:hidden
```

Supported values are DEFAULT, HIDDEN and PROTECTED. Use HIDDEN for genuinely internal exports; do not hide symbols simply to force a link to succeed. PLT-capable external calls allow the linker to resolve static/local cases or provide shared-library linkage as appropriate.

Address materialization is handled transparently where safe (`ADDR`, supported LEA/OFFSET and full-width load forms). A load/store through an imported data symbol may require two operations. Use the explicit helper rather than assuming a spare register:

```asm
option elfpic:1
extern counter:dword, scalar:real8
.code
mov eax,GOT(counter,r11)
mov GOT(counter,r11),eax
movsd xmm0,GOT(scalar,r10)
lock inc GOT(counter,r11)
```

The second argument names the clobbered temporary. It must be an allowed 64-bit GP register that does not conflict with operands, implicit registers or the active frame/stack. There is no OPTION GOT_TEMPORARY requirement. Ambiguous/unsafe unannotated operations fail instead of silently corrupting a register. Do not generalize `mov eax,counter` into a safe value-load example for all PIC imports; use GOT explicitly when reading the imported storage. A supported full-width load may transparently perform GOT indirection; confirm the desired value versus address semantics using the fixture for that operand width.

The packaged Linux project is the preferred complete example: `samplelib.asm` builds the SO; console/GTK clients share `api.inc`; it demonstrates exported data, private constants, a hidden helper, typed fields, atomic GOT access and DWARF. On Linux:

```sh
make ASSEMBLER=/absolute/path/to/uasm console check
make ASSEMBLER=/absolute/path/to/uasm
make ASSEMBLER=/absolute/path/to/uasm check-gui
```

The console needs the compiler/linker, make, Python and GDB for check; the GUI additionally needs GTK4 development files, pkg-config, a display or Xvfb, DBus and xauth for automated checks. The SO and PIE executable stay together using `$ORIGIN` RUNPATH. Recipes check for text relocations and a non-executable stack. External platform packages remain dependencies, not bundled personal configuration.

## Verification scope

The skill's `scripts/check_examples.py --assembler <path> --output <directory>` assembles bundled sources and checks a known namespace binary. It does not execute the GUI, link Windows APIs on Linux, or prove an instruction can execute on the host CPU. Complete sample build/check commands are separate.

In a UASM checkout, `go run .` from regress runs the suite; `-asm <path>` selects the binary, `-filter <text>` narrows tests, `go test ./...` tests the runner. Every assembly run clears results. Preserve failure artifacts before starting another run. The runner normalizes only documented non-semantic metadata; never replace all EXPs merely to obtain green results.
