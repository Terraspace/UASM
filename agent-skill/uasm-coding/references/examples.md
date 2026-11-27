# Example catalog

Paths below are relative to this skill folder. These are source projects copied from the recorded UASM snapshot, plus one compact language probe. They do not require the original author's personal assembly includes. Platform libraries/tools still apply.

| Directory under assets/examples | What to adapt |
|---|---|
| win64/namespaces | Balanced shared namespaces; private/public linkage across two objects; macro lookup; typed structs; static/instance OO and debugger locals |
| win64/nested_calls | Explicit return types, result spills, siblings, depth three, re-entry, pointers and REAL8 |
| win64/oo_tour | CLASS/OINTERFACE, owned Company, Init/Destroy, direct/virtual dispatch, typed memory/LOCAL/ASSUME receivers, namespace helpers, arrows and vectorcall |
| win64/direct2d_namespaces | Win32 window, COM declarations, Direct2D drawing, typed arrow calls and resource lifetimes |
| linux64/pltgot-gtk | Console and GTK4 PIE frontends, shared SO, exported data/GOT, SYSVHOME and DWARF/GDB checks |
| probes/interfaces.asm | Self-contained simulated COM/RAW tables, explicit prototypes, LOCAL receivers and nested return values |
| probes/literals.asm | Narrow/wide literal bytes, terminators and call forms checked at runtime |
| probes/namespace_scope.asm | Known-output binary for nested/reopened scope and macro expansion-site resolution |
| probes/language.asm | STRUCT/TYPEDEF/LOCAL, ASSUME, explicit typed memory and HLL syntax; assembly-only routine |

## Building the Windows projects outside the UASM repo

Use an x64 Native Tools Command Prompt, clear any unintended `UASM` environment options, change into a project directory, then:

```bat
build.cmd C:\tools\uasm\UASM.exe
```

Pass the explicit assembler path: the copied scripts retain their repository-relative fallback paths, which are not valid in a standalone skill installation. Generated files are under each project's build directory. Namespace build.cmd executes its console test; run the other console executables explicitly. The Direct2D executable is interactive and opens a window; do not start it as an unattended test without arranging shutdown. oo_tour/test.cmd checks both RSP and RBP and restores the RSP build. The VCXPROJ files support UasmPath overrides; do not blindly trust a relative fallback when extracted elsewhere.

The three Win64 console projects print PASS and exit zero. Keep the resulting PDB beside each executable to inspect initialized locals/parameters in Visual Studio. OO's uninitialized fields and freed pointers should not be treated as valid debugger values.

For probe interfaces/literals, assemble `-win64 -Zi8`, then link with `/SUBSYSTEM:CONSOLE /ENTRY:Start` and kernel32.lib; successful programs exit zero. The language probe is not a program entry point and should not be executed.

## Linux project

Use the build/check commands in [platforms](platforms.md). Pass `ASSEMBLER=/absolute/path/to/uasm` to every make invocation when the repository-relative default is unavailable. Main sources are console.asm, gtk.asm and samplelib.asm. `api.inc` defines their shared ABI. `debug_check.py` and `verify.py` supply concrete expectations; read them when modifying debugger or linker behavior.

## Quick portable validation

```text
python scripts/check_examples.py --assembler /path/to/uasm --output /path/to/temporary/objects
```

This needs Python 3.10+ and a compatible UASM binary, no SDK/linker. It compiles all twelve ASM files to COFF, ELF64 or binary as appropriate, and compares namespace_scope.bin to hand-calculated bytes. The JSON report distinguishes individual outcomes. It does not overwrite regression EXP files or claim cross-platform runtime verification.
